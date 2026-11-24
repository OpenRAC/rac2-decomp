/* func_L23_004177F8: boss set-up and per-frame refresh for Damosel orbit.
 * Quad v[10] reproduces retail's 0x100 frame; v[2..9] are never touched (allowed by owner
 * ruling of 8 November 2026, precedent L09_002F8BA0-g8.c).
 * The state->health store after i188 sets local-alloc so that 0.4 takes $f7 and 1.5708 $f3,
 * with sw 0x88 before swc1 0x60 as in retail. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));

typedef struct L23Class {
    char pad00[0x24];
    float scale;
} L23Class;

typedef struct L23Boss L23Boss;

typedef struct L23Moby {
    char pad00[0x10];
    Quad pos;
    unsigned char mode;
    char pad21[3];
    L23Class *cls;
    struct L23Moby *next;
    float scale;
    unsigned char alpha;
    char pad31;
    short colour;
    unsigned short flags;
    char pad36[0x68 - 0x36];
    void *vars;
    char pad6C[0x7C - 0x6C];
    short timer;
    char pad7E[0xAA - 0x7E];
    short kind;
    char padAC[0xC0 - 0xAC];
    Quad rot;
    char padD0[0x100 - 0xD0];
} L23Moby;

typedef struct L23Tint {
    char pad00[8];
    signed char r;
    char pad09;
    signed char g;
    char pad0B;
    signed char b;
} L23Tint;

struct L23Boss {
    char pad000[0x20];
    float health;
    short maxHealth;
    char pad026[0x50 - 0x26];
    float f50, f54, f58, f5C, f60;
    char pad064[0x80 - 0x64];
    float f80, f84;
    int flags88;
    char pad08C[0x150 - 0x8C];
    unsigned char b150;
    char pad151[0x170 - 0x151];
    float f170, f174;
    char pad178[4];
    float f17C;
    char pad180[8];
    int i188;
    char pad18C[0x1B7 - 0x18C];
    unsigned char b1B7;
    char pad1B8[0x230 - 0x1B8];
    int t230[(0x2F4 - 0x230) / 4];
    short pad2F4;
    short h2F6;
    char pad2F8[0x308 - 0x2F8];
    float f308, f30C, f310, f314;
    char pad318[4];
    int i31C;
    float f320, f324, f328, f32C, f330;
    short h334, h336, h338;
    char pad33A[0x358 - 0x33A];
    L23Moby *parts[10];
    char pad380[0x390 - 0x380];
    short h390;
    char pad392[6];
    short h398, h39A, h39C, h39E;
    char pad3A0[0x408 - 0x3A0];
    int i408;
    char pad40C[4];
    Quad m410[(0x570 - 0x410) / 16];
    char pad570[8];
    int i578;
    float f57C;
    char pad580[8];
    float f588;
    char pad58C[4];
    int i590, i594;
    char pad598[4];
    int i59C;
    char pad5A0[0x5B0 - 0x5A0];
    int i5B0;
    char pad5B4[0x5C4 - 0x5B4];
    int i5C4;
    float f5C8;
    int i5CC;
    float f5D0;
    char pad5D4[4];
    int i5D8;
    char pad5DC[0x608 - 0x5DC];
    int i608, i60C;
    L23Moby *m610, *m614;
    char pad618[8];
    L23Moby *m620, *m624;
};

typedef struct {
    char pad0[0x1E0];
    short f1E0;
    char pad1E2[0x1870 - 0x1E2];
    char f1870[0xC];
    int f187C;
    char pad1880[0x2290 - 0x1880];
    void *f2290;
    int f2294;
} L23Game;
typedef struct {
    char pad0[0x1A4];
    unsigned int f1A4;
} L23Pad;
extern int g_mothership_state_pair[2];
extern int g_boss_part_age_counter __attribute__((sda));
extern int g_boss_part_was_active __attribute__((sda));
extern int g_boss_camera_timer;
extern int g_boss_fight_timer;
extern int g_mothership_blast_reset_flag __attribute__((sda));
extern int g_charged_blast_fired_flag __attribute__((sda));
extern int g_charged_blast_armed_flag __attribute__((sda));
extern int g_charged_l23_blast_timer __attribute__((sda));
extern int g_boss_player_seen_flag;
extern int g_boss_damage_phase_started __attribute__((sda));
extern int g_enemy_effect_param;
extern float g_mothership_effect_radius;
extern float g_mothership_impact_param;
extern float g_mothership_state_param_a;
extern float g_mothership_knockback_scale __attribute__((sda));
extern int g_flying_enemy_active_flag __attribute__((sda));
extern float g_mothership_state_param_b;
extern float g_mothership_hit_speed;
extern int g_boss_part_hit_counter;
extern int g_selected_moby;
extern float g_mothership_initial_timer __attribute__((sda));
extern int g_boss_hud_stat_index;
extern int g_boss_hud_display_timer;
extern int g_mothership_reset_flag_b;
extern int g_mothership_reset_flag_a;
extern int g_enemy_relocate_count __attribute__((sda));
extern float g_mothership_surface_radius;
extern float g_boss_surface_height __attribute__((sda));
extern float g_mothership_max_health;
extern float g_mothership_hit_damage_scale;
extern float g_mothership_hit_damage_floor;
extern int g_mothership_slot_count;
extern int g_mothership_scan_slot_index __attribute__((sda));
extern float g_boss_second_measure_a __attribute__((sda));
extern float g_mothership_scale_factor __attribute__((sda));
extern int g_mothership_init_value_a __attribute__((sda));
extern int g_boss_hud_timer MACRO_ADDR;
extern L23Moby *g_mothership_boss_moby __attribute__((sda));
extern L23Moby *g_mothership_part_moby __attribute__((sda));
extern L23Moby *g_mothership_moby __attribute__((sda));
extern L23Moby *g_mothership_moby_begin, *g_mothership_moby_end, *g_mothership_moby_list;
extern int *g_path_piece_table;
extern L23Moby *g_mothership_effect_handles[4] MACRO_ADDR;
extern int g_mothership_init_values[4] MACRO_ADDR;
extern int g_mothership_scan_slots[4] SDATA(D_L23_001B1658);
extern Quad g_mothership_start_position SDATA(D_L23_001B13F0);
extern Quad g_boss_target_pos_a, g_boss_target_pos_b;
extern int g_mothership_beam_handles[8][3];
extern L23Moby *g_mothership_beam_end_handles[8][3];
extern Quad g_mothership_barrier_points[8][3];
extern L23Moby *g_mothership_crowd_mobys[];
extern unsigned char g_path_end_masks[0xFE0];
extern unsigned char g_hero_state[];
extern unsigned char g_pad_state[];
extern int math_fast_float_d(int *);
extern void func_001163A0(unsigned int);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void mothership_project_point_onto_surface(void *, float);
extern void moby_set_controller_speed_limits(L23Moby *, float, float, float, float);
extern void moby_set_state(L23Moby *, int, int);
extern void *memset(void *, int, unsigned int);
extern void mothership_link_touching_path_ends(L23Moby *);
extern void part_spawn_random_path_effects(L23Moby *);
extern void mothership_advance_scan_slot(L23Moby *);
extern void level_store_value_pair(int, int);
extern int mothership_call_helper_return_true(void);
extern int L23_DrawEncounterHud(void);
extern void cancel_hero_item_animation(void);
extern void release_moby_animation_slot(void *, void *);
extern int hero_l22_set_move_state(int, int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9(int, int);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_negate_and_forward(void *, void *, void *);
extern void UpdateShieldHitsAndStrength(L23Moby *);

/* Initialize the encounter objects and refresh their shared presentation state. */
void mothership_update(L23Moby *moby) {
    Quad vecs[10];
    L23Boss *state = moby->vars;
    L23Moby *obj;
    L23Moby *scan;
    int i, j, class_id, crowd_count, part_count, mode;
    float health;

    math_fast_float_d(&g_boss_hud_timer);
    if (moby->mode == 0) {
        g_mothership_state_pair[1] = 0;
        g_mothership_state_pair[0] = 0;
        g_boss_part_age_counter = 1;
        g_boss_part_was_active = 0;
        g_boss_camera_timer = 0;
        g_boss_fight_timer = 0;
        g_mothership_blast_reset_flag = 0;
        g_charged_blast_fired_flag = 0;
        g_charged_blast_armed_flag = 0;
        g_charged_l23_blast_timer = 0;
        g_boss_player_seen_flag = 0;
        g_boss_damage_phase_started = 0;
        state->m620 = 0;
        state->m624 = 0;
        g_flying_enemy_active_flag = 1;
        g_mothership_boss_moby = moby;
        state->i60C = 0;
        g_enemy_effect_param = state->i31C;
        g_mothership_effect_radius = state->f308;
        g_mothership_impact_param = state->f30C;
        g_mothership_state_param_a = state->f310;
        g_mothership_knockback_scale = state->f314;
        if (state->h334 > 8) state->h334 = 8;
        state->h336 = 2;
        g_mothership_state_param_b = state->f330;
        g_mothership_hit_speed = (float)state->h338;
        g_boss_part_hit_counter = 0;
        g_selected_moby = 0;
        state->i608 = 0;
        state->f5D0 = g_mothership_initial_timer;
        state->f5C8 = g_mothership_initial_timer;
        state->i5CC = 0;
        state->i5D8 = 0;
        state->i5B0 = 0;
        state->i5C4 = 0;
        state->i594 = 0;
        state->i590 = 0;
        state->i59C = 0;
        g_path_piece_table = state->t230;
        state->b1B7 = 1;
        func_001163A0(T1_COUNT);
        g_boss_hud_stat_index = -1;
        g_boss_hud_display_timer = 0;
        state->i408 = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                qzero(&vecs[0]);
                g_mothership_beam_handles[i][j] = 0;
                g_mothership_beam_end_handles[i][j] = 0;
                qcopy(&g_mothership_barrier_points[i][j], &vecs[0]);
            }
        }
        for (i = 0; i < 4; i++) g_mothership_effect_handles[i] = 0;
        i = 0;
        g_mothership_reset_flag_b = 0;
        g_mothership_reset_flag_a = 0;
        state->f57C = 0.098174773f;
        state->i578 = 0;
        g_enemy_relocate_count = 0;
        crowd_count = 0;
        part_count = 0;
        if (g_mothership_moby_begin < g_mothership_moby_end) {
        for (; &g_mothership_moby_begin[i] < g_mothership_moby_end; i++) {
                obj = &g_mothership_moby_begin[i];
                class_id = obj->kind;
                if (class_id == 0x7E5 /* moby class 2021 */) {
                    g_mothership_crowd_mobys[crowd_count++] = obj;
                } else if (class_id == 0x27D /* moby class 637 */) {
                    qcopy(&vecs[0], &obj->pos);
                    qcopy(g_hero_state + 0x80, &obj->pos);
                } else if (class_id == 0xF7E /* moby class 3966 */) {
                    state->parts[part_count++] = obj;
                } else if (class_id == 0x120F /* moby class 4623 */) {
                    state->m610 = obj;
                } else if (class_id == 0x123C /* moby class 4668 */) {
                    state->m614 = obj;
                } else if (class_id == MOBY_CLASS_MOTHERSHIP_BOSS_PART) {
                    g_mothership_part_moby = obj;
                } else if (class_id == 0xF6E /* moby class 3950 */) {
                    L23Tint *tint;
                    g_mothership_moby = obj;
                    obj->alpha = 255;
                    tint = g_mothership_moby->vars;
                    tint->r = 0;
                    tint->g = 0;
                    tint->b = -1;
                }
        }
        }
        FastVecSub(&vecs[0], &vecs[0], g_hero_state + 0xB0);
        g_mothership_surface_radius = FastVecLength(&vecs[0]);
        vecs[1] = 0;
        ((float *)&vecs[1])[0] = 500.0f;
        ((float *)&vecs[1])[1] = 500.0f;
        ((float *)&vecs[1])[2] = 430.0f;
        mothership_project_point_onto_surface(&vecs[1], 0.0f);
        qcopy(&g_boss_target_pos_a, &vecs[1]);
        vecs[1] = 0;
        ((float *)&vecs[1])[0] = 500.0f;
        ((float *)&vecs[1])[1] = 500.0f;
        ((float *)&vecs[1])[2] = 552.0f;
        mothership_project_point_onto_surface(&vecs[1], 0.0f);
        qcopy(&g_boss_target_pos_b, &vecs[1]);
        qcopy(&moby->pos, &g_mothership_start_position);
        mothership_project_point_onto_surface(&moby->pos, g_boss_surface_height);
        moby->colour = 255;
        moby->alpha = 255;
        moby->flags |= 0x100;
        health = (float)state->h2F6;
        state->f17C = 0.15f;
        state->maxHealth = state->h2F6;
        state->f170 = 0.5f;
        state->f174 = 0.5f;
        state->b150 = 20;
        state->i188 = -1;
        state->health = health;
        g_mothership_max_health = health * state->f328;
        {
            float share = health * state->f320 * 0.2f;
            g_mothership_hit_damage_floor = share * 0.083333336f;
            g_mothership_hit_damage_scale = share;
        }
        state->f32C = 1.0f - (state->f324 + state->f320 + state->f328);
        state->f84 = 0.5f;
        state->f58 = 0.4f;
        state->f54 = -7.0f;
        state->f50 = 7.0f;
        state->f5C = 0.4f;
        state->flags88 |= 5;
        state->f60 = 1.57079649f;
        state->f80 = 1.55334318f;
        moby_set_controller_speed_limits(moby, 0.019444445f, 0.6333334f, 0.0017453295f, 0.20943955f);
        moby_set_state(moby, 2, 0);
        memset(g_path_end_masks, 0, 0xFE0);
        state->h390 = 0;
        state->h39C = -1;
        state->h39A = -1;
        state->h398 = -1;
        state->h39E = 0;
        g_mothership_slot_count = 4;
        {
            int *dst = g_mothership_scan_slots;
            int *src = g_mothership_init_values;
            int left;
            for (left = 4; left != 0; left--) *dst++ = *src++;
        }
        g_mothership_scan_slot_index = 0;
        mothership_link_touching_path_ends(moby);
        part_spawn_random_path_effects(moby);
        state->f588 = g_boss_second_measure_a;
        state->flags88 |= 16;
        moby->timer = 15;
    } else {
        mothership_advance_scan_slot(moby);
        mode = moby->mode;
        if (mode != 4 && mode != 10 && mode != 11) {
            int part;
            for (part = 5; part < 10; part++) {
                if (state->parts[part]) state->parts[part]->flags |= 0x41;
            }
        }
        if (!state->m620) {
            for (scan = g_mothership_moby_list; scan; scan = scan->next) {
                if (scan->kind == 0x1252 /* moby class 4690 */) {
                    state->m620 = scan;
                    break;
                }
            }
        }
        if (!state->m624) {
            for (scan = g_mothership_moby_list; scan; scan = scan->next) {
                if (scan->kind == 0x1251 /* moby class 4689 */) {
                    state->m624 = scan;
                    break;
                }
            }
        }
    }
    level_store_value_pair((int)mothership_call_helper_return_true, (int)L23_DrawEncounterHud);
    moby->scale = moby->cls->scale * g_mothership_scale_factor;
    {
        int part;
        for (part = 0; part < 10; part++) {
            if (state->parts[part]) state->parts[part]->scale = state->parts[part]->cls->scale * g_mothership_scale_factor;
        }
    }
    if (state->m610) state->m610->scale = state->m610->cls->scale * g_mothership_scale_factor;
    if (state->m614) state->m614->scale = state->m614->cls->scale * g_mothership_scale_factor;
    if (g_boss_part_age_counter) {
        L23Game *game = (L23Game *)g_hero_state;
        L23Pad *pad = (L23Pad *)g_pad_state;
        g_boss_part_age_counter++;
        game->f1E0 = 10;
        state->h390 = 0;
        if (pad->f1A4 & 0x50) {
            g_boss_part_age_counter = 0;
            moby_set_state(moby, 1, 0);
            game->f1E0 = 20;
            pad->f1A4 = 0;
            g_boss_hud_timer = g_mothership_init_value_a;
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x3157), -1);
        } else if (g_boss_part_age_counter < 30) {
            game->f2294 = 0;
            cancel_hero_item_animation();
            release_moby_animation_slot(game->f2290, game->f1870);
            game->f187C = 0;
            hero_l22_set_move_state(0, 1);
        }
    }
    cam_compute_view_direction(&moby->pos, state->m410, 0);
    vec_negate_and_forward(&moby->rot, state->m410, 0);
    if (moby->mode != 7) mothership_project_point_onto_surface(&moby->pos, state->f588);
    UpdateShieldHitsAndStrength(moby);
}
