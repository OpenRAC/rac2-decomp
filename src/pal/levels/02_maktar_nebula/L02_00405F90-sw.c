#include "include_asm.h"

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
extern void func_PAL_L02_00406558(char *),func_PAL_L02_00406698(char *,void *);
extern void FastVecSub(void *,void *,void *);
extern void *part_find_owned_effect_slot(void *,u32,s32);
extern float func_PAL_002AA108(void *,void *);
extern void func_PAL_002B15D8(char *,int,void *,u8,float,float,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void func_PAL_0032F3B8(void *,void *,void *,float);

void func_PAL_L02_00405F90(char *e) {
    float old[4] __attribute__((aligned(16))), temp[4] __attribute__((aligned(16)));
    char *s = *(char **)(e+0x68), *p;
    float x,y,z,t;
    void *obj;
    if ((unsigned)(*(u8 *)(e+0x20)-2)<3) qcopy(&old,e+0x10);
    switch (*(u8 *)(e+0x20)) {
    case 0: {
        float inv;
        if (!*(s16 *)(s+0x24)) { *(s16 *)(s+0x24)=40; *(float *)(s+0x20)=40.0f; }
        moby_set_state(e,1,-1);
        *(int *)(s+0x16c)=-1;
        p=g_route_polygons[*(int *)(s+0x100)];
        *(char **)(s+0x164)=p;
        inv=fast_vec_dist(p+0x10,p+0x20);
        inv=1.0f/inv;
        *(float *)(s+0x15c)=inv*0.6f;
        *(float *)(s+0x154)=inv*0.002f;
        *(float *)(s+0x158)=inv*0.004f;
        *(float *)(s+0x160)=inv;
        *(int *)(s+0x150)=0;
        qcopy(s+0x120,*(char **)(s+0x164)+0x10);
        *(int *)(e+0x98)=0;
        *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
        break; }
    case 1:
        if (IsPointInCuboid(g_hero_position,*(int *)(s+0x104))) {
            if (!group_find_entity_in_state(*(int *)(s+0x110))) {moby_mark_spawned(e);return;}
            math_step_value_toward_target((float *)(s+0x14c),(float *)(s+0x150),(float)**(int **)(s+0x164)-1.0f,*(float *)(s+0x15c),*(float *)(s+0x158),*(float *)(s+0x15c));
            *(int *)(s+0x14c)=0; moby_set_state(e,2,-1);
            *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)&0xffbe)|0x1000;
            *(int *)(e+0x98)=*(int *)(*(char **)(e+0x24)+0x10);
        }
        break;
    case 2:
        x=*(float *)(s+0x150)*5e+01f;
        x+=*(float *)(s+0x14c);
        { float limit=(float)(**(int **)(s+0x164)-2); if(limit<x)x=limit; }
        y=x+1.0f;
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(s+0x164);
            char *lo=path+lowIndex*16;
            path+=highIndex*16;
            z=*(float *)(path+0x10)-*(float *)(lo+0x10);
        }
        {
            int highIndex=FloatToInt(y);
            int lowIndex=FloatToInt(x);
            char *path=*(char **)(s+0x164);
            char *lo=path+lowIndex*16;
            path+=highIndex*16;
            t=*(float *)(path+0x14);
            t=mat_fast_helper_a(z,t-*(float *)(lo+0x14));
        }
        t=1.0f-FastDiffRots(t,*(float *)(s+0x138)); if(t<0.1f)t=0.1f;
        math_step_value_toward_target((float *)(s+0x14c),(float *)(s+0x150),(float)**(int **)(s+0x164)-1.0f,*(float *)(s+0x154),*(float *)(s+0x158),t**(float *)(s+0x15c));
        path_sample_position(*(void **)(s+0x164),0,s+0x120,s+0x130,0,*(float *)(s+0x14c));
        if(*(float *)(s+0x14c)>=(float)**(int **)(s+0x164)-1.0f)moby_set_state(e,3,-1);
        break;
    case 3:
        if(*(int *)(s+0x110)!=-1 && math_fast_float_d(s+0x168)) {
            obj=group_find_entity_in_state(*(int *)(s+0x110));
            if(obj){ qcopy(&temp,e+0x10); temp[2]=coll_probe_ground_height_below(&temp,0,0.5f);PlayMobySound(0,0,e);actor_reset_pose_register_child(obj,&temp);*(int *)(s+0x168)=100; }
            else if(!moby_count_group_not_in_state(*(int *)(s+0x110),-1))moby_set_state(e,4,-1);
        }
        break;
    case 4:
        ApproachValue((float *)(s+0x11c),0.20000002f,0.002f);
        *(float *)(s+0x128)+=*(float *)(s+0x11c);
        if(!*(u8 *)(e+0x31)){moby_mark_spawned(e);return;}
    }
    *(float *)(e+0x2c)=*(float *)(*(char **)(e+0x24)+0x24)*1.5f;
    if(*(u8 *)(e+0x31)||*(u8 *)(e+0x20)==2||*(u8 *)(e+0x20)==4)func_PAL_L02_00406558(e);
    if(*(u8 *)(e+0x31)) {
        if(*(u8 *)(e+0x20)<2)return;
        if(*(u8 *)(e+0x20)<5){FastVecSub(&temp,e+0x10,&old);func_PAL_L02_00406698(e,&temp);}
    }
    if(*(u8 *)(e+0x20)>=2){
        void *hit=part_find_owned_effect_slot(e,0x10000,0); x=func_PAL_002AA108(e,hit);
        ApproachValue((float *)(s+0x20),0.0f,x); *(u8 *)(e+0xa8)=255;
        if(*(float *)(s+0x20)==0.0f){PlayMobySound(2,0,e);func_PAL_002B15D8(e,0x7f7,D_L02_001A8F20,255,5.0f,10.0f,5.0f,10.0f);FastVecSub(&temp,g_camera_l02_position,e+0x10);vec_scale_to_length(&temp,&temp,1.0f);func_PAL_0032F3B8(e,e+0x10,&temp,0.0f);moby_mark_spawned(e);}
    }
}
