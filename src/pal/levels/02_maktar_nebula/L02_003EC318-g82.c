#include "include_asm.h"

#include "common.h"
extern char *D_L02_001B359C;
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x530];
    char *captured;
    char pad5c4[0xE90];
    unsigned short captureMode;
} Hero003E87D8;
extern char D_00189E20[];
extern char D_00188660[];
extern unsigned short D_0018CA6C NOT_SDA;
extern float D_L02_001B0B80 __attribute__((sda));
extern float D_L02_001B0B84 __attribute__((sda));
extern float D_L02_001B0B88 __attribute__((sda));
extern float D_L02_001B0B8C __attribute__((sda));
extern float D_L02_001B0B90 __attribute__((sda));
extern float D_L02_001B0B94 __attribute__((sda));
extern float D_L02_001B0BA0 __attribute__((sda));
extern float D_L02_001B0BF0[4] __attribute__((sda, aligned(16)));
extern float effectOffset003E87D8[4] SDATA(D_L02_001B0BF0);
typedef struct { char pad[0x34]; unsigned short flags; } Actor003E87D8;
extern void func_002A7750(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00282E48(void *, void *);
extern void func_L00_003294F0(void *, int);
extern void func_00282C88(void *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_002AAA00(void *, void *, int, float, float, float, float);
extern void func_PAL_L02_003ED0D8(void *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_00424F58(char *, float, float);
extern void func_L00_00424C28(void);
extern void func_L00_00424B70(float, float);
extern int func_002B3868(void *);
extern int func_PAL_L02_003ED2A0(void *);
extern void func_L02_003CADA8(void *, void *);
extern void func_L02_003D01F0(void *, void *);
extern float func_00282C48(float);
extern void func_002E59F8(int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002B38B8(void *);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_PAL_L02_003EDCE8(char *);

/* Updates a tether actor's capture, release, turning and attached effect. */
void func_PAL_L02_003ECBC8(char *actor) {
    char *state = *(char **)(actor + 0x68);
    char *target = D_L02_001B359C + *(int *)state * 0x100;
    float local[4] __attribute__((aligned(16)));
    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        *(float *)(state + 0x48) = *(float *)(actor + 0xF8);
        if (*(int *)state != -1) {
            func_002A7750(actor, 1, -1);
            if (*(short *)(D_L02_001B359C + *(int *)state * 0x100 + 0xAA) == 0x9BC) {
                char *effect = func_0029EFD0(0xA61);
                *(char **)(state + 0x54) = effect;
                if (effect) {
                    func_002B37E8(effect, actor);
                    *(unsigned short *)(*(char **)(state + 0x54) + 0x34) |= 2;
                }
            }
        } else {
            func_002A7750(actor, 4, -1);
        }
        break;
    case 1:
        if ((*(unsigned short *)(target + 0x34) & 0x1000) && ((Hero003E87D8 *)D_00189E20)->captured == target &&
            func_00282E80(target + 0x10, actor + 0x10) < D_L02_001B0B80) {
            func_L00_003294F0(target, 1);
            func_00282C88(state + 0x10);
            func_002A7750(actor, 2, -1);
            break;
        }
        break;
    case 2:
        {
            float separation;
            float turnStep, turnLimit;
            float angle = func_00283B98(func_00283248(
                *(float *)(target + 0x10) - *(float *)(actor + 0x10),
                *(float *)(target + 0x14) - *(float *)(actor + 0x14)), 3.1415927f);
            if (func_00283C80(angle, *(float *)(actor + 0xF8)) > 1.5707964f)
                angle = func_00283B98(angle, 3.1415927f);
            turnStep = D_L02_001B0B88 * 6.981318e-06f;
            turnLimit = D_L02_001B0B8C * 0.0003490659f;
            func_002AAA00(actor + 0xF8, state + 0x40, 0, angle, turnStep, turnStep * 3.0f, turnLimit);
            func_PAL_L02_003ED0D8(actor);
            separation = func_00282E80(actor + 0x10, ((Hero003E87D8 *)D_00189E20)->position);
            if (((Hero003E87D8 *)D_00189E20)->captured != target || separation > D_L02_001B0BA0) {
                float distance, scaledDistance;
                ((Hero003E87D8 *)D_00189E20)->captured = 0;
                distance = func_00282E48(actor + 0x10, ((Hero003E87D8 *)D_00189E20)->position) - D_L02_001B0B84;
                if (distance < 0.0f)
                    distance = 0.0f;
                scaledDistance = distance * 0.020000001f;
                ((Actor003E87D8 *)target)->flags &= 0xEFFF;
                *(float *)(state + 0x44) = D_L02_001B0B90 * 0.020000001f + D_L02_001B0B94 * scaledDistance;
                func_002E5CF8(0, 0, actor);
                func_002A7750(actor, 3, -1);
            } else {
                ((Hero003E87D8 *)D_00189E20)->captureMode = 2;
                func_L00_00424F58(actor + 0x10, 0.78539824f, 0.0f);
                func_L00_00424C28();
                func_L00_00424B70(0.03f, 0.2f);
                if (*(unsigned short *)(target + 0x34) & 0x1000)
                    break;
                func_002A7750(actor, 1, -1);
            }
        }
        break;
    case 3:
        if (func_002B3868(actor)) {
            qzero_nc(state + 0x10);
            func_002E5CF8(0, 0, actor);
        }
        if (func_PAL_L02_003ED2A0(actor)) {
            func_L00_003294F0(target, 0);
            if (*(short *)(target + 0xAA) == 0x9BC) {
                func_L02_003CADA8(target, state + 0x10);
                D_0018CA6C = 0xFFFF;
            } else {
                func_L02_003D01F0(target, state + 0x10);
            }
            func_002A7750(actor, 1, -1);
        }
        break;
    }
    if (func_00282C48(*(float *)(state + 0x40)) > 0.0052359886f) {
        char *slot = D_00188660 + *(int *)(state + 0x58) * 0x70;
        if (*(char **)(slot + 0x88) != actor || *(unsigned char *)(slot + 0x74) == 0)
            *(int *)(state + 0x58) = func_002E5CF8(1, 4, actor);
        if (*(unsigned char *)(actor + 0x20) != 2)
            *(float *)(state + 0x40) = 0;
    } else {
        int index = *(int *)(state + 0x58);
        if (index != -1) {
            char *slot = D_00188660 + index * 0x70;
            if (*(char **)(slot + 0x88) == actor && *(unsigned char *)(slot + 0x74))
                func_002E59F8(index);
        }
        *(int *)(state + 0x58) = -1;
    }
    if (*(char **)(state + 0x54)) {
        func_00283098(local, effectOffset003E87D8, actor + 0xC0);
        func_00282CC0(*(char **)(state + 0x54) + 0x10, local, actor + 0x10);
        *(float *)(*(char **)(state + 0x54) + 0xF8) = *(float *)(actor + 0xF8);
        *(float *)(*(char **)(state + 0x54) + 0x2C) = *(float *)(*(char **)(*(char **)(state + 0x54) + 0x24) + 0x24) * D_L02_001B0BF0[3];
    }
    if (func_002B38B8(target))
        func_L00_002E6CF0(func_PAL_L02_003EDCE8, actor);
}
