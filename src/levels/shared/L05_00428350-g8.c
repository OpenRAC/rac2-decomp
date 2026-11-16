#include "include_asm.h"
#include "common.h"

/* The two small-data words below are reached through $gp in ordinary flow, not
   in a delay slot, so this unit has to be the -G8 sibling of L05_00428350.c. */
extern int g_ship_state __attribute__((sda));

extern int g_ship_transition_timer __attribute__((sda));

/* Three per-slot tables indexed by the state's slot number. Each is an incomplete sda array:
   cc1 then keeps every table address as one `la`, which the assembler expands to an adjacent
   absolute lui/addiu pair, while D_L05_001B157C (sized) is reached through $gp. */
extern float g_expanding_effect_scales[] __attribute__((sda));
extern int g_expanding_effect_alphas[] __attribute__((sda));
extern int g_blast_slot_used[] __attribute__((sda));
extern float g_limited_blast_count __attribute__((sda));
extern char g_origin_vec[];
extern float fast_vec_dist(void *, void *);
extern int FastDecTimer(void *);
extern void moby_mark_spawned(void *);
extern void gfx_add_draw_callback_second(void *, void *);
extern void DrawExpandingBillboardEffect(void *);

extern char *g_path_l05_entry_table MACRO_ADDR;
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern int g_current_map_index __attribute__((sda));
extern int hero_get_state_value_b(void);
extern float g_cam_look_a_x __attribute__((sda));
extern float g_cam_look_a_y __attribute__((sda));
extern float g_cam_look_a_z __attribute__((sda));
extern float g_cam_look_b_y __attribute__((sda));
extern float g_cam_look_b_z __attribute__((sda));
extern float g_cam_look_b_x __attribute__((sda));
extern float g_cam_look_c __attribute__((sda));
extern float g_cam_look_d_spring_length __attribute__((sda));
extern float g_cam_second_b_x __attribute__((sda));
extern float g_cam_second_b_y __attribute__((sda));
extern float g_cam_second_b_z __attribute__((sda));
extern float g_cam_first_b_x __attribute__((sda));
extern float g_cam_first_b_y __attribute__((sda));
extern float g_cam_first_b_z __attribute__((sda));
extern float g_cam_first_a_x __attribute__((sda));
extern float g_cam_first_a_y __attribute__((sda));
extern float g_cam_first_a_z __attribute__((sda));
extern float g_cam_param_c_alt __attribute__((sda));
extern float g_cam_param_d_alt __attribute__((sda));
extern float g_cam_third_b_y __attribute__((sda));
extern float g_cam_third_b_x __attribute__((sda));
extern float g_cam_third_b_z __attribute__((sda));
extern float g_cam_third_a_x __attribute__((sda));
extern float g_cam_third_a_y __attribute__((sda));
extern float g_cam_third_a_z __attribute__((sda));
extern float g_cam_third_c __attribute__((sda));
extern float g_cam_third_d __attribute__((sda));
extern float g_cam_second_look_a_x __attribute__((sda));
extern float g_cam_second_look_a_y __attribute__((sda));
extern float g_cam_second_look_a_z __attribute__((sda));
extern float g_cam_second_look_b_y __attribute__((sda));
extern float g_cam_second_look_b_z __attribute__((sda));
extern float g_cam_second_look_b_x __attribute__((sda));
extern float g_cam_second_look_d __attribute__((sda));
extern float g_cam_pitch_param_first __attribute__((sda));
extern float g_cam_pitch_param_second __attribute__((sda));
extern float g_cam_pitch_param_third __attribute__((sda));
extern float g_cam_yaw_param_first __attribute__((sda));
extern float g_cam_yaw_param_second __attribute__((sda));
extern float g_cam_yaw_param_third __attribute__((sda));
extern float g_cam_param_c_default __attribute__((sda));
extern float g_cam_param_d_default __attribute__((sda));

/* The look record reached through the object's model entry: eight floats from +0x240. */
typedef struct {
    char pad[0x240];
    float a[3];
    float b[3];
    float c, d;
} LookSettings_L05_00442880;

/* The parameter block at +0x50 of the object's +0x70 record. */
typedef struct {
    float a[3];
    float b[3];
    char pad[0x74 - 0x18];
    float c, d;
} Params_L05_00442880;

typedef struct {
    char pad[0x50];
    Params_L05_00442880 params;
} Record_L05_00442880;

/* Reports 1 while the second word is set; otherwise whether the first word,
   minus two, is below two as an unsigned value. */
int cam_is_mode_active(void)
{
    if (g_ship_transition_timer != 0)
        return 1;
    return (unsigned int)(g_ship_state - 2) < 2;
}

/* On the first pass seeds the slot's speed and timer, then picks the state's +0x40 rate from
   the distance to D_L05_001B96C0; afterwards either chains func_L05_00428518 or releases the
   slot and drops the live count. */
void expanding_effect_update(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (!*(unsigned char *)(object + 0x20)) {
        g_expanding_effect_scales[*(int *)(state + 0x3C)] = 0.01f;
        g_expanding_effect_alphas[*(int *)(state + 0x3C)] = 0x80;
        *(unsigned char *)(object + 0x20) = 1;
        if (fast_vec_dist(object + 0x10, g_origin_vec) > 200.0f)
            *(float *)(state + 0x40) = 4.0f;
        else if (fast_vec_dist(object + 0x10, g_origin_vec) > 100.0f)
            *(float *)(state + 0x40) = 2.0f;
        else if (fast_vec_dist(object + 0x10, g_origin_vec) > 25.0f)
            *(float *)(state + 0x40) = 1.0f;
        else if (fast_vec_dist(object + 0x10, g_origin_vec) > 0.0f)
            *(float *)(state + 0x40) = 0.5f;
    }
    if (!FastDecTimer(state)) {
        FastDecTimer(state + 4);
        gfx_add_draw_callback_second(DrawExpandingBillboardEffect, object);
    } else {
        g_blast_slot_used[*(int *)(state + 0x3C)] = 0;
        g_limited_blast_count -= 1.0f;
        moby_mark_spawned(object);
    }
}

/* Loads the default look, then one of three parameter sets: the first when
   func_L05_00379F38 reports set (its middle vector depends on D_001A79F0 == 15), the
   second (which also overrides the look) when D_001A79F0 is 15, the third otherwise. The
   struct field stores let the scheduler hoist the global loads past them as retail does. */
void cam_load_parameter_set(char *object)
{
    Record_L05_00442880 *record = *(Record_L05_00442880 **)(object + 0x70);
    Params_L05_00442880 *params = &record->params;
    char *entry = *(char **)(g_path_l05_entry_table + *(short *)(object + 0x84) * 32 + 0x1C);
    LookSettings_L05_00442880 *look =
        *(LookSettings_L05_00442880 **)(g_feltzin_target_mobys + (*(int *)(entry + 0x20) << 8) + 0x68);

    look->a[0] = g_cam_look_a_x;
    look->a[1] = g_cam_look_a_y;
    look->a[2] = g_cam_look_a_z;
    look->b[1] = g_cam_look_b_y;
    look->b[2] = g_cam_look_b_z;
    look->b[0] = g_cam_look_b_x;
    look->c = g_cam_look_c;
    look->d = g_cam_look_d_spring_length;
    if (hero_get_state_value_b()) {
        if (g_current_map_index == 15) {
            params->b[0] = g_cam_second_b_x;
            params->b[1] = g_cam_second_b_y;
            params->b[2] = g_cam_second_b_z;
        } else {
            params->b[0] = g_cam_first_b_x;
            params->b[1] = g_cam_first_b_y;
            params->b[2] = g_cam_first_b_z;
        }
        params->a[0] = g_cam_first_a_x;
        params->a[1] = g_cam_first_a_y;
        params->a[2] = g_cam_first_a_z;
        params->c = g_cam_param_c_alt;
        params->d = g_cam_param_d_alt;
    } else if (g_current_map_index == 15) {
        params->b[0] = g_cam_third_b_x;
        params->b[1] = g_cam_third_b_y;
        params->b[2] = g_cam_third_b_z;
        record->params.a[0] = g_cam_third_a_x;
        params->a[1] = g_cam_third_a_y;
        params->a[2] = g_cam_third_a_z;
        params->c = g_cam_third_c;
        params->d = g_cam_third_d;
        look->a[0] = g_cam_second_look_a_x;
        look->a[1] = g_cam_second_look_a_y;
        look->a[2] = g_cam_second_look_a_z;
        look->b[1] = g_cam_second_look_b_y;
        look->b[2] = g_cam_second_look_b_z;
        look->b[0] = g_cam_second_look_b_x;
        look->c = g_cam_look_c;
        look->d = g_cam_second_look_d;
    } else {
        params->b[0] = g_cam_pitch_param_first;
        params->b[1] = g_cam_pitch_param_second;
        params->b[2] = g_cam_pitch_param_third;
        record->params.a[0] = g_cam_yaw_param_first;
        params->a[1] = g_cam_yaw_param_second;
        params->a[2] = g_cam_yaw_param_third;
        params->c = g_cam_param_c_default;
        params->d = g_cam_param_d_default;
    }
}

/* A moby in the level's list, linked through +0x28 and tagged by the class id at +0xAA. */
typedef struct ListMoby_0042C928 {
    char pad0[0x28];
    struct ListMoby_0042C928 *next;
    char pad2C[0x7E];
    short oclass;
} ListMoby_0042C928;
extern u8 g_level_progress_flags[] MACRO_ADDR;
extern int D_001A79F0_1;
extern char *g_hero_moby NOT_SDA;
extern float g_collectible_spin_x __attribute__((sda));
extern float g_collectible_spin_y __attribute__((sda));
extern float g_collectible_spin_z __attribute__((sda));
extern ListMoby_0042C928 *g_pickup_first_moby __attribute__((sda));
extern ListMoby_0042C928 *g_moby_l05_list_head;
extern char *CreateMoby(s32 a0);
extern float math_random_angle(void);
extern void moby_init_randomized_vars(char *a0);
extern void set_moby_color(char *a0, s32 a1, s32 a2, s32 a3);

/* Creates a collectible of class 0x126C at a position, unless that one has already been collected. */
char *pickup_spawn_if_not_taken(float *pos, u32 kind, s32 a2, s32 a3)
{
    char *moby;
    char *vars;
    ListMoby_0042C928 *p;
    u8 *collected = g_level_progress_flags;

    if (kind >= 4 || collected[kind + (D_001A79F0_1 << 2)] != 0)
        return 0;
    moby = CreateMoby(0x126C);
    if (moby != 0) {
        float x, y, z, r;

        vars = *(char **)(moby + 0x68);
        *(long *)(moby + 0x38) = *(long *)(g_hero_moby + 0x38);
        qcopy(moby + 0x10, pos);
        *(s16 *)(moby + 0x32) = 0x40;
        *(u8 *)(moby + 0x30) = 0x40;
        *(u8 *)(moby + 0x31) = 1;
        *(u32 *)vars = kind;
        qcopy(vars + 0x10, moby + 0x10);
        *(float *)(vars + 0x1C) = *(float *)(moby + 0xF8);
        *(float *)(moby + 0xF0) = math_random_angle();
        *(float *)(moby + 0xF4) = math_random_angle();
        *(float *)(moby + 0xF8) = math_random_angle();
        r = math_random_angle();
        x = g_collectible_spin_x;
        y = g_collectible_spin_y;
        z = g_collectible_spin_z;
        *(float *)(moby + 0xFC) = r;
        *(s32 *)(vars + 8) = a3;
        *(s32 *)(vars + 4) = a2;
        x *= 0.00029088825f;
        y *= 0.00029088825f;
        z *= 0.00029088825f;
        *(float *)(vars + 0x60) = z;
        *(float *)(vars + 0x68) = x;
        *(float *)(vars + 0x64) = y;
        *(u8 *)(moby + 0x20) = 1;
        moby_init_randomized_vars(moby);
        set_moby_color(moby, 0x82, 0x82, 0x82);
        if (g_pickup_first_moby == 0) {
            for (p = g_moby_l05_list_head; p != 0; p = p->next) {
                if (p->oclass == 0xFBF)
                    g_pickup_first_moby = p;
            }
        }
    }
    return moby;
}

extern float g_cam_init_pos_x __attribute__((sda));
extern float g_cam_init_pos_y __attribute__((sda));
extern float g_cam_init_pos_z __attribute__((sda));
extern float g_cam_chase_goal_rate __attribute__((sda));
extern int g_ship_horizontal_input_ramp __attribute__((sda));
extern int g_ship_vertical_input_ramp __attribute__((sda));
extern void vec_clear_128(void *a0);
extern void cam_load_entry_vectors(void *a0);
extern void gfx_set_clamped_view_distance(float a0);
extern void func_L05_003D1E20(void);
extern void ship_save_settings(void);

typedef struct Block_00441D40 {
    float f00, f04, f08, f0C, f10, f14;
    int f18;
    short f1C;
    u8 f1E, f1F;
    int pad20;
    int f24;
    char pad28[0x28];
    char v50[0x10];
    char v60[0x10];
    int f70;
    float f74;
    float f78;
} Block_00441D40;

typedef struct Tail_00441D40 {
    char pad0[4];
    short f04;
    short f06;
    char pad8[4];
    short f0C;
    char padE[2];
    short f10;
} Tail_00441D40;

typedef struct State_00441D40 {
    float pos[3];
    int pad0C;
    char v10[0x30];
    int f40;
    int f44;
    char pad48[8];
    Block_00441D40 blk;
    char padCC[8];
    Tail_00441D40 tail;
} State_00441D40;

typedef struct Entry_00441D40 {
    char pad0[0x20];
    int index;
    char pad24[0x34];
    int f58;
} Entry_00441D40;

typedef struct Slot_00441D40 {
    char pad0[0x1C];
    Entry_00441D40 *entry;
} Slot_00441D40;

typedef struct ActorVars_00441D40 {
    char pad0[0x38];
    float rate;
    char pad3C[0x1D8];
    int f214;
} ActorVars_00441D40;

typedef struct Actor_00441D40 {
    char pad0[0x68];
    ActorVars_00441D40 *vars;
    char pad6C[0x94];
} Actor_00441D40;

typedef struct Object_00441D40 {
    char pad0[0x70];
    State_00441D40 *state;
    char pad74[0xA];
    short f7E;
    char pad80[4];
    short f84;
} Object_00441D40;

/* Sets up the starting state of the level's camera object: default position, blocks and rates. */
void cam_init_state(Object_00441D40 *object)
{
    State_00441D40 *state;
    State_00441D40 *state2;
    Block_00441D40 *blk;
    Tail_00441D40 *tail;
    Entry_00441D40 *entry;
    ActorVars_00441D40 *vars;
    Slot_00441D40 *table;
    char *actors;
    float rate;

    state = object->state;
    state->pos[0] = g_cam_init_pos_x;
    state->pos[1] = g_cam_init_pos_y;
    state->pos[2] = g_cam_init_pos_z;
    vec_clear_128(state->v10);
    state->f40 = 0;
    state->f44 = 0;

    state2 = object->state;
    blk = &state2->blk;
    blk->f00 = g_cam_yaw_param_first;
    blk->f04 = g_cam_yaw_param_second;
    blk->f08 = g_cam_yaw_param_third;
    blk->f74 = g_cam_param_c_default;
    blk->f78 = g_cam_param_d_default;
    blk->f0C = g_cam_pitch_param_first;
    blk->f10 = g_cam_pitch_param_second;
    blk->f14 = g_cam_pitch_param_third;
    blk->f70 = 0;
    blk->f1C = 0;
    blk->f18 = 0;
    blk->f24 = 0;
    blk->f1E = 0;
    blk->f1F = 0;
    vec_clear_128(state2->blk.v50);
    vec_clear_128(state2->blk.v60);
    cam_load_entry_vectors(object);
    gfx_set_clamped_view_distance(4096.0f);

    table = (Slot_00441D40 *)g_path_l05_entry_table;
    actors = g_feltzin_target_mobys;
    tail = &object->state->tail;
    tail->f06 = 0;
    tail->f0C = 0;
    tail->f10 = 0;
    tail->f04 = 0;
    rate = g_cam_chase_goal_rate * 0.016666668f;
    entry = table[object->f84].entry;
    entry->f58 = 0;
    vars = ((Actor_00441D40 *)(actors + (entry->index << 8)))->vars;
    vars->rate = rate;
    vars->f214 = -1;
    object->f7E = 0;
    g_ship_state = 0;
    func_L05_003D1E20();
    g_ship_horizontal_input_ramp = 0;
    g_ship_vertical_input_ramp = 0;
    ship_save_settings();
}

extern float g_stream_ring_radius_a __attribute__((sda));
extern float g_stream_ring_radius_b __attribute__((sda));
extern float g_stream_span_a __attribute__((sda));
extern float g_stream_span_b __attribute__((sda));
extern float g_stream_layer_width_a __attribute__((sda));
extern float g_stream_layer_length_a __attribute__((sda));
extern float g_stream_layer_width_b __attribute__((sda));
extern float g_stream_layer_length_b __attribute__((sda));
extern float g_stream_layer_width_c __attribute__((sda));
extern float g_stream_layer_length_c __attribute__((sda));
extern float g_stream_layer_width_d __attribute__((sda));
extern float g_stream_layer_length_d __attribute__((sda));
extern float g_stream_scroll_u_a __attribute__((sda));
extern float g_stream_scroll_u_speed __attribute__((sda));
extern float g_stream_scroll_v_a __attribute__((sda));
extern float g_stream_scroll_v_speed __attribute__((sda));
extern float g_stream_scroll_w_a __attribute__((sda));
extern float g_stream_scroll_w_speed __attribute__((sda));
extern float g_stream_scroll_x_a __attribute__((sda));
extern float g_stream_scroll_x_speed __attribute__((sda));
extern float g_stream_scroll_y_a __attribute__((sda));
extern float g_stream_scroll_y_speed __attribute__((sda));
extern int g_stream_layer_param_a __attribute__((sda));
extern int g_stream_layer_param_b __attribute__((sda));
extern int g_stream_layer_param_c __attribute__((sda));
extern int g_stream_layer_param_d __attribute__((sda));
extern int g_stream_strip_texture_a __attribute__((sda));
extern int g_stream_strip_texture_b __attribute__((sda));
extern int g_stream_strip_texture_c __attribute__((sda));
extern int g_stream_strip_texture_d __attribute__((sda));
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void gfx_draw_tiled_ground_quad(void *);
extern void gfx_build_textured_ring_strip(void *, void *, float, float, int, int,
                           float, float, float, float);

/* Advances five wrapped phases, then draws four layers along the actor heading. */
void gfx_draw_scrolling_stream_layers(u8 *actor)
{
    float direction[4] __attribute__((aligned(16)));
    g_stream_scroll_u_a += g_stream_scroll_u_speed;
    if (g_stream_scroll_u_a > 7.0f) g_stream_scroll_u_a -= 7.0f;
    else if (g_stream_scroll_u_a < -7.0f) g_stream_scroll_u_a += 7.0f;
    g_stream_scroll_v_a += g_stream_scroll_v_speed;
    if (g_stream_scroll_v_a > 7.0f) g_stream_scroll_v_a -= 7.0f;
    else if (g_stream_scroll_v_a < -7.0f) g_stream_scroll_v_a += 7.0f;
    g_stream_scroll_w_a += g_stream_scroll_w_speed;
    if (g_stream_scroll_w_a > 7.0f) g_stream_scroll_w_a -= 7.0f;
    else if (g_stream_scroll_w_a < -7.0f) g_stream_scroll_w_a += 7.0f;
    g_stream_scroll_x_a += g_stream_scroll_x_speed;
    if (g_stream_scroll_x_a > 7.0f) g_stream_scroll_x_a -= 7.0f;
    else if (g_stream_scroll_x_a < -7.0f) g_stream_scroll_x_a += 7.0f;
    g_stream_scroll_y_a += g_stream_scroll_y_speed;
    if (g_stream_scroll_y_a > 7.0f) g_stream_scroll_y_a -= 7.0f;
    else if (g_stream_scroll_y_a < -7.0f) g_stream_scroll_y_a += 7.0f;
    direction[0] = math_fast_sin_or_cos_a(*(float *)(actor + 0xF8));
    direction[1] = math_fast_sin_or_cos_b(*(float *)(actor + 0xF8));
    direction[2] = 0.0f;
    gfx_draw_tiled_ground_quad(actor);
    gfx_build_textured_ring_strip(actor + 0x10, direction, g_stream_span_b, g_stream_ring_radius_b, g_stream_strip_texture_b, g_stream_layer_param_b,
                     g_stream_layer_length_d * 0.03225806355f,
                     g_stream_layer_width_d * 0.2f, 0.0f, g_stream_scroll_u_a);
    gfx_build_textured_ring_strip(actor + 0x10, direction, g_stream_span_a, g_stream_ring_radius_a, g_stream_strip_texture_a, g_stream_layer_param_a,
                     g_stream_layer_length_a * 0.03225806355f,
                     g_stream_layer_width_a * 0.2f, g_stream_scroll_w_a, g_stream_scroll_u_a);
    gfx_build_textured_ring_strip(actor + 0x10, direction, g_stream_span_a, g_stream_ring_radius_a, g_stream_strip_texture_d, g_stream_layer_param_d,
                     g_stream_layer_length_c * 0.03225806355f,
                     g_stream_layer_width_c * 0.2f, g_stream_scroll_x_a, g_stream_scroll_v_a);
    gfx_build_textured_ring_strip(actor + 0x10, direction, g_stream_span_a, g_stream_ring_radius_a, g_stream_strip_texture_c, g_stream_layer_param_c,
                     g_stream_layer_length_b * 0.03225806355f,
                     g_stream_layer_width_b * 0.2f, g_stream_scroll_y_a, g_stream_scroll_u_a);
}
