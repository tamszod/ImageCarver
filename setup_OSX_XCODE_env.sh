#!/bin/bash
set -e

echo "Building ImageCarver (macOS with Xcode)..."

# Generate Xcode project
cmake -S . -B build -G Xcode

# Build using Xcode (Release config)
cmake --build build --config Release

echo "Done."