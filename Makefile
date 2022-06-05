all:
	g++ main.cpp Cube.cpp Search.cpp -o cube-solver

clean:
	rm -f cube-solver
