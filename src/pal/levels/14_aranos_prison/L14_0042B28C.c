#include "include_asm.h"
#include "common.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L14_0042B28C);

/* func_PAL_L14_0042BC18, the PAL copy of func_L14_004265B8: the same C, where the fade length 0x7D
   becomes 0x68 and both timers take the 50 Hz scale, the fade timer first. */
extern char *D_L14_001B268C __attribute__((sda));
extern unsigned char *D_L14_001B259C __attribute__((sda));
typedef int PrisonQword __attribute__((mode(TI)));
typedef struct {
    char pad00[0x18];
    int exitTrigger;            /* 0x18 */
    int enterTrigger;           /* 0x1C */
    char pad20[0x10];
    int gateCamera;             /* 0x30 */
    int doorCamera;             /* 0x34 */
    int pad38;
    int lift;                   /* 0x3C: entity index */
    int panel;                  /* 0x40: entity index */
    int beam;                   /* 0x44: entity index */
    int guard;                  /* 0x48: entity index */
    int switchEntity;           /* 0x4C: entity index */
    int door;                   /* 0x50: entity index */
    int text54, text58, text5C; /* 0x54..0x5C */
    int zone60;                 /* 0x60 */
    int text64;                 /* 0x64 */
    float volume;               /* 0x68 */
    int fadeTimer;              /* 0x6C */
    int nextState;              /* 0x70 */
    int waitTimer;              /* 0x74 */
    int fadeLength;             /* 0x78 */
    int music7C, music80, music84, music88; /* 0x7C..0x88 */
    int frames;                 /* 0x8C */
} PrisonLiftState;

/* The 0x100-byte entity record, with only the fields this function uses. */
typedef struct {
    char pad00[0x24];
    char *info;                 /* 0x24 */
    char pad28[0xC];
    unsigned short flags;       /* 0x34 */
    char pad36[0x62];
    int target;                 /* 0x98 */
} PrisonLiftEntity;

extern int D_L14_001FF4A4;
extern char D_L14_001B17A0[];
extern u8 D_0019B2E8[];
extern char D_00189EA0[];
extern u8 D_00189E20[];
extern int D_001A79F0 __attribute__((sda));
extern int D_001A7A00 __attribute__((sda));
extern int D_001A8F00 __attribute__((sda));
extern int D_L14_001A8FB0 __attribute__((sda));
extern int D_L14_001A8FB4 __attribute__((sda));
extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_001A7B30[] __attribute__((sda));
extern short D_001A63F0[];
extern int D_00138324;
extern u8 D_001395E1;

extern int func_002ACBC8(void *, int);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void func_L14_00426D18(void *);
extern void func_L00_003294F0(void *, int);
extern int func_L00_0030DDB0(int, int);
extern int func_002B3868(void *);
extern void func_PAL_L00_002B2958(int, int, void *);
extern void func_L01_00323310(int, int);
extern void func_PAL_L14_0042C4E8(void *);
extern int func_L14_00427210(void *);
extern void func_002A0430(int);
extern void func_002DF3F8(void *, void *);
extern void func_L02_002B5F50(int); /* the parameter is unused */
extern int func_L14_003DE8E8(void *);
extern void func_L14_003DE8F8(void *);
extern void func_0029F338(void *);
extern void func_L14_003DE990(void *);
extern void func_002A7750(void *, int, int);
extern void func_PAL_L00_002C4480(int, int);
extern int func_00282948(void *);
extern float func_00283198(float);
extern void func_L00_002E6EF8(void (*)(void *), void *);
extern void func_L14_00426DE8(char *);

void func_PAL_L14_0042BC18(unsigned char *moby) {
    PrisonLiftState *state = *(PrisonLiftState **)(moby + 0x68);
    unsigned char *lift = D_L14_001B259C + state->lift * 256;
    unsigned char *panel = D_L14_001B259C + state->panel * 256;
    unsigned char *guard = D_L14_001B259C + state->guard * 256;
    PrisonQword pos;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        state->fadeLength = 0x68;
        if (D_0019B2E8[state->text5C + D_001A79F0 * 16] & 0x80) {
            if (func_002ACBC8(D_00189EA0, state->enterTrigger)) {
                func_PAL_L00_002B9CD8(D_L14_001B268C + state->doorCamera * 128 + 0x30,
                                  D_L14_001B268C + state->doorCamera * 128 + 0x70, 0, 1);
                *(short *)(D_00189EA0 + 0x247C) = 0;
                D_001A7AF8[2] = 1;
                D_001A7B30[2] = 1;
                D_001A7AF8[3] = 1;
                D_001A7B30[3] = 1;
            }
            if (D_0019B2E8[state->zone60 + D_001A79F0 * 16] & 0x80) {
                func_L14_00426D18(moby);
                func_L00_003294F0(D_L14_001B259C + state->door * 256, 1);
            }
            func_002A7750(moby, 7, -1);
        } else {
            *(short *)(D_00189EA0 + 0x247C) = 1;
            D_001A7AF8[2] = 0;
            D_001A7B30[2] = 0;
            D_001A7AF8[3] = 0;
            D_001A7B30[3] = 0;
            if (D_0019B2E8[state->text58 + D_001A79F0 * 16] & 0x80) {
                func_L14_00426D18(moby);
                func_002A7750(moby, 5, -1);
            } else if (D_0019B2E8[state->text64 + D_001A79F0 * 16] & 0x80) {
                func_L14_00426D18(moby);
                func_002A7750(moby, 4, -1);
            } else if (D_0019B2E8[state->text54 + D_001A79F0 * 16] & 0x80) {
                func_002A7750(moby, 3, -1);
            } else if (D_L14_001FF4A4 != 0) {
                func_002A7750(moby, 1, -1);
            } else {
                func_002A7750(moby, 2, -1);
            }
        }
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0, state->enterTrigger)) {
            func_L00_0030DDB0((int)D_L14_001B17A0, 1);
            D_L14_001A8FB0 = 2;
            D_L14_001A8FB4 = 8;
            if (D_00138324 & 0x10)
                func_002A7750(moby, 2, -1);
        }
        break;
    case 2:
        if (func_002B3868(moby)) {
            unsigned char *liftNow = D_L14_001B259C + state->lift * 256;
            func_PAL_L00_002B9CD8(liftNow + 0x10, liftNow + 0xF0, 0x6F, 1);
            func_PAL_L00_002B2958(1, 0x3F, liftNow);
            if (D_001A63F0[0] != state->music7C)
                func_L01_00323310(state->music7C, state->music88);
        }
        func_PAL_L14_0042C4E8(moby);
        if (func_L14_00427210(guard)) {
            D_001395E1 = 1;
            func_002A0430(state->text54);
            func_002DF3F8(moby + 0xF0, moby + 0xF0);
            state->nextState = 3;
            func_002A7750(moby, 6, -1);
        }
        break;
    case 3:
        if (func_002B3868(moby)) {
            func_L02_002B5F50(0);
            func_PAL_L00_002B9CD8(moby + 0x10, moby + 0xF0, 0, 1);
            func_L14_00426D18(moby);
            *(int *)(D_00189E20 + 0x24CC) = D_001A7A00;
            if (D_001A63F0[0] != state->music80)
                func_L01_00323310(state->music80, state->music88);
        }
        if (func_L14_003DE8E8(D_L14_001B259C + state->panel * 256)) {
            func_002A0430(state->text64);
            func_002DF3F8(guard + 0x10, guard + 0xF0);
            state->nextState = 4;
            func_002A7750(moby, 6, -1);
        }
        break;
    case 4:
        if (func_002B3868(moby)) {
            PrisonLiftEntity *beam;
            func_L14_003DE8F8(panel);
            if (guard != 0 && guard[0x20] != 0xFE && guard[0x20] != 0xFD)
                func_0029F338(guard);
            beam = (PrisonLiftEntity *)(D_L14_001B259C + state->beam * 256);
            beam->target = 0;
            beam->flags = (beam->flags | 0x41) & ~0x1000;
            func_PAL_L00_002B9CD8(guard + 0x10, guard + 0xF0, 0x6F, 1);
            func_PAL_L00_002B2958(1, 0x3F, lift);
            if (D_001A63F0[0] != state->music7C)
                func_L01_00323310(state->music7C, state->music88);
        }
        func_PAL_L14_0042C4E8(moby);
        if (func_002ACBC8(D_00189EA0, state->exitTrigger)) {
            func_002A0430(state->text58);
            func_002DF3F8(&pos, panel + 0xF0);
            state->nextState = 5;
            func_002A7750(moby, 6, -1);
        }
        break;
    case 5:
        if (func_002B3868(moby)) {
            PrisonLiftEntity *beam;
            func_0029F338(lift);
            beam = (PrisonLiftEntity *)(D_L14_001B259C + state->beam * 256);
            beam->flags = (beam->flags & ~0x41) | 0x1000;
            beam->target = *(int *)(beam->info + 0x10);
            qcopy(&pos, D_L14_001B268C + state->gateCamera * 128 + 0x30);
            if (D_00189E20[0x22B4] == 1)
                func_L02_002B5F50(0);
            func_PAL_L00_002B9CD8(&pos, D_L14_001B268C + state->gateCamera * 128 + 0x70, 0, 1);
            func_L14_003DE990(panel);
            *(int *)(D_00189E20 + 0x24CC) = D_001A7A00;
            if (D_001A63F0[0] != state->music80)
                func_L01_00323310(state->music80, state->music88);
        }
        if (D_001A8F00 != 2 && D_L14_001B259C[state->switchEntity * 256 + 0x20] > 0x80) {
            func_002A0430(state->text5C);
            func_002DF3F8(D_L14_001B268C + state->doorCamera * 128 + 0x30,
                          D_L14_001B268C + state->doorCamera * 128 + 0x70);
            D_001A7AF8[2] = 1;
            D_001A7B30[2] = 1;
            D_001A7AF8[3] = 1;
            D_001A7B30[3] = 1;
            *(short *)(D_00189EA0 + 0x247C) = 0;
            func_002A7750(moby, 7, -1);
        }
        break;
    case 6:
        if (func_002B3868(moby)) {
            state->fadeTimer = ((s32)(state->fadeLength) * 5 + 2) / 6 * 2;
            state->waitTimer = ((s32)(state->fadeLength) * 5 + 2) / 6;
            func_PAL_L00_002C4480(0x6F, 1);
        }
        if (func_00282948(&state->waitTimer))
            func_002A7750(moby, state->nextState, -1);
        break;
    case 7:
        if (func_002B3868(moby))
            state->frames = 0;
        if (D_001A8F00 != 2 && state->frames >= 6 && D_001A63F0[0] != state->music84)
            func_L01_00323310(state->music84, state->music88);
        state->frames++;
        break;
    default:
        break;
    }
    if (state->fadeTimer != 0) {
        func_00282948(&state->fadeTimer);
        state->volume = func_00283198((float)state->fadeTimer * 1.5707964f / (float)state->fadeLength);
        func_L00_002E6EF8((void (*)(void *))func_L14_00426DE8, moby);
    }
}
