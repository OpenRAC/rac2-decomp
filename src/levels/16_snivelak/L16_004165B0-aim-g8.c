/* func_L16_00416FB0: own -G8 unit (default game profile by name). */
#include "common.h"

typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; } Hero;

/* The turret's tuning block at 0x001B1AD0: two muzzle offsets, then the aim offset whose w
   word is the ray radius, the shot speed (units per second), the projectile speed and the
   refire delay. Retail takes the two vectors' addresses $gp-relative (explicit SDATA views)
   and reads the radius as the aim vector's last word through the plain name, which the
   assembler keeps absolute (`lui $at`). */
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
extern char *func_L13_0040DC20(char *, char *, char *, s32, f32);

/* Once the refire timer runs out while a fire button is held: places the alternating muzzle
   and the aim point in the turret's frame, aims at the hit of a ray (or the camera-line
   collision point, or the far end of the camera line), spawns the projectile and rearms. */
void func_L16_00416FB0(char *self) {
    char muzzle[16], aim[16], far[16], near[16], velocity[16];
    char *vars = *(char **)(self + 0x68);
    f32 speed;

    if (!FastFloatHelperD(vars + 0x8C)) return;
    if (!(D_00138320 & 0xA0)) return;
    matrix_mul_vec3(muzzle, D_L16_001B1AD0_gp[*(s32 *)(vars + 0x88)], self + 0xC0);
    FastVecAdd(muzzle, muzzle, self + 0x10);
    matrix_mul_vec3(aim, D_L16_001B1AF0_gp, self + 0xC0);
    FastVecAdd(aim, aim, self + 0x10);
    vec_scale_to_length(near, D_L16_001B9B00 + 0x230, 2.0f);
    FastVecAdd(near, near, D_L16_001B9B00);
    vec_scale_to_length(far, D_L16_001B9B00 + 0x230, 120.0f);
    FastVecAdd(far, far, D_L16_001B9B00);
    *(s32 *)(self + 0x98) = 0;
    if (ProcessCollisionHit(aim, 0, ((Hero *)gHeroState)->ptr[0x2290 / 4], 0, D_L16_001B1AF0[3]) && D_L16_001BFF58)
        FastVecSub(velocity, D_L16_001BFF58 + 0x10, muzzle);
    else if (CollLine(near, far, 0, ((Hero *)gHeroState)->ptr[0x2290 / 4], 0))
        FastVecSub(velocity, D_L16_001BFF60, muzzle);
    else
        FastVecSub(velocity, far, muzzle);
    vec_scale_to_length(velocity, velocity, D_L16_001B1B00 * 0.01666666753590107f);
    speed = D_L16_001B1B04;
    *(s32 *)(self + 0x98) = *(s32 *)(*(char **)(self + 0x24) + 0x10);
    if (D_001A7A0A[0]) speed *= 5.0f;
    SpawnEA7Moby(self, velocity, muzzle, 0, speed);
    *(s32 *)(vars + 0x8C) = D_L16_001B1B08;
    *(s32 *)(vars + 0x88) = (*(s32 *)(vars + 0x88) + 1) & 1;
}
