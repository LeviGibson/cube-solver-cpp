//
//Created by 0x0015 on 06-05-2022 :)
//

#include "Search.h"

Algs::Algorithm algorithm;

void CubeUtil::Search::solve_recur(Cube& cube, bool extended, float maxDepth){
    if(cube.is_solved()){
        algorithm.print();
        return;
    }

    if(cube.has_simple_solution()){
        if (!extended){
            printf("Possible : ");
            algorithm.print();
            maxDepth+=12;
            extended = true;
        }
    } else if (extended){
        return;
    }

	if(maxDepth < algorithm.score()){
		//stop
		return;
	}

	for(int move=0;move<21;move++){
		if(!cube.is_full_repetition(move)){
			Cube tmpCube;
			tmpCube = cube;
			tmpCube.make_move(move);

			algorithm.append(move);
			solve_recur(tmpCube, extended, maxDepth);
            algorithm.pop();
		}
	}
}

void CubeUtil::Search::solve(Cube& cube, unsigned int depth){
	for (int32_t i = 0; i <= depth; i++){
		printf("searching depth %f\n", (float )i);
		solve_recur(cube, false, (float)i);
	}
}
