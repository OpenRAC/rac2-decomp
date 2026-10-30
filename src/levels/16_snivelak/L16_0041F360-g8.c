#include "common.h"
typedef int quad __attribute__((mode(TI)));
typedef union { quad q; struct { f32 x, y, z, w; } v; } RingPoint;
extern f32 D_L16_001B2008 __attribute__((sda));
extern u32 D_L16_001B2000 __attribute__((sda));
extern s32 D_L16_001B1FF8 __attribute__((sda));
extern u32 D_L16_001B2004[] MACRO_ADDR;
extern s32 D_L16_001B1FFC[] MACRO_ADDR;
extern f32 D_L16_001B200C[] MACRO_ADDR;
extern f32 D_L16_001B2010[] MACRO_ADDR;
extern f32 D_L16_001B2014[] MACRO_ADDR;
extern RingPoint D_L16_001A8F20 MACRO_ADDR;
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CC0(char *, char *, char *);
/* Integer-bank order: request, owner, flags, vector; independent f12: distance. */
extern void func_002A8C00(char *, char *, s32, char *, f32);
extern s32 func_002761F8(char *, char *, s32, char *, char *);
extern u32 func_00283D38(u32, u32, f32);
extern void func_L00_002EBE88(char *, s32, s32, s32, u32, u32, f32, f32, f32);

/* Constructs and clips the expanding ring, then draws its two surfaces. */
void func_L16_0041F360(char *self) {
    RingPoint points[33];
    RingPoint *point;
    /* The query copies 40 bytes. Retail initializes through +0x23 here;
     * +0x24..+0x27 is transported opaquely to the queue, not assumed padding. */
    char collision[48];
    char *st = *(char **)(self + 0x68);
    f32 angle;
    u32 inner, outer;
    s32 i, j, k;
    for (i = 0, point = points; i < 32; i++, point++) {
        angle = (f32)(i << 1) * 0.09817477315664291f - 3.141592741012573f;
        point->v.x = func_00283180(angle) * *(f32 *)(st + 0x2C);
        point->v.y = func_00283198(angle) * *(f32 *)(st + 0x2C);
        point->v.z = 0;
        func_00282CC0((char *)point, (char *)point, self + 0x10);
        point->v.w = D_L16_001B2008;
    }
    qcopy(&points[32], &points[0]);
    for (j = 0; j < 32; j++) {
        func_002A8C00(collision, self, 1, (char *)&D_L16_001A8F20, *(f32 *)(st + 0x28));
        collision[24] = 0;
        collision[25] = 1;
        *(u16 *)(collision + 26) = *(u16 *)(self + 0xAA);
        func_002761F8((char *)&points[j], (char *)&points[j + 1], 9, self, collision);
    }
    inner = func_00283D38(D_L16_001B2000 & 0xFFFFFF, D_L16_001B2000, *(f32 *)(st + 0x30));
    outer = func_00283D38(D_L16_001B2004[0] & 0xFFFFFF, D_L16_001B2004[0], *(f32 *)(st + 0x30));
    func_L00_002EBE88((char *)points, D_L16_001B1FF8, D_L16_001B1FFC[0], 33, inner, outer,
                      D_L16_001B2008, D_L16_001B200C[0], *(f32 *)(st + 0x34));
    for (k = 31; k >= 0; k--) points[k].v.w = D_L16_001B2010[0];
    func_L00_002EBE88((char *)points, D_L16_001B1FF8, D_L16_001B1FFC[0], 33, inner, outer,
                      D_L16_001B2010[0], D_L16_001B2014[0], -*(f32 *)(st + 0x34));
}
