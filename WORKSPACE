load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "w32api",
    build_file = "@//third_party:w32api.BUILD",
    sha256 = "37f6c38afcae8bf228991a6ca477215a51af25b7cfe9f705e8fcc1fd5525da72",
    urls = [
        "https://netactuate.dl.sourceforge.net/project/mingw/MinGW/Base/w32api/w32api-5.0.2/w32api-5.0.2-mingw32-dev.tar.xz",
    ],
)

http_archive(
    name = "emsdk",
    sha256 = "7a58a9996b113d3e0675df30b5f17e28aa47de2e684a844f05394fe2f6f12e8e",
    strip_prefix = "emsdk-c1589b55641787d55d53e883852035beea9aec3f/bazel",
    url = "https://github.com/emscripten-core/emsdk/archive/c1589b55641787d55d53e883852035beea9aec3f.tar.gz",
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")

emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")

emsdk_emscripten_deps()
