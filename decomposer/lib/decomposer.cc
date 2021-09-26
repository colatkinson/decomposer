#include <array>
#include <bitset>
#include <climits>
#include <iomanip>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

#define _X86_
#include <winnt.h>

namespace {

#define E(flag) std::tuple<DWORD, const char *>(flag, #flag)

constexpr std::array<std::tuple<DWORD, const char *>, 34> file_perms_map = {
    E(FILE_GENERIC_EXECUTE),
    E(FILE_GENERIC_READ),
    E(FILE_GENERIC_WRITE),
    E(FILE_ADD_FILE),
    E(FILE_ADD_SUBDIRECTORY),
    E(FILE_ALL_ACCESS),
    E(FILE_APPEND_DATA),
    E(FILE_CREATE_PIPE_INSTANCE),
    E(FILE_DELETE_CHILD),
    E(FILE_EXECUTE),
    E(FILE_LIST_DIRECTORY),
    E(FILE_READ_ATTRIBUTES),
    E(FILE_READ_DATA),
    E(FILE_READ_EA),
    E(FILE_TRAVERSE),
    E(FILE_WRITE_ATTRIBUTES),
    E(FILE_WRITE_DATA),
    E(FILE_WRITE_EA),
    E(STANDARD_RIGHTS_READ),
    E(STANDARD_RIGHTS_WRITE),
    E(STANDARD_RIGHTS_EXECUTE),
    E(STANDARD_RIGHTS_ALL),
    E(STANDARD_RIGHTS_REQUIRED),
    E(SPECIFIC_RIGHTS_ALL),
    E(ACCESS_SYSTEM_SECURITY),
    E(GENERIC_ALL),
    E(GENERIC_READ),
    E(GENERIC_WRITE),
    E(GENERIC_EXECUTE),
    E(DELETE),
    E(READ_CONTROL),
    E(WRITE_DAC),
    E(WRITE_OWNER),
    E(SYNCHRONIZE),
};

#undef E

constexpr const char *dupe_entry(const auto &flag_map) noexcept
{
    for (const auto &[_key, val] : flag_map) {
        std::string_view val_view(val);

        size_t count = 0;
        for (const auto &[_key_inner, val_inner] : flag_map) {
            if (val_view == val_inner) {
                ++count;
            }

            if (count > 1) {
                return val_inner;
            }
        }
    }

    return nullptr;
}

static_assert(dupe_entry(file_perms_map) == nullptr,
    "Duplicate entry found in file_perms_map");

template <size_t N>
bool matches(const std::bitset<N> &flag, const std::bitset<N> &input) noexcept
{
    if ((flag & input).none()) {
        return false;
    }

    for (size_t i = 0; i < flag.size(); ++i) {
        if (flag[i] && !input[i]) {
            return false;
        }
    }

    return true;
}

std::ostream &print_dword(std::ostream &out, DWORD val) noexcept
{
    constexpr int dword_hex_chars = sizeof(DWORD) * 2;
    out << std::hex << std::setw(dword_hex_chars) << std::setfill('0') << val;
    return out;
}

using match_map
    = std::map<DWORD, std::vector<const char *>, std::greater<DWORD>>;
match_map get_matching_flags(const DWORD &num_dw) noexcept
{
    using dword_bitset = std::bitset<sizeof(DWORD) * CHAR_BIT>;
    const dword_bitset num_bs(num_dw);

    match_map matched_flags;

    for (const auto &[flag, flag_str] : file_perms_map) {
        const dword_bitset flag_bs(flag);

        if (matches(flag_bs, num_bs)) {
            auto &map_entry = matched_flags[flag];
            map_entry.emplace_back(flag_str);
        }
    }

    return matched_flags;
}

void print_matching_flags(
    std::ostream &out, DWORD num_dw, const match_map &matched_flags) noexcept
{
    for (const auto &[val, names] : matched_flags) {
        print_dword(out, val) << ": ";

        for (const auto &name : names) {
            out << name << ' ';
        }

        out << std::endl;

        num_dw &= ~val;
    }

    print_dword(out, num_dw) << " unaccounted for\n";
}

}  // namespace

namespace decomposer {
bool decompose_flags(std::ostream &out, const std::string &num_str) noexcept
{
    const unsigned long long num_int
        = std::strtoull(num_str.c_str(), nullptr, 0);

    if (num_int > MAXDWORD) {
        out << num_str << " larger than MAXDWORD (0x" << std::hex << MAXDWORD
            << ')' << std::endl;
        return false;
    }
    const auto num_dw = static_cast<DWORD>(num_int);
    print_dword(out, num_dw) << '\n';

    const auto matched_flags = get_matching_flags(num_dw);
    print_matching_flags(out, num_dw, matched_flags);

    return true;
}
}  // namespace decomposer
