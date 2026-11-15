#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

typedef short s16;
typedef unsigned short u16;
typedef struct {
    u8 pad[0x20];
    u8 values[1];
} L03ChoiceRecord;
typedef struct {
    u8 pad[0x48];
    u32 field48, field4C;
    s16 previous, current, field54, field56, field58, field5A;
    s16 last, length, field60, cursor, depth;
} L03ChoicePath;

extern u32 D_L03_0024A7B0;
extern void choice_list_build(u8 *);
extern void ComputePathPuzzleTurn(u8 *);


/* Three measured byte-state cases and width-specific field views.
   The correspondence name UpdateMoby_2426 does not establish an original
   class, enumeration, allocation or field-name declaration. */
extern void moby_set_state(u8 *, u8, s32);

extern u32 flag_is_third_pending_set(u8 *);

typedef float f32;

typedef struct {
    u32 field00;
    u32 field04;
    f32 field08;
    f32 field0C;
} NativeCallbackTimer;

extern NativeCallbackTimer D_L04_001B98E0;

extern f32 D_L04_001B1C88 __attribute__((sda));

/* Four-byte pointer in the resident image (0x001B2A1C).  The retail reads it
   with a per-site `lui $r,%hi` + `lw $r,%lo($r)` pair, which is gas's expansion
   of the bare-symbol macro cc1 emits only for an `sda` symbol. */
extern u8 *D_L03_001B2A1C __attribute__((sda));

/* func_L03_003C5B28 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5CE8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5DC8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
extern void route_choose_target_point(u8 *, void *, f32 *);
extern void route_set_node_enabled_flag(u32, u8 *, s32);
extern s32 coll_test_point(void *, s32, void *, f32);
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_flag_bit(u8 *entity, s32 enabled);
extern char g_hero_position[];

typedef struct {
    u8 pad0[0x110];
    f32 f110;
    f32 f114;
    u8 pad118[0x220 - 0x118];
    u32 f220;
    u8 pad224[0x340 - 0x224];
    f32 f340[4];
    u8 pad350[0x358 - 0x350];
    u8 *f358;
} L03_5EE8Vars;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
} L03_5EE8Class;

typedef struct {
    u8 pad0[0x24];
    L03_5EE8Class *f24;
    u8 pad28[0x43 - 0x28];
    u8 f43;
    u8 pad44[0x68 - 0x44];
    L03_5EE8Vars *f68;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} L03_5EE8Moby;

/* Finds a safe spot for the object this one is holding and puts it down there. If the spot is blocked, it keeps holding the object. */
void moby_place_held_object(L03_5EE8Moby *moby) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 test[4] __attribute__((aligned(16)));
    L03_5EE8Vars *vars = moby->f68;

    route_set_node_enabled_flag(vars->f220, vars->f358 + 0x10, 0);
    route_choose_target_point(vars->f358, g_hero_position, pos);
    qcopy(test, pos);
    test[2] += vars->f110 + vars->f114;
    if (coll_test_point(test, 0, moby, vars->f110) == 0) {
        qcopy(vars->f340, pos);
        moby_set_flag_bit(vars->f358, 0);
        vars->f358 = 0;
        moby->f98 = moby->f24->f10;
        moby_set_state((u8 *)moby, 0x11, 4);
        if (moby->f43 != 0) {
            anim_start_blended(moby, 0, 0, 0x14);
        }
    } else {
        route_set_node_enabled_flag(vars->f220, vars->f358 + 0x10, 1);
    }
}

/* func_L03_003C9FB8 lives in L03_003C9FB8.c. */

/* Tells whether the object is in its first state. */
int moby_is_first_state(unsigned char *moby) { return moby[0x20] == 1; }

/* func_L03_003CA148 is matched in its own unit, L03_003CA148.c. */

/* Sets the height offset stored in the object. */
void moby_set_height_offset(u8 *moby, f32 height) {
    *(f32 *)(*(u8 **)(moby + 0x68) + 0xA0) = height;
}

/* func_L03_003CA230 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1300. */

/* Tells whether the object is in its first state. */
int moby_is_in_state_one(unsigned char *moby) { return moby[0x20] == 1; }



/* Updates a toggling object (moby class 2426). It switches between two states as its animation finishes, and sets a flag value while in the second one. */
void toggling_moby_update(u8 *moby) {
    switch (moby[0x20]) {
    case 0:
        moby_set_state(moby, 1, -1);
        *(u32 *)(moby + 0x98) = 0;
        *(unsigned short *)(moby + 0x34) =
            (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
        break;
    case 1:
        if (flag_is_third_pending_set(moby) != 0) {
            moby_set_state(moby, 2, -1);
            *(u32 *)(moby + 0x98) =
                *(u32 *)(*(u8 **)(moby + 0x24) + 0x10);
        }
        break;
    case 2:
        if (flag_is_third_pending_set(moby) == 0) {
            moby_set_state(moby, 1, -1);
            *(u32 *)(moby + 0x98) = 0;
        }
        break;
    }
}

extern int IsPointInCuboid(u8 *, u32);

/* Checks another object against a test value stored in this object. Returns 1 if it passes. */
u32 moby_check_against_stored_value(u8 *moby, u8 *other) {
    return IsPointInCuboid(other, *(u32 *)(*(u8 **)(moby + 0x68) + 0x60)) != 0;
}

/* func_L03_003CAAF0 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1354. */

/* Checks two points against the route graph of the indexed record. */
s32 route_check_points(u32 poolIndex, u8 *first, u8 *second);
extern void moby_compute_opposite_points(u8 *, f32 *, f32 *);
extern s32 FindRouteNodeIndex(u32, f32 *);
extern f32 vec_distance_xy(void *, f32 *);
extern f32 coll_probe_ground_height_below(f32 *, s32, f32);

/* Copies one of the two points func_L03_003CAAF0 computes into out: the first
   that func_L03_00419BD8 accepts, else the first that func_L03_00419C58 finds,
   else the one with the smaller func_00282E80 against D_00189EA0. One copy per
   branch: cross-jumping merges them, and their references order the saved
   registers as retail does. Then raises out[2] by 0.5 and replaces it with
   func_002A89A8's result. */
/* func_L03_003CAB80 lives in L03_003CAB80.c. */

extern f32 FastAddRotations(f32, f32);

/* Updates the Blue Swingshot Target. Once active, it turns two of its rotation values toward their goals. */
void blue_swingshot_target_update(u8 *moby) {
    if (*(u8 *)(moby + 0x31) == 0)
        return;
    *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4),
                                        0.10471977293491364f);
    *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8),
                                        0.04654212296009064f);
}

/* func_L03_003CC238 lives in L03_003CC238.c. */

/* Defined in L03_003CC478.c. */

/* func_L03_003D04E0 lives in L03_003D04E0-g8.c. */

/* func_L03_003D09D0 is matched in its own unit, src/levels/shared/L03_003D09D0.c (-g). */

/* func_L03_003D0AE0 lives in L03_003D0AE0-g8.c. */

extern f32 math_random_float_range(f32, f32);

extern s32 math_random_int_below(s32);

extern void vec_random_direction(f32 *, f32, f32);

extern void FastVecAdd(void *, void *, void *);

extern void part_spawn_ground_effect(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);

/* Spawns two puffs of particles with random size and speed, used by the particle emitter. */
void part_spawn_emitter_pair(u8 *moby, s32 matrix, s32 color) {
    f32 velocity[3];
    f32 size, life;
    s32 spin, tint;

    tint = color;
    size = math_random_float_range(0.25f, 1.0f);
    spin = math_random_int_below(2);
    life = math_random_float_range(3.0f, 7.0f) * (1.0f / 3600.0f);
    vec_random_direction(velocity, 0.0f, 0.1f);
    FastVecAdd(velocity, velocity, matrix);
    part_spawn_ground_effect(velocity, 0x28, 0x7F800000, 0, spin, tint, 0, size * 0.2f, size, life);
    part_spawn_ground_effect(velocity, 0x3C, 0x7F7F7F7F, 1, -spin, tint, 0, size * 0.14f, size * 0.7f, life);
}

/* func_L03_003D9578 is defined in L03_003D9578.c. */

/* func_L03_003D9820 is defined in L03_003D9820-g8.c. */

/* func_L03_003E21B0 lives in L03_003E21B0-g8.c. */

/* func_L03_003E26C8 is defined in L03_003E26C8-g8.c. */

/* func_L03_003E2968 is defined in L03_003E2968-g8.c. */

/* func_L03_003E2C08 is defined in L03_003C5B28-g8.c (it reads the step count through $gp). */

/* Picks a random value from a row of the table that is not already in use. Returns -1 if all are used. */
s32 SelectUnusedTableEntry(u8 *moby, u32 row, s32 usedCount, u32 *extraUsed, s32 extraCount) {
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 start;
    s32 six;
    s32 i;
    s32 value;
    s32 found;
    u32 rowOffset;
    start = math_random_int_below(6);
    six = 6;
    rowOffset = row * 24;

    for (i = 0; i < six; i++) {
        s32 index = (i + start) % six;
        s32 j;

        value = *(u32 *)((u8 *)&D_L03_0024A7B0 + (rowOffset + index * 4));
        if (value == -1)
            continue;
        j = 0;
        found = 0;
        for (; j < usedCount + 2; j++) {
            if (((L03ChoiceRecord *)vars)->values[j] == value)
                found = 1;
        }
        {
            s32 k;
            for (k = 0; k < extraCount; k++) {
                if (extraUsed[k] == value)
                    found = 1;
            }
        }
        if (found == 0)
            return value;
    }
    return -1;
}

/* Adds the current choice to the path, or takes back the last one if it was just chosen. Then it rebuilds the list of choices. */
void UpdateChoicePath(u8 *moby) {
    L03ChoicePath *path = *(L03ChoicePath **)(moby + 0x68);
    u8 *data = (u8 *)path;
    if (path->current == path->last) {
        *(u8 *)(data + path->previous + 0x10) = 0;
        data[path->length] = 0xFF;
        path->previous = path->last;
        if (path->length >= 2)
            path->last = data[path->length - 2];
        else
            path->last = 0;
        *(u8 *)(data + path->length + 0x30) = 0xFF;
        path->length--;
        if (path->depth != 0)
            path->depth--;
        else
            path->cursor--;
    } else {
        *(u8 *)(data + path->current + 0x10) = 1;
        {
            s16 depth = path->depth;
            u16 value = *(u16 *)&path->depth;
            if (depth == 0 && path->current == data[path->cursor + 0x21])
                path->cursor++;
            else
                path->depth = value + 1;
        }
        path->last = path->previous;
        path->previous = path->current;
        path->length++;
        data[path->length] = (u8)path->current;
    }
    choice_list_build(moby);
    path->field48 = 0;
    path->field4C = 0;
    path->field56 = 0;
    ComputePathPuzzleTurn(moby);
}

/* func_L03_003E3018 is defined in L03_003E3018.c. */

extern u32 D_0024A7B0;

extern s32 ref_L03_003E3750_00(u8 *, u32);

/* Copies the six values the record's own row of the shared table holds into the
   record's list, skipping the ones the record does not take, and ends the list
   with 255. */
void choice_list_build(u8 *a0) {
    u32 rec = *(u32 *)(a0 + 0x68);
    u32 v = *(u32 *)((u8 *)&D_0024A7B0 + *(short *)(rec + 0x50) * 24);
    s32 count = 0;
    u32 n = 0;
    u32 ok;

    if (v != 255) {
        u32 flags = rec + 0x20;
        u32 list = rec + 0x40;

        do {
            if (*(short *)(rec + 0x64) == 0 &&
                v == *(u8 *)(*(short *)(rec + 0x62) + flags + 1)) {
                ok = 1;
            } else if (ref_L03_003E3750_00(a0, v)) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok) {
                *(u8 *)(list + n) = v;
                n++;
            }
            count++;
            if (count >= 6)
                break;
            v = *(u32 *)((u8 *)&D_0024A7B0 + count * 4 + *(short *)(rec + 0x50) * 24);
        } while (v != 255);
    }
    *(u8 *)(rec + n + 0x40) = 255;
}

/* func_L03_003E3430 is defined in L03_003E3430.c. */

/* func_L03_003E3678 lives in L03_003E3678-g8.c. */



/* func_L03_003E3A00 lives in L03_003E3A00-g8.c. */

/* func_L03_003E4680 is defined in L03_003E4680-g8.c. */

/* func_L03_003E4148 is defined in L03_003E4148-g8.c. */


extern u8 *CreateMoby(s32);

extern void moby_init_child_from_parent(u8 *, u8 *);

extern void euler_rotation_basis(u8 *, u8 *);

/* Creates an Infiltrator Ball, links it to this object and remembers it in this object's data. */
void infiltrator_ball_spawn_for_moby(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *child = CreateMoby(MOBY_CLASS_INFILTRATOR_BALL);

    if (child == 0)
        return;
    moby_init_child_from_parent(child, moby);
    euler_rotation_basis(child + 0xC0, child + 0xF0);
    *(unsigned short *)(child + 0x34) =
        (*(unsigned short *)(child + 0x34) | 0x100);
    *(u32 *)(vars + 0x58) = (u32)child;
}

/* func_L03_003E50E0 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1CB0. */

extern void cam_set_mode_state(int);

extern void cam_set_value_target(int, int, f32, f32, f32, f32);

extern void moby_mark_spawned(u8 *);

extern s32 g_activeGadgetItem;

extern f32 D_001B9C14;

/* The retail materialises this one's address with `lui $at`, which is gas's expansion of the
   bare-symbol macro cc1 only emits for an `sda` symbol. */
extern f32 D_001B2464 __attribute__((sda));

/* Hands the entity's gadget class id to the active-gadget global, clears the entity's
 * gadget state and releases the resident class it was holding. */
void gadget_reset_state(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 zero = 0.0f;
    f32 scale = 1.12434113f;    /* bits 0x3F8FEA69 (0x3F8FEA69 != 1.12434f) */

    cam_set_mode_state(3);
    D_001B9C14 = scale;
    cam_set_value_target(1, 0, scale, 0.005f, 0.2f, zero);
    *(f32 *)(vars + 0x6C) = zero;
    g_activeGadgetItem = *(s32 *)(vars + 0x64);
    D_001B2464 = zero;
    if (*(u8 **)(vars + 0x58) != 0) {
        moby_mark_spawned(*(u8 **)(vars + 0x58));
        *(u32 *)(vars + 0x58) = 0;
    }
}

/* Turns on a flag in the object's data. */
void moby_set_flag_on(u8 *moby) {
    *(u32 *)(*(u8 **)(moby + 0x68) + 0x60) = 1;
}


/* func_L03_00409248 is defined in L03_00409248-g8.c. */

/* func_L03_00409AB0 lives in L03_00409AB0-g8.c. */


extern f32 math_fabs(f32);

/* Tells whether the object's height is almost exactly a stored height. */
int moby_is_at_stored_height(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    return math_fabs(*(f32 *)(moby + 0x18) - *(f32 *)(vars + 0x8)) < 0.01f;
}

/* func_L03_00419578 lives in L03_00419578-g8.c. */

/* Returns the stored count while the object is in state 2, otherwise 0. */
u32 moby_get_count_in_state_two(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 2)
        return *(u32 *)(vars + 0x10);
    return 0;
}

/* func_L03_004197C8 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x2AA0. */

/* Saves a value and counts down a stored number. When the count reaches zero, the object moves to state 3. */
void moby_decrement_count_and_finish(u8 *moby, u32 value) {
    u8 *vars = *(u8 **)(moby + 0x68);
    s32 count = *(s32 *)(vars + 0x10);
    *(u32 *)(vars + 0x1C) = value;
    count--;
    *(s32 *)(vars + 0x10) = count;
    if (count == 0)
        moby_set_state(moby, 3, -1);
}


extern void moby_mark_spawned(u8 *);

extern u32 path_build_region_link_graph(u8 *, u8 *, u8 *, s32);

/* On the first state, frees the object if it has no data. Otherwise it sets up its route table and moves to state 1. */
void route_init_pool_record(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);

    if (*(u8 *)(moby + 0x20) == 0) {
        if (vars == 0) {
            moby_mark_spawned(moby);
        } else {
            *(u32 *)(vars + 0x480) =
                path_build_region_link_graph(moby, vars, vars + 0x80, 0x20);
            moby_set_state(moby, 1, -1);
        }
    }
}

/* Hands one record of the pool the level index selects to the shared lookup and then sets or
   clears the low bit of the record's tenth halfword flag. */
void route_set_node_enabled_flag(u32 a0, u8 *a1, s32 a2) {
    u8 *rec = (u8 *)D_L03_001B2A1C + (a0 << 8);
    u8 *q = *(u8 **)(rec + 0x68);
    s32 index;

    if (*(u8 *)(rec + 0x20) == 0)
        route_init_pool_record(rec);
    index = -1;
    if (path_find_route_node_containing_point(a1, &q[0x80], ((s32 *)q)[0x120], &index) == 0)
        return;
    if (a2 != 0)
        *(unsigned short *)(q + (index << 5) + 0x8C) &= 0xFFFE;
    else
        *(unsigned short *)(q + (index << 5) + 0x8C) |= 1;
}

extern s32 ComputeRegionRouteHeading(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);

/* Asks the route graph of the indexed record about two points and a heading. Passes along the margin and tolerance. */
s32 route_query_graph_heading(u32 poolIndex, u8 *first, u8 *second, u8 *heading, s32 *firstIndex, s32 *secondIndex,
                     float margin, float tolerance) {
    u8 *vars = *(u8 **)((u8 *)D_L03_001B2A1C + (poolIndex << 8) + 0x68);

    return ComputeRegionRouteHeading(first, second, heading, vars + 0x80, *(s32 *)(vars + 0x480), firstIndex, secondIndex,
                            margin, tolerance);
}

/* Returns the value stored for a route node, or -1 if there is no node. */
s32 route_get_node_value(u32 poolIndex, s32 nodeIndex) {
    u8 *vars = *(u8 **)((u8 *)D_L03_001B2A1C + (poolIndex << 8) + 0x68);
    u8 *node;

    if (nodeIndex != -1) {
        node = vars + (nodeIndex << 5);
        return *(s32 *)(node + 0x80);
    }
    return -1;
}

extern s32 path_find_route_node_containing_point(u8 *, u8 *, s32, s32 *);

/* Finds which node of the route graph holds a point and writes its index. */
void route_lookup_node_index(u32 poolIndex, u8 *point, u8 *outIndex) {
    u8 *vars = *(u8 **)((u8 *)D_L03_001B2A1C + (poolIndex << 8) + 0x68);

    path_find_route_node_containing_point(point, vars + 0x80, *(s32 *)(vars + 0x480), (s32 *)outIndex);
}

s32 route_check_object_points(u8 *, u8 *, u8 *);

s32 route_check_points(u32 a0, u8 *first, u8 *second) {
    return route_check_object_points((u8 *)D_L03_001B2A1C + (a0 << 8), first, second);
}

/* The route graph a pool record points to. Reading count through the struct matters:
   the sentinel stores are fixed-address scalars, which cannot alias a varying struct
   field, so the load does not depend on them. */
typedef struct {
    u8 pad[0x80];
    u8 nodes[0x400];
    s32 count;
} L03RouteState;

/* Asks ComputeRegionRouteHeading about the two points on the object's route graph; the
   heading it writes and both node indices stay local. */
s32 route_check_object_points(u8 *object, u8 *first, u8 *second) {
    float angle;
    s32 firstIndex, secondIndex;
    L03RouteState *record = *(L03RouteState **)(object + 0x68);
    firstIndex = -1;
    secondIndex = -1;
    return ComputeRegionRouteHeading(first, second, &angle, record->nodes,
                            record->count, &firstIndex, &secondIndex,
                            0.0f, 0.1f);
}

/* Returns the node of the indexed record's route graph that holds a1, or -1. */
s32 FindRouteNodeIndex(u32 a0, f32 *a1) {
    L03RouteState *state = *(L03RouteState **)((u8 *)D_L03_001B2A1C + (a0 << 8) + 0x68);
    s32 out = -1;

    path_find_route_node_containing_point((u8 *)a1, state->nodes, state->count, &out);
    return out;
}

/* Does nothing. */
void moby_l03_noop(void)
{
}

/* func_L03_00424C40 is in L03_00424C40-g8.c (-G8, -fno-gcse). */

extern s32 math_random_int_below(s32);

/* Sets up the object's data with random color values and fixed numbers. */
void moby_init_random_colors(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 *color = (f32 *)(vars + 0x10);
    s32 i;

    for (i = 3; i >= 0; i--) {
        *color++ = (f32)math_random_int_below(0xFF);
    }
    *(f32 *)(vars + 0x20) = -1.0f;
    *(f32 *)(vars + 0x24) = -2.25f;
    *(f32 *)(vars + 0x28) = 1.25f;
    *(f32 *)(vars + 0x2C) = 2.5f;
    {
        s32 k = 3;
        u32 *target = (u32 *)(vars + 0x3C);
        u32 level = 0xFF;

        for (; k >= 0; k--) {
            *target = level;
            target--;
            level -= 0x40;
        }
    }
    *(f32 *)(vars + 0x40) = 2.0f;
    *(f32 *)(vars + 0x44) = 2.46f;
    *(f32 *)(vars + 0x4C) = 2.0f;
    *(f32 *)(vars + 0x48) = 2.46f;
}


/* The resident word at 0x001A79F0, below the level base, so its value is the same in every
   program.  The retail reads it absolutely in ordinary flow and through $gp in a delay slot,
   which is what the `sda` declaration's bare-symbol model gives in this unit. */
extern int g_current_map_index __attribute__((sda));

extern void moby_init_between_points(u8 *, void *, void *);

extern /* Splits a packed number into its top byte and its lower 24 bits and stores both in the object's data. */
void moby_set_packed_fields(u8 *, u32);

/* Allocates the object's record, copies the two source fields into it, hands the record to
   the two setup helpers, and writes into the resident block the size the word at 0x001A79F0
   selects. */
u8 *moby_create_configured(void *position, void *velocity, u32 packed, u8 *parent, u32 param, u32 keepTimer) {
    u8 *moby = CreateMoby(0x13BA /* moby class 5050 */);
    u8 *vars;

    if (moby != 0) {
        *(unsigned short *)(moby + 0x34) |= 0x100;
        vars = *(u8 **)(moby + 0x68);
        *(u8 *)(moby + 0x30) = (parent != 0) ? *(u8 *)(parent + 0x30) : 0x96;
        *(unsigned short *)(moby + 0x32) = (parent != 0) ? *(unsigned short *)(parent + 0x32) : 0x96;
        *(u8 *)(moby + 0x20) = 0;
        *(u32 *)(vars + 0x20) = param;
        *(u32 *)(vars + 0x44) = (u32)parent;
        moby_init_between_points(moby, position, velocity);
        moby_set_packed_fields(moby, packed);
        if (keepTimer == 0)
            *(u32 *)(vars + 0x3C) = 0;
        if (g_current_map_index == 0)
            *(u32 *)(vars + 0x48) = 0x48;
        if (g_current_map_index == 3)
            *(u32 *)(vars + 0x48) = 0x3F;
        if (g_current_map_index == 6)
            *(u32 *)(vars + 0x48) = 0x44;
        if (g_current_map_index == 9)
            *(u32 *)(vars + 0x48) = 0x48;
        if (g_current_map_index == 0x12)
            *(u32 *)(vars + 0x48) = 0x43;
    }
    return moby;
}


void moby_set_packed_fields(u8 *a0, u32 a1) {
    if (a0 != 0) {
        u8 *p = *(u8 **)(a0 + 0x68);
        *(u32 *)(p + 0x2C) = (s32)a1 >> 24;
        *(u32 *)(p + 0x40) = a1 & 0xFFFFFF;
    }
}

/* func_L03_0042B930 lives in the -g8 sibling: its first read is a $gp float. */

typedef struct {
    int a;
    int b;
    float c;
    int d;
    void (*e)(void);
} S_2fa6d8_r0043AC40;

extern S_2fa6d8_r0043AC40 r1_D_L02_00167680_FBB10 __asm__("r1_D_L02_00167680");

extern void r1_func_L02_002FBB48(void);

typedef struct {
    int a;
    int b;
    float c;
    float d;
} S_r0043AC40;

extern S_r0043AC40 r1_D_L02_00167680;

extern void r1_func_L02_002FBB48();

/* rac1-decomp src/overlays/shared/vendor_002A5218.c: func_L02_002FBB10 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002ec308.c, FUN_L02_002fa6d8. */
/* Resets a global record to zero, sets a large distance value and stores a callback. */
void global_record_reset(void) {
    r1_D_L02_00167680_FBB10.a = 0;
    r1_D_L02_00167680_FBB10.b = 0;
    r1_D_L02_00167680_FBB10.c = 10000.0f;
    r1_D_L02_00167680_FBB10.d = 0;
    r1_D_L02_00167680_FBB10.e = r1_func_L02_002FBB48;
}

extern f32 D_L03_001B9BEC;

extern void cam_set_aim_offset_target(s32, f32, f32);

extern void register_camera_update_callback(void *);

extern void timer_tick_countdown(void);

/* If a strength value is set, starts a timed effect scaled by it and registers a callback. */
void effect_start_scaled_if_set(void) {
    if (D_L03_001B9BEC != 0.0f) {
        cam_set_aim_offset_target(1, D_L03_001B9BEC * 0.35f, 0.005f);
        register_camera_update_callback(timer_tick_countdown);
    }
}

extern void timer_tick_countdown(void);


/* rac1-decomp src/game/stub.c: func_001E97C8 */
/* Takes an argument (callers pass one, e.g. r1_func_001EC210) and ignores
   it -- the unused parameter costs no codegen, still 0/8. */
/* Does nothing and returns 0. */
int util_return_zero(void *unusedArg) {
    return 0;
}


/* Does nothing. */
void moby_l03_noop_2(void)
{
}

/* Does nothing. */
void moby_l03_noop_3(void)
{
}
