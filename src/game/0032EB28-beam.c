#include "common.h"

/* The game's input and level state, reached through their absolute names. */
extern struct {
    char pad0[0x1230];
    int input;
    char pad1234[0x10];
    int mode;
    char pad1248[0x104C];
    int planet;
} D_00189E20;
extern int g_pad_pressed_flags;

/* The colours are one block: element 0 is the one-instruction load the delay slot
 * can take, while +4/+8/+12 are the backend's two-instruction form. */
extern int g_game_time[] __attribute__((sda));
extern int g_thermanator_beam_colors[] __attribute__((sda));

extern void moby_transform_joint_to_world(void *, int, void *);
extern float game_get_override_value(float);
extern void CalculateAimedLaunchVelocity(void *, void *, char *, float, float, float, float, char *);
extern int coll_trace_projectile_to_impact(float *, float *, float *, float *, void *, void *, int *, float);
extern void moby_set_entry_list_flag_byte(int, int);
extern float IntToFloat(int);
extern void stub_empty_10(void);
extern void stub_empty_11(void);
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

/* Aims a beam from the object, finds what it hits, and fires shots while the button is held. It also fades and smooths the meter that shows how far the target is done. */
void thermanator_update(Target *obj)
{
    BeamVars *v = obj->vars;
    Target *hit;
    float *pos;
    float dir[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    float distance, ratio, length;
    int a, b;

    pos = v->position;
    moby_transform_joint_to_world(obj, 0, pos);
    distance = game_get_override_value(4.5f);
    if (g_hero_state.planet == 29) {
        distance += 6.5f;
    }
    v->hit = 0;
    v->valid = 0;
    CalculateAimedLaunchVelocity(dir, pos, 0, 0.00001f, distance, 0.25f, 0.0030555558f, 0);
    coll_trace_projectile_to_impact(pos, dir, v->endpoint, v->normal, obj, &v->hit, 0, 0.0030555558f);
    hit = v->hit;
    if (hit != 0) {
        if (hit->class->type == 18) {
            TargetVars *target = hit->vars;
            target->maximum = 25;
            if (v->hit->slot != 255) {
                moby_set_entry_list_flag_byte(v->hit->slot, 25);
            }
            ratio = IntToFloat(v->hit->progress);
            ratio /= IntToFloat(target->maximum);
            v->fraction = ratio;
            if (target->reverse) {
                v->fraction = 1.0f - ratio;
                if (v->fraction == 0.0f) {
                    v->fraction = -0.001f;
                }
            }
            v->reverse = target->reverse;
            v->disabled = target->disabled != 0;
            v->valid = 1;
        }
    } else {
        v->fraction = -1000.0f;
    }

    switch (obj->state) {
    case 0:
        obj->state = 1;
        /* fall through: retail's table sends state 0 into state 1's store */
    case 1:
        obj->state = 2;
        break;
    case 2:
        if ((g_pad_pressed_flags & g_hero_state.input) && v->hit && v->valid && !v->disabled) {
            stub_empty_10();
            obj->state = 3;
            if (!v->reverse) {
                part_spawn_flying_chunk_b((int)obj, v->position, dir);
            } else {
                part_spawn_flying_chunk_a((int)obj, v->position, dir);
            }
            snd_play_from_class_bank(1, 0, (char *)obj, 0xFB0);
            if (v->reverse) {
                v->countdown = 14;
            } else {
                v->countdown = 7;
            }
        }
        break;
    case 3:
        if (!(g_pad_pressed_flags & g_hero_state.input) || !v->hit || !v->valid || v->disabled) {
            stub_empty_11();
            obj->state = 2;
        } else if (math_fast_float_d(&v->countdown)) {
            qcopy(spread, dir);
            length = FastVecLength(spread);
            spread[0] += math_random_float_range(-0.005f, 0.005f);
            spread[1] += math_random_float_range(-0.005f, 0.005f);
            spread[2] += math_random_float_range(-0.005f, 0.005f);
            vec_scale_to_length(spread, spread, length);
            if (!v->reverse) {
                part_spawn_flying_chunk_b((int)obj, v->position, spread);
            } else {
                part_spawn_flying_chunk_a((int)obj, v->position, spread);
            }
            snd_play_from_class_bank(1, 0, (char *)obj, 0xFB0);
            if (v->reverse) {
                v->countdown = 14;
            } else {
                v->countdown = 7;
            }
        }
        break;
    case 4:
        break;
    }

    if (g_hero_state.mode == 3) {
        obj->state = 4;
        v->fade -= 0.02f;
    } else {
        v->fade += 0.01f;
    }
    if (v->fade > 1.0f) {
        v->fade = 1.0f;
    } else if (v->fade < 0.0f) {
        v->fade = 0.0f;
    }

    if (v->fraction > -100.0f) {
        if (v->smoothed < -100.0f) {
            v->smoothed = v->fraction;
        } else if (v->fraction < v->smoothed - 0.01f) {
            v->smoothed -= 0.01f;
        } else if (v->smoothed + 0.01f < v->fraction) {
            v->smoothed += 0.01f;
        } else {
            v->smoothed = v->fraction;
        }
    } else {
        v->smoothed = v->fraction;
    }

    a = gfx_blend_colors_by_cycle(g_game_time[0], 90, g_thermanator_beam_colors[0], g_thermanator_beam_colors[1]);
    b = gfx_blend_colors_by_cycle(g_game_time[0], 90, g_thermanator_beam_colors[2], g_thermanator_beam_colors[3]);
    if (v->smoothed >= 0.0f && v->smoothed <= 1.0f) {
        gauge_popup_show(0, a, b, v->smoothed);
    }
    gfx_register_overlay_draw_callback(moby_update_attached_effect_by_state, obj);
}
