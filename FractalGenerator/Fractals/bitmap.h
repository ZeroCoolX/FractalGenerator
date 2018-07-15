#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include<string>
#include<cstdint>
#include<memory>
using namespace std;

#include "pixel.h"
#include "bitmap_file_header.h"
#include "bitmap_info_header.h"

namespace zerocoolsoftware {

class bitmap
{
private:
    const int PIXEL_COLORS = 3;

    int _width{0};
    int _height{0};
    unique_ptr<uint8_t []>_pixels{nullptr};

public:
    bitmap(int width, int height);
    void createBitmapHeaders(bitmap_file_header &fileHeader, bitmap_info_header &infoHeader);
    bool writeToFile(string filename, bitmap_file_header &fileHeader, bitmap_info_header &infoHeader);
    bool createBitmapFile(string filename);
    void setPixel(pixel &p);
    int getBitmapSize();
    virtual ~bitmap();
};

}


#endif // BITMAP_H_INCLUDED
