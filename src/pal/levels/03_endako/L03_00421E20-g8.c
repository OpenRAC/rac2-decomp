#include "names.h"
/* func_PAL_L03_00421E20, the PAL copy of func_L03_0041CA78: the same C, where 0.20943955f becomes
   0.25132746f; func_002A7470 becomes func_PAL_002A7E68; 0.00027777778f becomes 0.00040000002f;
   0.016666668f becomes 0.020000001f; 0.000004848137343f becomes 6.981318e - 06f; 0.00029088825f
   becomes 0.0003490659f; func_002B0ED8 becomes func_PAL_002B1A50; func_002AC728 becomes
   func_PAL_002AD288; 0.10000001f becomes 0.120000005f; func_002B0A68 becomes func_PAL_002B15D8;
   func_002B0A18 becomes func_PAL_002B1588; func_002A6C58 becomes func_PAL_002A7650. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern void moby_set_state(void *,int,int);
extern int PlayMobySound(int,int,void *);
extern void moby_mark_spawned(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern float g_sweeper_bot_speed_fast __attribute__((sda));
extern float g_sweeper_bot_speed_slow __attribute__((sda));
extern float g_sweeper_bot_rate_a __attribute__((sda));
extern float g_sweeper_bot_rate_b __attribute__((sda));
extern float g_sweeper_bot_slow_rate __attribute__((sda));
extern float g_sweeper_bot_fast_rate __attribute__((sda));
extern float g_sweeper_bot_local_offset[4] SDATA(D_L03_001B1BB0) __attribute__((sda));
extern u8 g_hero_position[], g_camera_pose_buffer[];
extern u8 g_effect_descriptor_default[] MACRO_ADDR;
extern int g_bot_hit_count, g_bot_unused_word, g_bot_hit_flag;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern int FloatToInt(float);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_PAL_002B1A50(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void part_spawn_explosion_with_sparks_pal(void *,void *,int,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void func_PAL_002B15D8(void *,int,void *,float,float,float,float,u8);
extern int snd_play_from_global_bank(int,unsigned int,void *);
extern void value_set_entry_by_index_pal(int,int);
extern void sweeper_bot_mark_stream(void *);
extern void SetDeathBits_pal(void *,int,int);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int weapon_select_aim_target(void *,int,void *,int,float,float);

void func_PAL_L03_00421E20(u8 *e) {
    u8 *s=*(u8 **)(e+0x68);
    float scale;
    Vec a,b;
    if(e[0x20]==0) {
        if(*(int *)(s+0x29c)) {
            scale=g_sweeper_bot_speed_fast;
            *(float *)(s+0x20)=1;
            *(short *)(s+0x24)=1;
        } else scale=g_sweeper_bot_speed_slow;
        *(float *)(e+0x2c)=*(float *)(*(u8 **)(e+0x24)+0x24)*scale;
        s[0x48]=FloatToInt(20);
        s[0x4a]=FloatToInt(6);
        if(*(int *)(s+0x290)==-1) {
            moby_mark_spawned(e);
            return;
        }
        { s32 initialMode = 3;
        *(int *)(s+0x2ac)=0; *(int *)(s+0x188)=initialMode;
        *(float *)(s+0x174)=*(float *)(s+0x170)=0.5f;
        *(float *)(s+0x17c)=0.4f; *(float *)(s+0x64)=0.25132746f; *(float *)(s+0x58)=0.4f;
        s[0x150]=7; s[0x28]=initialMode;
        *(float *)(s+0x68)=0.25132746f;
        *(float *)(s+0x84)=scale*0.05f;
        *(float *)(s+0x54)=scale*0.25f;
        *(float *)(s+0x50)=scale*0.5f;
        *(float *)(s+0x5c)=0.4f;
        *(float *)(s+0x60)=0.78539824f;
        *(float *)(s+0x80)=0.52359885f;
        *(int *)(s+0x8c)=*(int *)(s+0x290);
        qcopy(s+0x2b0,e+0x10); }
        if(*(u64 *)(s+0x2a0)!=0xffffffffULL) {
            moby_set_state(e,8,4);
            *(int *)(e+0x98)=0;
            *(u16 *)(e+0x34)=(*(u16 *)(e+0x34)|0x41)&0xefff;
        } else {
            moby_set_state(e,1,0);
            if(e[0x43]) func_PAL_002A7E68(e,0,0,0);
        }
        {
            float v0 = scale*0.00040000002f;
            float v1 = scale*0.020000001f;
            float v2 = g_sweeper_bot_rate_a*v0;
            float v3 = g_sweeper_bot_rate_b*v1;
            float v4 = g_sweeper_bot_slow_rate*6.981318e-06f;
            float v5 = g_sweeper_bot_fast_rate*0.0003490659f;
            *(float *)(s+0x70)=v2;
            *(float *)(s+0x74)=v2;
            *(float *)(s+0x78)=v3;
            *(float *)(s+0x64)=v4;
            *(float *)(s+0x6c)=v5;
            *(float *)(s+0x68)=v4;
        }
    }
    if(func_PAL_002B1A50(e,s+0x140,0) && *(float *)(s+0x20)<=0) {
        matrix_mul_vec3(&a,g_sweeper_bot_local_offset,e+0xc0);
        FastVecAdd(&a,&a,e+0x10);
        PlayMobySound(2,0,e);
        part_spawn_explosion_with_sparks_pal(e,&a,-1,0.333f,0);
        FastVecSub(&b,e+0x10,g_hero_position);
        b.f[2]=0;
        vec_scale_to_length(&b,&b,0.120000005f);
        func_PAL_002B15D8(e,31,g_effect_descriptor_default,3,6,3,6,255);
        if(*(int *)(g_hero_position+0x2214)==49) {
            g_bot_hit_count++;
            if(g_bot_hit_count>=10 && !g_item_enabled_flags[0x1C]) {
                g_item_enabled_flags[0x1C]=1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index_pal(0x1233,-1);
                g_bot_hit_flag=1;
            }
        }
        PlayMobySound(2,0,e);
        sweeper_bot_mark_stream(e);
        SetDeathBits_pal(e,0,3);
        moby_mark_spawned(e);
        return;
    }
    if(e[0x31] && fast_vec_dist(e+0x10,g_camera_pose_buffer)<24) {
        moby_update_ground_check(e);
        e[0x6f]=22;
    }
    if(e[0x95]<3) weapon_select_aim_target(e,*(int *)(s+0x294),0,0,16,0);
}
