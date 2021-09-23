#include <iostream>

#include "decomposer.hh"

int main(int argc, char **argv)
{
    if (argc != 2) {
        std::cerr << "Need exactly one arg" << std::endl;
        return 1;
    }

    auto res = decomposer::decompose_flags(std::cout, argv[1]);
    if (!res) {
        return 1;
    }

    return 0;
}
