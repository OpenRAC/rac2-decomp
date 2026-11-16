#include "names.h"
/* func_PAL_L09_0040E300, the PAL copy of func_L09_00409308: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L09_004091C8 becomes func_PAL_L09_0040E1C0; wrap func_002A7878(1200.0f,2400.0f) (({e}) * 5.0f + 2.0f) * ; wrap func_002A7878(1200.0f,2400.0f) (({e}) * 5.0f + 2.0f) * ; wrap func_002A7878(180.0f,300.0f) (({e}) * 5.0f + 2.0f) * 0.. */
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
extern void func_PAL_L09_0040E1C0(char *);

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
extern void func_PAL_002A7E68(void *, int, int, int);
extern void path_sample_position(void *, int, void *, void *, int, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_free_point_light(int);
extern void moby_mark_spawned(void *);
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
void func_PAL_L09_0040E300(char *obj)
{
    char *d = *(char **)(obj+0x68);
    char *r;
    float distance, angle, inverse;
    Quad_Dobbo target;
    switch (B(obj,0x20)) {
    case 0: {
        DobboPath *path;
        path = g_path_l09_table[I(d,0x260)];
        I(d,0x268)=0;
        *(DobboPath **)(d+0x26c)=path;
        distance = fast_vec_dist(path->points[0],path->points[1]);
        inverse = 1.0f / distance;
        F(d,0x29c)=(inverse*0.020000001f)*F(d,0x264);
        I(d,0x274)=part_l00_alloc_effect_slot_2(obj+0x10,F(d,0x278),F(d,0x288),F(d,0x27c),F(d,0x280),F(d,0x284));
        moby_set_state(obj,2,-1);
        break;
    }
    case 2:
        if (g_hero_state.mode==0x31) {
            r=g_hero_state.target;
            if(r && *(short *)(r+0xaa)==0x905 && B(r,0x20)!=0xfe && B(r,0x20)!=0xfd) {
                B(obj,0x30)=0xff; *(short *)(obj+0x32)=0x3ff; I(d,0x268)=0;
                if(((DobboAnimation *)obj)->animation!=4) func_PAL_002A7E68(obj,4,0,10);
                moby_set_state(obj,1,-1);
            }
        }
    case 3:
        if(((DobboAnimation *)obj)->animation==0 && math_fast_float_d(d+0x298)) {
                I(d,0x298)=FloatToInt(((math_random_float_range(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
                { int state=(func_001163B0()&1)+1;
                  if(((DobboAnimation *)obj)->animation!=state) func_PAL_002A7E68(obj,state,0,8); }
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=0) func_PAL_002A7E68(obj,0,0,8);
        }
        angle=mat_fast_helper_a(g_hero_state.position[0]-F(obj,0x10),g_hero_state.position[1]-F(obj,0x14));
        F(obj,0xf8)=FastAddRotations(F(obj,0xf8),fast_subtract_rotations(angle,F(obj,0xf8))*0.01f);
        break;
    case 1: {
        DobboPath *path;
        DobboPathEffect *effect;
        if(((DobboAnimation *)obj)->animation==4 && math_fast_float_d(d+0x298)) {
                I(d,0x298)=FloatToInt(((math_random_float_range(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
                if(((DobboAnimation *)obj)->animation!=2) func_PAL_002A7E68(obj,2,0,8);
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=4) func_PAL_002A7E68(obj,4,0,10);
        }
        path=*(DobboPath **)(d+0x26c);
        path_sample_position(path,1,obj+0x10,obj+0xf0,0,F(d,0x268));
        distance=fast_vec_dist(obj+0x10,g_hero_state.position);
        if(distance<10.0f) F(d,0x29c)*=1.01f;
        else if(distance>30.0f) F(d,0x29c)*=0.99f;
        else {
            path=*(DobboPath **)(d+0x26c);
            distance = fast_vec_dist(path->points[0],path->points[1]);
            inverse = 1.0f / distance;
            F(d,0x29c)+=((inverse*0.020000001f)*F(d,0x264)-F(d,0x29c))*0.05f;
        }
        F(d,0x268)+=F(d,0x29c);
        effect=&g_sound_effect_table[I(d,0x274)];
        qcopy(effect->position,obj+0x10);
        effect->position[3]=F(d,0x278);
        effect->dimensions[0]=F(d,0x27c);
        effect->dimensions[1]=F(d,0x280);
        effect->dimensions[2]=F(d,0x284);
        effect->flags=0;
        if(FloatToInt(F(d,0x268))+2>=(*(DobboPath **)(d+0x26c))->count) B(obj,0xbc)=1;
        break;
    }
    }
    if(((DobboAnimation *)obj)->animation==0) {
        if(vec_distance_xy(obj+0x10,g_hero_state.position)<8.0f &&
           FastDiffRots(F(obj,0xf8),mat_fast_helper_a(g_hero_state.aim[0]-F(obj,0x10),g_hero_state.aim[1]-F(obj,0x14)))<1.5707965f) {
            if(FastVecLength(g_hero_state.velocity)>0.01f) I(d,0x290)=100;
            else math_fast_float_d(d+0x290);
        } else if(I(d,0x290)) { I(d,0x290)=0; qcopy(d+0x250,g_hero_state.aim); }
        if(math_fast_float_d(d+0x294)) {
            I(d,0x294)=FloatToInt(((math_random_float_range(180.0f,300.0f)) * 5.0f + 2.0f) * 0.16666667f);
            angle=FastAddRotations(F(obj,0xf8),math_random_float_range(-90.0f,90.0f)*0.017453294f);
            distance=math_random_float_range(0.0f,30.0f)*0.017453294f;
            vec_build_spherical_offset(d+0x250,6.0f,angle,distance);
            FastVecAdd(d+0x250,d+0x250,obj+0x10);
        }
        if (I(d,0x290))
            qcopy(&target,g_hero_state.aim);
        else
            qcopy(&target,d+0x250);
    }
    if(B(obj,0xbc)) { gfx_free_point_light(I(d,0x274)); moby_mark_spawned(obj); }
    else func_PAL_L09_0040E1C0(obj);
}
#undef F
#undef I
#undef B
