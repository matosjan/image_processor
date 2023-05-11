#pragma once

#include <memory>
#include "filters.h"
#include "parser.h"
#include "util.h"

class FilterFactory {
public:
    std::unique_ptr<BaseFilter> CreateFilter(const FilterDescription& filter);
};
