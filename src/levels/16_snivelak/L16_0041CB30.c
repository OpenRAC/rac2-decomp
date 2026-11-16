#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct { Quad16 vector; int owner,flags; unsigned char enabled,kind; unsigned short id; float distance; int active; } CollisionRequest;
typedef struct { Vector128 beam; CollisionRequest request; Vector128 closest; } LaserWorkspace;
extern char g_sound_state[];
extern char *g_aim_target_moby;
extern char *g_hero_moby;
extern char *g_sweeping_laser_target_a MACRO_ADDR;
extern char *g_sweeping_laser_target_b MACRO_ADDR;
extern Quad16 g_particle_template MACRO_ADDR;
extern float FastAddRotations(float,float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int snd_play_from_class_bank(int,int,char *,int);
extern float vec_spring_to_target(void *,void *,void *,float,float,float);
extern float vec_distance_xy(void *,void *);
extern void moby_set_state(unsigned char *,int,int);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern void DrawBeamQuads(void *);
extern void make_hit_descriptor(char *,int,int,float,Quad16 *);
extern int CollLine(void *,void *,int,void *,void *);
extern float math_closest_point_on_segment(void *,void *,void *,void *);
extern void tracked_moby_set_state(int,int);
extern void global_object_start(char *,int);
/* Swings a laser beam between two points, plays its sound, and hurts whatever the beam touches. */
void sweeping_laser_update(char *object)
{
    LaserWorkspace local;
    char *state=*(char **)(object+0x68);
    char *target;
    char *sound,*sound2,*sound4;
    int handle;
    switch(*(unsigned char *)(object+0x20)) {
    case 0:
        *(float *)(object+0x18)+=0.57f;
        qcopy(state,(object+0x10));
        ((float *)&local.beam)[0]=math_fast_sin_or_cos_a(FastAddRotations(*(float *)(object+0xf8),1.570796490f))*9.5f;
        ((float *)&local.beam)[1]=math_fast_sin_or_cos_b(FastAddRotations(*(float *)(object+0xf8),1.570796490f))*9.5f;
        ((float *)&local.beam)[2]=0.0f;
        FastVecAdd(state+0x10,((float *)&local.beam),object+0x10);
        *(int *)(state+0x24)=-1;
        *(int *)(state+0x28)=-1;
        moby_set_state((unsigned char *)object,1,-1);
        break;
    case 1:
        sound4=g_sound_state+0x70**(int *)(state+0x24);
        if((*(char **)(sound4+0x88))!=object || (*(unsigned char *)(sound4+0x74))==0) *(int *)(state+0x24)=snd_play_from_class_bank(0,4,object,0x113a);
        vec_spring_to_target(object+0x10,state+0x10,state+0x20,0.001111111138f,0.002222222276f,0.06666667014f);
        if(vec_distance_xy(object+0x10,state+0x10)<0.03333333507f) moby_set_state((unsigned char *)object,2,-1);
        break;
    case 2:
        sound2=g_sound_state+0x70**(int *)(state+0x24);
        if((*(char **)(sound2+0x88))!=object || (*(unsigned char *)(sound2+0x74))==0) *(int *)(state+0x24)=snd_play_from_class_bank(0,4,object,0x113a);
        vec_spring_to_target(object+0x10,state,state+0x20,0.001111111138f,0.002222222276f,0.06666667014f);
        if(vec_distance_xy(object+0x10,state)<0.03333333507f) moby_set_state((unsigned char *)object,1,-1);
        break;
    }
    gfx_add_draw_callback_first(DrawBeamQuads,object);
    make_hit_descriptor((char *)&local.request,(int)object,1,4.0f,&g_particle_template);
    local.request.id=*(unsigned short *)(object+0xaa);
    ((float *)&local.beam)[0]=math_fast_sin_or_cos_a(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.beam)[1]=math_fast_sin_or_cos_b(*(float *)(object+0xf8))*25.0f;
    ((float *)&local.beam)[2]=0.0f;
    FastVecAdd(((float *)&local.beam),object+0x10,((float *)&local.beam));
    if(CollLine(object+0x10,((float *)&local.beam),0,object,&local.request)!=0 && g_aim_target_moby==g_hero_moby) {
        handle=*(int *)(state+0x28);
        if(handle!=-1) {
            sound=g_sound_state+handle*0x70;
            if((*(char **)(sound+0x88))==object && (*(unsigned char *)(sound+0x74))!=0) goto sound_ready;
        }
        *(int *)(state+0x28)=snd_play_from_class_bank(1,0,object,0x113a);
    }
sound_ready:
    target=g_sweeping_laser_target_a;
    if(target==0) target=g_sweeping_laser_target_b;
    if(target!=0) {
        math_closest_point_on_segment(&local.closest,object+0x10,((float *)&local.beam),target+0x10);
        if(vec_distance_xy(&local.closest,target+0x10)<0.15f) {
            if(*(short *)(target+0xaa)==0xb58) {
                if(*(unsigned char *)(target+0x20)!=5) tracked_moby_set_state(1,2);
            } else if(*(unsigned char *)(target+0x20)!=5) global_object_start((char *)1,2);
        }
    }
}
