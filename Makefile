SRC_DIR = ./src
EXTERNAL_DIR = ./src/external
DIST_DIR = ./dist

LIBS = $(wildcard $(EXTERNAL_DIR)/*.lib)

build:
	@# check if dist folder exists
	@if [ ! -d "$(DIST_DIR)" ]; then mkdir $(DIST_DIR); fi

	@# compile main.cpp and link all external libraries
	@g++ -o $(DIST_DIR)/main $(SRC_DIR)/main.cpp $(LIBS)

run: build
	@# run the compiled file
	@./$(DIST_DIR)/main
