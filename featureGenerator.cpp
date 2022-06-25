//
// Created by levigibson on 6/24/22.
//

#include "featureGenerator.h"
#include <iostream>
#include <fstream>
#include <cassert>

using std::string;
using std::cout;
using std::endl;

string algs[] = {
        "R U' R' D R U R' D' R U R' D R U' R' D'",
        "R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R",
        "D' R2 U R' U R' U' R U' R2 U' D R' U R",
        "R' U' R U D' R2 U R' U R U' R U' R2 D ",
        "R2 F2 R U2 R U2 R' F R U R' U' R' F R2",
        "R2 U' R U' R U R' U R2 D' U R U' R' D",
        "R U R' U' D R2 U' R U' R' U R' U R2 D' ",
        "M2 U M2 U2 M2 U M2",
        "R' U L' U2 R U' R' U2 R L",
        "R U R' F' R U R' U' R' F R2 U' R'",
        "R U R' U R U R' F' R U R' U' R' F R2 U' R' U2 R U' R'",
        "R' U L' U2 R U' L R' U L' U2 R U' L",
        "R U R' F' R U2 R' U2 R' F R U R U2 R'",
        "L U2 L' U2 L F' L' U' L U L F L2",
        "R U' R' U' R U R D R' U' R D' R' U2 R'",
        "R' U2 R U2 R' F R U R' U' R' F' R2",
        "R U R' U' R' F R2 U' R' U' R U R' F'",
        "R U R' U' R' F R2 U' R' U F' L' U L",
        "R U' R U R U R U' R' U' R2",
        "R2 U' R' U' R U R U R U' R",
        "M2 U M U2 M' U M2",
        "R2 U R U R' U' R' U' R' U R'",
        "R U' R U R' D R D' R U' D R2 U R2 D' R2",
        "F R U' R' U' R U R' F' R U R' U' R' F R F'",
        "M2 U M2 U M' U2 M2 U2 M'",
        "R U R' U' R' F R2 U R' U' F'",
        "L' U' L U' L F' L' F L' U2 L",
        "R U R' U R' F R F' R U2 R'",
        "M R U R' U R U2 R' U M'",
        "F U R U2 R' U' R U R' F'",
        "F U R U2 R' U' R U R' F'",
        "R U R' U' R' F R F'",
        "R U2 R2 F R F' R U2 R'",
        "L' U' L U' L' U L U L F' L' F",
        "R U R' U R U' B U' B' R'",
        "R U B' R B R2 U' R' F R F'",
        "R U B' U' R' U R B R'",
        "R B' R' U' R U B U' R'",
};

std::fstream file;
bool initialised = false;

void init(){
    initialised = true;
    file.open("notebooks/data.csv", std::ios::out);
    file << "ALGORITHM, FEATURE_R, FEATURE_L, FEATURE_U, FEATURE_D, FEATURE_F, FEATURE_B, FEATURE_RP, FEATURE_LP, FEATURE_UP, FEATURE_DP, FEATURE_FP, FEATURE_BP, FEATURE_R2, FEATURE_L2, FEATURE_U2, FEATURE_D2, FEATURE_F2, FEATURE_B2, FEATURE_M, FEATURE_MP, FEATURE_M2, FEATURE_REGRIPS, FEATURE_RL_REGRIPS, FEATURE_OVERWORKING, LABEL" << endl;
}

void write_features(Algs::Algorithm algorithm){
    assert(initialised);

//    Algs::Algorithm algorithm = Algs::Algorithm();
//    algorithm.parse(salg.c_str());
    algorithm.score(false);

    file << algorithm.toString() << ',';
    for (int i = 0; i <= FEATURE_OVERWORKING; ++i) {
        file << algorithm.features[i] << ',';
    }

    file << endl;

}
