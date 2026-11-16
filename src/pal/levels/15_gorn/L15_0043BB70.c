#include "include_asm.h"


#include "common.h"

/* func_L15_00435E80 is in L15_00435E80.c. */

/* Puts a path-mover object into its waiting state: sets its timers, speed and flags. */
void gorn_path_mover_wait_init_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);

    *(int *)(vars + 0x270) = 1;
    *(int *)(vars + 0x274) = 0x190;
    *(char *)(moby + 0x23) = 0x20;
    *(char *)(moby + 0x20) = 2;
    *(unsigned short *)(moby + 0x34) |= 8;
    *(float *)(vars + 0x180) = 450.0f;
    *(int *)(moby + 0x98) = 0;
}





extern void DrawPath(char *, int, int, int, float, int);
extern int follower_has_reached_target(char *);
extern void follower_set_push_vector(char *, char *);
extern void follower_set_state(char *, int);
extern void follower_l05_update_pal(char *);
extern int moby_process_collision_hit(char *, int, int, int);
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;
typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
extern char *g_path_l15_table[];
extern void gorn_path_mover_init_pal(char *);
extern void gorn_path_mover_start_follow_pal(void);
extern char *moby_get_motion_data(unsigned char *owner);
extern int math_fast_float_d(void *);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern void *state_get_stored_pointer_value(void);
extern void level_append_object(void *, void *, int, int);
extern int math_random_int_below(int);
extern s32 g_ship_damage_effect_count[] __attribute__((sda));
extern s32 g_gorn_ship_damage_joints[] SDATA(D_L15_001B1780);
extern s32 g_gorn_ship_part_joints[] SDATA(D_L15_001B17B0);
extern s32 PlayMobySound(s32 a, s32 b, void *c);
extern s32 math_random_int_below(s32 a);
extern f32 math_random_float_range(f32 a, f32 b);
extern s32 FloatToInt(f32 a);
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern int PlayMobySound(int, int, void *);
extern int math_random_int_below(int);

/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void gorn_path_mover_update_pal(char *object) {
    char *mover = object;
    char *state = *(char **)(mover + 0x68);

    switch (*(unsigned char *)(mover + 0x20)) {
    case 0:
        *(unsigned char *)(mover + 0x30) = 0xFF;
        if (state_get_stored_pointer_value() == 0) {
            return;
        }
        gorn_path_mover_init_pal(mover);
        if (*(int *)(state + 0x264) != 0) {
            level_append_object(mover, (void *)gorn_path_mover_start_follow_pal, 0, 0);
        }
        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        break;
    case 1: {
        GornPath *path;
        char *owner;
        int index;

        DrawPath(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        owner = (char *)moby_get_motion_data(mover);
        path = (GornPath *)g_path_l15_table[*(int *)(state + 0x268)];
        if (follower_has_reached_target(mover) != 0) {
            index = *(int *)(state + 0x26C);
            *(int *)(state + 0x26C) = index + 1;
            if (index + 1 == path->count - 1) {
                *(unsigned char *)(mover + 0x20) = 3;
            } else {
                float action = path->points[index].action;

                if (action != -1.0f) {
                    if ((FloatToInt(action) & 1) != 0) {
                        *(int *)(state + 0x274) = (FloatToInt(action) >> 1) * 0x32;
                        *(unsigned char *)(mover + 0x20) = 2;
                    }
                }
                follower_set_push_vector(mover, (char *)&path->points[*(int *)(state + 0x26C)]);
                *(int *)(owner + 0x130) = 0x196E6B;
            }
        }
        follower_set_state(mover, 0xC);
        follower_l05_update_pal(mover);
        moby_process_collision_hit(mover, 0, 1, 1);
        break;
    }
    case 2:
        if (math_fast_float_d((int *)(state + 0x274)) != 0) {
            *(unsigned char *)(mover + 0x20) = 1;
        }
        break;
    }
}


extern void gorn_path_mover_init(char *);
extern void moby_init_spawned_sub_object_pal(char *object, int flag);
extern void level_set_object_state_field(int arg0, int value);

/* Initialises a path-mover object: speed, flags, motion-data pointer, and starts it on its first path point. */
void gorn_path_mover_init_pal(char *object) {
    char *moby = object;
    char *vars = *(char **)(moby + 0x68);
    char *motion = (char *)moby_get_motion_data((unsigned char *)object);

    *(int *)(motion + 0x148) = 100;
    moby_init_spawned_sub_object_pal(moby, 1);
    *(float *)(vars + 0x180) = 100.0f;
    *(unsigned char *)(moby + 0x20) = 1;
    *(unsigned char *)(moby + 0x30) = 0xFF;
    *(unsigned short *)(moby + 0x32) = 0x1FF;
    *(unsigned short *)(moby + 0x34) |= 0x100;
    *(float *)(moby + 0x2C) = 0.20000000298023224f;
    *(float *)(vars + 0x278) = 12.0f;
    *(int *)(vars + 0x26C) = 0;
    *(int *)(vars + 0x270) = 0;
    *(int *)(vars + 0x274) = 0;
    *(int *)(motion + 0x154) = (int)(vars + 0x278);
    level_set_object_state_field((int)moby, 0xFFFF);
}


