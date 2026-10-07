#ifndef BITMAP_H
#define BITMAP_H

#include "Pixel.h"

class Bitmap
{
private:
    int width;
    int height;
    Pixel *pixels;
    bool Load(const char *path);

public:
    Bitmap(char *path);
    Pixel GetPixel(int x, int y) const;

    ~Bitmap()
    {
        delete[] pixels;
    }
};

#endif
