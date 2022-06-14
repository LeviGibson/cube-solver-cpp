//
// Created by levigibson on 6/5/22.
//

#include "simplecubes.h"

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <unistd.h>
#include "Cube.h"
#include "Algorithm.h"
#include <iostream>
#include <fstream>


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

Algs::Algorithm simplecubesAlg;

void find_hashable_solutions(int maxDepth, CubeUtil::Cube *cube) {
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

    if ((float )maxDepth < simplecubesAlg.score(true)) {
        return;
    }

    CubeUtil::Cube cube_copy = *cube;

    for (int move = 0; move <= CubeUtil::M2; move++) {
        if (!cube->is_full_repetition(move)) {
            cube->make_move(move);
            simplecubesAlg.append(move);
            find_hashable_solutions(maxDepth, cube);
            simplecubesAlg.pop();
            *cube = cube_copy;
        }
    }
}


void init_easy_solutions() {
    simplecubesAlg = Algs::Algorithm();

    printf("memsetting\n");
    memset(simple_solution_counts, 0, sizeof simple_solution_counts);
    memset(simple_solution_hashes, 0, sizeof simple_solution_hashes);

    printf("finding hashes\n");
    CubeUtil::Cube c = CubeUtil::Cube();
    find_hashable_solutions(simple_solution_depth, &c);

    printf("Found %d hashable solutions\n", four_move_hashes_found);
}

bool file_exists (char *filename) {
    FILE *file;

    file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    } else {
        return false;
    }
}

void init_key_generator() {
    //if needed binary files exist, read them

    if (file_exists((char*)"corner_keys.bin")
        && file_exists((char*)"edge_keys.bin")
        && file_exists((char*)"simple_solution_hashes.bin")
        && file_exists((char*)"simple_solution_counts.bin"))   {

        unsigned long tmp;
        FILE *fin = fopen("corner_keys.bin", "rb");
        tmp = fread(corner_keys, sizeof(uint64_t), 8*64*64, fin);
        fclose(fin);

        fin = fopen("edge_keys.bin", "rb");
        tmp = fread(edge_keys, sizeof(uint64_t), 12*32*32, fin);
        fclose(fin);

        fin = fopen("simple_solution_hashes.bin", "rb");
        tmp = fread(simple_solution_hashes, sizeof(uint64_t), simple_solution_hash_size*simple_solution_hash_batch_size, fin);
        fclose(fin);

        fin = fopen("simple_solution_hashes.bin", "rb");
        tmp = fread(simple_solution_hashes, sizeof(uint64_t), simple_solution_hash_size*simple_solution_hash_batch_size, fin);
        fclose(fin);

        fin = fopen("simple_solution_counts.bin", "rb");
        tmp = fread(simple_solution_counts, sizeof(uint16_t), simple_solution_hash_size, fin);
        fclose(fin);
    }
    //otherwise, generate the data and save it
    else {
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

        init_easy_solutions();

        unsigned long tmp;
        FILE *fin = fopen("corner_keys.bin", "wb");
        tmp = fwrite(corner_keys, sizeof(uint64_t), 8*64*64, fin);
        fclose(fin);

        fin = fopen("edge_keys.bin", "wb");
        tmp = fwrite(edge_keys, sizeof(uint64_t), 12*32*32, fin);
        fclose(fin);

        fin = fopen("simple_solution_hashes.bin", "wb");
        tmp = fwrite(simple_solution_hashes, sizeof(uint64_t), simple_solution_hash_size*simple_solution_hash_batch_size, fin);
        fclose(fin);

        fin = fopen("simple_solution_hashes.bin", "wb");
        tmp = fwrite(simple_solution_hashes, sizeof(uint64_t), simple_solution_hash_size*simple_solution_hash_batch_size, fin);
        fclose(fin);

        fin = fopen("simple_solution_counts.bin", "wb");
        tmp = fwrite(simple_solution_counts, sizeof(uint16_t), simple_solution_hash_size, fin);
        fclose(fin);
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
