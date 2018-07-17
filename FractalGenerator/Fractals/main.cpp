#include <iostream>
#include "bitmap.h"

using namespace std;
using namespace zerocoolsoftware;

int main()
{
    const int WIDTH = 800;
    const int HEIGHT = 600;

    bitmap fractalBitmap(WIDTH, HEIGHT);

    pixel p;
    p = {0, 0, 255, 0, 0};

    // Just hacking scaaling right now
    double minVal = 9999;
    double maxVal = -9999;

    // Make it all red!
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            double xFractal = (x - WIDTH/2) * (2.0/WIDTH); // range from  [-400,399] then [-1, 0.9999999]
            double yFractal = (y - HEIGHT/2) * (2.0/HEIGHT); // range from  [-300,299] then [-1, 0.9999999]

            // always set min/max to the least/most x we've seen
            if(yFractal < minVal){
                minVal = xFractal;
            }
            if(yFractal > maxVal){
                maxVal = xFractal;
            }
        }
    }

    cout << "min("<<minVal<<") : max("<<maxVal<<")" << endl;

    fractalBitmap.setPixel(p);

    fractalBitmap.createBitmapFile("fractal_bitmap.bmp");


    cout << " finished " << endl;
    return 0;
}
