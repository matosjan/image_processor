#include "bmp.h"

namespace BMP {

const int FILE_TYPE = 0x4d42;
const int BITS_PER_BYTE = 8;

BMPHeader ReadHeader(std::ifstream& in) {
    BMPHeader header;

    LilEndianReadNum(in, header.file_type);
    LilEndianReadNum(in, header.file_size);
    LilEndianReadNum(in, header.reserved1);
    LilEndianReadNum(in, header.reserved2);
    LilEndianReadNum(in, header.offset_data);

    return header;
}

DIBHeader ReadDIB(std::ifstream& in) {
    DIBHeader header;

    LilEndianReadNum(in, header.header_size);
    LilEndianReadNum(in, header.size.width);
    LilEndianReadNum(in, header.size.height);
    LilEndianReadNum(in, header.color_planes);
    LilEndianReadNum(in, header.bits_per_pixel);
    LilEndianReadNum(in, header.compression_method);
    LilEndianReadNum(in, header.bitmap_data_size);
    LilEndianReadNum(in, header.resolution.horizontal);
    LilEndianReadNum(in, header.resolution.vertical);
    LilEndianReadNum(in, header.colors.total);
    LilEndianReadNum(in, header.colors.important);

    return header;
}

void WriteHeader(std::ofstream& out, const BMPHeader& header) {
    WriteNum(out, header.file_type);
    WriteNum(out, header.file_size);
    WriteNum(out, header.reserved1);
    WriteNum(out, header.reserved2);
    WriteNum(out, header.offset_data);
}

void WriteDIBHeader(std::ofstream& out, const DIBHeader& header) {
    WriteNum(out, header.header_size);
    WriteNum(out, header.size.width);
    WriteNum(out, header.size.height);
    WriteNum(out, header.color_planes);
    WriteNum(out, header.bits_per_pixel);
    WriteNum(out, header.compression_method);
    WriteNum(out, header.bitmap_data_size);
    WriteNum(out, header.resolution.vertical);
    WriteNum(out, header.resolution.horizontal);
    WriteNum(out, header.colors.total);
    WriteNum(out, header.colors.important);
}

Image LoadBMP(const std::string& path) {
    std::ifstream in{path, std::ios::binary};
    if (!in.is_open()) {
        throw CustomExceptions("Couldn't open the input file");
    }
    BMPHeader header = ReadHeader(in);
    if (header.file_type != FILE_TYPE) {
        throw CustomExceptions("Wrong input file type!!!");
    }
    DIBHeader dib_header = ReadDIB(in);
    Image image{dib_header.size.height, dib_header.size.width};
    for (auto i = 0; i < dib_header.size.height; ++i) {
        for (auto j = 0; j < dib_header.size.width; ++j) {
            Color c;
            LilEndianReadNum(in, c.R);
            LilEndianReadNum(in, c.G);
            LilEndianReadNum(in, c.B);
            image.GetPixel(dib_header.size.height - i - 1, j) = c;
        }
        auto read_bytes = sizeof(Color) * dib_header.size.width;
        while (read_bytes % 4 != 0) {
            uint8_t padding;
            LilEndianReadNum(in, padding);
            ++read_bytes;
        }
    }
    return image;
}

void SaveBMP(const Image& img, const std::string& path) {
    DIBHeader dib_header;
    dib_header.size.width = img.GetWidth();
    dib_header.size.height = img.GetHeight();
    auto row_length = img.GetWidth() * (dib_header.bits_per_pixel / BITS_PER_BYTE);
    auto padding = ((row_length + (dib_header.bits_per_pixel / BITS_PER_BYTE)) / 4) * 4 - row_length;
    dib_header.bitmap_data_size = img.GetHeight() * row_length;

    BMPHeader header;
    header.file_type = FILE_TYPE;
    header.file_size = sizeof(BMPHeader) + sizeof(DIBHeader) +
                       img.GetHeight() * (img.GetWidth() + padding) * (dib_header.bits_per_pixel / BITS_PER_BYTE);
    header.offset_data = sizeof(BMPHeader) + sizeof(DIBHeader);

    std::ofstream out{path, std::ofstream::binary};
    WriteHeader(out, header);
    WriteDIBHeader(out, dib_header);

    for (size_t i = img.GetHeight(); i > 0; --i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            WriteNum(out, img.GetPixel(i - 1, j).R);
            WriteNum(out, img.GetPixel(i - 1, j).G);
            WriteNum(out, img.GetPixel(i - 1, j).B);
        }
        for (size_t n = 0; n < padding; ++n) {
            WriteNum<char>(out, 0);
        }
    }
    out.close();
}
}  // namespace BMP
