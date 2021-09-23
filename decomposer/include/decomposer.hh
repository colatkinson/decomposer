#ifndef DECOMPOSER_HH
#define DECOMPOSER_HH

#include <ostream>
#include <string>

namespace decomposer {
bool decompose_flags(std::ostream &out, const std::string &num_str) noexcept;
};

#endif /* DECOMPOSER_HH */
