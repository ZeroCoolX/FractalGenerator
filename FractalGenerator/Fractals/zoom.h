#ifndef ZOOM_H_INCLUDED
#define ZOOM_H_INCLUDED


namespace zerocoolsoftware{

struct zoom{
    int coordinateX{0};
    int coordinateY{0};
    double scale{0.0};
    zoom(int x, int y, double scale): coordinateX(x), coordinateY(y), scale(scale){}
};

}


#endif // ZOOM_H_INCLUDED
