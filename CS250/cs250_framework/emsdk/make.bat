@echo off

set SOURCES=../main.cpp
set INCLUDE_PATHS=-I..
set WARNINGS=-Werror -Wall -Wextra -Wpedantic
set PROJECT_NAME=Demo
set FLAGS=-std=c++14 -s USE_SDL=2 -s USE_WEBGL2=1 -s WASM=1 -o %PROJECT_NAME%.$(@).html --shell-file shell.$(@).html

if "%1" == "" (
    call:Release
    goto:eof
)

if "%1" == "release" (
    call:Release
    goto:eof
)

if "%1" == "debug" (
    call:debug
    goto:eof
)

if "%1" == "clean" (
    call:clean
    goto:eof
)

echo Unkown command given : "%1"
echo expected release, debug, or clean
goto:eof

:release
    call set FLAGS=%%FLAGS:$(@)=release%%
    @echo on
    call em++ %SOURCES% %INCLUDE_PATHS% %FLAGS% %WARNINGS% -Oz -o %PROJECT_NAME%.html
    @echo off
goto:eof

:debug
    call set FLAGS=%%FLAGS:$(@)=debug%%
    @echo on
    call em++ %SOURCES% %INCLUDE_PATHS% %FLAGS% %WARNINGS% -g
    @echo off
goto:eof

:clean
    @echo on
    call del /Q %PROJECT_NAME%*.html *.js *.wasm *.map *.wast
    @echo off
goto:eof