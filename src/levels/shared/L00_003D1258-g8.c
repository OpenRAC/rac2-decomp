/* Updates an ammo pickup: tests collection, awards ammo, then homes in and fades out. */
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

extern int D_L00_001A8FF0[] __attribute__((sda));
extern int g_frame_l00_counter[] __attribute__((sda));
extern int D_L00_001B2ADC[] MACRO_ADDR;

extern void *g_hero_moby NOT_SDA;
extern void vec_store_helper(void *);
extern void cam_moby_update(void *);
extern float fast_vec_dist(void *,void *);
extern int math_fast_float_d(void *);
extern float math_fabs(float);
extern float vec_distance_xy(void *,void *);
extern float gravity_get_center_distance(void *);
extern int weapon_add_ammo(int,int);
extern void part_reset_effects(int,int,int);
extern void moby_set_state(void *,int,int);
extern void vec_clear_128(void *);
extern int subtract_integer_with_clamp(int);
extern int PlayMobySound(int,int,void *);
extern void FastVecSub(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void ApproachValue(void *,float,float);
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
void AmmoPickupUpdate(char *moby)
{
    char *vars=*(char **)(moby+0x68);
    PickupResource *resource;
    int j,i,can_pick_up,changed,old_count,delta,sound;
    float speed,time_left,target_speed;
    float work[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float to_target[4] __attribute__((aligned(16)));
    float axis_cross[4] __attribute__((aligned(16)));
    float before[4] __attribute__((aligned(16)));
    float after[4] __attribute__((aligned(16)));
    float shift[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char matrix[48] __attribute__((aligned(16)));
    switch(B(moby,0x20)) {
    case 0:
        B(moby,0x20)=1;
        for(j=0;j<56;j++) {
            resource=&g_weapon_l00_table[g_item_slot_to_record[j]];
            if(resource->moby_class==S(moby,0xaa))I(vars,0x68)=j;
        }
        break;
    case 1:
        if(B(vars,0x5c)==3 && (g_frame_l00_counter[0]&15)==(((int)moby>>8)&15)) {
            qzero(vars);vec_store_helper(vars+0x10);B(vars,0x5c)=0;
        }
        qcopy(work,vars);
        cam_moby_update(moby);
        changed=0;
        if(fast_vec_dist(work,vars)>F(vars,0x48)*2.0f)changed=1;
        can_pick_up=1;
        if(B(vars,0x5c)||changed) {
            if(math_fast_float_d(vars+0x7c)) {
                if(math_fabs(F(moby,0x18)-PLAYER->position[2])>PLAYER->height)can_pick_up=0;
                else if(vec_distance_xy(moby+0x10,PLAYER->position)>PLAYER->range)can_pick_up=0;
            }
        } else {
            can_pick_up=0;
            if(math_fabs(F(moby,0x18)-PLAYER->position[2])<PLAYER->height &&
               vec_distance_xy(moby+0x10,PLAYER->position)<PLAYER->range)I(vars,0x7c)=3;
        }
        if(g_item_ammo_counts[I(vars,0x68)] >=
           ((PickupResource *)(g_item_slot_to_record[I(vars,0x68)] * 224 + (unsigned int)g_weapon_l00_table))->capacity)can_pick_up=0;
        if(D_L00_001A8FF0[0]) {
            if(gravity_get_center_distance(moby+0x10)<F(vars,0x78)-2.0f)goto force_pickup;
        } else if(F(moby,0x18)<F(vars,0x78)-2.0f)goto force_pickup;
        if(!PLAYER->override)goto check_enabled;
force_pickup:
        can_pick_up=1;
check_enabled:
        if(!PLAYER->enabled)can_pick_up=0;
        if(can_pick_up) {
            i=I(vars,0x68);old_count=g_item_ammo_counts[i];
            weapon_add_ammo(i,I(vars,0x60));
            if(old_count<g_item_ammo_counts[i]) {
                delta=g_item_ammo_counts[i]-old_count;
                if(delta==1) {
                    resource=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=resource->single_sound;
                } else {
                    resource=&g_weapon_l00_table[g_item_slot_to_record[i]];
                    sound=resource->multiple_sound;
                }
                part_reset_effects(sound,delta,-1);
            }
            moby_set_state(moby,2,-1);
            F(vars,0x74)=0.13333334f;
            vec_clear_128(vars);
            if(subtract_integer_with_clamp(g_frame_l00_counter[0]-D_L00_001B2ADC[0])>10) {
                PlayMobySound(0,0,moby);D_L00_001B2ADC[0]=g_frame_l00_counter[0];
            }
        }
        break;
    case 2:
        FastVecSub(work,moby+0x10,PLAYER->position);
        matrix_mul_vec3(work,work,PLAYER->matrix);
        target_speed=8.0f;
        if(work[2]>0.0f)target_speed=0.0f;
        ApproachValue(vars+0x74,target_speed,0.0066666668f);
        vec_scale_to_length(push,PLAYER->axis,F(vars,0x74));
        FastVecAdd(moby+0x10,moby+0x10,push);
        FastVecAdd(moby+0x10,moby+0x10,PLAYER->motion);
        speed=FastVecLength(vars);
        ApproachValue(&speed,1.0666667f,0.0066666668f);
        FastVecSub(to_target,PLAYER->target,moby+0x10);
        time_left=FastVecLength(to_target)/speed;
        if(time_left<30.0f)ApproachValue(moby+0x2c,0.0f,F(*(char **)(moby+0x24),0x24)*0.033333335f);
        if(F(moby,0x2c)==0.0f) {moby_mark_spawned(moby);return;}
        if(time_left<=1.0f) {moby_mark_spawned(moby);return;}
        vec_scale_to_length(vars,to_target,speed);
        FastVecAdd(moby+0x10,moby+0x10,vars);
        FastVecCross(axis_cross,PLAYER->axis,vars);
        vec_set_direction_with_complement(axis_cross,axis_cross,0.087266475f);
        *(Quadword *)up=0;up[2]=0.3f;
        matrix_mul_vec3(before,up,moby+0xc0);
        quaternion_to_rotation_basis(axis_cross,matrix);
        multiply_matrix3x3(moby+0xc0,matrix,moby+0xc0);
        matrix_mul_vec3(after,up,moby+0xc0);
        FastVecSub(shift,after,before);
        FastVecSub(moby+0x10,moby+0x10,shift);
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
