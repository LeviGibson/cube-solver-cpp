//
//Created by 0x0015 on 06-05-2022 :)
//

#include "Search.h"

int32_t ply;

void CubeUtil::Search::solve_recur(Cube& cube, bool extended, unsigned int depth){
    if(cube.is_solved()){
        printf("Cube solved!  moves:\n");
        for(int i=0;i<ply;i++){
            cube.print_move(moves[i]);
            printf("\n");
        }
        return;
    }

    if(cube.has_simple_solution()){
        if (!extended){
            printf("Found simple soltuion!\n");
            //cube.print_cube();
            depth+=8;
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
			//tmpCube.copy_cube(&cube);
			cube.copy_cube(&tmpCube);
			tmpCube.make_move(move);
			moves[ply] = move;
            ply++;
			solve_recur(tmpCube, extended, depth-1);
            ply--;
		}
	}
}

void CubeUtil::Search::solve(Cube& cube, unsigned int depth){
    ply = 0;
	moves.resize(depth+1+8, -1);
	for (unsigned int i = 0; i <= depth; i++){
		printf("searching depth %d\n", i);
		solve_recur(cube, false, i);
	}
}
