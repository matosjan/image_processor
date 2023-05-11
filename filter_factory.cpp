#include "filter_factory.h"

namespace FilterCreators {

std::unique_ptr<BaseFilter> CreateNegativeFilter() {
    std::unique_ptr<BaseFilter> result_filter(new NegativeFilter);
    return result_filter;
}

std::unique_ptr<BaseFilter> CreateGrayScaleFilter() {
    std::unique_ptr<BaseFilter> result_filter(new GrayscaleFilter);
    return result_filter;
}

std::unique_ptr<BaseFilter> CreateCropFilter(int width, int height) {
    std::unique_ptr<BaseFilter> result_filter(new CropFilter(width, height));
    return result_filter;
}

std::unique_ptr<BaseFilter> CreateSharpeningFilter() {
    std::unique_ptr<BaseFilter> result_filter(new SharpeningFilter());
    return result_filter;
}

std::unique_ptr<BaseFilter> CreateEdgeDetectionFilter(double threshold) {
    std::unique_ptr<BaseFilter> result_filter(new EdgeDetectionFilter(threshold));
    return result_filter;
}

}  // namespace FilterCreators

std::unique_ptr<BaseFilter> FilterFactory::CreateFilter(const FilterDescription& filter) {
    if (filter.filter_name == "-neg") {
        if (filter.params.empty()) {
            return FilterCreators::CreateNegativeFilter();
        } else {
            throw CustomExceptions("-negative filter does not accept any arguments");
        }
    } else if (filter.filter_name == "-gray") {
        if (filter.params.empty()) {
            return FilterCreators::CreateGrayScaleFilter();
        } else {
            throw CustomExceptions("-grayscale filter does accept any arguments");
        }
    } else if (filter.filter_name == "-crop") {
        if (filter.params.size() == 2 && ParamIsNum(filter.params[0]) && ParamIsNum(filter.params[1])) {
            return FilterCreators::CreateCropFilter(std::stoi(filter.params[0]), std::stoi(filter.params[1]));
        } else {
            throw CustomExceptions("Either wrong or none arguments were given to -crop filter");
        }
    } else if (filter.filter_name == "-sharp") {
        if (filter.params.empty()) {
            return FilterCreators::CreateSharpeningFilter();
        } else {
            throw CustomExceptions("-sharp filter does not accept any arguments");
        }
    } else if (filter.filter_name == "-edge") {
        if (filter.params.size() == 1 && ParamIsNum(filter.params.front())) {
            return FilterCreators::CreateEdgeDetectionFilter(std::stod(filter.params.front()));
        } else {
            throw CustomExceptions("Either wrong or none arguments were given to -edge filter");
        }
    } else {
        throw CustomExceptions("No such filter: " + filter.filter_name);
    }
}
