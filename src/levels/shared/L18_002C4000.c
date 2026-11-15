#include "include_asm.h"
#include "common.h"

extern void *memset(void *, int, unsigned int);
extern float g_hero_position[4];
extern float vec_distance_squared_xy(void *, void *);
extern int moby_is_state_two(unsigned char *);
extern int moby_enter_hit_state(unsigned char *, int);

/* Frozen Batch A A18-void-store-16; acknowledged claim 4cf4f8b91176606a7af1fd853f7ccd89fa63964199d0883686e46fb6a47255a8. */
typedef unsigned char BatchA_A18_u8;

typedef int BatchA_A18_s32;

typedef short BatchA_A18_BatchAs16;

/* Frozen Batch A A09-cond-select-36; acknowledged claim 3dadb64036892dfb357f8b3f0f7b47fc608b60613dcd8c823ef8df1bc26f7e5b. */
typedef unsigned char BatchA_A09_u8;

typedef int BatchA_A09_s32;

extern void func_00335668(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);


extern BatchA_A18_u8 D_0018C0D4;

/* func_L18_002D0C00 */
extern s32 D_L18_001AFBB0 MACRO_ADDR;
extern u8 g_hero_state[];
typedef struct {
    u8 reserved000[0x80];
    float position[4];
    u8 reserved090[0x1D00];
    float positionHistory[32][4];
    u8 reserved1F90[0x3AC];
    float headingHistory[32];
    s32 headingIndex, headingCount, positionIndex, positionCount;
} HeroHistory;
/* Partial input record: only the observed axes and button words are modeled. */
typedef struct {
    u8 reserved000[0x108];
    float horizontal, vertical;
    u8 reserved110[0x90];
    s32 held;
    u8 reserved1A4[12];
    s32 pressed;
} InputRecordPrefix;
extern InputRecordPrefix g_pad_state;
extern void hero_reset_speeds_and_vectors(void);
extern s32 FastDecTimer(void *);
extern s32 hero_get_movement_mode(void);
extern float hero_get_stick_magnitude(void);
extern float vec_length_xy(void *);
extern void hero_l18_update_state_machine(void);
extern void euler_to_matrix(void *, void *);
extern void set_identity_matrix(void *);
extern void matrix_from_basis_rows(void *, void *);
extern void hero_l18_update_speed_targets(void);
extern void hero_probe_ground_and_ledge(void);
extern void hero_update_timers_reach(void);

/* func_L18_002D1998 */
/* Partial probe-collision record: only the hit object, hit count and surface normal are modeled. */
typedef struct { u8 prefix[0x18]; s32 object; s32 count; u8 gap[0x20]; float normal[4]; } MotionCollision;
extern MotionCollision D_L18_001BFC00;
extern float cam_get_view_space_vector_length(void *);
/* func_L00_002D36E0(float *out, s32 flag, float x, float y, float z) elsewhere: this typed
   interleaving keeps both EE argument banks unchanged and gives retail's argument setup order. */
extern void hero_build_relative_point(float *, float, float, float, s32);
extern void vec_scale_to_length(void *, void *, float);
extern void cam_set_view_space_height(float *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 GetCollHitMaterial(void);
extern float cam_get_view_space_angle(void *);
extern float FastVecDot(void *, void *);

/* func_L18_002C4000 is defined in L18_002C4000-hero.c. */

/* func_L18_002C41F0 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

/* func_L18_002CFD68 is defined in L18_002CFD68-qcopy.c. */

/* func_L18_002CFF48 is defined in L18_002CFD68-qcopy.c. */

/* Runs once per frame for the hero: reads the controller, saves the hero position and heading history, and updates the hero movement. */
void hero_update_frame_input(void)
{
    u8 *base;
    u8 *snapshot;
    u8 *positions;
    s32 index;
    s32 active = D_L18_001AFBB0;
    if (active) {
        hero_reset_speeds_and_vectors();
        return;
    }
    snapshot = g_hero_state + 0x2030;
    qcopy(snapshot, snapshot - 0x1FB0);
    if (g_pad_state.held & 3) {
        u8 *hero = snapshot - 0x2030;
        if (*(s16 *)(hero + 0x1454) < 1) *(s16 *)(hero + 0x1454) = 1;
    } else FastDecTimer(snapshot - 0xBDC);
    base = g_hero_state;
    if (*(s32 *)(base + 0x2294) == 16) *(s16 *)(base + 0x1454) = 0;
    base[0x22C3] = hero_get_movement_mode();
    *(float *)(base + 0x1FB0) = g_pad_state.horizontal;
    *(float *)(base + 0x1FB4) = g_pad_state.vertical;
    *(s32 *)(base + 0x270) = 0;
    *(float *)(base + 0x24BC) = hero_get_stick_magnitude();
    if (vec_length_xy(base + 0x1FB0) < 0.25f) {
        /* horizontal and vertical start as the left and down bits. */
        s32 right = (g_pad_state.pressed >> 13) & 1;
        s32 horizontal = (g_pad_state.pressed >> 15) & 1;
        s32 up = (g_pad_state.pressed >> 14) & 1;
        s32 vertical = (g_pad_state.pressed >> 12) & 1;
        horizontal = right - horizontal;
        vertical = up - vertical;
        *(float *)(base + 0x1FB0) = (float)horizontal;
        *(float *)(base + 0x1FB4) = (float)vertical;
    }
    *(float *)(base + 0x24B8) = hero_get_stick_magnitude();
    hero_l18_update_state_machine();
    ((HeroHistory *)base)->headingHistory[((HeroHistory *)base)->headingIndex] = *(float *)(base + 0x98);
    *(s32 *)(base + 0x23BC) = (*(s32 *)(base + 0x23BC) + 1) % 32;
    if (++*(s32 *)(base + 0x23C0) > 32) *(s32 *)(base + 0x23C0) = 32;
    index = *(s32 *)(base + 0x23C4);
    positions = base + 0x1D90;
    qcopy_nc(positions + index * 16, (base + 0x80));
    *(s32 *)(base + 0x23C4) = (index + 1) % 32;
    if (++*(s32 *)(base + 0x23C8) > 32) *(s32 *)(base + 0x23C8) = 32;
    euler_to_matrix(base, base + 0x90);
    set_identity_matrix(base + 0x40);
    matrix_from_basis_rows(base + 0x40, base);
    hero_l18_update_speed_targets();
    hero_probe_ground_and_ledge();
    hero_update_timers_reach();
}

void ClipHeroVelocityAtWall(s32 force)
{
    float start[4], end[4], lowerStart[4], lowerEnd[4];
    float height, reach, angle, dot;
    s32 material;
    if (cam_get_view_space_vector_length(g_hero_state + 0xF0) < 0.0016666668f) return;
    /* Each block forms its own hero pointer; retail keeps only the %hi part across calls. */
    {
        u8 *hero = g_hero_state;
        height = 0.37f;
        reach = 0.5f;
        if ((u32)(*(s32 *)(hero + 0x229C) - 17) < 2) {
            height = 0.0f;
            reach = 0.7f;
        } else if (hero[0x22B4] == 4) height = 0.35f;
    }
    hero_build_relative_point(start, 0.0f, 0.0f, height, 1);
    hero_build_relative_point(lowerStart, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || vec_length_xy(g_hero_state + 0xF0) < 0.01f) {
        vec_scale_to_length(end, g_hero_state, reach);
        vec_scale_to_length(lowerEnd, g_hero_state, reach * 1.4f);
    } else {
        cam_set_view_space_height(end, g_hero_state + 0xF0, 0.0f);
        vec_scale_to_length(end, end, reach);
        FastVecScale(lowerEnd, end, 1.4f);
    }
    FastVecAdd(end, end, start);
    material = -1;
    FastVecAdd(lowerEnd, lowerEnd, lowerStart);
    {
        u8 *hero = g_hero_state;
        if (CollLine(lowerStart, lowerEnd, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) material = GetCollHitMaterial();
    }
    angle = 0.0f;
    {
        u8 *hero = g_hero_state;
        if (CollLine(start, end, 2, *(u8 **)(hero + 0x2290), 0) && D_L18_001BFC00.count > 0) angle = cam_get_view_space_angle(D_L18_001BFC00.normal);
    }
    if (angle >= 0.8726647f || material == 8 || material == 12) {
        u8 *hero = g_hero_state;
        *(s32 *)(hero + 0x270) = D_L18_001BFC00.object;
        cam_set_view_space_height(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 0.0f);
        vec_scale_to_length(D_L18_001BFC00.normal, D_L18_001BFC00.normal, 1.0f);
        dot = FastVecDot(D_L18_001BFC00.normal, hero + 0xF0);
        if (dot < 0.0f) {
            FastVecScale(D_L18_001BFC00.normal, D_L18_001BFC00.normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, D_L18_001BFC00.normal);
        }
    }
}


extern BatchA_A18_s32 ref_L18_002E4090_00(BatchA_A18_s32 a0, BatchA_A18_s32 a1);

/* Starts a sound or effect that depends on the current level mode, with a short or long version. */
void snd_start_mode_sound(BatchA_A18_s32 a0) {
    BatchA_A18_s32 e = a0 ? 2 : 1;
    switch (D_0018C0D4) {
    case 0:
        ref_L18_002E4090_00(0, e);
        break;
    case 4:
        ref_L18_002E4090_00(0x8D, e);
        break;
    }
}

/* func_L18_002E42F8 is defined in L18_002E42F8-flags-g8.c. */

/* func_L18_002F1098 is matched in its own unit, L18_002F1098-g8.c. */

extern void text_measure_width_scaled(void *a0, void *a1, const char *a2);
extern char D_L18_00296510[];

/* Draws a fixed text string for the caller. */
void text_draw_fixed(void *a0, void *a1) {
    text_measure_width_scaled(a0, a1, D_L18_00296510);
}

/* func_L18_003044B8 is defined in L18_003044B8.c. */

/* func_L18_00307C60 is defined in L18_002C4000-quad.c. */

/* Sets one byte in an entry of the object's table; fails if the entry does not exist. */
BatchA_A18_s32 moby_set_table_entry_byte(BatchA_A18_u8 *s, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(s + 0x98);
    BatchA_A18_u8 *q;
    if (p == 0) {
        return 0;
    }
    if (a1 >= (*(BatchA_A18_s32 *)(p + 0x4) >> 5)) {
        return 0;
    }
    p += ((a1 << 5) + 0x10);
    *(p + 2) = (BatchA_A18_u8)a2;
    return 1;
}

extern BatchA_A18_s32 point_in_path_xy(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern BatchA_A18_s32 D_001FE480[];

/* hands the slot's payload to its handler; the slot table entry holds count then payload */
/* Looks up a table entry and hands its data to a handler, or returns the default value if there is none. */
BatchA_A18_s32 moby_run_slot_handler(BatchA_A18_s32 a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p;
    if (a1 != -1) {
        p = (BatchA_A18_u8 *)D_001FE480[a1];
        if (p != 0) {
            if (*(BatchA_A18_s32 *)p != 0) {
                return point_in_path_xy(a0, (BatchA_A18_s32)(p + 0x10), *(BatchA_A18_s32 *)p);
            }
        }
    }
    return a2;
}

/* func_L18_0035D238 is defined in L18_0035D238.c. */

extern float path_find_best_point(void *a0, void *a1, void *a2, char *a3, float f12);
extern BatchA_A18_s32 D_001FE480[];

/* Looks up a path by number and finds the best point on it; returns -1 if there is no path. */
float path_find_best_point_by_id(void *a0, void *a1, void *a2, BatchA_A18_s32 a3, float f12) {
    if (a3 == -1) {
        return -1.0f;
    }
    a3 = D_001FE480[a3];
    if (a3 == 0) {
        return -1.0f;
    }
    return path_find_best_point(a0, a1, a2, (char *)a3, f12);
}

extern f32 FindSegmentSpherePoint(void *, void *, void *, void *, void *, f32);
extern f32 math_fabs(f32);
extern float fast_vec_dist(char *, void *);

/* GCC 2.9's zero-length trailing array describes the variable point payload. */
typedef struct { s32 count; u8 reserved04[12]; f32 point[0][4]; } PathPoints;

/* Finds the best projected point on the path, breaking near ties by distance. */
f32 path_find_best_point(void *out, void *origin, void *direction, char *path, float scale) {
    f32 candidate[4];
    f32 best = 100000000000.0f;
    f32 score, distance;
    s32 i = 0;
    PathPoints *points = (PathPoints *)path;
    for (; i < points->count - 1; i++) {
        score = FindSegmentSpherePoint(candidate, origin, direction, points->point[i], points->point[i + 1], scale);
        if (score < best) {
            best = score;
            qcopy(out, candidate);
        } else if (math_fabs(score - best) < 0.1f) {
            distance = fast_vec_dist((char *)candidate, origin);
            if (distance < fast_vec_dist(out, origin)) {
                best = score;
                qcopy(out, candidate);
            }
        }
    }
    return best;
}


/* func_L18_003F50D8 is matched in L18_003F50D8.c (built with -mno-split-addresses). */



/* func_L18_003F5650 is matched in L18_003F5650-g16.c (built with -G16). */

/* func_L18_003F6CA8 is matched in L18_002C4000-move.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

extern void moby_update_ground_check(void *);
extern void protopet_end_action(void *a0, void *a1);
extern void value_set_and_smooth(char *a0, char *a1, BatchA_A18_s32 a2, BatchA_A18_s32 a3, float f12);
extern char g_camera_l18_position[];

/* Advances the object's step counter, refreshes the emitter and asks the particle
   system for the new position; the distance test only runs when the flag is set. */
void protopet_update_step(void *a0) {
    BatchA_A18_u8 *moby = (BatchA_A18_u8 *)a0;
    void *vars;
    unsigned short step_count;

    step_count = *(unsigned short *)((char *)moby + 0x96);
    if (step_count <= 0xFFFE) {
        vars = *(void **)((char *)moby + 0x68);
        *(unsigned short *)((char *)moby + 0x96) = step_count + 1;
    } else {
        vars = *(void **)((char *)moby + 0x68);
    }
    *(unsigned short *)((char *)vars + 0x290) = 0;
    if (moby[0x31] != 0) {
        if (fast_vec_dist((char *)moby + 0x10, g_camera_l18_position) < 24.0f) {
            moby_update_ground_check(moby);
            moby[0x6F] = 0x16;
        }
    }
    if (*(float *)((char *)moby + 0x10) < 5.0f || *(float *)((char *)moby + 0x10) > 1018.0f ||
        *(float *)((char *)moby + 0x14) < 5.0f || *(float *)((char *)moby + 0x14) > 1018.0f ||
        *(float *)((char *)moby + 0x18) < 5.0f || *(float *)((char *)moby + 0x18) > 1018.0f) {
        protopet_end_action(moby, 0);
    }
    value_set_and_smooth((char *)moby, (char *)vars + 0x2B0, 2, 1, 1.8f);
}

extern float mat_fast_helper_a(float a, float b);

/* Switches the Protopet-area object to its turning mode and aims it at a target. */
void protopet_start_turn_toward_target(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x290) = 1;
    *(float *)((char *)p + 0x264) =
        mat_fast_helper_a(*(float *)(a1 + 0x0) - *(float *)(a0 + 0x10),
                      *(float *)(a1 + 0x4) - *(float *)(a0 + 0x14));
}

/* Tells if the object has run out of time or steps. */
int protopet_is_action_finished(void *moby) {
    int result;
    void *vars;

    result = 0;
    vars = *(void **)((unsigned char *)moby + 0x68);
    if (((unsigned short) (*(unsigned short *)((unsigned char *)moby + 0x96)) >= 0xF1U) || ((*(short *)((unsigned char *)vars + 0x294)) >= (*(short *)((unsigned char *)vars + 0x2A4)))) {
        result = 1;
    }
    return result;
}

extern float func_00308AD0(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1);
extern BatchA_A18_s32 protopet_is_in_either_active_state(BatchA_A18_u8 *s);

/* Tells if another object is close enough and in a state to be picked up. */
BatchA_A18_s32 protopet_is_near_pickup_ready(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1) {
    BatchA_A18_s32 r = 0;
    if (func_00308AD0(a0 + 0x10, a1 + 0x10) < 5.0f) {
        r = protopet_is_in_either_active_state(a1) != 0;
    }
    return r;
}

/* func_L18_003F73B8 */
extern float vec_distance_xy(char *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);

/* The 1.5707964 spelling is load-bearing: this assembler under-rounds by an ulp
   (1.5707964f, 1.57079637f and even 1.5707963705062866f all encode 0x3FC90FDB,
   retail holds 0x3FC90FDC).  Measured by sweeping spellings, COMPILER-NOTES. */
/* Tells if the target is close and in front of the object. */
int protopet_is_target_close_front(char *a0, float *a1)
{
    char *moby = a0;
    float *target = a1;
    int result = 0;

    if (*(unsigned char *)(moby + 0x31) != 0) {
        if (vec_distance_xy(moby + 0x10, a1) < 3.2f) {
            if (FastDiffRots(*(float *)(moby + 0xF8),
                             mat_fast_helper_a(target[0] - *(float *)(moby + 0x10),
                                           target[1] - *(float *)(moby + 0x14))) < 1.5707965f)
                result = 1;
        }
    }
    return result;
}


extern BatchA_A18_s32 math_random_int_below(BatchA_A18_s32 a0);

extern BatchA_A18_s32 protopet_count_group(BatchA_A18_s32 a0, BatchA_A18_u8 *a1);

/* runs the 0x1E gate and, when it clears, the record query into a local buffer;
   answers whether the query found anything */
BatchA_A18_s32 protopet_find_for_group(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 buf[16];
    BatchA_A18_s32 p;

    if (math_random_int_below(0x1E) == 0) {
        p = *(BatchA_A18_s32 *)(a0 + 0x68);
        return protopet_count_group(*(BatchA_A18_s32 *)((char *)p + 0x25C), buf) != 0;
    }
    return 0;
}

extern void moby_set_state(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2);
extern void moby_mark_spawned(void *);
extern void part_queue_moby_for_glow(void *, int, void *);
extern void protopet_reset_to_idle(BatchA_A18_u8 *a0);

/* Ends the object's current action: clears its state and either hands off to the next step or removes it. */
void protopet_end_action(void *a0, void *a1)
{
    char *moby = a0;
    int immediate = (int)a1;
    char *vars = *(char **)(moby + 0x68);
    short remaining;

    *(int *)(vars + 0x20) = 0;
    moby_set_state(moby, 0x13, 0);
    *(unsigned short *)(moby + 0x34) &= 0xEFFF;
    *(unsigned short *)(vars + 0x292) -= 1;
    remaining = *(unsigned short *)(vars + 0x292);
    if (remaining != -1 || *(short *)(vars + 0x296) == 0xE) {
        if (immediate != 0) {
            protopet_reset_to_idle(moby);
        } else {
            part_queue_moby_for_glow(moby, 0, protopet_reset_to_idle);
        }
    } else {
        if (immediate != 0) {
            moby_mark_spawned(moby);
        } else {
            part_queue_moby_for_glow(moby, 0, 0);
        }
    }
}

/* Resets the object's flags and puts it back in its idle state. */
void protopet_reset_to_idle(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x88) = 0;
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) & 0xEFFF) | 0x43);
    moby_set_state(a0, 1, 0);
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)(*(unsigned short *)(a0 + 0x34) & 0xEFFF);
}

/* The group id lists, the entity bank base and the resident group count. The two scalars are
   `sda` arrays of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui`/`lw`) as retail has it in this -G0 unit. */
extern unsigned short *D_L18_001FB320[];
extern char *g_moby_l18_table[] __attribute__((sda));
extern int D_L18_001B2838[] __attribute__((sda));

/* Counts the entities of kind 0xB69 in state 1 that the group's id list names, stores the count
   through a1 and returns the last of them (0 when there is none). Retail compares the state with
   0xFE and 0xFD before testing it for 1. */
BatchA_A18_s32 protopet_count_group(BatchA_A18_s32 a0, BatchA_A18_u8 *a1) {
    unsigned short *entry;
    unsigned char *entity;
    unsigned char *last;
    BatchA_A18_s32 *count = (BatchA_A18_s32 *)a1;

    *count = 0;
    if (a0 == -1)
        return 0;
    last = 0;
    for (entry = D_L18_001FB320[a0];
         (a0 & 0xFF) != 0xFF && a0 <= D_L18_001B2838[0] && entry != 0 &&
         ((short)entry[-1] >= 0 || entry == D_L18_001FB320[a0]);
         entry++) {
        entity = (unsigned char *)(g_moby_l18_table[0] + ((*entry & 0x7FFF) << 8));
        if (entity == 0)
            break;
        if (*(short *)(entity + 0xAA) == MOBY_CLASS_PROTOPET && entity[0x20] != 0xFE && entity[0x20] != 0xFD && entity[0x20] == 1) {
            (*count)++;
            last = entity;
        }
    }
    return (BatchA_A18_s32)last;
}

/* func_L18_003F76F0 lives in L18_003F76F0-copy.c. */

extern void vec_scale_to_length(void *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);

/* the object's state flags and aim angle are set, then the target is handed
   over to the object's controller */
void protopet_attach_to_target(BatchA_A18_u8 *moby, BatchA_A18_u8 *target, BatchA_A18_s32 flip) {
    float local[4];
    BatchA_A18_u8 *vars;
    BatchA_A18_s32 *info;
    BatchA_A18_s32 v1;
    BatchA_A18_u8 state;

    vars = *(BatchA_A18_u8 **)(moby + 0x68);
    state = moby[0x20];
    if (state == 1) {
        info = *(BatchA_A18_s32 **)(moby + 0x24);
        *(unsigned short *)(moby + 0x34) =
            (unsigned short)((*(unsigned short *)(moby + 0x34) & 0xFFBE) | 0x1000);
        v1 = info[4];
        *(unsigned short *)(moby + 0x34) =
            (unsigned short)(*(unsigned short *)(moby + 0x34) & 0xFFFD);
        *(BatchA_A18_s32 *)(moby + 0x98) = v1;
        vars[0x2E] = state;
        moby[0x7F] = 0;
        *(float *)(vars + 0x20) = (float)*(short *)(vars + 0x24);
        vec_scale_to_length(local, target + 0xC0, -0.5f);
        FastVecAdd(moby + 0x10, target + 0x10, local);
        if (flip != 0) {
            vec_scale_to_length(local, target + 0xD0, 0.5f);
        } else {
            vec_scale_to_length(local, target + 0xD0, -0.5f);
        }
        FastVecAdd(moby + 0x10, target + 0x10, local);
        *(float *)(moby + 0xF8) =
            mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(moby + 0x10),
                          *(float *)(target + 0x14) - *(float *)(moby + 0x14));
    }
    *(BatchA_A18_s32 *)(vars + 0x258) = (BatchA_A18_s32)target;
    moby_set_state(moby, 0xB, 2);
    protopet_set_ready_flag((BatchA_A18_u8 *)*(BatchA_A18_s32 *)(vars + 0x258));
}

/* func_L18_003F7988 lives in L18_003F7988-copy.c. */

/* Picks the right animation for the object depending on whether it has a target. */
void protopet_choose_anim_by_target(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 *moby = a0;
    BatchA_A18_s32 vars;
    if (moby[0x95] != 1) {
        return;
    }
    vars = *(BatchA_A18_s32 *)(moby + 0x68);
    if (*(BatchA_A18_s32 *)(vars + 0x258) != 0) {
        func_00335668(moby, 0xB, 2);
    } else if (*(BatchA_A18_s32 *)(vars + 0x278) != -1) {
        func_00335668(moby, 0xD, 2);
    } else {
        func_00335668(moby, 0xC, 2);
    }
    func_00335668(moby, 7, -1);
}

extern void protopet_choose_anim_by_target(BatchA_A18_u8 *a0);
/* Runs the animation choice only when the object is in the right mode. */
void protopet_choose_anim_if_active(BatchA_A18_u8 *a0) {
    if (a0[0x95] == 1) {
        protopet_choose_anim_by_target(a0);
    }
}

/* func_L18_003F7AB8 is defined in L18_002C4000-g8.c (this unit has $gp access for it). */

extern void moby_copy_saved_point_below(void *a0, void *a1);
extern void vec_scale_to_length(void *a0, void *a1, float f12);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern float coll_probe_ground_height_below(void *a0, BatchA_A18_s32 a1, float f12);
extern void euler_rotation_basis(char *a, char *b);

/* Moves the object's state word, refreshes the two transform matrices through the
   shared helpers and writes the measured distance back into the object. */
void protopet_setup_target_transforms(void *a0, void *a1, void *a2) {
    char scratch[16];
    char mat[16];
    unsigned short flags;
    void *info;
    void *vars;
    void *value;
    float angle;

    flags = *(unsigned short *)((char *)a0 + 0x34);
    info = *(void **)((char *)a0 + 0x24);
    flags = (unsigned short)((flags & 0xFFBE) | 0x1000);
    *(unsigned short *)((char *)a0 + 0x34) = flags;
    value = *(void **)((char *)info + 0x10);
    *(void **)((char *)a0 + 0x98) = value;
    moby_set_state((BatchA_A18_u8 *)a0, 5, 2);
    vars = *(void **)((char *)a0 + 0x68);
    *(void **)((char *)vars + 0x74C) = a2;
    if (a1 != 0) {
        moby_copy_saved_point_below(a1, mat);
        vec_scale_to_length(scratch, (char *)a1 + 0xD0, -0.3f);
        FastVecAdd((char *)a0 + 0x10, mat, scratch);
        *(float *)((char *)a0 + 0x18) = coll_probe_ground_height_below((char *)a0 + 0x10, 0, 0.5f);
        angle = mat_fast_helper_a(*(float *)mat - *(float *)((char *)a0 + 0x10),
                           *(float *)(mat + 4) - *(float *)((char *)a0 + 0x14));
        *(float *)((char *)a0 + 0xF8) = angle;
        euler_rotation_basis((char *)a0 + 0xC0, (char *)a0 + 0xF0);
        *(void **)((char *)vars + 0x750) = a1;
        *(BatchA_A18_u8 *)((char *)a0 + 0x7F) = 0;
    }
}

/* A18-void-store-16 freshly exact-verified under family reservation */
/* Sets a flag on the object so it counts as ready. */
void protopet_set_ready_flag(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_BatchAs16 *)((char *)p + 0x768) = 1;
}

/* A18-cond-select twin of 003F8E80: two independent state gates */
/* Tells if the object is in one of two particular states. */
BatchA_A18_s32 protopet_is_in_either_active_state(BatchA_A18_u8 *s) {
    BatchA_A18_s32 r = 0;
    if ((s[0x20] == 5 && s[0xBC] == 1) || (s[0x20] == 3 && s[0x94] == 5)) {
        r = 1;
    }
    return r;
}

/* A09-cond-select-36 freshly exact-verified under family reservation */
/* Tells if the object is in a particular state and sub-state. */
BatchA_A09_s32 protopet_is_in_state_substate(BatchA_A09_u8 *s) {
    BatchA_A09_s32 r = 0;
    if (s[0x20] == 6) { r = (s[0xBC] == 2); }
    return r;
}

/* func_L18_003F8EA8 is defined in L18_003F8EA8-qcopy.c. */

extern void func_00335388(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);

/* Puts the object into its starting animation and clears its links. */
void protopet_reset_to_start_anim(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    func_00335388(a0, 0, 0, 3);
    *(BatchA_A18_s32 *)(a0 + 0x48) = 0;
    *(unsigned short *)((char *)p + 0x98) = 0;
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF);
    func_00335668(a0, 1, 1);
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
}

/* func_L18_003F9DA0 is defined in L18_002C4000-switch-g8.c. */

extern void moby_reset_to_saved_transform(unsigned char *a0);
extern void protopet_reset_to_spawn(unsigned char *a0);

/* Slot i of the object's eight group ids (the words at +0x60). Retail rebuilds the slot address
   at every test of the walk, which is what an inline helper expanded in place does. */
static __inline__ int L18_GroupId(unsigned char *p, int i) {
    int off = i << 2;
    int *ids = (int *)(p + 0x60);
    return *(int *)((char *)ids + off);
}

/* Walks the id list of each of the object's eight groups and, for every entity in it, calls the
   handler of its kind (0xD5C, 0x11CC, 0xD9B, 0x11CF or 0xB69), clears the entity's word at +0x98
   and sets bits 0 and 1 of its flags at +0x34; then stores -1 at +0x88 of the object. */
/* Wakes every member of the object's eight groups and resets them. */
void protopet_wake_group_members(unsigned char *a0) {
    unsigned char *vars = *(unsigned char **)(a0 + 0x68);
    unsigned short *entry;
    unsigned char *entity;
    int i;

    for (i = 0; i < 8; i++) {
        for (entry = D_L18_001FB320[L18_GroupId(vars, i)];
             (L18_GroupId(vars, i) & 0xFF) != 0xFF && L18_GroupId(vars, i) <= D_L18_001B2838[0] &&
             entry != 0 && ((short)entry[-1] >= 0 || entry == D_L18_001FB320[L18_GroupId(vars, i)]);
             entry++) {
            entity = (unsigned char *)(g_moby_l18_table[0] + ((*entry & 0x7FFF) << 8));
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == MOBY_CLASS_TRAIN_WITH_RAIL || *(short *)(entity + 0xAA) == 0x11CC /* moby class 4556 */ ||
                *(short *)(entity + 0xAA) == MOBY_CLASS_TRAIN || *(short *)(entity + 0xAA) == 0x11CF /* moby class 4559 */) {
                moby_reset_to_saved_transform(entity);
            } else if (*(short *)(entity + 0xAA) == MOBY_CLASS_PROTOPET) {
                protopet_reset_to_spawn(entity);
            }
            *(int *)(entity + 0x98) = 0;
            *(unsigned short *)(entity + 0x34) |= 3;
        }
    }
    *(int *)(vars + 0x88) = -1;
}

/* Slot i of the state block's eight group ids (the words at +0x60). */
#define L18_GROUP_ID(i) (*(int *)(state + 0x60 + (i) * 4))

/* The engine's walk over a group's terminated stream of 15-bit actor indices, written as in
   the other matched walks (FOR_EACH_ID in L06_0033BDC0-g8.c). Its repeated `entry != 0` adds a
   label to the exit test that jump.c cannot thread before cse, so the rolled test is not copied
   in front of the loop; the PRE copies then land behind NOTE_INSN_LOOP_BEG, last in the init. */
#define L18_FOR_EACH_ID(entry, i) \
    for (entry = D_L18_001FB320[L18_GROUP_ID(i)]; \
         (L18_GROUP_ID(i) & 0xFF) != 0xFF && L18_GROUP_ID(i) <= D_L18_001B2838[0] && entry != 0 && \
         ((entry != 0 && (short)entry[-1] >= 0) || entry == D_L18_001FB320[L18_GROUP_ID(i)]); \
         entry++)

/* Disables every actor of group i: clears flag bits 0, 1 and 6 and sets bit 12 at +0x34,
   copies the word at +0x10 of the actor's +0x24 block to +0x98 and, unless the owner is of
   kind 0xB69, also clears the byte at +0x31 and sets bit 0 again. */
#define L18_DISABLE_GROUP(i) \
    L18_FOR_EACH_ID(entry, i) { \
        member = D_L18_001B281C[0] + (*entry & 0x7fff) * 0x100; \
        if (member == 0) \
            break; \
        flags = *(unsigned short *)(member + 0x34) & 0xffbc; \
        *(unsigned short *)(member + 0x34) = flags | 0x1000; \
        *(int *)(member + 0x98) = *(int *)(*(char **)(member + 0x24) + 0x10); \
        if (*(short *)(owner + 0xaa) != MOBY_CLASS_PROTOPET) { \
            member[0x31] = 0; \
            *(unsigned short *)(member + 0x34) = flags | 0x1001; \
        } \
    }

/* Disables the actor groups that belong to mode 0-4 of the owner's state block. */
void L18_DisableModeGroups(char *owner, unsigned int mode)
{
    unsigned char *state = *(unsigned char **)(owner + 0x68);
    unsigned short *entry;
    char *member;
    unsigned short flags;

    if (mode >= 8)
        return;
    switch (mode) {
    case 0:
        L18_DISABLE_GROUP(0);
        L18_DISABLE_GROUP(1);
        break;
    case 1:
        L18_DISABLE_GROUP(2);
        break;
    case 2:
        L18_DISABLE_GROUP(3);
        L18_DISABLE_GROUP(5);
        L18_DISABLE_GROUP(6);
        break;
    case 3:
        L18_DISABLE_GROUP(4);
        break;
    case 4:
        L18_DISABLE_GROUP(7);
        break;
    case 5:
    case 6:
    case 7:
        return;
    }
}

#undef L18_DISABLE_GROUP
#undef L18_FOR_EACH_ID
#undef L18_GROUP_ID

/* The bank base and group count again, read-only here: this walk calls nothing, and retail loads
   both once before the walk of each group (the count also once for the whole function) instead of
   rereading them after the stores, as const data lets loop.c hoist them. */
extern char *const D_L18_001B281C_1[] __attribute__((sda));
extern const int D_L18_001B2838_1[] __attribute__((sda));

/* Walks the id list of each of the object's eight groups like func_L18_003F9FB0 and, for every
   entity in it, clears its word at +0x98 and sets bits 0, 1 and 6 of its flags at +0x34 while
   clearing bit 12. */
/* Resets every member of the object's eight groups and turns on their flags. */
void protopet_reset_group_members(unsigned char *a0) {
    unsigned char *vars = *(unsigned char **)(a0 + 0x68);
    unsigned short *entry;
    unsigned char *entity;
    int i;

    for (i = 0; i < 8; i++) {
        for (entry = D_L18_001FB320[L18_GroupId(vars, i)];
             (L18_GroupId(vars, i) & 0xFF) != 0xFF && L18_GroupId(vars, i) <= D_L18_001B2838_1[0] &&
             entry != 0 && ((short)entry[-1] >= 0 || entry == D_L18_001FB320[L18_GroupId(vars, i)]);
             entry++) {
            entity = (unsigned char *)(D_L18_001B281C_1[0] + ((*entry & 0x7FFF) << 8));
            if (entity == 0)
                break;
            *(int *)(entity + 0x98) = 0;
            *(unsigned short *)(entity + 0x34) = (*(unsigned short *)(entity + 0x34) & 0xEFFF) | 0x43;
        }
    }
}

/* Uses up one count from the object's counter if there is any left. */
BatchA_A18_s32 protopet_try_use_counter(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    if (*(short *)((char *)p + 0xA8) > 0) {
        *(unsigned short *)((char *)p + 0xA8) =
            (unsigned short)(*(unsigned short *)((char *)p + 0xA8) - 1);
        return 1;
    }
    return 0;
}

/* Adds one to the object's counter. */
void protopet_increment_counter(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(unsigned short *)((char *)p + 0xA8) =
        (unsigned short)(*(unsigned short *)((char *)p + 0xA8) + 1);
}

/* Each scan reads the current slot id again when advancing its group iterator. */
static __inline__ int L18_SelectionGroupId(char *p, int i, int base) {
    int off = i << 2;
    int *groups = (int *)(p + base);
    return *(int *)((char *)groups + off);
}

/* Selects the source, secondary member and target from the owner's three group
   lists. The first target scan prefers entries passing the flag and distance tests. */
int SelectGroupMembersAndTarget(char *owner, int slot) {
    char *secondary[2];
    char *state = *(char **)(owner + 0x68);
    char *source = 0;
    char *selected = 0;
    char *entity;
    int i;

    memset(secondary, 0, 8);
    {
        unsigned short *entry;
        for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)];
             (L18_SelectionGroupId(state, slot, 0) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0)]); entry++) {
            entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (entity != 0 && *(unsigned char *)(entity + 0x20) != 0xfe &&
                *(unsigned char *)(entity + 0x20) != 0xfd &&
                (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                source = entity;
                break;
            }
        }
    }
    if (source == 0) return 0;
    for (i = 0; i < 1; i++) {
        {
            unsigned short *entry;
            for (entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)];
                 (L18_SelectionGroupId(state, slot, 0x20) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x20) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x20)]); entry++) {
                entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (entity != secondary[0] && entity != 0 &&
                    *(unsigned char *)(entity + 0x20) != 0xfe &&
                    *(unsigned char *)(entity + 0x20) != 0xfd &&
                    (*(unsigned short *)(entity + 0x34) & 1) != 0) {
                    secondary[i] = entity;
                    break;
                }
            }
        }
    }
    if (secondary[0] == 0) return 0;
    {
        unsigned short *entry;
        for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
             (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
             L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
             ((short)entry[-1] >= 0 ||
              entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
            entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
            if (entity == 0) break;
            if (*(unsigned char *)(entity + 0x31) != 0 &&
                vec_distance_squared_xy(g_hero_position, entity + 0x10) > 16.0f &&
                moby_is_state_two((unsigned char *)entity) == 0) {
                selected = entity;
                break;
            }
        }
    }
    if (selected == 0) {
        {
            unsigned short *entry;
            for (entity = 0, entry = D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)];
                 (L18_SelectionGroupId(state, slot, 0x10) & 0xff) != 0xff &&
                 L18_SelectionGroupId(state, slot, 0x10) <= D_L18_001B2838[0] && entry != 0 &&
                 ((short)entry[-1] >= 0 ||
                  entry == D_L18_001FB320[L18_SelectionGroupId(state, slot, 0x10)]); entry++) {
                entity = g_moby_l18_table[0] + (*entry & 0x7fff) * 0x100;
                if (entity == 0) break;
                if (moby_is_state_two((unsigned char *)entity) == 0) {
                    selected = entity;
                    break;
                }
            }
        }
        if (selected == 0) goto fail;
    }
    protopet_setup_target_transforms(source, entity, (void *)L18_SelectionGroupId(state, slot, 0x10));
    protopet_attach_to_target((unsigned char *)secondary[0], (unsigned char *)source, 0);
    moby_enter_hit_state((unsigned char *)selected, 1);
    return 1;
fail:
    return 0;
}

/* func_L18_003FAE50 lives in L18_003FAE50-beam.c. */

/* func_L18_003FB500 lives in L18_003FB500.c. */

/* func_L18_003FB5E8 is matched in its own unit, src/levels/shared/L18_003FB5E8-qcopy.c (-frac2-qcopy). */

/* Starts one of two animations on the object and clears its links. */
void protopet_start_enter_anim(BatchA_A18_u8 *a0, BatchA_A18_s32 a1) {
    if (a1 != 0) {
        func_00335668(a0, 3, -1);
    } else {
        func_00335668(a0, 2, -1);
    }
    *(BatchA_A18_s32 *)(a0 + 0x98) = 0;
    *(unsigned short *)(a0 + 0x34) =
        (unsigned short)((*(unsigned short *)(a0 + 0x34) | 0x41) & 0xEFFF);
}

/* func_L18_003FC9B8 lives in L18_003F7988-copy.c. */

/* func_L18_003FCA38 is defined in L18_003FCA38-g8.c. */



/* func_L18_003FCC48 lives in L18_003FCC48-particles.c. */

/* func_L18_003FCD70 lives in L18_003FCD70-particles.c. */


/* store -1 into field 0x74 of the object at s[0x68] */
void protopet_clear_link_minus_one(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_s32 *)((char *)p + 0x74) = -1;
}

/* Clears the object's saved link value to zero. */
void protopet_clear_link_zero(BatchA_A18_u8 *s) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(s + 0x68);
    *(BatchA_A18_s32 *)((char *)p + 0x74) = 0;
}


extern void func_0033A0B0(BatchA_A18_u8 *a0, BatchA_A18_u8 *a1);
extern void func_0032D118(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2,
                          BatchA_A18_s32 a3);

/* Sets the object to its default look with mid-grey color. */
void moby_reset_color_grey(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    *(unsigned short *)((char *)p + 0x50) = 0;
    *(unsigned short *)((char *)p + 0x52) = 1;
    func_0033A0B0(a0, (BatchA_A18_u8 *)p + 0x50);
    *(BatchA_A18_u8 *)((char *)p + 0x54) = 0x80;
    *(BatchA_A18_u8 *)((char *)p + 0x55) = 0x80;
    *(BatchA_A18_u8 *)((char *)p + 0x56) = 0x80;
    func_0032D118(a0, 0x80, 0x80, 0x80);
}


/* func_L18_00426E48 lives in L18_00426E48-g8.c. */

extern void func_002EC9C8(BatchA_A18_u8 *a0, BatchA_A18_s32 a1);

/* Starts an animation on the object, or passes the request on when it is in another mode. */
void moby_start_or_forward_anim(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2, float f12) {
    if (a0[0xBC] == 0) {
        if (a0[0x43] != a1) {
            func_00335388(a0, a1, a2, (BatchA_A18_s32)f12);
        }
    } else {
        func_002EC9C8((BatchA_A18_u8 *)a1, a2);
    }
}

extern void moby_set_controller_speed_limits(BatchA_A18_u8 *, float, float, float, float);
extern void math_fast_float_d(void *a0);

/* the object's scale angles are re-submitted in degrees, then the matrix is rebuilt */
void moby_rebuild_scale_matrix(BatchA_A18_u8 *a0) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(a0 + 0x68);
    if (a0[0x21] != 0xFF) {
        if (*(BatchA_A18_u8 *)(p + 0x39F) != 0) {
            moby_set_controller_speed_limits(a0, 0.00027777778450399637f * *(float *)(p + 0x3C4),
                          0.01666666753590107f * *(float *)(p + 0x3C0),
                          4.848137450608192e-06f * *(float *)(p + 0x3D4),
                          0.0002908882452175021f * *(float *)(p + 0x3D0));
            math_fast_float_d(*(void **)(p + 0x388));
        }
    }
    *(BatchA_A18_u8 *)(p + 0x39F) = 0;
}

extern void math_fast_float_d(void *a0);

/* Releases the shared resource used by the object, if it holds one. */
void moby_release_shared_resource(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    if (a0[0x21] != 0xFF && *(BatchA_A18_u8 *)(p + 0x3B0) != 0) {
        math_fast_float_d(*(void **)(p + 0x3AC));
    }
    *(BatchA_A18_u8 *)(p + 0x3B0) = 0;
}

/* Takes a hold on the shared resource used by the object, if it does not have one yet. */
void moby_acquire_shared_resource(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    BatchA_A18_s32 q;
    if (a0[0x21] == 0xFF) {
        return;
    }
    if (*(BatchA_A18_u8 *)(p + 0x3B0) != 0) {
        return;
    }
    q = *(BatchA_A18_s32 *)(p + 0x3AC);
    (*(BatchA_A18_s32 *)q)++;
    *(BatchA_A18_u8 *)(p + 0x3B0) = 1;
}

extern BatchA_A18_s32 path_measure_moby_against_entry(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, float f12);
extern BatchA_A18_s32 path_apply_entry_to_moby(BatchA_A18_u8 *a0, BatchA_A18_s32 a1,
                                        BatchA_A18_s32 a2, BatchA_A18_s32 a3);

/* re-seats the object on a new animation; -1 means "leave it to the level" */
BatchA_A18_s32 moby_set_anim(BatchA_A18_u8 *a0, BatchA_A18_s32 a1, BatchA_A18_s32 a2) {
    BatchA_A18_u8 *p = *(BatchA_A18_u8 **)(a0 + 0x68);
    BatchA_A18_s32 r;
    *(BatchA_A18_s32 *)(p + 0x38C) = a1;
    if (a1 == -1) {
        *(BatchA_A18_BatchAs16 *)(p + 0x1C8) = (BatchA_A18_BatchAs16)a1;
        return -1;
    }
    r = path_measure_moby_against_entry(a0 + 0x10, a1, 0.0f);
    if (path_apply_entry_to_moby(a0, a1, a2, r) != 0) {
        return *(short *)(p + 0x1C8);
    }
    *(unsigned short *)(p + 0x1C8) = 0;
    return -1;
}

extern BatchA_A18_s32 path_get_entry_id(void *a0);

/* Switches the object's animation helper on or off. */
BatchA_A18_s32 moby_toggle_anim_helper(BatchA_A18_u8 *a0) {
    BatchA_A18_s32 p = *(BatchA_A18_s32 *)(a0 + 0x68);
    if (*(short *)((char *)p + 0x1CA) != 0) {
        *(BatchA_A18_BatchAs16 *)((char *)p + 0x1CA) = 0;
        return 0;
    }
    *(BatchA_A18_BatchAs16 *)((char *)p + 0x1CA) =
        (BatchA_A18_BatchAs16)path_get_entry_id(*(void **)((char *)p + 0x38C));
    return 1;
}

/* func_L18_00427208 is defined in L18_00427208-qcopy.c. */

/* func_L18_004273F0 is matched in L18_004273F0-g8.c (built with -frac2-qcopy). */

/* func_L18_00427688 lives in L18_00427688-g32.c. */

/* func_L18_00427B48: 144 bytes against retail's 148; the chain pointer and the
   stored 1 take each other's register. Deposited in nonmatching/levels/. */
