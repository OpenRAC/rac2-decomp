#include "include_asm.h"

#include "common.h"
typedef int UiQuadword __attribute__((mode(TI)));
extern char *D_L00_001AFF98 __attribute__((sda));
extern unsigned char D_L00_001DB2BC[];
extern char *D_L00_001D9F00[];
extern UiQuadword D_00189EA0[];
extern int D_L00_001B2940[] MACRO_ADDR;
extern int D_L00_001B2950[] MACRO_ADDR;
extern short D_L00_001B2990[] MACRO_ADDR;
extern UiQuadword D_L00_001B2900 MACRO_ADDR, D_L00_001B2910 MACRO_ADDR, D_L00_001B2920 MACRO_ADDR,
    D_L00_001B2930 MACRO_ADDR;
extern float D_L00_001AFF4C __attribute__((sda));
extern float D_L00_001B29D4 __attribute__((sda));
extern char D_L00_0023FB80[];
extern int func_L00_002D3F30(int, int);
extern int func_002E5AD0(void *, int, int, void *, int);
extern unsigned char *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_L00_0037E670(int);
extern float func_L00_0037E668(void);
extern int func_002E5CF8(int, int, void *);
typedef struct {
    float f00;
    char pad04[0xC - 0x4];
    int f0C;
    int f10;
    int countdown;
    short entries[4];
    int words[4];
} OwnerState;
typedef struct {
    char pad00[0x10];
    UiQuadword position;
    unsigned char status;
    char pad21[0x30 - 0x21];
    unsigned char group;
    char pad31[3];
    unsigned short flags;
    char pad36[0x68 - 0x36];
    OwnerState *state;
    char pad6C[0xC0 - 0x6C];
    float forward[4], side[4], up[4], angles[4];
} Owner3A;

/* Creates the single object of this kind (0x1192 when mode is set, 0xA5C otherwise) unless one
   exists or the gate refuses, builds its basis from its angles, stores the scaled basis
   vectors and their combinations in the shared tables, clears the per-slot tables and resets
   the object's state block. Returns the object, or 0 when nothing was created. */
unsigned char *func_PAL_L00_003C77F0(int mode)
{
    Owner3A *owner;
    OwnerState *state;
    float *up;
    float *side;
    UiQuadword *position;
    short *entries;
    int *words;

    if (D_L00_001AFF98 != 0) {
        func_002E5AD0(*(char **)(D_L00_001D9F00[D_L00_001DB2BC[0]] + 0x28) + 0x80,
                      0, 0, D_00189EA0, 0x400);
        return 0;
    }
    if (func_L00_002D3F30(45, 1) == 0) {
        func_002E5AD0(*(char **)(D_L00_001D9F00[D_L00_001DB2BC[0]] + 0x28),
                      0, 0, D_00189EA0, 0x400);
        return 0;
    }

    owner = (Owner3A *)func_0029EFD0(mode ? 0x1192 : 0xA5C);
    if (owner != 0) {
        state = owner->state;
        D_L00_001AFF98 = (char *)owner;
        owner->flags |= 0x41;
        owner->group = 0xFF;
        owner->status = 1;
        func_002833F0(owner->forward, owner->angles);
        up = owner->up;
        position = &owner->position;
        side = owner->side;

        {
            int n;

            for (n = 3; n >= 0; n--)
                D_L00_001B2940[n] = 0;
        }
        func_00282F20(D_L00_0023FB80, owner->forward, D_L00_001AFF4C);
        qcopy(&D_L00_001B2900, up);
        func_00282F20(D_L00_0023FB80 + 0x140, side, D_L00_001AFF4C);
        qcopy(&D_L00_001B2910, owner->forward);
        func_00282F20(D_L00_0023FB80 + 0x280, up, D_L00_001AFF4C);
        qcopy(&D_L00_001B2920, side);
        func_00282CC0(D_L00_0023FB80 + 0x3C0, owner->forward, up);
        entries = state->entries;
        func_00282F20(D_L00_0023FB80 + 0x3C0, D_L00_0023FB80 + 0x3C0, D_L00_001AFF4C);
        words = state->words;
        func_00282DD8(&D_L00_001B2930, D_L00_0023FB80 + 0x3C0, side);

        {
            int n;

            for (n = 7; n >= 0; n--)
                D_L00_001B2950[n] = 0;
        }
        {
            int n;

            for (n = 4; n >= 0; n--)
                D_L00_001B2990[n] = 0;
        }
        D_L00_001B29D4 = 1.0f;

        func_L00_0037E670(mode);
        state->f00 = func_L00_0037E668();
        qcopy(position, D_00189EA0);
        state->f0C = -1;
        state->f10 = 0;
        state->countdown = 25;
        {
            int n;

            for (n = 3; n >= 0; n--)
                entries[n] = 0;
        }
        {
            int n;

            for (n = 3; n >= 0; n--)
                words[n] = 0;
        }
        func_002E5CF8(1, 0, owner);
    }
    return (unsigned char *)owner;
}
