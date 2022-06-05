#include <cstdio>
#include "Cube.h"
#include "Search.h"
#include "simplecubes.h"

int main(){
    init_key_generator();
    init_easy_solutions();

    CubeUtil::Cube c = CubeUtil::Cube();

    c.parse_alg("R U R' U' R' F R2 U' R' U' R U R' F'");

    c.print_cube();

    CubeUtil::Search::solve(c, 9);
}
