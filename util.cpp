#include "util.h"

bool ParamIsNum(const std::string& str) {
    try {
        std::stod(str);
        return true;
    } catch (std::exception& error) {
        return false;
    }
}
