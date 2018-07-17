#include <iostream>
#include <cstdint>
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

    // Make it all green!
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            double xFractal = (x - WIDTH/2) * (2.0/WIDTH); // range from  [-400,399] then [-1, 0.9999999]
            double yFractal = (y - HEIGHT/2) * (2.0/HEIGHT); // range from  [-300,299] then [-1, 0.9999999]

            int iterations = mandelbrot::getIterations(xFractal, yFractal);

            // map to a color [0,1]
            uint8_t green = (uint8_t)(256 * (double)iterations/mandelbrot::MAX_ITERATIONS);

            // set the pixel
            pixel currentPixel = {x, y, 0, green, 0};
            fractalBitmap.setPixel(currentPixel);

            // always set min/max to the least/most x we've seen
            if(green < minVal){
                minVal = green;
            }
            if(green > maxVal){
                maxVal = green;
            }
        }
    }

    cout << "min("<<minVal<<") : max("<<maxVal<<")" << endl;

    fractalBitmap.createBitmapFile("fractal_bitmap.bmp");


    cout << " finished " << endl;
    return 0;
}
