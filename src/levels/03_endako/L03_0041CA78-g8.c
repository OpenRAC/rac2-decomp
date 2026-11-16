#include "names.h"
/* func_L03_0041CA78 is a unit of its own: it reads level data through $gp (-G8) and its
   0x00000000FFFFFFFF sentinel needs the SN constant seed (addiu -1; dsrl32 0) selected by
   -Wa,--r5900-unsigned32-mask=sn (config/cflags.txt). The initialization stores are written
   in the order sched1 needs: stores whose value is reused later in the block come first. */
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
extern void anim_start_blended(void *,int,int,int);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void FastVecAdd(void *,void *,void *);
extern void part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,u8);
extern int snd_play_from_global_bank(int,unsigned int,void *);
extern void value_set_entry_by_index(int,int);
extern void sweeper_bot_mark_stream(void *);
extern void SetDeathBits(void *,int,int);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int weapon_select_aim_target(void *,int,void *,int,float,float);

/* Sets up the sweeper bot on its first frame and handles its death when it is hit. */
void sweeper_bot_update_core(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    float scale;
    Vec a,b;
    if(moby[0x20]==0) {
        if(*(int *)(vars+0x29c)) {
            scale=g_sweeper_bot_speed_fast;
            *(float *)(vars+0x20)=1;
            *(short *)(vars+0x24)=1;
        } else scale=g_sweeper_bot_speed_slow;
        *(float *)(moby+0x2c)=*(float *)(*(u8 **)(moby+0x24)+0x24)*scale;
        vars[0x48]=FloatToInt(20);
        vars[0x4a]=FloatToInt(6);
        if(*(int *)(vars+0x290)==-1) {
            moby_mark_spawned(moby);
            return;
        }
        { s32 initialMode = 3;
        *(int *)(vars+0x2ac)=0; *(int *)(vars+0x188)=initialMode;
        *(float *)(vars+0x174)=*(float *)(vars+0x170)=0.5f;
        *(float *)(vars+0x17c)=0.4f; *(float *)(vars+0x64)=0.20943955f; *(float *)(vars+0x58)=0.4f;
        vars[0x150]=7; vars[0x28]=initialMode;
        *(float *)(vars+0x68)=0.20943955f;
        *(float *)(vars+0x84)=scale*0.05f;
        *(float *)(vars+0x54)=scale*0.25f;
        *(float *)(vars+0x50)=scale*0.5f;
        *(float *)(vars+0x5c)=0.4f;
        *(float *)(vars+0x60)=0.78539824f;
        *(float *)(vars+0x80)=0.52359885f;
        *(int *)(vars+0x8c)=*(int *)(vars+0x290);
        qcopy(vars+0x2b0,moby+0x10); }
        if(*(u64 *)(vars+0x2a0)!=0xffffffffULL) {
            moby_set_state(moby,8,4);
            *(int *)(moby+0x98)=0;
            *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xefff;
        } else {
            moby_set_state(moby,1,0);
            if(moby[0x43]) anim_start_blended(moby,0,0,0);
        }
        {
            float v0 = scale*0.00027777778f;
            float v1 = scale*0.016666668f;
            float v2 = g_sweeper_bot_rate_a*v0;
            float v3 = g_sweeper_bot_rate_b*v1;
            float v4 = g_sweeper_bot_slow_rate*0.000004848137343f;
            float v5 = g_sweeper_bot_fast_rate*0.00029088825f;
            *(float *)(vars+0x70)=v2;
            *(float *)(vars+0x74)=v2;
            *(float *)(vars+0x78)=v3;
            *(float *)(vars+0x64)=v4;
            *(float *)(vars+0x6c)=v5;
            *(float *)(vars+0x68)=v4;
        }
    }
    if(moby_apply_damage_to_object(moby,vars+0x140,0) && *(float *)(vars+0x20)<=0) {
        matrix_mul_vec3(&a,g_sweeper_bot_local_offset,moby+0xc0);
        FastVecAdd(&a,&a,moby+0x10);
        PlayMobySound(2,0,moby);
        part_spawn_explosion_with_sparks(moby,&a,-1,0.333f,0);
        FastVecSub(&b,moby+0x10,g_hero_position);
        b.f[2]=0;
        vec_scale_to_length(&b,&b,0.10000001f);
        part_spawn_masked_debris(moby,31,g_effect_descriptor_default,3,6,3,6,255);
        if(*(int *)(g_hero_position+0x2214)==49) {
            g_bot_hit_count++;
            if(g_bot_hit_count>=10 && !g_item_enabled_flags[0x1C]) {
                g_item_enabled_flags[0x1C]=1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index(0x1233,-1);
                g_bot_hit_flag=1;
            }
        }
        PlayMobySound(2,0,moby);
        sweeper_bot_mark_stream(moby);
        SetDeathBits(moby,0,3);
        moby_mark_spawned(moby);
        return;
    }
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_camera_pose_buffer)<24) {
        moby_update_ground_check(moby);
        moby[0x6f]=22;
    }
    if(moby[0x95]<3) weapon_select_aim_target(moby,*(int *)(vars+0x294),0,0,16,0);
}
