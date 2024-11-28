build:
	@# check if dist folder exists
	@if [ ! -d "./dist" ]; then mkdir dist; fi

	@# compile main.cpp
	@g++ -o ./dist/main ./src/main.cpp

run: build
	@# run the compiled file
	@./dist/main