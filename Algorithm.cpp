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

float movescores[21] = {
        0.20146460715325873,
        0.005506331753192928,
        0.17239001623994535,
        0.1948749986342372,
        0.3079285510499981,
        0.7440934459893918,
        0.17516069681819588,
        0.012744491569962624,
        0.16695460255450867,
        0.2068950715760491,
        0.30579826684108563,
        0.4061302265220062,
        0.25968604250765726,
        0.21176140376898114,
        0.292967864116052,
        0.3634353582230373,
        0.49478778195913947,
        0.4985501000101583,
        0.4654453458054431,
        0.33905149295282966,
        0.4424952203013478,
};

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
        {1, 0, 0},
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
        {CubeUtil::FP, CubeUtil::F, CubeUtil::F2},
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
        {CubeUtil::FP, CubeUtil::F, CubeUtil::F2},
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
        {CubeUtil::FP, CubeUtil::F, CubeUtil::F2},
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
        memset(features, 0, sizeof(features));

        if (inverse)
            invert();

        float algScore = 0;

        if (!inverse && length) {
            if (moves[0] == CubeUtil::U || moves[0] == CubeUtil::UP || moves[0] == CubeUtil::U2)
                algScore -= movescores[moves[0]];

            if (moves[length - 1] == CubeUtil::U || moves[length - 1] == CubeUtil::UP || moves[length - 1] == CubeUtil::U2)
                algScore -= movescores[moves[0]];
        }

        algScore += wrist_score() * 0;
        algScore += rl_regrip_score() * 0.23001222709213578f;
        algScore += basic_movescore();
        algScore += overworking() * 0;

        if (inverse)
            invert();

        return algScore;
    }

    float Algorithm::basic_movescore(){

        float funScore = 0;

        for (int i = 0; i < length; ++i) {
            features[moves[i]]++;
            funScore += movescores[moves[i]];
        }

        return funScore;
    }

    void adjust_wrist_position(int32_t *rpos, int32_t *lpos, int32_t move){
        if (move == CubeUtil::R)
            (*rpos)++;
        else if (move == CubeUtil::RP)
            (*rpos)--;
        else if (move == CubeUtil::R2){
            int32_t R2table[] = {2, 3, 0};
            *rpos = R2table[*rpos];
        }

        if (move == CubeUtil::L)
            (*lpos)++;
        else if (move == CubeUtil::LP)
            (*lpos)--;
        else if (move == CubeUtil::L2){
            int32_t L2table[] = {2, 3, 0};
            *lpos = L2table[*lpos];
        }
    }

    float Algorithm::wrist_score_recur(int32_t rpos, int32_t lpos, int32_t startIndex) {
        float regrips = 0;

        for (int mid = startIndex; mid < length; mid++){
            int32_t move = moves[mid];

            if (!fingerTrickTable[move][rpos]) {
                regrips++;
                float minEval = 99999;
                for (int i = 0; i < 3; ++i) {
                    if (fingerTrickTable[move][i]){
                        float eval = wrist_score_recur(i, lpos, mid);
                        if (eval < minEval){
                            minEval = eval;
                        }
                    }
                }

                regrips += minEval;
                break;
            }

            if (abs(lpos) > 1) {
                regrips++;
                lpos = HOME;
            }

            adjust_wrist_position(&rpos, &lpos, move);
        }

        return (float )regrips;
    }

    float Algorithm::wrist_score() {
        float score = std::min(std::min(wrist_score_recur(HOME, HOME, 0),
                                 wrist_score_recur(DOWN, HOME, 0)),
                        wrist_score_recur(GR_UP, HOME, 0)) * 3;
        features[FEATURE_REGRIPS] = score;
        return score;
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

        features[FEATURE_RL_REGRIPS] = (float)regrips;
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

        features[FEATURE_OVERWORKING] = (float)overworks;
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
        memset(features, 0, sizeof(features));
        length = 0;
    }

    void Algorithm::parse(const char *alg) {
        clear();

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

            } else if (*alg == 'M') {

                if (*(alg + 1) == '\'')
                    append(CubeUtil::MP);
                else if (*(alg + 1) == '2')
                    append(CubeUtil::M2);
                else
                    append(CubeUtil::M);

            }

            alg++;
        }
    }

    std::string Algorithm::toString() {
        std::string s = "";

        for (int i = 0; i < length; ++i) {
            s += move_chars[moves[i]];
            if (move_chars[moves[i]][1] != ' ')
                s += ' ';
        }

        return s;
    }
} // Algs