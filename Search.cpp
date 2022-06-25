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
//            printf("Possible : ");
//            algorithm.print();
            maxDepth+=1.8;
            extended = true;
        }
    } else if (extended){
        return;
    }

	if(maxDepth < algorithm.score(false)){
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
	for (float i = 0; i <= (float )depth; i+=0.1){
		printf("searching depth %f\n", i);
		solve_recur(cube, false, i);
	}
}
