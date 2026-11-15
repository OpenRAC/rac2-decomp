#include "include_asm.h"
#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));

extern void moby_mark_spawned(void *);

extern void moby_transform_joint_to_world(void *, int, void *);

extern void *part_find_owned_effect_slot(void *, int, int);

extern void QueueMobyImpact(void *, void *);

typedef struct {
    TI128 f00;
    u32 f10;
    u32 f14;
    u8 f18;
    u8 f19;
    u16 f1A;
    f32 f1C;
    u32 f20;
} L01_003A6350_Params;

typedef struct {
    u8 pad[0x1FB0];
    f32 f1FB0;
    f32 f1FB4;
} D00189E20_View;

extern D00189E20_View g_hero_state;

extern void math_fast_float_d();

/* func_L01_003835D8 is defined in L01_003835D8-match.c. */

/* func_L01_003839F0 is defined in L01_003839F0.c. */

/* func_L01_003A5BB8 is defined in L01_003835D8-g8.c. */

/* func_L01_003A6028 is defined in L01_003A6028-g8.c. */

/* func_L01_003A6280 is defined in L01_003A6280-helper-g8.c. */

/* Small helper object that follows its parent. If something hits it, it passes the hit on to the parent. It removes itself when the parent is gone. */
void hit_relay_helper_update(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *parent = *(u8 **)(vars + 0x50);
    L01_003A6350_Params hit;
    void *result;

    if (parent == 0 || *(s16 *)(parent + 0xAA) != *(s32 *)(vars + 0x54) ||
        parent[0x20] == 0xFE || parent[0x20] == 0xFD) {
        moby_mark_spawned(object);
        return;
    }
    {
        if (*(s32 *)(vars + 0x5C) != -1) {
            moby_transform_joint_to_world(*(u32 *)(vars + 0x50), *(s32 *)(vars + 0x5C), object + 0x10);
        }
        result = part_find_owned_effect_slot(object, -1, 0);
        if (result != 0) {
            qcopy(&hit.f00, (u8 *)result + 0x10);
            hit.f10 = *(u32 *)((u8 *)result + 0x20);
            hit.f14 = *(u32 *)((u8 *)result + 0x24);
            hit.f18 = ((u8 *)result)[0x28];
            hit.f19 = ((u8 *)result)[0x29];
            hit.f1A = *(u16 *)((u8 *)result + 0x2A);
            hit.f1C = *(f32 *)((u8 *)result + 0x2C) * *(f32 *)(vars + 0x58);
            hit.f20 = *(u32 *)((u8 *)result + 0x30);
            QueueMobyImpact(*(u32 *)(vars + 0x50), &hit);
        }
        object[0xA8] = 0xFF;
    }
}

/* Reads how far the player is tilting and gives two numbers, each kept between -1 and 1. */
void hero_get_clamped_stick_tilt(float *out_x, float *out_y) {
    *out_x = -g_hero_state.f1FB0;
    *out_y = -g_hero_state.f1FB4;
    if (*out_x > 1.0f)
        *out_x = 1.0f;
    else if (*out_x < -1.0f)
        *out_x = -1.0f;
    if (*out_y > 1.0f)
        *out_y = 1.0f;
    else if (*out_y < -1.0f)
        *out_y = -1.0f;
}



/* func_L01_003B1F08 lives in L01_003B1F08.c. */

/* func_L01_003B4200 lives in L01_003B4200.c: its grouped copies and
   global-address scheduling need a per-file profile. */

/* func_L01_003B4480 lives in L01_003B4480.c: its 128-bit copy needs the grouped
   copy profile, which is a per-file flag. */

extern void memset(void *, int, int);

extern int coll_process_hit(float, char *, int, char *, int);

extern void *D_L01_001C3980[];

/* Finds up to 16 nearby creatures of one kind, marks them and remembers them in a list. */
void swamp_beast_collect_nearby(void *object, void **list, int *found) {
    int i;
    int hit_count;
    void *other;

    memset(list, 0, 4);
    *found = 0;
    hit_count = coll_process_hit(3.5f, (char *)object + 0x10, 1, (char *)object, 0);
    if (hit_count <= 0)
        return;
    for (i = 0; i < hit_count; i++) {
        other = D_L01_001C3980[i];
        if (other == 0)
            continue;
        if (*(s16 *)((u8 *)other + 0xAA) != 0xA26 /* moby class 2598 */)
            continue;
        *(u32 *)((u8 *)other + 0x9C) = 1;
        *(u8 *)((u8 *)D_L01_001C3980[i] + 0xBC) = 1;
        list[*found] = D_L01_001C3980[i];
        *found = *found + 1;
        if (*found >= 16)
            break;
    }
}

/* Removes the mark from every creature in the list made by the function above. */
void swamp_beast_clear_collected_marks(char **list, int *count) {
    int i;

    if (*count <= 0)
        return;
    i = 0;
    do {
        *(int *)(list[i] + 0x9C) = 0;
        i++;
    } while (i < *count);
}


/* func_L01_003B49D8 and func_L01_003B4AD0 live in L01_003B49D8.c: their clamp needs
   -ffast-math (the retail's min.s), which is a per-file flag. */

/* Gives back this creature's place in its group, if it had taken one. */
void swamp_beast_release_group_slot(u8 *object) {
    char *vars = *(char **)(object + 0x68);

    if (object[0x21] != 0xFF) {
        if (*(int *)(vars + 0x340) != 0) {
            math_fast_float_d(*(int **)(vars + 0x33C));
        }
    }
    *(int *)(vars + 0x340) = 0;
}

/* Takes a place in the creature's group if it has none yet, and counts it. Always returns 1. */
int swamp_beast_claim_group_slot(u8 *object) {
    char *vars = *(char **)(object + 0x68);
    int result = 1;

    if (object[0x21] != 0xFF) {
        if (*(int *)(vars + 0x340) == 0) {
            int *group_count = *(int **)(vars + 0x33C);
            *group_count = *group_count + 1;
        }
    }
    *(int *)(vars + 0x340) = result;
    return result;
}

/* func_L01_003B4C58 is defined in L01_003B4C58-g8.c. */

extern float coll_probe_ground_height_below(void *, int, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int math_random_int_range(int, int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern void part_l01_spawn_glow(void *, int, int, float, float, int);
extern void value_set_and_smooth(u8 *, u8 *, s32, s32, f32);

/* Throws a number of small particles around the object at the given height. A height of -1 means use the height of what it stands on. */
void part_spawn_surface_particles(char *object, int count, float height)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, left;

    if (height == -1.0f) {
        state = *(char **)(object + 0x68);
        if (*(int *)(state + 0x1E8) != -1 || *(int *)(state + 0x198) != 0)
            return;
        height = *(float *)(state + 0x1A0) + 0.015f;
    }
    if (height == 0.0f)
        height = coll_probe_ground_height_below(object + 0x10, 0, 0.5f) + 0.025f;
    for (left = 0; left < count; left++) {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.8f);
        first = math_random_float_range(0.0f, 1.5f);
        second = math_random_float_range(1.5f, 5.7f);
        life = math_random_int_range(100, 180);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, object + 0x10);
        position[2] = height;
        part_l01_spawn_glow(position, 0x38002028, 0x2020, first, second, life);
    }
}

/* Clears the measured 0x350 word when it is set, then draws the new duration
   if the old one is still short. */
/* Runs the creature's timers each frame and picks a new random wait when the old one is short. */
void swamp_beast_update_timers(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u16 flags;

    if (*(u32 *)(vars + 0x350) != 0) {
        *(u32 *)(vars + 0x350) = 0;
        if (*(s32 *)(vars + 0x330) < 200) {
            *(u32 *)(vars + 0x330) = math_random_int_range(300, 360);
        }
    }
    if (*(u32 *)(vars + 0x244) != 1)
        math_fast_float_d(vars + 0x330);
    flags = *(u16 *)(object + 0x96);
    if (flags < 65534)
        *(u16 *)(object + 0x96) = flags + 1;
    math_fast_float_d(vars + 0x32C);
    math_fast_float_d(vars + 0x334);
    value_set_and_smooth(object, vars + 0x250, 6, 1, 4.0f);
}

/* func_L01_003B53C8 is defined in L01_003835D8-g8.c. */

/* func_L01_003B57A8 uses the SDA pointer to the position table. */
extern u8 *D_L01_001B264C __attribute__((sda));
extern char g_hero_position[];
extern float vec_distance_xy(void *, void *);

/* Of the (up to four) positions whose indices are listed at the state's +0x310, copies the one
   func_00282E80 rates highest against D_00189EA0 to OUT (its rating at +0xC), then stores
   func_002A89A8's value for it at +0x8. A position is the 16-byte record at +0x30 of the
   index's 0x80-byte entry in the D_L01_001B264C table. */
void swamp_beast_find_best_patrol_position(u8 *object, u8 *result) {
    s32 *index_list = (s32 *)(*(u8 **)(object + 0x68) + 0x310);
    u8 pos[16] __attribute__((aligned(16)));
    s32 count = 4;
    f32 rating;

    *(f32 *)(result + 0xC) = 0.0f;
    while (--count >= 0) {
        if (*index_list != -1) {
            qcopy(pos, D_L01_001B264C + *index_list * 0x80 + 0x30);
            rating = vec_distance_xy(pos, g_hero_position);
            if (*(f32 *)(result + 0xC) < rating) {
                qcopy(result, pos);
                *(f32 *)(result + 0xC) = rating;
            }
        }
        index_list++;
    }
    *(f32 *)(result + 0x8) = coll_probe_ground_height_below(result, 0, 10.0f);
}

/* func_L01_003B5878 is defined in L01_003B5878-g8.c. */

/* func_L01_003B9F30 is defined in L01_003B9F30-g16.c. */

/* func_L01_003BAFB0 lives in the -g8 sibling file (it reads a float through $gp). */

/* func_L01_003BAFB8 is defined in L01_003BAFB8-g8.c. */
