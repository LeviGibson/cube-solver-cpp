//
// Created by levigibson on 6/6/22.
//

#ifndef CUBE_SOLVER_CPP_ALGORITHM_H
#define CUBE_SOLVER_CPP_ALGORITHM_H

#include <stdint.h>

namespace Algs {

    class Algorithm {
    private:
        int32_t moves[128];
    public:
        int32_t length = 0;
        Algorithm();
        void append(int32_t move);
        void pop();
        void print();
    };

} // Algs

#endif //CUBE_SOLVER_CPP_ALGORITHM_H
