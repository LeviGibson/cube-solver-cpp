all:
	g++ -std=c++17 -g main.cpp Cube.cpp Search.cpp simplecubes.cpp -o cube-solver

clean:
	rm -f cube-solver
