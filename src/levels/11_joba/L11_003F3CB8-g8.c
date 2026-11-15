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
extern f32 D_L11_001B0610 __attribute__((sda));
extern f32 D_L11_001B05E8 __attribute__((sda));
extern s32 D_L11_001B060C __attribute__((sda));
extern s32 D_L11_001B05E4 __attribute__((sda));
extern f32 D_L11_001B0624 __attribute__((sda));
extern f32 D_L11_001B0628 __attribute__((sda));
extern f32 D_L11_001B05FC __attribute__((sda));
extern f32 D_L11_001B0600 __attribute__((sda));
extern f32 D_L11_001B062C __attribute__((sda));
extern f32 D_L11_001B0630 __attribute__((sda));
extern f32 D_L11_001B0604 __attribute__((sda));
extern f32 D_L11_001B0608 __attribute__((sda));
extern s32 D_L11_001B05B4 __attribute__((sda));
extern s32 D_L11_001B05B8 __attribute__((sda));
extern s32 D_L11_001B0634 __attribute__((sda));
extern f32 D_L11_001B063C __attribute__((sda));
extern f32 D_L11_001B0640 __attribute__((sda));
extern f32 D_L11_001B0644 __attribute__((sda));
extern f32 D_L11_001B0648 __attribute__((sda));
extern f32 D_L11_001B064C __attribute__((sda));
extern f32 D_L11_001B0650 __attribute__((sda));
extern f32 D_L11_001B0638 __attribute__((sda));
extern s32 D_L11_001B05BC __attribute__((sda));
extern s32 D_L11_001B05C0 __attribute__((sda));
extern f32 D_L11_001B05D8 __attribute__((sda));
extern f32 D_L11_001B05D4 __attribute__((sda));
extern s32 D_L11_001B05CC __attribute__((sda));
extern f32 D_L11_001B05C8 __attribute__((sda));
extern f32 D_L11_001B05C4 __attribute__((sda));
extern s32 D_L11_001B05D0 __attribute__((sda));

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
            f32 amplitude = group ? D_L11_001B0610 : D_L11_001B05E8;
            s32 count = group ? D_L11_001B060C : D_L11_001B05E4;
            f32 points[count][4];
            s32 duration = small ? math_random_int_range(0x30, 0x80) : math_random_int_range(0x30, 0x50);
            f32 width = small ? math_random_float_range(D_L11_001B0624, D_L11_001B0628) : math_random_float_range(D_L11_001B05FC, D_L11_001B0600);
            f32 scale = small ? math_random_float_range(D_L11_001B062C, D_L11_001B0630) : math_random_float_range(D_L11_001B0604, D_L11_001B0608);
            u8 *path = data + 0xA0 + i * 0xA0;
            curve_build_jittered_points_alt(points, count, path, amplitude);
            DrawDualQuadStrip(points, count, duration, D_L11_001B05B4, D_L11_001B05B8, width, scale);
            if ((u16)(*(u16 *)state - 3) < 2) {
                f32 extra[D_L11_001B0634][4];
                s32 pick = math_random_int_range(count - 6, count - 3);
                qcopy_nc(frame, points[pick]);
                qcopy_nc(frame + 0x10, points[count - 2]);
                vec_add_random_offset(frame + 0x10, 1.0f);
                vec_random_direction(frame + 0x20, D_L11_001B063C, D_L11_001B0640);
                vec_random_direction(frame + 0x30, D_L11_001B063C, D_L11_001B0640);
                duration = math_random_int_range(0x30, 0x60);
                width = math_random_float_range(D_L11_001B0644, D_L11_001B0648);
                scale = math_random_float_range(D_L11_001B064C, D_L11_001B0650);
                curve_build_jittered_points_alt(extra, D_L11_001B0634, frame, D_L11_001B0638);
                DrawDualQuadStrip(extra, D_L11_001B0634, duration, D_L11_001B05BC, D_L11_001B05C0, width, scale);
            }
            if (group) {
                f32 jitter = math_random_float_range(-D_L11_001B05D8, D_L11_001B05D8);
                f32 size = D_L11_001B05D4 + jitter;
                s32 life = math_random_int_range(0x50, 0x60);
                f32 angle = math_random_angle();
                gfx_draw_aimed_effect_packet(path, D_L11_001B05CC, size, life, angle, 0x31, 2);
            }
        }
        {
            f32 size = D_L11_001B05C4 + D_L11_001B05C8 * ((L11ArcData *)data)->unk260[i];
            f32 half;
            s32 life;
            f32 angle;
            moby_transform_joint_to_world(object, i, frame);
            half = size * 0.5f;
            life = math_random_int_range(0x50, 0x60);
            angle = math_random_angle();
            gfx_draw_aimed_effect_packet(frame, D_L11_001B05CC, half, life, angle, 0x31, 2);
            size *= 0.7f;
            life = math_random_int_range(8, 0x16);
            angle = math_random_angle();
            gfx_draw_aimed_effect_packet(frame, D_L11_001B05D0, size, life, angle, 0xB, 2);
        }
    }
}
