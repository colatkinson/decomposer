load("//rules:common.bzl", "common_copts")

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
    ] + common_copts,
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
    deps = ["@w32api//:w32api_hdrs"],
)

cc_binary(
    name = "decompose",
    srcs = [
        "bin/main.cc",
    ],
    copts = common_copts,
    deps = [":decomposer"],
)
