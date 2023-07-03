@echo off

REM Create build folder if it doesn't exist
if not exist build mkdir build

REM Change to build folder
cd build

REM Run CMake in the root directory and write output to build folder
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release > build_output.txt

REM Build using Mingw
mingw32-make -j4

REM Change back to the root directory
cd ..

echo Build process completed.
