#include <iostream>
#include <fstream>

static bool load_file_bytes(const char *path, unsigned char *headers, const int size)
{

    std::ifstream file(path, std::ios::binary);

    if (!file)
    {
        return false;
    }

    file.read(reinterpret_cast<char *>(headers), size);
    return file.gcount() == size;
}

int main(const int argc, char **argv)
{
    const char *path = argc > 1 ? argv[1] : "image.bmp";
    unsigned char headers[54]{};

    if (!load_file_bytes(path, headers, 54))
    {
        std::cout << "Не удалось прочитать файл: " << path << '\n';
        return 1;
    }

    if (headers[0] != 'B' || headers[1] != 'M')
    {
        std::cout << "Это не BMP-файл\n";
        return 1;
    }

    std::cout << "Это BMP-файл\n";
    std::cout << "2b headers.bitmap_signature : " << headers[0] << headers[1] << "\n";
    std::cout << "4b headers.bitmap_file_size : " << (headers[2] | (headers[3] << 8) | (headers[4] << 16) | (headers[5] << 24)) << "\n";
    std::cout << "4b headers.bitmap_data_offset : " << (headers[10] | (headers[11] << 8) | (headers[12] << 16) | (headers[13] << 24)) << "\n";
    std::cout << "4b headers.bitmap_info_header_size : " << (headers[14] | (headers[15] << 8) | (headers[16] << 16) | (headers[17] << 24)) << "\n";
    std::cout << "4b headers.bitmap_width : " << (headers[18] | (headers[19] << 8) | (headers[20] << 16) | (headers[21] << 24)) << "\n";
    std::cout << "4b headers.bitmap_height : " << (headers[22] | (headers[23] << 8) | (headers[24] << 16) | (headers[25] << 24)) << "\n";
    std::cout << "2b headers.bitmap_planes : " << (headers[26] | (headers[27] << 8)) << "\n";
    std::cout << "2b headers.bitmap_bits_per_pixel : " << (headers[28] | (headers[29] << 8)) << "\n";
    std::cout << "4b headers.bitmap_compression : " << (headers[30] | (headers[31] << 8) | (headers[32] << 16) | (headers[33] << 24)) << "\n";
    std::cout << "4b headers.bitmap_image_size : " << (headers[34] | (headers[35] << 8) | (headers[36] << 16) | (headers[37] << 24)) << "\n";
    std::cout << "4b headers.bitmap_XpixelsPerM : " << (headers[38] | (headers[39] << 8) | (headers[40] << 16) | (headers[41] << 24)) << "\n";
    std::cout << "4b headers.bitmap_YpixelsPerM : " << (headers[42] | (headers[43] << 8) | (headers[44] << 16) | (headers[45] << 24)) << "\n";
    std::cout << "4b headers.bitmap_ColorsUsed : " << (headers[46] | (headers[47] << 8) | (headers[48] << 16) | (headers[49] << 24)) << "\n";
    std::cout << "4b headers.bitmap_ColorsImportant : " << (headers[50] | (headers[51] << 8) | (headers[52] << 16) | (headers[53] << 24)) << "\n";

    return 0;
}
