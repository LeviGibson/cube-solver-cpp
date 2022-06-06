//
//Created by 0x0015 on 06-05-2022 :)
//

#include "Search.h"

int32_t ply;
Algs::Algorithm algorithm;

void CubeUtil::Search::solve_recur(Cube& cube, bool extended, unsigned int depth){
    if(cube.is_solved()){
        algorithm.print();
        return;
    }

    if(cube.has_simple_solution()){
        if (!extended){
            depth+=7;
            extended = true;
        }
    } else if (extended){
        return;
    }

	if(depth == 0){
		//stop
		return;
	}
	for(int move=0;move<21;move++){
		if(!cube.is_full_repetition(move)){
			Cube tmpCube;
			tmpCube = cube;
			tmpCube.make_move(move);

			algorithm.append(move);
            ply++;
			solve_recur(tmpCube, extended, depth-1);
            ply--;
            algorithm.pop();
		}
	}
}

void CubeUtil::Search::solve(Cube& cube, unsigned int depth){
    ply = 0;
	for (unsigned int i = 0; i <= depth; i++){
		printf("searching depth %d\n", i);
		solve_recur(cube, false, i);
	}
}
