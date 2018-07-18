#ifndef FRACTAL_CREATOR_H_INCLUDED
#define FRACTAL_CREATOR_H_INCLUDED

#include<string>
using namespace std;

#include "zoom.h"

namespace zerocoolsoftware{

class fractal_creator{
public:
    fractal_creator();
    virtual ~fractal_creator();

    void calculateIteration();
    void drawFractal();
    void addZoom(const zoom &z);
    void writeBitmap(string name);
};

}


#endif // FRACTAL_CREATOR_H_INCLUDED
