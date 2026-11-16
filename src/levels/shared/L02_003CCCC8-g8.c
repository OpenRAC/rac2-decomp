#include "common.h"
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int PulseColor(int, int, float);
extern int FastDecTimer(void *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern void value_set_and_smooth(void *, float *, float, int, int);
extern float g_glow_pulse_rate_b __attribute__((sda));
extern float g_glow_pulse_rate_a __attribute__((sda));
extern int g_glow_tween_colors[] __attribute__((sda));
extern int g_glow_pulse_colors[] __attribute__((sda));
extern int g_arena_state_words[] __attribute__((sda));
extern char g_hero_state[];
/* Each frame, pulses the object colour and a linked part colour, counts down its timers and starts its shake effects. */
void moby_update_glow_pulse_timers(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    float phase;
    if (object[0x31]) {
        *(float *)(state + 0x38c) = FastAddRotations(*(float *)(state + 0x38c), g_glow_pulse_rate_b * 0.0002908882452175021f);
        phase = math_fast_sin_or_cos_b(*(float *)(state + 0x38c)) * 4.0f + 4.0f;
        if (phase > 1.0f)
            phase = 1.0f;
        else if (phase < 0.0f)
            phase = 0.0f;
        *(int *)(object + 0x78) = FastTweenColor(g_glow_tween_colors[0], g_glow_tween_colors[1], phase);
        if (*(char **)(state + 0x370)) {
            *(float *)(state + 0x388) = FastAddRotations(*(float *)(state + 0x388), g_glow_pulse_rate_a * 0.0002908882452175021f);
            *(int *)(*(char **)(state + 0x370) + 0x78) = PulseColor(g_glow_pulse_colors[0], g_glow_pulse_colors[1], *(float *)(state + 0x388));
        }
    }
    FastDecTimer(state + 0x386);
    FastDecTimer(state + 0x374);
    FastDecTimer(state + 0x376);
    FastDecTimer(state + 0x378);
    if (*(unsigned short *)(object + 0x96) < 65535)
        ++*(unsigned short *)(object + 0x96);
    if (g_arena_state_words[0] != 2 || *(int *)(g_hero_state + 0x2294) == 0x6f)
        *(short *)(state + 0x386) = 0;
    moby_update_eased_node(object, state + 0x210, 1, 0.03f, 0.3f);
    moby_update_eased_node(object, state + 0x290, 2, 0.03f, 0.3f);
    value_set_and_smooth(object, (float *)(state + 0x290), 2.5f, 2, 1);
}
