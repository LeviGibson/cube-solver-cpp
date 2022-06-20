#include <cstdio>
#include "Cube.h"
#include "Search.h"
#include "simplecubes.h"

int main(){
    init_key_generator();

//    Algs::Algorithm alg = Algs::Algorithm();
//    alg.parse("R U R' U' R' F R2 U' R' U' R U R' F'");
//    alg.print();

    CubeUtil::Cube c = CubeUtil::Cube();
    c.parse_alg("R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R ");
//    c.parse_alg("R U R' U' R' F R2 U' R' U' R U R' F'");
    CubeUtil::Search::solve(c, 64);
}
