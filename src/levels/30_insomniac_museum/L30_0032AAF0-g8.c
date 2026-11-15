#include "common.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry30;
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry30;
/* Reloaded at each search step in retail. */
extern struct { char pad[0x230]; int selected; } D_L30_001CA3A0;

extern int math_random_int_range(int, int);
extern float math_random_angle(void);
extern void gfx_draw_beam_quads_glows(void *, int, float, int, float, float, int, int, void *);
extern float D_L30_001B15AC __attribute__((sda));
extern float D_L30_001B15B0 __attribute__((sda));
extern int D_L30_001B15A4 __attribute__((sda));
extern int D_L30_001B15A8 __attribute__((sda));
extern int D_L30_001B156C __attribute__((sda));
extern int D_L30_001B1570 __attribute__((sda));

/* Small-data unit: every body here reaches a global through $gp, so the file is built
   with -G8 (the -g8.c name gives it that profile). */

extern float D_L30_001AEE90 __attribute__((sda));
extern float D_L30_001AEE94 __attribute__((sda));
extern char D_L30_001AEE98[];

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
extern float D_001B35B8;
extern int g_current_map_index;
extern float D_L30_001AEC24 __attribute__((sda));
extern float D_L30_001AEC2C __attribute__((sda));
extern float D_L30_001AEC28 __attribute__((sda));
extern float D_L30_001AEC20 __attribute__((sda));
extern int D_L30_001AEC18 __attribute__((sda));
extern int D_L30_001AEC10 __attribute__((sda));
extern int D_L30_001AEC1C __attribute__((sda));
extern int D_L30_001AEC14 __attribute__((sda));
extern int D_L30_001AEC08 __attribute__((sda));
extern float D_L30_001AEC0C __attribute__((sda));
extern int D_L30_001AEBB8 __attribute__((sda));
extern float D_00233A60[][24][24];

extern float IntToFloat(int);
extern int FloatToInt(float);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void museum_water_init_grid(void);
extern void museum_water_step_shape(void);
extern float math_l30_lerp_float(float, float, float);
extern void RaiseMuseumHeightFieldDome(int, int, float, float);
extern void DrawMuseumWaterGrid(void *);

extern char g_hero_state[];
extern char *D_001B2D1C __attribute__((sda));
extern void anim_start_blended(void *, int, int, int);
extern void cam_reset_entry(int);
extern void TryClaimNotice(int, int, int);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void museum_info_stand_advance_state(char *);

/* Updates the museum water pool (moby class 4504). It sets up the water surface, then ripples it, adds drops and draws it every frame. */
void museum_water_update(char *object) {
    int state = *(unsigned char *)(object + 0x20);

    switch (state) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(object + 0x18) += D_001B35B8;
        museum_water_init_grid();
        *(unsigned char *)(object + 0x30) = 0xFF;
        break;
    case 1:
        if (!(g_pad_state.f1A0 & 0x80))
            museum_water_step_shape();
        if (D_L30_001AEC24 >= D_L30_001AEC2C && math_random_int_below(200) == 1) {
            D_L30_001AEC24 = 0.0f;
            D_L30_001AEC18 += D_L30_001AEC10;
            D_L30_001AEC1C += D_L30_001AEC14;
            if (D_L30_001AEC18 < 4 || D_L30_001AEC18 > 20)
                D_L30_001AEC10 = -D_L30_001AEC10;
            if (D_L30_001AEC1C < 4 || D_L30_001AEC1C > 20)
                D_L30_001AEC14 = -D_L30_001AEC14;
            D_00233A60[D_L30_001AEBB8][D_L30_001AEC18][D_L30_001AEC1C] = D_L30_001AEC20;
        } else {
            FloatToInt(math_l30_lerp_float(IntToFloat(D_L30_001AEC18),
                                            IntToFloat(D_L30_001AEC18 + D_L30_001AEC10),
                                            D_L30_001AEC24));
            FloatToInt(math_l30_lerp_float(IntToFloat(D_L30_001AEC1C),
                                            IntToFloat(D_L30_001AEC1C + D_L30_001AEC14),
                                            D_L30_001AEC24));
        }
        D_L30_001AEC24 += D_L30_001AEC28;
        if (g_pad_state.f1A0 & 0x20)
            RaiseMuseumHeightFieldDome(12, 12, D_L30_001AEC08, D_L30_001AEC0C);
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

            STUB_printf(D_L30_001AEE98, class_id, extra_id);
            func_001163A0(ticks);
            *(int *)state = math_random_int_below(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        moby_set_state(object, 1, -1);
    } else {
        float f0 = D_L30_001AEE94;

        math_update_wrapped_angle_offset(object, state + 4, state + 8, D_L30_001AEE90,
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
                char *entry = D_001B2D1C + (*(int *)state << 8);

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
    scale = D_L30_001B15AC;
    scale *= *(float *)(object + 0x2C);
    value = math_random_int_range(95, 111);
    random = math_random_angle();
    gfx_draw_beam_quads_glows(object + 0x10, D_L30_001B156C, scale, value, random, 1.0f, D_L30_001B15A4, 2, object);
    scale2 = D_L30_001B15AC;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= D_L30_001B15B0;
    value2 = math_random_int_range(111, 127);
    random = math_random_angle();
    gfx_draw_beam_quads_glows(object + 0x10, D_L30_001B1570, scale2, value2, random, 1.0f, D_L30_001B15A8, 2, object);
}

extern float D_L30_001AEBC8 __attribute__((sda));
extern float D_L30_001AEBCC __attribute__((sda));
extern int D_L30_001AEBC0 __attribute__((sda));
extern int D_L30_001AEBC4 __attribute__((sda));
extern int D_L30_001AEBBC __attribute__((sda));

extern void StepMuseumHeightField(void);

/* Moves the water surface toward its next shape; when that is done it runs one step of the ripple simulation instead. */
void museum_water_step_shape(void) {
    if (0.95f <= D_L30_001AEBC8) {
        D_L30_001AEBC8 = D_L30_001AEBCC;
        StepMuseumHeightField();
        D_L30_001AEBC0 = D_L30_001AEBBC;
        D_L30_001AEBC4 = D_L30_001AEBB8;
    } else {
        int x;
        int y;

        D_L30_001AEBC0 = 2;
        D_L30_001AEBC4 = 2;
        for (x = 0; x < 24; x++) {
            for (y = 0; y < 24; y++) {
                D_00233A60[D_L30_001AEBC0][y][x] =
                    math_l30_lerp_float(D_00233A60[D_L30_001AEBBC][y][x],
                                      D_00233A60[D_L30_001AEBB8][y][x], D_L30_001AEBC8);
            }
        }
    }
    D_L30_001AEBC8 = D_L30_001AEBC8 + D_L30_001AEBCC;
}
