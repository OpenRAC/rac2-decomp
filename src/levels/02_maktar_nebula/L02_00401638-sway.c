#include "common.h"
extern char g_hero_position[];
extern void moby_set_state(char *,int,int);
extern float ApproachValue(float *,float,float);
extern int math_fast_float_d(void *);
extern char *g_route_polygons[];
extern char D_L02_001A8F20[] MACRO_ADDR, g_camera_l02_position[];
extern float fast_vec_dist(void *, void *);
extern int FloatToInt(float);
extern float mat_fast_helper_a(float,float), FastDiffRots(float,float);
extern int IsPointInCuboid(void *,int);
extern void *group_find_entity_in_state(int);
extern void math_step_value_toward_target(float *,float *,float,float,float,float);
extern void path_sample_position(void *,int,void *,void *,int,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern int PlayMobySound(int,int,void *);
extern void actor_reset_pose_register_child(void *,void *);
extern int moby_count_group_not_in_state(int,int);
extern void moby_mark_spawned(char *);
extern void sway_apply_wobble(char *),part_spawn_spark_bursts(char *,void *);
extern void FastVecSub(void *,void *,void *);
extern void *part_find_owned_effect_slot(void *,u32,s32);
extern float moby_update_aim_target_strength(void *,void *);
extern void part_spawn_masked_debris(char *,int,void *,u8,float,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_blast_effect_moby(void *,void *,void *,float);
/* Moves a swaying object along a preset path, drops a spawned item at the end, then lets the object fall apart and disappear. Update handler of moby class 2934. */
void sway_path_update(char *moby) {
    float oldPos[4] __attribute__((aligned(16))), scratch[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby+0x68), *path;
    float x,y,z,t;
    void *spawned;
    if ((unsigned)(*(u8 *)(moby+0x20)-2)<3) qcopy(&oldPos,moby+0x10);
    switch (*(u8 *)(moby+0x20)) {
    case 0: {
        float inv;
        if (!*(s16 *)(vars+0x24)) { *(s16 *)(vars+0x24)=40; *(float *)(vars+0x20)=40.0f; }
        moby_set_state(moby,1,-1);
        *(int *)(vars+0x16c)=-1;
        path=g_route_polygons[*(int *)(vars+0x100)];
        *(char **)(vars+0x164)=path;
        inv=fast_vec_dist(path+0x10,path+0x20);
        inv=1.0f/inv;
        *(float *)(vars+0x15c)=inv*0.5f;
        *(float *)(vars+0x154)=inv*0.0013888889f;
        *(float *)(vars+0x158)=inv*0.0027777778f;
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
        x=*(float *)(vars+0x150)*60.0f;
        x+=*(float *)(vars+0x14c);
        { float limit=(float)(**(int **)(vars+0x164)-2); if(limit<x)x=limit; }
        y=x+1.0f;
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lowPoint=path+lowIndex*16;
            path+=highIndex*16;
            z=*(float *)(path+0x10)-*(float *)(lowPoint+0x10);
        }
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(vars+0x164);
            char *lowPoint=path+lowIndex*16;
            path+=highIndex*16;
            t=*(float *)(path+0x14);
            t=mat_fast_helper_a(z,t-*(float *)(lowPoint+0x14));
        }
        t=1.0f-FastDiffRots(t,*(float *)(vars+0x138)); if(t<0.1f)t=0.1f;
        math_step_value_toward_target((float *)(vars+0x14c),(float *)(vars+0x150),(float)**(int **)(vars+0x164)-1.0f,*(float *)(vars+0x154),*(float *)(vars+0x158),t**(float *)(vars+0x15c));
        path_sample_position(*(void **)(vars+0x164),0,vars+0x120,vars+0x130,0,*(float *)(vars+0x14c));
        if(*(float *)(vars+0x14c)>=(float)**(int **)(vars+0x164)-1.0f)moby_set_state(moby,3,-1);
        break;
    case 3:
        if(*(int *)(vars+0x110)!=-1 && math_fast_float_d(vars+0x168)) {
            spawned=group_find_entity_in_state(*(int *)(vars+0x110));
            if(spawned){ qcopy(&scratch,moby+0x10); scratch[2]=coll_probe_ground_height_below(&scratch,0,0.5f);PlayMobySound(0,0,moby);actor_reset_pose_register_child(spawned,&scratch);*(int *)(vars+0x168)=120; }
            else if(!moby_count_group_not_in_state(*(int *)(vars+0x110),-1))moby_set_state(moby,4,-1);
        }
        break;
    case 4:
        ApproachValue((float *)(vars+0x11c),0.16666667f,0.0013888889f);
        *(float *)(vars+0x128)+=*(float *)(vars+0x11c);
        if(!*(u8 *)(moby+0x31)){moby_mark_spawned(moby);return;}
    }
    *(float *)(moby+0x2c)=*(float *)(*(char **)(moby+0x24)+0x24)*1.5f;
    if(*(u8 *)(moby+0x31)||*(u8 *)(moby+0x20)==2||*(u8 *)(moby+0x20)==4)sway_apply_wobble(moby);
    if(*(u8 *)(moby+0x31)) {
        if(*(u8 *)(moby+0x20)<2)return;
        if(*(u8 *)(moby+0x20)<5){FastVecSub(&scratch,moby+0x10,&oldPos);part_spawn_spark_bursts(moby,&scratch);}
    }
    if(*(u8 *)(moby+0x20)>=2){
        void *hitMoby=part_find_owned_effect_slot(moby,0x10000,0); x=moby_update_aim_target_strength(moby,hitMoby);
        ApproachValue((float *)(vars+0x20),0.0f,x); *(u8 *)(moby+0xa8)=255;
        if(*(float *)(vars+0x20)==0.0f){PlayMobySound(2,0,moby);part_spawn_masked_debris(moby,0x7f7,D_L02_001A8F20,255,5.0f,10.0f,5.0f,10.0f);FastVecSub(&scratch,g_camera_l02_position,moby+0x10);vec_scale_to_length(&scratch,&scratch,1.0f);part_spawn_blast_effect_moby(moby,moby+0x10,&scratch,0.0f);moby_mark_spawned(moby);}
    }
}


