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

char *func_PAL_L05_0041EA08(char *owner, void *pos, void *dir, int color1, int color2, int orient, int kind, int value, float scale)
{
    char *obj = CreateMoby(0xFFA);
    float up[4];
    char *st;
    float speed;
    *(EffectVector *)up = 0;
    up[2] = 1.0f;
    if (obj) {
        float initial = g_shot_base_speed;
        int life;
        float start, end;
        st = *(char **)(obj + 0x68);
        *(int *)(st+0x30) = kind;
        speed = initial * (0.020000001f);
        if (kind) speed = g_shot_l05_speed_scale * (0.020000001f);
        obj[0x20] = 0;
        *(unsigned char *)(obj+0x30) = 0xFF;
        life = FloatToInt(g_shot_life_distance / speed);
        end = g_shot_effect_end;
        start = g_shot_effect_start;
        *(char **)(st+4) = owner;
        *(int *)st = life;
        *(float *)(st+0x3c) = start;
        *(float *)(st+0x40) = (end-start)/(float)life;
        *(float *)(st+8) = math_random_angle();
        *(float *)(st+0xc) = scale;
        *(int *)(st+0x38) = value;
        if (*(int *)(st+0x30)) {
            *(int *)(st+0x20)=0x00FF2020;
            *(int *)(st+0x24)=0x7FEF2020;
            *(int *)(st+0x34)=0;
        } else {
            *(int *)(st+0x20)=color1;
            *(int *)(st+0x24)=color2 | 0x7F000000;
        }
        if (!orient) {
            qcopy(obj+0xc0,owner+0xc0);
            qcopy(obj+0xd0,owner+0xd0);
            qcopy(obj+0xe0,owner+0xe0);
            vec_scale_to_length(st+0x10,dir,speed);
        } else {
            vec_scale_to_length(obj+0xc0,dir,1.0f);
            FastVecCross(obj+0xd0,obj+0xc0,up);
            vec_scale_to_length(obj+0xd0,obj+0xd0,1.0f);
            FastVecCross(obj+0xe0,obj+0xd0,obj+0xc0);
            qcopy(st+0x10,dir);
        }
        qcopy(obj+0x10,pos);
        gfx_add_draw_callback_third(gfx_draw_energy_blast,obj);
    }
    return obj;
}
