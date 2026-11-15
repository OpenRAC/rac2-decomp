#include "include_asm.h"
#include "names.h"

typedef struct {float amplitude, offset; int frames, longest;} CameraShake;
typedef struct { char prefix[0x140]; float pos[4]; char pad[0x40]; char *current; char pad194[0x1dc]; float rows[12]; } CameraSystem;
extern CameraSystem g_active_camera;
extern float D_001A85B8 __attribute__((sda));
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fast_float_g(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);

void func_PAL_002717F8(CameraShake *s, int mode)
{
    float buf[4], matrix[12];
    float ratio, cube, frequency, elapsed, ramp;
    if (g_active_camera.current != 0 && *(short *)(g_active_camera.current + 0x86) == 6) {
        s->frames = 0;
        s->longest = 0;
    } else if (s->frames != 0) {
        if (s->longest < s->frames) s->longest = s->frames;
        math_fast_float_d(&s->frames);
        ratio = IntToFloat(s->frames) / IntToFloat(s->longest);
        switch (mode) {
        case 0: {
            float value = s->amplitude * math_fast_sin_or_cos_a(math_fast_float_g(IntToFloat(s->frames) * 2.0f)) * ratio * ratio;
            s->offset = value;
            vec_scale_to_length(buf, (g_active_camera.rows + 8), value);
            FastVecAdd(g_active_camera.pos, g_active_camera.pos, buf);
            break;
        }
        case 1: {
            float value = s->amplitude * math_fast_sin_or_cos_a(math_fast_float_g(IntToFloat(s->frames) * 2.0f)) * ratio * ratio;
            s->offset = value;
            vec_scale_to_length(buf, g_active_camera.rows, value);
            FastVecAdd(g_active_camera.pos, g_active_camera.pos, buf);
            break;
        }
        case 2: {
            float value;
            cube = ratio * ratio * ratio;
            frequency = D_001A85B8 * 0.017453294f;
            elapsed = IntToFloat(s->longest - s->frames) * (0.019867549f);
            ramp = elapsed * 6.0f;
            if (ramp > 1.0f) ramp = 1.0f;
            value = s->amplitude * math_fast_sin_or_cos_b(math_fast_float_g(elapsed * frequency - frequency * 8.0f)) * cube * ramp;
            s->offset = value;
            vec_set_direction_with_complement(buf, g_active_camera.rows, value);
            quaternion_to_rotation_basis(buf, matrix);
            multiply_matrix3x3(g_active_camera.rows, matrix, g_active_camera.rows);
            break;
        }
        }
    } else s->longest = 0;
}
