all: out/main run

out/main: main.cpp | out
	@clang++ -Wall -o out/main main.cpp

run: out/main | out
	@out/main > out/image.ppm

out:
	@mkdir -p out
