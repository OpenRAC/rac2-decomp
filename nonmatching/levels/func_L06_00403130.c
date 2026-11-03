/* GPT-6.1 Sol (high), task v1094. Near miss under the current default
 * -O2 -G0 -ffunction-sections: 1488/1504 bytes, 0/6 USA v1.01 places.
 * The entry guards and three vector copies now reproduce retail apart from
 * relocations, initialization scheduling and the owner-state branch slot.
 * SDATA views preserve unknown speed-table extents and the full previous-position
 * vector. The measured hero field layout avoids cumulative byte-offset reuse;
 * scalar sda declarations give the macro address model without retaining bases.
 * Remaining differences: UV stream allocation, missing reload after paired UV
 * stores, first scale-call latency padding, initialization and drift scheduling.
 * Explicit independent pointers/snapshots produce the displacement reloads but
 * retain UV bases across loops and alter loop control (1496-1512 bytes).
 * Declared volatile UV storage with snapshots still changes store/branch slots;
 * that trial is not retained. Next: recover the original UV aggregate/alias model.
 * Required declarations are included below. This file is never linked.
 */
#include "common.h"
typedef int AreaQuadword __attribute__((mode(TI)));
typedef union { AreaQuadword bits; float f[4]; } AreaVector;
typedef void (*DrawCallback_r002E6CF0)(void *);
typedef void (*DrawCallback_r002E6DB8)(void *);
extern void func_L00_002E6CF0(DrawCallback_r002E6CF0, void *);
extern void func_L00_002E6DB8(DrawCallback_r002E6DB8, void *);
extern void func_L06_00402570(void *);
extern int func_002ACBC8(void *, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int D_L06_001C9DC0;
extern int D_001A79F0 __attribute__((sda));
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x16e];
    short waterState;
    char pad200[0x2094];
    int action;
    int pad2298;
    int animation;
} WaterHero;
extern WaterHero D_00189E20;

extern int D_L06_001A9010 __attribute__((sda));
extern int D_L06_001A8A48 __attribute__((sda));
extern float D_L06_001B3284 __attribute__((sda));
extern float D_L06_001B3280 __attribute__((sda));
extern AreaVector D_L06_001B9A70[];
extern AreaVector D_L06_001B3290 __attribute__((sda));
extern AreaVector D_L06_001B32A0 __attribute__((sda));
extern AreaVector D_L06_001B32B0 __attribute__((sda));
extern float D_L06_001B3270[][2] __attribute__((sda));
extern float D_L06_001B3274[][2] __attribute__((sda));
extern AreaVector D_L06_001B3260;
#define D_L06_001B3260 D_L06_001B3260
extern char D_L06_001B9840[];
extern float D_L06_001B0060[] SDATA(D_L06_001B0060);
extern float D_L06_001B0070[][2] SDATA(D_L06_001B0070);
extern float D_L06_001B0074[][2] __attribute__((sda));
extern int D_001A79F0;
#define levelIndexGP D_001A79F0
extern float D_L06_001B3284;
#define baselineGP D_L06_001B3284
extern float D_001A7928 __attribute__((sda));
extern int D_L06_001B2348 __attribute__((sda));

void func_L06_00403130(unsigned char *owner)
{
    AreaVector movement, scaled;
    char *state = *(char **)(owner + 0x68);
    float range, fraction;
    int i;
    int level;

    if (D_L06_001C9DC0 != *(int *)(state + 0x38))
        return;
    level = D_001A79F0;
    if (level == 13 && D_00189E20.position[2] < 88.0f &&
        D_00189E20.action != 116)
        return;
    if (level == 11 && D_L06_001A9010 != 0)
        return;
    D_L06_001B3284 = *(float *)(state + 0x14);
    if (owner[0x20] == 0) {
        owner[0x20] = 1;
        owner[0x30] = 0xFF;
        qcopy(&D_L06_001B3290, &D_L06_001B9A70[0]);
        qcopy(&D_L06_001B32A0, &D_L06_001B9A70[1]);
        qcopy(&D_L06_001B32B0, &D_L06_001B9A70[2]);
        for (i = 1; i >= 0; i--) {
            D_L06_001B3270[1 - i][0] = 0.0f;
            D_L06_001B3274[1 - i][0] = 0.0f;
        }
        qcopy(&D_L06_001B3260, D_L06_001B9840);
        baselineGP = *(float *)(state + 0x14);
        return;
    }
    if (func_002ACBC8(&D_00189E20.position, *(int *)(state + 0x30))) {
        D_00189E20.waterState = 0;
        return;
    }
    if (func_002ACBC8(&D_00189E20.position, *(int *)(state + 0x34)) &&
        levelIndexGP != 13 && *(int *)(state + 0x38) == 0) {
        float angle = *(float *)(D_L06_001B9840 + 0x18);
        if (angle > 0.031f || angle < -1.62f ||
            (unsigned int)(D_00189E20.animation - 17) < 2) {
            D_00189E20.waterState = 0;
            return;
        }
    }
    if (func_002ACBC8(&D_00189E20.position, *(int *)(state + 0x34))) {
        D_00189E20.waterState = 0;
        return;
    }
    range = *(float *)(state + 0x18);
    if (D_00189E20.action == 28 || D_L06_001A8A48 != 0) {
        if (range > 32.0f)
            range = 32.0f;
    }
    D_00189E20.waterState = 2;
    func_00282CF0(&movement, D_L06_001B9840, &D_L06_001B3260);
    qcopy(&D_L06_001B3260, D_L06_001B9840);
    if (!(*(float *)(D_L06_001B9840 + 8) > *(float *)(state + 0x20)))
        return;
    for (i = 0; i < 2; i++) {
        func_00282D30(&scaled, &movement, (D_L06_001B0060[i] + D_L06_001B0060[i]) / (range * 5.0f));
        if (scaled.f[0] > 1.0f || scaled.f[0] < 1.0f)
            scaled.f[0] -= func_00283CE0(func_00283CF0(scaled.f[0]));
        if (scaled.f[1] > 1.0f || scaled.f[1] < 1.0f)
            scaled.f[1] -= func_00283CE0(func_00283CF0(scaled.f[1]));
        D_L06_001B3270[i][0] += scaled.f[0];
        D_L06_001B3274[i][0] += scaled.f[1];
        if (D_L06_001B3270[i][0] > 1.0f)
            D_L06_001B3270[i][0] -= 1.0f;
        if (D_L06_001B3270[i][0] < -1.0f)
            D_L06_001B3270[i][0] += 1.0f;
        if (D_L06_001B3274[i][0] > 1.0f)
            D_L06_001B3274[i][0] -= 1.0f;
        if (D_L06_001B3274[i][0] < -1.0f)
            D_L06_001B3274[i][0] += 1.0f;
    }
    fraction = func_00283CE0(D_L06_001B2348 % 360) * 0.017444444820284843f - 3.14f;
    D_L06_001B3280 = D_L06_001B3284 + func_00283198(fraction) * *(float *)(state + 0x3C);
    for (i = 0; i < 2; i++) {
        D_L06_001B3270[i][0] += D_L06_001B0070[i][0] * D_001A7928;
        if (D_L06_001B3270[i][0] > 1.0f)
            D_L06_001B3270[i][0] -= 1.0f;
        if (D_L06_001B3270[i][0] < -1.0f)
            D_L06_001B3270[i][0] += 1.0f;
        D_L06_001B3274[i][0] += D_L06_001B0074[i][0] * D_001A7928;
        if (D_L06_001B3274[i][0] > 1.0f)
            D_L06_001B3274[i][0] -= 1.0f;
        if (D_L06_001B3274[i][0] < -1.0f)
            D_L06_001B3274[i][0] += 1.0f;
    }
    if (*(int *)state < 0)
        func_L00_002E6DB8(func_L06_00402570, owner);
    else
        func_L00_002E6CF0(func_L06_00402570, owner);
}
