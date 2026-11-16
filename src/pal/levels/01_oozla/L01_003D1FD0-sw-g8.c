#include "include_asm.h"

#include "common.h"
extern void swamp_monster_apply_damage_pal(u8 *);
extern void swamp_monster_release_timers(u8 *);
extern void anim_start_blended_pal(void *,int,int,int);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern void swamp_monster_init_linked_body_part(u8 *);
extern void swamp_monster_spawn_splash_pal(u8 *, int, int, int);
extern u8 *g_path_l01_table[];
extern int math_random_int_below(int);
extern void script_queue_keyed_request(int,int);
extern void moby_set_state(u8 *,int,int);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void vec_fast_divide_helper(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern float mat_fast_helper_a(float,float);
extern float FastVecLength(void *);
extern float MobySpringTurn(void *,void *,float,float,float,float);
extern int point_in_path_xy(void *,void *,int);
extern s32 math_closest_point_on_polygon_edge(void *,void *,void *,int);
extern void moby_set_byte_on_group(int,int);
extern void SetDeathBits_pal(void *,int,int);
extern void moby_mark_spawned(void *);

/* Steps the owner state, moving along its path and releasing expired objects.
 * Separate unit for the jump table and small-data entity-base access. */
void swamp_monster_eye_update_pal(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float offset[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float angle;
    swamp_monster_apply_damage_pal(moby);
    switch (moby[0x95]) {
    case 0:
        swamp_monster_init_linked_body_part(moby);
        break;
    case 1:
        if (moby[0x60] & 2) {
            if (moby[0x42] != 2 && !math_random_int_below(15)) {
                if (moby[0x43] != 2) anim_start_blended_pal(moby,2,0,10);
            } else if (moby[0x43] != 1) anim_start_blended_pal(moby,1,0,10);
        }
        if (*(int *)(vars+0xBC)) {
            script_queue_keyed_request(*(int *)(vars+0xD0),*(int *)(vars+0xD8));
            if (moby[0x43]!=1) anim_start_blended_pal(moby,1,0,10);
            moby_set_state(moby,0,5);
        }
        break;
    case 2:
        if (!math_random_int_below(5)) swamp_monster_spawn_splash_pal(moby,3,10,1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby+0x34) &= 0xEFFF;
            if (moby[0x43]) anim_start_blended_pal(moby,0,0,10);
            *(float *)(moby+0x48)=0.0f;
            moby_set_state(moby,0,4);
        }
        break;
    case 3:
        if (!math_random_int_below(5)) swamp_monster_spawn_splash_pal(moby,3,10,1);
        if (moby[0x60] & 2) {
            *(u16 *)(moby+0x34) |= 0x1000;
            if (moby[0x43]!=1) anim_start_blended_pal(moby,1,0,10);
            moby_set_state(moby,0,5);
        }
        break;
    case 4:
        if (*(int *)(vars+0xBC)>0) {
            *(float *)(moby+0x48)=1.0f;
            if (moby[0x43]) anim_start_blended_pal(moby,0,0,10);
            moby_set_state(moby,0,3);
        }
        break;
    case 5:
        if (moby[0x60] & 2) {
            if (moby[0x42] != 2 && !math_random_int_below(15)) {
                if (moby[0x43] != 2) anim_start_blended_pal(moby,2,0,10);
            } else if (moby[0x43] != 1) anim_start_blended_pal(moby,1,0,10);
        }
        {
            if (!*(int *)(vars+0xBC)) qcopy(vars+0x70,vars+0x60);
            FastVecSub(offset,vars+0x70,moby+0x10);
            vec_fast_divide_helper(offset,offset,0.060000002f);
            FastVecAdd(moby+0x10,moby+0x10,offset);
            angle=mat_fast_helper_a(*(float *)(vars+0x80)-*(float *)(moby+0x10),*(float *)(vars+0x84)-*(float *)(moby+0x14));
            MobySpringTurn(moby,vars+0xB8,angle,0.0016755164f,0.1f,0.12566373f);
            if (!*(int *)(vars+0xBC)) {
                script_queue_keyed_request(*(int *)(vars+0xD4),*(int *)(vars+0xDC));
                *(u16 *)(moby+0x34) &= 0xEFFF;
                if (moby[0x43] != 3) anim_start_blended_pal(moby,3,0,20);
                moby_set_state(moby,0,2);
            }
        }
        break;
    case 6:
        FastVecAdd(offset,moby+0x10,vars+0x90);
        if (point_in_path_xy(offset,g_path_l01_table[*(int *)(vars+0xA8)]+0x10,*(int *)g_path_l01_table[*(int *)(vars+0xA8)]))
            qcopy(moby+0x10,offset);
        else {
            math_closest_point_on_polygon_edge(moby+0x10,offset,g_path_l01_table[*(int *)(vars+0xA8)]+0x10,*(int *)g_path_l01_table[*(int *)(vars+0xA8)]);
            FastVecSub(pull,vars+0x60,moby+0x10);
            vec_scale_to_length(pull,pull,0.040000003f);
            FastVecAdd(moby+0x10,moby+0x10,pull);
        }
        angle=FastVecLength(vars+0x90)-0.0044f;
        if (angle<0.0f) angle=0.0f;
        vec_scale_to_length(vars+0x90,vars+0x90,angle);
        if (*(float *)(vars+0x20)<=0.0f && !math_random_int_below(4)) swamp_monster_spawn_splash_pal(moby,3,10,1);
        if (moby[0x60]&2) {
            if (*(float *)(vars+0x20)<=0.0f) {
                *(u16 *)(moby+0x34) &= 0xEFFF;
                moby_set_state(moby,0,7);
            } else {
                *(u16 *)(moby+0x34) |= 0x1000;
                if (moby[0x43]!=1) anim_start_blended_pal(moby,1,0,10);
                moby_set_state(moby,0,5);
            }
        }
        break;
    case 7:
        script_queue_keyed_request(*(int *)(vars+0xD4),*(int *)(vars+0xDC));
        if (*(int *)(vars+0xB0)!=-1) moby_set_byte_on_group(*(int *)(vars+0xB0),1);
        SetDeathBits_pal(moby,0x200,3);
        if (*(int *)(vars+0xCC)!=-1) moby_mark_spawned(D_L01_001B255C_base[0]+(*(int *)(vars+0xCC)<<8));
        *(int *)(vars+0xCC)=-1;
        moby_mark_spawned(moby);
        return;
    }
    swamp_monster_release_timers(moby);
}
