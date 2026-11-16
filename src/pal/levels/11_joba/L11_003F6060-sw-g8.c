#include "include_asm.h"

#include "common.h"
extern f32 g_orbit_enemy_start_z __attribute__((sda));
extern f32 g_orbit_enemy_alt_z __attribute__((sda));
extern f32 g_joba_orbit_accel __attribute__((sda));
extern f32 g_joba_orbit_speed_limit __attribute__((sda));
extern f32 g_joba_orbit_radius __attribute__((sda));
extern f32 FastAddRotations(f32,f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 *arena_get_center_point(s32);
extern void euler_rotation_basis(void *,void *);

/* Moves a Joba enemy around the arena: speeds its orbit angle up or down by its state, places
   it on the orbit circle around the arena centre and turns it to face along the orbit (PAL: 50
   Hz rates). */
void joba_enemy_update_orbit_pal(u8 *moby) {
    u8 *enemy = moby;
    u8 *vars = *(u8 **)(enemy + 0x68);
    f32 speed_limit, orbit_speed, trig_value;
    switch (*(u8 *)(enemy + 0x42)) {
    case 1:
        orbit_speed = *(f32 *)(vars + 0x254) - g_joba_orbit_accel * 6.981318e-06f;
        speed_limit = g_joba_orbit_speed_limit * 0.0003490659f;
        *(f32 *)(vars + 0x254) = orbit_speed;
        if (orbit_speed > speed_limit) *(f32 *)(vars + 0x254) = speed_limit;
        else if (orbit_speed < -speed_limit) *(f32 *)(vars + 0x254) = -speed_limit;
        *(f32 *)(vars + 0x250) = FastAddRotations(*(f32 *)(vars + 0x250), *(f32 *)(vars + 0x254));
        break;
    case 2:
        orbit_speed = *(f32 *)(vars + 0x254) + g_joba_orbit_accel * 6.981318e-06f;
        speed_limit = g_joba_orbit_speed_limit * 0.0003490659f;
        *(f32 *)(vars + 0x254) = orbit_speed;
        if (orbit_speed > speed_limit) *(f32 *)(vars + 0x254) = speed_limit;
        else if (orbit_speed < -speed_limit) *(f32 *)(vars + 0x254) = -speed_limit;
        *(f32 *)(vars + 0x250) = FastAddRotations(*(f32 *)(vars + 0x250), *(f32 *)(vars + 0x254));
        break;
    case 0: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: break;
    }
    if (*(u8 *)(enemy + 0x20) == 5 || *(u8 *)(enemy + 0x20) == 9) return;
    if (*(s32 *)(enemy + 0xB8)) {
        trig_value = math_fast_sin_or_cos_a(*(f32 *)(vars + 0x250));
        *(f32 *)(enemy + 0x10) = g_joba_orbit_radius * trig_value + arena_get_center_point(*(s32 *)(enemy + 0xB8))[0];
        trig_value = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x250));
        *(f32 *)(enemy + 0x14) = g_joba_orbit_radius * trig_value + arena_get_center_point(*(s32 *)(enemy + 0xB8))[1];
    }
    if (*(u8 *)(enemy + 0x95) == 2) {
        *(f32 *)(enemy + 0x18) = g_orbit_enemy_start_z;
        *(f32 *)(enemy + 0xF4) = -1.5707964897155762f;
        *(s32 *)(enemy + 0xF0) = 0;
        *(f32 *)(enemy + 0xF8) = *(f32 *)(vars + 0x250);
        euler_rotation_basis(enemy + 0xC0, enemy + 0xF0);
    } else if (*(u8 *)(enemy + 0x95) == 1) {
        *(f32 *)(enemy + 0x18) = g_orbit_enemy_alt_z;
        *(f32 *)(enemy + 0xF4) = 1.5707964897155762f;
        *(s32 *)(enemy + 0xF0) = 0;
        *(f32 *)(enemy + 0xF8) = FastAddRotations(3.1415927410125732f, *(f32 *)(vars + 0x250));
        euler_rotation_basis(enemy + 0xC0, enemy + 0xF0);
    }
}
