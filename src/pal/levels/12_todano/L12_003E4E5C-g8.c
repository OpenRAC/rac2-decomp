#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_list_start __attribute__((sda));
extern u16 *g_moby_l12_group_lists[];
extern u16 g_slot_timer_reset_value __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((sda));
extern u8 *g_second_tracked_object __attribute__((sda));
extern int FloatToInt(float);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object_pal(void *,void *,int);
extern void squirrel_alert_group(void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern int point_in_path_xy(void *,void *,int,float);
extern void value_set_and_smooth_pal(void *,void *,int,int,float);
extern u8 g_hero_prev_position[];
extern u8 *g_hero_moby NOT_SDA;
extern u8 *g_path_zone_table[];
extern float g_guard_zone_range __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern int g_game_mode NOT_SDA;

/* Sets up the object's AI parameters on its first update, then refreshes its target state and
   clears it when the target leaves the object's zone. */
void guard_creature_update_pal(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);
    if(!moby[0x20]) {
        *(short *)(*(u8 **)(moby+0x24)+0x46)=5;
        *(u16 *)(moby+0x34)|=0x1000;
        vars[0x48]=FloatToInt(15.0f);vars[0x4A]=FloatToInt(6.0f);
        vars[0x29]=1;
        vars[0x70]=8; *(int *)(vars+0xA8)=3; vars[0x71]=11; vars[0x72]=11;
        vars[0x76]=13; vars[0x77]=14;
        *(float *)(vars+0x7C)=0.20000002f; *(float *)(vars+0x80)=0.10000001f;
        *(float *)(vars+0x84)=0.008f;
        *(float *)(vars+0x88)=0.012f; *(float *)(vars+0x8C)=0.006f;
        *(float *)(vars+0x90)=0.5f; *(float *)(vars+0x94)=0.5f; *(float *)(vars+0x9C)=0.4f;
        vars[0xCC]=7; vars[0xCD]=10; vars[0xCE]=7; vars[0xCF]=10; vars[0xD2]=8; vars[0xD3]=12;
        if(*(float *)(vars+0x36C)==0) *(float *)(vars+0x36C)=16;
        if(*(float *)(vars+0x370)==0) *(float *)(vars+0x370)=24;
        if(*(int *)(vars+0x140)) *(float *)(vars+0x20)=1;
        vars[0x28]=3;
        qcopy_nc(vars+0x340,moby+0x10);
        *(u8 **)(vars+0x198)=vars+0x240;*(u8 **)(vars+0x19C)=vars+0x2C0;
        *(float *)(vars+0x184)=1;*(float *)(vars+0x154)=0.25f;*(float *)(vars+0x150)=0.5f;
        *(float *)(vars+0x158)=0.4f;*(float *)(vars+0x15C)=0.4f;
        *(float *)(vars+0x160)=0.78539824f;*(float *)(vars+0x180)=0.52359885f;
        *(float *)(vars+0x17C)=0.008f;
        if(*(int *)(vars+0x378)!=-1) moby_set_state(moby,14,5);
        else if(*(int *)(vars+0x13C)==-1) {
            moby_set_state(moby,1,0);
            if(moby[0x43]) anim_start_blended_pal(moby,0,0,0);
        } else {
            moby_set_state(moby,9,4);
            if(moby[0x43]!=14) anim_start_blended_pal(moby,14,0,0);
            *(float *)(moby+0x18)+=4;*(int *)(moby+0x98)=0;
            *(u16 *)(moby+0x34)=(*(u16 *)(moby+0x34)|0x41)&0xEFFF;
        }
    }
    if(moby[0x31] && fast_vec_dist(moby+0x10,g_hero_prev_position)<24) {moby_update_ground_check(moby);moby[0x6F]=22;}
    if(moby_apply_damage_to_object_pal(moby,vars+0x60,0)) squirrel_alert_group(moby);
    *(short *)(vars+0x364)=weapon_select_aim_target(moby,-1,0,0,*(float *)(vars+0x36C),3);
    if(*(u8 **)(vars+0x120)) *(u8 **)(vars+0x368)=*(u8 **)(vars+0x120); else *(u8 **)(vars+0x368)=g_hero_moby;
    if(*(short *)(vars+0x364)==1) {
        float range=g_guard_zone_range;
        if(*(int *)(vars+0x130)!=-1) {
            u8 *zone=g_path_zone_table[*(int *)(vars+0x130)];
            if(!point_in_path_xy(*(u8 **)(vars+0x120)+0x10,zone+0x10,*(int *)zone,range)) *(short *)(vars+0x364)=0;
        }
    }
    value_set_and_smooth_pal(moby,vars+0x3C0,1,1,g_guard_zone_range);
}
