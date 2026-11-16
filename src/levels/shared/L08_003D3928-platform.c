#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { u8 pad[0x88]; float z; u8 pad2[0x2b0]; int object; int state; } EHero;
extern EHero g_hero_state;
typedef struct { u8 pad[0x74]; u8 active; u8 pad2[0x13]; int object; } ESound;
extern u8 g_sound_state[];
extern u8 *g_collision_box_table __attribute__((sda));
extern float math_fabs(float);
extern int FloatToInt(float);
extern void moby_set_state(void *, int, int);
extern int PlayMobySound(int, int, void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_move_angle_toward_target(float, float, float);
extern void snd_stop_voice(int);
extern void mat_combine_and_store(void *, void *, void *, void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
typedef struct { u8 pad[0x60]; TI128 pos; TI128 rot; int index; float duration; float progress; u8 pad2[2]; u8 trigger; u8 side; int sound; } EPlatform;
typedef struct { u8 pad[0xf0]; float rx, ry, rz; } EMob;
/* Moves a platform back and forth between two spots when the hero stands on it,
   playing a sound while it moves. */
void moving_platform_update(u8 *moby)
{
    TI128 old_pos, old_rot, delta;
    EPlatform *platform = *(EPlatform **)(moby+0x68);
    float dist_to_start,dist_to_end,blend;
    qcopy(&old_pos,moby+0x10);
    qcopy(&old_rot,moby+0xf0);
    switch(moby[0x20]) {
    case 0:
        platform->sound=-1;
        qcopy(&platform->pos,moby+0x10);
        qcopy(&platform->rot,moby+0xf0);
        if(E_F((u8 *)platform,0x68)<E_F(g_collision_box_table+platform->index*128,0x38)) platform->side=0; else platform->side=1;
        platform->progress=0;
        moby[0xbc]=0;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        dist_to_start=math_fabs(E_F((u8 *)platform,0x68)-g_hero_state.z);
        dist_to_end=math_fabs(E_F(g_collision_box_table+platform->index*128,0x38)-g_hero_state.z);
        if (((!platform->trigger || FloatToInt(platform->progress)==platform->side) && g_hero_state.object==(int)moby && g_hero_state.state!=0) ||
            (platform->progress<0.1f && dist_to_end<dist_to_start) || (platform->progress>0.9f && dist_to_start<dist_to_end)) {
            moby[0xbc]^=1;
            moby_set_state(moby,2,-1);
        }
        break;
    case 2:
        if(((ESound *)(g_sound_state+platform->sound*0x70))->object!=(int)moby || !((ESound *)(g_sound_state+platform->sound*0x70))->active)
            platform->sound=PlayMobySound(0,4,moby);
        if(moby[0xbc]) platform->progress+=1.0f/platform->duration;
        else platform->progress-=1.0f/platform->duration;
        if(platform->progress>1.0f) platform->progress=1.0f;
        else if(platform->progress<0.0f) platform->progress=0.0f;
        blend=(1.0f-math_fast_sin_or_cos_a(platform->progress*3.141592741f))*0.5f;
        FastVecSub(&delta,g_collision_box_table+platform->index*128+0x30,&platform->pos);
        FastVecScale(&delta,&delta,blend);
        FastVecAdd(moby+0x10,&platform->pos,&delta);
        ((EMob*)moby)->rz=math_move_angle_toward_target(E_F((u8 *)platform,0x78),E_F(g_collision_box_table+platform->index*128,0x78),blend);
        ((EMob*)moby)->ry=math_move_angle_toward_target(E_F((u8 *)platform,0x74),E_F(g_collision_box_table+platform->index*128,0x74),blend);
        ((EMob*)moby)->rx=math_move_angle_toward_target(E_F(platform,0x70),E_F(g_collision_box_table+platform->index*128,0x70),blend);
        if(moby[0xbc] ? platform->progress>=1.0f : platform->progress<=0.0f) {
            int i=platform->sound;
            if(i!=-1 && ((ESound *)(g_sound_state+i*0x70))->object==(int)moby && ((ESound *)(g_sound_state+i*0x70))->active) snd_stop_voice(i);
            platform->sound=-1;
            if(*(short *)(moby+0xaa)!=0xd49 /* moby class 3401 */) PlayMobySound(1,0,moby);
            moby_set_state(moby,3,-1);
        }
        break;
    case 3:
        if(g_hero_state.object!=(int)moby) moby_set_state(moby,1,-1);
        break;
    }
    if(moby[0x20]<4) {
        FastVecSub(&delta,moby+0x10,&old_pos);
        mat_combine_and_store((u8 *)platform+0x20,&delta,&old_rot,moby+0xf0);
    }
}


