#include "common.h"
typedef struct { u8 bytes[16]; } InitBytes;
typedef struct { float data[12]; } InitBlock;
extern InitBytes D_L12_001B1848;
extern u8 D_L12_001A8F20[] MACRO_ADDR;
extern void *D_L12_001FEAC0[];
extern float D_L12_001B17F0 __attribute__((sda));
extern float D_L12_001B17F4 __attribute__((sda)),D_L12_001B17F8 __attribute__((sda)),D_L12_001B1804 __attribute__((sda)),D_L12_001B1808 __attribute__((sda)),D_L12_001B180C __attribute__((sda));
extern int FloatToInt(float),func_001163B0(void),math_random_int_range(int,int);
extern u8 *CreateMoby(int),*part_spawn_flying_fragment(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(u8 *);
extern int part_spawn_damage_debris(void *,void *,void *),enemy_select_path(void *,int,int);
extern void FastVecSub(void *,void *,void *), shared_counter_release(void *), moby_set_state(void *,int,int), guard_switch_animation(void *,int,int,int);
extern void moby_transform_joint_to_world(void *,int,void *);
/* Sets up a creature moby on creation: its stats and animations, then it spawns a helper moby
   (moby class 4427) with two small child mobies attached to it. */
void InitStateDataWithPartner(u8 *creature) {
    u8 *vars=*(u8 **)(creature+0x68), *spawned,*spawned_vars; InitBytes init_bytes=D_L12_001B1848; float attach_pos[4]; int child_index,byte_index; u8 *parameters; float acceleration; int animation=9; float slow=0.004166666883975267f;
    *(float *)(creature+0x2C)*=D_L12_001B17F0;
    vars[0x60]=14;
    *(int *)(vars+0x98)=animation;
    vars[0x61]=18;
    vars[0x62]=17;
    vars[0x66]=20;
    vars[0x67]=255;
    *(float *)(vars+0x6C)=0.36666667461395264f;
    *(float *)(vars+0x70)=0.11666667461395264f;
    *(float *)(vars+0x74)=slow;
    *(float *)(vars+0x78)=0.008333333767950535f;
    *(float *)(vars+0x7C)=slow;
    *(float *)(vars+0x8C)=0.4f;
    vars[0xBC]=5;
    vars[0xBD]=animation;
    vars[0xBE]=4;
    vars[0xBF]=7;
    vars[0xC2]=10;
    vars[0xC3]=17;
    *(float *)(vars+0x90)=*(float *)(vars+0x310);
    *(float *)(vars+0xF8)=0.45f;
    vars[0x28]=3;
    *(u8 **)(vars+0x2F8)=0;
    *(u8 **)(vars+0x2F0)=0;
    *(u8 **)(vars+0x2F4)=0;
    *(float *)(vars+0x80)=0.7f;
    *(float *)(vars+0x84)=0.7f;
    *(float *)(vars+0x30)=1.7f;
    vars[0x2A]=2;
    vars[0x2E]=1;
    vars[0x4D]=0;
    vars[0x2F]=8;
    vars[0x48]=FloatToInt(25.0f);vars[0x4A]=FloatToInt(16.0f);
    { float value_a,value_b,value_c,value_d;
    acceleration=D_L12_001B180C*0.00027777778450399637f;
    vars[0x1E8]=12;vars[0x1E9]=11;
    value_b=D_L12_001B17F8*0.01666666753590107f;value_c=D_L12_001B1804*0.000004848137454391923f;
    value_d=D_L12_001B1808*0.0002908882452175021f;value_a=D_L12_001B17F4*0.00027777778450399637f;
    *(float *)(vars+0x100)=0.7f;*(float *)(vars+0x104)=0.5f;*(float *)(vars+0x108)=0.5f;*(float *)(vars+0x10C)=0.5f;
    *(float *)(vars+0x110)=0.7853982448577881f;*(float *)(vars+0x130)=0.349065899848938f;
    *(float *)(vars+0x12C)=acceleration;
    moby_set_controller_speed_limits(creature,value_a,value_b,value_c,value_d); }
    *(int *)(vars+0x138)|=0x80;*(int *)(vars+0x1DC)=0;*(float *)(vars+0x1D4)=3.0f;
    *(u16 *)(vars+0x1E4)=0;*(u16 *)(vars+0x1E2)=0;*(int *)(vars+0x1D0)=0;
    if(*(int *)(vars+0x2BC)!=-1)path_l01_compute_segment_lengths(D_L12_001FEAC0[*(int *)(vars+0x2BC)]);
    if(*(int *)(vars+0x2B4)!=-1)path_l01_compute_segment_lengths(D_L12_001FEAC0[*(int *)(vars+0x2B4)]);
    if(*(int *)(vars+0x2B8)!=-1)path_l01_compute_segment_lengths(D_L12_001FEAC0[*(int *)(vars+0x2B8)]);
    spawned=CreateMoby(0x114B /* moby class 4427 */);
    if(spawned) {
        *(u8 **)(vars+0x2F8)=spawned;*(u16 *)(spawned+0x32)=*(u16 *)(creature+0x32);spawned[0x30]=creature[0x30];
        *(u64 *)(spawned+0x38)=*(u64 *)(creature+0x38);*(int *)(spawned+0x78)=*(int *)(creature+0x78);spawned[0x31]=1;
        *(float *)(spawned+0x2C)*=D_L12_001B17F0;
        moby_transform_joint_to_world(creature,0,spawned+0x10);qcopy(spawned+0xF0,creature+0xF0);
        spawned_vars=*(u8 **)(spawned+0x68);*(InitBlock *)(spawned_vars+0x20)=*(InitBlock *)(vars+0x20);
        *(float *)(spawned_vars+0x20)=*(float *)(vars+0x20);*(u16 *)(spawned_vars+0x24)=*(u16 *)(vars+0x24);spawned_vars[0x28]=vars[0x28];
        *(float *)(spawned_vars+0x30)=0.7f;spawned_vars[0x2F]=4;spawned_vars[0x2A]=2;spawned_vars[0x4A]=3;spawned_vars[0x4D]=1;*(u8 **)(spawned_vars+0x70)=creature;
        for(child_index=0;child_index<2;child_index++) {
            u8 *child;
            moby_transform_joint_to_world(*(u8 **)(vars+0x2F8),child_index,attach_pos);FastVecSub(attach_pos,attach_pos,*(u8 **)(vars+0x2F8)+0x10);
            child=part_spawn_flying_fragment(*(u8 **)(vars+0x2F8),0xD66,attach_pos,D_L12_001A8F20,0,0,D_L12_001A8F20,D_L12_001A8F20,D_L12_001A8F20,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(creature+0x32);*(u8 **)(vars+0x2F0+child_index*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=spawned_vars+0x50;
        for(byte_index=0;byte_index<10;byte_index++)parameters[byte_index]=init_bytes.bytes[byte_index];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[8]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 1:parameters[5]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[9]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 2:parameters[7]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        }
        part_spawn_damage_debris(*(u8 **)(vars+0x2F8),spawned_vars+0x50,spawned_vars+0x20);{ u8 *partner=*(u8 **)(vars+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(vars[0x302] && !(vars[0x302]&2))vars[0x302]=1;
    enemy_select_path(creature,*(int *)(vars+0x2B4),-1);shared_counter_release(creature);**(int **)(vars+0x304)=0;
    if(*(int *)(vars+0x2B0)!=-1) {
        *(int *)(vars+0x2DC)=*(int *)(vars+0x2B0);*(int *)(vars+0x138)|=4;moby_set_state(creature,1,1);
        guard_switch_animation(creature,13,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    } else {
        int state;moby_set_state(creature,5,1);state=func_001163B0()&1;
        guard_switch_animation(creature,state,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    }
}
