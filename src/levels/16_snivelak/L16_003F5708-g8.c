#include "include_asm.h"

/* func_L16_003F5708 has a unit of its own: retail reads the particle colours and lifetime bounds
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

extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00282C48(float);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_00282C88(void *);
extern void func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Emits randomly positioned particles outside the central rectangle, each with colours blended
   at random between two pairs, a random size from the table and random lifetimes. */
void func_L16_003F5708(char *object)
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
        random[0] = func_002A78D8(0.0f, 26.0f);
        random[1] = func_002A78D8(0.0f, 8.0f);
        random[2] = func_002A7878(0.0f, 30.0f);
        *(Quadword *)position = *(Quadword *)random;
        if (func_00282C48(position[0]) < 9.0f && func_00282C48(position[2]) < 25.0f)
            continue;
        scale = *(float *)(object + 44) / *(float *)(*(char **)(object + 36) + 36);
        func_00282D30(position, position, scale);
        func_00283098(position, position, object + 192);
        func_00282CC0(position, position, object + 16);
        blend = func_002A7878(0.0f, 1.0f);
        first = func_00283D38(D_L16_001B10E8, D_L16_001B10EC[0], blend);
        blend = func_002A7878(0.0f, 1.0f);
        second = func_00283D38(D_L16_001B10F0[0], D_L16_001B10F4[0], blend);
        size = D_L16_001B10F8[func_002A77E0(2)];
        func_00282C88(random);
        random[3] = size;
        func_00282C88(direction);
        direction[3] = size;
        third = func_002A7820(1, D_L16_001B1108);
        fourth = func_002A7820(D_L16_001B110C[0], D_L16_001B1110[0]);
        func_002BAA28(position, random, direction, first, second, third, fourth, 60, D_L16_001B1104);
    }
}
