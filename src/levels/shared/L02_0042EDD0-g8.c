#include "include_asm.h"

/* func_L02_0042EDD0 is a unit of its own: it reads D_L02_001B2434 through $gp (hence -G8) and
   needs two opt-in profiles (docs/build/compiler-notes.md). -frac2-no-annulled-wide-stores keeps
   reorg from copying the 16-byte clear at the top of the second loop into the annulled slot of
   a `bnel` that closes the loop: retail keeps the clear under the loop label and ends with a
   plain `bnez` whose slot is the fall-through's `lwc1`. -frac2-zero-ti-barrier schedules
   that clear as the quadword-clear macro: the `swc1` of the vector's z then stays before the
   first `jal`, and `p++` fills its slot.  The pool bases and the group table are plain extern
   pointers (in this unit the bare `lw $r,sym` macro, a scalar MEM that loop.c and gcse hoist
   out of the first loop); only the $gp float carries `sda`. At level 26 the D_L02_ symbols are
   where its bytes read. */

typedef unsigned char u8;

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    float x, y, z, w;
    float pad[4];
} Rec32;

extern unsigned short **D_L02_001A9014;

extern Rec32 *D_L02_001B3C14;

extern u8 *D_L02_001B3C1C;

extern u8 *D_L02_001AD410;

extern float D_L02_001B2434 __attribute__((sda));

extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);

void func_L02_0042EDD0(u8 *a0) {
    int *s = *(int **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0: {
        unsigned short *p;
        Rec32 *e;
        u8 none = 0xFF;

        if (s[0] == -1)
            break;
        a0[0x30] = none;
        for (p = D_L02_001A9014[s[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L02_001A9014[s[0]]) &&
             (e = D_L02_001B3C14 + (*p & 0x7FFF)) != 0;
             p++)
            e->w = e->w + e->w;
        a0[0x20] = 1;
        break;
    }
    case 1: {
        unsigned short *p;
        u8 *e;
        float v[4];
        float m[12];
        float x;
        u8 *g;

        for (p = D_L02_001A9014[s[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L02_001A9014[s[0]]) &&
             (e = D_L02_001B3C1C + ((*p & 0x7FFF) << 6)) != 0;
             p++) {
            *(TI128 *)v = 0;
            v[2] = 0.00785398297f;
            func_002833F0(m, v);
            func_00283738(e, e, m);
        }
        g = D_L02_001AD410;
        x = *(float *)(g + 0x74) + D_L02_001B2434 * 0.016666668f;
        *(float *)(g + 0x74) = x;
        if (x > 1.0f)
            *(float *)(g + 0x74) = x - 1.0f;
        break;
    }
    }
}
