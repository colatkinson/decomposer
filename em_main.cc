#include <algorithm>
#include <iostream>
#include <sstream>

#include "decomposer.hh"

#include <emscripten.h>

extern "C" {
EMSCRIPTEN_KEEPALIVE char *em_decompose_flags(const char *num_str) noexcept
{
    if (num_str == nullptr) {
        return nullptr;
    }

    std::cout << "INPUT: " << num_str << std::endl;

    std::stringstream sstr;
    bool res = decomposer::decompose_flags(sstr, num_str);
    if (!res) {
        return nullptr;
    }

    std::string out = sstr.str();
    auto size = out.size() + 1;

    std::cout << out << std::endl;

    auto *out_buf = static_cast<char *>(calloc(sizeof(char), size));
    std::copy(out.begin(), out.end(), out_buf);
    std::cout << out_buf << std::endl;

    return out_buf;
}
}
