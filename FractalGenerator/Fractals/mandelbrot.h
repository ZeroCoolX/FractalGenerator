#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED
#include <memory>
#include<cstdint>
using namespace std;

namespace zerocoolsoftware{

// Pass two coordinates between -1,1 and for all values within the Mandlebrot set draw the pixel color representation
class mandelbrot{
public:
    static const int MAX_ITERATIONS = 1000;
    static const int SCALE_FACTOR = 600;

public:
    mandelbrot();
    virtual ~mandelbrot();

    static int calculateIterationForPixel(double x, double y);
    static double scale(double rawCoordinate, int sizeLimit, int xOffset=0);
    static double colorizeIteration(int iteration, int totalIterations, unique_ptr<int[]> &histogram);
};

}


#endif // MANDELBROT_H_INCLUDED
