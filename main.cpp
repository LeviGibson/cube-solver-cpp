#include <cstdio>
#include "Cube.h"
#include "Search.h"
#include "simplecubes.h"

int main(){
    init_key_generator();

    Algs::Algorithm alg = Algs::Algorithm();
    alg.parse("R U R' F' U' R U2 R2 U' R U' R' U2 F R2 U' R'");
    alg.print();

    CubeUtil::Cube c = CubeUtil::Cube();
    c.parse_alg("R U R2 F' U2 R U R' U R2 U2 R' U F R U' R' ");
//    c.parse_alg("R' U2 R U2 L U' R' U L' U L U' R U L' ");
    CubeUtil::Search::solve(c, 64);
}
