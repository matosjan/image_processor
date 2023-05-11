#include <iostream>

#include "runner.h"

int main(int argc, char* argv[]) {
    try {
        Runner runner;
        runner.Run(argc, argv);
        return 0;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}
