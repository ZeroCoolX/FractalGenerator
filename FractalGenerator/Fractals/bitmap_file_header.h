#ifndef BITMAP_FILE_HEADER_H_INCLUDED
#define BITMAP_FILE_HEADER_H_INCLUDED

#include<cstdint>

using namespace std;

#pragma pack(2)


namespace zerocoolsoftware{

struct bitmap_file_header
{
    char header[2] {'B','M'};
    int32_t fileSize;
    int32_t reserved {0};
    int32_t dataOffset;
};

}

#endif // BITMAP_FILE_HEADER_H_INCLUDED
