#include "common.h"
extern char *D_L01_001FE180[];
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern void anim_start_blended(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern int D_L01_001B2088;
typedef struct {
    char pad[0x2C];
    float radius;
} L01RadiusRecord;
extern L01RadiusRecord *D_L01_001B21C0;
extern char D_L01_001AFE38[] SDATA(D_L01_001AFE38);
extern void moby_update_floor_and_ceiling_heights(void *);
extern int FloatToInt(float);
extern void path_l01_compute_segment_lengths(void *);
extern void moby_set_state(void *, int, int);

/* Sets up a Mutant Firefly when it first appears: size, starting height, random spin, timers and its first animation. */
void mutant_firefly_init(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float radius_value;
    L01RadiusRecord *record;

    if (!D_L01_001B2088) **(int **)(vars + 0x250) = 0;
    qcopy(vars + 0x1D0, moby + 0x10);
    moby_update_floor_and_ceiling_heights(moby);
    radius_value = 0.0f;
    *(unsigned char *)(vars + 0x48) = FloatToInt(10.0f);
    *(unsigned char *)(vars + 0x4A) = FloatToInt(4.0f);
    *(unsigned char *)(vars + 0x200) = *(unsigned char *)(moby + 0x30);
    if (*(int *)(vars + 0x294) != -1) {
        record = D_L01_001B21C0;
        record += *(int *)(vars + 0x294);
        radius_value = record->radius;
    }
    if (radius_value > 0.0f) *(unsigned char *)(moby + 0x30) = FloatToInt(radius_value + 2.0f);
    *(unsigned char *)(vars + 0x200) = *(unsigned char *)(vars + 0x201) = *(unsigned char *)(moby + 0x30);
    if (*(int *)(vars + 0x298) != -1) {
        record = D_L01_001B21C0;
        record += *(int *)(vars + 0x298);
        radius_value = record->radius;
    }
    if (radius_value > 0.0f) *(unsigned char *)(vars + 0x200) = FloatToInt(radius_value + 2.0f);
    if (*(int *)(vars + 0x210) != -1) path_l01_compute_segment_lengths(D_L01_001FE180[*(int *)(vars + 0x210)]);
    if (*(int *)(vars + 0x214) != -1) path_l01_compute_segment_lengths(D_L01_001FE180[*(int *)(vars + 0x214)]);
    *(char **)(vars + 0x10) = vars + 0x50;
    *(unsigned char *)(vars + 0x60) = 9;
    *(float *)(vars + 0x80) = 0.3f;
    *(float *)(vars + 0x8C) = 0.4f;
    *(unsigned char *)(vars + 0xC6) = 1;
    *(unsigned char *)(vars + 0x69) = 1;
    *(short *)(vars + 0x88) = 0;
    *(unsigned char *)(vars + 0x6A) = 0;
    *(int *)(vars + 0x98) = 0;
    *(float *)(vars + 0x84) = 0.0f;
    *(int *)(vars + 0x220) = 0;
    *(unsigned char *)(vars + 0x28) = 0;
    *(float *)(vars + 0x30) = 0.0f;
    qcopy(vars + 0x1E0, moby + 0x10);
    *(float *)(vars + 0x240) = 0.0f;
    *(float *)(vars + 0x24C) = math_random_float_range(0.0f, 1.0f);
    *(float *)(vars + 0x26C) = math_random_float_range(-3.1415927f, 3.1415927f);
    *(float *)(vars + 0x270) = math_random_float_range(-3.1415927f, 3.1415927f);
    *(float *)(vars + 0x274) = math_random_float_range(-3.1415927f, 3.1415927f);
    *(float *)(vars + 0x260) = math_random_float_range(-3.1415927f, 3.1415927f) * 0.0002908882452175021f;
    *(float *)(vars + 0x264) = math_random_float_range(-3.1415927f, 3.1415927f) * 0.0002908882452175021f;
    *(float *)(vars + 0x268) = math_random_float_range(-3.1415927f, 3.1415927f) * 0.0002908882452175021f;
    *(void **)(vars + 0x190) = D_L01_001AFE38;
    *(float *)(vars + 0x1C0) = *(float *)(*(char **)(moby + 0x24) + 0x24);
    *(float *)(vars + 0x1B0) = *(float *)(vars + 0x30);
    *(short *)(vars + 0x202) = -1;
    *(float *)(vars + 0x204) = 0.0f;
    *(int *)(vars + 0x290) = 0;
    *(unsigned short *)(moby + 0x34) = *(unsigned short *)(moby + 0x34) | (func_001163B0() & -0x8000);
    *(float *)(vars + 0x22C) = 0.0f;
    *(int *)(vars + 0xCC) = *(int *)(vars + 0x214);
    *(int *)(vars + 0x29C) = *(int *)(vars + 0x294);
    switch (*(int *)(vars + 0x208)) {
    case 0:
        *(float *)(moby + 0x18) = *(float *)(vars + 0x224) - 1.7f;
        qcopy(vars + 0x1D0, moby + 0x10);
        qzero_nc(vars + 0x1F0);
        *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        if (*(unsigned char *)(moby + 0x43) != 1) anim_start_blended(moby, 1, 0, 3);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        *(float *)(moby + 0x18) = *(float *)(vars + 0x224);
        *(float *)(moby + 0x18) += *(float *)(vars + 0x24C) + 1.7f;
        qcopy(vars + 0x1D0, moby + 0x10);
        qzero_nc(vars + 0x1F0);
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        if (*(unsigned char *)(moby + 0x43) != 1) anim_start_blended(moby, 1, 0, 3);
        moby_set_state(moby, 6, 0);
        break;
    case 2:
        qcopy(vars + 0x1F0, vars + 0xD0);
        FastVecAdd(moby + 0x10, moby + 0x10, vars + 0x1F0);
        qcopy(vars + 0x1D0, moby + 0x10);
        if (*(unsigned char *)(moby + 0x43) != 5) anim_start_blended(moby, 5, 0, 3);
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        moby_set_state(moby, 4, -1);
        break;
    }
}
