/* func_L01_003C01C0 - 580 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L01_003C01C0-g8.c (-G8; gp pointers/floats sda), marker
   removal in L01_003BB9D0.c needed. 592 vs 580 bytes. Logic fully decoded and
   control flow matches.
   qcopy_nc (not qcopy) is right here: retail loads the gp table pointer once
   (qcopy's memory clobber made mine reload it).
   Remaining: retail recomputes `addiu a1,s0,0x60` for func_31C800 and again
   for func_31CC78 (and saves state byte in s2); mine CSEs st+0x60 into s2 and
   saves the state byte in s3 (+4 bytes, +1 saved reg).
   Tried: -frac2-gcse-unsplit-edges, reloading *(obj+0x68) in the second call
   (588 bytes but extra lw), st assigned late. */

#include "common.h"

extern int func_002B0ED8(void *, void *, int);
extern void func_002B1350(void *, void *, void *, int);
extern void func_002B3BA8(void *, int, int, int, float, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_L01_002F14E8(int, int, float);
extern u8 *D_L01_001B255C __attribute__((sda));
extern u8 *D_L01_001B264C __attribute__((sda));
extern float D_L01_001AFEE0 __attribute__((sda));
extern float D_L01_001AFEE4 __attribute__((sda));
extern float D_L01_001AFEE8 __attribute__((sda));
extern f32 D_00189EA0[];

void func_L01_003C01C0(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x68);
    u8 saved = obj[0x20];
    f32 life;
    f32 quad[4] __attribute__((aligned(16)));
    u8 *effect;
    s32 slot;
    s32 mode;
    f32 value;

    if (func_002B0ED8(obj, st + 0x60, 0) != 0 || st[0x2E] == 2) {
        life = *(f32 *)(st + 0x20);
        if (life <= 0.0f || st[0x2E] == 2) {
            *(f32 *)(st + 0x20) = 0.0f;
            if (st[0x2E] == 2) {
                if ((*(u16 *)(st + 0x98) & 1) == 0) {
                    qzero(quad);
                    func_002B1350(obj, st + 0x60, quad, 4);
                    st[0x2E] = 3;
                    obj[0x95] = 6;
                    obj[0x20] = 0x63;
                    obj[0xBC] = 0x63;
                }
            }
            slot = *(s32 *)(st + 0x2F8);
            if (slot != -1) {
                D_L01_001B255C[(slot << 8) + 0xBC] = 1;
                slot = *(s32 *)(st + 0x2FC);
                if (slot != -1) {
                    qcopy_nc(obj + 0x10, D_L01_001B264C + (slot << 7) + 0x30);
                    qcopy_nc(obj + 0xF0, D_L01_001B264C + (slot << 7) + 0x70);
                }
            }
        }
    }
    if (obj[0x20] == 0xFF) {
        obj[0x20] = saved;
    }
    func_002B3BA8(obj, *(s32 *)(st + 0x2F0), 0, 0, 0.0f, 0.0f);
    effect = *(u8 **)(st + 0x2E4);
    if (effect != 0) {
        func_00282CF0(effect + 0x20, obj + 0x10, D_00189EA0);
        (*(u8 **)(st + 0x2E4))[0x1F] = 1;
        *(f32 *)(*(u8 **)(st + 0x2E4) + 0x10) = D_L01_001AFEE0 * 0.0174532942f;
        if (st[0x2F4] != 0 || (obj[0x95] == 3 && obj[0x20] == 2)) {
            mode = 6;
            value = D_L01_001AFEE8;
        } else {
            mode = 3;
            value = D_L01_001AFEE4;
        }
        **(f32 **)(st + 0x2E4) = value;
        *(s32 *)(*(u8 **)(st + 0x2E4) + 0x34) = mode;
    }
    if (D_00189EA0[2] < *(f32 *)(obj + 0x18) + 20.0f) {
        if ((u8)(obj[0x95] - 2) < 5) {
            func_L01_002F14E8(2, 0, *(f32 *)(st + 0x20) / func_00283CE0(*(s16 *)(st + 0x24)));
        }
    }
}
