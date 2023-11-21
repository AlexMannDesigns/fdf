#!/bin/sh

files=$(find src -type f -name '*.c' -exec basename {} \; | xargs)

sed -i '' "s/SRC_FILES = .*/SRC_FILES = $files/" Makefile

