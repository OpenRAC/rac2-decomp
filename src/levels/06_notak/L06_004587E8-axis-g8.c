#include "names.h"
/* func_L06_004587E8 (1,572 bytes, Notak). Own unit: -O2 -G8 -ffunction-sections
 * -frac2-mult-add-no-flatten -frac2-pre-call-test -frac2-cse-noskip-store
 * -frac2-sched-retstore -frac2-sched-stackaddr (config/cflags.txt; docs/build/compiler-notes.md).
 * In the timer loop `base` is a set-once local holding the table address (owner ruling on
 * set-once locals): its `la` is hoisted and reload rematerialises it in $v1, as retail.
 * Owner standard of 12 November 2026 for the switches.
 */
#include "common.h"
extern short g_trail_active_timers[] __attribute__((sda));
extern short g_trail_alpha_timers[] __attribute__((sda));
extern char g_trail_vertex_buffer[];
extern float FastAddRotations(float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char g_sound_state[];
extern char g_effect_vector[] __attribute__((sda));
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern char g_hero_l06_position[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern int math_random_int_below(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern void moby_set_state(char *, int, int);
extern float math_random_float_range(float, float);
extern void func_00350388(char *);
typedef struct {
    char prefix[0x18];
    char *hit;
    int count;
    float point[4];
} NotakCollision;
extern NotakCollision g_collision_l06_result;
extern char g_trail_slot_table[];
extern int g_child_slot_light_ids[] __attribute__((sda));
extern int g_child_slot_used[];
extern void make_hit_descriptor(void *, char *, int, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int func_0031EBF8(float, void *, int, void *);
extern int coll_sweep_from_object(void *, void *, int, int, int, int, float, float, float);
extern void part_emit_paired_spin(float *, int);
extern void gfx_free_point_light(int);
extern void part_spawn_random_direction_effect(void *, float, float);
extern float FastVecLength(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern void gfx_add_draw_callback_third(void *, void *);
extern void projectile_draw_trails(char *);

/* Updates a flying projectile: it moves, leaves a twisting trail and bursts when it hits something. */
void trail_l06_projectile_update(char *moby) {
    float pos[4];
    typedef union { NotakQuad q; float f[4]; } Vec;
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    float *impact;
    char *sound_record;
    int snd, index, row, col;
    char *slot;
    int k, j, sign;
    int count = 6;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    int i;
    int one = 1;
    int type = *(unsigned char *)(moby + 0x20);
    {
    if (type == 0) goto c0;
    if (type == one) goto c1;
    goto def;
    c0: {
        char collision[112];
        *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), 0.104719773f);
        FastVecAdd(pos, moby + 0x10, vars);
        make_hit_descriptor(collision, moby, 1, vars, *(float *)(vars + 0x40));
        *(unsigned short *)(collision + 0x1A) = *(unsigned short *)(moby + 0xAA);
        if (CollLine(moby + 0x10, pos, 0, moby, collision) ||
            func_0031EBF8(0.3f, moby + 0x10, 0, moby) || math_fast_float_d(vars + 0x38)) {
            hit = g_collision_l06_result.hit;
            if (hit) {
                if (hit == *(char **)(vars + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E /* moby class 78 */)
                    coll_sweep_from_object(moby, moby + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(vars + 0x40), 1.0f);
                impact = (float *)(moby + 0x10);
            } else {
                impact = g_collision_l06_result.point;
            }
            part_emit_paired_spin(impact, 20);
            snd = *(int *)(vars + 0x4C);
            if (snd != -1) {
                sound_record = g_sound_state + snd * 0x70;
                if (*(char **)(sound_record + 0x88) == moby && *(unsigned char *)(sound_record + 0x74)) snd_stop_voice(snd);
            }
            *(int *)(vars + 0x4C) = -1;
            moby_set_state(moby, 1, -1);
            return;
        }
    update_position:
        qcopy(moby + 0x10, pos);
        goto def;
    }
    c1: {
        index = g_child_slot_light_ids[*(int *)(vars + 0x48)];
        if (index >= 0) {
            slot = g_trail_slot_table + index * 32;
            *(float *)(slot + 0x1C) -= 0.166666672f;
            if (!(*(float *)(slot + 0x1C) <= 0)) return;
            gfx_free_point_light(g_child_slot_light_ids[*(int *)(vars + 0x48)]);
            g_child_slot_light_ids[*(int *)(vars + 0x48)] = -1;
            g_child_slot_used[*(int *)(vars + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                for (col = 1; col < 4; col++)
                    qzero_nc(&((NotakQuad *)(g_trail_vertex_buffer + *(int *)(vars + 0x48) * 0x180 + (row << 6)))[col]);
            }
            func_00350388(moby);
            return;
        }
        g_child_slot_used[*(int *)(vars + 0x48)] = 0;
        func_00350388(moby);
        return;
    }
    }
def:
    qcopy(pos, moby + 0x10);
    {
        k = 0;
        if (g_trail_active_timers[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!g_trail_active_timers[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < count; i++) {
        Vec velocity, axis;
        short *base = g_trail_active_timers; short *timer = &base[i];
        if (--*timer < 0) *timer = 0;
        *timer = 2;
        g_trail_alpha_timers[i] = 64;
        part_spawn_random_direction_effect(velocity.f, 0.2f, 0.2f);
        if (FastVecLength(velocity.f) > 0.2f) vec_scale_to_length((char *)velocity.f, (char *)velocity.f, 0.2f);
        qcopy(&((Trail *)g_trail_vertex_buffer)[*(int *)(vars + 0x48)][i][0], pos);
        direction = 1.0f;
        for (j = 1; j < 4; j++) {
            float *prev = (float *)(&((Trail *)g_trail_vertex_buffer)[*(int *)(vars + 0x48)][i][j - 1]);
            FastVecSub(axis.f, prev, (float *)g_hero_l06_position);
            math_apply_axis_rotation_to_quat(velocity.f, velocity.f, axis.f, math_random_float_range(0.17453295f, 0.7853982448577881f) * direction);
            direction = -direction;
            FastVecAdd(&((Trail *)g_trail_vertex_buffer)[*(int *)(vars + 0x48)][i][j], &((Trail *)g_trail_vertex_buffer)[*(int *)(vars + 0x48)][i][j - 1], velocity.f);
        }
    }
    if (!math_random_int_below(2)) {
        size = math_random_float_range(0.2f, 0.9f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        part_spawn_ground_effect(moby + 0x10, 2, size * 0.1f, size, 0x7F7F2020, 0, sign, g_effect_vector, 0, 0);
        part_spawn_ground_effect(moby + 0x10, 2, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, g_effect_vector, 0, 0);
    }
    if (!snd_is_voice_playing_for_owner(moby, *(int *)(vars + 0x4C)))
        *(int *)(vars + 0x4C) = snd_play_from_class_bank(7, 4, moby, *(short *)(*(char **)(vars + 0x3C) + 0xAA));
    gfx_add_draw_callback_third(projectile_draw_trails, moby);
}
