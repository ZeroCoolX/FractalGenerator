// Something worth noting is that I cannot get this to work if I put the class method implementations
// In the .cpp file.
// If they are in the .h file it works beautifully.
// If they are in the .cpp file the object bitmap, and perhaps other unique_pointers memory allocation
// is lost. Its insanity
// So for right now - so I don't go insane (Actually too late) - Keep it in the .h file until I find
// someone, anyone, PLEASE - explain how this makes any sense
#ifndef FRACTAL_GENERATOR_H_INCLUDED
#define FRACTAL_GENERATOR_H_INCLUDED
#include<string>
#include <memory>
#include <math.h>
#include <iostream>
using namespace std;

#include "zoom.h"
#include "zoom_list.h"
#include "bitmap.h"
#include "mandelbrot.h"
namespace zerocoolsoftware{

class fractal_generator{
private:
    int _width;
    int _height;
    unique_ptr<int[]> _histogram;
    unique_ptr<int[]> _fractal;
    zoom_list _zooms;
    bitmap _bitmap;

public:
        fractal_generator(int width, int height);

        virtual ~fractal_generator();

        void calculateIterations();/*{
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
        }*/

        void drawFractal();/*{
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
        }*/

        void addZoom(const zoom &z);/*{
            _zooms.addZoom(z);
        }*/

        void writeBitmap(string name);/*{
            _bitmap.createBitmapFile("fractal_bitmap.bmp");
        }*/

    };

}

#endif // FRACTAL_GENERATOR_H_INCLUDED
