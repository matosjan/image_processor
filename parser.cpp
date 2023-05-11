#include "parser.h"

Parser::Parser(int argc, char* argv[]) {
    if (argc < MIN_ARG_NUMBER_) {
        throw CustomExceptions("Need at least 3 arguments");
    }
    input_file_path_ = argv[INPUT_FILE_POS_];
    output_file_path_ = argv[OUTPUT_FILE_POS_];

    FilterDescription filter;
    for (int i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            if (!filter.filter_name.empty()) {
                filter_descriptor_.push_back(filter);
            }
            filter.params.clear();
            filter.filter_name = argv[i];
        } else {
            filter.params.push_back(argv[i]);
        }
    }
    if (!filter.filter_name.empty()) {
        filter_descriptor_.push_back(filter);
    }
}

std::string Parser::InputFile() const {
    return input_file_path_;
}

std::string Parser::OutputFile() const {
    return output_file_path_;
}
std::vector<FilterDescription>& Parser::FilterDescriptorGetter() {
    return filter_descriptor_;
}
std::vector<FilterDescription> Parser::FilterDescriptorGetter() const {
    return filter_descriptor_;
}
