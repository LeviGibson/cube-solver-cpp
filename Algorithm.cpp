//
// Created by levigibson on 6/6/22.
//

#include <cstring>
#include <cstdio>
#include "Algorithm.h"
#include "Cube.h"

#define HOME 1
#define DOWN 0
#define UP 2

int32_t fingerTrickTable[21][3] = {
        //R
        {1, 1, 0},
        //L
        {1, 1, 1},
        //U
        {1, 1, 1},
        //D
        {1, 1, 1},
        //F
        {1, 1, 0},
        //B
        {0, 0, 1},
        //R'
        {0, 1, 1},
        //L'
        {1, 1, 1},
        //U'
        {1, 1, 1},
        //D'
        {1, 1, 1},
        //F'
        {1, 1, 1},
        //B'
        {0, 0, 1},
        //R2
        {1, 0, 1},
        //L2
        {1, 1, 1},
        //U2
        {1, 1, 1},
        //D2
        {1, 1, 1},
        //F2
        {1, 0, 0},
        //B2
        {0, 0, 1},
        //M, MP, M2
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
};

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

    float Algorithm::score() {
        float algScore = 0;
        algScore += (float )length;
        algScore += wrist_score();

        return algScore;
    }

    float Algorithm::wrist_score() {
        int32_t Rpos = HOME;

        for (int mid = 0; mid < length; mid++){
            int32_t move = moves[mid];

            if (!fingerTrickTable[move][Rpos])
                return 6;

            if (move == CubeUtil::R)
                Rpos++;
            else if (move == CubeUtil::RP)
                Rpos--;
            else if (move == CubeUtil::R2){
                Rpos = -Rpos;
            }
        }

        return 0;
    }
} // Algs