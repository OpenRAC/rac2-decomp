/* func_PAL_L16_003F9F10, the PAL copy of func_L16_003F5708: the same C, where third and fourth take
   the 50 Hz scale and 60 becomes 50. */

#include "include_asm.h"
#include "names.h"

/* func_PAL_L16_003F9F10 has a unit of its own: retail reads the particle colours and lifetime bounds
   through bare absolute `lui $r ; lw $r,%lo($r)` pairs that never sit in a delay slot, yet builds
   the size table's address with `addiu $v1,$gp,...` and adds the scaled index to it in a register.
   -mno-split-addresses gives the first form but folds the table into the load; the default split
   profile gives the table form but lets the scheduler drop a bare load into each call slot.
   -membedded-data makes cc1 count a small-data reference as two words (no delay slot, no
   displacement fold), which gives both, unchanged elsewhere: retail puts no $gp access of this
   function into a slot either. The `sda` incomplete arrays are the bare absolute reads
   (compiler-notes.md); the sized `sda` declarations are the $gp ones. */

typedef int Quadword __attribute__((mode(TI)));

extern float D_L16_001B10E4 __attribute__((sda));   /* particle count (200.0) */
extern int D_L16_001B10E8 __attribute__((sda));     /* first colour pair */
extern int D_L16_001B10EC[] __attribute__((sda));
extern int D_L16_001B10F0[] __attribute__((sda));   /* second colour pair */
extern int D_L16_001B10F4[] __attribute__((sda));
extern float D_L16_001B10F8[2] __attribute__((sda)); /* sizes, picked by func_002A77E0(2) */
extern int D_L16_001B1104 __attribute__((sda));
extern int D_L16_001B1108 __attribute__((sda));
extern int D_L16_001B110C[] __attribute__((sda));   /* lifetime bounds */
extern int D_L16_001B1110[] __attribute__((sda));

extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern float math_fabs(float);
extern void FastVecScale(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern void vec_clear_128(void *);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Emits randomly positioned particles outside the central rectangle, each with colours blended
   at random between two pairs, a random size from the table and random lifetimes. */
void func_PAL_L16_003F9F10(char *object)
{
    float position[4];
    float random[4];
    float direction[4];
    int i;
    float scale;
    int first, second, third, fourth;
    float size;
    float blend;

    for (i = 0; (float)i < D_L16_001B10E4; ++i) {
        *(Quadword *)random = 0;
        random[0] = math_random_signed_float_range(0.0f, 26.0f);
        random[1] = math_random_signed_float_range(0.0f, 8.0f);
        random[2] = math_random_float_range(0.0f, 30.0f);
        *(Quadword *)position = *(Quadword *)random;
        if (math_fabs(position[0]) < 9.0f && math_fabs(position[2]) < 25.0f)
            continue;
        scale = *(float *)(object + 44) / *(float *)(*(char **)(object + 36) + 36);
        FastVecScale(position, position, scale);
        matrix_mul_vec3(position, position, object + 192);
        FastVecAdd(position, position, object + 16);
        blend = math_random_float_range(0.0f, 1.0f);
        first = FastTweenColor(D_L16_001B10E8, D_L16_001B10EC[0], blend);
        blend = math_random_float_range(0.0f, 1.0f);
        second = FastTweenColor(D_L16_001B10F0[0], D_L16_001B10F4[0], blend);
        size = D_L16_001B10F8[math_random_int_below(2)];
        vec_clear_128(random);
        random[3] = size;
        vec_clear_128(direction);
        direction[3] = size;
        third = ((int)math_random_int_range(1, D_L16_001B1108) * 5 + 2) / 6;
        fourth = ((int)math_random_int_range(D_L16_001B110C[0], D_L16_001B1110[0]) * 5 + 2) / 6;
        part_spawn_trail(position, random, direction, first, second, third, fourth, 50, D_L16_001B1104);
    }
}
