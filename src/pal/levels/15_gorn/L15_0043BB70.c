#include "include_asm.h"


#include "common.h"

/* func_L15_00435E80 is in L15_00435E80.c. */

void func_PAL_L15_0043BD80(char *a0) {
    char *v1 = *(char **)(a0 + 0x68);

    *(int *)(v1 + 0x270) = 1;
    *(int *)(v1 + 0x274) = 0x190;
    *(char *)(a0 + 0x23) = 0x20;
    *(char *)(a0 + 0x20) = 2;
    *(unsigned short *)(a0 + 0x34) |= 8;
    *(float *)(v1 + 0x180) = 450.0f;
    *(int *)(a0 + 0x98) = 0;
}





extern void DrawPath(char *, int, int, int, float, int);
extern int follower_has_reached_target(char *);
extern void follower_set_push_vector(char *, char *);
extern void follower_set_state(char *, int);
extern void func_PAL_L05_0037E8E0(char *);
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
extern void func_PAL_L15_0043C8B8(char *);
extern void func_PAL_L15_0043C978(void);
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
void func_PAL_L15_0043C6A0(char *object) {
    char *mover = object;
    char *state = *(char **)(mover + 0x68);

    switch (*(unsigned char *)(mover + 0x20)) {
    case 0:
        *(unsigned char *)(mover + 0x30) = 0xFF;
        if (state_get_stored_pointer_value() == 0) {
            return;
        }
        func_PAL_L15_0043C8B8(mover);
        if (*(int *)(state + 0x264) != 0) {
            level_append_object(mover, (void *)func_PAL_L15_0043C978, 0, 0);
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
        func_PAL_L05_0037E8E0(mover);
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

void func_PAL_L15_0043C8B8(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2 = (char *)moby_get_motion_data((unsigned char *)a0);

    *(int *)(s2 + 0x148) = 100;
    moby_init_spawned_sub_object_pal(s0, 1);
    *(float *)(s1 + 0x180) = 100.0f;
    *(unsigned char *)(s0 + 0x20) = 1;
    *(unsigned char *)(s0 + 0x30) = 0xFF;
    *(unsigned short *)(s0 + 0x32) = 0x1FF;
    *(unsigned short *)(s0 + 0x34) |= 0x100;
    *(float *)(s0 + 0x2C) = 0.20000000298023224f;
    *(float *)(s1 + 0x278) = 12.0f;
    *(int *)(s1 + 0x26C) = 0;
    *(int *)(s1 + 0x270) = 0;
    *(int *)(s1 + 0x274) = 0;
    *(int *)(s2 + 0x154) = (int)(s1 + 0x278);
    level_set_object_state_field((int)s0, 0xFFFF);
}


