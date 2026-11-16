#include "names.h"
/* func_PAL_L04_00412AA0, the PAL copy of func_L04_0040E460: the same C, where rename func_L04_0040C0C0 becomes func_PAL_L04_00410678. */
#include "common.h"

extern char g_hero_position[];
extern signed char *g_moby_l04_pool __attribute__((sda));
extern void racer_release_sound_handles(int, unsigned char *);
extern void FastVecScale(void *, void *, float);
/* Integer and float arguments keep their order within each EE register bank. */
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int g_game_tick_counter[] __attribute__((sda));
extern int g_pad_pressed_flags;
extern float g_projection_scale_float;
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float ApproachValue(void *, float, float);
extern int math_fast_float_d(void *);
extern int vec_fast_helper_a(void *);
extern void moby_update_transform_history_followers(void *, int);
extern void level_init_pending_slot(void *, void *);
extern void level_append_record_to_table(void *, float, int, int);
extern void level_release_slot_list(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int snd_set_slot_field(int, int);
extern void UpdateViewContext(void);
extern int GetFirstMobyInGroup(void *, int, int, int);
extern int GetNextMobyInGroup(void *, void *, int, int);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
/* Frozen Batch A A04-table-select-76; acknowledged claim 8c4d82cfbf43e138ed35e757fdaeee3e7c4651fa684549ba9d5e8ac22c56d111. */
typedef unsigned char BatchA_A04_u8;

typedef unsigned int BatchA_A04_u32;

extern BatchA_A04_u32 g_current_map_index[] __attribute__((sda));

extern BatchA_A04_u8 g_game_flag_table[];

/* Steps the record's phase at +0x1FC down by 0.1 (wrapping up by 8 once it reaches -8) and
   draws the effect with it. */
void bike_animate_boost_flame_streak(void *arg0);

extern float math_fabs(float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void bike_animate_boost_flame_streak(void *);
extern void FastVecSub(void *, void *, void *);
extern float func_L00_002EE290(void *);
/* func_L04_004045E0 is in L04_00402D90-follower.c. */

/* func_L04_00407078 is in L04_00402D90-debris.c. */

/* func_L04_004073E8 is in L04_00402D90-trail.c. */

extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern int FloatToInt(float);
/* A04-table-select-76 freshly exact-verified under family reservation */
BatchA_A04_u32 race_get_course_win_count(BatchA_A04_u8 *a0);

/* A04-table-select family, incrementing form: bumps the state-selected byte */
/* shared native body of family A04-table-select: reads the state-selected byte */
/* A04-table-select family, incrementing form (second slot pair) */
extern BatchA_A04_u8 *g_particle_record_pool __attribute__((sda));

/* Sweeps the 0x800 packed 64-byte records, redrawing the four live kinds */
/* func_L04_0040A628 is in L04_00402D90-racers-g8.c. */

/* func_L04_0040A958 is in L04_00402D90-reset-g8.c. */

extern signed char *g_moby_l04_pool __attribute__((sda));

/* Retail reaches its record base off $gp (a small-data symbol), and the three
   state words at 0x48 of the record and of the indexed record. */
/* func_L04_0040AC98 reaches its global off $gp, so its body lives in
   L04_00402D90-g8.c. */

/* func_L04_0040ACA8 reaches one of its globals absolutely and another off $gp,
   so its body lives in L04_00402D90-g8.c. */

/* func_L04_0040BA68 reaches its small globals off $gp, so its body lives in
   L04_00402D90-select-g8.c. */

typedef unsigned int L04Quad __attribute__((mode(TI)));
/* The EE assigns the point, parameter and mode to a0-a2, and the two
 * float arguments to f12-f13, independently of their C interleaving. */
void func_PAL_L04_00410678(L04Quad *position, L04Quad *direction, int count, int mode);

extern void racer_emit_exhaust_particles();

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern float IntToFloat(int);

/* The five floats come first and the two ints last: the floats then go to
   f12-f16 and the ints to a1 and a2, and the int argument is set up after
   the float ones, as the retail code has it. */
/* The emitter table the object points at: the slot id at 0x644, then the
   four rows of four heights from 0x660 on. */
/* Walks the four rows of the emitter table: every row's height is lowered by
   the shared floor, the three threshold vectors are nudged by the row's share
   and handed to the particle scheduler, and a row that sinks too far is lifted
   back to the floor. */
void racer_emit_exhaust_particles(char *a0);

extern BatchA_A04_u8 g_sound_state[];

/* Releases the callback records this moby still holds: every handle slot that is set
   names a record of the callback table, and the one that belongs to this moby is
   handed to the release helper. Each slot is cleared afterwards. */
void racer_release_sound_handles(int a0, BatchA_A04_u8 *a1);

/* Inlining puts the literal rate straight into $f12, so each call loads it again. */
static inline void CallL00_00322AC0(void *state, float rate, int level, int slot)
{
    level_append_record_to_table(state, rate, level, slot);
}

void racer_update_boost_pal(unsigned char *m)
{
    float delta[4], rotation[16];
    unsigned char *item, *other;
    int red, green, blue;
    int period = 42;
    int alpha = 128;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    unsigned char *state;
    int *data;
    float wave, active, angle, sine, radius;
    unsigned int color;
    angle = IntToFloat(period);
    red = g_game_tick_counter[0] % period;
    {
        float phase = (float)red;
        wave = math_fast_sin_or_cos_b(((phase / angle) * 2.0f) * 3.1415927f + -3.1415927f);
    }
    red = FloatToInt(wave * 48.0f) + 104;
    green = FloatToInt(wave * 64.0f) + 208;
    blue = FloatToInt(wave * 24.0f) + 60;
    if (green > 255) green = 255;
    if (*(int *)(p + 0x278)) {
        ApproachValue(p + 0x27c, 0.20000002f, 0.008f);
        ApproachValue(p + 0x28c, 97.0f, 0.96631575f);
        if (*(int *)(p + 0x278)) math_fast_float_d(p + 0x278);
        moby_update_transform_history_followers(p + 0x4e0, 1);
        state = p + 0x4e0;
    } else {
        if ((m[0x20] == 3 || (g_pad_pressed_flags & 10)) && *(int *)(p + 0x338) < 25 && *(int *)(p + 0x33c) > 0) {
            *(int *)(p + 0x338) = 200;
            --*(int *)(p + 0x33c);
            if (m[0x20] != 3) snd_play_from_class_bank(0, 0, m, 0x474);
            if (!snd_is_voice_playing_for_owner(m, *(int *)(p + 0x714))) {
                if (m[0x20] != 3) *(int *)(p + 0x714) = PlayMobySound(15, 4, m);
                else {
                    *(int *)(p + 0x714) = PlayMobySound(24, 5, m);
                    snd_set_slot_field(*(int *)(p + 0x714), 0x400);
                }
            }
            if (*(unsigned char **)(p + 0x4c4)) {
                unsigned char *child = *(unsigned char **)(p + 0x4c4);
                unsigned char *childState = *(unsigned char **)(child + 0x68);
                if (*(float *)(p + 0x27c) <= 0.020000001f) *(int *)(childState + 0x1c0) = 0;
            }
            if (!*(int *)(p + 0x640)) {
                level_init_pending_slot(m, p + 0x4e0);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                CallL00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                *(int *)(p + 0x640) = 1;
            }
        }
        state = p + 0x4e0;
        if (math_fast_float_d(p + 0x338)) {
            active = 0.0f;
            level_release_slot_list(state);
            *(int *)(p + 0x640) = 0;
        } else {
            active = 1.0f;
            moby_update_transform_history_followers(state, 1);
        }
        ApproachValue(p + 0x27c, active * 0.120000005f, 0.002f);
        if (*(float *)(p + 0x27c) < 0.0f) *(float *)(p + 0x27c) = 0.0f;
        if (active > 0.5f) ApproachValue(p + 0x28c, 97.0f, 0.96631575f);
        else ApproachValue(p + 0x28c, 80.0f, 0.2439867f);
    }
    if (m[0x20] != 3) {
        float viewAngle = *(float *)(p + 0x28c);
        viewAngle *= 0.008726647f;
        sine = math_fast_sin_or_cos_b(viewAngle);
        sine /= math_fast_sin_or_cos_a(viewAngle);
        g_projection_scale_float = sine;
        UpdateViewContext();
    }
    if (*(int *)(p + 0x25c) != -1) {
        GetFirstMobyInGroup(&item, *(int *)(p + 0x25c), 0, 0);
        if (item) do {
            if (*(short *)(item + 0xaa) == 0xa99) {
                data = *(int **)(item + 0x68);
                FastVecSub(delta, item + 0x10, m + 0x10);
                if (*data == 0 && *(int *)(p + 0x33c) < 3 && func_L00_002EE290(delta) < 1.0f) {
                    ++*(int *)(p + 0x33c);
                    if (m[0x20] != 3) snd_play_from_class_bank(0, 0, m, 0xa99);
                    func_PAL_L04_00410678((L04Quad *)(item + 0x10), (L04Quad *)(p + 0x290), 8, 0);
                    *data = 250;
                }
            }
            GetNextMobyInGroup(&item, item, 0, 0);
        } while (item);
    }
    if (*(int *)(p + 0x254) != -1) {
        GetFirstMobyInGroup(&other, *(int *)(p + 0x254), 0, 0);
        if (other) {
            /* One four-term OR would be rebalanced by fold, so the terms join in steps. */
            unsigned int high = (alpha << 24) | (blue << 16);
            high |= green << 8;
            color = high | red;
            do {
                if (*(short *)(other + 0xaa) == 0x474) radius = 1.25f;
                else if (*(short *)(other + 0xaa) == 0xcef) radius = 3.75f;
                else goto next;
                *(unsigned short *)(other + 0x34) |= 16;
                *(unsigned int *)(other + 0x78) = color;
                if (!vec_fast_helper_a(other + 0xbc)) goto next;
                FastVecSub(delta, other + 0x10, g_hero_position);
                if (FastVecDot(delta, delta) > 20.0f) goto next;
                set_identity_matrix(rotation);
                matrix_from_basis_rows(rotation, other + 0xc0);
                transform_vector(delta, delta, rotation);
                if (!(math_fabs(delta[0]) < 2.8f) || !(math_fabs(delta[1]) < radius) || !(math_fabs(delta[2]) < 1.5f)) goto next;
                data = *(int **)(other + 0x68);
                *(int *)(p + 0x278) += *data;
                if (!snd_is_voice_playing_for_owner(m, *(int *)(p + 0x714))) {
                    if (m[0x20] != 3) *(int *)(p + 0x714) = PlayMobySound(15, 4, m);
                    else {
                        *(int *)(p + 0x714) = PlayMobySound(24, 5, m);
                        snd_set_slot_field(*(int *)(p + 0x714), 0x400);
                    }
                }
                if (m[0x20] != 3) PlayMobySound(12, 0, m);
                *(int *)(p + 0x650) = *data;
                other[0xbc] = 50;
                if (*(unsigned char **)(p + 0x4c4)) {
                    unsigned char *child = *(unsigned char **)(p + 0x4c4);
                    unsigned char *childState = *(unsigned char **)(child + 0x68);
                    if (*(float *)(p + 0x27c) <= 0.020000001f) *(int *)(childState + 0x1c0) = 0;
                }
                if (!*(int *)(p + 0x640)) {
                    level_init_pending_slot(m, p + 0x4e0);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 64, 1);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 48, 2);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 32, 3);
                    CallL00_00322AC0(p + 0x4e0, -0.7f, 16, 4);
                    *(int *)(p + 0x640) = 1;
                }
next:
                GetNextMobyInGroup(&other, other, 0, 0);
            } while (other);
        }
    }
}

/* func_L04_0040EC80 is in L04_00402D90-aim.c. */

/* func_L04_0040EF50 is in L04_00402D90-g8.c. */

