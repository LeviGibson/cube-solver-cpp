OBJS = main.cpp.o Cube.cpp.o Search.cpp.o simplecubes.cpp.o Algorithm.cpp.o featureGenerator.cpp.o

OUT	= cube-solver
CXX	= g++
BUILD_CXX_FLAGS	 = -Wall -std=c++17 -g
LINK_OPTS	 = 

all: $(OBJS)
	$(CXX) $(OBJS) -o $(OUT) $(LINK_OPTS)

%.cpp.o: %.cpp
	$(CXX) $< $(BUILD_CXX_FLAGS) $(LINK_OPTS) -c -o $@

prof:
	g++ *.cpp -pg -o cube-solver-prof

clean:
	rm -f $(OBJS) $(OUT)

rmbin:
	rm -f *.bin
