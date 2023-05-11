#pragma once

#include "image.h"
#include "util.h"

class BaseFilter {
public:
    virtual void ApplyFilter(Image& img) const = 0;
    virtual ~BaseFilter(){};
};

class NegativeFilter : public BaseFilter {
public:
    void ApplyFilter(Image& img) const override;
    ~NegativeFilter(){};
};

class GrayscaleFilter : public virtual BaseFilter {
public:
    void ApplyFilter(Image& img) const override;
    ~GrayscaleFilter(){};
};

class CropFilter : public BaseFilter {
public:
    CropFilter(int width, int height) : new_width_(width), new_height_(height){};
    void ApplyFilter(Image& img) const override;
    ~CropFilter(){};

private:
    int new_width_;
    int new_height_;
};

class MatrixBaseFilter : public virtual BaseFilter {
public:
    void ApplyFilter(Image& img) const override;
    virtual std::vector<std::vector<int>> GetMatrixCoefficients() const = 0;

private:
    const std::vector<std::pair<int, int>> NEW_COORDS_ = {{-1, 1}, {0, 1},   {1, 1},  {-1, 0},
                                                          {1, 0},  {-1, -1}, {0, -1}, {1, -1}};
};

class SharpeningFilter : public MatrixBaseFilter {
public:
    std::vector<std::vector<int>> GetMatrixCoefficients() const override;
    ~SharpeningFilter(){};

private:
    const std::vector<std::vector<int>> MATRIX_FOR_SHARP_ = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
};

class EdgeDetectionFilter : public virtual MatrixBaseFilter, public virtual GrayscaleFilter {
public:
    EdgeDetectionFilter(double threshold) : threshold_(threshold){};
    void ApplyFilter(Image& img) const override;
    std::vector<std::vector<int>> GetMatrixCoefficients() const override;
    ~EdgeDetectionFilter(){};

private:
    const std::vector<std::vector<int>> MATRIX_FOR_EDGE_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    const double MAX_SHADE_ = 255.0;
    double threshold_;
};
