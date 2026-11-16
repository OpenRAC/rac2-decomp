#include "include_asm.h"
#include "names.h"

/* func_US2_002E5520, the USA v2.00 copy of func_002E4708: the same C, where adding the yaw at
   D_L00_001B8DC0[6] to the angle becomes rotating buf by func_002836E8 of the matrix at +0x230. */

extern float g_camera_l00_position[];

extern void FastVecSub(void *dst, void *src, void *arg);
extern void mat_fast_helper_c(void *dst, void *src);
extern void matrix_mul_vec3(void *dst, void *src, void *m);
extern float mat_fast_helper_a(float a, float b);
extern float FastAddRotations(float a, float b);
extern float vec_length_xy(void *p);
extern float fast_subtract_rotations(float a, float b);
extern int FloatToInt(float a);

void snd_compute_voice_pan_us2(void *self, void *other)
{
    struct AngleState { char reserved[0x40]; float angle; };
    struct AngleState *state = (struct AngleState *)self;
    float buf[4];
    float m[12];
    float w;
    float r;

    FastVecSub(buf, other, g_camera_l00_position);
    mat_fast_helper_c(m, (char *)g_camera_l00_position + 0x230);
    matrix_mul_vec3(buf, buf, m);
    w = -mat_fast_helper_a(buf[0], buf[1]);
    if (w < 0.0f)
        w += 6.283185307179586f;
    if (vec_length_xy(buf) < 2.0f) {
        if (state->angle >= 0.0f) {
            r = fast_subtract_rotations(w, state->angle);
            if (r > 0.2f) {
                w = FastAddRotations(state->angle, 0.2f);
            } else if (r < -0.2f) {
                w = fast_subtract_rotations(state->angle, 0.2f);
            }
            state->angle = w;
        } else {
            state->angle = w;
        }
    } else {
        state->angle = -1.0f;
    }
    FloatToInt(w * 57.2957763671875f);
}
