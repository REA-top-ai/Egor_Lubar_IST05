#include <iostream>
#include "Bitmap.h"

using namespace std;

int main(const int argc, char **argv)
{
    if (argc < 2)
    {
        cout << "Укажите путь к BMP-файлу\n";
        return 1;
    }

    char *path = argv[1];
    Bitmap image(path);
    Pixel pixel = image.GetPixel(0, 0);

    cout << "Левый нижний пиксель: "
         << "R: " << static_cast<int>(pixel.R)
         << " G: " << static_cast<int>(pixel.G)
         << " B: " << static_cast<int>(pixel.B)
         << " Y: " << pixel.Y
         << "\n";

    return 0;
}
