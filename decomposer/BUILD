cc_library(
    name = "decomposer",
    srcs = [
        "lib/decomposer.cc",
    ],
    hdrs = [
        "include/decomposer.hh",
    ],
    copts = [
        "-Iexternal/w32api/include",
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = ["@w32api//:w32api_hdrs"],
)

cc_binary(
    name = "decompose",
    srcs = [
        "bin/main.cc",
    ],
    copts = [
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    deps = [":decomposer"],
)
