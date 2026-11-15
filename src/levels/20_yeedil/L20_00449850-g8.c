#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: the body reaches level globals through $gp. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern int D_L20_001A8F00;

extern char *D_0018A3E0 __attribute__((nosda));

extern float D_L20_001B23E0 __attribute__((sda));

extern float D_L20_001B23E4 __attribute__((sda));

/* Declared without sda: the load gcc copies into a delay slot is assembled through $gp,
   the reload after the 0xAC store stays absolute, as in retail. */
extern int D_L20_001B2AC8;

extern void func_L20_00449A78(char *);

extern void func_L20_00449AE8(char *);

extern void func_L20_00449BB0(char *);

extern void func_L01_0031AB20(void *, void *, float, float, float, int);

extern float func_002A89A8(char *, int, float);

extern float func_00282C48(float);

extern int func_00282948(int *);

/* The object's state block (only the fields this body touches). */
typedef struct {
    char pad0[0x20];
    float x20;
    u16 x24;
    char pad26[0x50 - 0x26];
    char x50[0x20];
    u32 x70;
    char pad74[0x84 - 0x74];
    float x84;
    float x88;
    char pad8C[0xA0 - 0x8C];
    int xA0;
    char padA4[0xA8 - 0xA4];
    int xA8;
    u32 xAC;
} State;

/* Update handler for moby class 4819: it sets itself up, waits quietly, and pops with an effect when the player targets it or comes close. */
void func_L20_00449850(char *moby) {
    State *state = *(State **)(moby + 0x68);
    int mode;

    if (D_L20_001A8F00 == 2 && *(u8 *)(moby + 0x20) != 1) {
        ResetMobyToIdle(moby);
    }
    mode = *(u8 *)(moby + 0x20);
    switch (mode) {
    case 0:
        state->x20 = 1.0f;
        state->x24 = 1;
        state->x70 |= 6;
        state->x84 = D_L20_001B23E0;
        state->x88 = D_L20_001B23E4;
        ResetMobyToIdle(moby);
        return;
    case 1:
        return;
    case 2:
        UpdatePushableMoby(moby, state->x50, 0.0f, 0.5f, 0.6f, state->xA0);
        break;
    }
    if (D_0018A3E0 == moby) {
        state->xAC = 1;
    }
    if (((D_L20_001B2AC8 & 0xF) == (((int)moby >> 8) & 0xF)
         && 5.0f < FloatAbs(*(float *)(moby + 0x18)
                                 - ProbeGroundHeightBelow(moby + 0x10, 0, 0.5f)))
        || (state->xAC != 0 && FastFloatHelperD(&state->xA8) != 0)) {
        VanishMobyWithEffect(moby);
    } else {
        FollowPathAndPopOnTouch(moby);
    }
}
