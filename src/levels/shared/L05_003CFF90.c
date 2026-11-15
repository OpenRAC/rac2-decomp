#include "common.h"

/* The fields this update uses in the object's own state and in the block func_002ED688 returns. */
typedef struct {
    char pad000[0x1B0];
    int target;                 /* 0x1B0: index of the object it aims at, or -1 */
    int hasCallback;            /* 0x1B4 */
    char block1B8[4];           /* 0x1B8 */
    int loopSound;              /* 0x1BC */
    int nearSound;              /* 0x1C0 */
} ObjVars003CFF90;

typedef struct {
    char pad000[0x104];
    int flag104;                /* 0x104 */
    int flag108;                /* 0x108 */
    char pad10C[4];
    int state110;               /* 0x110 */
    char pad114[8];
    int hasTarget;              /* 0x11C */
    char *targetObject;         /* 0x120 */
} ObjCommon003CFF90;

typedef struct {
    char pad00[0x74];
    unsigned char live;         /* 0x74 */
    char pad75[0x13];
    char *owner;                /* 0x88 */
    char pad8C[0x54];
} SoundSlot003CFF90;

extern ObjCommon003CFF90 *moby_get_motion_data(char *);
extern int state_get_stored_pointer_value(void);
extern void moby_init_reach_and_position(char *);
extern void vec_clear_128(void *);
extern void level_append_object(char *, void *, int, int);
extern void func_L05_003D02C8(void);
extern void moby_update_movement_state(char *);
extern int moby_process_collision_hit(char *, int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_check_player_in_view_and_range(char *, int, float);
extern int D_L05_001B251C __attribute__((sda));
extern float fast_vec_dist(void *, void *);
extern int math_random_int_below(int);
extern void moby_spawn_effect_once(char *);
extern int moby_can_take_next_step(char *);
extern void moby_start_movement_state(char *);
extern int math_fast_float_d(void *);
extern int math_fast_helper_a(void *, float);
extern void func_L05_003D0538(char *);
extern char g_sound_state[];

/* The object's three-state update. State 1 also aims at a target from the object table; states
   1 and 2 restart the looping sound when its slot no longer belongs to this object. */
/* Runs a creature's three states, aiming at its target, playing its sounds and attacking when
   it is ready. */
void func_L05_003CFF90(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    ObjVars003CFF90 *s = *(ObjVars003CFF90 **)(obj + 0x68);
    ObjCommon003CFF90 *p = moby_get_motion_data(obj);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned char *)(obj + 0x30) = 255;
        if (!state_get_stored_pointer_value()) return;
        moby_init_reach_and_position(obj);
        vec_clear_128(a);
        if (s->hasCallback) level_append_object(obj, func_L05_003D02C8, 0, 0);
        return;
    case 1:
        moby_update_movement_state(obj);
        if (moby_process_collision_hit(obj, 0, 0, 0) == 1) snd_play_from_class_bank(1, 0, obj, 0x957);
        moby_check_player_in_view_and_range(obj, 0, 176.0f);
        if (p->state110 == 1) {
            if (s->target != -1) {
                char *target;
                p->hasTarget = 1;
                target = (char *)(D_L05_001B251C + (s->target << 8));
                p->targetObject = target;
                if (fast_vec_dist(target + 0x10, obj + 0x10) < 10.0f) {
                    SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(g_sound_state + s->nearSound * 0x70);
                    if ((sound->owner != obj || sound->live == 0) && math_random_int_below(400) == 0)
                        s->nearSound = snd_play_from_class_bank(14, 0, obj, 0xFBF);
                }
            }
            if (p->flag108 && p->flag104) moby_spawn_effect_once(obj);
            if (moby_can_take_next_step(obj)) moby_start_movement_state(obj);
            math_fast_float_d(s->block1B8);
            qcopy(b, obj + 0x10);
            b[3] = *(float *)(obj + 0xC) * 0.0009765599970705807f;
            if (math_fast_helper_a(b, 100.0f) != -1) func_L05_003D0538(obj);
        }
        break;
    case 2:
        moby_update_movement_state(obj);
        if (moby_process_collision_hit(obj, 0, 0, 0) == 1) snd_play_from_class_bank(1, 0, obj, 0x957);
        moby_check_player_in_view_and_range(obj, 0, 176.0f);
        if (p->state110 == 1) {
            if (p->flag104) moby_spawn_effect_once(obj);
            if (moby_can_take_next_step(obj)) moby_start_movement_state(obj);
            math_fast_float_d(s->block1B8);
            func_L05_003D0538(obj);
        }
        break;
    }
    {
        SoundSlot003CFF90 *sound = (SoundSlot003CFF90 *)(g_sound_state + s->loopSound * 0x70);
        if (sound->owner != obj || sound->live == 0)
            s->loopSound = snd_play_from_class_bank(3, 6, obj, 0x957);
    }
}
