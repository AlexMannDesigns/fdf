#!/bin/sh

sed -i '' "s/SRC_FILES = .*/SRC_FILES = $(ls src | xargs)/" Makefile

