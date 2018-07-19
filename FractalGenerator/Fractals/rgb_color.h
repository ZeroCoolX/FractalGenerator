#ifndef RGB_COLOR_H_INCLUDED
#define RGB_COLOR_H_INCLUDED

namespace zerocoolsoftware{

struct rgb_color{
    double r;
    double g;
    double b;

    rgb_color(double r, double g, double b);
};

    rgb_color operator-(const rgb_color &first, const rgb_color &second);
};

#endif // RGB_COLOR_H_INCLUDED
