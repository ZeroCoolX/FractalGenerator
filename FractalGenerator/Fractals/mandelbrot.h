#ifndef MANDELBROT_H_INCLUDED
#define MANDELBROT_H_INCLUDED

namespace zerocoolsoftware{

// Pass two coordinates between -1,1 and for all values within the Mandlebrot set draw the pixel color representation
class mandelbrot{
public:
    static const int MAX_ITERATIONS = 500;

public:
    mandelbrot();
    virtual ~mandelbrot();

    static int getIterations(double x, double y);

};

}


#endif // MANDELBROT_H_INCLUDED
