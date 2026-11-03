/* func_L09_003FB9F8 -- NOT MATCHING. Tier opus-1 (v2074), 2 November 2026.
 * Profile: -O2 -G0 -ffunction-sections -g (a unit of its own; the declarations below differ in type
 * from L09_002F8BA0.c's, e.g. D_L09_001B3620..36A0 are float here, int there).
 * Best check.py: us and us2 "09_dobbo: instruction at +0x330 differs", 1440/1440 bytes, 0 of 1 places;
 * pal: not in the catalogue.
 * Starting point was the sol-high v1126 draft (1440/1440, first difference +0x118). Indexing the angle loop
 * and the output loop's stores as D_L09_00256510[row][i] (instead of row pointers) puts the table base inside
 * the loops, so loop.c hoists it and no global PRE'd %hi is left: the first-loop setup, angle-loop setup and the
 * qcopy address pair now match. Indexing the previousZ read too (both rows indexed) gives retail's
 * base-then-base+8 order, but then loop.c pass 2 has 52 insns and only threshold 49 left for the 1.0f store
 * constant (life 1), so it stays in the loop (1428 bytes). Row-pointer output + indexed previousZ is worse.
 * Still different:
 *  - output-loop setup (+0x328..+0x39C): retail materializes la D_L09_001B3660 before la D_L09_001B36A0, keeps
 *    the 0x60 constant in a0 and computes the base then base+8; ours forms base+8 from the previousZ pointer
 *    first (addiu a0,v0,8; addiu v0,a0,-8);
 *  - final-loop setup (+0x43C..+0x484): retail's la D_L09_00255E90 and la D_L09_001B37A0 use one register each,
 *    and the init order is s2=sp+0x30, s6=100, s3|=0x7F7F, s5=1 (ours puts s5=1 first).
 * Needs: the declarations below (MACRO_ADDR on the D_L09_001B35E0..37A0 tables and D_L09_001A8F20).
 */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

extern int func_L02_002F1658(void);
extern void func_00282CF0(float *, const float *, const float *);
extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern float func_00283B98(float, float);
extern float func_00283BE0(float, float);
extern void func_00282F20(void *, void *, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002ABB18(float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void func_002ACB48(void *, float);
extern char *func_L08_0034A078(void *, void *, int, void *);

extern int D_L09_001B35E0[16] MACRO_ADDR;
extern float D_L09_001B3620[16] MACRO_ADDR;
extern float D_L09_001B3660[16] MACRO_ADDR;
extern float D_L09_001B36A0[16] MACRO_ADDR;
extern int D_L09_001B36E0[16] MACRO_ADDR;
extern int D_L09_001B3720[16] MACRO_ADDR;
extern int D_L09_001B37A0[16] MACRO_ADDR;
extern unsigned char *D_L09_00255E90[16][2];
extern Vec D_L09_00255F40[16][4];
extern Vec D_L09_00256310[16];
extern Vec D_L09_00256410[16];
extern Vec D_L09_00256510[][6];
extern char D_L09_001A8F20[] MACRO_ADDR;

void func_L09_003FB9F8(void *object, int slot)
{
    Vec delta, origin, direction, pos;
    Vec *a, *b;
    float *previousZ;
    float length, step;
    int i, alpha, first, second;
    unsigned char **pair;
    char *effect, *payload;
    if (!func_L02_002F1658()) return;
    alpha = D_L09_00255E90[slot][0][0x23];
    func_00282CF0(delta.f, D_L09_00256310[slot].f, D_L09_00255F40[slot][0].f);
    first = slot * 2;
    second = first + 1;
    length = func_00282DF0(&delta);
    step = length / func_00283CE0(5);
    if (D_L09_001B35E0[slot] == 2) {

        D_L09_001B35E0[slot] = 3;
        for (i = 0; i < 6; i++) {
            float x = step * func_00283CE0(i);
            D_L09_00256510[first][i].f[1] = D_L09_00256510[first][i].f[2] = 0.0f;
            D_L09_00256510[first][i].f[3] = 1.0f;
            D_L09_00256510[second][i].f[0] = D_L09_00256510[first][i].f[0] = x;
            D_L09_00256510[second][i].f[1] = D_L09_00256510[second][i].f[2] = 0.0f;
            D_L09_00256510[second][i].f[3] = 1.0f;
        }
    }
    D_L09_001B3620[slot] = func_00283B98(D_L09_001B3620[slot], 0.17453295f);
    D_L09_001B3660[slot] = func_00283BE0(D_L09_001B3660[slot], 0.8028515577316284f);
    D_L09_001B36A0[slot] = func_00283B98(D_L09_001B36A0[slot], 0.052359998f);
    qcopy(&origin, &D_L09_00255F40[slot][0]);
    func_00282F20(&direction, &delta, step);
    {
    float angleStep = (360.0f / (func_00283CE0(6) * 0.5f)) * 0.017453294f;
    for (i = 0; i < 6; i++) {
        float t = func_00283CE0(i);
        float y = func_00283198(t / func_00283CE0(5) * 3.1415927f) * -0.09f + 0.1f;
        y *= func_00283198(func_002ABB18(D_L09_001B3620[slot] + t * angleStep));
        D_L09_00256510[first][i].f[1] = 0;
        D_L09_00256510[first][i].f[3] = 1;
        D_L09_00256510[first][i].f[2] = y;
        D_L09_00256510[first][i].f[0] = step * t;
    }
    }
    qcopy(&D_L09_00256410[slot], D_L09_00255E90[slot][1] + 0x10);
    previousZ = &D_L09_00256510[first][0].f[2];
    for (i = 0; i < 6; i++) {
        float t = func_00283CE0(i);
        float x = func_002ABB18(D_L09_001B3660[slot] + t * 0.99483776f);
        float z = func_002ABB18(D_L09_001B36A0[slot] + t * 0.20943999f);
        float y = func_00283198(z) * 0.2f;
        z = func_00283198(x);
        {
            float noise = func_002A78D8(0, 0.2f);
            D_L09_00256510[second][i].f[2] = (*previousZ + y * z) + noise;
        }
        D_L09_00256510[second][i].f[1] = func_00283180(x) * 0.1f;
        D_L09_00256510[second][i].f[3] = 1;
        D_L09_00256510[second][i].f[0] = step * t;
        previousZ += 4;
    }
    pair = D_L09_00255E90[slot];
    {
    for (first = 1; first >= 0; first--, pair++) {
        if (func_002A77E0(3)) continue;
        qcopy(&pos, *pair + 0x10);
        func_002ACB48(&pos, 0.1f);
        effect = func_L08_0034A078(&pos, D_L09_001A8F20, alpha * 127 / 100, *pair);
        if (effect) {
            payload = effect + 0x20;
            *(float *)(effect + 0xC) = 120000;
            *(short *)(effect + 0xA) = 4;
            *(float *)(payload + 0x10) = 1.0f / func_00283CE0(4);
            *(int *)(payload + 0x18) = 0x7F7F7F;
            if (D_L09_001B37A0[slot] == 1) *(short *)(payload + 0x16) = 1;
        }
    }
    }
    D_L09_001B36E0[slot] = -1;
    D_L09_001B3720[slot] = -1;
}
