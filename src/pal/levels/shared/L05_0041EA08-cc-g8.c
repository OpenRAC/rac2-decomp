#include "names.h"
/* func_PAL_L05_0041EA08, the PAL copy of func_L05_00419CC8: the same C, where expr 0.016666668f becomes 0.020000001f. */
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

/* Creates a flying shot effect (class 4090) with its speed, lifetime and colors (PAL: 50 Hz speed). */
char *moby_spawn_shot_effect_pal(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *moby = CreateMoby(0xFFA);
    float up[4];
    char *state;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (moby) {
        float initial = g_shot_base_speed;
        int life;
        float start, end;
        state = *(char **)(moby + 0x68);
        *(int *)(state+0x30) = kind;
        speed = initial * (0.020000001f);
        if (kind) speed = g_shot_l05_speed_scale * (0.020000001f);
        moby[0x20] = 0;
        *(unsigned char *)(moby+0x30) = 0xFF;
        life = FloatToInt(g_shot_life_distance / speed);
        end = g_shot_effect_end;
        start = g_shot_effect_start;
        *(char **)(state+4) = owner;
        *(int *)state = life;
        *(float *)(state+0x3c) = start;
        *(float *)(state+0x40) = (end-start)/(float)life;
        *(float *)(state+8) = math_random_angle();
        *(float *)(state+0xc) = scale;
        *(int *)(state+0x38) = value;
        if (*(int *)(state+0x30)) {
            *(int *)(state+0x20)=0x00FF2020;
            *(int *)(state+0x24)=0x7FEF2020;
            *(int *)(state+0x34)=0;
        } else {
            *(int *)(state+0x20)=color1;
            *(int *)(state+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(moby+0xc0,owner+0xc0);
            qcopy(moby+0xd0,owner+0xd0);
            qcopy(moby+0xe0,owner+0xe0);
            vec_scale_to_length(state+0x10,dir,speed);
        } else {
            vec_scale_to_length(moby+0xc0,dir,1.0f);
            FastVecCross(moby+0xd0,moby+0xc0,up);
            vec_scale_to_length(moby+0xd0,moby+0xd0,1.0f);
            FastVecCross(moby+0xe0,moby+0xd0,moby+0xc0);
            qcopy(state+0x10,dir);
        }
        qcopy(moby+0x10,pos);
        gfx_add_draw_callback_third(gfx_draw_energy_blast,moby);
    }
    return moby;
}
