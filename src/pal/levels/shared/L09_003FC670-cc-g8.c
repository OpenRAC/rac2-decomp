#include "names.h"
/* func_PAL_L09_003FC670, the PAL copy of func_L09_003F7CE0: the same C, where rename func_L02_0032B468 becomes func_PAL_L02_0032D5F8; rename func_002B3380 becomes func_PAL_002B3F18; rename func_L09_003F7518 becomes func_PAL_L09_003FBDF0. */
#include "common.h"
typedef struct { float data[12]; } InitBlock;
extern u8 g_default_particle_vec[] MACRO_ADDR;
extern void *g_path_l09_table[];
extern u8 g_trooper_param_defaults[] SDATA(D_L09_001B10D0);
extern float g_trooper_legs_scale __attribute__((sda));
extern float g_trooper_limit_turn_a __attribute__((sda)),g_trooper_limit_turn_b __attribute__((sda)),g_trooper_limit_turn_c __attribute__((sda)),g_trooper_limit_turn_d __attribute__((sda)),g_trooper_legs_acceleration __attribute__((sda)),g_trooper_default_param __attribute__((sda));
extern int FloatToInt(float),func_001163B0(void),math_random_int_range(int,int);
extern u8 *CreateMoby(int),*func_PAL_L02_0032D5F8(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(void *);
extern int part_spawn_damage_debris_pal(void *,void *,void *),enemy_select_path(void *,int,int);
extern void moby_transform_joint_point(void *,int,void *), copy_matrix3x4(void *,void *), func_002A0F48(void *), mat_normalize_columns(void *), func_002A10E8(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void FastVecSub(void *,void *,void *),shared_counter_release(void *),moby_set_state(void *,int,int),enemy_set_animation_state_pal(void *,int,int,int);
extern float coll_probe_ground_height_below(void *,int,float);
void func_PAL_L09_003FC670(u8 *o) {
    u8 *d=*(u8 **)(o+0x68), *p,*pd; float transform[16]; float pos[4]; int i,j; u8 *parameters; u8 stage; float acceleration; int animation=9; float slow=0.006f;
    *(float *)(o+0x2C)*=g_trooper_legs_scale;
    d[0x60]=14;
    *(int *)(d+0x98)=animation;
    d[0x61]=18;
    d[0x62]=17;
    d[0x66]=20;
    d[0x67]=255;
    *(float *)(d+0x6C)=0.44000003f;
    *(float *)(d+0x70)=0.14000002f;
    *(float *)(d+0x74)=slow;
    *(float *)(d+0x78)=0.012f;
    *(float *)(d+0x7C)=slow;
    *(float *)(d+0x8C)=0.4f;
    d[0xBC]=5;
    d[0xBD]=animation;
    stage=4;
    d[0xBF]=7;
    d[0xC2]=10;
    d[0xC3]=17;
    *(float *)(d+0x90)=*(float *)(d+0x310);
    *(float *)(d+0xF8)=0.45f;
    *(u8 **)(d+0x2F8)=0;
    *(u8 **)(d+0x2F0)=0;
    *(u8 **)(d+0x2F4)=0;
    *(float *)(d+0x80)=0.7f;
    *(float *)(d+0x84)=0.7f;
    d[0xBE]=stage;
    d[0x28]=3;
    *(float *)(d+0x30)=1.7f;
    d[0x2F]=8;
    d[0x2A]=2;
    d[0x4D]=0;
    d[0x2E]=1;
    d[0x48]=FloatToInt(25.0f);d[0x4A]=FloatToInt(16.0f);
    { float first,second,third,fourth;
    acceleration=g_trooper_legs_acceleration*0.00040000002f;
    d[0x1E8]=12;d[0x1E9]=11;
    first=g_trooper_limit_turn_a*0.00040000002f;second=g_trooper_limit_turn_b*0.020000001f;third=g_trooper_limit_turn_c*6.981318e-06f;
    fourth=g_trooper_limit_turn_d*0.0003490659f;
    *(float *)(d+0x100)=0.7f;*(float *)(d+0x104)=0.5f;*(float *)(d+0x108)=0.5f;*(float *)(d+0x10C)=1.0f;
    *(float *)(d+0x110)=0.7853982448577881f;*(float *)(d+0x130)=0.349065899848938f;
    *(float *)(d+0x12C)=acceleration;
    moby_set_controller_speed_limits(o,first,second,third,fourth); }
    *(int *)(d+0x138)|=0x80;*(int *)(d+0x1DC)=0;*(float *)(d+0x1D4)=3.0f;
    *(u16 *)(d+0x1E4)=0;*(u16 *)(d+0x1E2)=0;*(int *)(d+0x1D0)=0;
    if(*(int *)(d+0x2BC)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(d+0x2BC)]);
    if(*(int *)(d+0x2B4)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(d+0x2B4)]);
    if(*(int *)(d+0x2B8)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(d+0x2B8)]);
    p=CreateMoby(0xD0E);
    if(p) {
        *(u8 **)(d+0x2F8)=p;*(u16 *)(p+0x32)=*(u16 *)(o+0x32);p[0x30]=o[0x30];
        *(u64 *)(p+0x38)=*(u64 *)(o+0x38);*(int *)(p+0x78)=*(int *)(o+0x78);p[0x31]=1;
        *(float *)(p+0x2C)*=g_trooper_legs_scale;
        moby_transform_joint_to_world(o,0,p+0x10);qcopy(p+0xF0,o+0xF0);
        pd=*(u8 **)(p+0x68);*(InitBlock *)(pd+0x20)=*(InitBlock *)(d+0x20);
        *(float *)(pd+0x20)=*(float *)(d+0x20);*(u16 *)(pd+0x24)=*(u16 *)(d+0x24);pd[0x28]=d[0x28];
        pd[0x2F]=stage;*(float *)(pd+0x30)=0.7f;pd[0x2A]=2;pd[0x4D]=1;pd[0x4A]=3;pd[0x2E]=1;*(u8 **)(pd+0x70)=o;
        moby_transform_joint_point(o,0,transform);copy_matrix3x4(p+0xC0,transform);
        func_002A0F48(p);mat_normalize_columns(p+0xC0);func_002A10E8(p);
        for(i=0;i<2;i++) {
            u8 *child;
            moby_transform_joint_to_world(*(u8 **)(d+0x2F8),i,pos);FastVecSub(pos,pos,*(u8 **)(d+0x2F8)+0x10);
            child=func_PAL_L02_0032D5F8(*(u8 **)(d+0x2F8),0xD66,pos,g_default_particle_vec,0,0,g_default_particle_vec,g_default_particle_vec,g_default_particle_vec,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(o+0x32);*(u8 **)(d+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=pd+0x50;
        for(j=0;j<10;j++)parameters[j]=g_trooper_param_defaults[j];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=FloatToInt((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[8]=FloatToInt((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 1:parameters[5]=FloatToInt((2.0f/ *(s16 *)(d+0x24))*255.0f);parameters[9]=FloatToInt((1.0f/ *(s16 *)(d+0x24))*255.0f);break;
        case 2:parameters[7]=FloatToInt((2.0f/ *(s16 *)(d+0x24))*255.0f);break;
        }
        part_spawn_damage_debris_pal(*(u8 **)(d+0x2F8),pd+0x50,pd+0x20);{ u8 *partner=*(u8 **)(d+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(d[0x302]&1) {
        d[0x302]=(d[0x302]|1)&0xFD;
        if(d[0x31F]) {
            u8 *partner; u8 **slots; int k;
            o[0x31]=0;*(int *)(o+0x98)=0;*(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|1)&0xEFFF;
            partner=*(u8 **)(d+0x2F8);
            if(partner && *(s16 *)(partner+0xAA)==0xD0E && partner[0x20]!=254 && partner[0x20]!=253) {
                *(u16 *)(partner+0x34)|=1;(*(u8 **)(d+0x2F8))[0x31]=0;*(int *)(*(u8 **)(d+0x2F8)+0x98)=0;*(u16 *)(*(u8 **)(d+0x2F8)+0x34)&=0xEFFF;
            }
            slots=(u8 **)(d+0x2F0);
            for(k=0;k<2;k++) {
                u8 *child=slots[k];
                if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                    *(u16 *)(child+0x34)|=1;slots[k][0x31]=0;
                }
            }
            d[0x31C]=0;d[0x31D]=1;*(u16 *)(o+0x34)|=2;
        }
    }
    if(*(float *)(d+0x4BC)<10.0f)*(float *)(d+0x4BC)=g_trooper_default_param;
    enemy_select_path(o,*(int *)(d+0x2B4),-1);shared_counter_release(o);**(int **)(d+0x304)=0;
    if(*(int *)(d+0x2B0)!=-1) {
        *(int *)(d+0x2DC)=*(int *)(d+0x2B0);*(int *)(d+0x138)|=4;moby_set_state(o,1,1);
        if(coll_probe_ground_height_below(o+0x10,0,0.5f)<*(float *)(o+0x18)-*(float *)(d+0x10C)-0.1f)
            enemy_set_animation_state_pal(o,2,0,math_random_int_range(5,10));
        else
            enemy_set_animation_state_pal(o,13,0,math_random_int_range(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    } else {
        int state;moby_set_state(o,5,1);state=func_001163B0()&1;
        enemy_set_animation_state_pal(o,state,0,math_random_int_range(10,20));
        *(int *)(d+0x2D8)=*(int *)(d+0x2D0);
    }
}
