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

}  // namespace

namespace decomposer {
bool decompose_flags(std::ostream &out, const std::string &num_str) noexcept
{
    const unsigned long long num_int
        = std::strtoull(num_str.c_str(), nullptr, 0);

    if (num_int > MAXDWORD) {
        std::cerr << "Too big" << std::endl;
        return false;
    }
    const auto num_dw = static_cast<DWORD>(num_int);
    out << std::hex << std::setw(sizeof(DWORD) * 2) << std::setfill('0')
        << num_dw << std::endl;

    const std::bitset<sizeof(num_dw) * CHAR_BIT> num_bs(num_dw);

    std::map<DWORD, std::vector<const char *>, std::greater<DWORD>>
        matched_flags;

    for (const auto &[k, v] : file_perms_map) {
        const std::bitset<sizeof(k) * CHAR_BIT> k_bs(k);

        if (matches(k_bs, num_bs)) {
            auto map_entry = matched_flags.find(k);
            if (map_entry == matched_flags.end()) {
                matched_flags.emplace(k, std::vector<const char *>());
                map_entry = matched_flags.find(k);
            }

            map_entry->second.emplace_back(v);
        }
    }

    auto rem = num_dw;
    for (const auto &[val, names] : matched_flags) {
        out << std::hex << std::setw(sizeof(DWORD) * 2) << std::setfill('0')
            << val << ": ";

        for (const auto &name : names) {
            out << name << ' ';
        }

        out << std::endl;

        rem &= ~val;
    }

    out << std::hex << std::setw(sizeof(DWORD) * 2) << std::setfill('0') << rem
        << " rem" << std::endl;

    return true;
}
}  // namespace decomposer
