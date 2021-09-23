load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

cc_binary(
    name = "em_main",
    srcs = ["em_main.cc"],
    copts = [
        "-std=c++20",
        "-Wall",
        "-Werror",
    ],
    linkopts = select({
        "//rules:wasm_cpu": [
            """-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'""",
            """-s EXPORTED_FUNCTIONS='["_malloc", "_free", "stringToUTF8", "lengthBytesUTF8"]'""",
        ],
        "//conditions:default": [],
    }),
    tags = ["manual"],
    deps = ["//decomposer"],
)

wasm_cc_binary(
    name = "decomposer-wasm",
    cc_target = ":em_main",
)

py_binary(
    name = "devserver",
    srcs = [
        "devserver.py",
    ],
    data = [
        ":base16-flat.css",
        ":decomposer-wasm",
        ":dom.js",
        ":index.html",
        ":style.css",
    ],
    python_version = "PY3",
    deps = ["@rules_python//python/runfiles"],
)
