#include "include_asm.h"
#include "names.h"

/* func_L02_003EE938 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad[0x100];
    float f100;
    float f104;
} Pad003EE938;

extern void func_0029F338(char *);
extern void func_L02_003EEAD8(char *);
extern int func_00283CF0(float);
extern void func_002A7750(char *, int, int);
extern int func_L02_003EEFB8(char *);
extern float func_L02_003EEC58(char *);
extern void func_L02_003EEDD0(char *);
extern void func_002AA2E8(float *, float, float);
extern int D_L02_001B30C8 __attribute__((sda));
extern Pad003EE938 D_00138180;

/* The actor's state machine (byte at +0x20): 0 prepares it, 1 waits for the target to come within
   range on its own frame of eight, 2 follows the pad until the state asks to restart. */
void func_L02_003EE938(char *actor) {
    char *state = *(char **)(actor + 0x68);
    int value;

    switch (*(unsigned char *)(actor + 0x20)) {
    case 0:
        if (*(int *)state == -1) {
            MarkMobySpawned(actor);
            return;
        }
        InitActorPathBounds(actor);
        *(TI128 *)(actor + 0x10) = *(TI128 *)(state + 0x20);
        value = FloatToInt(*(float *)(state + 0x2C) * 1.5f);
        if (value >= 256)
            value = 255;
        *(unsigned char *)(actor + 0x30) = value;
        SetMobyState(actor, 1, -1);
        return;
    case 1:
        if ((gFrameCounter_L02 & 7) == (((int)actor >> 8) & 7)) {
            if (IsHeroNearPathPoint(actor)) {
                SetMobyState(actor, 2, -1);
                *(int *)(state + 0x34) = 0;
            }
        }
        return;
    case 2:
        *(float *)(state + 0x44) = UpdatePathProgress(actor);
        UpdateHeroPathHeading(actor);
        if (0.2f < gPadState.f100 + gPadState.f104)
            ApproachValue((float *)(state + 0x34), 0.0f, 0.33333334f);
        if (*(float *)(state + 4) + 1.0f < *(float *)(state + 0x44))
            SetMobyState(actor, 1, -1);
        return;
    }
}
