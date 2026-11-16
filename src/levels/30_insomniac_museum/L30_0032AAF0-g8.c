#include "common.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry30;
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry30;
/* Reloaded at each search step in retail. */
extern struct { char pad[0x230]; int selected; } g_menu_l30_state;

extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows(void *, int, float, int, float, float, int, int, void *);
extern float g_dust_puff_scale __attribute__((sda));
extern float g_dust_puff_scale_mul __attribute__((sda));
extern int g_dust_puff_beam_flags __attribute__((sda));
extern int g_dust_puff_beam_flags_alt __attribute__((sda));
extern int g_dust_puff_effect_main __attribute__((sda));
extern int g_dust_puff_effect_side __attribute__((sda));

/* Small-data unit: every body here reaches a global through $gp, so the file is built
   with -G8 (the -g8.c name gives it that profile). */

extern float g_museum_look_angle_rate __attribute__((sda));
extern float g_museum_look_param __attribute__((sda));
extern char g_str_museum_look_debug[];

extern void STUB_printf(const char *, ...);
extern void func_001163A0(unsigned int);
extern int math_random_int_below(int);
extern void moby_set_state(u8 *, int, int);
extern void math_update_wrapped_angle_offset(u8 *, u8 *, u8 *, float, float, float);
extern float FastAddRotations(float, float);

typedef struct {
    unsigned char pad[0x1A0];
    unsigned int f1A0;
    unsigned int f1A4;
} D00138180_Flags;

extern D00138180_Flags g_pad_state;
extern float g_museum_water_offset;
extern int g_current_map_index;
extern float g_museum_water_ripple_timer __attribute__((sda));
extern float g_museum_water_ripple_threshold __attribute__((sda));
extern float g_museum_water_ripple_step __attribute__((sda));
extern float g_museum_water_wave_height __attribute__((sda));
extern int g_museum_water_pos_row __attribute__((sda));
extern int g_museum_water_step_row __attribute__((sda));
extern int g_museum_water_pos_col __attribute__((sda));
extern int g_museum_water_step_col __attribute__((sda));
extern int g_museum_water_dome_radius __attribute__((sda));
extern float g_museum_water_dome_height __attribute__((sda));
extern int g_museum_water_current_buffer __attribute__((sda));
extern float g_museum_water_grids[][24][24];

extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void museum_water_init_grid(void);
extern void museum_water_step_shape(void);
extern float math_l30_lerp_float(float, float, float);
extern void RaiseMuseumHeightFieldDome(int, int, float, float);
extern void DrawMuseumWaterGrid(void *);

extern char g_hero_state[];
extern char *g_museum_entries __attribute__((sda));
extern void anim_start_blended(void *, int, int, int);
extern void cam_reset_entry(int);
extern int TryClaimNotice(int, int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void museum_info_stand_advance_state(char *);

/* Updates the museum water pool (moby class 4504). It sets up the water surface, then ripples it, adds drops and draws it every frame. */
void museum_water_update(char *object) {
    int state = *(unsigned char *)(object + 0x20);

    switch (state) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(object + 0x18) += g_museum_water_offset;
        museum_water_init_grid();
        *(unsigned char *)(object + 0x30) = 0xFF;
        break;
    case 1:
        if (!(g_pad_state.f1A0 & 0x80))
            museum_water_step_shape();
        if (g_museum_water_ripple_timer >= g_museum_water_ripple_threshold && math_random_int_below(200) == 1) {
            g_museum_water_ripple_timer = 0.0f;
            g_museum_water_pos_row += g_museum_water_step_row;
            g_museum_water_pos_col += g_museum_water_step_col;
            if (g_museum_water_pos_row < 4 || g_museum_water_pos_row > 20)
                g_museum_water_step_row = -g_museum_water_step_row;
            if (g_museum_water_pos_col < 4 || g_museum_water_pos_col > 20)
                g_museum_water_step_col = -g_museum_water_step_col;
            g_museum_water_grids[g_museum_water_current_buffer][g_museum_water_pos_row][g_museum_water_pos_col] = g_museum_water_wave_height;
        } else {
            FloatToInt(math_l30_lerp_float(IntToFloat(g_museum_water_pos_row),
                                            IntToFloat(g_museum_water_pos_row + g_museum_water_step_row),
                                            g_museum_water_ripple_timer));
            FloatToInt(math_l30_lerp_float(IntToFloat(g_museum_water_pos_col),
                                            IntToFloat(g_museum_water_pos_col + g_museum_water_step_col),
                                            g_museum_water_ripple_timer));
        }
        g_museum_water_ripple_timer += g_museum_water_ripple_step;
        if (g_pad_state.f1A0 & 0x20)
            RaiseMuseumHeightFieldDome(12, 12, g_museum_water_dome_radius, g_museum_water_dome_height);
        gfx_add_draw_callback_first(DrawMuseumWaterGrid, object);
        break;
    }
}

/* Steps one record: with the state byte clear it copies the record's own angle into the
   state block, and once the state index reaches thirteen it redraws the record with a fresh
   random duration, a timer sample and the state block's new bit mask. With the state byte
   set it folds the shared angle words into the record and the state block instead, and
   counts the frame in the record's halfword at 0x96. */
/* Updates a museum object (moby class 4942) that picks a random look out of thirteen, turns a little each frame and counts frames. */
void museum_random_look_update(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    if (*(u8 *)(object + 0x20) == 0) {
        float height = *(float *)(object + 0x18);
        unsigned int index = *(unsigned int *)state;

        *(float *)(state + 0xC) = height;
        if (index >= 13) {
            short class_id = *(short *)(object + 0xAA);
            short extra_id = *(short *)(object + 0xB2);
            unsigned int ticks = T1_COUNT;

            STUB_printf(g_str_museum_look_debug, class_id, extra_id);
            func_001163A0(ticks);
            *(int *)state = math_random_int_below(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        moby_set_state(object, 1, -1);
    } else {
        float f0 = g_museum_look_param;

        math_update_wrapped_angle_offset(object, state + 4, state + 8, g_museum_look_angle_rate,
                      f0 * 0.000290888245f, *(float *)(state + 0xC));
        *(float *)(object + 0xF8) =
            FastAddRotations(*(float *)(object + 0xF8), 0.01745329424738884f);
        *(u16 *)(object + 0x96) = 0;
    }
    counter = *(u16 *)(object + 0x96);
    *(u16 *)(object + 0x96) = counter + 1;
}

/* Updates a museum info stand (moby class 2263). When the player stands at it, it shows a message and lets the player press a button to use it. */
void museum_info_stand_update(char *object) {
    char *hero;
    char *state = *(char **)(object + 0x68);
    int id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                anim_start_blended(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                anim_start_blended(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                cam_reset_entry(*(int *)(state + 0xC));
        }
        break;
    case 3:
        id = -1;
        if (g_current_map_index != 0x15 && g_current_map_index != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                id = 0x279C;
                break;
            case 1:
                id = 0x279D;
                break;
            }
        } else {
            id = 0x27ED;
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == object && *(int *)(hero + 0x340) != 0) {
            TryClaimNotice(8, id, 1);
            if (g_pad_state.f1A4 & 0x10) {
                char *entry = g_museum_entries + (*(int *)state << 8);

                museum_info_stand_advance_state(entry);
                hero_reset_position_and_direction(entry + 0x10, entry + 0xF0, 0x6F, 1);
                *(unsigned char *)(hero + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *hero_block = g_hero_state;

        if (*(int *)(hero_block + 0x2294) == 0x6F) {
            *(unsigned char *)(hero_block + 0x22B5) = 0;
            hero_reset_position_and_direction(hero_block + 0x80, hero_block + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}

/* Spawns two puffs of dust at the object's position, each with a random size. */
void part_spawn_dust_puff_pair(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = g_dust_puff_scale;
    scale *= *(float *)(object + 0x2C);
    value = math_random_int_range(95, 111);
    random = math_random_angle();
    gfx_draw_beam_quads_glows(object + 0x10, g_dust_puff_effect_main, scale, value, random, 1.0f, g_dust_puff_beam_flags, 2, object);
    scale2 = g_dust_puff_scale;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= g_dust_puff_scale_mul;
    value2 = math_random_int_range(111, 127);
    random = math_random_angle();
    gfx_draw_beam_quads_glows(object + 0x10, g_dust_puff_effect_side, scale2, value2, random, 1.0f, g_dust_puff_beam_flags_alt, 2, object);
}

extern float g_museum_water_blend_t __attribute__((sda));
extern float g_museum_water_blend_step __attribute__((sda));
extern int g_museum_water_front_buffer __attribute__((sda));
extern int g_museum_water_previous_buffer __attribute__((sda));
extern int g_museum_water_source_buffer __attribute__((sda));

extern void StepMuseumHeightField(void);

/* Moves the water surface toward its next shape; when that is done it runs one step of the ripple simulation instead. */
void museum_water_step_shape(void) {
    if (0.95f <= g_museum_water_blend_t) {
        g_museum_water_blend_t = g_museum_water_blend_step;
        StepMuseumHeightField();
        g_museum_water_front_buffer = g_museum_water_source_buffer;
        g_museum_water_previous_buffer = g_museum_water_current_buffer;
    } else {
        int x;
        int y;

        g_museum_water_front_buffer = 2;
        g_museum_water_previous_buffer = 2;
        for (x = 0; x < 24; x++) {
            for (y = 0; y < 24; y++) {
                g_museum_water_grids[g_museum_water_front_buffer][y][x] =
                    math_l30_lerp_float(g_museum_water_grids[g_museum_water_source_buffer][y][x],
                                      g_museum_water_grids[g_museum_water_current_buffer][y][x], g_museum_water_blend_t);
            }
        }
    }
    g_museum_water_blend_t = g_museum_water_blend_t + g_museum_water_blend_step;
}
