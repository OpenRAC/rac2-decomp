#include "common.h"

extern void func_0029FCC0(void *, int, void *);
extern int func_00282948(char *);
extern char D_00189E20[];
extern void func_002FDF40(void *, void *, int, int, float, float, float, float);
extern int func_002FE5A0(void *, void *, void *, void *, void *, char **, int *, float);
extern int func_00300540(int);
extern void func_002FE8D8(void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_L00_002D3F30(int, int);
extern int func_002B0CE0(int, int, int);
extern void func_L00_002AF568(void);
extern void func_L00_002AF7D0(void);
extern void func_002E5CF8(int, int, void *);
extern char *func_L00_003DE088(void *, void *);
extern void ref_L00_003B7D48_00(void (*)(void *), void *);
extern void func_L00_003B8158(void *);
typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;

extern OBJ2 *D_L00_001AFBC0 __attribute__((sda));
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001A8F08 MACRO_ADDR;
extern int D_L00_001A8FF4 MACRO_ADDR;
extern int D_00138324 NOT_SDA;

/* Updates the Spiderbot Glove pickup. When the player presses the button near it and nothing blocks the way, the glove is picked up and the player's pickup action starts. */
void func_L00_003B7D48(char *m) {
    float pos[4], sweep_storage[4], normal[4];
    float *sweep;
    char *hit;
    int aux;
    char *d = *(char **)(m + 0x68);
    int result, state, ready;
    float height;

    {
        char *g = gHeroState;

        if (*(int *)(g + 0x1244) == 3)
            D_L00_001AFBC0 = 0;
        TransformMobyJointToWorld(m, 0, pos);
        *(int *)(d + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(g + 0x2294) == 29) ? 11.0f : 4.5f;
        CalculateAimedLaunchVelocity(sweep, pos, 0, 0, 1.6f, height, 0.13333334028720856f, 0.003055555745959282f);
    }
    *(int *)(d + 0x24) = TraceProjectileToImpact(pos, sweep, d, d + 0x10, m, &hit, &aux, 0.003055555745959282f);
    result = GetWeaponGroup(aux);
    if (D_L00_001A8F00 || D_L00_001A8F08 != -2)
        *(int *)(d + 0x2C) = 1;
    if (D_L00_001A8FF4 && *(float *)(d + 8) < 462.42999267578125f)
        *(int *)(d + 0x2C) = 1;
    if (result || !*(int *)(d + 0x24) || !*(int *)(d + 0x28))
        goto blocked;
    {
        char *g = gHeroState;

        state = *(int *)(g + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(g + 0x33C) && (*(short *)(*(char **)(g + 0x33C) + 0xAA) == 0x330 /* Taxi */ ||
                                      *(short *)(*(char **)(g + 0x33C) + 0xAA) == 0xB21 /* moby class 2849 */))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 /* moby class 2849 */ || *(short *)(hit + 0xAA) == 0xB5B /* moby class 2907 */))
            goto blocked;
    }
    GetObjectFacingDirection(d, normal);
    if (!(FastVecDot(d + 0x10, normal) < 0.75f))
        goto timer;
blocked:
    *(int *)(d + 0x2C) = 1;
timer:
    {
        char *g = gHeroState;

        ready = 1;
        if (*(int *)(g + 0x2294) == 29) {
            if (!FastFloatHelperD(g + 0x2534))
                ready = 0;
        } else
            *(int *)(g + 0x2534) = 40;
    }
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        D_L00_001AFBC0 = (OBJ2 *)m;
        *(unsigned char *)(m + 0x20) = 1;
        *(int *)(d + 0x28) = 1;
        *(int *)(d + 0x24) = 0;
        /* falls through */
    case 1: {
        char *g = gHeroState;

        if ((D_00138324 & *(int *)(g + 0x1230)) && !*(unsigned char *)(g + 0x22BC) &&
            !*(int *)(d + 0x2C) && ready) {
            if (SpendWeaponAmmo(-1, 1)) {
                *(short *)(g + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                *(short *)(g + 0x1D2) = 0;
                start_equipped_item_animation();
                *(unsigned char *)(m + 0x20) = 2;
                *(int *)(d + 0x20) = 12;
                *(int *)(d + 0x28) = 0;
            } else
                PlayMobySound(0, 0, m);
        }
        break;
    }
    case 2:
        if (FastFloatHelperD(d + 0x20)) {
            char *p = SpawnSpiderBotMoby(pos, sweep);

            if (p)
                *(char **)(p + 0xB8) = m;
            PlayMobySound(1, 0, m);
            cancel_hero_item_animation();
            *(unsigned char *)(m + 0x20) = 3;
            *(int *)(d + 0x20) = 5;
        }
        break;
    case 3:
        if (FastFloatHelperD(d + 0x20))
            *(unsigned char *)(m + 0x20) = 1;
        break;
    }
    ref_L00_003B7D48_00(UpdateHelperObjectHitTest, m);
}
