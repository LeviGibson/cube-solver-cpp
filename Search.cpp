#include "Search.h"


void CubeUtil::Search::solve_recur(Cube& cube, bool extended, unsigned int maxdepth, unsigned int depth){
	if(depth == 0){
		//stop
		return;
	}
	if(cube.is_cube_solved()){
		printf("Cube solved!  moves:\n");
		for(auto& o : moves){
			printf("\t%i\n", o);
		}
		return;
	}
	if(cube.cube_has_simple_solution()){
		if (!extended){
			printf("Found simple soltuion!\n");
			//cube.print_cube();
			depth+=8;
			maxdepth+=8;
			extended = 1;
		}
	} else if (extended){
		return;
	}

	for(int move=0;move<21;move++){
		if(!cube.full_is_repetition(move)){
			Cube tmpCube;
			//tmpCube.copy_cube(&cube);
			cube.copy_cube(&tmpCube);
			tmpCube.make_move(move);
			moves[maxdepth - depth] = move;
			solve_recur(tmpCube, extended, depth, depth-1);
		}
	}
}

void CubeUtil::Search::solve(Cube& cube, unsigned int depth){
	moves.resize(depth+1+8, -1);
	for (int i = 0; i <= depth; i++){
		printf("searching depth %d\n", i);
		solve_recur(cube, false, i, i);
	}
}
