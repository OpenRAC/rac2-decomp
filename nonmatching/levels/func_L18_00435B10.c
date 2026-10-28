/* func_L18_00435B10 - 436 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L18_00435B10-g8.c (-G8), marker removal in
   L18_00433460.c needed. Same size; first 0xA8 bytes match; control flow,
   switch, all calls match.
   Remaining ~30 diff lines = register naming of the 13-word context stores:
   retail count=t6, array base t7 (gp+0x26A8), 0x12 in a0, consts
   v0,v1,a1,a2,a3,t0 in order of ctx[2],[3],[6],[7],[11],[12], gp addrs
   t1,t2,t3, t4=1, t5=state.
   Mine allocates count/array/0x12 differently. Context stores are in the
   order [0],[1],[8],[9],[2],[3],[4],[5],[6],[7],[11],[12],[10] (that order in
   the draft). Tried tab pointer var, ternary, count += sum, aggregate
   initializer (bad: whole-struct copy).
   Names: sda arrays D_L18_001B1698/16B0/16D4/16D8 (2 elems), functions
   func_L00_002E6EF8, func_L18_00435CC8 as stored pointers. */

#include "common.h"

extern int func_L00_00329520(void *, int);
extern void func_L04_003A1A78(void *);
extern void func_L04_003A5C08(void *, float);
extern void func_L04_003A1C98(void *);
extern void func_L04_003A1FA0(void *);
extern void func_L04_003A1FE0(void *);
extern void func_L00_002E6EF8(void);
extern void func_L18_00435CC8(void);
extern u8 D_00189E20[];
extern float D_L18_001B97C0[];
extern char D_L18_002A9C40[];
extern char D_L18_00257C80[];
extern char D_L18_00257DA0[];
extern char D_L18_002BD860[];
extern s32 D_L18_001B1698[2] __attribute__((sda));
extern s32 D_L18_001B16B0[2] __attribute__((sda));
extern s32 D_L18_001B16D4[2] __attribute__((sda));
extern s32 D_L18_001B16D8[2] __attribute__((sda));

void func_L18_00435B10(u8 *obj) {
    s32 ctx[13];
    u8 *st;
    u8 *hero = D_00189E20;
    u8 *boss = *(u8 **)(hero + 0x1830);
    s32 idx;
    s32 count;

    if (boss != 0 && *(s16 *)(boss + 0xAA) == 0x45 && boss[0x20] != 0xFE && boss[0x20] != 0xFD
        && *(s32 *)(hero + 0x2294) == 0x31) {
        return;
    }
    st = *(u8 **)(obj + 0x68);
    if (st == 0) {
        return;
    }
    if (*(s32 *)(st + 0x10) != 0 && obj[0x20] != 0 && *(s32 *)(st + 0x28) != -1) {
        if (func_L00_00329520(D_L18_001B97C0, *(s32 *)(st + 0x28)) == 0) {
            return;
        }
    }
    idx = *(s32 *)(st + 0x18);
    count = 1;
    if (idx != -1) {
        count = D_L18_001B1698[idx];
    }
    ctx[0] = 0x12;
    ctx[1] = count + *(s32 *)(st + 0x10);
    ctx[8] = (s32)D_L18_001B16D4;
    ctx[9] = (s32)D_L18_001B16D8;
    ctx[2] = (s32)D_L18_002A9C40;
    ctx[3] = (s32)D_L18_00257C80;
    ctx[4] = (s32)D_L18_001B16B0;
    ctx[5] = (s32)D_L18_001B1698;
    ctx[6] = (s32)D_L18_00257DA0;
    ctx[7] = (s32)D_L18_002BD860;
    ctx[11] = (s32)func_L18_00435CC8;
    ctx[12] = (s32)func_L00_002E6EF8;
    ctx[10] = (s32)obj;
    switch (obj[0x20]) {
    case 0:
        func_L04_003A1A78(ctx);
        func_L04_003A5C08(obj, *(float *)(st + 0x2C));
    case 1:
        func_L04_003A1C98(ctx);
        break;
    case 2:
        func_L04_003A1FA0(ctx);
        break;
    }
    func_L04_003A1FE0(ctx);
}
