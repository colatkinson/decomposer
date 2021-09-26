# Decomposer

Break win32 permission flags down to mulch

## Description

Windows permissions are... complicated. There's about ten different ways to do a
given thing. Did you want to open that file with `STANDARD_RIGHTS_READ`,
`GENERIC_READ`, or `FILE_GENERIC_READ`?

Not only this, but these flags can be combined in a variety of interesting ways.

Given one of these flag combos, `decomposer` will break it down into its
constituent parts. For example:

```
$ decompose 1507743
000000000017019f
0000000000120116: FILE_GENERIC_WRITE 
0000000000120089: FILE_GENERIC_READ 
0000000000100000: SYNCHRONIZE 
0000000000040000: WRITE_DAC 
0000000000020000: STANDARD_RIGHTS_READ STANDARD_RIGHTS_WRITE STANDARD_RIGHTS_EXECUTE READ_CONTROL 
0000000000010000: DELETE 
0000000000000100: FILE_WRITE_ATTRIBUTES 
0000000000000080: FILE_READ_ATTRIBUTES 
0000000000000010: FILE_WRITE_EA 
0000000000000008: FILE_READ_EA 
0000000000000004: FILE_ADD_SUBDIRECTORY FILE_APPEND_DATA FILE_CREATE_PIPE_INSTANCE 
0000000000000002: FILE_ADD_FILE FILE_WRITE_DATA 
0000000000000001: FILE_LIST_DIRECTORY FILE_READ_DATA 
0000000000000000 unaccounted for
```

It is available as both a native CLI, and as a WASM-powered web app.

## Getting Started

### Prerequisites

1. [Bazel](https://bazel.build/)
2. A C++ compiler with support for C++20
3. `make`

Everything else gets pulled down automatically by Bazel.

**NOTE**: As of now, only Linux has been tested. But macOS and Windows support
is in the pipeline.

### Building

With make: `make`

With Bazel: `bazel build //...`

### Running

Development web server: `bazel run //web:devserver`

CLI: `bazel run //decomposer:decompose -- 1507743`

Alternatively, you can run the binary directly: `./bazel-bin/decomposer/decompose 1507743`

## License

This project is licensed under the GPL version 2. See the [license](./LICENSE)
for more details.
