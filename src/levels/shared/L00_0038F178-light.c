#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } Vector;
typedef struct { u8 initial, maximum, minimum, rise, fall; } ColorCycle;
typedef struct {
    Vector offset, origin;
    char *parent;
    u8 intensity;
    ColorCycle color[3];
    float initialRadius, maximumRadius, minimumRadius, radiusRise, radiusFall;
    int lifetime;
    u32 flags;
    int light;
    float rgb[3], radius;
    int parentIndex;
    u8 hold[4];
    u16 interval[4], timer[4];
    u8 delay[4];
} LightState;
/* Incomplete sda array read as [0]: retail's tied absolute macro load of the moby table base. */
extern char *g_moby_array_base[] __attribute__((sda));
extern Vector g_light_table[8][2];
extern float IntToFloat(int), math_random_float_range(float, float);
extern int FloatToInt(float), math_fast_float_d(int *), FastDecTimer(u16 *), vec_fast_helper_a(u8 *), math_fast_helper_a(void *, float);
extern void gfx_free_point_light(int), moby_mark_spawned(void *), FastVecScale(void *, void *, float), matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern int part_l00_alloc_effect_slot_2(void *, float, float, float, float, float);
/* The retail code checks flag pairs through the aligned lifetime/flags doubleword. */
/* colorReset mirrors the radius cycle's reset flag but no colour path sets it: retail keeps the
 * constant test (li v0,1; bnel v0,zero), so a nonzero interval never randomizes the channel. */
#define UPDATE_COLOR(n, randomFlag, pairMask, pairValue, pauseFlag, downFlag, topFlag, bottomFlag) { int colorReset = 0; \
    if (s->interval[n] && func_00282978(&s->timer[n])) { \
        s->timer[n] = s->interval[n]; \
        s->rgb[n] = (float)s->color[n].minimum; \
        s->flags &= ~(downFlag); \
    } \
    if (!(s->flags & (randomFlag))) { \
        if ((*(u64 *)&s->lifetime & (pairMask)) == (pairValue)) s->flags ^= (pauseFlag); \
        if (!(s->flags & (pauseFlag))) { \
            if (s->flags & (downFlag)) { \
                low = IntToFloat(s->color[n].minimum) * 0.01f; \
                s->rgb[n] -= IntToFloat(s->color[n].fall) * 0.01f; \
                if (s->rgb[n] <= low) { \
                    s->rgb[n] = low; \
                    if ((s->flags & (bottomFlag)) && !s->interval[n]) s->flags ^= (downFlag); \
                } \
            } else { \
                high = IntToFloat(s->color[n].maximum) * 0.01f; \
                s->rgb[n] += IntToFloat(s->color[n].rise) * 0.01f; \
                if (high <= s->rgb[n]) { \
                    s->rgb[n] = high; \
                    if (!(s->flags & (topFlag))) s->flags ^= (downFlag); \
                    else { s->flags = (s->flags | (pauseFlag)) ^ (downFlag); s->delay[n] = s->hold[n]; } \
                } \
            } \
        } else { \
            if (s->hold[n] && func_002829A8(&s->delay[n])) s->flags ^= (pauseFlag); \
        } \
    } else { \
        if (!s->interval[n] || colorReset == 1) { \
            s->rgb[n] = func_002A7878((float)FloatToInt((float)s->color[n].minimum) * 0.01f, \
                                      (float)FloatToInt((float)s->color[n].maximum) * 0.01f); \
        } \
    } }
/* Updates a configured animated point light: radius, RGB cycles and attachment. */
void UpdateAnimatedPointLight(u8 *actor) {
    LightState *s;
    Vector sphere, origin, offset;
    u8 startup;
    int radiusReset, index;
    float low, high, intensity;
    if (!actor) return;
    s = *(LightState **)(actor + 0x68);
    radiusReset = 0;
    if (!s) return;
    if (!(u8)actor[0x20]) {
        actor[0x30] = 0xFF;
        startup = *((u8 *)&s->origin + 12); actor[0xBC] = startup;
        qcopy(&s->origin, (actor + 0x10));
        s->light = -1;
        *((u8 *)&s->origin + 12) = startup;
        *(u32 *)&s->offset.f[3] = s->flags;
        s->timer[0] = s->interval[0];
        s->timer[1] = s->interval[1];
        s->timer[2] = s->interval[2];
        s->timer[3] = s->interval[3];
        s->rgb[0] = IntToFloat(s->color[0].initial) * 0.01f;
        s->rgb[1] = IntToFloat(s->color[1].initial) * 0.01f;
        s->rgb[2] = IntToFloat(s->color[2].initial) * 0.01f;
        index = s->parentIndex;
        s->radius = s->initialRadius;
        if (index != -1) s->parent = g_moby_array_base[0] + index * 0x100;
        if (s->radiusRise < 0) s->radiusRise = -s->radiusRise;
        if (s->radiusFall < 0) s->radiusFall = -s->radiusFall;
        actor[0x20] = 1;
    }
    if ((u8)actor[0xBC]) { --((u8 *)actor)[0xBC]; return; }
    if (s->lifetime != -1 && math_fast_float_d(&s->lifetime)) {
        if (s->light != -1) { gfx_free_point_light(s->light); s->light = -1; }
        moby_mark_spawned(actor); return;
    }
    qcopy(&sphere, (actor + 0x10)); sphere.f[3] = s->radius;
    if (math_fast_helper_a(&sphere, 255) == -1) goto hidden;
    if (s->parent) qcopy(&origin, (s->parent + 0x10));
    else qcopy(&origin, &s->origin);
    if (!(s->flags & 0x800000)) {
        if (s->flags & 0x100000) {
            if (s->flags & 0x200000) {
                offset.f[0] = math_random_float_range(-s->offset.f[0], s->offset.f[0]);
                offset.f[1] = math_random_float_range(-s->offset.f[1], s->offset.f[1]);
                offset.f[2] = math_random_float_range(-s->offset.f[2], s->offset.f[2]);
            } else {
                u32 saved = *(u32 *)&s->offset.f[3]; s->offset.f[3] = 0;
                FastVecScale(&offset, &s->offset, math_random_float_range(s->offset.f[3], 1));
                *(u32 *)&s->offset.f[3] = saved;
            }
        } else {
            u32 saved = *(u32 *)&s->offset.f[3]; s->offset.f[3] = 0;
            qcopy(&offset, &s->offset); *(u32 *)&s->offset.f[3] = saved;
        }
        if ((s->flags & 0x400000) && s->parent) matrix_mul_vec3(&offset, &offset, s->parent + 0xC0);
        FastVecAdd(actor + 0x10, &origin, &offset);
    } else qcopy((actor + 0x10), &origin);
    if (s->interval[3] && FastDecTimer(&s->timer[3])) {
        s->timer[3] = s->interval[3];
        if (s->flags & 4) { radiusReset = 1; s->radius = s->minimumRadius; s->flags &= ~8; }
    }
    if (!(s->flags & 0x80000)) {
        if ((*(u64 *)&s->lifetime & 0x300000000ULL) == 0x200000000ULL) s->flags ^= 2;
        if (!(s->flags & 2)) {
            if (s->flags & 8) {
                s->radius -= s->radiusFall;
                if (s->radius <= s->minimumRadius) {
                    s->radius = s->minimumRadius;
                    if ((s->flags & 4) && !s->interval[3]) s->flags ^= 8;
                }
            } else {
                s->radius += s->radiusRise;
                if (s->maximumRadius <= s->radius) {
                    s->radius = s->maximumRadius;
                    if (!(s->flags & 1)) s->flags ^= 8;
                    else { s->flags = (s->flags | 2) ^ 8; s->delay[3] = s->hold[3]; }
                }
            }
        } else {
            if (s->hold[3] && vec_fast_helper_a(&s->delay[3])) s->flags ^= 2;
        }
    } else {
        if (!s->interval[3] || radiusReset == 1) s->radius = math_random_float_range(s->minimumRadius, s->maximumRadius);
    }
    UPDATE_COLOR(0, 0x10000, 0x3000000000ULL, 0x2000000000ULL, 0x20, 0x80, 0x10, 0x40);
    UPDATE_COLOR(1, 0x20000, 0x30000000000ULL, 0x20000000000ULL, 0x200, 0x800, 0x100, 0x400);
    UPDATE_COLOR(2, 0x40000, 0x300000000000ULL, 0x200000000000ULL, 0x2000, 0x8000, 0x1000, 0x4000);
    if (s->light == -1) {
        s->light = part_l00_alloc_effect_slot_2(actor + 0x10, s->radius * 0.8f, IntToFloat(s->intensity) * 0.01f, s->rgb[0], s->rgb[1], s->rgb[2]);
    } else {
        Vector *entry = g_light_table[s->light];
        qcopy(&entry[1], (actor + 0x10));
        entry[1].f[3] = s->radius * 0.8f;
        entry[0].f[0] = s->rgb[0]; entry[0].f[1] = s->rgb[1]; entry[0].f[2] = s->rgb[2];
        entry[0].f[3] = IntToFloat(s->intensity) * 0.01f;
    }
    return;
hidden:
    if (s->light != -1) { gfx_free_point_light(s->light); s->light = -1; }
}
