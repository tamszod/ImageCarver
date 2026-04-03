#!/bin/bash

echo "Building ImageCarver (macOS)..."

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

echo "Done."