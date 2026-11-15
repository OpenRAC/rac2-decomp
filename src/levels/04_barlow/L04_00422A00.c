#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef float f32;


extern u8 D_L04_001395C7;
extern u8 D_L04_002CA518;

extern void func_2CC1F0(void *a0);
extern void func_30EA08(void *a0);
extern void func_33B9B0(void *a0, s32 a1, s32 a2);
extern void func_3317E8(void *a0);
extern void func_340BB8(void *a0, void *a1);
extern void func_345328(void *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern void func_348708(void *a0, void *a1, s32 a2, s32 a3, f32 f12);
extern int func_34C4C8(void);
extern void *func_33E6B0(void *a0, s32 a1, s32 a2);
extern void func_40A090(int a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, u8 *a5);

/* func_L04_00456628: the sda incomplete arrays keep retail's absolute macro loads
   (lui into the destination register); D_001A7B00 is the inventory have-flag table. */
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_001395B8[];
extern s32 D_L04_001B2008[] __attribute__((sda));
extern u8 *D_L04_001B25CC[] __attribute__((sda));
extern u8 g_hero_position[];
extern void func_2DFC18(void *a0, void *a1, s32 a2, s32 a3);
extern s32 func_342228(void *a0, void *a1);

extern void moby_mark_spawned(void *a0);
extern int flag_is_third_pending_set(u8 *a0);
extern void moby_mark_table_entry_flagged(u32 a0);
extern s32 req_push_queue(u8 *a0, s32 a1);
extern s32 req_launch_queued(void *a0);
extern void game_set_slowdown_factor(void);
extern float math_spring_float_to_goal(float *a0, float *a1, float f12, float f13, float f14, float f15);
extern void PlayMobySound(s32 a0, s32 a1, char *a2);

extern u8 D_0019B2E8[];
extern int g_current_map_index __attribute__((sda));
extern int g_moby_l04_pool __attribute__((sda));
extern u8 D_L04_001BF880[];

typedef struct { u8 pad_0[0x20]; u8 flags; } FlareMoby;
typedef struct {
    FlareMoby *moby; s32 state; f32 intensity; s32 pad_c;
    s16 alpha[16]; s16 tex[16]; s32 color[16]; f32 dist[16]; f32 scale[16];
} LensFlare;
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern LensFlare g_lens_flare;
extern u8 D_L04_001B9680[];
extern int D_L04_001B0D08;
extern ScreenExtent g_screen_width __attribute__((sda));
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern void gfx_project_world_point_to_screen(f32 *, void *);
extern long long GetEffectTextureDescriptor(int);
extern f32 math_fabs(f32);
extern int FloatToInt(f32);
extern void VU1_addGSregister(int, long long);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, long long, long long);

/* Defined in L04_00422D40-qcopy.c. */
/* Projects the flare object to the screen and draws its 14 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare). The base size is read through a pointer: retail
   rematerializes its address inside the loop. */
void gfx_l04_draw_lens_flare(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    f32 scr[4], ctr[4], d[4], off[4], at[4];
    f32 dist, fade, fx, fy, half;
    int i, size, rgba, x, y;
    long long tex;
    int *baseSize;

    if (g_lens_flare.state != 1 || (g_lens_flare.moby->flags & 0x80)) {
        g_lens_flare.state = 0;
        return;
    }
    if (g_lens_flare.intensity <= 0.0f)
        return;
    dist = fast_vec_dist(D_L04_001B9680, vars + 0x30);
    ctr[0] = IntToFloat(g_screen_width.half_width);
    ctr[1] = IntToFloat(g_screen_width.half_height);
    baseSize = &D_L04_001B0D08;
    gfx_project_world_point_to_screen(scr, vars + 0x30);
    scr[0] = (scr[0] - IntToFloat(g_screen_width.left)) * 0.0625f;
    scr[1] = (scr[1] - IntToFloat(g_screen_width.top)) * 0.0625f;
    d[0] = ctr[0] - scr[0];
    d[1] = ctr[1] - scr[1];
    for (i = 0; i < 14; i++) {
        tex = GetEffectTextureDescriptor(g_lens_flare.tex[i] + 0x49);
        off[0] = d[0] * g_lens_flare.dist[i];
        off[1] = d[1] * g_lens_flare.dist[i];
        at[0] = ctr[0] + off[0];
        at[1] = ctr[1] + off[1];
        fade = dist - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        fx = math_fabs(d[0]) / ctr[0] * -5.0f + 5.5f;
        if (fx > 1.0f)
            fx = 1.0f;
        else if (fx < 0.0f)
            fx = 0.0f;
        fy = math_fabs(d[1]) / ctr[1] * -5.0f + 5.5f;
        if (fy > 1.0f)
            fy = 1.0f;
        else if (fy < 0.0f)
            fy = 0.0f;
        fade *= fx * fy * g_lens_flare.intensity;
        rgba = (FloatToInt(fade * g_lens_flare.alpha[i]) << 24) | (g_lens_flare.color[i] & 0xFFFFFF);
        size = FloatToInt(*baseSize * g_lens_flare.scale[i]);
        VU1_addGSregister(0x42, 0x8000000048LL);
        half = size >> 1;
        x = FloatToInt(at[0] - half);
        y = FloatToInt(at[1] - half);
        DrawTexturedQuad(x, y, size, size, 0, 0, 0x40, 0x40, rgba, tex);
    }
    g_lens_flare.intensity = 0.0f;
}
/* func_L04_00423258 is in L04_00423258-g8.c. */
/* Counts the object's state up, easing its timer down while it is over the
   limit, and hands the level's recorder the object's channel when it runs out. */
void barlow_lift_update(u8 *object) {
    u32 *vars = *(u32 **)(object + 0x68);

    if (object[0x20] == 0)
        object[0x20] = 1;
    if (object[0x20] == 2) {
        f32 height = *(f32 *)(object + 0x18);
        if (height >= 30.0f)
            *(f32 *)(object + 0x18) = height - 0.28333336114883423f;
        if (*(f32 *)(object + 0x18) < 30.0f)
            object[0x20] = 4;
    }
    if (object[0x20] == 3) {
        math_spring_float_to_goal((f32 *)(object + 0x18), (f32 *)vars, 55.0f,
                      0.008333333767950535f, 0.013888888992369175f,
                      0.45000001788139343f);
        if (55.0f <= *(f32 *)(object + 0x18)) {
            PlayMobySound(0, 0, (char *)object);
            vars[1] = 0;
            object[0x20] = 1;
        }
    }
}
struct BarlowEntry { u8 bytes[256]; };
extern u8 g_hero_position[];
extern u16 *g_moby_l04_group_lists[];
extern u8 D_L04_001B1218[];
extern u8 D_L04_001B1230[];
extern int IsPointInCuboid(void *, int);
extern int moby_count_group_not_in_state(int, int);
extern void STUB_printf(const char *, ...);

/* Waits for a trigger, then switches on the linked groups of objects, and switches them back off when the trigger ends. */
void linked_groups_toggle(u8 *object) {
    int *data = *(int **)(object + 0x68);
    int i;
    if (object[0x20] == 0) {
        if (IsPointInCuboid(g_hero_position, data[4]))
            object[0x20] = 1;
    }
    if (object[0x20] == 1) {
        u16 *ids;
        u8 *entry;
        struct BarlowEntry *base;
        for (i = 0; i < 4; i++) {
            if (g_moby_l04_group_lists[*(int *)((u32)data + (i << 2))] && moby_count_group_not_in_state(*(int *)((u32)data + (i << 2)), -1) >= 2) {
                base = (struct BarlowEntry *)g_moby_l04_pool;
                ids = g_moby_l04_group_lists[*(int *)((u32)data + (i << 2))];
                do {
                    entry = base[*ids & 0x7FFF].bytes;
                    *(u16 *)(entry + 0x34) |= 0x43;
                    *(int *)(entry + 0x98) = 0;
                } while ((s16)*ids++ >= 0);
            }
        }
        STUB_printf(D_L04_001B1218);
        object[0x20] = 2;
    }
    if (object[0x20] == 2) {
        if (!IsPointInCuboid(g_hero_position, data[4]))
            object[0x20] = 3;
    }
    if (object[0x20] == 3) {
        u16 *ids;
        u8 *entry;
        struct BarlowEntry *base;
        for (i = 0; i < 4; i++) {
            if (g_moby_l04_group_lists[*(int *)((u32)data + (i << 2))] && moby_count_group_not_in_state(*(int *)((u32)data + (i << 2)), -1) >= 2) {
                base = (struct BarlowEntry *)g_moby_l04_pool;
                ids = g_moby_l04_group_lists[*(int *)((u32)data + (i << 2))];
                do {
                    entry = base[*ids & 0x7FFF].bytes;
                    *(u16 *)(entry + 0x34) &= ~0x41;
                    *(int *)(entry + 0x98) = *(int *)(*(u8 **)(entry + 0x24) + 0x10);
                    *(u16 *)(entry + 0x34) &= ~2;
                } while ((s16)*ids++ >= 0);
            }
        }
        STUB_printf(D_L04_001B1230);
        moby_mark_spawned(object);
    }
}

/* func_L04_00439870 is defined in L04_00422A00-g8.c (this unit's -G8 profile gives the
   retail's address forms). */
extern void func_40A090(int a0, u8 *a1, u8 *a2, u8 *a3, u8 *a4, u8 *a5);

extern u8 D_L04_001B12B0[] __attribute__((sda));
extern u8 D_L04_001B12E8[] __attribute__((sda));
extern u8 D_L04_001B1300[] __attribute__((sda));
extern u8 D_L04_001B1330[] __attribute__((sda));
extern u8 D_L04_001B1348[] __attribute__((sda));
extern u8 D_L04_001B3280[] __attribute__((sda));
extern u8 D_L04_001B32B0[] __attribute__((sda));
extern u8 D_L04_001B32E0[] __attribute__((sda));
extern u8 D_L04_001B3300[] __attribute__((sda));
extern u8 D_L04_001B3320[] __attribute__((sda));
extern u8 D_L04_001B3330[] __attribute__((sda));
extern u8 D_L04_001B3360[] __attribute__((sda));
extern u8 D_L04_001B3378[] __attribute__((sda));
extern u8 D_L04_001B33A0[] __attribute__((sda));
extern u8 D_L04_001B33B0[] __attribute__((sda));
extern u8 D_L04_001B33B8[] __attribute__((sda));
extern u8 D_L04_001B33D8[] __attribute__((sda));
extern u8 D_L04_001B33E8[] __attribute__((sda));
extern u8 D_L04_001B3418[] __attribute__((sda));
extern u8 D_L04_001B3430[] __attribute__((sda));
extern u8 D_L04_001B3458[] __attribute__((sda));
extern u8 D_L04_001B3468[] __attribute__((sda));
extern u8 D_L04_001B3470[] __attribute__((sda));
extern u8 D_L04_001B3474[] __attribute__((sda));
extern u8 D_L04_001B3478[] __attribute__((sda));
extern u8 D_L04_001B347C[] __attribute__((sda));
extern u8 D_L04_001B3480[] __attribute__((sda));
extern u8 D_L04_001B3484[] __attribute__((sda));
extern u8 D_L04_001B3488[] __attribute__((sda));
extern u8 D_L04_0026D370[];
extern u8 D_L04_0026D3E0[];
extern u8 D_L04_0026D490[];
extern u8 D_L04_0026D4F0[];
extern u8 D_L04_002CA3E0[];
extern u8 D_L04_002CA438[];

extern void path_measure_segments(int, void *, void *, void *, void *, void *);

/* Sets up the seven animation walk paths used by the Barlow cutscene. */
void barlow_init_animation_paths(void) {
    path_measure_segments(7, D_L04_001B12B0, D_L04_0026D370, D_L04_001B3300, D_L04_001B33B8, D_L04_001B3470);
    path_measure_segments(3, D_L04_001B12E8, D_L04_001B3280, D_L04_001B3320, D_L04_001B33D8, D_L04_001B3474);
    {
        u8 *data = D_L04_002CA3E0;
        path_measure_segments(11, data, D_L04_0026D3E0, D_L04_001B3330, D_L04_001B33E8, D_L04_001B3478);
    }
    path_measure_segments(6, D_L04_001B1300, D_L04_0026D490, D_L04_001B3360, D_L04_001B3418, D_L04_001B347C);
    path_measure_segments(9, D_L04_002CA438, D_L04_0026D4F0, D_L04_001B3378, D_L04_001B3430, D_L04_001B3480);
    path_measure_segments(3, D_L04_001B1330, D_L04_001B32B0, D_L04_001B33A0, D_L04_001B3458, D_L04_001B3484);
    path_measure_segments(2, D_L04_001B1348, D_L04_001B32E0, D_L04_001B33B0, D_L04_001B3468, D_L04_001B3488);
}



/* On its first update waits for a go signal, then sets a level flag and moves to the next state. */
void barlow_start_trigger_update(u8 *object) {
    if (object[0x20] != 0)
        return;
    if (func_34C4C8() != 0) {
        func_2CC1F0(&D_L04_002CA518);
        D_L04_001395C7 = 1;
        func_33B9B0(object, 1, -1);
    }
}
/* func_L04_0044AAC8 is defined in L04_00422A00-g8.c (it reads small data through $gp). */
/* func_L04_0044BC90 is defined in L04_0044BC90-g8.c. */

/* Defined in L04_0044BC90-g8.c. */
/* func_L04_0044C598 is in L04_0044C598-g8.c. */
/* func_L04_0044D0C0 is in L04_0044D0C0-g8.c. */
/* func_L04_0044D428 is in L04_0044D428-g8.c. */
extern void func_30E9D8(void *a0);
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);

/* Counts the object up, turns it towards the hero and keeps the turn inside
   a sixty degree limit, then hands the result to the frame helpers. */
void enemy_turn_toward_hero(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *target;
    f32 angle, negLimit, deltaX, deltaY, limit;

    func_340BB8(object, vars + 0x50);
    func_30E9D8(vars + 0x2FC);
    func_30EA08(vars + 0x302);
    if (*(u16 *)(object + 0x96) <= 0xFFFE)
        *(u16 *)(object + 0x96) = *(u16 *)(object + 0x96) + 1;
    if (object[0x95] == 2) {
        target = *(u8 **)(vars + 0x250);
        deltaX = *(f32 *)(target + 0x10) - *(f32 *)(object + 0x10);
        deltaY = *(f32 *)(target + 0x14) - *(f32 *)(object + 0x14);
        limit = 1.047197699546814f;
        angle = func_30F468(deltaX, deltaY);
        angle = func_30FE88(angle, *(f32 *)(object + 0xF8));
        if (limit < angle) {
            angle = limit;
        } else {
            negLimit = -limit;
            if (angle < negLimit)
                angle = negLimit;
        }
        if (*(u16 *)(object + 0x34) & 0x8000)
            angle = -angle;
        angle = func_30FE40(angle, *(f32 *)(vars + 0x2C8));
        *(f32 *)(vars + 0x2C8) = angle;
        if (limit < angle) {
            *(f32 *)(vars + 0x2C8) = limit;
        } else {
            negLimit = -limit;
            if (angle < negLimit)
                *(f32 *)(vars + 0x2C8) = negLimit;
        }
    }
    func_348708(object, vars + 0x260, 1, 1, 2.5f);
}
/* Defined in L04_0044D860-g8.c. */

/* subtracts the sub-structure's field from the owner's timer and reports it */
int linked_part_consume_timer(char *object) {
    char *vars = *(char **)(object + 0x68);
    char *part = func_33E6B0(*(char **)(vars + 0x290), 0x10000, 0);

    if (part != 0) {
        *(f32 *)(vars + 0x20) -= *(f32 *)(part + 0x2C);
        return 1;
    }
    return 0;
}

/* Frees up to three linked child objects and clears the links to them. */
void linked_children_free(char *object) {
    char *vars = *(char **)(object + 0x68);
    void *child;

    child = *(void **)(vars + 0x2AC);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x2AC) = 0;
    }
    child = *(void **)(vars + 0x288);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x288) = 0;
    }
    child = *(void **)(vars + 0x290);
    if (child != 0) {
        func_3317E8(child);
        *(void **)(vars + 0x290) = 0;
    }
}
/* Defined in L04_004502D0-g8.c. */
extern float FastVecLength(void *);
extern void FastVecSub(void *, void *, void *);
extern void ComputeRegionRouteHeading(void *, void *, void *, void *, int, void *, void *, f32, f32);
extern void math_approach_target_with_direction_mode(void *, f32, f32, f32, f32, void *, int);
extern f32 FastDiffRots(f32, f32);
extern void math_step_value_toward_target(void *, void *, f32, f32, f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern int moby_move_over_ground(void *, void *, void *, f32, f32, f32, f32, int);

/* Walks the object toward a target while turning to face it. Returns 1 when it has arrived and finished turning, or when it has been stuck for too long. */
int enemy_walk_toward_target(u8 *object, void *target, f32 desiredHeading, f32 speed, f32 stopDistance, f32 margin) {
    f32 delta[4], displacement[4], destination[4];
    f32 angle, frameSpeed = 0.0f;
    u8 *data = *(u8 **)(object + 0x68);
    int done = 0;
    f32 distance, acceleration;
    FastVecSub(delta, target, object + 0x10);
    delta[2] = 0.0f;
    distance = FastVecLength(delta);
    acceleration = speed * 0.0008333333535119891f;
    if (stopDistance < distance) {
        int collision = *(int *)(data + 0x540);
        angle = 0.0f;
        ComputeRegionRouteHeading(object + 0x10, target, &angle, data + 0x340, collision, data + 0x550, data + 0x554, margin, 0.4f);
        math_approach_target_with_direction_mode(object + 0xF8, angle, 0.006981317885220051f, 0.0034906589426100254f, 0.20943954586982727f, data + 0x28C, 0);
        if (FastDiffRots(*(f32 *)(object + 0xF8), angle) < 0.523598849773407f) {
            math_step_value_toward_target(&frameSpeed, data + 0x558, distance, acceleration, acceleration, speed * 0.01666666753590107f);
        } else {
            *(f32 *)(data + 0x558) = 0.0f;
        }
    } else {
        math_approach_target_with_direction_mode(object + 0xF8, desiredHeading, 0.006981317885220051f, 0.2f, 0.20943954586982727f, data + 0x28C, 0);
        ApproachValue((f32 *)(data + 0x558), 0.0f, acceleration);
        if (*(f32 *)(data + 0x558) == 0.0f && FastDiffRots(*(f32 *)(object + 0xF8), desiredHeading) < 0.0872664749622345f) {
            *(f32 *)(data + 0x28C) = 0.0f;
            done = 1;
        }
    }
    vec_scale_to_length(displacement, object + 0xC0, *(f32 *)(data + 0x558));
    FastVecAdd(destination, displacement, object + 0x10);
    if (!moby_move_over_ground(object, object + 0x10, destination, 0.75f, 0.75f, 0.4f, 0.523598849773407f, 0))
        *(int *)(data + 0x55C) += 1;
    if (*(int *)(data + 0x55C) >= 30) {
        *(int *)(data + 0x55C) = 0;
        done = 1;
    }
    return done;
}


/* Counts down the object's timers, ages the object by one tick and updates its animation blending. */
void enemy_tick_timers_blend(char *object) {
    char *vars = *(char **)(object + 0x68);
    u16 age;

    func_340BB8(object, vars + 0x50);
    func_30EA08(vars + 0x270);
    func_30EA08(vars + 0x272);
    func_30EA08(vars + 0x26);
    age = *(u16 *)(object + 0x96);
    if (age <= 0xFFFE) {
        *(u16 *)(object + 0x96) = age + 1;
    }
    vars += 0x2C0;
    func_345328(object, vars, 4, 0.03f, 0.3f);
    func_348708(object, vars, 4, 1, 2.5f);
}
/* Starts the object's encounter state and, once it is running, hands the level's
   camera table the object's slot and asks the frame helpers to update it. */
void barlow_encounter_trigger_update(u8 *object) {
    u32 *links = *(u32 **)(object + 0x68);

    if (object[0x20] == 0) {
        if (D_0019B2E8[object[0xB0] + g_current_map_index * 16] & 0x80) {
            moby_mark_spawned(object);
            return;
        }
        object[0x20] = 1;
    }
    if (object[0x20] == 1) {
        if (flag_is_third_pending_set((u8 *)(g_moby_l04_pool + (*links << 8)))) {
            moby_mark_table_entry_flagged(object[0xB0]);
            req_push_queue(D_L04_001BF880, 0x38);
            req_launch_queued(D_L04_001BF880);
            game_set_slowdown_factor();
            moby_mark_spawned(object);
        }
    }
}
/* On the first update: with inventory item 0x1F owned, the byte at D_001395B8+0x12
   clear and the level counter D_L04_001B2008 below 5, passes the +0x30/+0x70 vectors
   of the level record the object names to func_2DFC18 (RAC1's Hero_ResetToPosition
   call shape); with the item owned and that byte set, hands the object to
   func_3317E8. Later, once func_342228 accepts the hero position (D_00189EA0) for
   the object's volume and the item is still owned, sets the byte and does the same. */
void barlow_item_pickup_trigger_update(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *record;
    if (object[0x20] == 0) {
        if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] == 0 && D_L04_001B2008[0] < 5) {
            record = D_L04_001B25CC[0] + (*(s32 *)(vars + 4) << 7);
            func_2DFC18(record + 0x30, record + 0x70, 0, 1);
        } else if (D_001A7B00[0x1F] != 0 && D_001395B8[0x12] != 0) {
            func_3317E8(object);
            return;
        } else {
            object[0x20] = 1;
        }
        object[0x30] = 0xFF;
    }
    if (object[0x20] == 1) {
        if (func_342228(g_hero_position, *(void **)vars) != 0) {
            if (D_001A7B00[0x1F] != 0) {
                D_001395B8[0x12] = 1;
                func_3317E8(object);
            }
        }
    }
}
