#include "include_asm.h"


/* func_PAL_L12_00418BD8, the PAL copy of func_L12_00413CE0: the same C, with the value
   stored in f2E0 scaled to 50 Hz. A unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

extern u16 *D_L12_001FB960[];

/* The path-follower state of an entity: the record fields the nearest-entity hand-over touches. */
typedef struct {
    u8 pad00[0x2B0];
    s32 f2B0;
    s32 f2B4;
    s32 f2B8;
    s32 f2BC;
    s32 f2C0;
    u8 pad2C4[0x2D0 - 0x2C4];
    s32 f2D0;
    s32 f2D4;
    u8 pad2D8[0x2DC - 0x2D8];
    s32 f2DC;
    u16 f2E0;
    u8 pad2E2[0x2EA - 0x2E2];
    u8 f2EA;
    u8 pad2EB[0x302 - 0x2EB];
    u8 f302;
    u8 f303;
} PathState;

extern u8 *D_L12_001B2E9C_base[3] __asm__("D_L12_001B2E9C") __attribute__((sda));

extern s32 D_L12_001B2EB8;

extern s32 D_L12_001B1840 __attribute__((sda));

extern u8 *D_L12_001FEAC0[];

extern f32 func_00282E80(void *a, void *b);

/* Hands the object's path state to the nearest eligible entity of its group. */
void func_PAL_L12_00418BD8(u8 *a0)
{
    PathState *state = *(PathState **)(a0 + 0x68);
    u8 *best;
    f32 bestd;
    f32 vec[4];
    u16 *p;
    u8 *e;
    PathState *sub;
    f32 d;

    if (state->f2C0 != -1) {
        *(TI128 *)vec = *(TI128 *)(D_L12_001FEAC0[state->f2C0] + 0x10);
        best = 0;
        bestd = 100000.0f;
        for (p = D_L12_001FB960[a0[0x21]];
             a0[0x21] != 0xFF && a0[0x21] <= D_L12_001B2EB8 && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L12_001FB960[a0[0x21]]);
             p++) {
            e = D_L12_001B2E9C_base[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            sub = *(PathState **)(e + 0x68);
            d = func_00282E80(e + 0x10, vec);
            if (sub != 0 && (sub->f302 & 1)) {
                if (d < bestd) {
                    bestd = d;
                    best = e;
                }
            }
        }
        if (best != 0) {
            PathState *dst = *(PathState **)(best + 0x68);

            dst->f2B0 = state->f2B0;
            dst->f2B4 = state->f2B4;
            dst->f2B8 = state->f2B8;
            dst->f2BC = state->f2BC;
            dst->f2C0 = state->f2C0;
            dst->f2D0 = state->f2D0;
            dst->f2D4 = state->f2D4;
            dst->f2E0 = ((s32)D_L12_001B1840 * 5 + 2) / 6;
            dst->f2DC = state->f2C0;
            dst->f2EA = 1;
            dst->f302 = 2;
            dst->f303 = state->f303;
        }
    }
}
