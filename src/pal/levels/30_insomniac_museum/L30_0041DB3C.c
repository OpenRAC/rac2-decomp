#include "include_asm.h"
#include "names.h"
extern char *museum_tweak_menu_spawn(void *);
extern void MuseumTweakMenuAddItem(void *, void *, void *, int, int, int);
extern char g_hero_position[];
extern long g_pad_pressed_flags;
extern int math_random_int_range(int, int);
extern void moby_set_state(void *, int, int);
extern int IsPointInCuboid(void *, int);
extern int ForceClaimNotice(int, int, int);
extern int flag_set_first_pending(void *);
extern unsigned char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern unsigned char *g_particle_l30_texture_table[];
extern char g_str_effect_pos_x[];
extern char g_str_effect_pos_y[];
extern char g_str_effect_pos_z[];
extern char g_str_effect_scale[];
extern char g_str_effect_color_red[];
extern char g_str_effect_color_green[];
extern char g_str_effect_color_blue[];
extern char g_str_effect_offset[];
extern char g_str_effect_alpha_a[];
extern char g_str_effect_alpha_b[];
extern char g_str_effect_size_a[];
extern char g_str_effect_size_b[];
extern char g_str_effect_gravity[];
extern char g_str_effect_particle_type[];
extern char g_str_effect_particle_frame[];
extern char g_str_effect_angle_a[];
extern char g_str_effect_angle_b[];
typedef struct { char pad[0x4c]; short minimum, maximum; } MuseumParticleBounds;

/* func_PAL_L30_0041DB3C, the PAL copy of func_L30_004186B0: the same C, where the third argument is scaled to 50 Hz
   and the colour is computed in a local before the call, so its first two loads come before the division. */
/* Updates a museum particle test spot: it opens a tweak menu for the particle settings and spawns a particle at random intervals (PAL version). */
void UpdateMuseumParticleTester_pal(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    MuseumParticleBounds *bounds = (MuseumParticleBounds *)vars;
    unsigned char *particle;
    int color;

    switch ((unsigned char)obj[0x20]) {
    case 0:
        if (bounds->maximum < 0) bounds->maximum = 0;
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0x48) != -1 && IsPointInCuboid(g_hero_position, *(int *)(vars + 0x48))) {
            ForceClaimNotice(1, 0x1338, 1);
            if ((g_pad_pressed_flags & 3) == 3) moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(obj)) {
            *(char **)(vars + 0x3C) = museum_tweak_menu_spawn(obj);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x00, g_str_effect_pos_x, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x04, g_str_effect_pos_y, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x08, g_str_effect_pos_z, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x10, g_str_effect_scale, 0, 1, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x14, g_str_effect_color_red, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x18, g_str_effect_color_green, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x1C, g_str_effect_color_blue, 0, 0, 255);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x20, g_str_effect_offset, 0, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x24, g_str_effect_alpha_a, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x28, g_str_effect_alpha_b, 0, 0, 127);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x2C, g_str_effect_size_a, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x30, g_str_effect_size_b, 1, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x34, g_str_effect_gravity, 1, -1000, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x40, g_str_effect_particle_type, 0, 0, 103);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x44, g_str_effect_particle_frame, 0, 0, 20);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x4C, g_str_effect_angle_a, 3, 0, 1000);
            MuseumTweakMenuAddItem(*(char **)(vars + 0x3C), vars + 0x4E, g_str_effect_angle_b, 3, 0, 1000);
        }
        ForceClaimNotice(1, 0, 1);
        if (*(char **)(vars + 0x3C) == 0
            || *(short *)(*(char **)(vars + 0x3C) + 0xAA) != 0x118A
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFE
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFD) {
            moby_set_state(obj, 1, -1);
        }
        break;
    }

    if ((*(float *)(vars + 0xC))-- == 0.0f) {
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        color = (*(int *)(vars + 0x1C) << 16) | (*(int *)(vars + 0x18) << 8) | *(int *)(vars + 0x14);
        particle = part_spawn_gravity_fade(obj + 0x10, vars, (*(int *)(vars + 0x10) * 5 + 2) / 6,
                                 color,
                                 *(int *)(vars + 0x20), *(int *)(vars + 0x24), *(int *)(vars + 0x28),
                                 *(float *)(vars + 0x2C) * 210000.0f, *(float *)(vars + 0x30) * 210000.0f,
                                 *(float *)(vars + 0x34), *(int *)(vars + 0x38));
        if (particle) {
            particle[9] = 0xFF;
            particle[2] = g_particle_l30_texture_table[*(int *)(vars + 0x40)][*(int *)(vars + 0x44)];
        }
    }
}
