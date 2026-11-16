#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern u8 *part_alloc(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern u8 *g_fading_particle_params;
extern void part_l00_update_fading_effect_3(char *);
/* Spawns a short-lived particle that moves and fades, and returns it (0 if none is free). */
u8 *part_spawn_fading_particle(float *position,float *velocity,int duration,int color,int kind,int alpha,int endAlpha,float size,float endSize,float drag)
{
    u8 *effect = part_alloc(0x69);
    u8 *motion;
    float lifetime;
    if (effect) {
        *(Quad *)(effect+0x10) = *(Quad *)position;
        *(int *)(effect+4) = (alpha << 24) | color;
        motion = effect+0x20;
        effect[9] = FloatToInt(4.0f)+64;
        effect[1] = 0;
        *(float *)(effect+0xC) = size;
        effect[3] = 0x48;
        effect[8] = math_random_int_below(255);
        effect[2] = *g_fading_particle_params;
        *(short *)(effect+0xA) = duration;
        *(float *)(effect+0x20) = velocity[0];
        *(float *)(motion+4) = velocity[1];
        *(float *)(motion+8) = velocity[2];
        *(float *)(motion+0xC) = drag;
        motion[0x15] = kind;
        lifetime = IntToFloat(duration);
        *(float *)(motion+0x10) = (endSize-size)/lifetime;
        motion[0x14] = (endAlpha-alpha)/duration;
        *(void (**)(char *))(motion+0x1C) = part_l00_update_fading_effect_3;
    }
    return effect;
}
