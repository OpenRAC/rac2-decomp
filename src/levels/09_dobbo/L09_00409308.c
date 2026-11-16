#include "common.h"
typedef int Quad_Dobbo __attribute__((mode(TI)));
typedef struct DobboPlayer {
    char pad0[0x80];
    float position[4];
    char pad90[0x50];
    float aim[4];
    char padf0[0x20];
    float velocity[4];
    char pad120[0x1710];
    char *target;
    char pad1834[0xa60];
    int mode;
} DobboPlayer;
extern DobboPlayer g_hero_state;
typedef struct DobboAnimation {
    char pad[0x43];
    unsigned char animation;
} DobboAnimation;
extern float math_random_float_range(float, float);
extern void moby_set_state(char *, int, int);
extern int math_fast_float_d(void *);
extern void part_spawn_death_sparks(char *);

typedef struct DobboPath {
    int count;
    char pad[12];
    float points[0][4];
} DobboPath;
extern DobboPath *g_path_l09_table[];
typedef struct DobboPathEffect {
    float dimensions[3];
    int flags;
    float position[4];
} DobboPathEffect;
extern DobboPathEffect g_sound_effect_table[];
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern float mat_fast_helper_a(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastAddRotations(float, float);
extern float FastDiffRots(float, float);
extern float FastVecLength(void *);
extern int FloatToInt(float);
extern int func_001163B0(void);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
/* Per-frame update of a guide creature (moby class 3610): it rides along a path once the hero gets on a glider, looks at the hero and watches where he aims. */
void path_guide_update(char *obj)
{
    char *vars = *(char **)(obj+0x68);
    char *glider;
    float distance, angle, inverse;
    Quad_Dobbo target;
    switch (B(obj,0x20)) {
    case 0: {
        DobboPath *path;
        path = g_path_l09_table[I(vars,0x260)];
        I(vars,0x268)=0;
        *(DobboPath **)(vars+0x26c)=path;
        distance = fast_vec_dist(path->points[0],path->points[1]);
        inverse = 1.0f / distance;
        F(vars,0x29c)=(inverse*0.0166666675f)*F(vars,0x264);
        I(vars,0x274)=part_l00_alloc_effect_slot_2(obj+0x10,F(vars,0x278),F(vars,0x288),F(vars,0x27c),F(vars,0x280),F(vars,0x284));
        moby_set_state(obj,2,-1);
        break;
    }
    case 2:
        if (g_hero_state.mode==0x31) {
            glider=g_hero_state.target;
            if(glider && *(short *)(glider+0xaa)==MOBY_CLASS_GLIDER && B(glider,0x20)!=0xfe && B(glider,0x20)!=0xfd) {
                B(obj,0x30)=0xff; *(short *)(obj+0x32)=0x3ff; I(vars,0x268)=0;
                if(((DobboAnimation *)obj)->animation!=4) anim_start_blended(obj,4,0,10);
                moby_set_state(obj,1,-1);
            }
        }
    case 3:
        if(((DobboAnimation *)obj)->animation==0 && math_fast_float_d(vars+0x298)) {
                I(vars,0x298)=FloatToInt(math_random_float_range(1200.0f,2400.0f));
                { int state=(func_001163B0()&1)+1;
                  if(((DobboAnimation *)obj)->animation!=state) anim_start_blended(obj,state,0,10); }
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=0) anim_start_blended(obj,0,0,10);
        }
        angle=mat_fast_helper_a(g_hero_state.position[0]-F(obj,0x10),g_hero_state.position[1]-F(obj,0x14));
        F(obj,0xf8)=FastAddRotations(F(obj,0xf8),fast_subtract_rotations(angle,F(obj,0xf8))*0.01f);
        break;
    case 1: {
        DobboPath *path;
        DobboPathEffect *effect;
        if(((DobboAnimation *)obj)->animation==4 && math_fast_float_d(vars+0x298)) {
                I(vars,0x298)=FloatToInt(math_random_float_range(1200.0f,2400.0f));
                if(((DobboAnimation *)obj)->animation!=2) anim_start_blended(obj,2,0,10);
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=4) anim_start_blended(obj,4,0,10);
        }
        path=*(DobboPath **)(vars+0x26c);
        path_sample_position(path,1,obj+0x10,obj+0xf0,0,F(vars,0x268));
        distance=fast_vec_dist(obj+0x10,g_hero_state.position);
        if(distance<10.0f) F(vars,0x29c)*=1.01f;
        else if(distance>30.0f) F(vars,0x29c)*=0.99f;
        else {
            path=*(DobboPath **)(vars+0x26c);
            distance = fast_vec_dist(path->points[0],path->points[1]);
            inverse = 1.0f / distance;
            F(vars,0x29c)+=((inverse*0.0166666675f)*F(vars,0x264)-F(vars,0x29c))*0.05f;
        }
        F(vars,0x268)+=F(vars,0x29c);
        effect=&g_sound_effect_table[I(vars,0x274)];
        qcopy(effect->position,obj+0x10);
        effect->position[3]=F(vars,0x278);
        effect->dimensions[0]=F(vars,0x27c);
        effect->dimensions[1]=F(vars,0x280);
        effect->dimensions[2]=F(vars,0x284);
        effect->flags=0;
        if(FloatToInt(F(vars,0x268))+2>=(*(DobboPath **)(vars+0x26c))->count) B(obj,0xbc)=1;
        break;
    }
    }
    if(((DobboAnimation *)obj)->animation==0) {
        if(vec_distance_xy(obj+0x10,g_hero_state.position)<8.0f &&
           FastDiffRots(F(obj,0xf8),mat_fast_helper_a(g_hero_state.aim[0]-F(obj,0x10),g_hero_state.aim[1]-F(obj,0x14)))<1.5707965f) {
            if(FastVecLength(g_hero_state.velocity)>0.01f) I(vars,0x290)=120;
            else math_fast_float_d(vars+0x290);
        } else if(I(vars,0x290)) { I(vars,0x290)=0; qcopy(vars+0x250,g_hero_state.aim); }
        if(math_fast_float_d(vars+0x294)) {
            I(vars,0x294)=FloatToInt(math_random_float_range(180.0f,300.0f));
            angle=FastAddRotations(F(obj,0xf8),math_random_float_range(-90.0f,90.0f)*0.017453294f);
            distance=math_random_float_range(0.0f,30.0f)*0.017453294f;
            vec_build_spherical_offset(vars+0x250,6.0f,angle,distance);
            FastVecAdd(vars+0x250,vars+0x250,obj+0x10);
        }
        if (I(vars,0x290))
            qcopy(&target,g_hero_state.aim);
        else
            qcopy(&target,vars+0x250);
    }
    if(B(obj,0xbc)) { gfx_free_point_light(I(vars,0x274)); moby_mark_spawned(obj); }
    else part_spawn_death_sparks(obj);
}
#undef F
#undef I
#undef B
