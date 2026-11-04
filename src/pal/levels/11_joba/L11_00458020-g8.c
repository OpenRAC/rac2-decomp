/* func_PAL_L11_00458020, the PAL copy of func_L11_00452450: the same C, where 0.0055555557f
   becomes 0.008f; 0.004444444552063942f becomes 0.0064000003f; 0.13333334028720856f becomes
   0.16000001f; 0.0011635529808700085f becomes 0.0016755164f; 0.10471977293491364f becomes
   0.12566373f; func_L11_00452DF8 becomes func_PAL_L11_004589C8; func_002B0ED8 becomes
   func_PAL_002B1A50; 0.8377582f becomes 1.0053098f. */
#include "common.h"

extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern void func_00282CC0(void *, void *, void *);

typedef struct JobObject JobObject;

typedef struct {
    u8 pad00[0x18];
    float *params;          /* +0x18, points at paramBlock */
    u8 pad1C[4];
    float health;           /* +0x20 */
    u8 pad24[4];
    u8 f28;
    u8 f29;
    u8 pad2A[4];
    u8 f2E;
    u8 pad2F;
    float f30;
    u8 f34;
    u8 pad35[0x48 - 0x35];
    u8 f48;
    u8 pad49;
    u8 f4A;
    u8 pad4B[5];
    u8 hitInfo[0x10];       /* +0x50 */
    u8 f60;
    u8 pad61[8];
    u8 f69;
    u8 pad6A[0x80 - 0x6A];
    float f80;
    float f84;
    u8 pad88[4];
    float f8C;
    u8 pad90[8];
    s32 f98;
    u8 pad9C[0xFC - 0x9C];
    float fFC;
    float paramBlock[5];    /* +0x100 */
    u8 pad114[0x12C - 0x114];
    float f12C;
    float f130;
    float f134;
    u8 pad138[0x1D4 - 0x138];
    float f1D4;
    u8 pad1D8[0x1E6 - 0x1D8];
    u8 f1E6;
    u8 pad1E7;
    u8 f1E8;
    u8 f1E9;
    u8 pad1EA[0x1FC - 0x1EA];
    u16 spawnTimer;         /* +0x1FC */
    u8 pad1FE[0x2F0 - 0x1FE];
    float basis[12];        /* +0x2F0 */
    float anchor[4];        /* +0x320 */
    u8 pad330[0x354 - 0x330];
    JobObject *turret;      /* +0x354 */
    float turnRate;         /* +0x358 */
    u8 pad35C[0x364 - 0x35C];
    s16 fireTimer;          /* +0x364 */
    u8 pad366[0x36E - 0x366];
    s16 f36E;
} JobState;

struct JobObject {
    u8 pad00[0x10];
    float position[4];      /* +0x10 */
    u8 stage;               /* +0x20 */
    u8 pad21[0x31 - 0x21];
    u8 f31;
    u8 pad32[2];
    u16 flags;              /* +0x34 */
    u8 pad36[0x68 - 0x36];
    JobState *state;        /* +0x68 */
    u8 pad6C[3];
    u8 f6F;
    u8 pad70[0x95 - 0x70];
    u8 f95;
    u8 pad96[0xB8 - 0x96];
    s32 fB8;
    u8 padBC[4];
    float rotation[12];     /* +0xC0 */
};

extern s32 func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void *func_002A9640(void *, s32, s32);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void func_00283698(void *, void *);
extern void func_002AFFD8(void *, void *, s32);
extern s32 func_L11_004461C0(s32, void *);
extern void func_002A7750(void *, s32, s32);
extern char D_L11_001BA8C0[];
extern s32 D_001A8FF4;

extern void func_002B60B0(char *, float, float, float, float);
extern void func_PAL_L11_004589C8(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_0029FC20(void *, int, void *);
extern void func_00282C88(void *);
extern void func_002830C0(void *, void *, void *);
extern s32 func_002B3BA8(void *, s32, s32, s32, float, float);

/* Per-frame update of an L11 object: on its first frame it seeds its state block (a random-sign
   turn rate of 15 to 40 degrees, the 0.5/0.4 constant set) and runs its setup; then it sets the
   proximity flag, rebuilds the frame at state + 0x290 and, from stage 3 on, runs its hit, death
   and tracking checks. */
void func_PAL_L11_00458020(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *aim;
    char *hit;
    char *source;
    float matrix[16];
    float turnRate;
    s16 kind;

    if (*(u8 *)(object + 0x20) == 0) {
        *(char **)(state + 0x18) = state + 0x100;
        turnRate = func_002A7878(15.0f, 40.0f) * 0.017453294f;
        if (func_002A77E0(2) != 0)
            turnRate = -turnRate;
        *(f32 *)(state + 0x2C8) = turnRate;
        if (func_002A77E0(2) == 1)
            *(u16 *)(object + 0x34) |= 0x8000;
        *(u8 *)(state + 0x48) = func_00283CF0(15.0f);
        *(u8 *)(state + 0x4A) = func_00283CF0(12.0f);
        *(u8 *)(state + 0x60) = 0xB;
        *(s32 *)(state + 0x98) = 4;
        *(f32 *)(state + 0x100) = 0.8f;
        *(f32 *)(state + 0x104) = *(f32 *)(state + 0x84) = *(f32 *)(state + 0x80) = 0.5f;
        *(f32 *)(state + 0x10C) = *(f32 *)(state + 0x108) = *(f32 *)(state + 0x8C) = 0.4f;
        *(f32 *)(state + 0x110) = 1.5707965f;
        *(f32 *)(state + 0x130) = 0.52359885f;
        *(f32 *)(state + 0x12C) = 0.008f;
        *(f32 *)(state + 0x134) = 2.8f;
        func_002B60B0(object, 0.0064000003f, 0.16000001f,
                      0.0016755164f, 0.12566373f);
        *(u8 *)(state + 0x28) = 3;
        func_PAL_L11_004589C8(object);
    }
    if (*(s16 *)(state + 0x2D8) == 0 && *(u8 *)(object + 0x20) != 0xC && D_001A8FF4 == 0) {
        *(u16 *)(object + 0x34) |= 0x400;
        if (*(u8 *)(object + 0x31) != 0 && func_00282E48(object + 0x10, D_L11_001BA8C0) < 24.0f) {
            func_002A93B0(object);
            *(u8 *)(object + 0x6F) = 0x16;
        }
    } else {
        *(u16 *)(object + 0x34) &= 0xFBFF;
    }
    aim = state + 0x290;
    func_0029FCC0(object, 1, state + 0x270);
    func_0029FCC0(object, 2, state + 0x280);
    func_0029FC20(object, 3, matrix);
    func_00282C88(aim);
    *(s32 *)(state + 0x298) = 0;
    *(f32 *)(state + 0x290) = 0.25f;
    func_002830C0(aim, aim, matrix);
    func_00282CC0(aim, aim, matrix + 12);
    if (*(u8 *)(object + 0x20) >= 3) {
        hit = (char *)func_002A9640(object, 0x10000, 1);
        if (hit != 0) {
            source = *(char **)(hit + 0x20);
            if (source != 0 && *(u8 *)(object + 0x31) == 0) {
                kind = *(s16 *)(source + 0xAA);
                if (kind == 0xA03 || kind == 0xB89)
                    *(s32 *)(hit + 0x2C) = 0;
            }
        }
        if (func_PAL_002B1A50(object, state + 0x50, 0) == 5) {
            *(s32 *)(state + 0xE0) = 0;
            *(f32 *)(state + 0xE4) = 1.0053098f;
        }
        if (*(s16 *)(state + 0x2D8) != 0) {
            char *pos;
            func_00283698(state + 0x230, object + 0xC0);
            pos = object + 0x10;
            func_002AFFD8(pos, state + 0x260, 0);
            if (func_L11_004461C0(*(s32 *)(object + 0xB8), pos) == 0) {
                *(s32 *)(state + 0x20) = 0;
                func_002A7750(object, 0xC, 4);
            }
        }
        if (*(u8 *)(object + 0x20) >= 2 && *(u8 *)(state + 0x2E) == 2)
            func_PAL_L11_004589C8(object);
        *(s16 *)(state + 0x2D0) = func_002B3BA8(object, *(s32 *)(state + 0x2CC), 0, 0, 100.0f, 100.0f);
        *(s32 *)(state + 0x2C4) = *(s32 *)(state + 0x220);
    }
}
