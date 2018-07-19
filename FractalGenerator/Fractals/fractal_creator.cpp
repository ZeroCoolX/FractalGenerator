#include<string>
#include <math.h>
#include <memory>
using namespace std;

#include "fractal_creator.h"
#include "zoom_list.h"
#include "mandelbrot.h"
#include "pixel.h"
#include "bitmap.h"

#include <iostream>

namespace zerocoolsoftware{

fractal_creator::fractal_creator(int width, int height):  _width(width),
                _height(height),
                _histogram(new int[mandelbrot::MAX_ITERATIONS]{0}),
                _fractal(new int[width*height]{0}),
                _zooms(width, height),
                _bitmap(width, height){_zooms.addZoom(zoom(width/2, height/2, 4.0/width));}

void fractal_creator::calculateIterations(){
    // Store the number of iterations per pixel and build the histogram as well as scale
    for(int y = 0; y < _height; ++y){
        for(int x = 0; x < _width; ++x){
            //system("CLS");
            pair<double, double> coordinate = _zooms.doZoom(x, y);

            // Calculate the iteration for this pixel
            int iteration = mandelbrot::getIteration(coordinate.first, coordinate.second);

            _fractal[y*_width + x] = iteration;

            // Increment the index for this iteration - but do not store those pixels in the mandelbrot set (aka black pixels)
            if(iteration != mandelbrot::MAX_ITERATIONS){
                ++_histogram[iteration];
            }
        }
    }

    /*int cnt = 0;
    for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
        cout << _histogram[i] << " " << flush;
        cnt += _histogram[i];
    }
    cout << cnt << ";" << _width*_height << endl;*/
}

void fractal_creator::drawFractal(){
    // Calculate total of all pixels in histogram
    int totalIterations = 0;
    for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
        totalIterations += _histogram[i];
    }

        cout << "total iterations : " << totalIterations << endl;

    for(int y = 0; y < _height; ++y){
        for(int x = 0; x < _width; ++x){

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;


            // pull the iteration from the fractal pixel map
            int iteration = _fractal[y * _width + x];

            if(iteration != mandelbrot::MAX_ITERATIONS){
                // Colorize the iteration
                double hue = mandelbrot::colorizeIteration(iteration,totalIterations, _histogram);
                green = pow(255, hue);
            }


            // set the pixel
            pixel currentPixel = {x, y, red, green, blue};
            _bitmap.setPixel(currentPixel);
        }
    }
}

void fractal_creator::addZoom(const zoom &z){
    _zooms.addZoom(z);
}

void fractal_creator::writeBitmap(string name){
    _bitmap.createBitmapFile("fractal_bitmap.bmp");
}


fractal_creator::~fractal_creator(){

}

};
