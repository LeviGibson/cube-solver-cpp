//
// Created by levigibson on 6/6/22.
//

#ifndef CUBE_SOLVER_CPP_ALGORITHM_H
#define CUBE_SOLVER_CPP_ALGORITHM_H

#include <cstdint>
#include <string>

enum {FEATURE_R, FEATURE_L, FEATURE_U, FEATURE_D, FEATURE_F, FEATURE_B, FEATURE_RP, FEATURE_LP, FEATURE_UP, FEATURE_DP, FEATURE_FP, FEATURE_BP, FEATURE_R2, FEATURE_L2, FEATURE_U2, FEATURE_D2, FEATURE_F2, FEATURE_B2, FEATURE_M, FEATURE_MP, FEATURE_M2, FEATURE_REGRIPS, FEATURE_RL_REGRIPS, FEATURE_OVERWORKING};

namespace Algs {

    class Algorithm {
    private:
        int32_t moves[128];
        float wrist_score();
        float wrist_score_recur(int32_t rpos, int32_t lpos, int32_t startIndex);
        float rl_regrip_score();
        float overworking();
    public:
        float features[128];
        int32_t length = 0;
        Algorithm();
        void append(int32_t move);
        void pop();
        void print();
        std::string toString();
        float score(bool inverse);
        void invert();
        void parse(const char *alg);
        void clear();
        float basic_movescore();
    };

} // Algs

#endif //CUBE_SOLVER_CPP_ALGORITHM_H
