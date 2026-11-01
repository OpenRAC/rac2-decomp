/* Closer C, 1 November 2026: 456/452, 40 rows. range < D ? range : D; the class table cast through unsigned keeps mult + addu
 * (as func_L00_003E4BF0); a struct hero is rebuilt in the loop as retail. Left: cc1 hoists D_00139568 and 5627.92f, retail neither.
 */
/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections -ffast-math (for min.s), as its own unit
 * src/game/00327B40-g8.c with that cflags line; take the marker out of 00327038.c.
 * Retail: 452 bytes; compiled: 444 bytes.
 * Coverage: us: 0/28 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Pushes every object in range (the smaller of a global radius and the state's) away
 * from the object, unless it is the hero or neither pushable nor flagged 0x4000.
 *
 * The test, the min.s, the query and the call sequence match. The loop differs in what
 * the loop optimiser hoists: retail keeps the class table base, 0xE0 and 1 in saved
 * registers and rebuilds &D_00189E20 and &D_00139568 (lui/addiu, then the offset) in
 * every iteration; cc1 hoists those two addresses (offsets folded) and base + 0x70.
 * Tried: a local game pointer in the loop; the class table as a 0xE0-byte struct or a
 * pointer sum; -mno-split-addresses on the unit (440 bytes); incomplete sda arrays for
 * any of the three tables (436-456 bytes).
 * Next: a spelling where the two addresses are not loop-invariant to loop.c.
 */

#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

/* The message an object is pushed with: the push vector, then its kind. */
typedef struct {
    f32 push[4];
    s32 unused10[2];
    u8 type;
    u8 strength;
    u16 source_kind;
    s32 unused1C;
    s32 active;
} PushMsg_327B40;

extern s32 D_001B0100 __attribute__((sda));
extern f32 D_001B00F4 __attribute__((sda));
extern u8 *D_001BF000[];
typedef struct { char prefix[0x70]; float damage; char tail[0x6C]; } Class_7B40;
extern Class_7B40 D_00239BA0[];
extern u8 D_00139568[];
typedef struct { char pad[0x2290]; u8 *target; } Hero_7B40;
extern Hero_7B40 D_00189E20;

extern int func_00277F48(float, void *, int, void *, void *);
extern int func_002AB1F0(unsigned char *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, u8 *, s32, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, int);

void func_00327B40(u8 *self)
{
    f32 dir[4] __attribute__((aligned(16)));
    PushMsg_327B40 msg __attribute__((aligned(16)));
    u8 *state = *(u8 **)(self + 0x68);
    f32 range;
    u8 *obj;
    int n;
    int i;

    if (*(s32 *)(state + 0x20) < D_001B0100 - 20)
        return;
    range = *(f32 *)(state + 0x24);
    range = range < D_001B00F4 ? range : D_001B00F4;
    n = func_00277F48(range, self + 0x10, 0, self, 0);
    for (i = 0; i < n; i++) {
        obj = D_001BF000[i];
        if (func_002AB1F0(obj) == 0 && (*(u16 *)(obj + 0x34) & 0x4000) == 0)
            continue;
        if (obj == D_00189E20.target)
            continue;
        func_00282CF0(dir, obj + 0x10, self + 0x10);
        func_00282F20(dir, dir, 1.0f);
        func_00282F20(msg.push, msg.push, 1.0f);
        func_002A8C00(msg.push, self, 0x830000, dir,
                      ((Class_7B40 *)((unsigned int)D_00239BA0 + D_00139568[0x20] * sizeof(Class_7B40)))->damage);
        *(TI128 *)msg.push = *(TI128 *)dir;
        msg.push[3] = 5627.9248046875f;
        msg.type = 5;
        msg.strength = 3;
        msg.source_kind = *(u16 *)(obj + 0xAA);
        msg.active = 1;
        func_002A8E20(obj, &msg);
        func_0032D758(obj, 0x20, *(s32 *)(self + 0xB8));
    }
}
