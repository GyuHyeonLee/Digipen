
SOURCES = ../main.cpp
INCLUDE_PATHS = -I..
WARNINGS = -Werror -Wall -Wextra -Wpedantic
PROJECT_NAME = Demo
FLAGS = -std=c++14 -s USE_SDL=2 -s USE_WEBGL2=1 -s WASM=1 -o $(PROJECT_NAME).$(@).html --shell-file shell.$(@).html

release:
	em++ $(SOURCES) $(INCLUDE_PATHS) $(FLAGS) $(WARNINGS) -Oz -o $(PROJECT_NAME).html
debug:
	em++ $(SOURCES) $(INCLUDE_PATHS) $(FLAGS) $(WARNINGS) -g
clean:
	rm $(PROJECT_NAME)*.html *.js *.wasm *.map *.wast