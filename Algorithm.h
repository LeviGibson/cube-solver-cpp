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
        float wrist_score();
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
    };

} // Algs

#endif //CUBE_SOLVER_CPP_ALGORITHM_H
