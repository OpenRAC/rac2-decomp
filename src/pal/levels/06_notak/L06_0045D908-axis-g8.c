#include "names.h"
/* func_PAL_L06_0045D908 (1,572 bytes, Notak): the PAL copy of func_L06_004587E8
 * (src/levels/06_notak/L06_004587E8-axis-g8.c) with its spin rate for 50 Hz: pi/25 per frame
 * instead of pi/30. Built with the v1.01 unit's flags (config/cflags.txt); its set-once `base`
 * local is allowed by the same owner ruling.
 */
#include "common.h"
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float FastAddRotations(float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char g_sound_state[];
extern char D_L06_001A8F20[] __attribute__((sda));
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern char D_L06_001B9840[];
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
extern NotakCollision D_L06_001BFC80;
extern char D_L06_001C79C0[];
extern int D_L06_001B3778[] __attribute__((sda));
extern int D_L06_001B3760[];
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

void func_PAL_L06_0045D908(char *o) {
    float pos[4];
    typedef union { NotakQuad q; float f[4]; } Vec;
    char *st = *(char **)(o + 0x68);
    char *hit;
    float *impact;
    char *s;
    int snd, index, row, col;
    char *p;
    int k, j, sign;
    int count = 6;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    int i;
    int one = 1;
    int type = *(unsigned char *)(o + 0x20);
    {
    if (type == 0) goto c0;
    if (type == one) goto c1;
    goto def;
    c0: {
        char collision[112];
        *(float *)(o + 0xF0) = FastAddRotations(*(float *)(o + 0xF0), 0.125663728f);
        FastVecAdd(pos, o + 0x10, st);
        make_hit_descriptor(collision, o, 1, st, *(float *)(st + 0x40));
        *(unsigned short *)(collision + 0x1A) = *(unsigned short *)(o + 0xAA);
        if (CollLine(o + 0x10, pos, 0, o, collision) ||
            func_0031EBF8(0.3f, o + 0x10, 0, o) || math_fast_float_d(st + 0x38)) {
            hit = D_L06_001BFC80.hit;
            if (hit) {
                if (hit == *(char **)(st + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E)
                    coll_sweep_from_object(o, o + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(st + 0x40), 1.0f);
                impact = (float *)(o + 0x10);
            } else {
                impact = D_L06_001BFC80.point;
            }
            part_emit_paired_spin(impact, 20);
            snd = *(int *)(st + 0x4C);
            if (snd != -1) {
                s = g_sound_state + snd * 0x70;
                if (*(char **)(s + 0x88) == o && *(unsigned char *)(s + 0x74)) snd_stop_voice(snd);
            }
            *(int *)(st + 0x4C) = -1;
            moby_set_state(o, 1, -1);
            return;
        }
    update_position:
        qcopy(o + 0x10, pos);
        goto def;
    }
    c1: {
        index = D_L06_001B3778[*(int *)(st + 0x48)];
        if (index >= 0) {
            p = D_L06_001C79C0 + index * 32;
            *(float *)(p + 0x1C) -= 0.166666672f;
            if (!(*(float *)(p + 0x1C) <= 0)) return;
            gfx_free_point_light(D_L06_001B3778[*(int *)(st + 0x48)]);
            D_L06_001B3778[*(int *)(st + 0x48)] = -1;
            D_L06_001B3760[*(int *)(st + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                for (col = 1; col < 4; col++)
                    qzero_nc(&((NotakQuad *)(D_L06_0025FFC0 + *(int *)(st + 0x48) * 0x180 + (row << 6)))[col]);
            }
            func_00350388(o);
            return;
        }
        D_L06_001B3760[*(int *)(st + 0x48)] = 0;
        func_00350388(o);
        return;
    }
    }
def:
    qcopy(pos, o + 0x10);
    {
        k = 0;
        if (D_L06_001B3790[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!D_L06_001B3790[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < count; i++) {
        Vec velocity, axis;
        short *base = D_L06_001B3790; short *t = &base[i];
        if (--*t < 0) *t = 0;
        *t = 2;
        D_L06_001B37A0[i] = 64;
        part_spawn_random_direction_effect(velocity.f, 0.2f, 0.2f);
        if (FastVecLength(velocity.f) > 0.2f) vec_scale_to_length((char *)velocity.f, (char *)velocity.f, 0.2f);
        qcopy(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][0], pos);
        direction = 1.0f;
        for (j = 1; j < 4; j++) {
            float *prev = (float *)(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1]);
            FastVecSub(axis.f, prev, (float *)D_L06_001B9840);
            math_apply_axis_rotation_to_quat(velocity.f, velocity.f, axis.f, math_random_float_range(0.17453295f, 0.7853982448577881f) * direction);
            direction = -direction;
            FastVecAdd(&((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j], &((Trail *)D_L06_0025FFC0)[*(int *)(st + 0x48)][i][j - 1], velocity.f);
        }
    }
    if (!math_random_int_below(2)) {
        size = math_random_float_range(0.2f, 0.9f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        part_spawn_ground_effect(o + 0x10, 2, size * 0.1f, size, 0x7F7F2020, 0, sign, D_L06_001A8F20, 0, 0);
        part_spawn_ground_effect(o + 0x10, 2, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, D_L06_001A8F20, 0, 0);
    }
    if (!snd_is_voice_playing_for_owner(o, *(int *)(st + 0x4C)))
        *(int *)(st + 0x4C) = snd_play_from_class_bank(7, 4, o, *(short *)(*(char **)(st + 0x3C) + 0xAA));
    gfx_add_draw_callback_third(projectile_draw_trails, o);
}
