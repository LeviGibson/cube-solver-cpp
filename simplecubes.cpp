//
// Created by levigibson on 6/5/22.
//

#include "simplecubes.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include "Cube.h"



u_int64_t get_random_U64(){
    u_int64_t rando = 0ULL;
    rando |= (u_int64_t)rand();
    rando |= ((u_int64_t)rand() << 32);
    return rando;
}

U64 corner_keys[8][64][64];
U64 edge_keys[12][32][32];
int four_move_hashes_found = 0;

U64 simple_solution_hashes[simple_solution_hash_size][simple_solution_hash_batch_size];
uint16_t simple_solution_counts[simple_solution_hash_size];

int cmpfunc(const void *a, const void *b) {
    if (*(U64 *) a > *(U64 *) b) return 1;
    if (*(U64 *) a < *(U64 *) b) return -1;
    return 0;
}



void find_hashable_solutions(int depth, CubeUtil::Cube *cube) {
    U64 key = cube->get_key();
    U64 index = key % simple_solution_hash_size;
    int is_entered = 0;

    for (int i = 0; i <= simple_solution_counts[index]; ++i) {
        if (simple_solution_hashes[index][i] == key) {
            is_entered = 1;
        }
    }

    if (!is_entered) {
        simple_solution_hashes[index][simple_solution_counts[index]] = key;
        simple_solution_counts[index]++;
        assert(simple_solution_counts[index] < simple_solution_hash_batch_size);
        four_move_hashes_found++;
    }

    if (depth == 0) {
        return;
    }

    CubeUtil::Cube cube_copy = *cube;
    //cube->copy_cube(&cube_copy);

    for (int move = 0; move <= CubeUtil::M2; move++) {
        if (!cube->is_full_repetition(move)) {
            cube->make_move(move);

            find_hashable_solutions(depth - 1, cube);
            //cube->paste_cube(&cube_copy);
	    *cube = cube_copy;
        }
    }
}


void init_easy_solutions() {
    printf("memsetting\n");
    memset(simple_solution_counts, 0, sizeof simple_solution_counts);
    memset(simple_solution_hashes, 0, sizeof simple_solution_hashes);

    printf("finding hashes\n");
    CubeUtil::Cube c = CubeUtil::Cube();
    find_hashable_solutions(simple_solution_depth, &c);

    printf("Found %d hashable solutions\n", four_move_hashes_found);
}

void init_key_generator() {
    for (int cs = 0; cs < 8; cs++) {
        for (int i = 0; i < 64; ++i) {
            for (int corner = 0; corner < 64; corner++) {
                corner_keys[cs][corner][i] = get_random_U64();
            }
        }
    }
    for (int es = 0; es < 12; es++) {
        for (int i = 0; i < 32; ++i) {
            for (int edge = 0; edge < 32; edge++) {
                edge_keys[es][i][edge] = get_random_U64();
            }
        }
    }
}



void print_U64_binary(U64 number) {
    printf("\n");
    for (int i = 0; i < 64; i++) {
        if (i % 8 == 0)
            printf("\n");
        if ((number >> i) & 1ULL) {
            printf(" 1 ");
        } else {
            printf(" 0 ");
        }
    }
    printf("\n");
}
