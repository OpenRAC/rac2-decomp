#include "common.h"

extern int func_002B38B8(char *);
extern int func_002B3868(char *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_0032DA58(char *, void *, void *, float);
extern void func_002A7750(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern char *func_00273730(char *, int, int, int, void *, void *, void *, int, float, float);
extern void func_0029F338(char *);
extern void func_00273B70(char *);
extern int func_002A7820(int, int);

/* The spawn bounds: minimum vector at +0x00, maximum vector at +0x10. An incomplete `sda` array
   gives retail's mix: element 0 is a one-instruction load (GP in a call's delay slot, absolute
   elsewhere), while every other element is a `sym+offset` address, which cc1 counts as two
   instructions, keeps out of delay slots and the assembler expands absolute. */
extern float D_L07_001B0C00[] __attribute__((sda));
/* The offset vector, addressed through $gp. */
extern float D_L07_001B0C20[] SDATA(D_L07_001B0C20);
/* Two {minimum, maximum} pairs for the child's two random parameters; retail reads +0x08 $gp
   relative and the others absolute. */
extern float D_L07_001B0C30[] __attribute__((sda));
extern float D_L07_001B0C30_gp[] SDATA(D_L07_001B0C30);

/* A four-state burst: state 1 passes the rotated, offset position to func_0032DA58, state 2
   spawns nine children that run this function in state 3, where each counts down a random
   lifetime. */
/* Per-frame update for moby class 3387: a burst effect that spawns nine short-lived pieces and
   then goes away. */
void func_L07_003EE3B0(char *moby)
{
    float velocity[4] __attribute__((aligned(16)));
    int i;
    float childParamA, childParamB;
    char *child;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (IsThirdPendingFlagSet(moby)) {
            matrix_mul_vec3(velocity, D_L07_001B0C20, moby + 0xC0);
            FastVecAdd(velocity, velocity, moby + 0x10);
            SpawnBlastEffectMoby(moby, velocity, moby + 0xD0, 0.0f);
            SetMobyState(moby, 2, -1);
        }
        break;
    case 2:
        if (SetFirstPendingFlag(moby))
            PlayMobySound(0, 0, moby);
        for (i = 0; i < 9; i++) {
            velocity[0] = RandomFloatRange(D_L07_001B0C00[0], D_L07_001B0C00[4]) * 0.016666667f;
            velocity[1] = RandomFloatRange(D_L07_001B0C00[1], D_L07_001B0C00[5]) * 0.016666667f;
            velocity[2] = RandomFloatRange(D_L07_001B0C00[2], D_L07_001B0C00[6]) * 0.016666667f;
            matrix_mul_vec3(velocity, velocity, moby + 0xC0);
            childParamA = RandomSignedFloatRange(D_L07_001B0C30[0], D_L07_001B0C30[1]);
            childParamB = RandomFloatRange(D_L07_001B0C30_gp[2], D_L07_001B0C30[3]);
            child = CreateCameraMoby(moby, 2, *(short *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0, velocity, 255, childParamA, childParamB);
            if (child) {
                *(void (**)(char *))(child + 0x64) = UpdateBurstDebrisMoby;
                *(unsigned short *)(child + 0x34) |= 0x2000;
                SetMobyState(child, 3, -1);
            }
        }
        MarkMobySpawned(moby);
        break;
    case 3:
        if (SetFirstPendingFlag(moby))
            *(unsigned short *)(moby + 0x96) = RandomIntRange(0, 60);
        UpdateCameraMoby(moby);
        if (*(unsigned short *)(moby + 0x96) == 0 || --*(unsigned short *)(moby + 0x96) == 0) {
            if (*(unsigned char *)(moby + 0x23) >= 4)
                *(unsigned char *)(moby + 0x23) -= 4;
            else
                MarkMobySpawned(moby);
        }
        break;
    }
}
