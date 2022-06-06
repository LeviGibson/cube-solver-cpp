//
// Created by levigibson on 6/2/22.
//

#ifndef CUBE_SOLVER_CPP_CUBE_H
#define CUBE_SOLVER_CPP_CUBE_H


#include <stdint.h>
#define U8 uint8_t
#define U64 uint64_t
#define U32 uint32_t
#define I8 int8_t
#define I32 int32_t

namespace CubeUtil {

    enum {
        R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2, M, MP, M2
    };
    enum {
        X, Y, Z, XP, YP, ZP, X2, Y2, Z2
    };
    enum {
        AXIS_M, AXIS_E, AXIS_S
    };
    enum {
        SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B
    };



    #define encode_piece(index, orientation) \
        ((index) | ((orientation) << 4))

    #define get_piece_index(piece) ((piece) & 15)
    #define get_piece_orientation(piece) ((piece) >> 4)

    /**
    #define increment_corner_orientation(corner) \
        corner = (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 1)%3))

    #define decrement_corner_orientation(corner) \
        corner = (encode_piece(get_piece_index((corner)), (get_piece_orientation((corner)) + 2)%3))**/


    class Cube {
    private:
        U8 corners[8]{};
        U8 edges[12]{};
        I32 moveTransformer[21] = {R, L, U, D, F, B, RP, LP, UP, DP, FP, BP, R2, L2, U2, D2, F2, B2, M, MP, M2};
        I8 moveToAxis[21] = {AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S, AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S,
                                 AXIS_M, AXIS_M, AXIS_E, AXIS_E, AXIS_S, AXIS_S, AXIS_M, AXIS_M, AXIS_M};
        I8 moveToSide[21] = {SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B, SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B, SIDE_R, SIDE_L, SIDE_U, SIDE_D, SIDE_F, SIDE_B};
        I8 axisHistory[3] = {0, 0, 0};
        I8 sideHistory[6] = {0, 0, 0, 0, 0, 0};

    public:
        Cube();

        void reset_history();

        U64 get_key();
        int has_simple_solution();

        void make_move(int move);

	/*
        void copy_cube(Cube *target);
        void paste_cube(Cube *target);
	*/
	//completly unnecesary.  by the magic of C++ -> Cube newCube = otherCube

        void parse_alg(const char *alg);

        int is_solved();
        int is_full_repetition(int move);

        void print_move(int move);
        void print();

        void update_rotation(int move);
    };

}

#endif //CUBE_SOLVER_CPP_CUBE_H
