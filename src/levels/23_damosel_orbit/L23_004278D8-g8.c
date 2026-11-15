#include "common.h"

/* func_L23_004278D8 is a unit of its own: it reads $gp (hence -g8), and it is built with -g,
   whose line label in front of the division makes the assembler pad it with retail's two nops
   (the effect func_L23_004160B0 uses). The division stays in a statement of its own.
   Measured on this body:
   - D_L23_001B36FC is a plain extern: it comes out absolute (`lui $at` + `lwc1`) outside a delay
     slot, as retail; marked sda it would be one $gp-relative load;
   - the particle emitter is func_L23_004160B0's, with its constants in the same order (90.0f,
     1/60, pi/180 as locals of the loop body) and `vec[2]` stored twice. */

extern u8 *D_L23_001B1484 __attribute__((sda));

extern s32 D_L23_001B1694 __attribute__((sda));

extern s32 D_0018C0B0 __attribute__((nosda));

extern float D_L23_001B36FC;

extern char D_L23_001BA500[];

extern u8 *func_002A9640(u8 *, s32, s32);

extern void func_00282978(u8 *);

extern s32 func_L23_0041E260(void);

extern s32 func_L23_0041B948(void);

extern void func_L23_0041E570(void);

extern void func_002AB800(u8 *, u8 *);

extern void func_002AB8C0(u8 *, u8 *);

extern void func_L23_0041C578(u8 *);

extern float func_002A78D8(float, float);

extern float func_00283B98(float, float);

extern float func_002A7878(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern u8 *func_00273730(u8 *, s32, s32, s32, u8 *, u8 *, float *, float, float, s32);

extern void func_00310C88(void);

/* Hit handler of the object: takes the damage of the object that hit it (unless the shield state
   or the hit filter rejects the hit), then spawns one particle per set bit of the mask word, at
   most ten, fewer the more of the timer is left. */
void func_L23_004278D8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *hit;
    s32 n;
    s32 i;
    float vec[3];

    hit = func_002A9640(moby, 0x30000, 1);
    moby[0xA8] = 0xFF;
    FastDecTimer(vars + 0x26);
    if (hit != 0) {
        if (func_L23_0041E260() == 0 || *(s16 *)(vars + 0x26) != 0 ||
            (D_L23_001B1484 != 0 && func_L23_0041B948() != 0) ||
            (*(s32 *)(hit + 0x20) == D_0018C0B0 && D_L23_001B1694 < 0)) {
            if (func_L23_0041B948() != 0)
                func_L23_0041E570();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(float *)(vars + 0x20) = *(float *)(vars + 0x20) - *(float *)(hit + 0x2C);
        if (*(float *)(vars + 0x20) > 0.0f) {
            vars[0x147] = 0xFF;
            func_002AB800(moby, vars + 0x140);
            func_L23_0041C578(*(u8 **)(hit + 0x20));
            if (*(s16 *)(*(u8 **)(hit + 0x20) + 0xAA) != 0x118F)
                *(s16 *)(vars + 0x26) = 0x14;
            if (*(u16 *)(moby + 0x7C) != 0) {
                float f;

                f = *(float *)(vars + 0x20) / D_L23_001B36FC;
                n = 10 - (s32)(f * 10.0f);
                for (i = 0; i < n; i++) {
                    s32 mask = *(u16 *)(moby + 0x7C);

                    if ((mask >> i) & 1) {
                        float angle, speed;
                        u8 *p;
                        u8 *base = (u8 *)D_L23_001BA500;
                        float spread = 90.0f;
                        float per_tick = 0.016666668f;
                        float to_rad = 0.017453294f;

                        *(u16 *)(moby + 0x7C) = mask & ~(1 << i);
                        angle = FastAddRotations(func_002A78D8(spread, 120.0f) * to_rad,
                                              *(float *)(base + 0x158));
                        speed = func_002A7878(2.0f, 4.0f) * per_tick;
                        vec[0] = func_00283180(angle) * speed;
                        vec[1] = func_00283198(angle) * speed;
                        vec[2] = 0.0f;
                        vec[2] = func_002A7878(5.0f, 8.0f) * per_tick;
                        p = func_00273730(moby, 1, *(s16 *)(moby + 0xAA), i, moby + 0x10, moby + 0xF0,
                                          vec, spread, 15.0f, 0xFF);
                        if (p != 0)
                            *(void (**)(void))(p + 0x64) = func_00310C88;
                    }
                }
            }
        }
    }
    func_002AB8C0(moby, vars + 0x140);
}
