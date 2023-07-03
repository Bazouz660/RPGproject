#!/bin/bash

if [[ $(uname) == "Linux" ]]; then
    ./buildLinux.sh
elif [[ $(uname) == "Darwin" ]]; then
    echo "Unsupported operating system: macOS"
else
    ./buildWin.bat
fi
