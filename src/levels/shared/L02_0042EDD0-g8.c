#include "include_asm.h"
#include "names.h"

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

/* Sets up a linked group of parts once, then turns them a little every frame and advances a shared 0 to 1 timer. */
void func_L02_0042EDD0(u8 *object) {
    int *vars = *(int **)(object + 0x68);

    switch (object[0x20]) {
    case 0: {
        unsigned short *p;
        Rec32 *e;
        u8 none = 0xFF;

        if (vars[0] == -1)
            break;
        object[0x30] = none;
        for (p = D_L02_001A9014[vars[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L02_001A9014[vars[0]]) &&
             (e = D_L02_001B3C14 + (*p & 0x7FFF)) != 0;
             p++)
            e->w = e->w + e->w;
        object[0x20] = 1;
        break;
    }
    case 1: {
        unsigned short *p;
        u8 *e;
        float angles[4];
        float rotationMatrix[12];
        float timer;
        u8 *sharedState;

        for (p = D_L02_001A9014[vars[0]];
             p != 0 && ((p != 0 && (short)p[-1] >= 0) || p == D_L02_001A9014[vars[0]]) &&
             (e = D_L02_001B3C1C + ((*p & 0x7FFF) << 6)) != 0;
             p++) {
            *(TI128 *)angles = 0;
            angles[2] = 0.00785398297f;
            euler_rotation_basis(rotationMatrix, angles);
            multiply_matrix3x3(e, e, rotationMatrix);
        }
        sharedState = D_L02_001AD410;
        timer = *(float *)(sharedState + 0x74) + D_L02_001B2434 * 0.016666668f;
        *(float *)(sharedState + 0x74) = timer;
        if (timer > 1.0f)
            *(float *)(sharedState + 0x74) = timer - 1.0f;
        break;
    }
    }
}
