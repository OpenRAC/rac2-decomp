#include "names.h"
/* func_PAL_L01_003C0A98, the PAL copy of func_L01_003BCEC8: the same C. */
#include "common.h"

/* Small data reached through $gp: these are only one instruction at -G8. */
/* Oozla debris update. */
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern float g_debris_drift_scale __attribute__((sda));
extern char g_coll_line_hit_point[];

/* Updates a falling debris piece. It drifts, tilts, bounces off walls, fades out near the end of its life and is then removed (PAL version). */
void debris_l01_piece_update_pal(char *moby)
{
    char *state = *(char **)(moby + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float saved, scale, tilt;

    qcopy(pos, moby + 0x10);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        moby_mark_spawned(moby);
        return;
    case 1:
        if (math_fast_float_d(state + 0x30)) {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(state + 0x30) = FloatToInt(8.666667f);
            *(unsigned short *)(moby + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (math_fast_float_d(state + 0x30)) {
            moby_mark_spawned(moby);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(moby + 0x23) = FloatToInt((float)*(int *)(state + 0x30) * 14.76923f);
        break;
    }
    *(float *)(state + 0x40) = FastAddRotations(*(float *)(state + 0x40), 0.04188791f);
    *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8),
                                           *(float *)(state + 0x18) * math_fast_sin_or_cos_b(*(float *)(state + 0x40)));
    *(float *)(moby + 0xF0) += (*(float *)(state + 0x44) - *(float *)(moby + 0xF0)) * 0.02f;
    if (*(unsigned char *)(moby + 0x20) != 2) {
        tilt = math_fast_sin_or_cos_a(*(float *)(state + 0x40)) * 0.17453295f;
        scale = g_debris_drift_scale;
        *(float *)(moby + 0xF4) = tilt;
        saved = *(float *)(state + 8);
        *(float *)(state + 8) = 0.0f;
        FastVecScale(state, state, scale);
        *(float *)(state + 8) = saved;
        FastVecAdd(moby + 0x10, moby + 0x10, state);
        *(float *)(state + 8) -= *(float *)(state + 0x38);
        if (*(float *)(state + 8) < *(float *)(state + 0x3C))
            *(float *)(state + 8) = *(float *)(state + 0x3C);
    } else {
        *(float *)(moby + 0xF4) += (0.17453295f - *(float *)(moby + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (CollLine(pos, moby + 0x10, 2, moby, 0)) {
        qcopy(moby + 0x10, g_coll_line_hit_point);
        /* qzero(state + 8): retail passes a misaligned pointer here (original bug; sq ignores the low four address bits). Allowed by owner ruling (2026-11-09). */
        qzero(state + 8);
        *(int *)(state + 0x38) = 0;
        qzero(state + 0x10);
        if (*(unsigned char *)(moby + 0x20) != 2) {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(state + 0x30) = FloatToInt(8.666667f);
            *(unsigned short *)(moby + 0x34) |= 0x2000;
        }
    }
}
