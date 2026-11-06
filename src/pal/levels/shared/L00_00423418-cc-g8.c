#include "include_asm.h"

#include "common.h"

/* func_PAL_L00_00423418, the PAL copy of func_L00_0041E168: the same C, where the particle life 60 becomes 50,
 * 1/60 becomes 0.02 and the last argument of both particle calls gains * 1.44f. */

extern char D_L00_001B8DC0[], D_00189ED0[];
typedef struct { u8 pad0[4]; u8 flag; u8 pad5[224 - 5]; } Weapon_L00_0041E168;
typedef struct { u8 pad0[0x16]; u8 slot; } Save_L00_0041E168;
extern Weapon_L00_0041E168 D_L00_00262570[];
extern Save_L00_0041E168 D_00139568;
extern int D_L00_001A8FF0 MACRO_ADDR;
extern float D_L00_001B1488 __attribute__((sda)), D_L00_001B148C __attribute__((sda));
extern float D_L00_001B1474 __attribute__((sda)), D_L00_001B1478 __attribute__((sda));
extern float D_L00_001B147C __attribute__((sda)), D_L00_001B1480 __attribute__((sda)), D_L00_001B1484 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, unsigned int, float, float, int, int, void *, int, float);

void func_PAL_L00_00423418(float *origin, int count, int mode)
{
    float velocity[4] __attribute__((aligned(16)));
    float previous[4] __attribute__((aligned(16)));
    float difference[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float projection[4] __attribute__((aligned(16)));
    float size, rotation;
    int direction;
    unsigned int color;
    char *particle;

    func_00282CF0(difference, D_L00_001B8DC0, origin);
    if (D_L00_001A8FF0 == 0) {
        difference[2] = 0.0f;
        axis[0] = 0.0f;
        axis[1] = 0.0f;
        axis[2] = 1.0f;
        axis[3] = 1.0f;
    } else {
        func_00282CF0(projection, origin, D_00189ED0);
        func_00282F20(axis, projection, 1.0f);
        func_00282D30(projection, axis, func_00282DB0(axis, difference));
        func_00282CF0(difference, difference, projection);
    }
    if (count <= 0)
        return;
    do {
        size = func_002A7878(D_L00_001B1488, D_L00_001B148C);
        direction = func_002A77E0(2);
        if (direction == 0)
            direction--;
        rotation = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, difference, axis, rotation);
        func_00282F20(velocity, velocity, func_002A7878(D_L00_001B1474, D_L00_001B1478) * 0.020000001f);
        velocity[2] = func_002A7878(D_L00_001B147C, D_L00_001B1480) * 0.020000001f;
        qcopy(previous, origin);
        origin[0] += func_002A78D8(0.0f, 0.15f);
        origin[1] += func_002A78D8(0.0f, 0.15f);
        origin[2] += func_002A78D8(0.0f, 0.15f);
        if (((Weapon_L00_0041E168 *)(D_00139568.slot * sizeof(Weapon_L00_0041E168) + (unsigned int)D_L00_00262570))->flag)
            color = mode ? 0x802080 : 0x802020;
        else
            color = 0x202080;
        particle = func_002C2210(origin, 50, color | 0x7F000000, size * 0.1f, size, 0, direction, velocity, 1, D_L00_001B1484 * 1.44f);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 112;
        particle = func_002C2210(origin, 50, 0x7F7F7F7F, size * 0.07f, size * 0.7f, 1, -direction, velocity, 1, D_L00_001B1484 * 1.44f);
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 112;
    } while (--count);
}
