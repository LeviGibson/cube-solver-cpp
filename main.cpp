#include <cstdio>
#include "Cube.h"

int main(){

    CubeUtil::Cube c = CubeUtil::Cube();

    CubeUtil::Cube cube_copy;
    c.copy_cube(&cube_copy);
    c.make_move(CubeUtil::R);
    c.print_cube();
    c.paste_cube(&cube_copy);
    c.print_cube();

}
