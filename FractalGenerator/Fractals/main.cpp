#include <iostream>
#include <cstdint>
#include <memory>
#include <math.h>
#include <iostream>

#include "pixel.h"
#include "mandelbrot.h"
#include "bitmap.h"
#include "zoom_list.h"
#include "fractal_generator.h"
#include "rgb_color.h"

using namespace std;
using namespace zerocoolsoftware;

int main()
{

    int height = 600;
    string filename = "fractal_bitmap.bmp";

    cout << "Booting up..." << endl;
    cout << "Calculating Fractal iterations..." << endl;
    fractal_generator fractalGen(800, height);

    //fractalGen.addZoom(zoom(307, height-189, 0.1));
    //fractalGen.addZoom(zoom(169, HEIGHT - 433, 0.1));
    //fractalGen.addZoom(zoom(409, HEIGHT - 294, 0.1));
    //fractalGen.addZoom(zoom(781, HEIGHT - 366, 0.1));
    //fractalGen.addZoom(zoom(381, HEIGHT - 320, 0.1));
    fractalGen.calculateIterations();

    cout << "Drawing Fractal..." << endl;
    fractalGen.drawFractal();

    cout << "Writing Fractal to " << filename << "..." << endl;
    fractalGen.writeBitmap(filename);

    cout << "Fractal Generation complete!" << endl;
    return 0;
}
