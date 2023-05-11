#include "filters.h"
#include "image.h"

void NegativeFilter::ApplyFilter(Image& img) const {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            img.GetPixel(i, j).R = 255 - img.GetPixel(i, j).R;
            img.GetPixel(i, j).G = 255 - img.GetPixel(i, j).G;
            img.GetPixel(i, j).B = 255 - img.GetPixel(i, j).B;
        }
    }
}

void GrayscaleFilter::ApplyFilter(Image& img) const {
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            img.GetPixel(i, j).R =
                0.299 * img.GetPixel(i, j).R + 0.587 * img.GetPixel(i, j).G + 0.114 * img.GetPixel(i, j).B;
            img.GetPixel(i, j).G = img.GetPixel(i, j).R;
            img.GetPixel(i, j).B = img.GetPixel(i, j).R;
        }
    }
}

void CropFilter::ApplyFilter(Image& img) const {
    img.ResizeHeight(new_height_);
    img.ResizeWidth(new_width_);
}

void MatrixBaseFilter::ApplyFilter(Image& img) const {
    std::vector<std::vector<int>> matrix = GetMatrixCoefficients();
    Image tmp_img = img;
    for (size_t i = 0; i < tmp_img.GetHeight(); ++i) {
        for (size_t j = 0; j < tmp_img.GetWidth(); ++j) {
            int new_r = matrix[1][1] * static_cast<int>(tmp_img.GetPixel(i, j).R);
            int new_g = matrix[1][1] * static_cast<int>(tmp_img.GetPixel(i, j).G);
            int new_b = matrix[1][1] * static_cast<int>(tmp_img.GetPixel(i, j).B);
            for (auto diff : NEW_COORDS_) {
                size_t new_x =
                    std::max(0, std::min(static_cast<int>(tmp_img.GetHeight()) - 1, static_cast<int>(i) + diff.first));
                size_t new_y =
                    std::max(0, std::min(static_cast<int>(tmp_img.GetWidth()) - 1, static_cast<int>(j) + diff.second));
                new_r += matrix[diff.first + 1][diff.second + 1] * static_cast<int>(tmp_img.GetPixel(new_x, new_y).R);
                new_g += matrix[diff.first + 1][diff.second + 1] * static_cast<int>(tmp_img.GetPixel(new_x, new_y).G);
                new_b += matrix[diff.first + 1][diff.second + 1] * static_cast<int>(tmp_img.GetPixel(new_x, new_y).B);
            }
            img.GetPixel(i, j).R = static_cast<uint8_t>(std::min(255, std::max(0, new_r)));
            img.GetPixel(i, j).G = static_cast<uint8_t>(std::min(255, std::max(0, new_g)));
            img.GetPixel(i, j).B = static_cast<uint8_t>(std::min(255, std::max(0, new_b)));
        }
    }
}

std::vector<std::vector<int>> SharpeningFilter::GetMatrixCoefficients() const {
    return MATRIX_FOR_SHARP_;
}

void EdgeDetectionFilter::ApplyFilter(Image& img) const {
    GrayscaleFilter::ApplyFilter(img);
    MatrixBaseFilter::ApplyFilter(img);
    for (size_t i = 0; i < img.GetHeight(); ++i) {
        for (size_t j = 0; j < img.GetWidth(); ++j) {
            if (static_cast<double>(img.GetPixel(i, j).R) > threshold_ * MAX_SHADE_) {
                img.GetPixel(i, j).R = 255;
            } else {
                img.GetPixel(i, j).R = 0;
            }
            img.GetPixel(i, j).G = img.GetPixel(i, j).R;
            img.GetPixel(i, j).B = img.GetPixel(i, j).R;
        }
    }
}

std::vector<std::vector<int>> EdgeDetectionFilter::GetMatrixCoefficients() const {
    return MATRIX_FOR_EDGE_;
}
