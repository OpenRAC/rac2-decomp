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

/* Creates a lightning arc object for an owner and gives it one of four reusable sets of points. */
char *func_L00_00412FF8(char *owner)
{
    char *moby = CreateMoby(0x1195 /* moby class 4501 */);
    char *vars;
    int counter;
    float offset[4];

    if (moby != 0) {
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        vars = *(char **)(moby + 0x68);
        *(unsigned short *)(vars + 0x1E) = D_L00_001B13DC;
        *(int *)(vars + 0x18) = -1;
        euler_rotation_basis(moby + 0xC0, D_00189EB0);
        counter = D_L00_001B1378;
        *(char **)(vars + 0) = D_L00_0025A1A0 + counter * 0xA0;
        *(char **)(vars + 4) = D_L00_0025A420 + counter * 0x140;
        if ((unsigned int)counter >= 4)
            D_L00_001B1378 = 0;
        D_L00_001B1378 = (D_L00_001B1378 + 1) % 4;
        *(int *)(vars + 0x24) = D_L00_001B137C;
        *(char **)(vars + 0x20) = owner;
        FastVecScale(offset, *(char **)(D_00189EB0 + 0x2200) + 0xE0, 0.75f);
        FastVecAdd(moby + 0x10, D_00189EB0 - 0x10, offset);
        ResetWaveLineEffect(moby);
    }
    return moby;
}

/* Emits three effect particles at the object, then four spawns along its velocity at rising heights. */
void func_L00_004173B0(char *moby)
{
    Vec up, velocity, pos, pos2, pos3, pos4;
    char *vars = *(char **)(moby + 0x68);
    int i;
    float angle, random, life, speed, spread, frame;

    ComputeViewDirection(moby + 0x10, &up, 1);
    if (*(int *)(vars + 4) != 0)
        return;
    frame = 0.016666668f;
    for (i = 0; i < 3; i++) {
        angle = RandomFloatRange(-0.9599311948f, -1.3962635994f);
        random = RandomAngle();
        speed = RandomFloatRange(0.0f, 0.5f);
        spread = 0.3f;
        frame = 0.016666668f;
        speed *= frame;
        BuildSphericalOffset(&velocity, speed, random, angle);
        life = RandomFloatRange(0.65f, 0.85f) * 210000.0f;
        pos.f[0] = *(float *)(moby + 0x10) + RandomSignedFloatRange(0.0f, spread);
        pos.f[1] = *(float *)(moby + 0x14) + RandomSignedFloatRange(0.0f, spread);
        pos.f[2] = *(float *)(moby + 0x18) + RandomSignedFloatRange(0.0f, spread);
        SpawnSpinningParticle_L00(life, &pos, &velocity, 0x4F808080, 0x08101010, RandomIntRange(35, 50), 1, 0.5f, 1, -1, 1);
    }
    ComputeViewDirection(moby + 0x10, &velocity, 1);
    vec_scale_to_length(&velocity, &velocity, 0.2f);
    qcopy_nc(&pos, moby + 0x10);
    pos.f[2] += RandomFloatRange(0.1f, 0.4f);
    SpawnObjectRelativeParticle(moby, &pos, &velocity, &D_L00_001B1418, RandomIntBelow(2));
    qcopy_nc(&pos2, moby + 0x10);
    pos2.f[2] += RandomFloatRange(0.9f, 1.2f);
    SpawnObjectRelativeParticle(moby, &pos2, &velocity, &D_L00_001B13F8, RandomIntBelow(2));
    qcopy_nc(&pos3, moby + 0x10);
    pos3.f[2] += RandomFloatRange(0.8f, 1.5f);
    SpawnObjectRelativeParticle(moby, &pos3, &velocity, &D_L00_001B1408, RandomIntBelow(2));
    qcopy_nc(&pos4, moby + 0x10);
    SpawnObjectRelativeParticle(moby, &pos4, &velocity, &D_L00_001B1428, RandomIntBelow(2));
}
