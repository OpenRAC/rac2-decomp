#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(void *, int, int);
extern float mat_fast_helper_a(float, float);
extern float vec_length_xy(char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern int PlayMobySound(int, int, char *);
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern unsigned char g_sound_state[];
extern int func_001163B0(void);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern int CollLine(void *, void *, int, int, int);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern char *moby_get_private_value_0(void *);
extern void moby_forward_position_call(void *, void *, int);
extern void moby_update_effect_by_class(char *);
extern void SpawnActorPuff(void *);
extern void part_spawn_trail_at_owner(void *);
extern char *g_hit_l02_result;

/* Update for a projectile moby. It flies along its direction, leaves a trail of points, hits things or leaves the map, then removes itself. */
void projectile_l02_update(unsigned char *obj)
{
    float old[4] __attribute__((aligned(16)));
    union {
        TI128 q;
        float f[4];
    } point;
    float step[4] __attribute__((aligned(16)));
    char packet[48] __attribute__((aligned(16)));
    float impact[4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(obj + 0x68);
    char *hit, *info;
    int i;

    point.q = 0;
    point.f[0] = -0.3f;
    point.f[3] = 1.0f;
    switch ((unsigned char)obj[0x20]) {
    case 0: {
        int random;
        moby_set_state(obj, 1, -1);
        random = func_001163B0();
        *(int *)(vars + 0x60) = 0;
        *(int *)(vars + 0x7c) = -1;
        vars[0x74] = random & 1;
        *(float *)(obj + 0xf8) = mat_fast_helper_a(*(float *)vars, *(float *)(vars + 4));
        *(float *)(obj + 0xf4) = -mat_fast_helper_a(vec_length_xy(vars), *(float *)(vars + 8));
        euler_rotation_basis(obj + 0xc0, obj + 0xf0);
        matrix_mul_vec3(&point, &point, obj + 0xc0);
        FastVecAdd(&point, &point, obj + 0x10);
        vec_scale_to_length((char *)&step, (char *)&point, 0.01f);
        qcopy(vars + 0x20, &point);
        for (i = 0; i < 3; i++) {
            FastVecAdd(vars + 0x30 + i * 16, vars + 0x20 + i * 16, &step);
        }
        vars[0x79] = 2;
    }
    /* Fall through to the first movement update. */
    case 1: {
        unsigned char *p;
        int id;
        *(float *)(obj + 0xf8) = mat_fast_helper_a(*(float *)vars, *(float *)(vars + 4));
        *(float *)(obj + 0xf4) = -mat_fast_helper_a(vec_length_xy(vars), *(float *)(vars + 8));
        *(float *)(vars + 0x60) -= 0.1f;
        if (*(float *)(vars + 0x60) <= -8.0f) {
            *(float *)(vars + 0x60) += 8.0f;
        }
        matrix_mul_vec3(&point, &point, obj + 0xc0);
        FastVecAdd(&point, &point, obj + 0x10);
        qcopy(&old, obj + 0x10);
        FastVecAdd(obj + 0x10, obj + 0x10, vars);
        id = *(int *)(vars + 0x7c);
        p = g_sound_state + id * 0x70;
        if (*(char **)(p + 0x88) != obj || !p[0x74]) {
            *(int *)(vars + 0x7c) = PlayMobySound(0, 4, obj);
        }
        if (CollLine(&old, obj + 0x10, 0, *(int *)(obj + 0xb8), 0)) {
            hit = g_hit_l02_result;
            if (hit) {
                make_hit_descriptor(packet, obj, 0x10001, vars, *(float *)(vars + 0x6c));
                packet[0x18] = 5;
                packet[0x19] = 3;
                *(unsigned short *)(packet + 0x1a) = *(unsigned short *)(obj + 0xaa);
                QueueMobyImpact(hit, packet);
                PlayMobySound(1, 0, obj);
                info = moby_get_private_value_0(hit);
                if (info) {
                    moby_forward_position_call(hit, &step, 1);
                    FastVecScale(&impact, &step, *(float *)(info + 0x10));
                    FastVecAdd(&impact, &impact, hit + 0x10);
                }
            } else {
                PlayMobySound(1, 0, obj);
            }
            moby_update_effect_by_class(obj);
            obj[0x20] = 2;
            *(unsigned short *)(obj + 0x34) |= 0x41;
        }
        if (math_fast_float_d(vars + 0x70) ||
            *(float *)(obj + 0x10) < 2.0f || *(float *)(obj + 0x10) > 1021.0f ||
            *(float *)(obj + 0x14) < 2.0f || *(float *)(obj + 0x14) > 1021.0f ||
            *(float *)(obj + 0x18) < 2.0f || *(float *)(obj + 0x18) > 1021.0f) {
            obj[0x20] = 2;
            *(unsigned short *)(obj + 0x34) |= 0x41;
            qcopy(obj + 0x10, &old);
            break;
        }
        if (!vars[0x7a]) {
            FastVecSub((float *)&step, (float *)(vars + 0x10), (float *)vars);
            if (*(float *)(vars + 0x64) < FastVecLength(&step)) {
                vec_scale_to_length((char *)&step, (char *)&step, *(float *)(vars + 0x64));
            } else {
                vars[0x7a] = 1;
            }
            FastVecAdd(vars, vars, &step);
        }
        if (!(unsigned char)vars[0x77]) {
            SpawnActorPuff(obj);
            vars[0x77] = vars[0x78];
        } else {
            vars[0x77]--;
        }
        if (!(unsigned char)vars[0x79]) {
            for (i = 3; i > 0; i--) {
                qcopy(vars + 0x20 + i * 16, vars + 0x10 + i * 16);
            }
            qcopy(vars + 0x20, &point);
            vars[0x79] = 2;
        } else {
            vars[0x79]--;
        }
        break;
    }
    case 2: {
        unsigned char *p;
        int id;
        id = *(int *)(vars + 0x7c);
        if (id != -1) {
            p = g_sound_state + id * 0x70;
            if (*(char **)(p + 0x88) == obj && p[0x74]) {
                snd_stop_voice(id);
            }
        }
        *(int *)(vars + 0x7c) = -1;
        moby_mark_spawned(obj);
        return;
    }
    }
    if (obj[0x20] == 1) {
        gfx_add_draw_callback_third(part_spawn_trail_at_owner, obj);
    }
}
