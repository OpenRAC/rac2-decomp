#include "include_asm.h"
#include "names.h"
extern int g_museum_tweak_menu_active __attribute__((sda));
extern short g_menu_command_flag;
extern unsigned long long g_pad_state[];
extern unsigned char g_tweak_item_types[];
extern void *g_tweak_item_ptrs[];
extern int g_tweak_item_ranges[][2];
extern void func_2EDB20(void *, void *);
extern void func_323FB0(void *, int, int);
extern void museum_tweak_menu_draw(char *);
extern int func_326868(void *, int);
extern int func_32B1B0(int, int, int);
extern void func_320FD0(void *, int, int);
extern int func_32C070(void *);
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
char *museum_explosion_spawn(void *, float, int, int, int, int, int, int, int, int, int, int);
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

extern void VU1_addGSregister(int, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);
extern struct { char pad[0x150]; short x, y; } g_screen_adjust_offsets;
extern void gfx_l05_draw_jittered_billboard_quad(void *, int, float, float, float, float, float, int);

extern void func_42C028(int);
extern void func_316DB8(char *);
extern int g_slot_index_first;

/* Restores a saved setting and removes the helper object this object created. */
void museum_effect_object_release(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    func_42C028(3);
    g_slot_index_first = *(int *)(vars + 0x5C);
    func_316DB8(*(char **)(vars + 0x50));
}


/* Updates the tuning menu: draws it, moves the cursor, and changes the chosen value with left and right. */
void museum_tweak_menu_update(char *moby) {
    int *vars = *(int **)(moby + 0x68);
    int step = 0;
    g_museum_tweak_menu_active = 1;
    g_menu_command_flag = 5;
    func_2EDB20(museum_tweak_menu_draw, moby);
    if (g_pad_state[0x1A0 / 8] & 0x9000000000ULL) {
        func_316DB8(moby);
        return;
    }
    if (((int *)g_pad_state)[0x1A4 / 4] & 0x4000) {
        func_323FB0(vars, vars[1] - 1, 1);
        if (vars[2] < vars[0] - 15) vars[2]++;
    } else if (((int *)g_pad_state)[0x1A4 / 4] & 0x1000) {
        func_323FB0(vars, 0, 1);
        if (vars[0] < vars[2]) vars[2]--;
    } else if (((int *)g_pad_state)[0x1A0 / 4] & 0x2000) {
        step = (((int *)g_pad_state)[0x1A0 / 4] & 15) ? 5 : 1;
    } else if (((int *)g_pad_state)[0x1A0 / 4] & 0x8000) {
        step = (((int *)g_pad_state)[0x1A0 / 4] & 15) ? -5 : -1;
    }
    if (step && *(unsigned short *)(moby + 0x96) >= 5) {
        *(unsigned short *)(moby + 0x96) = 0;
        switch (g_tweak_item_types[vars[0]]) {
        case 0: {
            int value = *(int *)g_tweak_item_ptrs[vars[0]];
            value += step;
            if (value > g_tweak_item_ranges[vars[0]][1]) value = g_tweak_item_ranges[vars[0]][1];
            else if (value < g_tweak_item_ranges[vars[0]][0]) value = g_tweak_item_ranges[vars[0]][0];
            *(int *)g_tweak_item_ptrs[vars[0]] = value;
            break;
        }
        case 1: {
            float value = *(float *)g_tweak_item_ptrs[vars[0]] + step * 0.01f;
            if (value > g_tweak_item_ranges[vars[0]][1]) value = g_tweak_item_ranges[vars[0]][1];
            else if (value < g_tweak_item_ranges[vars[0]][0]) value = g_tweak_item_ranges[vars[0]][0];
            *(float *)g_tweak_item_ptrs[vars[0]] = value;
            break;
        }
        case 2: {
            unsigned char value = *(unsigned char *)g_tweak_item_ptrs[vars[0]];
            value += step;
            if (value > g_tweak_item_ranges[vars[0]][1]) value = g_tweak_item_ranges[vars[0]][1];
            else if (value < g_tweak_item_ranges[vars[0]][0]) value = g_tweak_item_ranges[vars[0]][0];
            *(unsigned char *)g_tweak_item_ptrs[vars[0]] = value;
            break;
        }
        case 3: {
            short value = *(short *)g_tweak_item_ptrs[vars[0]];
            value += step;
            if (value > g_tweak_item_ranges[vars[0]][1]) value = g_tweak_item_ranges[vars[0]][1];
            else if (value < g_tweak_item_ranges[vars[0]][0]) value = g_tweak_item_ranges[vars[0]][0];
            *(short *)g_tweak_item_ptrs[vars[0]] = value;
            break;
        }
        }
    }
    (*(unsigned short *)(moby + 0x96))++;
}


/* func_L30_00413528 is defined in L30_00413528.c. */

/* func_L30_004135A0 is defined in L30_004135A0-g8.c. */


/* Updates the explosion tester: opens the tuning menu on a button press and spawns a test explosion every 45 frames. */
void UpdateMuseumExplosionTester(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *menu;
    long buttons;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(int *)(moby + 0x1C) = 0;
        func_320FD0(moby, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0x3C) != -1 && func_326868(g_hero_position, *(int *)(vars + 0x3C))) {
            func_32B1B0(1, 0x27E6, 1);
            buttons = g_pad_pressed_flags;
            buttons &= 3;
            if (buttons == 3) func_320FD0(moby, 2, -1);
        }
        break;
    case 2:
        if (func_32C070(moby)) {
            *(char **)(vars + 0x2C) = museum_tweak_menu_spawn(moby);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 4, g_str_tweak_toggle_label, 1, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 12, g_str_tweak_value_label_a, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 16, g_str_tweak_value_label_b, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 20, g_str_tweak_value_label_c, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 24, g_str_tweak_value_label_d, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 28, g_str_tweak_value_label_e, 0, 0, 50);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 32, g_str_tweak_color_label_a, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 36, g_str_tweak_color_label_b, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 40, g_str_tweak_color_label_c, 0, 0, 255);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 48, g_str_tweak_flag_label_a, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 52, g_str_tweak_flag_label_b, 0, 0, 1);
            MuseumTweakMenuAddItem(*(void **)(vars + 0x2C), vars + 8, g_str_tweak_flag_label_c, 0, 0, 1);

        }
        func_32B1B0(1, 0, 1);
        menu = *(char **)(vars + 0x2C);
        if (!menu || *(short *)(menu + 0xAA) != 0x118A /* moby class 4490 */ || *(unsigned char *)(menu + 0x20) == 0xFE || *(unsigned char *)(menu + 0x20) == 0xFD) {
            func_320FD0(moby, 1, -1);
        }
        break;
    }
    if (*(float *)(moby + 0x1C) >= 45.0f) {
        int color;
        *(int *)(moby + 0x1C) = 0;
        color = (*(int *)(vars + 40) << 16) | (*(int *)(vars + 36) << 8) | *(int *)(vars + 32);
        *(char **)vars = museum_explosion_spawn(moby + 0x10, *(float *)(vars + 4), *(int *)(vars + 8), *(int *)(vars + 12), *(int *)(vars + 16), *(int *)(vars + 20), *(int *)(vars + 24), *(int *)(vars + 28), *(int *)(vars + 48), *(int *)(vars + 52), *(int *)(vars + 56), color);
    }
    *(float *)(moby + 0x1C) += 1.0f;
}

/* func_L30_004153D8 is defined in L30_004153D8.c. */

/* func_L30_004158B0 is defined in L30_004158B0-g8.c. */

/* func_L30_00416A88 is defined in L30_00416A88-g8.c. */

/* func_L30_00416D88 is defined in L30_00416D88-g8.c. */

/* func_L30_00417988 is defined in L30_00417988-g8.c. */

typedef unsigned short u16;

extern char *func_316A50(int);
extern void func_32BFF0(void *, void *);
extern void func_2F56B0(void *, void *);

/* Creates a helper effect object linked to this one and stores it in this object's variables. */
void museum_effect_object_spawn(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *spawned;

    spawned = func_316A50(0xB28 /* moby class 2856 */);
    if (spawned == 0) return;
    func_32BFF0(spawned, moby);
    func_2F56B0(spawned + 0xC0, spawned + 0xF0);
    *(u16 *)(spawned + 0x34) |= 0x100;
    *(char **)(vars + 0x50) = spawned;
}


/* Updates the particle tester: opens the tuning menu on a button press and emits a test particle at random intervals. */
void UpdateMuseumParticleTester(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    MuseumParticleBounds *bounds = (MuseumParticleBounds *)vars;
    unsigned char *particle;

    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (bounds->maximum < 0) bounds->maximum = 0;
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (*(int *)(vars + 0x48) != -1 && IsPointInCuboid(g_hero_position, *(int *)(vars + 0x48))) {
            ForceClaimNotice(1, 0x27E6, 1);
            if ((g_pad_pressed_flags & 3) == 3) moby_set_state(moby, 2, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            *(char **)(vars + 0x3C) = museum_tweak_menu_spawn(moby);
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
            || *(short *)(*(char **)(vars + 0x3C) + 0xAA) != 0x118A /* moby class 4490 */
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFE
            || (unsigned char)(*(char **)(vars + 0x3C))[0x20] == 0xFD) {
            moby_set_state(moby, 1, -1);
        }
        break;
    }

    if ((*(float *)(vars + 0xC))-- == 0.0f) {
        if (bounds->minimum > bounds->maximum) bounds->minimum = bounds->maximum;
        else if (bounds->minimum < 0) bounds->minimum = 0;
        *(float *)(vars + 0xC) = math_random_int_range(bounds->minimum, bounds->maximum);
        particle = part_spawn_gravity_fade(moby + 0x10, vars, *(int *)(vars + 0x10),
                                 (*(int *)(vars + 0x1C) << 16) | (*(int *)(vars + 0x18) << 8) | *(int *)(vars + 0x14),
                                 *(int *)(vars + 0x20), *(int *)(vars + 0x24), *(int *)(vars + 0x28),
                                 *(float *)(vars + 0x2C) * 210000.0f, *(float *)(vars + 0x30) * 210000.0f,
                                 *(float *)(vars + 0x34), *(int *)(vars + 0x38));
        if (particle) {
            particle[9] = 0xFF;
            particle[2] = g_particle_l30_texture_table[*(int *)(vars + 0x40)][*(int *)(vars + 0x44)];
        }
    }
}

/* Draws a screen flash and fades a light near the end of a countdown. */
void museum_draw_countdown_effect(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    if (*(short *)(vars + 2) - *(short *)vars < 2 && *(short *)(vars + 4)) {
        if (*(int *)(vars + 0x1C)) {
            VU1_addGSregister(0x42, 0x48);
            gfx_draw_colored_rectangle(0, g_screen_adjust_offsets.y, 0, g_screen_adjust_offsets.x, (unsigned long)(int)0x80808080);
        }
    }
    if (*(int *)(vars + 0x18)) {
        if (*(short *)(vars + 2) - *(short *)vars < 10) {
            float blend = (*(short *)(vars + 2) - *(short *)vars) * 0.1f;
            gfx_l05_draw_jittered_billboard_quad(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        } else if ((unsigned short)(*(unsigned short *)vars - 0x2E) < 4) {
            float blend = (*(short *)vars - 0x2D) * 0.1f;
            gfx_l05_draw_jittered_billboard_quad(moby + 0x10, 0x3C, *(float *)(vars + 8) + (*(float *)(vars + 12) - *(float *)(vars + 8)) * blend, 0.5f, 0.0f, 0.0f, 0.0f, 0);
        }
    }
}

extern int func_2F4B08(char *);
extern void func_2EDD78(void *, char *);
extern void screen_flash_and_glow_draw(char *);

/* Runs the next step once the first check passes, otherwise removes this object. */
void museum_run_follow_up_step(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    if (func_2F4B08(vars) == 0) {
        func_2F4B08(vars + 4);
        func_2EDD78((void *)screen_flash_and_glow_draw, moby);
    } else {
        func_316DB8(moby);
    }
}

/* func_L30_0041B848 is defined in L30_0041B848.c. */
