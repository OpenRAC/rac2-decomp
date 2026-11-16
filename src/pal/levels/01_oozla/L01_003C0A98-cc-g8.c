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

void func_PAL_L01_003C0A98(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    float pos[4] __attribute__((aligned(16)));
    float saved, scale, tilt;

    qcopy(pos, obj + 0x10);
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        moby_mark_spawned(obj);
        return;
    case 1:
        if (math_fast_float_d(s + 0x30)) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = FloatToInt(8.666667f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
            return;
        }
        break;
    case 2:
        if (math_fast_float_d(s + 0x30)) {
            moby_mark_spawned(obj);
            return;
        }
        /* Fade while the removal timer runs. */
        *(unsigned char *)(obj + 0x23) = FloatToInt((float)*(int *)(s + 0x30) * 14.76923f);
        break;
    }
    *(float *)(s + 0x40) = FastAddRotations(*(float *)(s + 0x40), 0.04188791f);
    *(float *)(obj + 0xF8) = FastAddRotations(*(float *)(obj + 0xF8),
                                           *(float *)(s + 0x18) * math_fast_sin_or_cos_b(*(float *)(s + 0x40)));
    *(float *)(obj + 0xF0) += (*(float *)(s + 0x44) - *(float *)(obj + 0xF0)) * 0.02f;
    if (*(unsigned char *)(obj + 0x20) != 2) {
        tilt = math_fast_sin_or_cos_a(*(float *)(s + 0x40)) * 0.17453295f;
        scale = g_debris_drift_scale;
        *(float *)(obj + 0xF4) = tilt;
        saved = *(float *)(s + 8);
        *(float *)(s + 8) = 0.0f;
        FastVecScale(s, s, scale);
        *(float *)(s + 8) = saved;
        FastVecAdd(obj + 0x10, obj + 0x10, s);
        *(float *)(s + 8) -= *(float *)(s + 0x38);
        if (*(float *)(s + 8) < *(float *)(s + 0x3C))
            *(float *)(s + 8) = *(float *)(s + 0x3C);
    } else {
        *(float *)(obj + 0xF4) += (0.17453295f - *(float *)(obj + 0xF4)) * 0.1f;
    }
    pos[2] += 1.0f;
    if (CollLine(pos, obj + 0x10, 2, obj, 0)) {
        qcopy(obj + 0x10, g_coll_line_hit_point);
        /* qzero(state + 8): retail passes a misaligned pointer here (original bug; sq ignores the low four address bits). Allowed by owner ruling (2026-11-09). */
        qzero(s + 8);
        *(int *)(s + 0x38) = 0;
        qzero(s + 0x10);
        if (*(unsigned char *)(obj + 0x20) != 2) {
            *(unsigned char *)(obj + 0x20) = 2;
            *(int *)(s + 0x30) = FloatToInt(8.666667f);
            *(unsigned short *)(obj + 0x34) |= 0x2000;
        }
    }
}
