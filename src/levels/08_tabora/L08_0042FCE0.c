#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern void moby_set_state(void *,int,int);
extern float FastAddRotations(float,float);
extern char *part_find_owned_effect_slot(void *,int,int);
extern float moby_update_aim_target_strength(void *,void *);
extern void gfx_start_color_fade(void *,void *);
extern void gfx_update_color_fade(void *,void *);
extern void PlayMobySound(int,int,void *);
extern void set_moby_color(void *,int,int,int);
extern int moby_count_group_not_in_state(int,int);
extern int math_random_int_range(int,int);
extern void part_spawn_bolt_pickups(void *,int,int,int,int,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,int);
extern void moby_mark_spawned(void *);
extern int g_active_emitter_count __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern int D_L08_002B35C0[];
/* A breakable object with a few hit points: flashes when hit, and when destroyed it bursts into effects. */
void breakable_l08_update(char *moby) {
    char *vars=*(char **)(moby+0x68);
    float hit;
    float offset[4] __attribute__((aligned(16)));
    int effectId;
    switch(*(u8 *)(moby+0x20)) {
    case 0:
        *(s16 *)(vars+0x24)=5;
        *(float *)(vars+0x20)=5.0f;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        *(float *)(moby+0xF8)=FastAddRotations(*(float *)(moby+0xF8),*(float *)(vars+0x64)*0.0002908882452175021f);
        hit=moby_update_aim_target_strength(moby,part_find_owned_effect_slot(moby,0x230000,0));
        if(hit>0.0f) {
            *(u8 *)(vars+0x57)=255;
            *(u8 *)(vars+0x58)=128;
            *(u8 *)(vars+0x59)=128;
            gfx_start_color_fade(moby,vars+0x50);
            if(g_active_emitter_count<4) *(float *)(vars+0x20)-=hit;
        }
        if(*(float *)(vars+0x20)<0.0f) {
            PlayMobySound(0,0,moby);
            moby_set_state(moby,2,-1);
        }
        gfx_update_color_fade(moby,vars+0x50);
        *(u8 *)(moby+0xA8)=255;
        break;
    case 2:
        set_moby_color(moby,*(u8 *)(vars+0x54),*(u8 *)(vars+0x55),*(u8 *)(vars+0x56));
        if(moby_count_group_not_in_state(*(u8 *)(moby+0x21),-1)==1) {
            effectId=*(int *)((g_current_map_index << 2)+(char *)D_L08_002B35C0)*35-1;
            part_spawn_bolt_pickups(moby,effectId,effectId,3,-1,math_random_int_range(1,3),0.0f);
        }
        *(u128 *)offset=0;
        offset[0]=0.11666667461395264f; offset[1]=0.06666667014360428f;
        matrix_mul_vec3(offset,offset,moby+0xC0);
        if(*(u8 *)(moby+0x31)) part_spawn_masked_debris(moby,255,offset,3.0f,6.0f,3.0f,6.0f,255);
        else part_spawn_masked_debris(moby,170,offset,3.0f,6.0f,3.0f,6.0f,255);
        moby_mark_spawned(moby);
        break;
    }
}
