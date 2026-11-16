#include "names.h"
/* The incomplete SDA array keeps the particle vector address together;
 * -frac2-hazard-labels retains the visibility join on its required hazard nop.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; s32 i[4]; } ControllerScratch;
extern u8 *g_moby_l02_pool;
extern u8 *g_matrix_l02_record_table;
extern u8 g_camera_l02_position[];
extern u8 g_moby_group_flags[];
extern s32 g_current_map_index __attribute__((sda));
typedef union { u8 b[0x2400]; u8 *ptr[0x900]; void *v[0x900]; TI128 q[0x240]; } Hero;
extern Hero g_hero_state;
extern TI128 g_scratch_vec;
extern float g_zero_l02_vector[] __attribute__((sda));
extern void moby_set_group_enabled(s32, s32);
extern float math_random_angle(void);
extern float vec_distance_xy(void *, void *);
extern void moby_set_state(u8 *, u8, s32);
extern s32 moby_is_state_two(u8 *);
extern float ApproachValue(float *, float, float);
extern void moby_mark_spawned(void *);
extern void moby_mark_table_entry_flagged(u32);
extern void level_capture_checkpoint_state(void *, void *);
extern s32 CollLine(void *, void *, s32, void *, s32);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern void *part_spawn_hero_relative(void *, void *, u32, s32, s32, s32, float);
extern void scale_vector(float *, u8 *, float);
extern s32 math_fast_helper_a(float *, float);
extern float FastAddRotations(float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void energy_gate_draw_effect(u8 *);

/* Track the four linked actors and fade the controller's visible effect. */
/* Update handler of moby class 3201: it removes itself and its four partners once they are all gone. */
void energy_gate_update(u8 *object)
{
    ControllerScratch scratch[2];
    u8 *state = *(u8 **)(object + 0x68);
    s32 *ids;
    float *phase;

    switch (object[0x20]) {
    case 0:
        {
        s32 i;
        if (g_moby_group_flags[object[0xB0] + (g_current_map_index << 4)] & 0x80) {
            moby_set_group_enabled(*(s32 *)(state + 0x10), 1);
            moby_mark_spawned(object);
            return;
        }
        *(float *)(state + 0x1C) = 1.0f;
        *(float *)(state + 0x2C) = math_random_angle();
        *(s32 *)(state + 0x20) = 0;
        *(float *)(state + 0x24) = 0.5f;
        {
        float visible = vec_distance_xy(g_camera_l02_position, object + 0x10) > 66.0f ? 0.0f : 1.0f;
        *(float *)(state + 0x1C) = visible;
        }
        i = 3;
        phase = (float *)(state + 0x3C);
        do { *phase-- = 1.0f; } while (--i >= 0);
        object[0x30] = 0x65;
        moby_set_state(object, 1, -1);
        object[0x31] = 0;
        *(u16 *)(object + 0x34) |= 1;
        break;
        }
    case 1:
        {
            s32 ready = 1;
            s32 i;
            for (i = 0, ids = (s32 *)state; i < 4; i++) {
                if (!moby_is_state_two(g_moby_l02_pool + (*ids << 8))) {
                    ready = 0;
                    break;
                }
                ids++;
            }
            if (ready)
                moby_set_state(object, 2, -1);
        }
        break;
    case 2:
        ApproachValue((float *)(state + 0x1C), 0.0f, 0.016666668f);
        if (*(float *)(state + 0x1C) <= 0.0f) {
            s32 i;
            ids = (s32 *)state;
            i = 3;
            do { moby_mark_spawned(g_moby_l02_pool + (*ids++ << 8)); } while (--i >= 0);
            moby_set_group_enabled(*(s32 *)(state + 0x10), 1);
            moby_mark_table_entry_flagged(object[0xB0]);
            {
                u8 *record = g_matrix_l02_record_table + (*(s32 *)(state + 0x14) << 7);
                level_capture_checkpoint_state(record + 0x30, record + 0x70);
            }
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (*(float *)(state + 0x1C) != 0.0f) {
        if (g_hero_state.ptr[0x270 / 4] == object || g_hero_state.ptr[0x26C / 4] == object) {
            scratch[0].quad = g_hero_state.q[0xE0 / 16];
            scratch[0].f[0] = *(float *)(object + 0x10);
            if (CollLine(&g_hero_state.q[0xE0 / 16], scratch[0].f, 2, g_hero_state.v[0x2290 / 4], 0)) {
                s32 lifetime;
                s32 shade;
                scratch[1].quad = g_scratch_vec;
                scratch[1].f[2] += math_random_float_range(-0.5f, 0.5f);
                lifetime = (u8)math_random_int_range(30, 60);
                shade = (u8)math_random_int_below(255);
                part_spawn_hero_relative(scratch[1].f, g_zero_l02_vector, 0x60106070, lifetime, shade, 0, 1.0f);
            }
        }
        scale_vector(scratch[0].f, object, 0.0009765625f);
        if (math_fast_helper_a(scratch[0].f, 80.0f) != -1) {
            *(float *)(state + 0x2C) = FastAddRotations(*(float *)(state + 0x2C), 0.040724356f);
            *(float *)(state + 0x28) += 0.020833334f;
            if (*(float *)(state + 0x28) > 1.0f)
                *(float *)(state + 0x28) -= 1.0f;
            {
            s32 i;
            phase = (float *)(state + 0x20);
            i = 1;
            do {
                *phase += 0.011100001f;
                if (*phase > 1.0f)
                    *phase -= 1.0f;
                phase++;
            } while (--i >= 0);
            }
            gfx_add_draw_callback_first(energy_gate_draw_effect, object);
        }
        if (vec_distance_xy(object + 0x10, g_camera_l02_position) > 68.0f)
            ApproachValue((float *)(state + 0x1C), 0.0f, 0.008333334f);
        else
            ApproachValue((float *)(state + 0x1C), 1.0f, 0.008333334f);
    } else if (*(float *)(state + 0x1C) < 1.0f && vec_distance_xy(object + 0x10, g_camera_l02_position) < 64.0f)
        ApproachValue((float *)(state + 0x1C), 1.0f, 0.008333334f);

    {
    s32 *out = (s32 *)scratch;
    s32 i;
    ids = (s32 *)state;
    i = 3;
    do {
    *out = !moby_is_state_two(g_moby_l02_pool + (*ids++ << 8));
    out++;
    } while (--i >= 0);
    }
    if (*(float *)(state + 0x34) != 0.0f && ((s32 *)scratch)[0] == 0 && ((s32 *)scratch)[1] == 0)
        *(float *)(state + 0x34) = 0.0f;
    if (*(float *)(state + 0x38) != 0.0f && ((s32 *)scratch)[2] == 0 && ((s32 *)scratch)[3] == 0)
        *(float *)(state + 0x38) = 0.0f;
    if (*(float *)(state + 0x30) != 0.0f && ((s32 *)scratch)[0] == 0)
        *(float *)(state + 0x30) = 0.0f;
    if (*(float *)(state + 0x3C) != 0.0f && ((s32 *)scratch)[3] == 0)
        *(float *)(state + 0x3C) = 0.0f;
}
