#include "common.h"
typedef struct { float data[12]; } InitBlock;
extern u8 g_default_particle_vec[] MACRO_ADDR;
extern void *g_path_l09_table[];
extern u8 g_trooper_param_defaults[] SDATA(D_L09_001B10D0);
extern float g_trooper_legs_scale __attribute__((sda));
extern float g_trooper_limit_turn_a __attribute__((sda)),g_trooper_limit_turn_b __attribute__((sda)),g_trooper_limit_turn_c __attribute__((sda)),g_trooper_limit_turn_d __attribute__((sda)),g_trooper_legs_acceleration __attribute__((sda)),g_trooper_default_param __attribute__((sda));
extern int FloatToInt(float),func_001163B0(void),math_random_int_range(int,int);
extern u8 *CreateMoby(int),*part_spawn_flying_fragment(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(void *);
extern int part_spawn_damage_debris(void *,void *,void *),enemy_select_path(void *,int,int);
extern void moby_transform_joint_point(void *,int,void *), copy_matrix3x4(void *,void *), func_002A0F48(void *), mat_normalize_columns(void *), func_002A10E8(void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern void FastVecSub(void *,void *,void *),shared_counter_release(void *),moby_set_state(void *,int,int),enemy_set_animation_state(void *,int,int,int);
extern float coll_probe_ground_height_below(void *,int,float);
/* Sets up a new trooper: fills in its tuning values, creates its torso and two arm parts, and picks its first animation. */
void trooper_legs_init(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *torso,*torso_vars; float transform[16]; float pos[4]; int i,j; u8 *parameters; u8 stage; float acceleration; int animation=9; float slow=0.004166666883975267f;
    *(float *)(moby+0x2C)*=g_trooper_legs_scale;
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
    stage=4;
    vars[0xBF]=7;
    vars[0xC2]=10;
    vars[0xC3]=17;
    *(float *)(vars+0x90)=*(float *)(vars+0x310);
    *(float *)(vars+0xF8)=0.45f;
    *(u8 **)(vars+0x2F8)=0;
    *(u8 **)(vars+0x2F0)=0;
    *(u8 **)(vars+0x2F4)=0;
    *(float *)(vars+0x80)=0.7f;
    *(float *)(vars+0x84)=0.7f;
    vars[0xBE]=stage;
    vars[0x28]=3;
    *(float *)(vars+0x30)=1.7f;
    vars[0x2F]=8;
    vars[0x2A]=2;
    vars[0x4D]=0;
    vars[0x2E]=1;
    vars[0x48]=FloatToInt(25.0f);vars[0x4A]=FloatToInt(16.0f);
    { float first,second,third,fourth;
    acceleration=g_trooper_legs_acceleration*0.00027777778450399637f;
    vars[0x1E8]=12;vars[0x1E9]=11;
    first=g_trooper_limit_turn_a*0.00027777778450399637f;second=g_trooper_limit_turn_b*0.01666666753590107f;third=g_trooper_limit_turn_c*0.000004848137454391923f;
    fourth=g_trooper_limit_turn_d*0.0002908882452175021f;
    *(float *)(vars+0x100)=0.7f;*(float *)(vars+0x104)=0.5f;*(float *)(vars+0x108)=0.5f;*(float *)(vars+0x10C)=1.0f;
    *(float *)(vars+0x110)=0.7853982448577881f;*(float *)(vars+0x130)=0.349065899848938f;
    *(float *)(vars+0x12C)=acceleration;
    moby_set_controller_speed_limits(moby,first,second,third,fourth); }
    *(int *)(vars+0x138)|=0x80;*(int *)(vars+0x1DC)=0;*(float *)(vars+0x1D4)=3.0f;
    *(u16 *)(vars+0x1E4)=0;*(u16 *)(vars+0x1E2)=0;*(int *)(vars+0x1D0)=0;
    if(*(int *)(vars+0x2BC)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(vars+0x2BC)]);
    if(*(int *)(vars+0x2B4)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(vars+0x2B4)]);
    if(*(int *)(vars+0x2B8)!=-1)path_l01_compute_segment_lengths(g_path_l09_table[*(int *)(vars+0x2B8)]);
    torso=CreateMoby(MOBY_CLASS_MEGACORP_TROOPER_TORSO);
    if(torso) {
        *(u8 **)(vars+0x2F8)=torso;*(u16 *)(torso+0x32)=*(u16 *)(moby+0x32);torso[0x30]=moby[0x30];
        *(u64 *)(torso+0x38)=*(u64 *)(moby+0x38);*(int *)(torso+0x78)=*(int *)(moby+0x78);torso[0x31]=1;
        *(float *)(torso+0x2C)*=g_trooper_legs_scale;
        moby_transform_joint_to_world(moby,0,torso+0x10);qcopy(torso+0xF0,moby+0xF0);
        torso_vars=*(u8 **)(torso+0x68);*(InitBlock *)(torso_vars+0x20)=*(InitBlock *)(vars+0x20);
        *(float *)(torso_vars+0x20)=*(float *)(vars+0x20);*(u16 *)(torso_vars+0x24)=*(u16 *)(vars+0x24);torso_vars[0x28]=vars[0x28];
        torso_vars[0x2F]=stage;*(float *)(torso_vars+0x30)=0.7f;torso_vars[0x2A]=2;torso_vars[0x4D]=1;torso_vars[0x4A]=3;torso_vars[0x2E]=1;*(u8 **)(torso_vars+0x70)=moby;
        moby_transform_joint_point(moby,0,transform);copy_matrix3x4(torso+0xC0,transform);
        func_002A0F48(torso);mat_normalize_columns(torso+0xC0);func_002A10E8(torso);
        for(i=0;i<2;i++) {
            u8 *child;
            moby_transform_joint_to_world(*(u8 **)(vars+0x2F8),i,pos);FastVecSub(pos,pos,*(u8 **)(vars+0x2F8)+0x10);
            child=part_spawn_flying_fragment(*(u8 **)(vars+0x2F8),0xD66 /* moby class 3430 */,pos,g_default_particle_vec,0,0,g_default_particle_vec,g_default_particle_vec,g_default_particle_vec,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 /* moby class 3430 */ && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(moby+0x32);*(u8 **)(vars+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=torso_vars+0x50;
        for(j=0;j<10;j++)parameters[j]=g_trooper_param_defaults[j];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[8]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 1:parameters[5]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[9]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 2:parameters[7]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        }
        part_spawn_damage_debris(*(u8 **)(vars+0x2F8),torso_vars+0x50,torso_vars+0x20);{ u8 *partner=*(u8 **)(vars+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(vars[0x302]&1) {
        vars[0x302]=(vars[0x302]|1)&0xFD;
        if(vars[0x31F]) {
            u8 *partner; u8 **slots; int k;
            moby[0x31]=0;*(int *)(moby+0x98)=0;*(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|1)&0xEFFF;
            partner=*(u8 **)(vars+0x2F8);
            if(partner && *(s16 *)(partner+0xAA)==MOBY_CLASS_MEGACORP_TROOPER_TORSO && partner[0x20]!=254 && partner[0x20]!=253) {
                *(u16 *)(partner+0x34)|=1;(*(u8 **)(vars+0x2F8))[0x31]=0;*(int *)(*(u8 **)(vars+0x2F8)+0x98)=0;*(u16 *)(*(u8 **)(vars+0x2F8)+0x34)&=0xEFFF;
            }
            slots=(u8 **)(vars+0x2F0);
            for(k=0;k<2;k++) {
                u8 *child=slots[k];
                if(child && *(s16 *)(child+0xAA)==0xD66 /* moby class 3430 */ && child[0x20]!=254 && child[0x20]!=253) {
                    *(u16 *)(child+0x34)|=1;slots[k][0x31]=0;
                }
            }
            vars[0x31C]=0;vars[0x31D]=1;*(u16 *)(moby+0x34)|=2;
        }
    }
    if(*(float *)(vars+0x4BC)<10.0f)*(float *)(vars+0x4BC)=g_trooper_default_param;
    enemy_select_path(moby,*(int *)(vars+0x2B4),-1);shared_counter_release(moby);**(int **)(vars+0x304)=0;
    if(*(int *)(vars+0x2B0)!=-1) {
        *(int *)(vars+0x2DC)=*(int *)(vars+0x2B0);*(int *)(vars+0x138)|=4;moby_set_state(moby,1,1);
        if(coll_probe_ground_height_below(moby+0x10,0,0.5f)<*(float *)(moby+0x18)-*(float *)(vars+0x10C)-0.1f)
            enemy_set_animation_state(moby,2,0,math_random_int_range(5,10));
        else
            enemy_set_animation_state(moby,13,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    } else {
        int state;moby_set_state(moby,5,1);state=func_001163B0()&1;
        enemy_set_animation_state(moby,state,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    }
}
