#ifndef ZOOM_LIST_H_INCLUDED
#define ZOOM_LIST_H_INCLUDED

#include <vector>
#include <utility>
using namespace std;

#include "zoom.h"

namespace zerocoolsoftware{

class zoom_list{
private:
    double _xCenter{0};
    double _yCenter{0};
    double _zoomScale{1};

    int _screenWidth{0};
    int _screenHeight{0};
    vector<zoom> zooms;

public:
    zoom_list(int width, int height);
    void addZoom(const zoom &z);
    pair<double, double> doZoom(int x, int y);
};

}


#endif // ZOOM_LIST_H_INCLUDED
