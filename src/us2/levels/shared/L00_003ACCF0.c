#include "include_asm.h"
#include "names.h"

/* func_US2_L00_003ACCF0, the USA v2.00 copy of func_L00_003AB8B8: the same C, where the last call
 * becomes func_US2_L00_003AB8F8 and gains a fifth argument, 5. */

typedef struct {
    char pad[0x50];
    float angle;
    char tail[0x8C];
} AngleRecord_262570;

typedef struct {
    char pad[0x760];
    char pad2[0xBF8 - 0x760];
    void *pBF8;
    char pad3[0x2294 - 0xBFC];
    int i2294;
    char pad4[0x24EC - 0x2298];
    short h24EC;
} Res_189E20;

extern unsigned char g_seeker_weapon_index[];
extern AngleRecord_262570 g_weapon_l00_table[];
extern Res_189E20 g_hero_state;
extern char g_cam_follow_matrix[];
extern void vec_scale_to_length(void *, void *, float);
extern void vec_compute_object_to_target(void *, void *, void *, int, float);
extern char *effect_spawn_owned_moby_us2(void *, void *, void *, void *, int);

/* Fires the seeker effect from the hero's facing, aimed at the locked target when there is one (US2 copy of hero_fire_effect_from_facing). */
void hero_fire_effect_from_facing_us2(char *position, char *owner) {
    float velocity[4];
    float angle;
    AngleRecord_262570 *weapon;
    Res_189E20 *hero;
    void *target;

    weapon = &g_weapon_l00_table[g_seeker_weapon_index[0]];
    angle = weapon->angle * 0.01666666753590107f;
    if (g_hero_state.i2294 == 0x1D) {
        vec_scale_to_length(velocity, g_cam_follow_matrix, angle);
    } else if (g_hero_state.h24EC == 1) {
        vec_scale_to_length(velocity, owner + 0xD0, -angle);
    } else {
        vec_scale_to_length(velocity, (char *)&g_hero_state + 0x760, angle);
    }
    hero = &g_hero_state;
    target = 0;
    if (hero->pBF8 != 0) {
        vec_compute_object_to_target(hero->pBF8, position, velocity, 0, angle);
        target = hero->pBF8;
    }
    effect_spawn_owned_moby_us2(position, velocity, owner, target, 5);
}
