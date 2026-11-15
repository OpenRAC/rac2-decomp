#include "include_asm.h"

#include "common.h"
typedef int MissileQuadword __attribute__((mode(TI)));
typedef union { MissileQuadword q; float f[4]; } PositionVector;
typedef struct { float progress[3]; u8 gap4C[4]; float rate[3]; } MissileTiming;
typedef struct {
    PositionVector point[4]; MissileTiming timing; u8 gap5C[12]; int sound;
} MissileState;
extern u8 g_sound_state[];
typedef union { u8 b[0x2600]; f32 f[0x980]; } Hero;
extern Hero g_hero_state;
extern float D_L16_001B9B00[4] NOT_SDA;
extern int D_L16_001A8F00;
extern u8 *D_L16_001BFF58 NOT_SDA;
extern float D_L16_001B1648[3] __attribute__((sda));
extern float D_L16_001B1658[3] __attribute__((sda));
extern float D_L16_001B1664 __attribute__((sda));
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int), func_PAL_002A7E68(void *, int, int, int);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float), vec_scale_to_length(void *, void *, float);
extern float mat_fast_helper_a(float, float), math_random_signed_float_range(float, float), math_random_float_range(float, float);
extern void func_PAL_L16_00412C28(u8 *);
extern void StepAngleTowardTarget(float *, int, float, float);
extern void *part_find_owned_effect_slot(void *, int, int);
extern u8 *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void moby_mark_spawned(void *), moby_set_state(void *, int, int);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern char *func_PAL_0032F3B8(void *, void *, void *, float);
extern int coll_sweep_from_object(void *, void *, float, int, int, float, float, int, int);

/* The sound handle indexes 0x70-byte resident records. The sound owner and
 * active byte are checked before stopping a handle that may have been reused. */
void func_PAL_L16_004124A0(u8 *moby)
{
    MissileState *state = *(MissileState **)(moby + 0x68);
    float oldPosition[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    int handle, i;
    MissileTiming *timing;
    float *rate;
    PositionVector *segmentEnd;
    switch (moby[0x20]) {
    case 0: {
        u8 *rec = g_sound_state + state->sound * 0x70;
        if (*(u8 **)(rec + 0x88) != moby || !rec[0x74])
            state->sound = PlayMobySound(0, 4, moby);
        qcopy(oldPosition, (moby + 0x10));
        qcopy((moby + 0x10), &state->point[0]);
        timing = &state->timing;
        rate = state->timing.rate;
        segmentEnd = &state->point[1];
        for (i = 0; i < 3; i++) {
            if (i == 0 || timing->progress[i-1] > D_L16_001B1664) {
                math_step_value_toward_target(&timing->progress[i],
                    &rate[i], 1.0f,
                    D_L16_001B1648[i] * 0.00040000002f,
                    D_L16_001B1648[i] * 0.00040000002f,
                    D_L16_001B1658[i] * 0.020000001f);
                if (i == 2 && state->timing.progress[1] > 0.95f && moby[0x43])
                    func_PAL_002A7E68(moby, 0, 0, 17);
            }
            FastVecSub(delta, &segmentEnd[i], &state->point[i]);
            FastVecScale(delta, delta, timing->progress[i]);
            FastVecAdd(moby + 0x10, moby + 0x10, delta);
        }
        StepAngleTowardTarget((float *)(moby + 0xf8), 0,
            mat_fast_helper_a(g_hero_state.f[0x80 / 4] - *(float *)(moby + 0x10),
                g_hero_state.f[0x84 / 4] - *(float *)(moby + 0x14)), 0.25132746f);
        func_PAL_L16_00412C28(moby);
        if (part_find_owned_effect_slot(moby, 0x10000, 0) || D_L16_001A8F00 == 2) {
            PlayMobySound(2, 0, moby);
            handle = state->sound;
            if (handle != -1) {
                u8 *rec = g_sound_state + handle * 0x70;
                if (*(u8 **)(rec + 0x88) == moby && rec[0x74]) snd_stop_voice(handle);
            }
            state->sound = -1;
            for (i = 0; i < 3; i++) {
                switch (i) {
                case 0: FastVecScale(velocity, moby + 0xd0, 0.18f); break;
                case 1: FastVecScale(velocity, moby + 0xd0, -0.18f); break;
                case 2: FastVecScale(velocity, moby + 0xe0, 0.120000005f); break;
                default: qzero(velocity); break;
                }
                func_PAL_002735D0(moby, 1, *(short *)(moby + 0xaa), i,
                    moby + 0x10, moby + 0xf0, velocity, 255, math_random_signed_float_range(90.0f, 180.0f), math_random_float_range(5.0f, 15.0f));
            }
            func_PAL_L00_003FB330(moby + 0x10, 0, 0, 0, 0, 20, 45, 1,
                1.0f, 20.0f, 1, 0, 0, 0);
            moby_mark_spawned(moby);
        } else {
            if (state->timing.progress[2] >= 1.0f) moby_set_state(moby, 1, -1);
            if (CollLine(oldPosition, moby + 0x10, 0, moby, 0)) {
                if (D_L16_001BFF58 &&
                    (*(short *)(D_L16_001BFF58 + 0xaa) == 0xf78 ||
                     *(short *)(D_L16_001BFF58 + 0xaa) == 0x7e8)) return;
            } else {
                if (!(state->timing.progress[1] >= 0.9f)) return;
                if (!coll_test_point(moby + 0x10, 0, moby, 1.5f)) return;
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    }
    case 1: {
        u8 *rec;
        handle = state->sound;
        if (handle != -1) {
            rec = g_sound_state + handle * 0x70;
            if (*(u8 **)(rec + 0x88) == moby && rec[0x74]) snd_stop_voice(handle);
        }
        state->sound = -1;
        PlayMobySound(1, 0, moby);
        FastVecSub(oldPosition, D_L16_001B9B00, moby + 0x10);
        vec_scale_to_length(oldPosition, oldPosition, 1.0f);
        func_PAL_0032F3B8(moby, moby + 0x10, oldPosition, 0.0f);
        coll_sweep_from_object(moby, moby + 0x10, 2.0f, 0x10001, 0, 5.0f, 1.0f, 1, 0);
        moby_mark_spawned(moby);
        break;
    }
    }
}
