#include "common.h"


extern void moby_mark_spawned(void *);
extern void anim_start_blended(void *, int, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void *SpawnDirectedEffectObject(void *, void *, void *, int);
extern float math_random_float_range(float, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_range(int, int);
extern u8 *part_spawn_velocity_particle(void *, void *, int, int, float);

/* family c459a266b43242d6 - 352 bytes, 2 placements
   levels/19_grelbin @0x00412F70, levels/8_tabora @0x0041E630

   Fills five output floats from two pinned tables and a resident flag word,
   then clamps the three still free outputs to [-1, 1]. */

extern float D_00189E20_14[];

extern int g_pad_state[];

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TI128 __attribute__((mode(TI)));

/* A resident word: the same address and the same value in every program.  It is
   read as a symbol here (the `sda` declaration leaves the one- or two-instruction
   choice to the assembler) and as a literal in func_L08_003DB4A0, whose two
   conditional loads the literal address form is what reproduces. */
extern s32 g_current_map_index __attribute__((sda));

/* shared callee, named by its catalogue row (08:003289D0, 19:00319288) */
extern void math_store_angle_update_result(void *, s32, s32, s32, float);

extern char g_hero_position[];
extern float vec_distance_xy(char *, void *);

/* Two 0x30-byte target records: [0] the tracked owner, [1] the nearest one seen. */
typedef struct {
    TI128 pos;      /* 0x00 */
    void *owner;    /* 0x10 */
    float dist;     /* 0x14 */
    s32 unk18;      /* 0x18 */
    s32 unk1C;      /* 0x1C */
    s32 valid;      /* 0x20 */
    s32 pad[3];
} L08Target;

extern L08Target g_lock_on_targets[] __attribute__((sda));

/* One entity of the group: the kind word is at 0xAA. */
typedef struct L08Thing {
    u8 pad[0xAA];
    s16 kind;
} L08Thing;

/* The group: the count is at 0x44, the list of entities at 0x18C. */
typedef struct L08Group {
    u8 pad0[0x44];
    s16 count;
    u8 pad1[0x18C - 0x46];
    L08Thing *items[1];     /* bounded by count */
} L08Group;

extern L08Group g_tabora_scene;
extern s32 g_cutscene_l08_active_flag[] __attribute__((sda));
extern u8 g_unlocked_item_flags[] __attribute__((sda));
extern u8 g_mystic_manipulator_data[] __attribute__((sda));
extern f32 g_mystic_scale_vec[] __attribute__((sda));

extern void AttachManipulator(u8 *, u32, u8 *);

/* For func_L08_00435A78. */
extern void moby_set_state(void *, int, int);
extern s32 level_get_saved_count(void);
extern void moby_disable_object_list_flags(void), moby_reset_vars_defaults(void *);
extern int hero_is_reachable_for_count(void *, int, float);
extern void level_apply_index_for_key(void *), text_print_localized_formatted(int, ...);
extern int req_push_queue(void *, int), game_is_either_mode_two(void);
extern void moby_set_byte_on_group(int, int), moby_restore_object_list_flags(void);
extern s32 req_launch_queued(void *);
extern void STUB_printf(const char *, ...);
extern int MemcardSave(int, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void func_L00_0030C710(int);
extern int FastDecTimer(void *), math_fast_float_d(void *), FloatToInt(float);
extern float mat_fast_helper_a(float, float), FastDiffRots(float, float);
extern float FastAddRotations(float, float), fast_subtract_rotations(float, float), vec_length_xy(void *);
extern void FastVecSub(void *, void *, void *);
extern void moby_update_eased_node(void *, void *, int, float, float);

/* The hero: read at 0x80 (centre), 0xE0 (position) and 0x110 (velocity). */
typedef struct {
    u8 pad0[0x80];
    char x80[0x60];
    f32 pos[4];
    u8 padF0[0x20];
    f32 x110[4];
} L08Hero;
extern L08Hero g_hero_state;

/* One 0x100-byte entity of the table at D_L08_001B29DC. */
typedef struct {
    u8 pad0[0x31];
    u8 x31;
    u8 pad32[2];
    u16 x34;
    u8 pad36[0xBC - 0x36];
    u8 xBC;
    u8 padBD[0x100 - 0xBD];
} L08Moby;
extern L08Moby *g_moby_array MACRO_ADDR;

/* Words retail never moves into a delay slot are fields read at an offset from
   an earlier symbol; bare names are loaded by $gp in a slot (docs/build/compiler-notes.md). */
extern u8 g_player_stats[] __attribute__((sda));
extern u8 g_mystic_state[] __attribute__((sda));
extern int g_mystic_flag_table[] __attribute__((sda));
extern int g_frame_l08_counter MACRO_ADDR;
extern int g_saved_entity_count MACRO_ADDR;
extern int g_player_bolts MACRO_ADDR;
extern u8 g_game_flag_table[];
extern int g_pad_held_flags;
extern int g_mystic_prices[];
extern u8 g_request_l08_queue[];
extern char g_str_mystic_debug[];

/* Measures the resident actor position against POS: a nearer POS replaces record [1]
   (owner, distance, position), and record [0] is refreshed when OWNER is its owner.
   The records are reached as `sda` offsets, so every access is one assembler macro. */
/* Offers a candidate lock-on target: keeps it if it is the closest one seen so far this frame. */
void UpdateNearestTarget(void *owner, void *pos)
{
    float distance = vec_distance_xy(g_hero_position, pos);

    if (distance < g_lock_on_targets[1].dist) {
        g_lock_on_targets[1].unk1C = 0;
        g_lock_on_targets[1].owner = owner;
        g_lock_on_targets[1].unk18 = 0;
        g_lock_on_targets[1].dist = distance;
        qcopy(&g_lock_on_targets[1].pos, pos);
        g_lock_on_targets[1].valid = 1;
    }
    if (g_lock_on_targets[0].owner == owner) {
        g_lock_on_targets[0].dist = distance;
        qcopy(&g_lock_on_targets[0].pos, pos);
        g_lock_on_targets[0].valid = 1;
    }
}

/* func_L08_003D39F0 is defined in L08_003D3928-g8.c. */

/* One resident word, two states, and a 16-byte table entry: hands the entry to
   func_L00_00326048 with an alpha of 0x3D7A35E0. */
/* Updates a Glider Pad (moby class 2440): draws its glow effect once it has its data. */
void glider_pad_update(u8 *moby)
{
    s32 effect_data = *(s32 *)(moby + 0x68);

    if (effect_data == 0)
        return;
    math_store_angle_update_result(moby, effect_data, 0x80AAAAD2, 0x80396464, 0.0610865355f);
}


/* Updates an effect object (moby class 2465): when its target is hit it plays an animation and
   throws a burst of sparks, and it removes itself when the target is gone. */
void hit_effect_update(u8 *moby)
{
    float direction[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float random_dir[4] __attribute__((aligned(16)));
    u8 *target = *(u8 **)*(u32 *)(moby + 0x68);
    int sparks_left;
    if (!target || target[0x20] == 0xFE || target[0x20] == 0xFD) {
        moby_mark_spawned(moby);
        return;
    }
    if ((moby[0x60] & 2) && moby[0x43])
        anim_start_blended(moby, 0, 0, 0);
    if (moby[0xBC]) {
        moby[0xBC] = 0;
        if (moby[0x43] != 1) anim_start_blended(moby, 1, 0, 0);
        vec_build_spherical_offset(direction, 1.0f, *(float *)(moby+0xF8), -*(float *)(moby+0xF4));
        moby_transform_joint_to_world(moby, 0, position);
        SpawnDirectedEffectObject(moby, position, direction, 0x5A);
        sparks_left = 4;
        do {
            *(TI128 *)random_dir = 0;
            random_dir[0] = math_random_float_range(-1.0f, 1.0f);
            random_dir[1] = math_random_float_range(-1.0f, 1.0f);
            random_dir[2] = math_random_float_range(-1.0f, 1.0f);
            *(TI128 *)velocity = *(TI128 *)random_dir;
            vec_scale_to_length(velocity, velocity, FastVecLength(direction)*0.65f);
            FastVecAdd(velocity, direction, velocity);
            vec_scale_to_length(velocity, velocity, math_random_float_range(0.050000004f, 0.10000001f));
            part_spawn_velocity_particle(position, velocity, 0x5F2F4F6F, math_random_int_range(5,10), 50000.0f);
        } while (--sparks_left >= 0);
        vec_scale_to_length(direction, direction, 0.008333334f);
        part_spawn_velocity_particle(position, direction, 0x2F4F7F7F, math_random_int_range(4,7), 500000.0f);
    }
}

/* Returns 2 in one special mode and 1 otherwise. */
/* The same resident word, but the 8 case falls through to a 1/2 selector. */
s32 mode_get_selector(void)
{
    s32 mode = g_current_map_index;
    s32 result = 1;

    if (mode == 8)
        return 1;
    if (mode == 0x13)
        result = 2;
    return result;
}


/* func_L08_003DB8E8 is matched in its own unit, L08_003DB8E8-g8.c. */






/* func_L08_003F6610 is matched in its own unit, L08_003F6610-g8.c. */

/* func_L08_0041E4F8 is defined in L08_0041E4F8-flags-g8.c. */

/* Reads the controller and gives back five movement values, each limited to the range -1 to 1. */
/* shared native body of family c459a266b43242d6 */
void vehicle_read_controls(float *stick_x, float *lift_axis, float *stick_y, float *throttle, float *turn_axis)
{
    float axis;
    float up_down;
    int buttons;

    *stick_x = -D_00189E20_14[2028];
    *stick_y = -D_00189E20_14[2029];
    buttons = g_pad_state[104];
    up_down = 0.0f;
    if (buttons & 0x40)
        up_down = 1.0f;
    axis = (buttons & 0x20) ? (up_down - 1.0f) : up_down;
    *lift_axis = axis;
    *throttle = *(float *)&g_pad_state[75];
    buttons = g_pad_state[104];
    axis = 0.0f;
    if (buttons & 0x1)
        axis = 1.0f;
    if (buttons & 0x2)
        axis = axis - 1.0f;
    *turn_axis = axis;
    if (*stick_x > 1.0f)
        *stick_x = 1.0f;
    else if (*stick_x < -1.0f)
        *stick_x = -1.0f;
    if (*lift_axis > 1.0f)
        *lift_axis = 1.0f;
    else if (*lift_axis < -1.0f)
        *lift_axis = -1.0f;
    if (*turn_axis > 1.0f)
        *turn_axis = 1.0f;
    else if (*turn_axis < -1.0f)
        *turn_axis = -1.0f;
}

/* func_L08_0041E790 is defined in L08_0041E790-g8.c. */

/* func_L08_0041EA88 is defined in L08_0041EA88-match.c. */

/* func_L08_004207D0 is defined in L08_004207D0-g8.c. */

/* func_L08_0042E678 is defined in L08_0042E678-g8.c. */

/* func_L08_0042EF00 is defined in L08_0042EF00-g8.c. */

/* func_L08_00435600 is defined in L08_00435600-helpers.c. */

/* Copies a position value into the object's private data. */
/* Stores one 16-byte block through the pointer at 0x68 of the argument. */
void moby_store_position_private(u8 *moby, void *source)
{
    *(volatile TI128 *)*(u32 *)(moby + 0x68) = *(TI128 *)source;
}

/* func_L08_004356B8 is defined in L08_004356B8-g8.c. */


/* Makes every other object of the same kind glow bright when the shop screen is open. */
/* For every listed entity of A0's kind, while the mode word is 2 and the resident
   flag is set, hands it to func_0029F978 with the level block at 0x001B22E0 unless its
   byte 1 is set, and sets the vector at 0x001B2300 to 2.3. */
void mystic_handle_entity_list(L08Thing *sample)
{
    L08Thing *other;
    s32 i;

    if (g_cutscene_l08_active_flag[0] != 2)
        return;
    if (g_unlocked_item_flags[0] == 0)
        return;
    for (i = 0; i < g_tabora_scene.count; i++) {
        other = g_tabora_scene.items[i];
        if (other->kind != sample->kind)
            continue;
        if (g_mystic_manipulator_data[1] != 0)
            continue;
        AttachManipulator((u8 *)other, 0, g_mystic_manipulator_data);
        g_mystic_scale_vec[0] = 2.3f;
        g_mystic_scale_vec[1] = 2.3f;
        g_mystic_scale_vec[2] = 2.3f;
    }
}

#define I(p, o) (*(int *)((u8 *)(p) + (o)))
#define H(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define F(p, o) (*(float *)((u8 *)(p) + (o)))
#define QUANTITY (*(s16 *)(D_001A7A00 + 0x1A))
#define PRICE (D_L08_001A7C80[0xF] ? D_L08_00295E50[3] : D_L08_00295E50[2])

/* Updates The Mystic (moby class 3646), a shopkeeper that sells an item and buys back the
   player's collected bolts or Raritanium, and turns its head to watch the hero. */
/* An interaction state machine at byte 0x20: offers an item for its price while
   the quantity at D_001A7A00+0x1A covers it, then buys the remaining quantity back
   at 1000 (10000 with the flag at D_001A7A00+0xA) each; afterwards aims the head at the hero. */
void UpdateItemTraderNpc(u8 *mystic)
{
    float look_target[4] __attribute__((aligned(16)));
    float head_pos[4] __attribute__((aligned(16)));
    float to_target[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(mystic + 0x68);
    int pay_multiplier, watching_hero;
    float blend_speed, yaw, pitch, angle;
    float blend_weight = 0.3f;

    mystic_handle_entity_list((L08Thing *)mystic);
    if (g_cutscene_l08_active_flag[0] == 6) {
        mystic[0x31] = 0;
        H(mystic, 0x34) |= 1;
        F(mystic, 0xF4) = -3.14159274f;
    } else {
        mystic[0x31] = 1;
        F(mystic, 0xF4) = 0;
        H(mystic, 0x34) &= 0xFFFE;
    }
    if (g_frame_l08_counter == 5)
        level_get_saved_count();
    switch (mystic[0x20]) {
    case 0:
        if (!g_game_flag_table[0x1C])
            moby_disable_object_list_flags();
        else if (I(vars, 0x124) != -1) {
            moby_mark_spawned(&g_moby_array[I(vars, 0x124)]);
            I(vars, 0x124) = -1;
        }
        level_get_saved_count();
        moby_reset_vars_defaults(mystic);
        if (g_game_flag_table[0x1C]) {
            if (QUANTITY <= 0)
                moby_set_state(mystic, 6, -1);
            else
                moby_set_state(mystic, 7, -1);
        } else if (g_game_flag_table[0x1B]) {
            if (QUANTITY < PRICE)
                moby_set_state(mystic, 3, -1);
            else
                moby_set_state(mystic, 4, -1);
        } else
            moby_set_state(mystic, 1, -1);
        break;
    case 1:
        if (hero_is_reachable_for_count(mystic, 10, 2.5f)) {
            level_apply_index_for_key(mystic);
            if (req_push_queue(g_request_l08_queue, 0x59)) {
                g_game_flag_table[0x1B] = 1;
                req_launch_queued(g_request_l08_queue);
                moby_set_state(mystic, 2, -1);
            }
        }
        break;
    case 2:
        if (g_cutscene_l08_active_flag[0] == 2) {
            mystic[0x31] = 0;
            H(mystic, 0x34) |= 1;
        }
        if (I(vars, 0x124) != -1 && g_cutscene_l08_active_flag[0] == 2) {
            g_moby_array[I(vars, 0x124)].x34 |= 1;
            g_moby_array[I(vars, 0x124)].x31 = 0;
        }
        g_mystic_flag_table[1] = 1;
        if (!game_is_either_mode_two()) {
            g_mystic_flag_table[1] = 0;
            mystic[0x31] = 1;
            H(mystic, 0x34) &= 0xFFFE;
            if (I(vars, 0x124) != -1) {
                g_moby_array[I(vars, 0x124)].x34 &= 0xFFFE;
                g_moby_array[I(vars, 0x124)].x31 = 1;
            }
            if (QUANTITY < PRICE)
                moby_set_state(mystic, 3, -1);
            else
                moby_set_state(mystic, 4, -1);
        }
        break;
    case 3:
        if (QUANTITY >= PRICE)
            moby_set_state(mystic, 4, -1);
        else if (hero_is_reachable_for_count(mystic, 10, 2.5f)) {
            text_print_localized_formatted(0x27A4, PRICE, -1);
            level_apply_index_for_key(mystic);
        }
        break;
    case 4:
        if (QUANTITY < PRICE)
            moby_set_state(mystic, 3, -1);
        else if (hero_is_reachable_for_count(mystic, 10, 2.5f)) {
            text_print_localized_formatted(0x2796, PRICE, -1);
            level_apply_index_for_key(mystic);
            if (g_pad_held_flags & 0x10) {
                req_push_queue(g_request_l08_queue, 0x5A);
                QUANTITY -= PRICE;
                req_launch_queued(g_request_l08_queue);
                moby_set_state(mystic, 5, -1);
            }
        }
        break;
    case 5:
        if (g_cutscene_l08_active_flag[0] == 2) {
            mystic[0x31] = 0;
            H(mystic, 0x34) |= 1;
        }
        if (I(vars, 0x124) != -1 && g_cutscene_l08_active_flag[0] == 2) {
            moby_mark_spawned(&g_moby_array[I(vars, 0x124)]);
            I(vars, 0x124) = -1;
        }
        g_mystic_flag_table[1] = 1;
        if (!game_is_either_mode_two()) {
            g_mystic_flag_table[1] = 0;
            mystic[0x31] = 1;
            H(mystic, 0x34) &= 0xFFFE;
            if (mystic[0x21] != 0xFF)
                moby_set_byte_on_group(mystic[0x21], 1);
            g_game_flag_table[0x1C] = 1;
            moby_restore_object_list_flags();
            STUB_printf(g_str_mystic_debug);
            if (I(vars, 0x124) != -1) {
                moby_mark_spawned(&g_moby_array[I(vars, 0x124)]);
                I(vars, 0x124) = -1;
            }
            if (I(vars, 0x120) != -1)
                g_moby_array[I(vars, 0x120)].xBC = 1;
            MemcardSave(0, -1);
            if (QUANTITY <= 0)
                moby_set_state(mystic, 6, -1);
            else
                moby_set_state(mystic, 7, -1);
        }
        break;
    case 6:
        if (QUANTITY > 0)
            moby_set_state(mystic, 7, -1);
        else if (hero_is_reachable_for_count(mystic, 10, 2.5f)) {
            if (!g_saved_entity_count)
                text_print_localized_formatted(0x27D0, 0, -1);
            else
                text_print_localized_formatted(0x27A7, -1);
            level_apply_index_for_key(mystic);
        }
        break;
    case 7:
        if (QUANTITY <= 0)
            moby_set_state(mystic, 6, -1);
        else {
            pay_multiplier = g_player_stats[0xA] ? 10 : 1;
            if (hero_is_reachable_for_count(mystic, 10, 2.5f)) {
                pay_multiplier *= 1000;
                text_print_localized_formatted(0x2797, QUANTITY, QUANTITY * pay_multiplier, -1);
                level_apply_index_for_key(mystic);
                if (g_pad_held_flags & 0x10) {
                    level_get_saved_count();
                    g_player_bolts += QUANTITY * pay_multiplier;
                    snd_play_from_class_bank(0, 0, mystic, math_random_int_range(13, 17));
                    QUANTITY = 0;
                    func_L00_0030C710(180);
                    moby_set_state(mystic, 8, -1);
                }
            }
        }
        break;
    case 8:
        H(mystic, 0x96)++;
        if (H(mystic, 0x96) > 0x7FF8)
            H(mystic, 0x96) = 0x7FF8;
        if (H(mystic, 0x96) > 40 && H(mystic, 0x96) < 90 && H(mystic, 0x96) % 4 == 0)
            snd_play_from_class_bank(0, 0, mystic, math_random_int_range(13, 17));
        if (hero_is_reachable_for_count(mystic, 10, 2.5f))
            text_print_localized_formatted(0x27D0, g_saved_entity_count, -1);
        else
            moby_set_state(mystic, 6, -1);
        break;
    }
    if (mystic[0x20]) {
        if (mystic[0x43] == 1 && FastDecTimer(vars + 0x11E)) {
            H(vars, 0x11E) = FloatToInt(math_random_float_range(1200, 2400));
            if (mystic[0x43] != 2)
                anim_start_blended(mystic, 2, 0, 10);
        } else if ((mystic[0x60] & 2) && mystic[0x43] != 1)
            anim_start_blended(mystic, 1, 0, 10);
    }
    blend_speed = 0.02f;
    watching_hero = 0;
    if (mystic[0x43] == 1) {
        watching_hero = 1;
        if (vec_distance_xy((char *)mystic + 0x10, g_hero_state.x80) < 8 &&
            FastDiffRots(F(mystic, 0xF8), mat_fast_helper_a(g_hero_state.pos[0] - F(mystic, 0x10),
                                                       g_hero_state.pos[1] - F(mystic, 0x14))) < 1.57079649f) {
            if (FastVecLength(g_hero_state.x110) > 0.01f)
                I(vars, 0x114) = 120;
            else
                math_fast_float_d(vars + 0x114);
        } else if (I(vars, 0x114)) {
            I(vars, 0x114) = 0;
            qcopy(vars + 0x100, g_hero_state.pos);
        }
        if (math_fast_float_d(vars + 0x118)) {
            I(vars, 0x118) = FloatToInt(math_random_float_range(180, 300));
            angle = FastAddRotations(F(mystic, 0xF8), math_random_float_range(-90, 90) * 0.0174532942f);
            pitch = math_random_float_range(0, 30) * 0.0174532942f;
            vec_build_spherical_offset(vars + 0x100, 6, angle, pitch);
            FastVecAdd(vars + 0x100, vars + 0x100, mystic + 0x10);
        }
        if (I(vars, 0x114)) {
            qcopy(look_target, g_hero_state.pos);
            blend_speed = 0.04f;
        } else
            qcopy(look_target, vars + 0x100);
    }
    if (watching_hero) {
        qcopy(head_pos, mystic + 0x10);
        head_pos[2] += 2;
        FastVecSub(to_target, look_target, head_pos);
        yaw = fast_subtract_rotations(mat_fast_helper_a(to_target[0], to_target[1]), F(mystic, 0xF8));
        pitch = -mat_fast_helper_a(vec_length_xy(to_target), to_target[2]);
        if (yaw > 1.57079649f)
            yaw = 1.57079649f;
        else if (yaw < -1.57079649f)
            yaw = -1.57079649f;
        if (pitch > 0.52359885f)
            pitch = 0.52359885f;
        else if (pitch < -0.52359885f)
            pitch = -0.52359885f;
        F(vars, 0x64) = pitch;
        F(vars, 0x68) = yaw * 0.6f;
        F(vars, 0xE8) = yaw * 0.4f;
    }
    if (g_unlocked_item_flags[0])
        F(vars, 0x70) = 2.75f;
    moby_update_eased_node(mystic, vars, 0, blend_speed, blend_weight);
    moby_update_eased_node(mystic, vars + 0x80, 1, blend_speed, blend_weight);
}

#undef I
#undef H
#undef F
#undef QUANTITY
#undef PRICE
