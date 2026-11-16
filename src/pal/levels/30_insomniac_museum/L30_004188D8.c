#include "include_asm.h"
#include "names.h"



extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long g_pad_pressed_flags;
extern char g_str_tweak_toggle_label[];
extern char g_str_tweak_value_label_a[];
extern char g_str_tweak_value_label_b[];
extern char g_str_tweak_value_label_c[];
extern char g_str_tweak_value_label_d[];
extern char g_str_tweak_value_label_e[];
extern char g_str_tweak_color_label_a[];
extern char g_str_tweak_color_label_b[];
extern char g_str_tweak_color_label_c[];
extern char g_str_tweak_flag_label_a[];
extern char g_str_tweak_flag_label_b[];
extern char g_str_tweak_flag_label_c[];
/* Spawns an explosion object at a position, aims it at the player, shakes the screen if close, then starts the particle burst (PAL version). */
char *museum_explosion_spawn_pal(void *, float, int, int, int, int, int, int, int, int, int, int);

/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


/* Updates a museum explosion test spot: with both buttons pressed in its zone it opens a tweak menu, and every 45 frames it spawns an explosion with the tweaked values (PAL version). */
void museum_explosion_tweak_update_pal(char *obj) {
    char *state = *(char **)(obj + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(obj + 0x1C) = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(state + 0x3C) != -1 && IsPointInCuboid(g_hero_position, *(int *)(state + 0x3C))) {
            ForceClaimNotice(1, 0x1338, 1);
            buttons = g_pad_pressed_flags;
            buttons &= 3;
            if (buttons == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(state + 0x2C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 4, g_str_tweak_toggle_label, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 12, g_str_tweak_value_label_a, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 16, g_str_tweak_value_label_b, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 20, g_str_tweak_value_label_c, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 24, g_str_tweak_value_label_d, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 28, g_str_tweak_value_label_e, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 32, g_str_tweak_color_label_a, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 36, g_str_tweak_color_label_b, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 40, g_str_tweak_color_label_c, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 48, g_str_tweak_flag_label_a, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 52, g_str_tweak_flag_label_b, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(state + 0x2C), state + 8, g_str_tweak_flag_label_c, 0, 0, 1);

        }
        ForceClaimNotice(1, 0, 1);
        menu = *(char **)(state + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            moby_set_state(obj, 1, -1);
        }
        break;
    }
    if (*(float *)(obj + 0x1C) >= 45.0f) {
        int color;
        *(int *)(obj + 0x1C) = 0;
        color = (*(int *)(state + 40) << 16) | (*(int *)(state + 36) << 8) | *(int *)(state + 32);
        *(char **)state = museum_explosion_spawn_pal(obj + 0x10, *(float *)(state + 4), *(int *)(state + 8), *(int *)(state + 12), *(int *)(state + 16), *(int *)(state + 20), *(int *)(state + 24), *(int *)(state + 28), *(int *)(state + 48), *(int *)(state + 52), *(int *)(state + 56), color);
    }
    *(float *)(obj + 0x1C) += 1.0f;
}


#include "common.h"
extern char *CreateMoby(int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void EmitMuseumExplosionParticles_pal(void *, void *);
extern struct Player153 {
    char pad[0x140];
    float position[4];
    char pad2[0x10];
    float shake_strength;
    int pad3;
    int shake_duration, shake_timer;
    char pad4[0x200];
    float forward[4];
} D_L30_001B9C80;
typedef struct {
    short life, initial_life, duration;
    short pad;
    float inner, outer, strength, scale;
    int sound, flash, a2, a3, a4, a5, a6, a8, color;
} State153;

char *museum_explosion_spawn_pal(void *pos, float scale, int shake, int a2, int a3, int a4, int a5, int a6, int sound, int a8, int a9, int color) {
    float direction[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float sphere[4] __attribute__((aligned(16)));
    float toward_player[4] __attribute__((aligned(16)));
    char *obj = CreateMoby(0x11E5);
    State153 *state;
    if (obj) {
        state = *(State153 **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        *(unsigned char *)(obj + 0x20) = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        FastVecSub(direction, g_camera_l30_state.position, obj + 0x10);
        vec_scale_to_length(direction, direction, 1.0f);
        cam_compute_view_direction(obj + 0x10, normal, 1);
        qcopy(obj + 0xC0, direction);
        FastVecCross(obj + 0xD0, obj + 0xC0, normal);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, 1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        state->initial_life = state->life = 50;
        state->inner = scale + scale;
        state->outer = scale * 4.0f;
        state->a2 = a2;
        state->a3 = a3;
        state->a4 = a4;
        state->a5 = a5;
        state->a6 = a6;
        state->a8 = a8;
        state->flash = a9;
        state->sound = sound;
        state->color = color;
        state->scale = scale;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (math_fast_helper_a(sphere, 128.0f) == 1) {
            state->duration = 8;
            state->strength = 0.125f;
            if (fast_vec_dist(pos, g_camera_l30_state.position) < 48.0f && shake) {
                g_camera_l30_state.shake_timer = 0;
                g_camera_l30_state.shake_duration = 33;
                g_camera_l30_state.shake_strength = 0.075f;
            }
            if (state->sound) {
                FastVecSub(toward_player, obj + 0x10, g_camera_l30_state.position);
                vec_scale_to_length(toward_player, toward_player, 1.0f);
                if (1.5707963705062866f - math_fast_angle_helper(FastVecDot(toward_player, g_camera_l30_state.forward)) < 0.45378565788269043f)
                    state->sound = 1;
                else
                    state->sound = 0;
            }
        } else {
            state->duration = 0;
            state->sound = 0;
        }
        EmitMuseumExplosionParticles_pal(obj, normal);
    }
    return obj;
}
