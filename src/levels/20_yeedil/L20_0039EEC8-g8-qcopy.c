#include "names.h"
/* func_L20_0039EEC8 makes an object of class 0x1316 at `position` for `owner`, resets its
   rotation matrix and fills D_L20_00234880 and D_L20_00235500 from the matrix axes.
   - The object's position is copied with the qcopy helper; its volatile asm keeps the
     beqz delay slot filled from the return path (`daddu $v0,$s6,$zero`).
   - The matrix is reset through `object + 0xC0` and the three axis pointers are taken
     after the first clear loop: gcse then copies the call's argument (`addiu $a0` and
     `daddu $fp,$a0`).
   - The tables cleared by the three loops and the scalars D_L20_001AEDA0 and
     D_L20_001B3904 are incomplete `sda` arrays: the compiler emits `la`/`lw`/`sw` macros,
     which the assembler expands into absolute lui forms. The loop counters are separate.
   - The 6.0f scale D_L20_001AED40 is a sized `sda` float, read through $gp. */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char *CreateMoby(int);
extern void set_identity_rotation_rows(void *);
extern void vec_scale_to_length(void *, const void *, float);
extern void FastVecAdd(void *, const void *, const void *);
extern void FastVecSub(void *, const void *, const void *);
extern void FastVecCross(void *, const void *, const void *);
extern unsigned int g_electric_orb_state_color[] __attribute__((sda));
extern float g_electric_basis_length __attribute__((sda));
extern int g_orb_trail_counts[] __attribute__((sda));
extern int g_orb_trail_state[] __attribute__((sda));
extern short g_orb_arm_numerators[] __attribute__((sda));
extern float g_orb_alpha_scale[] __attribute__((sda));
extern Vector g_orb_arm_vectors[8][25];
extern Vector g_electric_orb_basis_vectors[8];

/* Creates the electric orb at a position and sets up the directions of its eight arms. */
unsigned char *electric_orb_spawn(unsigned char *owner, const Vector *position) {
    unsigned char *object = CreateMoby(0x1316 /* moby class 4886 */);
    unsigned char *state;
    Vector *x, *y, *z;
    int i, j, k;
    if (object) {
        qcopy(object + 0x10, position);
        set_identity_rotation_rows(object + 0xC0);
        state = *(unsigned char **)(object + 0x68);
        object[0x30] = 255;
        *(unsigned char **)(object + 0xB8) = owner;
        *(int *)state = 5;
        *(unsigned int *)(state + 4) = g_electric_orb_state_color[0] & 0xFFFFFF;
        *(int *)(state + 0x10) = 0;
        *(int *)(state + 0x14) = 0;
        for (i = 7; i >= 0; --i) g_orb_trail_counts[i] = 0;
        x = (Vector *)(object + 0xC0);
        z = (Vector *)(object + 0xE0);
        y = (Vector *)(object + 0xD0);
        vec_scale_to_length(&g_orb_arm_vectors[0][0], x, g_electric_basis_length);
        g_electric_orb_basis_vectors[0].q = z->q;
        vec_scale_to_length(&g_orb_arm_vectors[1][0], y, g_electric_basis_length);
        g_electric_orb_basis_vectors[1].q = x->q;
        vec_scale_to_length(&g_orb_arm_vectors[2][0], z, g_electric_basis_length);
        g_electric_orb_basis_vectors[2].q = y->q;
        FastVecAdd(&g_orb_arm_vectors[3][0], x, z);
        vec_scale_to_length(&g_orb_arm_vectors[3][0], &g_orb_arm_vectors[3][0], g_electric_basis_length);
        FastVecCross(&g_electric_orb_basis_vectors[3], &g_orb_arm_vectors[3][0], y);
        vec_scale_to_length(&g_electric_orb_basis_vectors[3], &g_electric_orb_basis_vectors[3], 1.0f);
        FastVecAdd(&g_orb_arm_vectors[4][0], x, y);
        vec_scale_to_length(&g_orb_arm_vectors[4][0], &g_orb_arm_vectors[4][0], g_electric_basis_length);
        FastVecCross(&g_electric_orb_basis_vectors[4], &g_orb_arm_vectors[4][0], z);
        vec_scale_to_length(&g_electric_orb_basis_vectors[4], &g_electric_orb_basis_vectors[4], 1.0f);
        FastVecSub(&g_orb_arm_vectors[5][0], y, z);
        vec_scale_to_length(&g_orb_arm_vectors[5][0], &g_orb_arm_vectors[5][0], g_electric_basis_length);
        FastVecCross(&g_electric_orb_basis_vectors[5], &g_orb_arm_vectors[5][0], x);
        vec_scale_to_length(&g_electric_orb_basis_vectors[5], &g_electric_orb_basis_vectors[5], 1.0f);
        FastVecSub(&g_orb_arm_vectors[6][0], x, z);
        vec_scale_to_length(&g_orb_arm_vectors[6][0], &g_orb_arm_vectors[6][0], g_electric_basis_length);
        FastVecCross(&g_electric_orb_basis_vectors[6], &g_orb_arm_vectors[6][0], y);
        vec_scale_to_length(&g_electric_orb_basis_vectors[6], &g_electric_orb_basis_vectors[6], 1.0f);
        FastVecSub(&g_orb_arm_vectors[7][0], x, y);
        vec_scale_to_length(&g_orb_arm_vectors[7][0], &g_orb_arm_vectors[7][0], g_electric_basis_length);
        FastVecCross(&g_electric_orb_basis_vectors[7], &g_orb_arm_vectors[7][0], z);
        vec_scale_to_length(&g_electric_orb_basis_vectors[7], &g_electric_orb_basis_vectors[7], 1.0f);
        for (j = 7; j >= 0; --j) g_orb_trail_state[j] = 0;
        for (k = 9; k >= 0; --k) g_orb_arm_numerators[k] = 0;
        g_orb_alpha_scale[0] = 1.0f;
    }
    return object;
}
