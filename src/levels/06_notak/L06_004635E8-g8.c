#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern char *func_L00_0033E220(void *, void *, unsigned int, int, int, int, int, float, float, int);
extern void func_002A7750(char *, int, int);
extern int func_0035CBA0(char *, int, int);
extern void func_00350388(char *);
extern void func_L00_0032A258(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_L01_0031A278(char *, void *, float, float, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void func_00283098(void *, void *, void *);
extern void func_L00_003263D0(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
extern float D_L06_001B1CB8 __attribute__((sda));
extern float D_L06_001B1CB0 __attribute__((sda));
extern float D_L06_001B1CC0 __attribute__((sda));
extern float D_L06_001B1CE0 __attribute__((sda));
extern float D_L06_001B1CE4, D_L06_001B1CE8;
/* Updates a Notak effect object: it waits for a trigger, then sprays sparks and particles and removes itself. */
void func_L06_004635E8(char *moby) {
    float pos[4], vel[4];
    char *vars = *(char **)(moby + 0x68);
    int i;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        float scale;
        *(u128 *)pos = 0;
        pos[2] = 3.75f;
        scale = *(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24);
        pos[2] *= scale;
        SpawnObjectFollowingEffect(pos, moby, 0x300033FF, -1, 1, -1, 0, scale * 525000.0f, 0.75f, -1);
        SpawnObjectFollowingEffect(pos, moby, 0x280033FF, -1, 0, -1, 0, scale * 525000.0f, 0.75f, -1);
        *(int *)(moby + 0x78) = -16192;
        SetMobyState(moby, 1, -1);
        /* fall through */
    }
    case 1:
        if (func_0035CBA0(moby, 0x4010000, 0) && *(int *)vars == 0) SetMobyState(moby, 2, -1);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        ExplodeObjectIntoPieces(moby, &D_L06_001B1CC0, &D_L06_001B1CB8, &D_L06_001B1CB0, 0xFFFF, 0, -1, 6, 0xFF, 0xFF, 0);
        ComputeMobyLocalPoint(moby, pos, D_L06_001B1CE0, D_L06_001B1CE4, D_L06_001B1CE8);
        SpawnExplosion(pos, 0, 5, 5, 5, 20, 5, 0, 1, 1, 1, 0, 1.0f, 20.0f);
        for (i = 0; i < 4; i++) {
            vel[0] = (i / 2 * 2 - 1) * 0.05000000447f;
            vel[1] = (i % 2 * 2 - 1) * 0.05000000447f;
            vel[2] = 0.1166666746f;
            matrix_mul_vec3(vel, vel, moby + 0xC0);
            SpawnTintedEffects(moby, pos, 3, 0.2f, 1, vel, 5.0f, 0x7F40FFFF, 1.45f, 2.2f, 0);
        }
        func_00350388(moby);
        break;
    }
}
