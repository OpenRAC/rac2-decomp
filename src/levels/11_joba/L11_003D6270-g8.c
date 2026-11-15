#include "include_asm.h"

#include "common.h"

extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);

extern s32 func_002A77E0(s32 arg0);

extern s32 func_L11_00440C80(s32 arg0);

extern s32 D_L11_001B056C __attribute__((sda));

extern s32 D_L11_001B058C __attribute__((sda));

extern f32 D_L11_001B0670;

extern void func_L11_003F33E0(u8 *arg0);

extern void func_L00_002E6EF8(void *arg0, u8 *arg1);

extern void func_L11_003F3CB8(u8 *arg0);

extern void func_L11_003F4F30(u8 *arg0);

extern void func_002AB8C0(u8 *arg0, void *arg1);

extern void func_002A0488(u8 *arg0, u32 arg1, u32 arg2, u32 arg3);

extern void func_002B0990(u8 *arg0, void *arg1, f32 arg2, s32 arg3, s32 arg4);

extern u8 *func_002A9640(s32 arg0, s32 arg1, s32 arg2);

extern f32 func_002A96A0(u8 *arg0, u8 *arg1);

extern void func_002AB800(u8 *arg0, u8 *arg1);

/* The prototype returns a value: that keeps $v0 busy after the call, as the retail has it. */
extern s32 func_002B3380(u8 *arg0, u8 *arg1, u8 *arg2);

extern s32 func_002B3BA8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5);

extern void func_L11_003F3098(u8 *arg0);

/* The 7.0 the timed effect is compared against, reached through $gp. */
extern f32 D_L11_001B0570 __attribute__((sda));

extern s32 D_L11_001FFA78[];

/* Runs the object's timer down, keeps the shared step counter in step with it, and retires
   the object when the timed effect is over. */
void func_L11_003F1DB0(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u32 off;
    f32 f2;

    if (*(u8 *)(s0 + 0x20) == 0) {
        return;
    }
    s1 = *(u8 **)(s0 + 0x68);
    s2 = func_002A9640(s0, 0x10000, 0);
    f2 = func_002A96A0(s0, s2);
    if (s2 != 0) {
        if (*(u8 *)(s0 + 0x20) >= 3) {
            *(f32 *)(s1 + 0x20) = *(f32 *)(s1 + 0x20) - f2;
            /* The index is a byte offset into the table: keeping it in a variable leaves
               the constant out of the symbol's address, as the retail has it. */
            off = *(u8 *)(s1 + 0x37) * 4 + 0xE0;
            *(s32 *)((u8 *)D_L11_001FFA78 + off) += (s32)(f2 * 32.0f);
            if (*(f32 *)(s2 + 0x2C) != 0.0f) {
                s3 = s1 + 0x70;
                func_002AB800(s0, s3);
                if (*(f32 *)(s2 + 0x2C) >= D_L11_001B0570 || *(f32 *)(s1 + 0x20) <= 0.0f) {
                    func_002AB800(s0, s3);
                    func_002A7750(s0, 8, -1);
                }
            }
        }
    }
    *(u8 *)(s0 + 0xA8) = 0xFF;
    func_002B3380(s0, s1 + 0x50, s1 + 0x20);
    if (*(u8 *)(s0 + 0x20) >= 2 && *(u8 *)(s1 + 0x2E) == 2) {
        *(s32 *)(s1 + 0x20) = 0;
        func_L11_003F3098(s0);
    }
    *(s32 *)(s1 + 0x258) = func_002B3BA8(s0, *(s32 *)(s1 + 0x25C), 0, 0, 200.0f, 200.0f);
}

/* Arms the object's two state records through two callbacks and the class setup, then, when
   the twin record is clear, starts the 0x2A0 animation. */

/* Retires the object and copies two measured state bytes into its state block. */
void func_L11_003F2D38(u8 *arg0) {
    u8 *s0 = arg0;
    s32 v1 = *(s32 *)(s0 + 0x68);
    if (*(u16 *)(v1 + 0x278) >= 2)
        return;
    if (*(u16 *)(v1 + 0x27A) >= 2)
        return;
    if (func_002A77E0(D_L11_001B058C) != 0
        && func_L11_00440C80(*(s32 *)(s0 + 0xB8)) < D_L11_001B056C) {
        func_002A7750(s0, 7, -1);
    } else {
        func_002A7750(s0, 6, -1);
    }
}

extern void func_00283098(void *out, void *in, void *matrix);

extern void func_00282CC0(void *out, void *in, void *matrix);

extern f32 func_00283248(f32 a0, f32 a1);

extern void func_002833F0(void *a0, void *a1);

extern s32 func_00283CF0(f32 a0);

extern void func_L11_00436910(u8 *a0, s32 a1, s32 a2);

extern void func_L11_004496A0(u8 *a0, s32 a1, s32 a2);

extern void func_L11_0044C328(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00452C58(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00454C78(u8 *a0, s32 a1, s32 a2);

extern void func_L11_00456438(u8 *a0, s32 a1);

extern u32 D_L11_001B0D9C __attribute__((sda));

extern u8 D_00189E20[];

/* Places the measured point on the state's three vertices, then walks them: each one gets
   its angle to the shared origin and the class call its identifier names. */
void func_L11_00417340(u8 *arg0) {
    u8 *s0 = arg0;
    u8 *s1 = *(u8 **)(s0 + 0x68);
    u8 *p;
    u8 *base;
    f32 loc[4];
    s32 total;
    s32 i;

    loc[0] = 0.0f;
    loc[1] = -9.0f;
    loc[2] = -3.0f;
    loc[3] = 0.0f;
    matrix_mul_vec3(loc, loc, s0 + 0xC0);
    FastVecAdd(loc, loc, s0 + 0x10);

    if (*(u8 **)(s1 + 0x10) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x10) = loc[0] - 2.0f;
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x14) = loc[1];
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x10) + 0x1C) = loc[3];
    }
    if (*(u8 **)(s1 + 0x14) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x10) = loc[0];
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x14) = loc[1] + 1.0f;
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x14) + 0x1C) = loc[3];
    }
    if (*(u8 **)(s1 + 0x18) != 0) {
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x10) = loc[0];
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x14) = loc[1] - 1.0f;
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x18) = loc[2];
        *(f32 *)(*(u8 **)(s1 + 0x18) + 0x1C) = loc[3];
    }

    base = D_00189E20;
    p = *(u8 **)(s1 + 0x10);
    total = 0;
    for (i = 0; i < 3; i++) {
        if (i == 1) {
            p = *(u8 **)(s1 + 0x14);
        }
        if (i == 2) {
            p = *(u8 **)(s1 + 0x18);
        }
        if (p == 0) {
            continue;
        }
        *(s32 *)(p + 0xF0) = 0;
        *(f32 *)(p + 0xF4) = 0.0f;
        *(f32 *)(p + 0xF8) = func_00283248(*(f32 *)(base + 0x80) - *(f32 *)(p + 0x10),
                                          *(f32 *)(base + 0x84) - *(f32 *)(p + 0x14));
        *(s32 *)(p + 0xFC) = 0;
        euler_rotation_basis(p + 0xC0, p + 0xF0);
        switch (*(s16 *)(p + 0xAA)) {
        case 0xD98:
            func_L11_004496A0(p, total, 0);
            break;
        case 0xDCF:
            func_L11_0044C328(p, total, 0);
            break;
        case 0xDF4:
            func_L11_00452C58(p, total, 0);
            break;
        case 0xDF7:
            *(f32 *)(p + 0x18) += 0.5f;
            func_L11_00454C78(p, FloatToInt((f32)total * 0.16666667f), 0);
            break;
        case 0xDF9:
            func_L11_00456438(p, total);
            break;
        case 0xD37:
            func_L11_00436910(p, total, 0);
            break;
        }
        total += D_L11_001B0D9C;
    }

    *(u8 **)(s1 + 0x10) = 0;
    *(u8 **)(s1 + 0x14) = 0;
    *(u8 **)(s1 + 0x18) = 0;
}
