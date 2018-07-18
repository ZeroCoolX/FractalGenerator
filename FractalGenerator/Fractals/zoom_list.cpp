#include "zoom_list.h"

namespace zerocoolsoftware{

zoom_list::zoom_list(int width, int height) : _screenWidth(width), _screenHeight(height){

}

void zoom_list::addZoom(const zoom &z){
    zooms.push_back(z);

    // Calcualte how far the user clicked from the center 0,0 (in fractal coordinates)
    _xCenter += (z.coordinateX - _screenWidth/2) * _zoomScale;
    _yCenter += (z.coordinateY - _screenHeight/2) * _zoomScale;
    _zoomScale *= z.scale;
}

pair<double, double> zoom_list::doZoom(int x, int y){
    double xFractal = (x - _screenWidth/2)*_zoomScale + _xCenter;
    double yFractal = (y - _screenHeight/2)*_zoomScale + _yCenter;
    return pair<double, double>(xFractal, yFractal);
}

};
