#include "names.h"
/* func_US2_L01_00398790, the USA v2.00 copy of func_L01_003973A0: the same C, where rename func_002B0A18 becomes func_US2_002B1880. */
#include "common.h"
extern int g_current_map_index MACRO_ADDR;
extern short g_platform_mode NOT_SDA;
extern unsigned char g_level_progress_flags[];
extern char g_hero_state[];
extern int g_platinum_bolt_flag;
extern float g_collectible_height_scale __attribute__((sda));
extern float g_bob_base_height __attribute__((sda));
extern float g_bob_l01_amplitude __attribute__((sda));
extern float g_bolt_spin_speed_a __attribute__((sda));
extern float g_bolt_bob_spin_speed __attribute__((sda));
extern float g_bolt_spin_speed_b __attribute__((sda));
extern float g_bolt_spin_speed_c __attribute__((sda));
extern int g_sparkle_chance __attribute__((sda));
extern int g_platinum_bolt_counter __attribute__((sda));
extern int g_platinum_bolt_timer __attribute__((sda));
extern int g_camera_lock_flag __attribute__((sda));
extern float math_random_angle(void);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float,float);
extern float vec_distance_xy(void*,void*);
extern float math_fabs(float);
extern int math_random_int_below(int);
extern void moby_init_randomized_vars(void*),part_draw_bolt_glow_rings(void*),part_spawn_sparkle_trail_above_ground(void*),teleporter_start_arrival(void*),cam_blend_moby_update(void*),bobbing_l01_moby_update(void*);
extern void value_set_entry_by_index_us2(int,int), moby_mark_spawned(void*), moby_set_state(void*,int,int), anim_start_blended(void*,int,int,int);
extern int PlayMobySound(int,int,void*);
extern int MemcardSave(int,int);
extern void set_hero_animation(int,int,float),hero_reset_position_and_direction(void*,void*,int,int),cam_set_mode_state(int);
extern int math_fast_float_d(void*);

/* Runs a platinum bolt: it bobs and spins until Ratchet grabs it, then records the pickup and saves (USA v2.00). */
void platinum_bolt_update_us2(unsigned char *moby)
{
    char *vars = *(char **)(moby+0x68);
    int i;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (*(int *)vars == -1 || g_level_progress_flags[*(int *)vars + (g_current_map_index << 2)]) goto remove;
        {
            qcopy_nc(vars+0x10,moby+0x10);
            *(float *)(vars+0x1C)=*(float *)(moby+0xF8);
            *(float *)(moby+0xF0)=math_random_angle();
            *(float *)(moby+0xF4)=math_random_angle();
            *(float *)(moby+0xF8)=math_random_angle();
            ((float *)moby)[0xFC/4]=math_random_angle();
            ((float *)vars)[0x68/4]=g_bolt_spin_speed_a*0.0002908882452175021f;
            ((float *)vars)[0x64/4]=g_bolt_spin_speed_b*0.0002908882452175021f;
            ((float *)vars)[0x60/4]=g_bolt_spin_speed_c*0.0002908882452175021f;
            if (*(short *)(moby+0x32)<64) *(short *)(moby+0x32)=64;
            moby[0x20]=1;
            moby_init_randomized_vars(moby);
        }
        break;
    case 1: {
        char *player;
        *(float *)(moby+0x2C)=*(float *)(*(char **)(moby+0x24)+0x24)*g_collectible_height_scale;
        {
            float phase = math_fast_sin_or_cos_b(*(float *)(moby+0xFC));
            float height = *(float *)(vars+0x18)+g_bob_base_height+g_bob_l01_amplitude*phase;
            float step = g_bolt_spin_speed_a*0.0002908882452175021f;
            float angle;
            *(float *)(moby+0x18)=height;
            angle=FastAddRotations(*(float *)(moby+0xF0),step);
            step=g_bolt_spin_speed_b*0.0002908882452175021f;
            *(float *)(moby+0xF0)=angle;
            angle=FastAddRotations(*(float *)(moby+0xF4),step);
            step=g_bolt_spin_speed_c*0.0002908882452175021f;
            *(float *)(moby+0xF4)=angle;
            angle=FastAddRotations(*(float *)(moby+0xF8),step);
            step=g_bolt_bob_spin_speed*0.0002908882452175021f;
            *(float *)(moby+0xF8)=angle;
            *(float *)(moby+0xFC)=FastAddRotations(*(float *)(moby+0xFC),step);
        }
        part_draw_bolt_glow_rings(moby);
        if (!math_random_int_below(g_sparkle_chance)) part_spawn_sparkle_trail_above_ground(moby);
        player=g_hero_state+0x80;
        if (!(vec_distance_xy(moby+0x10,player)<3.0f)) break;
        player -= 0x80;
        if (math_fabs(*(float *)(moby+0x18)-*(float *)(player+0x88))<2.0f &&
            *(int *)(player+0x24CC) &&
            ((unsigned char)player[0x22B4]==3 || !player[0x22B4])) {
            if (!*(short *)(vars+0xC) && *(int *)(player+0x2294)!=0x31) goto inactive;
            g_platinum_bolt_timer=180;
            value_set_entry_by_index_us2(0x124B,-1);
            g_level_progress_flags[*(int *)vars+(g_current_map_index<<2)]=1;
            g_platinum_bolt_counter++;
            MemcardSave(0,-1);
            PlayMobySound(1,0,moby);
        remove:
            moby_mark_spawned(moby);
        }
        break;
    }
    inactive:
        if (*(int *)(vars+0x78)) {
            *(unsigned short *)(moby+0x34) |= 0x41;
            moby_set_state(moby,3,-1);
            break;
        }
        goto initialize;
    case 3:
        if (g_platform_mode) break;
    initialize:
        teleporter_start_arrival(moby);
        break;
    case 2: {
        {
            char *player = g_hero_state;
            g_platinum_bolt_flag=1;
            *(short *)(player+0x1DC)=3;
            cam_blend_moby_update(moby);
            qcopy_nc(moby+0x10,player+0x80);
            player += 0x90;
            qcopy_nc(moby+0xF0,player);
        }
        if ((unsigned char)moby[0x42]==1) {
            bobbing_l01_moby_update(moby);
            if (!math_random_int_below(10)) part_spawn_sparkle_trail_above_ground(moby);
            if (moby[0x60]&2) {
                if (moby[0x43]) anim_start_blended(moby,0,0,0);
                *(unsigned short *)(moby+0x34)|=1;
                moby[0x31]=0;
                for (i=3;i>=0;i--) part_spawn_sparkle_trail_above_ground(moby);
            }
        }
        {
        char *player = g_hero_state;
        if (*(int *)(player+0xC28)&2) set_hero_animation(0,0,30.0f);
        if (!moby[0x42] && math_fast_float_d(vars+0x6C)) {
            g_platinum_bolt_timer=180;
            value_set_entry_by_index_us2(0x124B,-1);
            g_level_progress_flags[*(int *)vars+(g_current_map_index<<2)]=1;
            g_platinum_bolt_counter++;
            g_camera_lock_flag=0;
            hero_reset_position_and_direction(player+0x80,player+0x90,0,0);
            cam_set_mode_state(0);
            MemcardSave(0,-1);
            moby_mark_spawned(moby);
        }
        }
        break;
    }
    }
}
