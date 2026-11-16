#include "common.h"


extern char *CreateMoby(int);
extern int FloatToInt(float);
extern float math_random_angle(void);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern void gfx_draw_energy_blast(char *);
extern float g_shot_base_speed __attribute__((sda));
extern float g_shot_l05_speed_scale __attribute__((sda));
extern float g_shot_life_distance __attribute__((sda));
extern float g_shot_effect_start __attribute__((sda));
extern float g_shot_effect_end __attribute__((sda));
typedef int EffectVector __attribute__((mode(TI)));

/* Creates a shot-like effect object that starts at a position and flies along a direction. It copies the owner's turn or builds its own, and gets its draw function set up. */
char *moby_spawn_shot_effect(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *effect = CreateMoby(0xFFA /* moby class 4090 */);
    float up[4];
    char *vars;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (effect) {
        float base_speed = g_shot_base_speed;
        int life;
        float start, end;
        vars = *(char **)(effect + 0x68);
        *(int *)(vars+0x30) = kind;
        speed = base_speed * (1.0f / 60.0f);
        if (kind) speed = g_shot_l05_speed_scale * (1.0f / 60.0f);
        effect[0x20] = 0;
        *(unsigned char *)(effect+0x30) = 0xFF;
        life = FloatToInt(g_shot_life_distance / speed);
        end = g_shot_effect_end;
        start = g_shot_effect_start;
        *(char **)(vars+4) = owner;
        *(int *)vars = life;
        *(float *)(vars+0x3c) = start;
        *(float *)(vars+0x40) = (end-start)/(float)life;
        *(float *)(vars+8) = math_random_angle();
        *(float *)(vars+0xc) = scale;
        *(int *)(vars+0x38) = value;
        if (*(int *)(vars+0x30)) {
            *(int *)(vars+0x20)=0x00FF2020;
            *(int *)(vars+0x24)=0x7FEF2020;
            *(int *)(vars+0x34)=0;
        } else {
            *(int *)(vars+0x20)=color1;
            *(int *)(vars+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(effect+0xc0,owner+0xc0);
            qcopy(effect+0xd0,owner+0xd0);
            qcopy(effect+0xe0,owner+0xe0);
            vec_scale_to_length(vars+0x10,dir,speed);
        } else {
            vec_scale_to_length(effect+0xc0,dir,1.0f);
            FastVecCross(effect+0xd0,effect+0xc0,up);
            vec_scale_to_length(effect+0xd0,effect+0xd0,1.0f);
            FastVecCross(effect+0xe0,effect+0xd0,effect+0xc0);
            qcopy(vars+0x10,dir);
        }
        qcopy(effect+0x10,pos);
        gfx_add_draw_callback_third(gfx_draw_energy_blast,effect);
    }
    return effect;
}
