#include<iostream>
#include<fstream>
#include "bitmap.h"
#include "bitmap_file_header.h"
#include "bitmap_info_header.h"

using namespace std;
using namespace zerocoolsoftware;

namespace zerocoolsoftware {

bitmap::bitmap(int width, int height) : _width(width), _height(height), _pixels(new uint8_t[width*height*3]{}){
}

bool bitmap::createBitmapFile(string fileName)
{
    // create headers
    bitmap_file_header fileHeader;
    bitmap_info_header infoHeader;
    createBitmapHeaders(fileHeader, infoHeader);


    // write headers and pixels to file
    bool success = writeToFile(fileName, fileHeader, infoHeader);

    if(success){
        cout << " Bitmap " << fileName << " successfully written to" << endl;
    }else{
        cout << "Something went terribly wrong while attempting to create the bitmap" << endl;
    }
    return success;
}

void bitmap::createBitmapHeaders(bitmap_file_header &fileHeader, bitmap_info_header &infoHeader)
{
    fileHeader.fileSize = sizeof(bitmap_file_header) + sizeof(bitmap_info_header) + getBitmapSize();
    fileHeader.dataOffset = sizeof(bitmap_file_header) + sizeof(bitmap_info_header);

    infoHeader.width = _width;
    infoHeader.height = _height;
}

bool bitmap::writeToFile(string filename, bitmap_file_header &fileHeader, bitmap_info_header &infoHeader){
    fstream bitmapFile;
    bitmapFile.open(filename, ios::out | ios::binary);

    if(!bitmapFile.is_open()){
        cout << "File: " << filename << " did not open correctly!" << endl;
        return false;
    }

    // Write file header
    bitmapFile.write((char *)&fileHeader, sizeof(fileHeader));
    // Write info header
    bitmapFile.write((char *)&infoHeader, sizeof(infoHeader));
    // Write the rest of the pixels
    bitmapFile.write((char *)_pixels.get(), getBitmapSize());

    bitmapFile.close();
    return true;
}

void bitmap::setPixel(pixel &p){
    // Retrieve pointer to the whole memory block that represents the screen
    uint8_t * pPixel = _pixels.get();
    // Must scale by PIXEL_COLORS (3) because each pixel is 3 bytes
    pPixel += ((p.row * PIXEL_COLORS) * _width) + (p.column * PIXEL_COLORS);

    // little endian format - least sig byte stored left to right (reversed from decimal)
    // since each pPixel is 3 bytes, we should assign the color for each byte of the 3
    uint8_t color = 255;
    pPixel[0] = p.blue;
    pPixel[1] = p.green;
    pPixel[2] = p.red;
}

// Helper that does the bitmap size calculation
int bitmap::getBitmapSize(){
    return (_width * _height * PIXEL_COLORS);
}


bitmap::~bitmap() {
}

}
