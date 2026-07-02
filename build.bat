@echo off
setlocal

g++ -std=c++17 -Wall -Wextra -pedantic ^
  src\main.cpp ^
  src\calculator.cpp ^
  src\date_calculator.cpp ^
  src\history.cpp ^
  -o syxjsq.exe

if errorlevel 1 (
  echo Build failed.
  exit /b 1
)

echo Build succeeded: syxjsq.exe
