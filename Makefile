all:
	g++ main.cpp Cube.cpp -o cube-solver

clean:
	rm -f cube-solver
