#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED

#include<cstdint>
using namespace std;

namespace zerocoolsoftware{

// Pass two coordinates between -1,1 and for all values within the Mandlebrot set draw the pixel color representation
class mandelbrot{
public:
    static const int MAX_ITERATIONS = 500;
    static const int SCALE_FACTOR = 600;

public:
    mandelbrot();
    virtual ~mandelbrot();

    static int getIteration(double x, double y);
    static double scale(double rawCoordinate, int sizeLimit, int xOffset=0);
    static uint8_t colorizeIteration(int iteration);
};

}


#endif // MANDELBROT_H_INCLUDED
