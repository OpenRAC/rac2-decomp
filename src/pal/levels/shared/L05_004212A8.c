#include "names.h"
/* func_PAL_L05_004212A8, the PAL copy of func_L05_003CD598: the same C, where 0xFF becomes 0xD4;
   0.0039215689f becomes 0.004716981f; 0x50FF4040 becomes 0x40405FFF; 0x10FF4040 becomes
   0x10405FFF. */
#include "include_asm.h"
typedef int V4_L05_003CD598 __attribute__((mode(TI)));
extern unsigned char ref_L05_003CD598_00[];
extern void FastVecSub(float *, void *, float *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecAdd(float *, float *, float *);
extern int math_fast_float_d(void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern int FloatToInt(float);

typedef struct { unsigned char pad[9]; unsigned char fade; } Sprite_L05_003CD598;
extern Sprite_L05_003CD598 *part_spawn_fading(void *, void *, int, int, int, int, int, float);

typedef struct { float phase[4]; float rate[4]; int alpha[4]; float size[4]; } GlowState_L05_003CD598;
/* Draws four pulsing glow sprites trailing behind the object, each fading in and out (PAL: 50 Hz scale). */
void glow_ring_draw_pulsing_sprites_pal(unsigned char *actor)
{
    GlowState_L05_003CD598 *state = *(GlowState_L05_003CD598 **)(actor + 0x68);
    float sprite_pos[4];
    float step[4];
    float origin[4];
    int i;

    *(V4_L05_003CD598 *)origin = *(V4_L05_003CD598 *)(actor + 0x10);
    origin[2] += 0.25f;
    FastVecSub(sprite_pos, ref_L05_003CD598_00, origin);
    vec_scale_to_length(sprite_pos, sprite_pos, -0.3f);
    vec_scale_to_length(step, sprite_pos, 0.1f);
    FastVecAdd(sprite_pos, sprite_pos, origin);

    for (i = 0; i < 4; i++) {
        float v = state->phase[i] + state->rate[i];
        void *color;
        Sprite_L05_003CD598 *sprite;
        state->phase[i] = v;
        if (v >= 255.0f)
            state->phase[i] = v - 255.0f;
        else if (v <= 0.0f)
            state->phase[i] = v + 255.0f;
        if (math_fast_float_d(&state->alpha[i]))
            state->alpha[i] = 0xD4;
        v = math_fabs(0.5f - IntToFloat(0xD4 - state->alpha[i]) * 0.004716981f);
        color = FastTweenColor(0x40405FFF, 0x10405FFF, v);
        sprite = part_spawn_fading(sprite_pos, color, FloatToInt(state->phase[i]) & 0xFF, 0x35, 1, 2, 0, state->size[i]);
        if (sprite)
            sprite->fade = FloatToInt(1.0f) + 0x60;
        FastVecAdd(sprite_pos, sprite_pos, step);
    }
}
