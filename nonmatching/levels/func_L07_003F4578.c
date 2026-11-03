/* func_L07_003F4578: retained near miss, opus-1 (v2224), 3 November 2026.
   Profile: -O2 -G8 -ffunction-sections (own -g8.c unit; -g changes nothing).
   check.py: 1012/1012 bytes, 0/1 places (USA v1.01); 14 non-relocation rows
   differ, all in the `(segment + 1) % 32` block of the particle loop: the
   same instructions with different temporaries (retail seg+1 in a1, seg+32
   in a0, quotient v0, q<<5 v1) and sched2 order. In this build local-alloc
   ties the chain into three quantities ({t1,q,q<<5}, {seg+1,rem,rem*16},
   {-1,slt}); retail's registers fit an untied chain. `next` variables,
   operand order, a reused index and -g do not change it.
   Fixed here: one index per loop (the first loop's i in s1, the
   third's in s7), the second loop written count-up (loop.c reverses it, so
   the 31 init follows the pointer inits), MACRO_ADDR on D_L07_001A8F20 (the
   la stays in the loop, unsplit), and the parameter pairs: E70[] incomplete
   sda array read [0]/[1] (E74 = CONST lui form, out of delay slots), E78 as
   an sda scalar plus D_L07_001B0E78_4[] MACRO_ADDR alias for E7C (the
   D_L10_001B1390_4 convention). Earlier drafts named E64/E6C; retail
   reads 0x001B0E74/0x001B0E7C.
*/

#include "common.h"

typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct {
    Vector direction;
    u8 *owner;
    s32 flags;
    u8 type, count;
    u16 classId;
    f32 amount;
    s32 mode;
    f32 extra;
} Query;
typedef struct {
    Vector points[33];
    union { Query query; struct { Vector point, direction; } particle; } work;
} Frame;
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A8C00(void *, void *, s32, void *, f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern u32 func_00283D38(u32, u32, f32);
extern void func_L00_002EBE88(void *, s32, s32, s32, u32, u32, f32, f32, f32);
extern s32 func_L02_002F1658(void);
extern s32 func_002A7820(s32, s32);
extern f32 func_002A78D8(f32, f32);
extern s32 func_00283CF0(f32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern s32 func_002A77E0(s32);
extern void func_00282D08(void *, void *, void *, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void *func_002C16C0(void *, void *, s32, s32, s32, s32, f32, f32, f32, f32, f32);
extern u8 D_L07_001A8F20[] MACRO_ADDR;
extern s32 D_L07_001B0E54 __attribute__((sda));
extern u32 D_L07_001B0E58 __attribute__((sda));
extern s32 D_L07_001B0E70[] __attribute__((sda));
extern f32 D_L07_001B0E40 __attribute__((sda));
extern f32 D_L07_001B0E78 __attribute__((sda));
extern f32 D_L07_001B0E78_4[] MACRO_ADDR;
extern u32 D_L07_001B0E88 __attribute__((sda));
extern u32 D_L07_001B0E8C;
extern s32 D_L07_001B0E80 __attribute__((sda));
extern s32 D_L07_001B0E84;
extern f32 D_L07_001B0E90 __attribute__((sda));
extern f32 D_L07_001B0E94;

/* Sample a closed ring, perform its collision passes, then emit its particles. */
void func_L07_003F4578(u8 *object)
{
    Frame frame;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *position = object + 0x10;
    s32 i, j, k, segment, size, count;
    u32 color0, color1, color;
    f32 angle, life, step;

    for (i = 0; i < 32; i++) {
        angle = (f32)(i * 2) * 0.09817477f - 3.1415927f;
        frame.points[i].f[0] = func_00283180(angle) * *(f32 *)(state + 0x24);
        frame.points[i].f[1] = func_00283198(angle) * *(f32 *)(state + 0x24);
        frame.points[i].f[2] = 0.0f;
        if (*(u8 **)(state + 0x20) != 0)
            func_00283098(&frame.points[i], &frame.points[i], *(u8 **)(state + 0x20) + 0xC0);
        func_00282CC0(&frame.points[i], &frame.points[i], object + 0x10);
        frame.points[i].f[3] = D_L07_001B0E90;
    }
    qcopy(&frame.points[32], &frame.points[0]);
    for (j = 0; j < 32; j++) {
        func_002A8C00(&frame.work.query, object, 1, D_L07_001A8F20, *(f32 *)(state + 0x34));
        frame.work.query.type = 0;
        frame.work.query.count = 1;
        frame.work.query.classId = *(u16 *)(object + 0xAA);
        func_002761F8(&frame.points[j], &frame.points[j + 1], 9, object, &frame.work.query);
    }
    color0 = func_00283D38(D_L07_001B0E88 & 0xFFFFFF, D_L07_001B0E88, *(f32 *)(state + 0x28));
    color1 = func_00283D38(D_L07_001B0E8C & 0xFFFFFF, D_L07_001B0E8C, *(f32 *)(state + 0x28));
    func_L00_002EBE88(frame.points, D_L07_001B0E80, D_L07_001B0E84, 33,
                     color0, color1, D_L07_001B0E90, D_L07_001B0E94, *(f32 *)(state + 0x2C));
    if (!func_L02_002F1658())
        return;
    for (k = 0; (f32)k < (f32)D_L07_001B0E54 * *(f32 *)(state + 0x24); k++) {
        size = func_002A7820(D_L07_001B0E70[0], D_L07_001B0E70[1]);
        count = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        life = func_002A7878(D_L07_001B0E78, D_L07_001B0E78_4[1]) * 210000.0f;
        step = D_L07_001B0E40 * (1.0f / 60.0f);
        func_002AA2E8(&step, 0.0f, func_002A7878(0.0f, 2.0f) * (1.0f / 60.0f));
        segment = func_002A77E0(32);
        func_00282D08(&frame.work.particle.point, &frame.points[segment],
                     &frame.points[(segment + 1) % 32], func_002A7878(0.0f, 1.0f));
        func_00282CF0(&frame.work.particle.direction, &frame.work.particle.point, position);
        frame.work.particle.direction.f[2] = 0.0f;
        func_00282F20(&frame.work.particle.direction, &frame.work.particle.direction, step);
        frame.work.particle.point.f[3] = 2.0f;
        color = D_L07_001B0E58;
        func_00283D38(color & 0xFFFFFF, color, *(f32 *)(state + 0x28));
        func_002C16C0(&frame.work.particle.point, &frame.work.particle.direction,
                     size, (s32)color >> 24, color & 0xFFFFFF,
                     count, life, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}
