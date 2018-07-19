
#include "fractal_generator.h"

namespace zerocoolsoftware{

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
        }

        void fractal_generator::drawFractal(){
            // Calculate total of all pixels in histogram
            int totalIterations = 0;
            for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
                totalIterations += _histogram[i];
            }

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

        void fractal_generator::addZoom(const zoom &z){
            _zooms.addZoom(z);
        }

        void fractal_generator::writeBitmap(string name){
            _bitmap.createBitmapFile("fractal_bitmap.bmp");
        }
};
