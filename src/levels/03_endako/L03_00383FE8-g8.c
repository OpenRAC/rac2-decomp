#include "common.h"
extern void func_002A7750(void *, int, int);
extern char *func_002A9640(void *, int, int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float), func_00283198(float);
extern void func_00302470(void *, void *, void *, int, int, int);
extern int D_L03_001AEC30 __attribute__((sda));
extern char D_L03_001AEC10[8] __attribute__((sda)), D_L03_001AEC08[8] __attribute__((sda)), D_L03_001AEC00[8] __attribute__((sda));
extern void func_L00_0032A258(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_L02_002DCEA0(int, float);
extern float D_L03_001B2460;
extern char *func_0029EFD0(int);
extern char D_L03_001B9980[];
extern int D_L03_001A8FB4, D_L03_001A8FB0;
/* Updates a hit-reactive object. It waits to be struck, bursts into sparks, and when the Dynamo hits it, it drops a pickup item and shows a message. */
void func_L03_00383FE8(char *moby)
{
    float pos[4], vel[4];
    int i;
    char *spawned;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        SetMobyState(moby, 1, -1);
        break;
    case 1: {
        char *hit;
        hit = FindOwnedEffectSlot(moby, 0x4010000, 0);
        if (hit) {
            hit = *(char **)(hit + 0x20);
            if (hit && *(short *)(hit + 0xAA) == 0x825 /* Dynamo */)
                SetMobyState(moby, 3, -1);
            else SetMobyState(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    }
    case 2: {
        char *position = moby + 0x10;
        if (!D_L03_001AEC30) {
            D_L03_001AEC30 = 1;
            qcopy(pos, position);
            pos[2] += 0.5f;
            i = 9;
            do {
                float angle, speed;
                i--;
                angle = RandomAngle();
                speed = RandomFloatRange(0, 1) * (1.0f/60.0f);
                vel[0] = FastSinOrCosA(angle) * speed;
                vel[1] = FastSinOrCosB(angle) * speed;
                vel[2] = 0;
                vel[2] = RandomFloatRange(5, 10) * (1.0f/60.0f);
                SpawnBoltPickup(moby, pos, vel, 0, 100, 0);
            } while (i >= 0);
        }
        ExplodeObjectIntoPieces(moby, D_L03_001AEC10, D_L03_001AEC08, D_L03_001AEC00, 65535, 0, -1, 6, 65535, 255, 0);
        SpawnExplosion(position, 0, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 0.5f, 20);
        MarkMobySpawned(moby);
        break;
    }
    case 3:
        if (SetFirstPendingFlag(moby)) StartTimedCountdown(1, 15);
        if (D_L03_001B2460 >= 1) {
            spawned = CreateMoby(0x1335);
            if (spawned) {
                qcopy(spawned + 0x10, D_L03_001B9980);
                *(unsigned char *)(spawned + 0x30) = 255;
            }
            D_L03_001A8FB4 = 2;
            D_L03_001A8FB0 = 15;
            SetMobyState(moby, 1, -1);
        } else {
            unsigned int count = *(unsigned short *)(moby + 0x96);
            unsigned int oldCount = count++;
            *(unsigned short *)(moby + 0x96) = count;
            if (oldCount >= 61) SetMobyState(moby, 1, -1);
        }
        break;
    }
}
