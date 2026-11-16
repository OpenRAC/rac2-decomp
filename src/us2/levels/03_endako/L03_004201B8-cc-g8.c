#include "names.h"
/* func_US2_L03_004201B8, the USA v2.00 copy of func_L03_0041EAE0: the same C, where rename func_002B0A18 becomes func_US2_002B1880; rename func_002A6C58 becomes func_US2_002A7AA8. */
#include "common.h"

/* func_US2_L03_004201B8 reaches several level words through $gp, so it needs -G8.
 * Its state record is written through struct members: their MEMs are
 * in-struct, which lets the scheduler place the $gp scalar loads above the
 * record's stores as retail does. */
extern void snd_stop_voice(int);
extern void moby_set_state(void *,int,int);
extern void anim_start_immediate(void *,int,int);
extern int FloatToInt(float);
extern void *part_find_owned_effect_slot(void *,u32,int);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void *SpawnExplosion(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,u8);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_us2(int,int);
extern int PlayMobySound(int,int,void *);
extern void SetDeathBits_us2(void *,int,int);
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
/* Sets up the laser bot on its first frame and handles its death. */
void laser_bot_init_check_hit_us2(u8 *moby) {
    StateEAE0 *vars=*(StateEAE0 **)(moby+0x68);
    float point[4],velocity[4];
    void *hit;
    int path_index;
    float move_speed,turn_speed;
    if(moby[0x20]==0) {
        if(vars->f340!=-1) {
            snd_stop_voice(vars->f340);
            vars->f340=-1;
        }
        *(s16 *)(*(u8 **)(moby+0x24)+0x46)=5;
        if(vars->f288) {
            moby_set_state(moby,4,1);
            anim_start_immediate(moby,0,0);
            vars->f20=3;
            vars->f24=3;
            vars->f33C=4.5f;
        } else {
            path_index=vars->f280;
            if(path_index==-1) {
                if(vars->f340!=-1) {
                    snd_stop_voice(vars->f340);
                    vars->f340=-1;
                }
                moby_mark_spawned(moby);
                return;
            }
            qcopy(moby+0x10,g_path_l03_entry_table[path_index]+16);
            vars->f148|=0x210;
            vars->f32C=1;
            if(vars->f28C) {
                moby_set_state(moby,9,4);
                anim_start_immediate(moby,0,0);
                vars->f33C=0;
                *(int *)(moby+0x98)=0;
                *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;
            } else {
                moby_set_state(moby,3,0);
                anim_start_immediate(moby,0,0);
                vars->f33C=6;
            }
        }
        vars->f48=FloatToInt(20);
        vars->f4A=FloatToInt(17.6f);
        vars->f70=8;
        vars->fA8=3;
        vars->f90=0.5f;
        vars->f94=0.5f;
        vars->f9C=0.4f;
        vars->fA0=*(float *)(moby+0x18)-1;
        move_speed=g_robot_speed_scale*0.00027777778f;
        turn_speed=g_robot_turn_scale*0.016666668f;
        vars->f30=0.75f;
        vars->f144=0.05f;
        vars->f114=0.25f;
        vars->f118=0.4f;
        vars->f134=move_speed;
        vars->f110=0.5f;
        vars->f11C=0.4f;
        vars->f120=0.78539824f;
        vars->f140=0.52359885f;
        vars->f330=1;
        vars->f130=move_speed;
        vars->f138=turn_speed;
        *(float *)(moby+0x2C)=*(float *)(*(u8 **)(moby+0x24)+0x24)*g_laser_bot_damage_scale;
        vars->f290=0;
    }
    hit=part_find_owned_effect_slot(moby,0x10000,0);
    if(hit && *(u8 **)((u8 *)hit+0x20)) {
        u8 *other=*(u8 **)((u8 *)hit+0x20);
        if(*(s16 *)(other+0xAA)==MOBY_CLASS_MEGACORP_LASER_BOT && *(float *)(other+0x18)<*(float *)(moby+0x18)+2) moby[0xA8]=0xFF;
    }
    if(moby_apply_damage_to_object(moby,vars->f60,0) && vars->f20<=0) {
        matrix_mul_vec3(point,g_laser_bot_beam_point,moby+0xC0);
        FastVecAdd(point,point,moby+0x10);
        SpawnExplosion(point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
        vec_scale_to_length(velocity,vars->fE0,0.06666667f);
        part_spawn_masked_debris(moby,31,velocity,3,6,3,6,255);
        if(g_game_mode==49) {
            D_L03_001A9044_gp=g_bot_hit_count[0]+1;
            if(D_L03_001A9044_gp>=10 && !g_item_enabled_flags[0x1C]) {
                g_item_enabled_flags[0x1C]=1;
                snd_play_from_global_bank(1,0,0);
                value_set_entry_by_index_us2(0x1233,-1);
                g_bot_hit_flag[0]=1;
            }
        }
        PlayMobySound(3,0,moby);
        SetDeathBits_us2(moby,0,3);
        if(vars->f340!=-1) {
            snd_stop_voice(vars->f340);
            vars->f340=-1;
        }
        moby_mark_spawned(moby);
        return;
    }
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_camera_pose_buffer)<24) {
        moby_update_ground_check(moby);
        moby[0x6F]=22;
    }
}
