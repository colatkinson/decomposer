load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

config_setting(
    name = "wasm_cpu",
    values = {"cpu": "wasm"},
)

cc_library(
    name = "decomposer",
    srcs = [
        "decomposer.cc",
    ],
    hdrs = [
        "decomposer.hh",
    ],
    copts = [
        "-Iexternal/w32api/include",
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    deps = ["@w32api//:w32api_hdrs"],
)

cc_binary(
    name = "main",
    srcs = ["main.cc"],
    copts = [
        "-Iexternal/w32api/include",
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    linkopts = select({
        ":wasm_cpu": [
            "--oformat=html",
            "-s MINIFY_HTML=0",
        ],
        "//conditions:default": [],
    }),
    deps = [":decomposer"],
)

cc_binary(
    name = "em_main",
    srcs = ["em_main.cc"],
    copts = [
        "-Iexternal/w32api/include",
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    linkopts = select({
        ":wasm_cpu": [
            "--oformat=html",
            "-s MINIFY_HTML=0",
            """-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'""",
            """-s EXPORTED_FUNCTIONS='["_malloc", "_free", "stringToUTF8", "lengthBytesUTF8"]'""",
        ],
        "//conditions:default": [],
    }),
    tags = ["manual"],
    deps = [":decomposer"],
)

wasm_cc_binary(
    name = "decomposer-wasm.html",
    cc_target = ":em_main",
)
