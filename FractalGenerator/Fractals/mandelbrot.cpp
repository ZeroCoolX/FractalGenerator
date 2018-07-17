#include<complex>
using namespace std;

#include "mandelbrot.h"

namespace zerocoolsoftware
{
mandelbrot::mandelbrot(){

}

int mandelbrot::getIterations(double x, double y){
    // If ever gets higher than 2 it will escape to infinity
    complex<double> currentComplex = 0;
    // complex number for which we are testing whether or not its in the M-Set
    complex<double> pointOnComplexPlane(x, y);

    int iterations = 0;

    while(iterations < MAX_ITERATIONS){
        currentComplex = currentComplex*currentComplex + pointOnComplexPlane;

        // The number of iterations it takes to break out of the mandelbrot set determines the
        // color of the pixel
        if(abs(currentComplex) > 2){
            break;
        }

        ++iterations;
    }

    return iterations;
}

mandelbrot::~mandelbrot(){
    // Destructor
}
}
