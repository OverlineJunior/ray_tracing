MAIN := src/main.cpp

all: out/main run

out/main: $(MAIN) | out
	@clang++ -Wall -o out/main $(MAIN)

run: out/main | out
	@out/main > out/image.ppm

out:
	@mkdir -p out
