//
// Created by levigibson on 6/6/22.
//

#ifndef CUBE_SOLVER_CPP_ALGORITHM_H
#define CUBE_SOLVER_CPP_ALGORITHM_H

#include <cstdint>

namespace Algs {

    class Algorithm {
    private:
        int32_t moves[128];
        float wrist_score(int32_t rpos, int32_t lpos, int32_t startIndex);
        float rl_regrip_score();
        float overworking();
    public:
        int32_t length = 0;
        Algorithm();
        void append(int32_t move);
        void pop();
        void print();
        float score(bool inverse);
        void invert();
        void parse(const char *alg);
        void clear();
        float basic_movescore();
    };

} // Algs

#endif //CUBE_SOLVER_CPP_ALGORITHM_H
