/* func_PAL_L23_0041C820, the PAL copy of func_L23_004177F8: the same C, where rename func_0029B758 becomes func_PAL_0029C0F0; rename func_L00_0030DD70 becomes func_PAL_L00_0030FBC0; rename func_L00_002AF7D0 becomes func_PAL_L00_002AF6C0; rename func_L22_002C9898 becomes func_PAL_L22_002C99C8; rename func_L23_0041B9F0 becomes func_PAL_L23_00420AD0; scale D_L23_001B14A0. */
/* func_PAL_L23_0041C820: boss set-up and per-frame refresh for Damosel orbit.
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
extern void level_store_value_pair_pal(int, int);
extern int mothership_call_helper_return_true(void);
extern int L23_DrawEncounterHud(void);
extern void cancel_hero_item_animation_pal(void);
extern void release_moby_animation_slot(void *, void *);
extern int hero_l22_set_action_pal(int, int);
extern char *GetLocalizedString(int);
extern int level_l00_call_module_handler_with_arg_9_pal(int, int);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_negate_and_forward(void *, void *, void *);
extern void UpdateShieldHitsAndStrength_pal(L23Moby *);

/* Initialize the encounter objects and refresh their shared presentation state. */
void mothership_update_pal(L23Moby *moby) {
    Quad v[10];
    L23Boss *vars = moby->vars;
    L23Moby *entity;
    L23Moby *scan;
    int i, j, class_id, crowd_index, part_index, mode;
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
        vars->m620 = 0;
        vars->m624 = 0;
        g_flying_enemy_active_flag = 1;
        g_mothership_boss_moby = moby;
        vars->i60C = 0;
        g_enemy_effect_param = vars->i31C;
        g_mothership_effect_radius = vars->f308;
        g_mothership_impact_param = vars->f30C;
        g_mothership_state_param_a = vars->f310;
        g_mothership_knockback_scale = vars->f314;
        if (vars->h334 > 8) vars->h334 = 8;
        vars->h336 = 2;
        g_mothership_state_param_b = vars->f330;
        g_mothership_hit_speed = (float)vars->h338;
        g_boss_part_hit_counter = 0;
        g_selected_moby = 0;
        vars->i608 = 0;
        vars->f5D0 = g_mothership_initial_timer;
        vars->f5C8 = g_mothership_initial_timer;
        vars->i5CC = 0;
        vars->i5D8 = 0;
        vars->i5B0 = 0;
        vars->i5C4 = 0;
        vars->i594 = 0;
        vars->i590 = 0;
        vars->i59C = 0;
        g_path_piece_table = vars->t230;
        vars->b1B7 = 1;
        func_001163A0(T1_COUNT);
        g_boss_hud_stat_index = -1;
        g_boss_hud_display_timer = 0;
        vars->i408 = 0;
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 3; j++) {
                qzero(&v[0]);
                g_mothership_beam_handles[i][j] = 0;
                g_mothership_beam_end_handles[i][j] = 0;
                qcopy(&g_mothership_barrier_points[i][j], &v[0]);
            }
        }
        for (i = 0; i < 4; i++) g_mothership_effect_handles[i] = 0;
        i = 0;
        g_mothership_reset_flag_b = 0;
        g_mothership_reset_flag_a = 0;
        vars->f57C = 0.098174773f;
        vars->i578 = 0;
        g_enemy_relocate_count = 0;
        crowd_index = 0;
        part_index = 0;
        if (g_mothership_moby_begin < g_mothership_moby_end) {
        for (; &g_mothership_moby_begin[i] < g_mothership_moby_end; i++) {
                entity = &g_mothership_moby_begin[i];
                class_id = entity->kind;
                if (class_id == 0x7E5) {
                    g_mothership_crowd_mobys[crowd_index++] = entity;
                } else if (class_id == 0x27D) {
                    qcopy(&v[0], &entity->pos);
                    qcopy(g_hero_state + 0x80, &entity->pos);
                } else if (class_id == 0xF7E) {
                    vars->parts[part_index++] = entity;
                } else if (class_id == 0x120F) {
                    vars->m610 = entity;
                } else if (class_id == 0x123C) {
                    vars->m614 = entity;
                } else if (class_id == MOBY_CLASS_MOTHERSHIP_BOSS_PART) {
                    g_mothership_part_moby = entity;
                } else if (class_id == 0xF6E) {
                    L23Tint *tint;
                    g_mothership_moby = entity;
                    entity->alpha = 255;
                    tint = g_mothership_moby->vars;
                    tint->r = 0;
                    tint->g = 0;
                    tint->b = -1;
                }
        }
        }
        FastVecSub(&v[0], &v[0], g_hero_state + 0xB0);
        g_mothership_surface_radius = FastVecLength(&v[0]);
        v[1] = 0;
        ((float *)&v[1])[0] = 500.0f;
        ((float *)&v[1])[1] = 500.0f;
        ((float *)&v[1])[2] = 430.0f;
        mothership_project_point_onto_surface(&v[1], 0.0f);
        qcopy(&g_boss_target_pos_a, &v[1]);
        v[1] = 0;
        ((float *)&v[1])[0] = 500.0f;
        ((float *)&v[1])[1] = 500.0f;
        ((float *)&v[1])[2] = 552.0f;
        mothership_project_point_onto_surface(&v[1], 0.0f);
        qcopy(&g_boss_target_pos_b, &v[1]);
        qcopy(&moby->pos, &g_mothership_start_position);
        mothership_project_point_onto_surface(&moby->pos, g_boss_surface_height);
        moby->colour = 255;
        moby->alpha = 255;
        moby->flags |= 0x100;
        health = (float)vars->h2F6;
        vars->f17C = 0.15f;
        vars->maxHealth = vars->h2F6;
        vars->f170 = 0.5f;
        vars->f174 = 0.5f;
        vars->b150 = 20;
        vars->i188 = -1;
        vars->health = health;
        g_mothership_max_health = health * vars->f328;
        {
            float share = health * vars->f320 * 0.2f;
            g_mothership_hit_damage_floor = share * 0.083333336f;
            g_mothership_hit_damage_scale = share;
        }
        vars->f32C = 1.0f - (vars->f324 + vars->f320 + vars->f328);
        vars->f84 = 0.5f;
        vars->f58 = 0.4f;
        vars->f54 = -7.0f;
        vars->f50 = 7.0f;
        vars->f5C = 0.4f;
        vars->flags88 |= 5;
        vars->f60 = 1.57079649f;
        vars->f80 = 1.55334318f;
        moby_set_controller_speed_limits(moby, 0.028f, 0.76000005f, 0.0025132746f, 0.25132746f);
        moby_set_state(moby, 2, 0);
        memset(g_path_end_masks, 0, 0xFE0);
        vars->h390 = 0;
        vars->h39C = -1;
        vars->h39A = -1;
        vars->h398 = -1;
        vars->h39E = 0;
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
        vars->f588 = g_boss_second_measure_a;
        vars->flags88 |= 16;
        moby->timer = 15;
    } else {
        mothership_advance_scan_slot(moby);
        mode = moby->mode;
        if (mode != 4 && mode != 10 && mode != 11) {
            int part;
            for (part = 5; part < 10; part++) {
                if (vars->parts[part]) vars->parts[part]->flags |= 0x41;
            }
        }
        if (!vars->m620) {
            for (scan = g_mothership_moby_list; scan; scan = scan->next) {
                if (scan->kind == 0x1252) {
                    vars->m620 = scan;
                    break;
                }
            }
        }
        if (!vars->m624) {
            for (scan = g_mothership_moby_list; scan; scan = scan->next) {
                if (scan->kind == 0x1251) {
                    vars->m624 = scan;
                    break;
                }
            }
        }
    }
    level_store_value_pair_pal((int)mothership_call_helper_return_true, (int)L23_DrawEncounterHud);
    moby->scale = moby->cls->scale * g_mothership_scale_factor;
    {
        int part;
        for (part = 0; part < 10; part++) {
            if (vars->parts[part]) vars->parts[part]->scale = vars->parts[part]->cls->scale * g_mothership_scale_factor;
        }
    }
    if (vars->m610) vars->m610->scale = vars->m610->cls->scale * g_mothership_scale_factor;
    if (vars->m614) vars->m614->scale = vars->m614->cls->scale * g_mothership_scale_factor;
    if (g_boss_part_age_counter) {
        L23Game *game = (L23Game *)g_hero_state;
        L23Pad *pad = (L23Pad *)g_pad_state;
        g_boss_part_age_counter++;
        game->f1E0 = 8;
        vars->h390 = 0;
        if (pad->f1A4 & 0x50) {
            g_boss_part_age_counter = 0;
            moby_set_state(moby, 1, 0);
            game->f1E0 = 17;
            pad->f1A4 = 0;
            g_boss_hud_timer = (((int)(g_mothership_init_value_a) * 5 + 2) / 6);
            level_l00_call_module_handler_with_arg_9_pal(GetLocalizedString(0x106b), -1);
        } else if (g_boss_part_age_counter < 30) {
            game->f2294 = 0;
            cancel_hero_item_animation_pal();
            release_moby_animation_slot(game->f2290, game->f1870);
            game->f187C = 0;
            hero_l22_set_action_pal(0, 1);
        }
    }
    cam_compute_view_direction(&moby->pos, vars->m410, 0);
    vec_negate_and_forward(&moby->rot, vars->m410, 0);
    if (moby->mode != 7) mothership_project_point_onto_surface(&moby->pos, vars->f588);
    UpdateShieldHitsAndStrength_pal(moby);
}
