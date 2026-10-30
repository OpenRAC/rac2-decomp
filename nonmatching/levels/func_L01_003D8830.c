/* func_L01_003D8830 - 672 bytes, level 01 only. Spawns cfg.count particles on a
   ring around the object (D_L01_002A4E78 holds the emitter settings).

   Attempt, 30 October 2026: 672/672 bytes, 0/1 USA place (tools/check.py).
   Needs its own unit with -g (config/cflags.txt: -O2 -G0 -ffunction-sections -g)
   and `low = v / spread` on its own line: that reproduces retail's two nops
   before the second div.s (MATCHING-BLOCKERS 5). Two load orders still differ:
   - entry: retail loads startColor (lw $fp) before spilling obj (sw $a0,0x40($sp));
     cc1 spills first;
   - after func_00282CC0: retail loads pos[2] before cfg.height; cc1 loads height
     first.
   Tried without change: loading count before endColor, assigning the three
   settings after the declarations, the w stores before the z add, a struct
   instead of f32[4] for pos; `height + pos[2]` swaps the add as well; a
   countdown loop moves s4 into the prologue; -ffast-math, -frac2-qcopy(-barrier),
   -fno-sched-interblock, -O2 -G0 -g alone change nothing; -mno-split-addresses,
   -fno-schedule-insns and -mastra-keep-frame-order are worse. */

#include "common.h"

typedef struct {
    s32 startColor;    /* 0x00 */
    s32 endColor;      /* 0x04 */
    s32 altStartColor; /* 0x08 */
    s32 altEndColor;   /* 0x0C */
    f32 kind[2];       /* 0x10 */
    f32 duration[2];   /* 0x18 */
    f32 size[2];       /* 0x20 */
    f32 spread;        /* 0x28 */
    f32 rise;          /* 0x2C */
    s32 count;         /* 0x30 */
    f32 height;        /* 0x34 */
    f32 speed;         /* 0x38 */
    f32 lift;          /* 0x3C */
    f32 outer;         /* 0x40 */
    f32 inner;         /* 0x44 */
    f32 velW;          /* 0x48 */
    f32 accelW;        /* 0x4C */
} L01RingEmitter;
extern L01RingEmitter D_L01_002A4E78;
extern f32 func_002A7878(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00283098(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_00283CF0(f32);
extern s32 func_001163B0(void);
extern u8 *func_002BAA28(void *, void *, void *, s32, s32, s32, s32, s32, s32);

void func_L01_003D8830(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 vel[4] __attribute__((aligned(16)));
    f32 accel[4] __attribute__((aligned(16)));
    s32 start = D_L01_002A4E78.startColor;
    s32 n = D_L01_002A4E78.count;
    s32 end = D_L01_002A4E78.endColor;
    s32 i, a, b, c, alt;
    f32 r, v, low;
    u8 *part;

    for (i = 0; i < n; i++) {
        r = func_00283180(func_002A7878(-3.1415927f, 3.1415927f));
        r *= func_002A7878(D_L01_002A4E78.inner, D_L01_002A4E78.outer);
        pos[0] = r;
        r = func_00283198(func_002A7878(-3.1415927f, 3.1415927f));
        r *= func_002A7878(D_L01_002A4E78.inner, D_L01_002A4E78.outer);
        pos[1] = r;
        pos[2] = 0.0f;
        func_00283098(pos, pos, obj + 0xC0);
        v = D_L01_002A4E78.speed * ((D_L01_002A4E78.outer - func_00282DF0(pos)) * 0.016666668f) / D_L01_002A4E78.outer;
        low = v / D_L01_002A4E78.spread;
        func_00282F20(vel, pos, func_002A7878(low, v));
        vel[2] += func_002A7878(D_L01_002A4E78.lift / D_L01_002A4E78.rise, D_L01_002A4E78.lift) * 0.016666668f;
        qzero(accel);
        func_00282CC0(pos, pos, obj + 0x10);
        pos[2] += D_L01_002A4E78.height;
        vel[3] = D_L01_002A4E78.velW;
        accel[3] = D_L01_002A4E78.accelW;
        alt = func_001163B0() & 1;
        if (!alt && (func_001163B0() & 1)) {
            start = D_L01_002A4E78.altStartColor;
            end = D_L01_002A4E78.altEndColor;
        }
        a = func_00283CF0(func_002A7878(D_L01_002A4E78.kind[0], D_L01_002A4E78.kind[1]));
        b = func_00283CF0(func_002A7878(D_L01_002A4E78.duration[0], D_L01_002A4E78.duration[1]));
        c = func_00283CF0(func_002A7878(D_L01_002A4E78.size[0], D_L01_002A4E78.size[1]));
        part = func_002BAA28(pos, vel, accel, start, end, a, b, c, -1);
        if (part && alt)
            part[3] = 0x48;
    }
}
