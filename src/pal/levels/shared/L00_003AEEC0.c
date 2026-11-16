#include "include_asm.h"
#include "names.h"

extern int math_random_int_below(int);
extern int FloatToInt(float);
extern char *func_PAL_002BE9A8(void *, int, void *, float, float, unsigned int, float, float, int);
extern char g_default_vector[] __attribute__((section(".sdata")));

void seeker_spawn_impact_sparks_pal(void *unused, void *position)
{
    int i, sign;
    char *p, *q;
    for (i=1; i>=0; i--) {
        int n=math_random_int_below(16);
        sign=math_random_int_below(2);
        p=func_PAL_002BE9A8(position, sign ? -n : n, g_default_vector, 0.04f, 1.0f, 0x7f204080, 0.9f, 50000.0f, 1);
        q=p+32;
        if(p) {
            *(short *)(p+10)=8;
            p[9]=FloatToInt(4.0f)+64;
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    { int n=16;
    int j;
    for(j=0;j<2;j++) {
        p=func_PAL_002BE9A8(position,n,g_default_vector,0.02f,1.0f,0x7fffffff,0.97f,15000.0f,1);
        n=-n;
        q=p+32;
        if(p) {
            p[9]=FloatToInt(4.0f)+64;
            *(short *)(p+10)=2;
            p[8]=math_random_int_below(255);
            *(int *)(q+4)=2;
            q[10]=127;
            q[11]=*(unsigned char *)(p+10);
        }
    }
    }
}


typedef struct {
    char pad[0x50];
    float angle;
    char tail[0x8C];
} AngleRecord_262570;
typedef struct {
    char pad[0x760];
    char pad2[0xBF8 - 0x760];
    void *pBF8;
    char pad3[0x2294 - 0xBFC];
    int i2294;
    char pad4[0x24EC - 0x2298];
    short h24EC;
} Res_189E20;
extern unsigned char g_seeker_weapon_index[];
extern AngleRecord_262570 g_weapon_l00_table[];
extern Res_189E20 g_hero_state;
extern char g_cam_follow_matrix[];
extern void vec_scale_to_length(void *, void *, float);
extern void vec_compute_object_to_target(void *, void *, void *, int, float);
extern char *func_PAL_L00_003ADC68(void *, void *, void *, void *);

char *hero_fire_effect_from_facing_pal(char *a0, char *a1) {
    float buf[4];
    float angle;
    AngleRecord_262570 *e;
    Res_189E20 *g;
    void *p;

    e = &g_weapon_l00_table[g_seeker_weapon_index[0]];
    angle = e->angle * 0.020000001f;
    if (g_hero_state.i2294 == 0x1D) {
        vec_scale_to_length(buf, g_cam_follow_matrix, angle);
    } else if (g_hero_state.h24EC == 1) {
        vec_scale_to_length(buf, a1 + 0xD0, -angle);
    } else {
        vec_scale_to_length(buf, (char *)&g_hero_state + 0x760, angle);
    }
    g = &g_hero_state;
    p = 0;
    if (g->pBF8 != 0) {
        vec_compute_object_to_target(g->pBF8, a0, buf, 0, angle);
        p = g->pBF8;
    }
    return func_PAL_L00_003ADC68(a0, buf, a1, p);
}





