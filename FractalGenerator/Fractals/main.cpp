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

    // Make it all red!
    for(int y = 0; y < HEIGHT; ++y){
        for(int x = 0; x < WIDTH; ++x){
            p.row = y;
            p.column = x;
            fractalBitmap.setPixel(p);
        }
    }

    fractalBitmap.setPixel(p);

    fractalBitmap.createBitmapFile("fractal_bitmap.bmp");


    cout << " finished " << endl;
    return 0;
}
