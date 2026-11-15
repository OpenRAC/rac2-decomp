#include "include_asm.h"
#include "common.h"

/* func_L00_00412FF8 reads its spawn counters through $gp, and func_L00_004173B0 its
 * spawn configurations, hence -G8. */

extern int D_L00_001B1378 __attribute__((sda));
extern int D_L00_001B137C __attribute__((sda));
extern unsigned short D_L00_001B13DC __attribute__((sda));
extern char D_00189EB0[];
extern char D_L00_0025A1A0[];
extern char D_L00_0025A420[];
extern char *func_0029EFD0(int id);
extern void func_002833F0(char *dst, char *src);
extern void func_00282D30(float *dst, char *src, float scale);
extern void func_00282CC0(char *dst, char *src, float *local);
extern void func_L00_00413298(char *object);

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void func_002AFFD8(void *, void *, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
extern void func_002AF000(void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void *func_L00_0033E888(float, void *, void *, int, int, int, int, float, int, int, int);
extern void *func_L00_0033C0D0(void *, void *, void *, void *, int);
extern char D_L00_001B1418 __attribute__((sda));
extern char D_L00_001B13F8 __attribute__((sda));
extern char D_L00_001B1408 __attribute__((sda));
extern char D_L00_001B1428 __attribute__((sda));

char *func_L00_00412FF8(char *owner)
{
    char *object = CreateMoby(0x1195);
    char *state;
    int counter;
    float local[4];

    if (object != 0) {
        *(unsigned char *)(object + 0x20) = 1;
        *(unsigned char *)(object + 0x30) = 0xFF;
        state = *(char **)(object + 0x68);
        *(unsigned short *)(state + 0x1E) = D_L00_001B13DC;
        *(int *)(state + 0x18) = -1;
        euler_rotation_basis(object + 0xC0, D_00189EB0);
        counter = D_L00_001B1378;
        *(char **)(state + 0) = D_L00_0025A1A0 + counter * 0xA0;
        *(char **)(state + 4) = D_L00_0025A420 + counter * 0x140;
        if ((unsigned int)counter >= 4)
            D_L00_001B1378 = 0;
        D_L00_001B1378 = (D_L00_001B1378 + 1) % 4;
        *(int *)(state + 0x24) = D_L00_001B137C;
        *(char **)(state + 0x20) = owner;
        FastVecScale(local, *(char **)(D_00189EB0 + 0x2200) + 0xE0, 0.75f);
        FastVecAdd(object + 0x10, D_00189EB0 - 0x10, local);
        func_L00_00413298(object);
    }
    return object;
}

/* Emits three effect particles at the object, then four spawns along its velocity at rising heights. */
void func_L00_004173B0(char *object)
{
    Vec up, velocity, pos, pos2, pos3, pos4;
    char *state = *(char **)(object + 0x68);
    int i;
    float angle, random, life, speed, spread, frame;

    func_002AFFD8(object + 0x10, &up, 1);
    if (*(int *)(state + 4) != 0)
        return;
    frame = 0.016666668f;
    for (i = 0; i < 3; i++) {
        angle = func_002A7878(-0.9599311948f, -1.3962635994f);
        random = func_002A7940();
        speed = func_002A7878(0.0f, 0.5f);
        spread = 0.3f;
        frame = 0.016666668f;
        speed *= frame;
        func_002AF000(&velocity, speed, random, angle);
        life = func_002A7878(0.65f, 0.85f) * 210000.0f;
        pos.f[0] = *(float *)(object + 0x10) + func_002A78D8(0.0f, spread);
        pos.f[1] = *(float *)(object + 0x14) + func_002A78D8(0.0f, spread);
        pos.f[2] = *(float *)(object + 0x18) + func_002A78D8(0.0f, spread);
        func_L00_0033E888(life, &pos, &velocity, 0x4F808080, 0x08101010, func_002A7820(35, 50), 1, 0.5f, 1, -1, 1);
    }
    func_002AFFD8(object + 0x10, &velocity, 1);
    vec_scale_to_length(&velocity, &velocity, 0.2f);
    qcopy_nc(&pos, object + 0x10);
    pos.f[2] += func_002A7878(0.1f, 0.4f);
    func_L00_0033C0D0(object, &pos, &velocity, &D_L00_001B1418, func_002A77E0(2));
    qcopy_nc(&pos2, object + 0x10);
    pos2.f[2] += func_002A7878(0.9f, 1.2f);
    func_L00_0033C0D0(object, &pos2, &velocity, &D_L00_001B13F8, func_002A77E0(2));
    qcopy_nc(&pos3, object + 0x10);
    pos3.f[2] += func_002A7878(0.8f, 1.5f);
    func_L00_0033C0D0(object, &pos3, &velocity, &D_L00_001B1408, func_002A77E0(2));
    qcopy_nc(&pos4, object + 0x10);
    func_L00_0033C0D0(object, &pos4, &velocity, &D_L00_001B1428, func_002A77E0(2));
}
