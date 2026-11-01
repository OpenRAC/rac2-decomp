#include "include_asm.h"

#include "common.h"
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;
extern f32 D_L16_001B1AD0_gp[][4] SDATA(D_L16_001B1AD0);
extern f32 D_L16_001B1AF0_gp[] SDATA(D_L16_001B1AF0);
extern f32 D_L16_001B1AF0[] MACRO_ADDR;
extern f32 D_L16_001B1B00 __attribute__((sda));
extern f32 D_L16_001B1B04 __attribute__((sda));
extern s32 D_L16_001B1B08 __attribute__((sda));
extern u32 D_00138320 __attribute__((nosda));
extern u8 D_001A7A0A[] __attribute__((sda));
extern char D_00189E20[];
extern char D_L16_001B9B00[];
extern char *D_L16_001BFF58 __attribute__((nosda));
extern char D_L16_001BFF60[];
extern s32 func_00282948(char *);
extern void func_00283098(char *, f32 *, char *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, f32);
extern s32 func_00277F48(char *, s32, char *, s32, f32);
extern s32 func_002761F8(char *, char *, s32, char *, s32);
extern void func_00282CF0(char *, char *, char *);
extern char *func_PAL_L13_00412518(char *, char *, char *, s32, f32);

/* Once the refire timer runs out while a fire button is held: places the alternating muzzle
   and the aim point in the turret's frame, aims at the hit of a ray (or the camera-line
   collision point, or the far end of the camera line), spawns the projectile and rearms. */
void func_PAL_L16_0041C1F0(char *self) {
    char muzzle[16], aim[16], far[16], near[16], velocity[16];
    char *st = *(char **)(self + 0x68);
    f32 speed;

    if (!func_00282948(st + 0x8C)) return;
    if (!(D_00138320 & 0xA0)) return;
    func_00283098(muzzle, D_L16_001B1AD0_gp[*(s32 *)(st + 0x88)], self + 0xC0);
    func_00282CC0(muzzle, muzzle, self + 0x10);
    func_00283098(aim, D_L16_001B1AF0_gp, self + 0xC0);
    func_00282CC0(aim, aim, self + 0x10);
    func_00282F20(near, D_L16_001B9B00 + 0x230, 2.0f);
    func_00282CC0(near, near, D_L16_001B9B00);
    func_00282F20(far, D_L16_001B9B00 + 0x230, 120.0f);
    func_00282CC0(far, far, D_L16_001B9B00);
    *(s32 *)(self + 0x98) = 0;
    if (func_00277F48(aim, 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], 0, D_L16_001B1AF0[3]) && D_L16_001BFF58)
        func_00282CF0(velocity, D_L16_001BFF58 + 0x10, muzzle);
    else if (func_002761F8(near, far, 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], 0))
        func_00282CF0(velocity, D_L16_001BFF60, muzzle);
    else
        func_00282CF0(velocity, far, muzzle);
    func_00282F20(velocity, velocity, D_L16_001B1B00 * 0.020000001f);
    speed = D_L16_001B1B04;
    *(s32 *)(self + 0x98) = *(s32 *)(*(char **)(self + 0x24) + 0x10);
    if (D_001A7A0A[0]) speed *= 5.0f;
    func_PAL_L13_00412518(self, velocity, muzzle, 0, speed);
    *(s32 *)(st + 0x8C) = ((s32)(D_L16_001B1B08) * 5 + 2) / 6;
    *(s32 *)(st + 0x88) = (*(s32 *)(st + 0x88) + 1) & 1;
}
