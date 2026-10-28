/* func_L30_00416D88 - 548 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   draft.c = new file L30_00416D88-g8.c (-G8; gp floats/ints sda), marker
   removal in L30_0040E660.c needed. Logic fully decoded (spawn of obj 0x11EA,
   two func_002C2210 calls).
   Needs reuse of the float param `scale` for the rand result (done: f20/f21
   match). Remaining: saved-register order (retail s1=parent, s0=type, s3=pos,
   s5=dir, s4=obj, s2=obj+0x10, then s3=obj+0xD0, s1=obj+0xC0 reuse),
   null check: retail `beqz s4,end` with v0=s4 in the shared tail (mine bnel
   with delay copy), D_L30_001A8F20 address (lui/addiu t1) is rebuilt at each
   of the 2 calls in retail, CSE'd into s0 in mine; 0x34 |= 0x100 / 0x23 store
   order. */

#include "common.h"

extern u8 *func_0029EFD0(int);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282E20(void *);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_002833F0(void *, void *);
extern void func_002C2210(void *, int, int, int, int, void *, int, float, float, float);
extern float D_L30_001B1FAC __attribute__((sda));
extern int D_L30_001B1F08 __attribute__((sda));
extern int D_L30_001B1F0C __attribute__((sda));
extern u8 D_L30_001A8F20[];

u8 *func_L30_00416D88(u8 *parent, f32 *dir, f32 *pos, int type, float scale) {
    u8 *obj = func_0029EFD0(0x11EA);
    u8 *st;

    if (obj != 0) {
        if (obj == 0) {
        }
    return obj;
    }
    obj[0x30] = 0xFF;
    *(s16 *)(obj + 0x32) = 0xFF;
    obj[0x31] = 1;
    obj[0xBC] = type;
    obj[0x20] = 0;
    *(u64 *)(obj + 0x38) = *(u64 *)(parent + 0x38);
    qcopy(obj + 0x10, pos);
    st = *(u8 **)(obj + 0x68);
    qcopy(st, dir);
    *(u8 **)(st + 0x10) = parent;
    *(f32 *)(st + 0x14) = scale;
    *(f32 *)(st + 0x20) = 0.15f;
    *(u16 *)(obj + 0x34) |= 0x208;
    *(f32 *)(obj + 0xF8) = func_00283B98(func_00283248(dir[0], dir[1]), 1.5707964f);
    *(f32 *)(obj + 0xF0) = -func_00283248(func_00282E20(dir), dir[2]);
    scale = func_002A7940();
    func_002ACEC0(obj + 0xE0, obj + 0xE0, obj + 0xD0, scale);
    func_002ACEC0(obj + 0xC0, obj + 0xC0, obj + 0xD0, scale);
    func_002833F0(obj + 0xC0, obj + 0xF0);
    obj[0x23] = 0x80;
    *(u16 *)(obj + 0x34) |= 0x100;
    *(f32 *)(obj + 0x2C) = D_L30_001B1FAC;
    *(s32 *)(st + 0x24) = 0;
    scale = func_002A7878(8.0f, 10.0f);
    func_002C2210(obj + 0x10, 0xF, D_L30_001B1F08, 0, 0xA, D_L30_001A8F20, 0, scale * 0.3f, scale, 0.0f);
    func_002C2210(obj + 0x10, 0xF, D_L30_001B1F0C, 1, -0xA, D_L30_001A8F20, 0, scale * 0.04f, scale * 0.4f, 0.0f);
    return obj;
}
