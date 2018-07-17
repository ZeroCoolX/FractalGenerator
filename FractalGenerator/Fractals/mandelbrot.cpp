#include<complex>
#include <memory>
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

double mandelbrot::colorizeIteration(int iteration, int totalIterations, unique_ptr<int[]> &histogram){
    double colorHue = 0; // [0,1]
    // sum up all the pixels that have less iterations than this one including this number of iterations
    // As we move from pixels of a high number of iterations to a low number of iterations we calculate a color for each group of the
    // particular number of iterations.
    // Moving to the next group - we increase the number value of that color proportionately to the number of pixels that had the last number of iterations
    for(int i = 0; i <= iteration; ++i){
        // number between 0 and 1
        colorHue += ((double)histogram[i])/totalIterations;
    }
    return colorHue;
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
