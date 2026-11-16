#include "include_asm.h"

#include "common.h"
extern u8 *g_moby_list_start __attribute__((sda));
extern u16 *g_moby_l12_group_lists[];
extern u16 g_slot_timer_reset_value __attribute__((sda));
extern u8 *g_tracked_object_ptr __attribute__((sda));
extern u8 *g_second_tracked_object __attribute__((sda));
extern int FloatToInt(float);
extern void moby_set_state(void *,int,int);
extern void func_PAL_002A7E68(void *,int,int,int);
extern float fast_vec_dist(void *,void *);
extern void moby_update_ground_check(void *);
extern int func_PAL_002B1A50(void *,void *,int);
extern void squirrel_alert_group(void *);
extern int weapon_select_aim_target(void *,int,int,int,float,float);
extern int point_in_path_xy(void *,void *,int,float);
extern void func_PAL_002B14F8(void *,void *,int,int,float);
extern u8 g_hero_prev_position[];
extern u8 *g_hero_moby NOT_SDA;
extern u8 *g_path_zone_table[];
extern float g_guard_zone_range __attribute__((sda));
extern u8 g_hero_position[];
extern u8 g_item_owned_flags[] __attribute__((sda));
extern int g_game_mode NOT_SDA;

/* Sets up the object's AI parameters on its first update, then refreshes its target state and
   clears it when the target leaves the object's zone. */
void func_PAL_L12_003E58E8(u8 *o) {
    u8 *d=*(u8 **)(o+0x68);
    if(!o[0x20]) {
        *(short *)(*(u8 **)(o+0x24)+0x46)=5;
        *(u16 *)(o+0x34)|=0x1000;
        d[0x48]=FloatToInt(15.0f);d[0x4A]=FloatToInt(6.0f);
        d[0x29]=1;
        d[0x70]=8; *(int *)(d+0xA8)=3; d[0x71]=11; d[0x72]=11;
        d[0x76]=13; d[0x77]=14;
        *(float *)(d+0x7C)=0.20000002f; *(float *)(d+0x80)=0.10000001f;
        *(float *)(d+0x84)=0.008f;
        *(float *)(d+0x88)=0.012f; *(float *)(d+0x8C)=0.006f;
        *(float *)(d+0x90)=0.5f; *(float *)(d+0x94)=0.5f; *(float *)(d+0x9C)=0.4f;
        d[0xCC]=7; d[0xCD]=10; d[0xCE]=7; d[0xCF]=10; d[0xD2]=8; d[0xD3]=12;
        if(*(float *)(d+0x36C)==0) *(float *)(d+0x36C)=16;
        if(*(float *)(d+0x370)==0) *(float *)(d+0x370)=24;
        if(*(int *)(d+0x140)) *(float *)(d+0x20)=1;
        d[0x28]=3;
        qcopy_nc(d+0x340,o+0x10);
        *(u8 **)(d+0x198)=d+0x240;*(u8 **)(d+0x19C)=d+0x2C0;
        *(float *)(d+0x184)=1;*(float *)(d+0x154)=0.25f;*(float *)(d+0x150)=0.5f;
        *(float *)(d+0x158)=0.4f;*(float *)(d+0x15C)=0.4f;
        *(float *)(d+0x160)=0.78539824f;*(float *)(d+0x180)=0.52359885f;
        *(float *)(d+0x17C)=0.008f;
        if(*(int *)(d+0x378)!=-1) moby_set_state(o,14,5);
        else if(*(int *)(d+0x13C)==-1) {
            moby_set_state(o,1,0);
            if(o[0x43]) func_PAL_002A7E68(o,0,0,0);
        } else {
            moby_set_state(o,9,4);
            if(o[0x43]!=14) func_PAL_002A7E68(o,14,0,0);
            *(float *)(o+0x18)+=4;*(int *)(o+0x98)=0;
            *(u16 *)(o+0x34)=(*(u16 *)(o+0x34)|0x41)&0xEFFF;
        }
    }
    if(o[0x31] && fast_vec_dist(o+0x10,g_hero_prev_position)<24) {moby_update_ground_check(o);o[0x6F]=22;}
    if(func_PAL_002B1A50(o,d+0x60,0)) squirrel_alert_group(o);
    *(short *)(d+0x364)=weapon_select_aim_target(o,-1,0,0,*(float *)(d+0x36C),3);
    if(*(u8 **)(d+0x120)) *(u8 **)(d+0x368)=*(u8 **)(d+0x120); else *(u8 **)(d+0x368)=g_hero_moby;
    if(*(short *)(d+0x364)==1) {
        float range=g_guard_zone_range;
        if(*(int *)(d+0x130)!=-1) {
            u8 *zone=g_path_zone_table[*(int *)(d+0x130)];
            if(!point_in_path_xy(*(u8 **)(d+0x120)+0x10,zone+0x10,*(int *)zone,range)) *(short *)(d+0x364)=0;
        }
    }
    func_PAL_002B14F8(o,d+0x3C0,1,1,g_guard_zone_range);
}
