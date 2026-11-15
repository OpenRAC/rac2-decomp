#include "common.h"
extern f32 D_L11_001B0540 __attribute__((sda));
extern f32 D_L11_001B0544 __attribute__((sda));
extern f32 D_L11_001B0550 __attribute__((sda));
extern f32 D_L11_001B0554 __attribute__((sda));
extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 FastAddRotations(f32,f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 *arena_get_center_point(s32);
extern void euler_rotation_basis(void *,void *);
/* Spins the enemy around its anchor point, speeding up in one direction, and turns it to
   face along its orbit. */
void joba_enemy_update_orbit(u8 *mobyArg) {
    u8 *moby = mobyArg;
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 limit, speed, trig;
    switch (*(u8 *)(moby + 0x42)) {
    case 1:
        speed = *(f32 *)(vars + 0x254) - D_L11_001B0550 * 0.000004848137447610265f;
        limit = D_L11_001B0554 * 0.0002908882452175021f;
        *(f32 *)(vars + 0x254) = speed;
        if (speed > limit) *(f32 *)(vars + 0x254) = limit;
        else if (speed < -limit) *(f32 *)(vars + 0x254) = -limit;
        *(f32 *)(vars + 0x250) = FastAddRotations(*(f32 *)(vars + 0x250), *(f32 *)(vars + 0x254));
        break;
    case 2:
        speed = *(f32 *)(vars + 0x254) + D_L11_001B0550 * 0.000004848137447610265f;
        limit = D_L11_001B0554 * 0.0002908882452175021f;
        *(f32 *)(vars + 0x254) = speed;
        if (speed > limit) *(f32 *)(vars + 0x254) = limit;
        else if (speed < -limit) *(f32 *)(vars + 0x254) = -limit;
        *(f32 *)(vars + 0x250) = FastAddRotations(*(f32 *)(vars + 0x250), *(f32 *)(vars + 0x254));
        break;
    case 0: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: break;
    }
    if (*(u8 *)(moby + 0x20) == 5 || *(u8 *)(moby + 0x20) == 9) return;
    if (*(s32 *)(moby + 0xB8)) {
        trig = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x250));
        *(f32 *)(moby + 0x10) = D_L11_001B0558 * trig + arena_get_center_point(*(s32 *)(moby + 0xB8))[0];
        trig = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x250));
        *(f32 *)(moby + 0x14) = D_L11_001B0558 * trig + arena_get_center_point(*(s32 *)(moby + 0xB8))[1];
    }
    if (*(u8 *)(moby + 0x95) == 2) {
        *(f32 *)(moby + 0x18) = D_L11_001B0540;
        *(f32 *)(moby + 0xF4) = -1.5707964897155762f;
        *(s32 *)(moby + 0xF0) = 0;
        *(f32 *)(moby + 0xF8) = *(f32 *)(vars + 0x250);
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    } else if (*(u8 *)(moby + 0x95) == 1) {
        *(f32 *)(moby + 0x18) = D_L11_001B0544;
        *(f32 *)(moby + 0xF4) = 1.5707964897155762f;
        *(s32 *)(moby + 0xF0) = 0;
        *(f32 *)(moby + 0xF8) = FastAddRotations(3.1415927410125732f, *(f32 *)(vars + 0x250));
        euler_rotation_basis(moby + 0xC0, moby + 0xF0);
    }
}
