workspace(name = "decomposer")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

# Mingw Windows headers, so we can compile on Linux
http_archive(
    name = "w32api",
    build_file = "@//third_party:w32api.BUILD",
    sha256 = "37f6c38afcae8bf228991a6ca477215a51af25b7cfe9f705e8fcc1fd5525da72",
    urls = [
        "https://netactuate.dl.sourceforge.net/project/mingw/MinGW/Base/w32api/w32api-5.0.2/w32api-5.0.2-mingw32-dev.tar.xz",
    ],
)

# For packing up the output tarball
http_archive(
    name = "rules_pkg",
    urls = [
        "https://mirror.bazel.build/github.com/bazelbuild/rules_pkg/releases/download/0.5.1/rules_pkg-0.5.1.tar.gz",
        "https://github.com/bazelbuild/rules_pkg/releases/download/0.5.1/rules_pkg-0.5.1.tar.gz",
    ],
    sha256 = "a89e203d3cf264e564fcb96b6e06dd70bc0557356eb48400ce4b5d97c2c3720d",
)
load("@rules_pkg//:deps.bzl", "rules_pkg_dependencies")
rules_pkg_dependencies()

# For running the devserver
http_archive(
    name = "rules_python",
    sha256 = "954aa89b491be4a083304a2cb838019c8b8c3720a7abb9c4cb81ac7a24230cea",
    url = "https://github.com/bazelbuild/rules_python/releases/download/0.4.0/rules_python-0.4.0.tar.gz",
)

# For building as wasm
emsdk_commit = "deb6453391c3e0da66eee71a14bff64ce73ff713"
http_archive(
    name = "emsdk",
    sha256 = "fc3cbdcc72c5a4ea3349ca92cc53480b194be404e03847d51768b72b73714017",
    strip_prefix = "emsdk-%s/bazel" % emsdk_commit,
    url = "https://github.com/emscripten-core/emsdk/archive/%s.tar.gz" % emsdk_commit,
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")
emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")
emsdk_emscripten_deps()
