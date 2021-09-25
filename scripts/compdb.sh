#!/bin/bash
set -euo pipefail

tmp=""
tmp="$(dirname "$(mktemp -u)")"

readonly repo="bazel-compilation-database"
readonly commit="f3f86bc1e6e214207cb64d2c46ce6dcf5e7b21e3"
readonly fname="$commit.tar.gz"
readonly url="https://github.com/grailbio/$repo/archive/$fname"

readonly tar_path="$tmp/$fname"

if [ ! -f "$tar_path" ]; then
    echo "Downloading $url"
    wget --output-document="$tar_path" "$url"
fi

readonly dir_path="$tmp/$repo-$commit"

if [ ! -d "$dir_path" ]; then
    pushd "$tmp"
    echo "Extracting $tar_path to $dir_path"
    tar xf "$tar_path"
    popd
fi

python3 "$dir_path/generate.py" "$@"
