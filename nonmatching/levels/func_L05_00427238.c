/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections.
 * us: 0/4; us2: 0/4; pal: absent.
 * 1124/1196 bytes; frame 0xB0. Four full vectors, short-circuit query/effect paths, all eleven
 * burst integer-bank arguments including three stack slots, and six-argument particle spawning
 * are retained. Both burst helpers keep their actual pointer returns. Branch folding, loop
 * source pointers and outgoing arguments differ.
 * Reopen: Independent impact/trail CFG and packet/argument lifetime witness.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(void *);
extern int func_00277258(void *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L05_004276E8(void *, void *, void *);
extern void *func_L05_00424990(void *, int, int, int, int, int, int, int, int, int, int, float);
extern void *func_L05_003D1E60(void *, int, int);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern u8 *func_002BD8B0(void *, void *, u32, u32, int, int, float);
extern float D_L05_001B1530 __attribute__((sda));
extern float D_L05_001B1534 __attribute__((sda));
extern char D_L05_001BFB00[], D_L05_001BFB20[], D_L05_001BFB30[], D_L05_001FF240[];

void func_L05_00427238(u8 *actor)
{
    Vector previous, trail, delta, velocity;
    u8 *state = *(u8 **)(actor + 0x68);
    float *position = (float *)(actor + 0x10);
    int hit, i;
    float radius;
    qcopy(&previous, position);
    func_00282CC0(position, position, state);
    *(float *)(actor + 0x2C) += 0.07f;
    if (*(float *)(*(char **)(actor + 0x24) + 0x24) < *(float *)(actor + 0x2C))
        *(float *)(actor + 0x2C) = *(float *)(*(char **)(actor + 0x24) + 0x24);
    if (func_00282948(state + 0x18) != 0 ||
        position[0] < 2.0f || position[0] > 1021.0f ||
        position[1] < 2.0f || position[1] > 1021.0f ||
        position[2] < 2.0f || position[2] > 1021.0f)
        goto destroy;
    if (func_00282948(state + 0x28) != 0) {
        hit = 0;
        radius = *(int *)(state + 0x24) != 0 ? D_L05_001B1534 : D_L05_001B1530;
        if (func_00277258(position, 16, *(void **)(state + 0x20), radius) != 0) {
            hit = 1;
            qcopy(position, D_L05_001BFB30);
        }
        if ((hit || func_002761F8(&previous, position, 16, *(void **)(state + 0x20), 0)) &&
            *(int *)(D_L05_001BFB00 + 0x18) != 0) {
            func_002E5DA0(7, 0, actor, 0xFBF);
            goto impact;
        }
        goto finish;
    }
    if (func_00278E78() != 6) {
        radius = *(int *)(state + 0x24) != 0 ? 1.5f : 1.0f;
        hit = 0;
        if (func_00277258(position, 16, *(void **)(state + 0x20), radius) != 0) {
            hit = 1;
            qcopy(position, D_L05_001BFB30);
        }
        if (hit || func_002761F8(&previous, position, 16, *(void **)(state + 0x20), 0)) {
            func_002E5DA0(7, 0, actor, 0xFBF);
            goto impact;
        }
    }
    trail.q = previous.q;
    func_00282CF0(&delta, position, &previous);
    func_00282D30(&delta, &delta, 0.3330000043f);
    for (i = 2; i >= 0; i--) {
        float azimuth, elevation;
        u32 a, b;
        u8 *particle;
        func_00282CC0(&trail, &trail, &delta);
        azimuth = func_002A7940();
        elevation = func_002A7940();
        func_002AF000(&velocity, 0.01250000112f, azimuth, elevation);
        if (*(int *)(state + 0x24) != 0) {
            particle = func_002BD8B0(&trail, &velocity, 0x4FFF0040, 0x1FFF0040, 10, 1, 30000.0f);
            a = 0x4FFF2040;
            b = 0x1FFF2040;
        } else {
            particle = func_002BD8B0(&trail, &velocity, 0x4F00FF20, 0x1F00FF20, 10, 1, 30000.0f);
            a = 0x4F20FF20;
            b = 0x1F20FF20;
        }
        if (particle != 0)
            particle[2] = (*(u8 **)(D_L05_001FF240 + 0x184))[7];
        particle = func_002BD8B0(&trail, &velocity, a, b, 10, 1, 15000.0f);
        if (particle != 0)
            particle[2] = (*(u8 **)(D_L05_001FF240 + 0x184))[7];
    }
    return;
impact:
    qcopy(position, D_L05_001BFB20);
    func_L05_004276E8(actor, state, position);
finish:
    if (*(int *)(state + 0x2C) != 0) {
        if (*(int *)(state + 0x24) != 0)
            func_L05_00424990(position, 0, 50, 30, 30, 30, 40, 1, 1, 1, 1, 2.0f);
        func_L05_003D1E60(position, 0, 0);
    }
destroy:
    func_0029F338(actor);
}
