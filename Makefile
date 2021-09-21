all: build
.PHONY: all

build:
	bazel build //...
.PHONY: build

opt:
	bazel build //... --compilation_mode=opt
.PHONY: opt

test:
.PHONY: test

fmt:
	find ./ \( -iname '*.cc' -o -iname '*.hh' \) -exec clang-format -i {} \;
.PHONY: fmt

lint:
	find ./ \( -iname '*.cc' -o -iname '*.hh' \) -print0 | xargs -n 1 -0 clang-format --Werror --dry-run
.PHONY: lint
