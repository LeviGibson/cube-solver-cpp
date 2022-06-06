//
// Created by levigibson on 6/6/22.
//

#include <cstring>
#include <cstdio>
#include "Algorithm.h"
#include "Cube.h"

namespace Algs {

    Algorithm::Algorithm() {
        memset(moves, 0, sizeof(moves));
    }

    void Algorithm::append(int32_t move) {
        moves[length] = move;
        length++;
    }

    void Algorithm::pop() {
        moves[length-1] = 0;
        length--;
    }

    void Algorithm::print() {
        for (int i = 0; i < length; ++i) {
            CubeUtil::print_move(moves[i]);
            printf(" ");
        }
        printf("\n");
    }
} // Algs