#ifndef DECOMPOSER_HH
#define DECOMPOSER_HH

#include <ostream>
#include <string>

namespace decomposer {
[[nodiscard]] bool decompose_flags(
    std::ostream &out, const std::string &num_str) noexcept;
};

#endif /* DECOMPOSER_HH */
