@echo off

echo Building ImageCarver (Windows)...

cmake -S . -B build -G "Visual Studio 17 2022"
cmake --build build --config Release

echo Done.
pause