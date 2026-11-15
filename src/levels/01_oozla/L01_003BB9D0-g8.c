#include "common.h"

extern int func_001163B0(void);

extern int func_002A7820(int, int);

extern void func_002A7750(void *, int, int);

extern void func_L01_003BFDC8(void *, int, int, int);

extern void func_00282978(void *);

extern void func_002AB8C0(void *, void *);

extern void func_002B0990(void *, void *, int, int, float);

/* Small data reached through $gp: these are only one instruction at -G8. */
extern unsigned short D_L01_001AFED4 __attribute__((sda));

extern unsigned short D_L01_001AFED8 __attribute__((sda));

extern unsigned short D_L01_001AFEDC __attribute__((sda));

extern float D_L01_001AFEFC __attribute__((sda));

typedef struct L01_003C0760_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C0760_OWNED;

typedef struct L01_003C0760_OBJ {
    char pad0[0x68];
    L01_003C0760_OWNED *f68;
} L01_003C0760_OBJ;

/* Starts one of the Swamp Monster II attacks with a random blend time, then sets its state and timing value. */
void func_L01_003C0760(L01_003C0760_OBJ *moby)
{
    L01_003C0760_OBJ *obj = moby;
    L01_003C0760_OWNED *vars = obj->f68;
    int blendFrames = RandomIntRange(7, 12);

    SetMobyAnimationAndSpeed(obj, 8, 0, blendFrames);
    SetMobyState(obj, 3, 3);
    vars->f2DC = D_L01_001AFED4;
}

typedef struct L01_003C07C8_OWNED {
    char pad0[0x2DA];
    unsigned short f2DA;
} L01_003C07C8_OWNED;

typedef struct L01_003C07C8_OBJ {
    char pad0[0x68];
    L01_003C07C8_OWNED *f68;
} L01_003C07C8_OBJ;

/* Starts another Swamp Monster II attack with a random blend time, then sets its state and timing value. */
void func_L01_003C07C8(L01_003C07C8_OBJ *moby)
{
    L01_003C07C8_OBJ *obj = moby;
    L01_003C07C8_OWNED *vars = obj->f68;
    int blendFrames = RandomIntRange(9, 11);

    SetMobyAnimationAndSpeed(obj, 13, 0, blendFrames);
    SetMobyState(obj, 2, 3);
    vars->f2DA = D_L01_001AFED8;
}

typedef struct L01_003C0830_OWNED {
    char pad0[0x2DE];
    unsigned short f2DE;
} L01_003C0830_OWNED;

typedef struct L01_003C0830_OBJ {
    char pad0[0x68];
    L01_003C0830_OWNED *f68;
    char pad1[0x9C - 0x6C];
    int f9C;
} L01_003C0830_OBJ;

/* Starts the Swamp Monster II grab attack: picks a random blend time, sets the attack flags and the timing value. */
void func_L01_003C0830(L01_003C0830_OBJ *moby)
{
    L01_003C0830_OBJ *obj = moby;
    L01_003C0830_OWNED *vars = obj->f68;
    int blendFrames = RandomIntRange(7, 11);

    SetMobyAnimationAndSpeed(obj, 14, 0, blendFrames);
    SetMobyState(obj, 4, 3);
    obj->f9C = obj->f9C | 0x30;
    vars->f2DE = D_L01_001AFEDC;
}

typedef struct L01_003C06E8_OWNED {
    char pad0[0x2DC];
    unsigned short f2DC;
} L01_003C06E8_OWNED;

typedef struct L01_003C06E8_OBJ {
    char pad0[0x68];
    L01_003C06E8_OWNED *f68;
} L01_003C06E8_OBJ;

/* Starts a Swamp Monster II claw attack, choosing one of two animations at random. */
void func_L01_003C06E8(L01_003C06E8_OBJ *moby)
{
    L01_003C06E8_OBJ *obj = moby;
    L01_003C06E8_OWNED *vars = obj->f68;
    int animIndex = (Rand() & 1) + 6;
    int blendFrames = RandomIntRange(10, 15);

    SetMobyAnimationAndSpeed(obj, animIndex, 0, blendFrames);
    SetMobyState(obj, 1, 3);
    vars->f2DC = D_L01_001AFED4;
}

typedef struct L01_003C0140_OWNED {
    char pad0[0x68];
    void *f68;
} L01_003C0140_OWNED;

typedef struct L01_003C0140_OBJ {
    char pad0[0x68];
    L01_003C0140_OWNED *f68;
    char pad1[0x96 - 0x6C];
    unsigned short f96;
} L01_003C0140_OBJ;

/* Runs the Swamp Monster II's per-frame timers and counts up how long it has been alive. */
void func_L01_003C0140(L01_003C0140_OBJ *moby)
{
    L01_003C0140_OBJ *obj = moby;
    L01_003C0140_OWNED *vars = obj->f68;

    UpdateColorFade(moby, (char *)vars + 0x50);
    if (obj->f96 <= 0xFFFE) {
        obj->f96 = obj->f96 + 1;
    }
    FastDecTimer((char *)vars + 0x2DE);
    FastDecTimer((char *)vars + 0x2DA);
    FastDecTimer((char *)vars + 0x2DC);
    SetValueAndStartSmoothChange(obj, (char *)vars + 0x220, 10, 1, D_L01_001AFEFC);
}

/* Oozla debris update. */
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern float D_L01_001AFE30 __attribute__((sda));
extern char D_L01_001BF920[];

/* Updates a falling debris piece. It drifts, tilts, bounces off walls, fades out near the end of its life and is then removed. */
void func_L01_003BCEC8(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float savedHeight, driftScale, tilt;

    qcopy(pos, moby + 0x10);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        MarkMobySpawned(moby);
        return;
    case 1:
        if (FastFloatHelperD(vars + 0x30)) {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(vars + 0x30) = FloatToInt(10.0f);
            *(unsigned short *)(moby + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (FastFloatHelperD(vars + 0x30)) {
            MarkMobySpawned(moby);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(moby + 0x23) = FloatToInt((float)*(int *)(vars + 0x30) * 12.8f);
        break;
    }
    *(float *)(vars + 0x40) = FastAddRotations(*(float *)(vars + 0x40), 0.034906592f);
    *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8),
                                           *(float *)(vars + 0x18) * FastSinOrCosB(*(float *)(vars + 0x40)));
    *(float *)(moby + 0xF0) += (*(float *)(vars + 0x44) - *(float *)(moby + 0xF0)) * 0.02f;
    if (*(unsigned char *)(moby + 0x20) != 2) {
        tilt = FastSinOrCosA(*(float *)(vars + 0x40)) * 0.17453295f;
        driftScale = D_L01_001AFE30;
        *(float *)(moby + 0xF4) = tilt;
        savedHeight = *(float *)(vars + 8);
        *(float *)(vars + 8) = 0.0f;
        FastVecScale(vars, vars, driftScale);
        *(float *)(vars + 8) = savedHeight;
        FastVecAdd(moby + 0x10, moby + 0x10, vars);
        *(float *)(vars + 8) -= *(float *)(vars + 0x38);
        if (*(float *)(vars + 8) < *(float *)(vars + 0x3C))
            *(float *)(vars + 8) = *(float *)(vars + 0x3C);
    } else {
        *(float *)(moby + 0xF4) += (0.17453295f - *(float *)(moby + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (CollLine(pos, moby + 0x10, 2, moby, 0)) {
        qcopy(moby + 0x10, gCollLineHitPoint);
        /* qzero(state + 8): retail passes a misaligned pointer here (original bug; sq ignores the low four address bits). Allowed by owner ruling (2026-11-09). */
        qzero(vars + 8);
        *(int *)(vars + 0x38) = 0;
        qzero(vars + 0x10);
        if (*(unsigned char *)(moby + 0x20) != 2) {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(vars + 0x30) = FloatToInt(10.0f);
            *(unsigned short *)(moby + 0x34) |= 0x2000;
        }
    }
}
