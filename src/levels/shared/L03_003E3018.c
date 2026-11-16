#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec4;

/* The path record at +0x68 of the puzzle object (see func_L03_003E26C8). */
typedef struct {
    u8 order[16];
    u8 visited[16];
    u8 path[16];
    u8 facing[16];
    u8 choices[16];
    s16 current;
    s16 next;
    u8 pad54[8];
    s16 last;
    s16 length;
} PuzzlePath;

extern Vec4 g_puzzle_node_directions[14];
extern int g_path_puzzle_adjacency[14][6];
extern Vec4 g_moby_basis_matrix[3];
/* Both quaternions are read through the bare-symbol `la` macro (the adjacent lui/addiu
   pairs), which cc1 emits for an sda symbol. */
extern Vec4 g_puzzle_rotation_quat __attribute__((sda));
extern Vec4 g_puzzle_target_quat __attribute__((sda));
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecScale(void *, void *, f32);
extern void FastVecCross(void *, void *, void *);
extern f32 FastVecDot(void *, void *);
extern f32 FastVecLength(void *);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void multiply_quaternions(void *, void *, void *);

/* Works out the orientation the puzzle turns to: the turn that brings its current node onto
   the negated first row of the basis D_L03_001B9BB0, then the roll about that row that
   brings to the front the neighbour chosen for this path length (once, the neighbour lying
   furthest along the basis's third row). Both turns are composed onto the orientation
   D_L03_001B36B0 into D_L03_001B36C0; the matrix at +0xC0, turned for the tests, is rebuilt
   from D_L03_001B36B0. */
void ComputePathPuzzleTurn(u8 *moby) {
    f32 matrix[12];
    Vec4 neg, v, axis, turn, test;
    PuzzlePath *path_state = *(PuzzlePath **)(moby + 0x68);
    f32 angle = -1.0f;
    f32 best, x, y;
    int i, n;

    matrix_mul_vec3(&v, &g_puzzle_node_directions[path_state->current], moby + 0xC0);
    FastVecScale(&neg, &g_moby_basis_matrix[0], angle);
    best = angle;
    FastVecCross(&axis, &v, &neg);
    axis.w = FastVecDot(&v, &neg);
    angle = mat_fast_helper_a(axis.w, FastVecLength(&axis)) * 0.5f;
    vec_scale_to_length(&axis, &axis, math_fast_sin_or_cos_b(angle));
    axis.w = math_fast_sin_or_cos_a(angle);
    quaternion_to_rotation_basis(&axis, matrix);
    multiply_matrix3x3(moby + 0xC0, matrix, moby + 0xC0);

    if (path_state->facing[path_state->length] == 255) {
        i = 0;
        do {
            n = g_path_puzzle_adjacency[path_state->current][i];
            if (n != -1) {
                matrix_mul_vec3(&test, &g_puzzle_node_directions[n], moby + 0xC0);
                x = FastVecDot(&test, &g_moby_basis_matrix[2]);
                y = FastVecDot(&test, &g_moby_basis_matrix[1]);
                if (x > best) {
                    mat_fast_helper_a(x, y);
                    best = x;
                    path_state->facing[path_state->length] = n;
                }
            }
        } while (++i < 6);
    }

    matrix_mul_vec3(&test, &g_puzzle_node_directions[path_state->facing[path_state->length]], moby + 0xC0);
    x = FastVecDot(&test, &g_moby_basis_matrix[2]);
    y = FastVecDot(&test, &g_moby_basis_matrix[1]);
    angle = mat_fast_helper_a(x, y) * 0.5f;
    vec_scale_to_length(&turn, &neg, math_fast_sin_or_cos_b(angle));
    turn.w = math_fast_sin_or_cos_a(angle);
    multiply_quaternions(&g_puzzle_target_quat, &g_puzzle_rotation_quat, &axis);
    multiply_quaternions(&g_puzzle_target_quat, &g_puzzle_target_quat, &turn);
    quaternion_to_rotation_basis(&g_puzzle_rotation_quat, moby + 0xC0);
}
