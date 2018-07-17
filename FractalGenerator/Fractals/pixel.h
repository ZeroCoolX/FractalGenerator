#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include<cstdint>

using namespace std;

namespace zerocoolsoftware {

struct pixel
{
    pixel();
    pixel(int column, int row, uint8_t red, uint8_t green, uint8_t blue) :
        column(column), row(row), red(red), green(green), blue(blue){}

    int column;
    int row;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};

}

#endif // PIXEL_H_INCLUDED
