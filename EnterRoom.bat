@echo off

set "DAY=%~1"
set "SOURCE_PATH=.\Dungeon\Room %DAY%\Room%DAY%.cpp"
set "OUTPUT_PATH=.\Dungeon\Room %DAY%\output\Room%DAY%.exe"

cls

g++.exe -Wall -Wextra -g3 "%SOURCE_PATH%" -o "%OUTPUT_PATH%"
if errorlevel 1 (
    echo Compilation failed!
    exit /b 1
)

"%OUTPUT_PATH%"