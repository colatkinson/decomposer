load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")
load("@rules_pkg//:pkg.bzl", "pkg_tar")
load("@rules_pkg//:mappings.bzl", "pkg_files")
load("//rules:common.bzl", "common_copts")

cc_binary(
    name = "em_main",
    srcs = ["em_main.cc"],
    copts = common_copts,
    features = ["optimized_for_size"],
    linkopts = select({
        "//rules:wasm_cpu": [
            """-s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]'""",
            """-s EXPORTED_FUNCTIONS='["_malloc", "_free"]'""",
            "-s FILESYSTEM=0",
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

static_files = [
    ":dom.js",
    ":index.html",
    ":style.css",
]

py_binary(
    name = "devserver",
    srcs = [
        "devserver.py",
    ],
    data = [
        ":decomposer-wasm",
    ] + static_files,
    python_version = "PY3",
    deps = ["@rules_python//python/runfiles"],
)

# Package into a single tar for deployment
pkg_files(
    name = "wasm_files",
    srcs = [":decomposer-wasm"],
    prefix = "decomposer-wasm",
)

pkg_tar(
    name = "site",
    srcs = [
        ":wasm_files",
    ] + static_files,
)
