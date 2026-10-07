#include "Bitmap.h"
#include <fstream>

using namespace std;

static bool load_file_bytes(const char *path, unsigned char *headers, const int size)
{
    ifstream file(path, ios::binary);

    if (!file)
    {
        return false;
    }

    file.read(reinterpret_cast<char *>(headers), size);
    return file.gcount() == size;
}

bool Bitmap::Load(const char *path)
{
    unsigned char headers[54]{};

    if (!load_file_bytes(path, headers, 54))
    {
        return false;
    }

    if (headers[0] != 'B' || headers[1] != 'M')
    {
        return false;
    }

    width = *reinterpret_cast<int *>(&headers[18]);
    height = *reinterpret_cast<int *>(&headers[22]);
    unsigned int dataOffset = *reinterpret_cast<unsigned int *>(&headers[10]);

    ifstream file(path, ios::binary);
    file.seekg(dataOffset, ios::beg);
    pixels = new Pixel[width * height];

    int padding = (4 - (width * 3) % 4) % 4;

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            unsigned char colors[3];
            file.read(reinterpret_cast<char *>(colors), 3);

            int index = y * width + x;

            pixels[index].B = colors[0];
            pixels[index].G = colors[1];
            pixels[index].R = colors[2];
            pixels[index].Y = 0.2126 * pixels[index].R + 0.7152 * pixels[index].G + 0.0722 * pixels[index].B;
        }

        file.seekg(padding, ios::cur);
    }

    return true;
}

Bitmap::Bitmap(char *path)
{
    Load(path);
}

Pixel Bitmap::GetPixel(int x, int y) const
{
    int index = y * width + x;
    return pixels[index];
}
