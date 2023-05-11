#include "bmp.h"
#include "filter_factory.h"
#include "runner.h"
#include "parser.h"

void Runner::Run(int argc, char **argv) {
    Parser parser(argc, argv);
    auto img = BMP::LoadBMP(parser.InputFile());
    FilterFactory factory;

    for (size_t i = 0; i < parser.FilterDescriptorGetter().size(); ++i) {
        factory.CreateFilter(parser.FilterDescriptorGetter()[i])->ApplyFilter(img);
    }

    BMP::SaveBMP(img, parser.OutputFile());
}
