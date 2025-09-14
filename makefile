all: out/main.exe run

out/main.exe: main.cpp | out
	@clang++ -Wall -o out/main.exe main.cpp

run: out/main.exe | out
	@out\main.exe > out\image.ppm

out:
	@mkdir out
