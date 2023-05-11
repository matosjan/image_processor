#include "image.h"

Image::Image(int height, int width) {
    field_.resize(height, std::vector<Color>(width, {.R = 255, .G = 255, .B = 255}));
}

Color& Image::GetPixel(int x, int y) {
    return field_[x][y];
}

Color Image::GetPixel(int x, int y) const {
    return field_[x][y];
}

size_t Image::GetHeight() const {
    return field_.size();
}

size_t Image::GetWidth() const {
    return field_[0].size();
}

void Image::ResizeHeight(int new_height) {
    if (new_height < static_cast<int>(field_.size())) {
        field_.resize(new_height);
    }
}

void Image::ResizeWidth(int new_width) {
    if (new_width < static_cast<int>(field_[0].size())) {
        for (size_t i = 0; i < field_.size(); ++i) {
            field_[i].resize(new_width);
        }
    }
}
