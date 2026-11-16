#include "include_asm.h"

#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern u8 g_item_slot_to_record[];
extern int g_item_ammo_counts[];
typedef struct {
    char pad_00[0x38]; s16 multiple_sound; s16 single_sound;
    char pad_3C[2]; s16 moby_class;
    char pad_40[0x4E]; u16 capacity;
    char pad_90[0x50];
} PickupResource;
extern PickupResource g_weapon_l00_table[];
typedef struct {
    char pad_00[0x20]; float axis[4];
    char pad_30[0x10]; float matrix[16];
    float position[4]; char pad_90[0x50]; float target[4];
    char pad_F0[0x60]; float motion[4];
    char pad_160[0x2162]; u8 override;
    char pad_22C3[0x1E1]; float range; float height;
    char pad_24AC[0x20]; int enabled;
} PickupPlayer;
extern char g_hero_state[];
#define PLAYER ((PickupPlayer *)D_00189E20)
extern int g_hero_locked_flag[] __attribute__((sda));
extern int g_frame_l00_counter[] __attribute__((sda));
extern int g_sound_last_frame[] MACRO_ADDR;
extern void *g_hero_moby NOT_SDA;
extern void vec_store_helper(void *);
extern s32 cam_moby_update_pal(void *);
extern float fast_vec_dist(void *,void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *,void *);
extern float gravity_get_center_distance(void *);
extern int weapon_add_ammo(int,int);
extern void part_reset_effects_pal(int,int,int);
extern void moby_set_state(void *,int,int);
extern void vec_clear_128(void *);
extern int subtract_integer_with_clamp(int);
extern int PlayMobySound(int,int,void *);
extern void FastVecSub(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern f32 ApproachValue(void *,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float FastVecLength(void *);
extern void moby_mark_spawned(void *);
extern void FastVecCross(void *,void *,void *);
extern void vec_set_direction_with_complement(void *,void *,float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern int vec_fast_helper_d(void *,void *);

/* Per-frame update of a dropped pickup (ammo and similar). It picks up its item when the player is close and not full, plays the pickup sound, and while collected flies toward the player before disappearing. */
void AmmoPickupUpdate_pal(char *moby)
{
    char *vars=*(char **)(moby+0x68);
    PickupResource *entry;
    int j,i,can_pickup,moved,old_count,delta,sound;
    float speed,time,target_speed;
    float to_player[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    float to_target[4] __attribute__((aligned(16)));
    float spin_axis[4] __attribute__((aligned(16)));
    float up_before[4] __attribute__((aligned(16)));
    float up_after[4] __attribute__((aligned(16)));
    float up_delta[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char matrix[48] __attribute__((aligned(16)));
    switch(B(moby,0x20)) {
    case 0:
        B(moby,0x20)=1;
        for(j=0;j<56;j++) {
            entry=&g_weapon_l00_table[g_item_slot_to_record[j]];
            if(entry->moby_class==S(moby,0xaa))I(vars,0x68)=j;
        }
        break;
    case 1:
        if(B(vars,0x5c)==3 && (g_frame_l00_counter[0]&15)==(((int)moby>>8)&15)) {
            qzero(vars);vec_store_helper(vars+0x10);B(vars,0x5c)=0;
        }
        qcopy(to_player,vars);
        cam_moby_update_pal(moby);
        moved=0;
        if(fast_vec_dist(to_player,vars)>F(vars,0x48)*2.0f)moved=1;
        can_pickup=1;
        if(B(vars,0x5c)||moved) {
            if(math_fast_float_d(vars+0x7c)) {
                if(math_fabs(F(moby,0x18)-PLAYER->position[2])>PLAYER->height)can_pickup=0;
                else if(vec_distance_xy(moby+0x10,PLAYER->position)>PLAYER->range)can_pickup=0;
            }
        } else {
            can_pickup=0;
            if(math_fabs(F(moby,0x18)-PLAYER->position[2])<PLAYER->height &&
               vec_distance_xy(moby+0x10,PLAYER->position)<PLAYER->range)I(vars,0x7c)=3;
        }
        if(g_item_ammo_counts[I(vars,0x68)] >=
           ((PickupResource *)(g_item_slot_to_record[I(vars,0x68)] * 224 + (unsigned int)g_weapon_l00_table))->capacity)can_pickup=0;
        if(g_hero_locked_flag[0]) {
            if(gravity_get_center_distance(moby+0x10)<F(vars,0x78)-2.0f)goto force_pickup;
        } else if(F(moby,0x18)<F(vars,0x78)-2.0f)goto force_pickup;
        if(!PLAYER->override)goto check_enabled;
force_pickup:
        can_pickup=1;
check_enabled:
        if(!PLAYER->enabled)can_pickup=0;
        if(can_pickup) {
            i=I(vars,0x68);old_count=g_item_ammo_counts[i];
            weapon_add_ammo(i,I(vars,0x60));
            if(old_count<g_item_ammo_counts[i]) {
                delta=g_item_ammo_counts[i]-old_count;
                if(delta==1) {
                    entry=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=entry->single_sound;
                } else {
                    entry=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=entry->multiple_sound;
                }
                part_reset_effects_pal(sound,delta,-1);
            }
            moby_set_state(moby,2,-1);
            F(vars,0x74)=0.16000001f;
            vec_clear_128(vars);
            if(subtract_integer_with_clamp(g_frame_l00_counter[0]-g_sound_last_frame[0])>8) {
                PlayMobySound(0,0,moby);g_sound_last_frame[0]=g_frame_l00_counter[0];
            }
        }
        break;
    case 2:
        FastVecSub(to_player,moby+0x10,PLAYER->position);
        matrix_mul_vec3(to_player,to_player,PLAYER->matrix);
        target_speed=8.0f;
        if(to_player[2]>0.0f)target_speed=0.0f;
        ApproachValue(vars+0x74,target_speed,0.0096f);
        vec_scale_to_length(drift,PLAYER->axis,F(vars,0x74));
        FastVecAdd(moby+0x10,moby+0x10,drift);
        FastVecAdd(moby+0x10,moby+0x10,PLAYER->motion);
        speed=FastVecLength(vars);
        ApproachValue(&speed,1.2800001f,0.0096f);
        FastVecSub(to_target,PLAYER->target,moby+0x10);
        time=FastVecLength(to_target)/speed;
        if(time<25.0f)ApproachValue(moby+0x2c,0.0f,F(*(char **)(moby+0x24),0x24)*0.04f);
        if(F(moby,0x2c)==0.0f) {moby_mark_spawned(moby);return;}
        if(time<=1.0f) {moby_mark_spawned(moby);return;}
        vec_scale_to_length(vars,to_target,speed);
        FastVecAdd(moby+0x10,moby+0x10,vars);
        FastVecCross(spin_axis,PLAYER->axis,vars);
        vec_set_direction_with_complement(spin_axis,spin_axis,0.10471977f);
        *(Quadword *)up=0;up[2]=0.3f;
        matrix_mul_vec3(up_before,up,moby+0xc0);
        quaternion_to_rotation_basis(spin_axis,matrix);
        multiply_matrix3x3(moby+0xc0,matrix,moby+0xc0);
        matrix_mul_vec3(up_after,up,moby+0xc0);
        FastVecSub(up_delta,up_after,up_before);
        FastVecSub(moby+0x10,moby+0x10,up_delta);
        break;
    }
    if(B(moby,0x20)==1 && vec_fast_helper_d(moby,g_hero_moby)) {
        B(moby,0x23)=B(moby,0x23)>36?B(moby,0x23)-4:36;
    } else {
        B(moby,0x23)=B(moby,0x23)<124?B(moby,0x23)+4:128;
    }
    if(*(s8 *)(moby+0x23)>=0)*(u16 *)(moby+0x34)|=0x2000;
    else *(u16 *)(moby+0x34)&=0xdfff;
}
