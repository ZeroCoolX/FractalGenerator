#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#include "fractal_generator.h"
#include "mandelbrot.h"
namespace zerocoolsoftware{

void fractal_generator::run(string name){
    calculateIterations();
    calculateColorRangeTotals();
    drawFractal();
    string filename = name+".bmp";
    writeBitmap(filename);
}

void fractal_generator::addColorRange(double rangeEnd, const rgb_color &color){
    _rangeValues.push_back(rangeEnd * mandelbrot::MAX_ITERATIONS);
    _rangleColors.push_back(color);

    // Ensures we do not add a 0.0 range total for the first call
    if(_initialRangeSet){
        _totalColorsInRange.push_back(0);
    }

    _initialRangeSet = true;
}

int fractal_generator::calculateColorRangeFromIteration(int iteration) const{
    int range = 0;
    // Start at 1 because we do not want to process the 0.0 range
    for(int i = 1; i < _rangeValues.size(); ++i){
        range = i;

        if(_rangeValues[i] > iteration){
            break;
        }
    }

    --range;

    assert(range > -1);
    assert(range < _rangeValues.size());

    return range;
}

void fractal_generator::addZoom(const zoom &z){
    _zooms.addZoom(z);
}

void fractal_generator::calculateColorRangeTotals(){
    int rangeIndex = 0;
    for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
            // Get the number of pixels that have i number of iterations
        int pixels = _histogram[i];

        if(i >= _rangeValues[rangeIndex+1]){
            ++rangeIndex;
        }

        _totalColorsInRange[rangeIndex] += pixels;
    }

    int overallTotal = 0;
    for(int val : _totalColorsInRange){
        overallTotal += val;
        cout << "Range Total: " << val << endl;
    }
}




fractal_generator::fractal_generator(int width, int height):
    _width(width),
    _height(height),
    _histogram(new int[mandelbrot::MAX_ITERATIONS]{0}),
    _fractal(new int[width*height]{0}),
    _zooms(width, height),
    _bitmap(width, height)
    {
        _zooms.addZoom(zoom(width/2, height/2, 4.0/width));
    }

fractal_generator::~fractal_generator(){}

void fractal_generator::calculateIterations(){
    // Store the number of iterations per pixel and build the histogram as well as scale
    for(int y = 0; y < _height; ++y){
        for(int x = 0; x < _width; ++x){
            pair<double, double> coordinate = _zooms.doZoom(x, y);

            int iteration = mandelbrot::calculateIterationForPixel(coordinate.first, coordinate.second);

            _fractal[y*_width + x] = iteration;

            // Increment the index for this iteration - but do not store those pixels in the mandelbrot set (aka black pixels)
            if(iteration != mandelbrot::MAX_ITERATIONS){
                ++_histogram[iteration];
            }
        }
    }
}

int fractal_generator::calculateTotalPixelsInHistogram(){
    int total = 0;
    for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
        total += _histogram[i];
    }
    return total;
}

void fractal_generator::drawFractal(){
    int totalPixels = calculateTotalPixelsInHistogram();

    for(int y = 0; y < _height; ++y){
        for(int x = 0; x < _width; ++x){

            // pull the iteration from the fractal pixel map
            int iteration = _fractal[y * _width + x];

            int range = calculateColorRangeFromIteration(iteration);
            int totalPixelsInRange = _totalColorsInRange[range];
            int rangeStart = _rangeValues[range];

            rgb_color &startColor = _rangleColors[range];
            rgb_color &endColor = _rangleColors[range+1];
            rgb_color colorDiff = endColor - startColor;

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;

            if(iteration != mandelbrot::MAX_ITERATIONS){
                int totalPixels = 0;

                // Colorize the iteration
                for(int i = rangeStart; i < iteration; ++i){
                    totalPixels += _histogram[i];
                }
                //double hue = mandelbrot::colorizeIteration(iteration,totalPixels,_histogram);
                red = startColor.r + colorDiff.r * (double)totalPixels/totalPixelsInRange;
                green = startColor.g + colorDiff.g * (double)totalPixels/totalPixelsInRange;
                blue = startColor.b + colorDiff.b * (double)totalPixels/totalPixelsInRange;
            }
            // set the pixel
            pixel currentPixel = {x, y, red, green, blue};
            _bitmap.setPixel(currentPixel);
        }
    }
}


void fractal_generator::writeBitmap(string name){
    _bitmap.createBitmapFile(name);
}
};
