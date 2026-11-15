#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
    f32 normal[4];
} CollResult;
extern char g_hero_state[];
extern CollResult g_collision_result __attribute__((aligned(16)));
extern u8 g_sound_state[];
extern void vec_transform_or_copy(void *, void *);
extern void mem_fast_helper_b(void *, int);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern char *SelectBestTargetInCone(void *, void *, int *, float, float, void *, int, int, float, float, float, int, int);
extern char *pair_choose_owner_for_key(char *, char **, int, int *, int);
extern void KeyOwnerTableInsert(char *, char *, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_steer_effect_direction(int, void *, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecLength(void *);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern float math_fabs(float);
extern int CollLine(void *, void *, int, void *, void *);
extern float math_spring_float_to_goal(float *, float, float *, float, float, float);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void func_PAL_L00_003AEB58(char *, char *, void *);
extern void vec_steer_toward_target(void *, char *, char *, void *, int, float, float, float);
extern void func_PAL_L00_003AEEC0(char *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_cosine_blend(float, float, float);
extern float *moby_get_private_value_0(char *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void part_queue_ground_shadow(char *, float);
extern f32 coll_project_point_on_segment(void *, void *, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void table_clear_entry_flag(int);
extern void moby_mark_spawned(void *);
#define HERO_PLAYER (*(char **)(D_00189E20 + 0x2290))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define I(p, o) (*(int *)((char *)(p) + (o)))
#define H(p, o) (*(short *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))

void func_PAL_L00_003ADEA8(char *moby)
{
    struct {
        float saved[4];
        union {
            struct { char *list[32]; int count, found; } search;
            struct { float dir[4], a[4], b[4], c[4], d[4], e[4]; } flight;
        } phase;
        int hitPlayer;
    } work __attribute__((aligned(16)));
    char *state = P(moby, 0x68);
    int moved;
    char *hero;
    float magnitude;

    vec_transform_or_copy(moby + 0x10, moby + 0x10);
    qcopy(work.saved, moby + 0x10);
    if (!P(state, 0x14)) {
        work.phase.search.count = 0;
        mem_fast_helper_b(work.phase.search.list, 0x80);
        if (P(state, 0x74)) {
            if (math_fast_float_d(state + 0x78)) {
                P(state, 0x14) = P(state, 0x74);
                P(state, 0x74) = 0;
            }
        } else {
            char *target;
            char *hero;
            SelectBestTargetInCone(moby + 0x10, state, &work.phase.search.count, 3.14159298f, 3.14159298f, work.phase.search.list, 0x20, 0, 8.0f, 0.0f, 0.0f, 0, 0);
            work.phase.search.found = 0;
            hero = g_hero_state;
            target = pair_choose_owner_for_key(P(hero, 0x2290), work.phase.search.list, work.phase.search.count, &work.phase.search.found, -1);
            P(state, 0x14) = target;
            if (!target)
                goto acquired;
            if (work.phase.search.found)
                KeyOwnerTableInsert(P(hero, 0x2290), target, 0x11);
        }
        if (P(state, 0x14)) {
            B(moby, 0x20) = 1;
            func_PAL_002A7E68(moby, 0, 0, 8);
            qcopy(state + 0x40, state);
            H(state, 0x54) = 17;
        }
    }
acquired:
    cam_compute_view_direction(moby + 0x10, work.phase.flight.dir, 1);
    part_steer_effect_direction(I(state, 0x70), state, 0);
    switch (B(moby, 0x20)) {
    case 0: {
        float step;
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        qcopy(work.phase.flight.a, moby + 0x10);
        moved = 0;
        FastVecScale(work.phase.flight.b, work.phase.flight.dir, 0.5f);
        FastVecSub(work.phase.flight.c, moby + 0x10, work.phase.flight.b);
        if (CollLine(work.phase.flight.a, work.phase.flight.c, 0x12, HERO_PLAYER, 0)) {
            FastVecSub(work.phase.flight.d, moby + 0x10, g_collision_result.pos);
            step = 0.5f - FastVecLength(work.phase.flight.d);
            if (step > 0.080000006f)
                step = 0.080000006f;
            if (F(state, 0x7C) < step) {
                moved = 1;
                FastVecScale(work.phase.flight.b, work.phase.flight.b, step + step);
                FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.b);
                F(state, 0x7C) = step;
            }
        }
        if (!moved && F(state, 0x7C) != 0.0f) {
            FastVecScale(work.phase.flight.d, work.phase.flight.dir, F(state, 0x7C));
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.d);
            math_spring_float_to_goal((float *)(state + 0x7C), 0.0f, (float *)(state + 0x58), 0.02f, 0.2f, 0.0f);
            if (F(state, 0x7C) < 0.001f)
                F(state, 0x7C) = 0.0f;
        }
        if (!snd_is_voice_playing_for_owner(moby, I(state, 0x5C)))
            I(state, 0x5C) = PlayMobySound(0, 4, moby);
        if (FastDecTimer(state + 0x18)) {
            g_collision_result.moby = 0;
            func_PAL_L00_003AEB58(moby, state, moby + 0x10);
            table_clear_entry_flag(I(state, 0x70));
            moby_mark_spawned(moby);
            return;
        }
        break;
    }
    case 3: {
        char *target;
        if (FastDecTimer(state + 0x54)) {
            g_collision_result.moby = 0;
            func_PAL_L00_003AEB58(moby, state, moby + 0x10);
            table_clear_entry_flag(I(state, 0x70));
            moby_mark_spawned(moby);
            return;
        }
        {
            float now = IntToFloat(H(state, 0x54));
            float total = IntToFloat(8);
            float ratio = now / total;
            F(state, 0x50) = math_cosine_blend(0.5f, 1.5f, ratio);
        }
        target = P(state, 0x14);
        if (target) {
            u8 kind = B(target, 0x20);
            if (kind == 0xFE)
                goto drift;
            if (kind == 0xFD)
                goto drift;
            if (!I(target, 0x98))
                goto drift;
        }
        vec_steer_toward_target(moby + 0x10, state, target, state + 0x30, 1, 0.02f, 0.3f, 0.0f);
    drift:
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        break;
    }
    case 1:
        if (FastDecTimer(state + 0x54)) {
            B(moby, 0x20) = 2;
            H(state, 0x56) = 8;
        }
        vec_steer_toward_target(moby + 0x10, state, P(state, 0x14), state + 0x30, 0, 0.04f, 0.3f, 0.0f);
        FastVecScale(state + 0x40, state + 0x40, 0.82000005f);
        FastVecAdd(moby + 0x10, moby + 0x10, state + 0x40);
        {
            float now = IntToFloat(H(state, 0x54));
            float total = IntToFloat(17);
            float ratio = now / total;
            F(state, 0x50) = math_cosine_blend(1.5f, 0.5f, ratio);
        }
        if (P(state, 0x14)) {
            FastVecSub(work.phase.flight.a, moby + 0x10, P(state, 0x14) + 0x10);
            vec_scale_to_length(work.phase.flight.a, work.phase.flight.a, 0.10000001f);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.a);
        }
        break;
    case 2: {
        float half = IntToFloat(8) * 0.5f;
        float t = IntToFloat(H(state, 0x56)) - half;
        float ratio = t / half;
        float scale;
        if (ratio < 0.0f)
            ratio = 0.0f;
        scale = ratio * 0.10000001f;
        if (P(state, 0x14)) {
            FastVecSub(work.phase.flight.a, moby + 0x10, P(state, 0x14) + 0x10);
            vec_scale_to_length(work.phase.flight.a, work.phase.flight.a, scale);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.a);
        }
        if (FastDecTimer(state + 0x56)) {
            B(moby, 0x20) = 3;
            vec_scale_to_length(state, state, 1.2f);
            if (P(state, 0x14)) {
                float targetScale;
                cam_compute_view_direction(moby + 0x10, work.phase.flight.a, 1);
                targetScale = moby_get_private_value_0(P(state, 0x14))[4];
                FastVecScale(work.phase.flight.b, work.phase.flight.a, targetScale);
                FastVecAdd(work.phase.flight.c, P(state, 0x14) + 0x10, work.phase.flight.b);
                H(state, 0x54) = ((s32)(FloatToInt(fast_vec_dist(work.phase.flight.c, moby + 0x10) * 0.8333333f + 5.0f)) * 5 + 2) / 6;
            } else {
                H(state, 0x54) = 8;
            }
            if (I(state, 0x5C) != -1) {
                u8 *slot = g_sound_state + I(state, 0x5C) * 0x70;
                if (*(char **)(slot + 0x88) == moby && slot[0x74])
                    snd_stop_voice(I(state, 0x5C));
            }
            I(state, 0x5C) = -1;
            PlayMobySound(1, 0, moby);
        }
        break;
    }
    }
    if (F(moby, 0x10) < 2.0f || F(moby, 0x10) > 1021.0f || F(moby, 0x14) < 2.0f || F(moby, 0x14) > 1021.0f
        || F(moby, 0x18) < 2.0f || F(moby, 0x18) > 1021.0f) {
        table_clear_entry_flag(I(state, 0x70));
        moby_mark_spawned(moby);
        return;
    }
    qcopy(work.phase.flight.a, moby + 0x10);
    FastVecScale(work.phase.flight.b, work.phase.flight.dir, -2.0f);
    FastVecAdd(work.phase.flight.b, moby + 0x10, work.phase.flight.b);
    if (CollLine(work.phase.flight.a, work.phase.flight.b, 0x12, moby, 0)) {
        float length, limit;
        FastVecSub(work.phase.flight.c, work.phase.flight.a, g_collision_result.pos);
        length = FastVecLength(work.phase.flight.c);
        if (length < 0.0001f) {
            g_collision_result.moby = 0;
            func_PAL_L00_003AEB58(moby, state, moby + 0x10);
            table_clear_entry_flag(I(state, 0x70));
            moby_mark_spawned(moby);
            return;
        }
        limit = 0.030000001f;
        FastVecScale(work.phase.flight.c, work.phase.flight.c, 1.0f / length);
        FastVecAdd(work.phase.flight.d, g_collision_result.pos, work.phase.flight.c);
        FastVecSub(work.phase.flight.e, work.phase.flight.d, moby + 0x10);
        if (FastVecDot(work.phase.flight.e, work.phase.flight.dir) > 0.0f) {
            float distance = FastVecLength(work.phase.flight.e);
            if (distance > limit)
                FastVecScale(work.phase.flight.e, work.phase.flight.e, limit / distance);
            FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.e);
        }
    }
    magnitude = 1.0f;
    vec_scale_to_length(moby + 0xC0, state, magnitude);
    FastVecCross(moby + 0xD0, moby + 0xC0, work.phase.flight.dir);
    vec_scale_to_length(moby + 0xD0, moby + 0xD0, magnitude);
    magnitude = 0.00001f;
    FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
    F(state, 0x20) = FastAddRotations(F(state, 0x20), 0.06f);
    FastVecScale(work.phase.flight.c, work.phase.flight.dir, F(state, 0x24));
    FastVecSub(moby + 0x10, moby + 0x10, work.phase.flight.c);
    F(state, 0x24) = math_fast_sin_or_cos_b(F(state, 0x20)) * 0.15f;
    FastVecScale(work.phase.flight.c, work.phase.flight.dir, F(state, 0x24));
    FastVecAdd(moby + 0x10, moby + 0x10, work.phase.flight.c);
    moby_scale_owner_words_by_angles(moby, state + 0x28, state + 0x2C, 0.5f, 0.1f, 0.025f);
    if (math_fabs(F(moby, 0xF0)) > magnitude) {
        math_build_axis_angle_quat(work.phase.flight.c, moby + 0xC0, F(moby, 0xF0));
        vec_rotate_by_quaternion(moby + 0xD0, moby + 0xD0, work.phase.flight.c);
        vec_rotate_by_quaternion(moby + 0xE0, moby + 0xE0, work.phase.flight.c);
    }
    if (math_fabs(F(moby, 0xF4)) > magnitude) {
        math_build_axis_angle_quat(work.phase.flight.c, moby + 0xD0, F(moby, 0xF4));
        vec_rotate_by_quaternion(moby + 0xC0, moby + 0xC0, work.phase.flight.c);
        vec_rotate_by_quaternion(moby + 0xE0, moby + 0xE0, work.phase.flight.c);
    }
    work.hitPlayer = 0;
    moved = 0;
    part_queue_ground_shadow(moby, 0.2f);
    hero = g_hero_state;
    if (CollLine(work.saved, moby + 0x10, 0x10, P(hero, 0x2290), 0)) {
        work.hitPlayer = 1;
    } else if (B(moby, 0x20) == 3) {
        FastVecScale(work.phase.flight.c, work.phase.flight.dir, moby_get_private_value_0(P(state, 0x14))[4]);
        FastVecAdd(work.phase.flight.d, P(state, 0x14) + 0x10, work.phase.flight.c);
        coll_project_point_on_segment(work.phase.flight.e, work.saved, moby + 0x10, work.phase.flight.d);
        if (fast_vec_dist(work.phase.flight.e, work.phase.flight.d) <= 0.5f) {
            moved = 1;
            qcopy(moby + 0x10, work.phase.flight.e);
            g_collision_result.moby = P(state, 0x14);
        }
    } else if (coll_test_point(moby + 0x10, 0x10, P(hero, 0x2290), 0.2f)) {
        moved = 1;
        qcopy(moby + 0x10, g_collision_result.normal);
    }
    if (moved || work.hitPlayer) {
        func_PAL_L00_003AEB58(moby, state, moby + 0x10);
        table_clear_entry_flag(I(state, 0x70));
        moby_mark_spawned(moby);
        return;
    }
    if (F(moby, 0x10) < 2.0f || F(moby, 0x10) > 1021.0f || F(moby, 0x14) < 2.0f || F(moby, 0x14) > 1021.0f
        || F(moby, 0x18) < 2.0f || F(moby, 0x18) > 1021.0f) {
        table_clear_entry_flag(I(state, 0x70));
        moby_mark_spawned(moby);
        return;
    }
    FastVecScale(work.phase.flight.c, moby + 0xC0, -0.25f);
    FastVecAdd(work.phase.flight.c, work.phase.flight.c, moby + 0x10);
    func_PAL_L00_003AEEC0(moby, work.phase.flight.c);
}
