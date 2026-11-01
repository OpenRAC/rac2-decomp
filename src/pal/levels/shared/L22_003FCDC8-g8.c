#include "include_asm.h"

#include "common.h"
extern f32 D_L22_001B0BA4 __attribute__((sda));
extern f32 D_L22_001B0BA8 __attribute__((sda));
extern f32 D_L22_001B0BB4 __attribute__((sda));
extern f32 D_L22_001B0B90 __attribute__((sda));
extern f32 D_L22_001B0B94 __attribute__((sda));
extern f32 D_L22_001B0B98 __attribute__((sda));
extern f32 D_L22_001B0BB0 __attribute__((sda));
extern u8 D_L22_001B9C80[];
extern void func_00283098(f32 *, f32 *, u8 *);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern f32 func_00283248(f32, f32);
extern f32 func_00282E80(u8 *, u8 *);
extern f32 func_00283B98(f32, f32);
extern void func_0029F338(void *);

/* Runs the object's speed ramp, then either tears it down (no controller slot, or a
 * slot of kind 0xFE/0xFD) or points it along the level's direction vector and stores
 * the turn it must make plus the angle it turns at. */
void func_PAL_L22_003FCDC8(u8 *a0) {
    u8 *obj = a0;
    u8 *ctl = *(u8 **)(obj + 0x68);
    u8 *sub = *(u8 **)(obj + 0x24);
    u8 *p;
    u8 *dst;
    u8 *buf;
    f32 v[8];
    f32 t;
    f32 x, y, z, angle, scale, control_speed;

    *(f32 *)(obj + 0x2C) = *(f32 *)(sub + 0x24)
        * (D_L22_001B0BA4 + (D_L22_001B0BA8 - D_L22_001B0BA4) * *(f32 *)(ctl + 0x18));
    p = *(u8 **)(ctl + 0x10);
    if (p == 0 || *(u8 *)(p + 0x20) == 0xFE || *(u8 *)(p + 0x20) == 0xFD) {
        func_0029F338(obj);
        return;
    }
    dst = obj + 0x10;
    control_speed = D_L22_001B0BB4;
    x = D_L22_001B0B90;
    y = D_L22_001B0B94;
    z = D_L22_001B0B98;
    *(f32 *)(ctl + 0xC) = control_speed;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    func_00283098(v, v, D_L22_001B9C80 + 0x230);
    buf = (u8 *)(v + 4);
    func_00282CC0(buf, (u8 *)v, D_L22_001B9C80);
    qcopy(dst, buf);
    *(f32 *)(obj + 0xF8) = func_00283248(*(f32 *)(ctl + 0x0) - *(f32 *)(obj + 0x10),
                                         *(f32 *)(ctl + 0x4) - *(f32 *)(obj + 0x14));
    t = func_00282E80(dst, ctl);
    angle = -func_00283248(t, *(f32 *)(ctl + 0x8) - *(f32 *)(obj + 0x18));
    scale = D_L22_001B0BB0;
    *(f32 *)(obj + 0xF4) = angle;
    *(f32 *)(obj + 0xF0) = func_00283B98(*(f32 *)(obj + 0xF0), scale * 0.0003490659f);
}
