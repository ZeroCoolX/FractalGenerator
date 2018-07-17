#include <iostream>
#include <cstdint>
#include<memory>

#include "pixel.h"
#include "mandelbrot.h"
#include "bitmap.h"

using namespace std;
using namespace zerocoolsoftware;

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

    bitmap fractalBitmap(WIDTH, HEIGHT);

    // Just hacking scaaling right now
    double minVal = 9999;
    double maxVal = -9999;

    // Histogram - stores the number of pixels that corresponds to each number of iterations
    unique_ptr<int[]> histogram(new int[mandelbrot::MAX_ITERATIONS+1]{0});

    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            // Scale the given pixel coordinate to be within [-1,1)
            double xFractal = mandelbrot::scale(x, WIDTH, 200); // range from  [-400,399] then [-1, 0.9999999]
            double yFractal = mandelbrot::scale(y, HEIGHT); // range from  [-300,299] then [-1, 0.9999999]

            // Calculate the iteration for this pixel
            int iteration = mandelbrot::getIteration(xFractal, yFractal);

            // Increment the index for this iteration
            ++histogram[iteration];

            // Colorize the iteration
            uint8_t color = mandelbrot::colorizeIteration(iteration);

            // set the pixel
            pixel currentPixel = {x, y, 0, color, 0};
            fractalBitmap.setPixel(currentPixel);

            // always set min/max to the least/most x we've seen
            if(color < minVal){
                minVal = color;
            }
            if(color > maxVal){
                maxVal = color;
            }
        }
    }

    cout << "min("<<minVal<<") : max("<<maxVal<<")" << endl;

    fractalBitmap.createBitmapFile("fractal_bitmap.bmp");


    cout << " finished " << endl;
    return 0;
}
