#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef short s16;

typedef int s32;

typedef float f32;

typedef struct State_L04_00454BF8 {
    s32 group;          /* 0x00: index of the id list in D_L04_001A9014 */
    s32 flags;          /* 0x04 */
    s32 mode;           /* 0x08 */
    s32 pad0C;
    f32 band[4];        /* 0x10 */
    f32 scale;          /* 0x20 */
    f32 dir_in[3];      /* 0x24 */
    f32 gain;           /* 0x30 */
    s32 rgba_a[4];      /* 0x34 */
    s32 rgba_b[4];      /* 0x44 */
    f32 off_in[3];      /* 0x54 */
    f32 radius;         /* 0x60 */
    f32 fade_start;     /* 0x64 */
    f32 fade_end;       /* 0x68 */
    f32 off2_in[3];     /* 0x6C */
    f32 reach;          /* 0x78 */
    s32 pad7C;
    s32 trigger;        /* 0x80 */
    u8 alpha;           /* 0x84 */
    u8 pad85[0x90 - 0x85];
    f32 dir[4];         /* 0x90 */
    f32 off[4];         /* 0xA0 */
    f32 off2[4];        /* 0xB0 */
    s32 color_a;        /* 0xC0 */
    s32 color_b;        /* 0xC4 */
    u8 padC8[0xE0 - 0xC8];
    f32 time;           /* 0xE0 */
    f32 period;         /* 0xE4 */
    f32 step;           /* 0xE8 */
} State_L04_00454BF8;

typedef struct Mtx_L04_00454BF8 {
    f32 axis[3][4];     /* 0x00 */
    f32 pos[4];         /* 0x30 */
} Mtx_L04_00454BF8;

extern void func_0029F338(void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_L02_002F1FB8(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern float func_00282E48(void *, void *);
extern float func_00283CC8(float *, float);
extern f32 func_L04_00455418(void *, f32);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00283098(void *, void *, void *);
extern float func_002831B0(float);
extern f32 func_L04_004554F8(f32);
extern void func_L00_0036EF68(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void *func_L04_00363CA0(void *, int, float);
extern int func_00283D38(int, int, float);

extern s32 D_L04_001A9018 __attribute__((sda));
extern u16 **D_L04_001A9014 __attribute__((sda));
extern u8 *D_L04_001B2B54 __attribute__((sda));
extern Mtx_L04_00454BF8 *D_L04_001B2B5C __attribute__((sda));
extern char D_L04_001B9680[];

/* A light controller. State 0 checks its id list (released when the group is out of range or has
   no list), converts its record (bands scaled, colours packed, fade angles to radians, the three
   vectors copied and normalised) and falls into state 1. State 1 advances the clock and, when its
   trigger is -1 or func_002ACBC8 holds for it, walks the group's id list: each matrix of
   D_L04_001B2B5C within 32 units of the camera gets a blend from one of four modes (wave along
   a direction, distance, position phase, or a sweeping axis), the two packed colours are mixed by
   it, the light record of D_L04_001B2B54 is recoloured (flag 1), and a glow facing the camera is
   spawned (flag 2), faded by the angle between its offset and the view.
   It is a -g unit: the line label on the case 1 division is what makes the assembler pad it with
   the retail's nop. The sweep's thresholds are locals set at the head of their case, which is what
   puts them in saved registers before the calls. */
void func_L04_00454BF8(u8 *self)
{
    State_L04_00454BF8 *st = *(State_L04_00454BF8 **)(self + 0x68);
    f32 to_cam[4];
    f32 axis[4];
    f32 probe[4];
    f32 spot[4];
    f32 pull[4];
    f32 whole;
    u16 *p;
    Mtx_L04_00454BF8 *e;
    u8 *light;
    s32 group;
    s32 color;
    s32 alpha;
    f32 blend;
    f32 fade;
    f32 time;
    f32 theta;
    f32 phi;
    f32 sin_theta;
    f32 elev;
    f32 along;
    f32 angle;
    f32 size;
    f32 half;
    f32 quarter;
    f32 rise;
    f32 full;
    f32 fall;
    f32 gone;
    s32 glow;
    s32 red;
    s32 green;
    s32 blue;
    s32 word_a;
    s32 word_b;

    switch (self[0x20]) {
    case 0:
        group = st->group;
        if (group >= D_L04_001A9018 || group == -1 || D_L04_001A9014[group] == 0) {
            MarkMobySpawned(self);
            return;
        }
        st->time = 0.0f;
        st->step = 0.016666668f;
        st->fade_start *= 0.017453294f;
        st->fade_end *= 0.017453294f;
        word_a = st->rgba_a[3] << 24 | st->rgba_a[2] << 16;
        word_a |= st->rgba_a[1] << 8;
        word_a |= st->rgba_a[0];
        st->color_a = word_a;
        word_b = st->rgba_b[3] << 24 | st->rgba_b[2] << 16;
        word_b |= st->rgba_b[1] << 8;
        word_b |= st->rgba_b[0];
        st->color_b = word_b;
        st->band[0] *= st->scale;
        st->band[1] *= st->scale;
        st->band[2] *= st->scale;
        st->band[3] *= st->scale;
        st->scale = 1.0f;
        st->period = st->band[0] + st->band[1] + st->band[2] + st->band[3];
        self[0x30] = st->alpha;
        st->dir[0] = st->dir_in[0];
        st->dir[1] = st->dir_in[1];
        st->dir[2] = st->dir_in[2];
        st->dir[3] = 0.0f;
        if (st->dir[0] == 0.0f && st->dir[1] == 0.0f && st->dir[2] == 0.0f)
            st->mode = 0;
        else
            vec_scale_to_length(st->dir, st->dir, 1.0f);
        st->off[0] = st->off_in[0];
        st->off[1] = st->off_in[1];
        st->off[2] = st->off_in[2];
        st->off[3] = 0.0f;
        vec_scale_to_length(st->off, st->off, 1.0f);
        st->off2[0] = st->off2_in[0];
        st->off2[1] = st->off2_in[1];
        st->off2[2] = st->off2_in[2];
        st->off2[3] = 0.0f;
        SetMobyState(self, 1, -1);
    case 1:
        st->time += st->step;
        if (st->trigger != -1 && IsPointInCuboid(D_L04_001B9680, st->trigger) == 0)
            return;
        for (p = D_L04_001A9014[st->group];
             p != 0 && ((s16)p[-1] >= 0 || p == D_L04_001A9014[st->group]); p++) {
            e = &D_L04_001B2B5C[*p & 0x7FFF];
            if (e == 0)
                break;
            SubtractVec4(to_cam, D_L04_001B9680, e->pos);
            blend = 0.0f;
            light = D_L04_001B2B54 + ((*p & 0x7FFF) << 5);
            if (FastVecLength(to_cam) > 32.0f)
                continue;
            switch (st->mode) {
            case 1:
                along = FastVecDot(e->pos, st->dir) * st->gain / FastVecLength(st->dir);
                blend = ComputePeriodicLightBlend(st, st->time + along);
                break;
            case 2:
                blend = ComputePeriodicLightBlend(st, st->time + fast_vec_dist(self + 0x10, e->pos));
                break;
            case 3:
                blend = ComputePeriodicLightBlend(st, st->time + st->period *
                                                     SplitFloatFraction(&whole, e->pos[0] + e->pos[1] + e->pos[2]));
                break;
            case 4:
                half = 0.5f;
                quarter = 1.5707965f;
                rise = 1.3962636f;
                full = 1.48353f;
                fall = 1.6580629f;
                gone = 2.007129f;
                time = st->time;
                theta = time * half * 3.1415927f;
                phi = time * quarter;
                sin_theta = FastSinOrCosB(theta);
                axis[0] = sin_theta * FastSinOrCosA(phi);
                axis[1] = sin_theta * FastSinOrCosB(phi);
                axis[2] = FastSinOrCosA(theta);
                matrix_mul_vec3(axis, axis, self + 0xC0);
                SubtractVec4(probe, e->pos, self + 0x10);
                vec_scale_to_length(probe, probe, 1.0f);
                elev = 1.5707964f - FastAngleHelper(FastVecDot(probe, axis));
                if (elev > rise) {
                    if (elev <= full)
                        blend = SmoothStep((elev - rise) / (full - rise));
                    else if (elev <= fall)
                        blend = 1.0f;
                    else if (elev <= gone)
                        blend = 1.0f - SmoothStep((elev - fall) / (gone - fall));
                }
                break;
            }
            color = FastTweenColor(st->color_b, st->color_a, blend);
            if (st->flags & 1) {
                blue = (color >> 16) & 0xFF;
                green = (color >> 8) & 0xFF;
                red = color & 0xFF;
                func_L00_0036EF68(light, red, green, blue);
            }
            if (st->flags & 2) {
                fade = 1.0f;
                vec_scale_to_length(axis, to_cam, 1.0f);
                matrix_mul_vec3(probe, st->off, e);
                angle = 1.5707964f - FastAngleHelper(FastVecDot(probe, axis));
                if (angle >= st->fade_end)
                    fade = 0.0f;
                else if (angle > st->fade_start)
                    fade = SmoothStep((angle - st->fade_end) / (st->fade_start - st->fade_end));
                alpha = (u32)color >> 24;
                if (alpha == 0)
                    continue;
                if (fade == 0.0f)
                    continue;
                if (fade != 1.0f)
                    alpha = (s32)((f32)alpha * fade);
                glow = (color & 0xFFFFFF) | (alpha << 24);
                size = FastVecLength(e);
                matrix_mul_vec3(spot, st->off2, e);
                FastVecAdd(spot, spot, e->pos);
                FastVecSub(pull, D_L04_001B9680, spot);
                vec_scale_to_length(pull, pull, st->reach * size);
                FastVecAdd(spot, spot, pull);
                SpawnEffectRecord(spot, glow, st->radius * size * 210000.0f);
            }
        }
        break;
    }
}
