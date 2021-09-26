#include <algorithm>
#include <sstream>

#include "decomposer.hh"

#include <emscripten.h>

extern "C" {
EMSCRIPTEN_KEEPALIVE char *em_decompose_flags(const char *num_str) noexcept
{
    if (num_str == nullptr) {
        return nullptr;
    }

    std::ostringstream sstr;
    [[maybe_unused]] bool res = decomposer::decompose_flags(sstr, num_str);

    std::string out = sstr.str();
    auto size = out.size() + 1;

    // Parens cause zero-initialization
    auto *out_buf = new (std::nothrow) char[size]();
    if (!out_buf) {
        return nullptr;
    }

    out.copy(out_buf, size);
    out_buf[size - 1] = '\0';

    return out_buf;
}

EMSCRIPTEN_KEEPALIVE void em_free(char *buf) noexcept { delete[] buf; }
}
