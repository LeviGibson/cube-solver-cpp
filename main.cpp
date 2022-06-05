#include <cstdio>
#include <cstdlib>
#include "Cube.h"
#include "simplecubes.h"

int main(){
    srand(1001974038);
    init_key_generator();
    init_easy_solutions();

    CubeUtil::Cube c = CubeUtil::Cube();
    c.make_move(CubeUtil::R);
    c.make_move(CubeUtil::U);
    c.make_move(CubeUtil::RP);
    c.make_move(CubeUtil::UP);
    printf("%d\n", c.cube_has_simple_solution());
//
//    CubeUtil::Cube cube_copy;
//    c.copy_cube(&cube_copy);
//    c.make_move(CubeUtil::R);
//    c.print_cube();
//    c.paste_cube(&cube_copy);
//    c.print_cube();

}
