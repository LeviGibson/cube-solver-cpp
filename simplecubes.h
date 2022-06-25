//
// Created by levigibson on 6/5/22.
//

#ifndef CUBE_SOLVER_CPP_SIMPLECUBES_H
#define CUBE_SOLVER_CPP_SIMPLECUBES_H

#include "Cube.h"

#define simple_solution_hash_size 400000
#define simple_solution_hash_batch_size 500
#define simple_solution_depth 1.7

extern U64 corner_keys[8][64][64];
extern U64 edge_keys[12][32][32];

extern U64 simple_solution_hashes[simple_solution_hash_size][simple_solution_hash_batch_size];
extern uint16_t simple_solution_counts[simple_solution_hash_size];

void init_key_generator();
void init_easy_solutions();

#endif //CUBE_SOLVER_CPP_SIMPLECUBES_H
