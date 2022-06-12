//
// Created by levigibson on 6/6/22.
//

#include <cstring>
#include <cstdio>
#include <iostream>
#include "Algorithm.h"
#include "Cube.h"

#define DOWN 0
#define HOME 1
#define GR_UP 2

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

int32_t overworkingTable[21][3] = {
        //R
        {-1, -1, -1},
        //L
        {-1, -1, -1},
        //U
        {-1, -1, -1},
        //D
        {CubeUtil::D, -1, -1},
        //F
        {CubeUtil::F, CubeUtil::F2, -1},
        //B
        {CubeUtil::B, CubeUtil::B2, 1},
        //R'
        {-1, -1, -1},
        //L'
        {-1, -1, -1},
        //U'
        {CubeUtil::UP, -1, -1},
        //D'
        {CubeUtil::DP, -1, -1},
        //F'
        {CubeUtil::FP, -1, -1},
        //B'
        {CubeUtil::BP, -1, -1},
        //R2
        {-1, -1, -1},
        //L2
        {-1, -1, -1},
        //U2
        {-1, -1, -1},
        //D2
        {CubeUtil::D2, CubeUtil::D, CubeUtil::DP},
        //F2
        {CubeUtil::F, CubeUtil::F2, 0},
        //B2
        {CubeUtil::B, CubeUtil::BP, CubeUtil::B2},
        //M, MP, M2
        {CubeUtil::M, -1, -1},
        {CubeUtil::MP, 1, 1},
        {CubeUtil::M2, CubeUtil::MP, 1}
};

//https://stackoverflow.com/questions/52644140/reverse-array-c
void arrayReverse(int* array, int size) {
    for (int i = 0; i <= (size / 2); i++) {
        int swap = array[size - 1 - i];
        array[size - 1 - i] = array[i];
        array[i] = swap;
    }
}

namespace Algs {

    Algorithm::Algorithm() {
        clear();
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
        printf(" (%f)\n", score(false));
    }

    float Algorithm::score(bool inverse) {
        if (inverse)
            invert();

        float algScore = 0;
        algScore += (float )length;
        algScore += wrist_score();
        algScore += rl_regrip_score();
        algScore += overworking();

        if (inverse)
            invert();

        return algScore;
    }

    float Algorithm::wrist_score() {
        int32_t Rpos = HOME;
        int32_t Lpos = HOME;

        for (int mid = 0; mid < length; mid++){
            int32_t move = moves[mid];

            if (!fingerTrickTable[move][Rpos])
                return 6;

            if (abs(Lpos) > 1)
                return 6;

            if (move == CubeUtil::R)
                Rpos++;
            else if (move == CubeUtil::RP)
                Rpos--;
            else if (move == CubeUtil::R2){
                int32_t R2table[] = {2, 3, 0};
                Rpos = R2table[Rpos];
            }

            if (move == CubeUtil::L)
                Lpos++;
            else if (move == CubeUtil::LP)
                Lpos--;
            else if (move == CubeUtil::L2){
                int32_t L2table[] = {2, 3, 0};
                Lpos = L2table[Lpos];
            }
        }

        return 0;
    }

    float Algorithm::rl_regrip_score() {
        int32_t position = 1;
        int32_t regrips = 0;

        for (int mid = 0; mid < length; mid++) {
            int32_t move = moves[mid];

            if (position == 1 && (move == CubeUtil::L || move == CubeUtil::LP || move == CubeUtil::L2)) {
                position = 0;
                regrips++;
            } else if (position == 0 && (move == CubeUtil::R || move == CubeUtil::RP || move == CubeUtil::R2)) {
                position = 1;
                regrips++;
            }

        }
        return (float )regrips;
    }

    float Algorithm::overworking() {
        int32_t overworks = 0;

        if (length <= 2)
            return 0;

        for (int mid = 2; mid < length; mid++) {
            int32_t move = moves[mid];
            int32_t owmove = moves[mid-2];

            if (overworkingTable[move][0] == owmove || overworkingTable[move][1] == owmove || overworkingTable[move][2] == owmove)
                overworks++;
        }
        return (float )overworks;
    }

    void Algorithm::invert() {
        arrayReverse(moves, length);
        for (int i = 0; i < length; ++i) {
            moves[i] = CubeUtil::inverseMoves[moves[i]];
        }
    }

    void Algorithm::clear(){
        memset(moves, 0, sizeof(moves));
        length = 0;
    }

    void Algorithm::parse(const char *alg) {
        while (*alg) {
            if (*alg == 'R') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::RP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::R2);
                else
                    append(CubeUtil::R);

            } else if (*alg == 'U') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::UP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::U2);
                else
                    append(CubeUtil::U);

            } else if (*alg == 'F') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::FP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::F2);
                else
                    append(CubeUtil::F);

            } else if (*alg == 'L') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::LP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::L2);
                else
                    append(CubeUtil::L);

            } else if (*alg == 'D') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::DP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::D2);
                else
                    append(CubeUtil::D);

            } else if (*alg == 'B') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::BP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::B2);
                else
                    append(CubeUtil::B);

            }

            alg++;
        }
    }
} // Algs