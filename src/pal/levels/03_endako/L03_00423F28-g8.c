#include "names.h"
/* func_PAL_L03_00423F28, the PAL copy of func_L03_0041EAE0: the same C, where 0.00027777778f
   becomes 0.00040000002f; 0.016666668f becomes 0.020000001f; func_002B0ED8 becomes
   func_PAL_002B1A50; func_0032C700 becomes func_PAL_L00_003FB330; 0.06666667f becomes
   0.080000006f; func_002B0A68 becomes func_PAL_002B15D8; func_002B0A18 becomes func_PAL_002B1588;
   func_002A6C58 becomes func_PAL_002A7650. */
#include "common.h"

extern void snd_stop_voice(int);
extern void moby_set_state(void *,int,int);
extern void anim_start_immediate(void *,int,int);
extern int FloatToInt(float);
extern void *part_find_owned_effect_slot(void *,u32,int);
extern int moby_apply_damage_to_object_pal(void *,void *,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_masked_debris_pal(void *,int,void *,float,float,float,float,u8);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_pal(int,int);
extern int PlayMobySound(int,int,void *);
extern void SetDeathBits_pal(void *,int,int);
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern u8 *g_path_l03_entry_table[] NOT_SDA;
extern float g_robot_speed_scale __attribute__((sda));
extern float g_robot_turn_scale __attribute__((sda));
extern float g_laser_bot_damage_scale __attribute__((sda));
extern float g_laser_bot_beam_point[4] SDATA(D_L03_001B1C30) __attribute__((sda));
extern int g_game_mode NOT_SDA;
extern int g_bot_hit_count[] NOT_SDA __attribute__((sda));
extern int D_L03_001A9044_gp SDATA(D_L03_001A9044) __attribute__((sda));
extern int g_bot_hit_flag[] __attribute__((sda));
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern float g_camera_pose_buffer[] NOT_SDA;
typedef struct {
    u8 pad0[0x20];
    float f20;
    s16 f24;
    u8 pad26[0xA];
    float f30;
    u8 pad34[0x14];
    u8 f48;
    u8 pad49[0x1];
    u8 f4A;
    u8 pad4B[0x15];
    u8 f60[0x10];
    u8 f70;
    u8 pad71[0x1F];
    float f90;
    float f94;
    u8 pad98[0x4];
    float f9C;
    float fA0;
    u8 padA4[0x4];
    int fA8;
    u8 padAC[0x34];
    float fE0[4];
    u8 padF0[0x20];
    float f110;
    float f114;
    float f118;
    float f11C;
    float f120;
    u8 pad124[0xC];
    float f130;
    float f134;
    float f138;
    u8 pad13C[0x4];
    float f140;
    float f144;
    int f148;
    u8 pad14C[0x134];
    int f280;
    u8 pad284[0x4];
    int f288;
    int f28C;
    int f290;
    u8 pad294[0x98];
    s16 f32C;
    u8 pad32E[0x2];
    float f330;
    u8 pad334[0x8];
    float f33C;
    int f340;
} StateEAE0;
/* Laser bot init and death: sets it up on its first frame, then explodes it when hit (sparks, hit counter) (PAL). */
void laser_bot_init_check_hit_pal(u8 *moby) {
    StateEAE0 *state=*(StateEAE0 **)(moby+0x68);
    float point[4],velocity[4];
    void *hit;
    int path_index;
    float speed_rate,turn_rate;
    if(moby[0x20]==0) {
        if(state->f340!=-1) {
            snd_stop_voice(state->f340);
            state->f340=-1;
        }
        *(s16 *)(*(u8 **)(moby+0x24)+0x46)=5;
        if(state->f288) {
            moby_set_state(moby,4,1);
            anim_start_immediate(moby,0,0);
            state->f20=3;
            state->f24=3;
            state->f33C=4.5f;
        } else {
            path_index=state->f280;
            if(path_index==-1) {
                if(state->f340!=-1) {
                    snd_stop_voice(state->f340);
                    state->f340=-1;
                }
                moby_mark_spawned(moby);
                return;
            }
            qcopy(moby+0x10,g_path_l03_entry_table[path_index]+16);
            state->f148|=0x210;
            state->f32C=1;
            if(state->f28C) {
                moby_set_state(moby,9,4);
                anim_start_immediate(moby,0,0);
                state->f33C=0;
                *(int *)(moby+0x98)=0;
                *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;
            } else {
                moby_set_state(moby,3,0);
                anim_start_immediate(moby,0,0);
                state->f33C=6;
            }
        }
        state->f48=FloatToInt(20);
        state->f4A=FloatToInt(17.6f);
        state->f70=8;
        state->fA8=3;
        state->f90=0.5f;
        state->f94=0.5f;
        state->f9C=0.4f;
        state->fA0=*(float *)(moby+0x18)-1;
        speed_rate=g_robot_speed_scale*0.00040000002f;
        turn_rate=g_robot_turn_scale*0.020000001f;
        state->f30=0.75f;
        state->f144=0.05f;
        state->f114=0.25f;
        state->f118=0.4f;
        state->f134=speed_rate;
        state->f110=0.5f;
        state->f11C=0.4f;
        state->f120=0.78539824f;
        state->f140=0.52359885f;
        state->f330=1;
        state->f130=speed_rate;
        state->f138=turn_rate;
        *(float *)(moby+0x2C)=*(float *)(*(u8 **)(moby+0x24)+0x24)*g_laser_bot_damage_scale;
        state->f290=0;
    }
    hit=part_find_owned_effect_slot(moby,0x10000,0);
    if(hit && *(u8 **)((u8 *)hit+0x20)) {
        u8 *other=*(u8 **)((u8 *)hit+0x20);
        if(*(s16 *)(other+0xAA)==MOBY_CLASS_MEGACORP_LASER_BOT && *(float *)(other+0x18)<*(float *)(moby+0x18)+2) moby[0xA8]=0xFF;
    }
    if(moby_apply_damage_to_object_pal(moby,state->f60,0) && state->f20<=0) {
        matrix_mul_vec3(point,g_laser_bot_beam_point,moby+0xC0);
        FastVecAdd(point,point,moby+0x10);
        SpawnExplosion_pal(point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
        vec_scale_to_length(velocity,state->fE0,0.080000006f);
        part_spawn_masked_debris_pal(moby,31,velocity,3,6,3,6,255);
        if(g_game_mode==49) {
            D_L03_001A9044_gp=g_bot_hit_count[0]+1;
            if(D_L03_001A9044_gp>=10 && !g_item_enabled_flags[0x1C]) {
                g_item_enabled_flags[0x1C]=1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index_pal(0x1233,-1);
                g_bot_hit_flag[0]=1;
            }
        }
        PlayMobySound(3,0,moby);
        SetDeathBits_pal(moby,0,3);
        if(state->f340!=-1) {
            snd_stop_voice(state->f340);
            state->f340=-1;
        }
        moby_mark_spawned(moby);
        return;
    }
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_camera_pose_buffer)<24) {
        moby_update_ground_check(moby);
        moby[0x6F]=22;
    }
}
