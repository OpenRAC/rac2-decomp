#include "include_asm.h"

#include "common.h"
extern struct {
    char pad0[0x1230];
    int input;
    char pad1234[0x10];
    int mode;
    char pad1248[0x104C];
    int planet;
} D_00189E20;
extern int g_pad_pressed_flags;
extern int g_game_time[] __attribute__((sda));
extern int g_thermanator_beam_colors[] __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
extern float game_get_override_value(float);
extern void CalculateAimedLaunchVelocity_us2(void *, void *, char *, float, float, float, float, char *);
extern int coll_trace_projectile_to_impact(float *, float *, float *, float *, void *, void *, int *, float);
extern void moby_set_entry_list_flag_byte(int, int);
extern float IntToFloat(int);
extern void stub_empty_12(void);
extern void stub_empty_12(void);
extern char *part_spawn_flying_chunk_b(int, void *, void *);
extern char *part_spawn_flying_chunk_a(int, void *, void *);
extern int math_fast_float_d(void *);
extern float FastVecLength(void *);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int gfx_blend_colors_by_cycle(int, int, int, int);
extern void gauge_popup_show(int, int, int, float);
extern void gfx_register_overlay_draw_callback(void *, void *);
extern void moby_update_attached_effect_by_state(char *);
typedef struct TargetClass {
    char pad0[0x46];
    s16 type;
} TargetClass;
typedef struct Target {
    char pad0[0x20];
    u8 state;
    u8 slot;
    char pad22[2];
    TargetClass *class;
    char pad28[0x40];
    void *vars;
    char pad6C[0x50];
    u8 progress;
} Target;
typedef struct TargetVars {
    char pad0[0x14];
    u8 reverse;
    u8 maximum;
    s16 disabled;
} TargetVars;
typedef struct BeamVars {
    float unknown0[4];
    float endpoint[4];
    float normal[4];
    float position[4];
    int valid;
    int unknown44;
    float smoothed;
    float fraction;
    float fade;
    Target *hit;
    int countdown;
    int reverse;
    int disabled;
} BeamVars;
extern void stub_empty_11(void);

/* Updates the Thermanator beam: traces the shot to its impact, fires chunks at a target while the button is held, and shows the gauge (v2.00 copy). */
void thermanator_update_us2(Target *moby)
{
    BeamVars *vars = moby->vars;
    Target *hit;
    float *pos;
    float dir[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    float distance, ratio, length;
    int color_a, color_b;

    pos = vars->position;
    moby_transform_joint_to_world(moby, 0, pos);
    distance = game_get_override_value(4.5f);
    if (g_hero_state.planet == 29) {
        distance += 6.5f;
    }
    vars->hit = 0;
    vars->valid = 0;
    CalculateAimedLaunchVelocity_us2(dir, pos, 0, 0.00001f, distance, 0.25f, 0.0030555558f, 0);
    coll_trace_projectile_to_impact(pos, dir, vars->endpoint, vars->normal, moby, &vars->hit, 0, 0.0030555558f);
    hit = vars->hit;
    if (hit != 0) {
        if (hit->class->type == 18) {
            TargetVars *target = hit->vars;
            target->maximum = 25;
            if (vars->hit->slot != 255) {
                moby_set_entry_list_flag_byte(vars->hit->slot, 25);
            }
            ratio = IntToFloat(vars->hit->progress);
            ratio /= IntToFloat(target->maximum);
            vars->fraction = ratio;
            if (target->reverse) {
                vars->fraction = 1.0f - ratio;
                if (vars->fraction == 0.0f) {
                    vars->fraction = -0.001f;
                }
            }
            vars->reverse = target->reverse;
            vars->disabled = target->disabled != 0;
            vars->valid = 1;
        }
    } else {
        vars->fraction = -1000.0f;
    }

    switch (moby->state) {
    case 0:
        moby->state = 1;
        /* fall through: retail's table sends state 0 into state 1's store */
    case 1:
        moby->state = 2;
        break;
    case 2:
        if ((g_pad_pressed_flags & g_hero_state.input) && vars->hit && vars->valid && !vars->disabled) {
            stub_empty_11();
            moby->state = 3;
            if (!vars->reverse) {
                part_spawn_flying_chunk_b((int)moby, vars->position, dir);
            } else {
                part_spawn_flying_chunk_a((int)moby, vars->position, dir);
            }
            snd_play_from_class_bank(1, 0, (char *)moby, 0xFB0);
            if (vars->reverse) {
                vars->countdown = 14;
            } else {
                vars->countdown = 7;
            }
        }
        break;
    case 3:
        if (!(g_pad_pressed_flags & g_hero_state.input) || !vars->hit || !vars->valid || vars->disabled) {
            stub_empty_12();
            moby->state = 2;
        } else if (math_fast_float_d(&vars->countdown)) {
            qcopy(spread, dir);
            length = FastVecLength(spread);
            spread[0] += math_random_float_range(-0.005f, 0.005f);
            spread[1] += math_random_float_range(-0.005f, 0.005f);
            spread[2] += math_random_float_range(-0.005f, 0.005f);
            vec_scale_to_length(spread, spread, length);
            if (!vars->reverse) {
                part_spawn_flying_chunk_b((int)moby, vars->position, spread);
            } else {
                part_spawn_flying_chunk_a((int)moby, vars->position, spread);
            }
            snd_play_from_class_bank(1, 0, (char *)moby, 0xFB0);
            if (vars->reverse) {
                vars->countdown = 14;
            } else {
                vars->countdown = 7;
            }
        }
        break;
    case 4:
        break;
    }

    if (g_hero_state.mode == 3) {
        moby->state = 4;
        vars->fade -= 0.02f;
    } else {
        vars->fade += 0.01f;
    }
    if (vars->fade > 1.0f) {
        vars->fade = 1.0f;
    } else if (vars->fade < 0.0f) {
        vars->fade = 0.0f;
    }

    if (vars->fraction > -100.0f) {
        if (vars->smoothed < -100.0f) {
            vars->smoothed = vars->fraction;
        } else if (vars->fraction < vars->smoothed - 0.01f) {
            vars->smoothed -= 0.01f;
        } else if (vars->smoothed + 0.01f < vars->fraction) {
            vars->smoothed += 0.01f;
        } else {
            vars->smoothed = vars->fraction;
        }
    } else {
        vars->smoothed = vars->fraction;
    }

    color_a = gfx_blend_colors_by_cycle(g_game_time[0], 90, g_thermanator_beam_colors[0], g_thermanator_beam_colors[1]);
    color_b = gfx_blend_colors_by_cycle(g_game_time[0], 90, g_thermanator_beam_colors[2], g_thermanator_beam_colors[3]);
    if (vars->smoothed >= 0.0f && vars->smoothed <= 1.0f) {
        gauge_popup_show(0, color_a, color_b, vars->smoothed);
    }
    gfx_register_overlay_draw_callback(moby_update_attached_effect_by_state, moby);
}
