#include "names.h"
/* func_PAL_L12_004184A0, the PAL copy of func_L12_004135A8: the same C, where rename func_L02_0032B468 becomes func_PAL_L02_0032D5F8; rename func_002B3380 becomes func_PAL_002B3F18; rename func_L12_00412E50 becomes func_PAL_L12_00417C90. */
#include "common.h"
typedef struct { u8 bytes[16]; } InitBytes;
typedef struct { float data[12]; } InitBlock;
extern InitBytes g_guard_init_bytes;
extern u8 g_zero_l12_vec[] MACRO_ADDR;
extern void *g_path_zone_table[];
extern float g_guard_child_scale __attribute__((sda));
extern float g_guard_anim_rate_a __attribute__((sda)),g_guard_anim_rate_b __attribute__((sda)),g_guard_anim_rate_c __attribute__((sda)),g_guard_anim_rate_d __attribute__((sda)),g_guard_acceleration __attribute__((sda));
extern int FloatToInt(float),func_001163B0(void),math_random_int_range(int,int);
extern u8 *CreateMoby(int),*part_spawn_flying_fragment_pal(void *,int,void *,void *,int,int,void *,void *,void *,float);
extern void moby_set_controller_speed_limits(u8 *,float,float,float,float);
extern float path_l01_compute_segment_lengths(u8 *);
extern int part_spawn_damage_debris_pal(void *,void *,void *),enemy_select_path(void *,int,int);
extern void FastVecSub(void *,void *,void *), shared_counter_release(void *), moby_set_state(void *,int,int), guard_switch_animation_pal(void *,int,int,int);
extern void moby_transform_joint_to_world(void *,int,void *);
/* Sets up a guard: fills its movement and animation tuning, creates its flame partner object and the two hand children, picks its path and puts it in its first state (PAL: 50 Hz rates). */
void guard_init_state_with_partner_pal(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *flame,*flame_vars; InitBytes bytes=g_guard_init_bytes; float pos[4]; int i,j; u8 *parameters; float acceleration; int animation=9; float slow=0.006f;
    *(float *)(moby+0x2C)*=g_guard_child_scale;
    vars[0x60]=14;
    *(int *)(vars+0x98)=animation;
    vars[0x61]=18;
    vars[0x62]=17;
    vars[0x66]=20;
    vars[0x67]=255;
    *(float *)(vars+0x6C)=0.44000003f;
    *(float *)(vars+0x70)=0.14000002f;
    *(float *)(vars+0x74)=slow;
    *(float *)(vars+0x78)=0.012f;
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
    { float first,second,third,fourth;
    acceleration=g_guard_acceleration*0.00040000002f;
    vars[0x1E8]=12;vars[0x1E9]=11;
    second=g_guard_anim_rate_b*0.020000001f;third=g_guard_anim_rate_c*6.981318e-06f;
    fourth=g_guard_anim_rate_d*0.0003490659f;first=g_guard_anim_rate_a*0.00040000002f;
    *(float *)(vars+0x100)=0.7f;*(float *)(vars+0x104)=0.5f;*(float *)(vars+0x108)=0.5f;*(float *)(vars+0x10C)=0.5f;
    *(float *)(vars+0x110)=0.7853982448577881f;*(float *)(vars+0x130)=0.349065899848938f;
    *(float *)(vars+0x12C)=acceleration;
    moby_set_controller_speed_limits(moby,first,second,third,fourth); }
    *(int *)(vars+0x138)|=0x80;*(int *)(vars+0x1DC)=0;*(float *)(vars+0x1D4)=3.0f;
    *(u16 *)(vars+0x1E4)=0;*(u16 *)(vars+0x1E2)=0;*(int *)(vars+0x1D0)=0;
    if(*(int *)(vars+0x2BC)!=-1)path_l01_compute_segment_lengths(g_path_zone_table[*(int *)(vars+0x2BC)]);
    if(*(int *)(vars+0x2B4)!=-1)path_l01_compute_segment_lengths(g_path_zone_table[*(int *)(vars+0x2B4)]);
    if(*(int *)(vars+0x2B8)!=-1)path_l01_compute_segment_lengths(g_path_zone_table[*(int *)(vars+0x2B8)]);
    flame=CreateMoby(0x114B);
    if(flame) {
        *(u8 **)(vars+0x2F8)=flame;*(u16 *)(flame+0x32)=*(u16 *)(moby+0x32);flame[0x30]=moby[0x30];
        *(u64 *)(flame+0x38)=*(u64 *)(moby+0x38);*(int *)(flame+0x78)=*(int *)(moby+0x78);flame[0x31]=1;
        *(float *)(flame+0x2C)*=g_guard_child_scale;
        moby_transform_joint_to_world(moby,0,flame+0x10);qcopy(flame+0xF0,moby+0xF0);
        flame_vars=*(u8 **)(flame+0x68);*(InitBlock *)(flame_vars+0x20)=*(InitBlock *)(vars+0x20);
        *(float *)(flame_vars+0x20)=*(float *)(vars+0x20);*(u16 *)(flame_vars+0x24)=*(u16 *)(vars+0x24);flame_vars[0x28]=vars[0x28];
        *(float *)(flame_vars+0x30)=0.7f;flame_vars[0x2F]=4;flame_vars[0x2A]=2;flame_vars[0x4A]=3;flame_vars[0x4D]=1;*(u8 **)(flame_vars+0x70)=moby;
        for(i=0;i<2;i++) {
            u8 *child;
            moby_transform_joint_to_world(*(u8 **)(vars+0x2F8),i,pos);FastVecSub(pos,pos,*(u8 **)(vars+0x2F8)+0x10);
            child=part_spawn_flying_fragment_pal(*(u8 **)(vars+0x2F8),0xD66,pos,g_zero_l12_vec,0,0,g_zero_l12_vec,g_zero_l12_vec,g_zero_l12_vec,0);
            if(child && *(s16 *)(child+0xAA)==0xD66 && child[0x20]!=254 && child[0x20]!=253) {
                *(u16 *)(child+0x32)=*(u16 *)(moby+0x32);*(u8 **)(vars+0x2F0+i*4)=child;*(u16 *)(child+0x34)|=2;
            }
        }
        parameters=flame_vars+0x50;
        for(j=0;j<10;j++)parameters[j]=bytes.bytes[j];
        switch(func_001163B0()%3) {
        case 0:parameters[4]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[8]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 1:parameters[5]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);parameters[9]=FloatToInt((1.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        case 2:parameters[7]=FloatToInt((2.0f/ *(s16 *)(vars+0x24))*255.0f);break;
        }
        part_spawn_damage_debris_pal(*(u8 **)(vars+0x2F8),flame_vars+0x50,flame_vars+0x20);{ u8 *partner=*(u8 **)(vars+0x2F8);*(u16 *)(partner+0x7C)&=0xFCFF; }
    }
    if(vars[0x302] && !(vars[0x302]&2))vars[0x302]=1;
    enemy_select_path(moby,*(int *)(vars+0x2B4),-1);shared_counter_release(moby);**(int **)(vars+0x304)=0;
    if(*(int *)(vars+0x2B0)!=-1) {
        *(int *)(vars+0x2DC)=*(int *)(vars+0x2B0);*(int *)(vars+0x138)|=4;moby_set_state(moby,1,1);
        guard_switch_animation_pal(moby,13,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    } else {
        int state;moby_set_state(moby,5,1);state=func_001163B0()&1;
        guard_switch_animation_pal(moby,state,0,math_random_int_range(10,20));
        *(int *)(vars+0x2D8)=*(int *)(vars+0x2D0);
    }
}
