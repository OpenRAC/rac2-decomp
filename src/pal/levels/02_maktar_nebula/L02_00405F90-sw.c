#include "include_asm.h"

#include "common.h"
extern char g_hero_position[];
extern void moby_set_state(char *,int,int);
extern float ApproachValue(float *,float,float);
extern int math_fast_float_d(void *);
extern char *g_route_polygons[];
extern char g_zero_l02_vector[] MACRO_ADDR, g_camera_l02_position[];
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern float mat_fast_helper_a(float,float), FastDiffRots(float,float);
extern int IsPointInCuboid(void *,int);
extern void *group_find_entity_in_state(int);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
extern void path_sample_position(void *,int,void *,void *,int,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern int PlayMobySound(int,int,void *);
extern void actor_reset_pose_register_child(void *,void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_mark_spawned(char *);
extern void sway_apply_wobble_pal(char *),part_spawn_spark_bursts_pal(char *,void *);
extern void FastVecSub(void *,void *,void *);
extern void *part_find_owned_effect_slot(void *,u32,s32);
extern float moby_update_aim_target_strength_pal(void *,void *);
extern void part_spawn_masked_debris_pal(char *,int,void *,u8,float,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern char *part_spawn_blast_effect_moby_pal(void *,void *,void *,float);

/* Updates the swaying platform: it waits for the hero to enter its area, follows its path while
   spawned entities ride along, falls apart when done, and blows up once its health is gone
   (PAL copy of sway_path_update). */
void sway_path_update_pal(char *moby) {
    float old[4] __attribute__((aligned(16))), temp[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby+0x68), *route;
    float x,y,z,t;
    void *obj;
    if ((unsigned)(*(u8 *)(moby+0x20)-2)<3) qcopy(&old,moby+0x10);
    switch (*(u8 *)(moby+0x20)) {
    case 0: {
        float inv;
        if (!*(s16 *)(vars+0x24)) { *(s16 *)(vars+0x24)=40; *(float *)(vars+0x20)=40.0f; }
        moby_set_state(moby,1,-1);
        *(int *)(vars+0x16c)=-1;
        route=g_route_polygons[*(int *)(vars+0x100)];
        *(char **)(vars+0x164)=route;
        inv=fast_vec_dist(route+0x10,route+0x20);
        inv=1.0f/inv;
        *(float *)(vars+0x15c)=inv*0.6f;
        *(float *)(vars+0x154)=inv*0.002f;
        *(float *)(vars+0x158)=inv*0.004f;
        *(float *)(vars+0x160)=inv;
        *(int *)(vars+0x150)=0;
        qcopy(vars+0x120,*(char **)(vars+0x164)+0x10);
        *(int *)(moby+0x98)=0;
        *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
        break; }
    case 1:
        if (IsPointInCuboid(g_hero_position,*(int *)(vars+0x104))) {
            if (!group_find_entity_in_state(*(int *)(vars+0x110))) {moby_mark_spawned(moby);return;}
            math_step_value_toward_target((float *)(vars+0x14c),(float *)(vars+0x150),(float)**(int **)(vars+0x164)-1.0f,*(float *)(vars+0x15c),*(float *)(vars+0x158),*(float *)(vars+0x15c));
            *(int *)(vars+0x14c)=0; moby_set_state(moby,2,-1);
            *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)&0xffbe)|0x1000;
            *(int *)(moby+0x98)=*(int *)(*(char **)(moby+0x24)+0x10);
        }
        break;
    case 2:
        x=*(float *)(vars+0x150)*5e+01f;
        x+=*(float *)(vars+0x14c);
        { float limit=(float)(**(int **)(vars+0x164)-2); if(limit<x)x=limit; }
        y=x+1.0f;
        {
            int high_index=FloatToInt(y);
            int low_index=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lo=path+low_index*16;
            path+=high_index*16;
            z=*(float *)(path+0x10)-*(float *)(lo+0x10);
        }
        {
            int high_index=FloatToInt(y);
            int low_index=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lo=path+low_index*16;
            path+=high_index*16;
            t=*(float *)(path+0x14);
            t=mat_fast_helper_a(z,t-*(float *)(lo+0x14));
        }
        t=1.0f-FastDiffRots(t,*(float *)(vars+0x138)); if(t<0.1f)t=0.1f;
        math_step_value_toward_target((float *)(vars+0x14c),(float *)(vars+0x150),(float)**(int **)(vars+0x164)-1.0f,*(float *)(vars+0x154),*(float *)(vars+0x158),t**(float *)(vars+0x15c));
        path_sample_position(*(void **)(vars+0x164),0,vars+0x120,vars+0x130,0,*(float *)(vars+0x14c));
        if(*(float *)(vars+0x14c)>=(float)**(int **)(vars+0x164)-1.0f)moby_set_state(moby,3,-1);
        break;
    case 3:
        if(*(int *)(vars+0x110)!=-1 && math_fast_float_d(vars+0x168)) {
            obj=group_find_entity_in_state(*(int *)(vars+0x110));
            if(obj){ qcopy(&temp,moby+0x10); temp[2]=coll_probe_ground_height_below(&temp,0,0.5f);PlayMobySound(0,0,moby);actor_reset_pose_register_child(obj,&temp);*(int *)(vars+0x168)=100; }
            else if(!moby_count_group_not_in_state(*(int *)(vars+0x110),-1))moby_set_state(moby,4,-1);
        }
        break;
    case 4:
        ApproachValue((float *)(vars+0x11c),0.20000002f,0.002f);
        *(float *)(vars+0x128)+=*(float *)(vars+0x11c);
        if(!*(u8 *)(moby+0x31)){moby_mark_spawned(moby);return;}
    }
    *(float *)(moby+0x2c)=*(float *)(*(char **)(moby+0x24)+0x24)*1.5f;
    if(*(u8 *)(moby+0x31)||*(u8 *)(moby+0x20)==2||*(u8 *)(moby+0x20)==4)sway_apply_wobble_pal(moby);
    if(*(u8 *)(moby+0x31)) {
        if(*(u8 *)(moby+0x20)<2)return;
        if(*(u8 *)(moby+0x20)<5){FastVecSub(&temp,moby+0x10,&old);part_spawn_spark_bursts_pal(moby,&temp);}
    }
    if(*(u8 *)(moby+0x20)>=2){
        void *hit=part_find_owned_effect_slot(moby,0x10000,0); x=moby_update_aim_target_strength_pal(moby,hit);
        ApproachValue((float *)(vars+0x20),0.0f,x); *(u8 *)(moby+0xa8)=255;
        if(*(float *)(vars+0x20)==0.0f){PlayMobySound(2,0,moby);part_spawn_masked_debris_pal(moby,0x7f7,g_zero_l02_vector,255,5.0f,10.0f,5.0f,10.0f);FastVecSub(&temp,g_camera_l02_position,moby+0x10);vec_scale_to_length(&temp,&temp,1.0f);part_spawn_blast_effect_moby_pal(moby,moby+0x10,&temp,0.0f);moby_mark_spawned(moby);}
    }
}
