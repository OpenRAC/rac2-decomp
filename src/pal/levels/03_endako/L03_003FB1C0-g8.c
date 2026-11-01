#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern void func_L03_003F6918(u8 *, int);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00280B90(void *, void *, int);
extern Vector D_L03_001B10A0[4] __attribute__((sda));
extern float D_L03_001B10E0[8] __attribute__((sda));
extern float D_L03_001B10E4[] MACRO_ADDR;
extern int D_L03_001B1100[2] __attribute__((sda));
extern float D_L03_001B1064 __attribute__((sda));
extern u8 D_L03_001B9980[];

/* Removes inactive targets and draws a textured quad at each remaining target. */
void func_PAL_L03_003FB1C0(u8 *self) {
    struct { Vector a, b, c, pos; } frame;
    /* The initializer writes four 64-bit state words at +0x70..+0x88. */
    struct { Vector v[4]; int color[4]; float uv[4][2]; long state[4]; } packet;
    u8 *st = *(u8 **)(self + 0x68);
    int i, j, k;
    float scale;

    for (i = 0; i < *(int *)(st + 0x3BC); i++) {
        u8 *obj = *(u8 **)(st + 0x340 + i * 4);
        if (!obj || *(s16 *)(obj + 0xAA) != 0xA72 || obj[0x20] == 0xFE || obj[0x20] == 0xFD)
            func_L03_003F6918(self, i);
    }
    if (*(int *)(st + 0x3BC) == 0)
        return;
    func_00281DE8(&packet, 5, 1, 0x80);
    for (j = 0; j < 4; j++) {
        qcopy(&packet.v[j], &D_L03_001B10A0[j]);
        packet.color[j] = D_L03_001B1100[j >> 1];
        packet.uv[j][0] = D_L03_001B10E0[j * 2];
        packet.uv[j][1] = D_L03_001B10E4[j * 2];
    }
    scale = D_L03_001B1064 * 0.020000001f;
    for (k = 0; k < *(int *)(st + 0x3BC); k++) {
        u8 *obj = *(u8 **)(st + 0x340 + k * 4);
        u8 *data = *(u8 **)(obj + 0x68);
        qcopy(&frame.pos, obj + 0x10);
        frame.pos.f[3] = 1.0f;
        func_00282CF0(&frame.a, D_L03_001B9980, &frame.pos);
        func_00282F20(&frame.b, data, (float)*(s16 *)(data + 0x12) * scale);
        func_00282DD8(&frame.c, &frame.b, &frame.a);
        func_00282F20(&frame.c, &frame.c, 1.0f);
        func_00282DD8(&frame.a, &frame.b, &frame.c);
        func_00280B90(&packet, &frame.a, 0);
    }
}
