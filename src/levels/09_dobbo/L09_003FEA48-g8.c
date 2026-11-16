#include "common.h"

extern f32 g_dobbo_fast_move_speed __attribute__((sda));
extern f32 g_dobbo_slow_move_speed __attribute__((sda));
extern void func_L08_00316678(char *a, s32 b, s32 c, s32 d);

typedef union {
    u16 h;
    s32 w;
} U16S32;

extern U16S32 g_dobbo_timer_value __attribute__((sda));
extern void func_2EA110(char *p);

/* Switches the creature to its fast-moving animation and sets its turn speed. */
void dobbo_start_fast_move_anim(char *moby, s32 param) {
    char *self = moby;
    f32 speed = g_dobbo_fast_move_speed * 0.0166666675f;
    char *vars = *(char **)(self + 0x68);
    *(f32 *)(vars + 0x1D4) = 3.0f;
    *(f32 *)(vars + 0x1D0) = speed;
    if (*(u8 *)(self + 0x43) == 7) {
        return;
    }
    func_L08_00316678(moby, 7, 0, param);
}

/* Switches the creature to its slow-moving animation and sets its turn speed. */
void dobbo_start_slow_move_anim(char *moby, s32 param) {
    char *self = moby;
    f32 speed = g_dobbo_slow_move_speed * 0.0166666675f;
    char *vars = *(char **)(self + 0x68);
    *(f32 *)(vars + 0x1D4) = 1.75f;
    *(f32 *)(vars + 0x1D0) = speed;
    if (*(u8 *)(self + 0x43) == 6) {
        return;
    }
    func_L08_00316678(moby, 6, 0, param);
}

/* Ticks the object's two timers and its age counter, refilling the timers when needed. */
void dobbo_tick_timers_age(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    u16 age;
    if (*(s16 *)(vars + 0x270) != 0
        || (*(s32 *)(vars + 0x234) == 1 && *(s16 *)(vars + 0x26C) < g_dobbo_timer_value.w / 2)) {
        *(u16 *)(vars + 0x26C) = g_dobbo_timer_value.h;
        *(s16 *)(vars + 0x270) = 0;
    }
    func_2EA110(vars + 0x26C);
    func_2EA110(vars + 0x26E);
    age = *(u16 *)(self + 0x96);
    if (age < 0xFFFF) {
        *(u16 *)(self + 0x96) = age + 1;
    }
}


/* Small-data handles: the resident mode word (-0x7600 -> 0x001A79F0), the resident
   release word (-0x5FB0 -> 0x001A9040) and the level's record table (0x386C ->
   0x001B285C), all read with $gp pinned at 0x001AEFF0. */
extern s32 g_release_effect_state __attribute__((sda));
extern s32 g_release_busy_flag __attribute__((sda));
extern char *g_moby_record_table __attribute__((sda));

extern s32 func_323340(char *a0, char *a1, s32 a2);
extern int moby_is_hero_or_special(char *a0);
extern void group_flag_peers(char *a0);
extern void func_326368(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);

/* Drops the record the sub-object points at, once, when the resident mode word says 9,
   then rebuilds the sub-object's effect with both blend weights at zero. */
void record_release_rebuild_effect(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    s16 record_index;

    if (func_323340(moby, vars + 0x160, 0) != 0) {
        if (g_release_effect_state == 9) {
            record_index = *(s16 *)(vars + 0x1D0);
            if (record_index != -1) {
                if (moby_is_hero_or_special(g_moby_record_table + (record_index << 8)) == 0) {
                    g_release_busy_flag = 0;
                }
                *(s16 *)(vars + 0x1D0) = -1;
            }
        }
        group_flag_peers(moby);
    }
    func_326368(moby, *(s32 *)(vars + 0x448), 0, 0, 0.0f, 0.0f);
}

/* The same resident mode word, read here as an ordinary global (lui + lw) rather than
   through $gp: the two references name the same word, one small and one not. */
extern s32 g_current_map_index;

extern void dobbo_wandering_init_vars(void);
extern float fast_vec_dist(char *a0, char *a1);
extern void moby_update_ground_check(void *a0);
extern s32 moby_apply_damage_to_object(char *a0, char *a1, s32 a2);
extern void dobbo_alert_wandering_group(char *a0);
extern void dobbo_destroy_with_debris(char *a0);
extern s32 weapon_select_aim_target(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern char g_camera_l09_position[];

/* Releases the record the sub-object holds once the resident mode word says 9, then
   rebuilds the sub-object's effect. */
void dobbo_update_release_record(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    s32 hit_level;
    s16 record_index;

    if (*(u8 *)(self + 0x20) == 0) {
        dobbo_wandering_init_vars();
    }
    if (*(u8 *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, g_camera_l09_position) < 24.0f) {
            moby_update_ground_check(self);
            *(u8 *)(self + 0x6F) = 0x16;
        }
    }
    hit_level = moby_apply_damage_to_object(self, vars + 0x50, 0);
    if (g_current_map_index == 9) {
        record_index = *(s16 *)(vars + 0xC0);
        if (record_index != -1) {
            if (moby_is_hero_or_special(g_moby_record_table + (record_index << 8)) == 0) {
                g_release_busy_flag = 0;
            }
            *(s16 *)(vars + 0xC0) = -1;
        }
    }
    if (hit_level != 0) {
        dobbo_alert_wandering_group(self);
        if (hit_level >= 4) {
            dobbo_destroy_with_debris(self);
        }
    }
    if (*(u8 *)(self + 0x95) != 3 && *(u8 *)(self + 0x95) != 4) {
        *(s16 *)(vars + 0x334) = weapon_select_aim_target(self, *(s32 *)(vars + 0x230), 0, 0, 16.0f, 0.0f);
    }
}

extern void dobbo_init_enemy_vars(void);
extern void dobbo_alert_group_wake_first(char *a0, s32 a1);

/* The same release as func_L09_00404E58, with this level's own calls: when the
   resident mode word says 9 the record the sub-object holds is released, then the
   record's update runs with the value func_002B0ED8 returned, and the sub-object's
   effect is rebuilt from the sub-object's own index and position. */
void dobbo_update_large_release_record(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    s32 hit_level;
    s16 record_index;

    if (*(u8 *)(self + 0x20) == 0) {
        dobbo_init_enemy_vars();
    }
    if (*(u8 *)(self + 0x31) != 0) {
        if (fast_vec_dist(self + 0x10, g_camera_l09_position) < 48.0f) {
            moby_update_ground_check(self);
            *(u8 *)(self + 0x6F) = 0x2D;
        }
    }
    hit_level = moby_apply_damage_to_object(self, vars + 0x50, 0);
    if (g_current_map_index == 9) {
        record_index = *(s16 *)(vars + 0xC0);
        if (record_index != -1) {
            if (moby_is_hero_or_special(g_moby_record_table + (record_index << 8)) == 0) {
                g_release_busy_flag = 0;
            }
            *(s16 *)(vars + 0xC0) = -1;
        }
    }
    dobbo_alert_group_wake_first(self, hit_level);
    weapon_select_aim_target(self, *(s32 *)(vars + 0x28C), 0, 0, *(f32 *)(vars + 0x24C), 0.0f);
}

/* The walks below read the group table of id lists absolute. The group count and the entity base
   are plain externs here, which come out as bare `lui`/`lw` pairs in ordinary flow and as $gp
   loads in a branch delay slot; the base takes a second name because D_L09_001B285C above is the
   $gp form. */
extern s32 g_max_l09_group_id;

extern u8 *D_L09_001B285C_1;

extern u16 *g_track_entry_table[];

/* The vector the scaled copy starts from: small data, so its address is a $gp offset. */
extern char g_dobbo_glow_offset[1] __attribute__((sda));

/* The colour pair func_00283D38 blends. */
extern s32 g_dobbo_glow_colors[2];

extern void FastVecScale(char *, char *, f32);

extern void transform_vector(char *, char *, char *);

extern s32 FastTweenColor(s32, s32, f32);

extern void gfx_l00_draw_billboard_quad(char *, s32, f32, f32);

typedef struct {
    s32 a, b;
} ColorPair;

/* The object's blended colour word: a member store, which the scheduler knows cannot alias the
   scalar global D_L09_001B2388 (a plain cast store it must keep in front of that load). */
typedef struct {
    u8 pad[0x78];
    s32 colour;
} TintedObject;

extern ColorPair g_dobbo_tint_colors[2];

extern s32 g_frame_l09_counter;

extern f32 FastAddRotations(f32, f32);

extern f32 math_fast_sin_or_cos_b(f32);

extern void moby_transform_joint_point(u8 *, s32, u8 *);

extern void gfx_add_draw_callback_first(void *, u8 *);

void dobbo_draw_pulsing_glows(u8 *a0);

/* Steps the object's pulse: the angle at +0x348 advances by 2*pi/30 through the resident angle
   blend, its sine is mapped to 0..1 and kept at +0x34C, and the colour pair D_L09_001B1400 is
   blended by it into the object's word at +0x78. When the state's stamp (+0x350) differs from
   D_L09_001B2388, every visible class-0xD90 entity of the object's group that is not in state
   0xFE or 0xFD gets its point refreshed (func_0029FC20, selector 0) into its vector at +0x240
   and the same stamp; then func_L09_00405490 is registered as the object's callback. */
void dobbo_update_pulsing_tint(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    ColorPair color = g_dobbo_tint_colors[0];
    u16 *id_ptr;
    u8 *entity;
    u8 *entity_vars;
    f32 angle;
    f32 wave;

    angle = FastAddRotations(*(f32 *)(state + 0x348), 0.20943954f);
    *(f32 *)(state + 0x348) = angle;
    wave = math_fast_sin_or_cos_b(angle) * 0.5f + 0.5f;
    *(f32 *)(state + 0x34C) = wave;
    ((TintedObject *)moby)->colour = FastTweenColor(color.a, color.b, wave);
    if (*(s32 *)(state + 0x350) != g_frame_l09_counter) {
        for (id_ptr = g_track_entry_table[moby[0x21]];
             moby[0x21] != 0xFF && moby[0x21] <= g_max_l09_group_id && id_ptr != 0 &&
             ((id_ptr != 0 && (s16)id_ptr[-1] >= 0) || id_ptr == g_track_entry_table[moby[0x21]]);
             id_ptr++) {
            entity = D_L09_001B285C_1 + ((*id_ptr & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity[0x31] != 0 && *(s16 *)(entity + 0xAA) == 0xD90 /* moby class 3472 */) {
                if (entity[0x20] != 0xFE) {
                    if (entity[0x20] != 0xFD) {
                        entity_vars = *(u8 **)(entity + 0x68);
                        moby_transform_joint_point(entity, 0, entity_vars + 0x240);
                        *(s32 *)(entity_vars + 0x350) = g_frame_l09_counter;
                    }
                }
            }
        }
        gfx_add_draw_callback_first((void *)dobbo_draw_pulsing_glows, moby);
    }
}

/* Callback of func_L09_004052F8 for every class-0xD90 entity of the object's group that is not
   hidden (byte 0x31) or in state 0xFE or 0xFD: scales the sub-object's vector by its float at
   +0x344, transforms it by the matrix at +0x240, blends the colour pair by the float at +0x34C
   and hands the result to func_L00_00325AE8 with the +0x344 float scaled by 0.2. */
void dobbo_draw_pulsing_glows(u8 *moby) {
    f32 point[4];
    u16 *id_ptr;
    u16 *group_list;
    u8 *entity;
    u8 *entity_vars;
    s32 color;

    if (moby[0x21] == 0xFF)
        return;
    group_list = g_track_entry_table[moby[0x21]];
    if (group_list == 0)
        return;
    for (id_ptr = group_list;
         moby[0x21] != 0xFF && moby[0x21] <= g_max_l09_group_id && id_ptr != 0 &&
         ((id_ptr != 0 && (s16)id_ptr[-1] >= 0) || id_ptr == g_track_entry_table[moby[0x21]]);
         id_ptr++) {
        entity = D_L09_001B285C_1 + ((*id_ptr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        if (entity[0x31] != 0 && *(s16 *)(entity + 0xAA) == 0xD90 /* moby class 3472 */) {
            if (entity[0x20] != 0xFE) {
                if (entity[0x20] != 0xFD) {
                    entity_vars = *(u8 **)(entity + 0x68);
                    FastVecScale((char *)point, g_dobbo_glow_offset, *(f32 *)(entity_vars + 0x344));
                    transform_vector((char *)point, (char *)point, (char *)(entity_vars + 0x240));
                    color = FastTweenColor(g_dobbo_glow_colors[0], g_dobbo_glow_colors[1],
                                      *(f32 *)(entity_vars + 0x34C));
                    gfx_l00_draw_billboard_quad((char *)point, color, *(f32 *)(entity_vars + 0x344) * 0.2f, 0.08f);
                }
            }
        }
    }
}

extern int func_316A28(int a);
extern int func_316A68(int a, int b);
extern void func_31F4D0(char *a0, int a1);
extern float func_2EB478(float a, float b);
extern float func_2EAA60(float a);
extern float func_2EAA78(float a);
extern int func_2EB5D0(float a);
extern void func_2EA750(float f12, void *a0, void *a1);
extern int g_dobbo_spin_anim_id __attribute__((sda));
extern int D_L09_001B15B8_4[] MACRO_ADDR;
extern float g_dobbo_spin_turn_rate __attribute__((sda));
extern float g_dobbo_spin_radius __attribute__((sda));
extern int g_dobbo_spin_scale __attribute__((sda));
extern u8 g_dobbo_spin_angle_base __attribute__((sda));

/* Spins a moving object around and sets its direction, facing and blend from its path values. */
void dobbo_update_spin_direction(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *velocity;
    float dir[3];
    int frame_offset;
    float scale;
    int anim_id;
    if (func_316A28(7)) {
        anim_id = g_dobbo_spin_anim_id;
    } else {
        anim_id = D_L09_001B15B8_4[1];
    }
    func_31F4D0(moby, anim_id);
    velocity = moby + 0xC0;
    *(float *)(vars + 0x10) = func_2EB478(*(float *)(vars + 0x10), g_dobbo_spin_turn_rate * 0.00029088825f);
    dir[0] = func_2EAA60(*(float *)(vars + 0x10)) * g_dobbo_spin_radius;
    dir[1] = func_2EAA78(*(float *)(vars + 0x10)) * g_dobbo_spin_radius;
    dir[2] = 0;
    scale = (float)g_dobbo_spin_scale;
    *(float *)(moby + 0xF0) = dir[0];
    *(float *)(moby + 0xF4) = dir[1];
    frame_offset = func_2EB5D0(scale * (*(float *)vars + *(float *)(vars + 4)) * 0.5f);
    *(u8 *)(moby + 0x23) = g_dobbo_spin_angle_base + frame_offset + func_316A68(-9, 9);
    *(u16 *)(moby + 0x34) |= 0x800;
    func_2EACD0(velocity, moby + 0xF0);
    func_2EA750(*(float *)vars, velocity, velocity);
    func_2EA750(*(float *)(vars + 4), moby + 0xD0, moby + 0xD0);
}

typedef struct { u8 pad[0x464]; u8 spent[1]; } L09_CellFlags;
extern L09_CellFlags g_dobbo_flags;
extern u8 g_moby_nibble_table[];
extern char *g_dobbo_point_table[] __attribute__((sda));
extern void func_317B40(int a0, int a1, int a2, int a3);

/* Updates the indicator on a linked object, lighting it up once the item it needs has been collected. */
void dobbo_update_item_indicator(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *linked;
    char *linked_vars;
    int item_id;
    int flags;
    s32 linked_index = *(s32 *)(vars + 0x64);

    if (linked_index == -1)
        return;
    linked = (char *)((linked_index << 8) + (int)g_moby_record_table);
    if (*(u8 *)(linked + 0x20) == 0xFE)
        return;
    if (*(u8 *)(linked + 0x20) == 0xFD)
        return;
    linked_vars = *(char **)(linked + 0x68);
    if (*(s32 *)(linked_vars + 0x70) == -1)
        return;
    if (*(s32 *)(vars + 0x50) != -1
        && (item_id = *(u16 *)((*(s32 *)(vars + 0x50) << 8) + (int)g_moby_record_table + 0xB2),
            g_dobbo_flags.spent[(s16)item_id] != 0
            || (flags = g_moby_nibble_table[((s16)item_id >> 1) + (g_current_map_index << 10)],
                (item_id & 1) ? (flags >> 4) & 7 : flags & 7) != 0)) {
        *(float *)((*(s32 *)(linked_vars + 0x70) << 7) + (int)g_dobbo_point_table[0] + 0x38) = 325.25f;
        func_317B40(*(s32 *)(vars + 0x4C), 1, 1, 1);
    } else {
        *(float *)((*(s32 *)(linked_vars + 0x70) << 7) + (int)g_dobbo_point_table[0] + 0x38) = 325.0f;
        func_317B40(*(s32 *)(vars + 0x4C), 0, 0, 0);
    }
}

extern s32 g_game_mode __attribute__((nosda));
extern u8 g_level_progress_flags[];
extern u8 g_collection_progress_flags[] __attribute__((sda));
extern void func_30C790(char *a0);
extern void dobbo_release_linked(char *a0);

/* Checks whether every requirement is met and, if so, releases the two linked objects and finishes. Returns 1 when done. */
s32 dobbo_release_linked_if_ready(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    s32 none;
    s32 linked_index;
    s32 item_id;

    if (g_game_mode == 0x31)
        return 0;
    if (*(s32 *)(vars + 0x2C) != -1) {
        char *linked = (char *)((*(s32 *)(vars + 0x2C) << 8) + (s32)g_moby_record_table);
        if (*(u8 *)(linked + 0x20) != 0xFE) {
            if (*(u8 *)(linked + 0x20) != 0xFD) {
                if (g_level_progress_flags[*(s32 *)*(char **)(linked + 0x68) + (g_current_map_index << 2)] == 0)
                    return 0;
            }
        }
    }
    if (*(s32 *)(vars + 0x7C) != -1) {
        char *linked = (char *)((*(s32 *)(vars + 0x7C) << 8) + (s32)g_moby_record_table);
        if (*(u8 *)(linked + 0x20) != 0xFE) {
            if (*(u8 *)(linked + 0x20) != 0xFD) {
                if (*(u8 *)(*(s32 *)*(char **)(linked + 0x68) + (s32)g_collection_progress_flags) == 0)
                    return 0;
            }
        }
    }
    linked_index = *(s32 *)(vars + 0x50);
    if (linked_index != -1) {
        item_id = *(u16 *)((linked_index << 8) + (s32)g_moby_record_table + 0xB2);
        if (g_dobbo_flags.spent[(s16)item_id] == 0) {
            s32 flags = g_moby_nibble_table[((s16)item_id >> 1) + (g_current_map_index << 10)];
            if (item_id & 1)
                flags = (flags >> 4) & 7;
            else
                flags = flags & 7;
            if (flags == 0)
                return 0;
        }
    }
    none = -1;
    linked_index = *(s32 *)(vars + 0x64);
    if (linked_index != none) {
        func_30C790((linked_index << 8) + g_moby_record_table);
        *(s32 *)(vars + 0x64) = none;
    }
    linked_index = *(s32 *)(vars + 0x68);
    if (linked_index != none) {
        func_30C790((linked_index << 8) + g_moby_record_table);
        *(s32 *)(vars + 0x68) = none;
    }
    dobbo_release_linked(moby);
    return 1;
}
