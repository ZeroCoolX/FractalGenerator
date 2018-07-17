#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>

#include "pixel.h"
#include "mandelbrot.h"
#include "bitmap.h"
#include "zoom.h"

using namespace std;
using namespace zerocoolsoftware;

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

    bitmap fractalBitmap(WIDTH, HEIGHT);

    // Histogram - stores the number of pixels that corresponds to each number of iterations
    unique_ptr<int[]> histogram(new int[mandelbrot::MAX_ITERATIONS]{0});

    // Storing the number of iterations per pixel
    unique_ptr<int[]> fractal(new int[WIDTH*HEIGHT]{0});

    // Store the number of iterations per pixel and build the histogram as well as scale
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            // Scale the given pixel coordinate to be within [-1,1)
            double xFractal = mandelbrot::scale(x, WIDTH, 200); // range from  [-400,399] then [-1, 0.9999999]
            double yFractal = mandelbrot::scale(y, HEIGHT); // range from  [-300,299] then [-1, 0.9999999]

            // Calculate the iteration for this pixel
            int iteration = mandelbrot::getIteration(xFractal, yFractal);

            fractal[y*WIDTH + x] = iteration;

            // Increment the index for this iteration - but do not store those pixels in the mandelbrot set (aka black pixels)
            if(iteration != mandelbrot::MAX_ITERATIONS){
                ++histogram[iteration];
            }
        }
    }

    // Calculate total of all pixels in histogram
    int totalIterations = 0;
    for(int i = 0; i < mandelbrot::MAX_ITERATIONS; ++i){
        totalIterations += histogram[i];
    }

    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){

            uint8_t red = 0;
            uint8_t green = 0;
            uint8_t blue = 0;


            // pull the iteration from the fractal pixel map
            int iteration = fractal[y * WIDTH + x];

            if(iteration != mandelbrot::MAX_ITERATIONS){
                // Colorize the iteration
                double hue = mandelbrot::colorizeIteration(iteration,totalIterations, histogram);
                green = pow(255, hue);
            }


            // set the pixel
            pixel currentPixel = {x, y, red, green, blue};
            fractalBitmap.setPixel(currentPixel);
        }
    }

    fractalBitmap.createBitmapFile("fractal_bitmap.bmp");


    cout << " finished " << endl;
    return 0;
}
