#include<complex>
#include<cstdint>
using namespace std;

#include "mandelbrot.h"

namespace zerocoolsoftware
{
mandelbrot::mandelbrot(){

}

// Scale the given pixel coordinate to be within [-1,1)
double mandelbrot::scale(double rawCoordinate, int sizeLimit, int xOffset){
    return (rawCoordinate - sizeLimit/2 - xOffset) * (2.0/SCALE_FACTOR);
}

uint8_t mandelbrot::colorizeIteration(int iteration){
    // map to a color [0,1]
    uint8_t color = (uint8_t)(256 * (double)iteration/mandelbrot::MAX_ITERATIONS);
    // Since we defined color to be a uint8_t it will still work in terms of the program (355 inclusive)
    color = color * color * color;
    return color;
}

int mandelbrot::getIteration(double x, double y){
    // If ever gets higher than 2 it will escape to infinity
    complex<double> currentComplex = 0;
    // complex number for which we are testing whether or not its in the M-Set
    complex<double> pointOnComplexPlane(x, y);

    int iteration = 0;

    while(iteration < MAX_ITERATIONS){
        currentComplex = currentComplex*currentComplex + pointOnComplexPlane;

        // The number of iterations it takes to break out of the mandelbrot set determines the
        // color of the pixel
        if(abs(currentComplex) > 2){
            break;
        }

        ++iteration;
    }

    return iteration;
}

mandelbrot::~mandelbrot(){
    // Destructor
}
}
