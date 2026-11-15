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

extern Vec4 D_L03_0029BBF0[14];
extern int D_0024A7B0[14][6];
extern Vec4 D_L03_001B9BB0[3];
/* Both quaternions are read through the bare-symbol `la` macro (the adjacent lui/addiu
   pairs), which cc1 emits for an sda symbol. */
extern Vec4 D_L03_001B36B0 __attribute__((sda));
extern Vec4 D_L03_001B36C0 __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern f32 func_00282DB0(void *, void *);
extern f32 func_00282DF0(void *);
extern f32 func_00283248(f32, f32);
extern f32 func_00283198(f32);
extern f32 func_00283180(f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_002837D0(void *, void *, void *);

/* Works out the orientation the puzzle turns to: the turn that brings its current node onto
   the negated first row of the basis D_L03_001B9BB0, then the roll about that row that
   brings to the front the neighbour chosen for this path length (once, the neighbour lying
   furthest along the basis's third row). Both turns are composed onto the orientation
   D_L03_001B36B0 into D_L03_001B36C0; the matrix at +0xC0, turned for the tests, is rebuilt
   from D_L03_001B36B0. */
void func_L03_003E3018(u8 *p) {
    f32 matrix[12];
    Vec4 neg, v, axis, turn, test;
    PuzzlePath *q = *(PuzzlePath **)(p + 0x68);
    f32 angle = -1.0f;
    f32 best, x, y;
    int i, n;

    matrix_mul_vec3(&v, &D_L03_0029BBF0[q->current], p + 0xC0);
    FastVecScale(&neg, &D_L03_001B9BB0[0], angle);
    best = angle;
    FastVecCross(&axis, &v, &neg);
    axis.w = FastVecDot(&v, &neg);
    angle = func_00283248(axis.w, FastVecLength(&axis)) * 0.5f;
    vec_scale_to_length(&axis, &axis, func_00283198(angle));
    axis.w = func_00283180(angle);
    quaternion_to_rotation_basis(&axis, matrix);
    multiply_matrix3x3(p + 0xC0, matrix, p + 0xC0);

    if (q->facing[q->length] == 255) {
        i = 0;
        do {
            n = D_0024A7B0[q->current][i];
            if (n != -1) {
                matrix_mul_vec3(&test, &D_L03_0029BBF0[n], p + 0xC0);
                x = FastVecDot(&test, &D_L03_001B9BB0[2]);
                y = FastVecDot(&test, &D_L03_001B9BB0[1]);
                if (x > best) {
                    func_00283248(x, y);
                    best = x;
                    q->facing[q->length] = n;
                }
            }
        } while (++i < 6);
    }

    matrix_mul_vec3(&test, &D_L03_0029BBF0[q->facing[q->length]], p + 0xC0);
    x = FastVecDot(&test, &D_L03_001B9BB0[2]);
    y = FastVecDot(&test, &D_L03_001B9BB0[1]);
    angle = func_00283248(x, y) * 0.5f;
    vec_scale_to_length(&turn, &neg, func_00283198(angle));
    turn.w = func_00283180(angle);
    multiply_quaternions(&D_L03_001B36C0, &D_L03_001B36B0, &axis);
    multiply_quaternions(&D_L03_001B36C0, &D_L03_001B36C0, &turn);
    quaternion_to_rotation_basis(&D_L03_001B36B0, p + 0xC0);
}
