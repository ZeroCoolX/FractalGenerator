#include <iostream>
#include <string>
using namespace std;

#include "zoom.h"
#include "fractal_generator.h"
using namespace zerocoolsoftware;

void run_fractal(string filename, int zoomInTo, zoom *zooms);

int main()
{
    string filename = "fractal_bitmap";
    cout << "Booting up fractal generator..." << endl;


    zoom zooms[5] = {
    zoom(307, 189, 0.1),
    zoom(169, 433, 0.1),
    zoom(409, 294, 0.1),
    zoom(781, 366, 0.1),
    zoom(81, 320, 0.1)
    };

    run_fractal(filename,0, zooms);

    for(int i = 0; i < 1; ++i){
        string fixed_filename = (filename + "" + std::to_string(i));
        run_fractal(fixed_filename, (i+1), zooms);
    }
}

void run_fractal(string filename, int zoomInTo, zoom *zooms){

    cout << "Generating fractal with "<< zoomInTo << " many zoom(s) : " << endl;

    fractal_generator fractalGen(800, 600);

    for(int i = 0; i < zoomInTo; ++i){
        fractalGen.addZoom(zooms[i]);
    }

    fractalGen.addColorRange(0.0, rgb_color(0,   7,   100));
    fractalGen.addColorRange(0.16, rgb_color(32,  107, 203));
    fractalGen.addColorRange(0.42, rgb_color(237, 255, 255));
    fractalGen.addColorRange(0.6425, rgb_color(255, 170, 0));
    fractalGen.addColorRange(0.8575, rgb_color(0,   2,   0));

    fractalGen.run(filename);
}
