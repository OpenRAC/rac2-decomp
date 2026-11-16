#include "include_asm.h"
#include "names.h"

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
extern char *effect_spawn_owned_moby(void *, void *, void *, void *);

/* Fires a weapon effect from the hero in the direction the hero is facing. */
char *hero_fire_effect_from_facing(char *position, char *moby) {
    float velocity[4];
    float angle;
    AngleRecord_262570 *timing;
    Res_189E20 *hero;
    void *owner;

    timing = &g_weapon_l00_table[g_seeker_weapon_index[0]];
    angle = timing->angle * 0.01666666753590107f;
    if (g_hero_state.i2294 == 0x1D) {
        vec_scale_to_length(velocity, g_cam_follow_matrix, angle);
    } else if (g_hero_state.h24EC == 1) {
        vec_scale_to_length(velocity, moby + 0xD0, -angle);
    } else {
        vec_scale_to_length(velocity, (char *)&g_hero_state + 0x760, angle);
    }
    hero = &g_hero_state;
    owner = 0;
    if (hero->pBF8 != 0) {
        vec_compute_object_to_target(hero->pBF8, position, velocity, 0, angle);
        owner = hero->pBF8;
    }
    return effect_spawn_owned_moby(position, velocity, moby, owner);
}


