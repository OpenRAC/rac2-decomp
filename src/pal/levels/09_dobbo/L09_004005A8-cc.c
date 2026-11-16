#include "names.h"
/* func_PAL_L09_004005A8, the PAL copy of func_L09_003FB9F8: the same C, where rename func_L08_0034A078 becomes func_PAL_L08_0034C4A8. */
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

extern int level_is_resident_flag_clear(void);
extern void FastVecSub(float *, const float *, const float *);
extern float FastVecLength(void *);
extern float IntToFloat(int);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_wrap_angle_to_pi(float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern void vec_add_random_offset(void *, float);
extern char *func_PAL_L08_0034C4A8(void *, void *, int, void *);

extern int g_beam_slot_state_2[16] MACRO_ADDR;
extern float g_beam_slot_angle_x[16] MACRO_ADDR;
extern float g_beam_slot_angle_y[16] MACRO_ADDR;
extern float g_beam_slot_angle_z[16] MACRO_ADDR;
extern int g_beam_slot_light_handle[16] MACRO_ADDR;
extern int g_beam_slot_light_handle_alt[16] MACRO_ADDR;
extern int g_beam_slot_flag[16] MACRO_ADDR;
extern unsigned char *g_sound_slot_ptrs[16][2];
extern Vec g_sound_slot_origins[16][4];
extern Vec g_sound_slot_positions[16];
extern Vec g_sound_slot_target_positions[16];
extern Vec g_beam_strip_buffers[][6];
extern char g_default_particle_vec[] MACRO_ADDR;

void UpdateBeamLinkStrips_pal(void *object, int slot)
{
    Vec delta, origin, direction, pos;
    float length, step;
    int i, alpha, first, second;
    char *effect, *payload;
    if (!level_is_resident_flag_clear()) return;
    alpha = g_sound_slot_ptrs[slot][0][0x23];
    FastVecSub(delta.f, g_sound_slot_positions[slot].f, g_sound_slot_origins[slot][0].f);
    first = slot * 2;
    second = first + 1;
    length = FastVecLength(&delta);
    step = length / IntToFloat(5);
    if (g_beam_slot_state_2[slot] == 2) {
        g_beam_slot_state_2[slot] = 3;
        for (i = 0; i < 6; i++) {
            float x = step * IntToFloat(i);
            g_beam_strip_buffers[first][i].f[1] = g_beam_strip_buffers[first][i].f[2] = 0.0f;
            g_beam_strip_buffers[first][i].f[3] = 1.0f;
            g_beam_strip_buffers[second][i].f[0] = g_beam_strip_buffers[first][i].f[0] = x;
            g_beam_strip_buffers[second][i].f[1] = g_beam_strip_buffers[second][i].f[2] = 0.0f;
            g_beam_strip_buffers[second][i].f[3] = 1.0f;
        }
    }
    g_beam_slot_angle_x[slot] = FastAddRotations(g_beam_slot_angle_x[slot], 0.17453295f);
    g_beam_slot_angle_y[slot] = fast_subtract_rotations(g_beam_slot_angle_y[slot], 0.8028515577316284f);
    g_beam_slot_angle_z[slot] = FastAddRotations(g_beam_slot_angle_z[slot], 0.052359998f);
    qcopy(&origin, &g_sound_slot_origins[slot][0]);
    vec_scale_to_length(&direction, &delta, step);
    {
        float angleStep = (360.0f / (IntToFloat(6) * 0.5f)) * 0.017453294f;
        for (i = 0; i < 6; i++) {
            float t = IntToFloat(i);
            float y = math_fast_sin_or_cos_b(t / IntToFloat(5) * 3.1415927f) * -0.09f + 0.1f;
            y *= math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_beam_slot_angle_x[slot] + t * angleStep));
            g_beam_strip_buffers[first][i].f[1] = 0;
            g_beam_strip_buffers[first][i].f[3] = 1;
            g_beam_strip_buffers[first][i].f[2] = y;
            g_beam_strip_buffers[first][i].f[0] = step * t;
        }
    }
    qcopy(&g_sound_slot_target_positions[slot], g_sound_slot_ptrs[slot][1] + 0x10);
    for (i = 0; i < 6; i++) {
        float t = IntToFloat(i);
        float x = math_wrap_angle_to_pi(g_beam_slot_angle_y[slot] + t * 0.99483776f);
        float z = math_wrap_angle_to_pi(g_beam_slot_angle_z[slot] + t * 0.20943999f);
        float y = math_fast_sin_or_cos_b(z) * 0.2f;
        z = math_fast_sin_or_cos_b(x);
        {
            float noise = math_random_signed_float_range(0, 0.2f);
            (g_beam_strip_buffers[second] + i)->f[2] = (g_beam_strip_buffers[first][i].f[2] + y * z) + noise;
        }
        (g_beam_strip_buffers[second] + i)->f[1] = math_fast_sin_or_cos_a(x) * 0.1f;
        (g_beam_strip_buffers[second] + i)->f[3] = 1;
        (g_beam_strip_buffers[second] + i)->f[0] = step * t;
    }
    /* first is reused here as the endpoint index (retail keeps both in s5). */
    for (first = 0; first < 2; first++) {
        if (math_random_int_below(3)) continue;
        qcopy(&pos, g_sound_slot_ptrs[slot][first] + 0x10);
        vec_add_random_offset(&pos, 0.1f);
        effect = func_PAL_L08_0034C4A8(&pos, g_default_particle_vec, alpha * 127 / 100, g_sound_slot_ptrs[slot][first]);
        if (effect) {
            payload = effect + 0x20;
            *(float *)(effect + 0xC) = 120000;
            *(short *)(effect + 0xA) = 3;
            *(float *)(payload + 0x10) = 1.0f / IntToFloat(3);
            *(int *)(payload + 0x18) = 0x7F7F7F;
            if (g_beam_slot_flag[slot] == 1) *(short *)(payload + 0x16) = 1;
        }
    }
    g_beam_slot_light_handle[slot] = -1;
    g_beam_slot_light_handle_alt[slot] = -1;
}
