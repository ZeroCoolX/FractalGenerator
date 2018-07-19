#include "rgb_color.h"

namespace zerocoolsoftware{

rgb_color::rgb_color(double r, double g, double b) : r(r), g(g), b(b){
}

rgb_color operator-(const rgb_color &first, const rgb_color &second){
    return rgb_color(first.r-second.r, first.g-second.g, first.b-second.b);
}

};
