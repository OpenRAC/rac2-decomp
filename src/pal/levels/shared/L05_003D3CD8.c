#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad000[0x1B0];
    int target;                  
    int hasCallback;             
    char block1B8[4];            
    int loopSound;               
    int nearSound;               
} ObjVars003CFF90;
typedef struct {
    char pad000[0x104];
    int flag104;                 
    int flag108;                 
    char pad10C[4];
    int state110;                
    char pad114[8];
    int hasTarget;               
    char *targetObject;          
} ObjCommon003CFF90;
typedef struct {
    char pad00[0x74];
    unsigned char live;          
    char pad75[0x13];
    char *owner;                 
    char pad8C[0x54];
} SoundSlot003CFF90;
extern ObjCommon003CFF90 *moby_get_motion_data(char *);
extern void *state_get_stored_pointer_value(void);
extern void moby_init_reach_and_position_pal(char *);
extern void vec_clear_128(void *);
extern void level_append_object(char *, void *, int, int);
extern void func_L05_003D02C8(void);
extern void follower_l05_update_pal(char *);
extern int moby_process_collision_hit(char *, int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_check_player_in_view_and_range(char *, int, float);
extern int g_feltzin_target_mobys __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern void moby_spawn_effect_once_pal(char *);
extern int moby_can_take_next_step(char *);
extern void follower_start_wander_pal(char *);
extern int math_fast_float_d(void *);
extern int math_fast_helper_a(void *, float);
extern void moby_spawn_trail_marks_pal(char *);
extern char g_sound_state[];

/* The object'vars three-state update. State 1 also aims at a target from the object table; states
   1 and 2 restart the looping sound when its slot no longer belongs to this object. */
void follower_moby_update_pal(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    ObjVars003CFF90 *vars = *(ObjVars003CFF90 **)(obj + 0x68);
    ObjCommon003CFF90 *common = moby_get_motion_data(obj);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned char *)(obj + 0x30) = 255;
        if (!state_get_stored_pointer_value()) return;
        moby_init_reach_and_position_pal(obj);
        vec_clear_128(a);
        if (vars->hasCallback) level_append_object(obj, func_L05_003D02C8, 0, 0);
        return;
    case 1:
        follower_l05_update_pal(obj);
        if (moby_process_collision_hit(obj, 0, 0, 0) == 1) snd_play_from_class_bank(1, 0, obj, 0x957);
        moby_check_player_in_view_and_range(obj, 0, 176.0f);
        if (common->state110 == 1) {
            if (vars->target != -1) {
                char *target;
                common->hasTarget = 1;
                target = (char *)(g_feltzin_target_mobys + (vars->target << 8));
                common->targetObject = target;
                if (fast_vec_dist(target + 0x10, obj + 0x10) < 10.0f) {
                    SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(g_sound_state + vars->nearSound * 0x70);
                    if ((sound->owner != obj || sound->live == 0) && math_random_int_below(400) == 0)
                        vars->nearSound = snd_play_from_class_bank(14, 0, obj, 0xFBF);
                }
            }
            if (common->flag108 && common->flag104) moby_spawn_effect_once_pal(obj);
            if (moby_can_take_next_step(obj)) follower_start_wander_pal(obj);
            math_fast_float_d(vars->block1B8);
            qcopy(b, obj + 0x10);
            b[3] = *(float *)(obj + 0xC) * 0.0009765599970705807f;
            if (math_fast_helper_a(b, 100.0f) != -1) moby_spawn_trail_marks_pal(obj);
        }
        break;
    case 2:
        follower_l05_update_pal(obj);
        if (moby_process_collision_hit(obj, 0, 0, 0) == 1) snd_play_from_class_bank(1, 0, obj, 0x957);
        moby_check_player_in_view_and_range(obj, 0, 176.0f);
        if (common->state110 == 1) {
            if (common->flag104) moby_spawn_effect_once_pal(obj);
            if (moby_can_take_next_step(obj)) follower_start_wander_pal(obj);
            math_fast_float_d(vars->block1B8);
            moby_spawn_trail_marks_pal(obj);
        }
        break;
    }
    {
        SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(g_sound_state + vars->loopSound * 0x70);
        if (sound->owner != obj || sound->live == 0)
            vars->loopSound = snd_play_from_class_bank(3, 6, obj, 0x957);
    }
}

