#ifndef FRACTAL_GENERATOR_H_INCLUDED
#define FRACTAL_GENERATOR_H_INCLUDED
#include<string>
#include <memory>
#include <vector>
#include <math.h>
#include <iostream>
using namespace std;

#include "zoom.h"
#include "zoom_list.h"
#include "bitmap.h"
#include "mandelbrot.h"
#include "rgb_color.h"
namespace zerocoolsoftware{

class fractal_generator{
private:
    int _width;
    int _height;
    unique_ptr<int[]> _histogram;
    unique_ptr<int[]> _fractal;
    zoom_list _zooms;
    bitmap _bitmap;

    vector<int> _rangeValues;
    vector<rgb_color> _rangleColors;
    vector<int> _totalColorsInRange;

    bool _initialRangeSet{false};

private:
    void calculateIterations();
    int calculateTotalPixelsInHistogram();
    void calculateColorRangeTotals();
    int calculateColorRangeFromIteration(int iteration) const;
    void drawFractal();
    void writeBitmap(string name);

public:
    fractal_generator(int width, int height);
    virtual ~fractal_generator();
    void addZoom(const zoom &z);
    void addColorRange(double rangeEnd, const rgb_color &color);
    void run(string name);
};

}

#endif // FRACTAL_GENERATOR_H_INCLUDED
