#pragma once

#include <string>
#include <string_view>
#include <vector>
#include "util.h"

struct FilterDescription {
    std::string filter_name;
    std::vector<std::string> params;
};

class Parser {
public:
    Parser(int argc, char* argv[]);
    std::string InputFile() const;
    std::string OutputFile() const;
    std::vector<FilterDescription>& FilterDescriptorGetter();
    std::vector<FilterDescription> FilterDescriptorGetter() const;

private:
    const int MIN_ARG_NUMBER_ = 3;
    const int INPUT_FILE_POS_ = 1;
    const int OUTPUT_FILE_POS_ = 2;

    std::string input_file_path_;
    std::string output_file_path_;
    std::vector<FilterDescription> filter_descriptor_;
};
