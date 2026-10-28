/* func_L12_003E0858 - 364 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c is a new file L12_003E0858-rc2.c, cflags: `-O2 -G0 -ffunction-
   sections -frac2-qcopy`. Plain Vec struct copies compile to ld/sd; copies
   via the Quad member (.q) give lq/sq. Size 364? (39 masked diff lines,
   mostly one shift).
   Remaining diff: in the found block retail has a0=def(obj->0x24),
   a1=obj+0x10, v1=s0+0x740, a2=&there; mine a1=def, a2=obj+0x10, a0=s0+0x740,
   a3=&there; and in the loop retail t1=3000,t0=1,a3=global (mine t0/t1/a2).
   Tried: all 120 orders of the 5 found-block statements, op/def locals.
   Constant 0x3C888889 = 0.016666668f. Marker in
   src/levels/12_todano/L12_00398E50.c restored. */

#include "common.h"

extern s32 D_L12_001B2E9C_2;
extern u16 *D_L12_001FB960[];

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; f32 f[4]; } Vec;

extern float func_00283248(float, float);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern void func_002A0F48(void *);

s32 func_L12_003E0858(s32 index, Vec *pos, Vec *dest) {
    Vec here;
    Vec there;
    Vec *h = &here;
    Vec *t = &there;
    u16 *list = D_L12_001FB960[index];
    s32 found = 0;
    u8 *object;
    u8 *state;

    here.q = pos->q;
    there.q = dest->q;
    if (list == 0) {
        return 0;
    }
    do {
        object = (u8 *)D_L12_001B2E9C_2 + ((*list & 0x7FFF) << 8);
        if (*(s16 *)(object + 0xAA) == 3000 && object[0x20] == 1) {
            found = 1;
            *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
            state = *(u8 **)(object + 0x68);
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            *(Quad *)(object + 0x10) = h->q;
            *(Quad *)(state + 0x740) = t->q;
            *(f32 *)(object + 0xF8) = func_00283248(t->f[0] - *(f32 *)(object + 0x10), t->f[1] - *(f32 *)(object + 0x14));
            *(s32 *)(object + 0xF0) = 0;
            *(s32 *)(object + 0xF4) = 0;
            func_002A7470(object, 2, 0, 2);
            object[0x20] = 2;
            *(s32 *)(state + 0x798) = 0;
            *(s32 *)(state + 0x794) = 0;
            *(f32 *)(state + 0x7AC) = func_002A7878(5.5f, 6.5f) * 0.016666668f;
            func_002A0F48(object);
            break;
        }
    } while ((s16)*list++ >= 0);
    return found;
}
