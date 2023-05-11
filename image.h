#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

struct Color {
    uint8_t R = 0;
    uint8_t G = 0;
    uint8_t B = 0;
};

class Image {
public:
    Image(int height, int width);

    Color& GetPixel(int x, int y);
    Color GetPixel(int x, int y) const;

    size_t GetHeight() const;
    size_t GetWidth() const;

    void ResizeWidth(int new_width);
    void ResizeHeight(int new_height);

private:
    std::vector<std::vector<Color>> field_;
};
