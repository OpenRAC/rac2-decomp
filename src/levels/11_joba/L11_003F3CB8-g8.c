#include "common.h"

/* The two per-path sizes are an array member: indexing it adds the index to the base
   (base first), as retail does. */
typedef struct {
    u8 pad0[0x260];
    f32 unk260[2];
} L11ArcData;

extern s32 math_random_int_range(s32, s32);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_angle(void);
extern void vec_random_direction(void *, f32, f32);
extern void curve_build_jittered_points_alt(void *, s32, void *, f32);
extern void DrawDualQuadStrip(void *, s32, s32, s32, s32, f32, f32);
extern void vec_add_random_offset(void *, f32);
extern void moby_transform_joint_to_world(u8 *, s32, void *);
/* Integer and FP arguments interleaved in the ABI's per-bank order (a0-a3/t0, f12/f13):
   retail sets the size before the life count. */
extern void gfx_draw_aimed_effect_packet(void *, s32, f32, s32, f32, s32, s32);
extern f32 g_joba_beam_group_amplitude __attribute__((sda));
extern f32 g_joba_beam_amplitude __attribute__((sda));
extern s32 g_joba_beam_group_point_count __attribute__((sda));
extern s32 g_joba_beam_point_count __attribute__((sda));
extern f32 g_joba_beam_small_width_min __attribute__((sda));
extern f32 g_joba_beam_small_width_max __attribute__((sda));
extern f32 g_joba_beam_width_min __attribute__((sda));
extern f32 g_joba_beam_width_max __attribute__((sda));
extern f32 g_joba_beam_small_scale_min __attribute__((sda));
extern f32 g_joba_beam_small_scale_max __attribute__((sda));
extern f32 g_joba_beam_scale_min __attribute__((sda));
extern f32 g_joba_beam_scale_max __attribute__((sda));
extern s32 g_joba_beam_strip_param_a __attribute__((sda));
extern s32 g_joba_beam_strip_param_b __attribute__((sda));
extern s32 g_joba_beam_extra_point_count __attribute__((sda));
extern f32 g_joba_beam_frame_dir_min __attribute__((sda));
extern f32 g_joba_beam_frame_dir_max __attribute__((sda));
extern f32 g_joba_beam_alt_width_min __attribute__((sda));
extern f32 g_joba_beam_alt_width_max __attribute__((sda));
extern f32 g_joba_beam_alt_scale_min __attribute__((sda));
extern f32 g_joba_beam_alt_scale_max __attribute__((sda));
extern f32 g_joba_beam_extra_jitter __attribute__((sda));
extern s32 g_joba_beam_extra_strip_param_a __attribute__((sda));
extern s32 g_joba_beam_extra_strip_param_b __attribute__((sda));
extern f32 g_joba_beam_spark_jitter __attribute__((sda));
extern f32 g_joba_beam_spark_base_size __attribute__((sda));
extern s32 g_joba_beam_effect_type_a __attribute__((sda));
extern f32 g_joba_beam_glow_size_scale __attribute__((sda));
extern f32 g_joba_beam_glow_base_size __attribute__((sda));
extern s32 g_joba_beam_effect_type_b __attribute__((sda));

/* Emits the two articulated effect paths and their joint effects. */
/* Draws the two Joba beams as glowing strips along their points, with extra branches and spark flashes at the ends. */
void joba_beams_draw(u8 *object)
{
    u8 frame[0xA0] __attribute__((aligned(16)));
    u8 *data = *(u8 **)(object + 0x68);
    s16 *state = (s16 *)(data + 0x278);
    s32 i;
    for (i = 0; i < 2; i++, state++) {
        if (*state != 0) {
            s32 group = (u16)(*(u16 *)state - 3) < 3;
            s32 small = (u16)(*(u16 *)state - 3) < 2;
            f32 amplitude = group ? g_joba_beam_group_amplitude : g_joba_beam_amplitude;
            s32 count = group ? g_joba_beam_group_point_count : g_joba_beam_point_count;
            f32 points[count][4];
            s32 duration = small ? math_random_int_range(0x30, 0x80) : math_random_int_range(0x30, 0x50);
            f32 width = small ? math_random_float_range(g_joba_beam_small_width_min, g_joba_beam_small_width_max) : math_random_float_range(g_joba_beam_width_min, g_joba_beam_width_max);
            f32 scale = small ? math_random_float_range(g_joba_beam_small_scale_min, g_joba_beam_small_scale_max) : math_random_float_range(g_joba_beam_scale_min, g_joba_beam_scale_max);
            u8 *path = data + 0xA0 + i * 0xA0;
            curve_build_jittered_points_alt(points, count, path, amplitude);
            DrawDualQuadStrip(points, count, duration, g_joba_beam_strip_param_a, g_joba_beam_strip_param_b, width, scale);
            if ((u16)(*(u16 *)state - 3) < 2) {
                f32 extra[g_joba_beam_extra_point_count][4];
                s32 pick = math_random_int_range(count - 6, count - 3);
                qcopy_nc(frame, points[pick]);
                qcopy_nc(frame + 0x10, points[count - 2]);
                vec_add_random_offset(frame + 0x10, 1.0f);
                vec_random_direction(frame + 0x20, g_joba_beam_frame_dir_min, g_joba_beam_frame_dir_max);
                vec_random_direction(frame + 0x30, g_joba_beam_frame_dir_min, g_joba_beam_frame_dir_max);
                duration = math_random_int_range(0x30, 0x60);
                width = math_random_float_range(g_joba_beam_alt_width_min, g_joba_beam_alt_width_max);
                scale = math_random_float_range(g_joba_beam_alt_scale_min, g_joba_beam_alt_scale_max);
                curve_build_jittered_points_alt(extra, g_joba_beam_extra_point_count, frame, g_joba_beam_extra_jitter);
                DrawDualQuadStrip(extra, g_joba_beam_extra_point_count, duration, g_joba_beam_extra_strip_param_a, g_joba_beam_extra_strip_param_b, width, scale);
            }
            if (group) {
                f32 jitter = math_random_float_range(-g_joba_beam_spark_jitter, g_joba_beam_spark_jitter);
                f32 size = g_joba_beam_spark_base_size + jitter;
                s32 life = math_random_int_range(0x50, 0x60);
                f32 angle = math_random_angle();
                gfx_draw_aimed_effect_packet(path, g_joba_beam_effect_type_a, size, life, angle, 0x31, 2);
            }
        }
        {
            f32 size = g_joba_beam_glow_base_size + g_joba_beam_glow_size_scale * ((L11ArcData *)data)->unk260[i];
            f32 half;
            s32 life;
            f32 angle;
            moby_transform_joint_to_world(object, i, frame);
            half = size * 0.5f;
            life = math_random_int_range(0x50, 0x60);
            angle = math_random_angle();
            gfx_draw_aimed_effect_packet(frame, g_joba_beam_effect_type_a, half, life, angle, 0x31, 2);
            size *= 0.7f;
            life = math_random_int_range(8, 0x16);
            angle = math_random_angle();
            gfx_draw_aimed_effect_packet(frame, g_joba_beam_effect_type_b, size, life, angle, 0xB, 2);
        }
    }
}
