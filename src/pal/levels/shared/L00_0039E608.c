#include "common.h"
#include "include_asm.h"



typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;
typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;
extern void func_002FDBD8_1(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_PAL_L00_003A06F8(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_1(1.0f, context, context->vector_10, 0);
    }
}

extern int D_18C0B4;
extern void func_002A7470(char *object, int mode, int a2, int a3);

/* The mode word at 0x18C0B4 must be 8 and the object's byte 0x43 must not be 6; the
 * helper then takes the object with mode 6, zero and ten. */
void func_PAL_L00_003A0730(char *object)
{
    if (D_18C0B4 == 8) {
        if (*(unsigned char *)(object + 0x43) != 6)
            func_002A7470(object, 6, 0, 8);
    }
}

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
extern char *D_L00_001B1E9C[] __attribute__((sda));
extern Vector D_L00_001C6F40[8][2];
extern float func_00283CE0(int), func_002A7878(float, float);
extern int func_00283CF0(float), func_00282948(int *), func_00282978(u16 *), func_002829A8(u8 *), func_00283DB8(void *, float);
extern void func_00291450(int), func_0029F338(void *), func_00282D30(void *, void *, float), func_00283098(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
/* The retail code checks flag pairs through the aligned lifetime/flags doubleword. */
/* colorReset mirrors the radius cycle's reset flag but no colour path sets it: retail keeps the
 * constant test (li v0,1; bnel v0,zero), so a nonzero interval never randomizes the channel. */
#define UPDATE_COLOR(n, randomFlag, pairMask, pairValue, pauseFlag, downFlag, topFlag, bottomFlag) { int colorReset = 0; \
    if (s->interval[n] && func_00282978(&s->timer[n])) { \
        s->timer[n] = ((s32)s->interval[n] * 5 + 2) / 6; \
        s->rgb[n] = (float)s->color[n].minimum; \
        s->flags &= ~(downFlag); \
    } \
    if (!(s->flags & (randomFlag))) { \
        if ((*(u64 *)&s->lifetime & (pairMask)) == (pairValue)) s->flags ^= (pauseFlag); \
        if (!(s->flags & (pauseFlag))) { \
            if (s->flags & (downFlag)) { \
                low = func_00283CE0(s->color[n].minimum) * 0.01f; \
                s->rgb[n] -= func_00283CE0(s->color[n].fall) * 0.012f; \
                if (s->rgb[n] <= low) { \
                    s->rgb[n] = low; \
                    if ((s->flags & (bottomFlag)) && !s->interval[n]) s->flags ^= (downFlag); \
                } \
            } else { \
                high = func_00283CE0(s->color[n].maximum) * 0.01f; \
                s->rgb[n] += func_00283CE0(s->color[n].rise) * 0.012f; \
                if (high <= s->rgb[n]) { \
                    s->rgb[n] = high; \
                    if (!(s->flags & (topFlag))) s->flags ^= (downFlag); \
                    else { s->delay[n] = ((s32)s->hold[n] * 5 + 2) / 6; s->flags = (s->flags | (pauseFlag)) ^ (downFlag); } \
                } \
            } \
        } else { \
            if (s->hold[n] && func_002829A8(&s->delay[n])) s->flags ^= (pauseFlag); \
        } \
    } else { \
        if (!s->interval[n] || colorReset == 1) { \
            s->rgb[n] = func_002A7878((float)func_00283CF0((float)s->color[n].minimum) * 0.01f, \
                                      (float)func_00283CF0((float)s->color[n].maximum) * 0.01f); \
        } \
    } }
/* func_PAL_L00_003A0950, the PAL copy of func_L00_0039D598: the same C, where the 50 Hz build scales
 * the radius and colour timers and hold delays by 5/6 and the radius and colour steps by 1.2, and each
 * hold arm sets the delay before the flags. */
/* Updates a configured animated point light: radius, RGB cycles and attachment. */
void func_PAL_L00_003A0950(u8 *actor) {
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
        s->rgb[0] = func_00283CE0(s->color[0].initial) * 0.01f;
        s->rgb[1] = func_00283CE0(s->color[1].initial) * 0.01f;
        s->rgb[2] = func_00283CE0(s->color[2].initial) * 0.01f;
        index = s->parentIndex;
        s->radius = s->initialRadius;
        if (index != -1) s->parent = D_L00_001B1E9C[0] + index * 0x100;
        if (s->radiusRise < 0) s->radiusRise = -s->radiusRise;
        if (s->radiusFall < 0) s->radiusFall = -s->radiusFall;
        actor[0x20] = 1;
    }
    if ((u8)actor[0xBC]) { --((u8 *)actor)[0xBC]; return; }
    if (s->lifetime != -1 && func_00282948(&s->lifetime)) {
        if (s->light != -1) { func_00291450(s->light); s->light = -1; }
        func_0029F338(actor); return;
    }
    qcopy(&sphere, (actor + 0x10)); sphere.f[3] = s->radius;
    if (func_00283DB8(&sphere, 255) == -1) goto hidden;
    if (s->parent) qcopy(&origin, (s->parent + 0x10));
    else qcopy(&origin, &s->origin);
    if (!(s->flags & 0x800000)) {
        if (s->flags & 0x100000) {
            if (s->flags & 0x200000) {
                offset.f[0] = func_002A7878(-s->offset.f[0], s->offset.f[0]);
                offset.f[1] = func_002A7878(-s->offset.f[1], s->offset.f[1]);
                offset.f[2] = func_002A7878(-s->offset.f[2], s->offset.f[2]);
            } else {
                u32 saved = *(u32 *)&s->offset.f[3]; s->offset.f[3] = 0;
                func_00282D30(&offset, &s->offset, func_002A7878(s->offset.f[3], 1));
                *(u32 *)&s->offset.f[3] = saved;
            }
        } else {
            u32 saved = *(u32 *)&s->offset.f[3]; s->offset.f[3] = 0;
            qcopy(&offset, &s->offset); *(u32 *)&s->offset.f[3] = saved;
        }
        if ((s->flags & 0x400000) && s->parent) func_00283098(&offset, &offset, s->parent + 0xC0);
        func_00282CC0(actor + 0x10, &origin, &offset);
    } else qcopy((actor + 0x10), &origin);
    if (s->interval[3] && func_00282978(&s->timer[3])) {
        s->timer[3] = ((s32)s->interval[3] * 5 + 2) / 6;
        if (s->flags & 4) { radiusReset = 1; s->radius = s->minimumRadius; s->flags &= ~8; }
    }
    if (!(s->flags & 0x80000)) {
        if ((*(u64 *)&s->lifetime & 0x300000000ULL) == 0x200000000ULL) s->flags ^= 2;
        if (!(s->flags & 2)) {
            if (s->flags & 8) {
                s->radius -= s->radiusFall * 1.2f;
                if (s->radius <= s->minimumRadius) {
                    s->radius = s->minimumRadius;
                    if ((s->flags & 4) && !(((s32)s->interval[3] * 5 + 2) / 6)) s->flags ^= 8;
                }
            } else {
                s->radius += s->radiusRise * 1.2f;
                if (s->maximumRadius <= s->radius) {
                    s->radius = s->maximumRadius;
                    if (!(s->flags & 1)) s->flags ^= 8;
                    else { s->delay[3] = ((s32)s->hold[3] * 5 + 2) / 6; s->flags = (s->flags | 2) ^ 8; }
                }
            }
        } else {
            if (s->hold[3] && func_002829A8(&s->delay[3])) s->flags ^= 2;
        }
    } else {
        if (!s->interval[3] || radiusReset == 1) s->radius = func_002A7878(s->minimumRadius, s->maximumRadius);
    }
    UPDATE_COLOR(0, 0x10000, 0x3000000000ULL, 0x2000000000ULL, 0x20, 0x80, 0x10, 0x40);
    UPDATE_COLOR(1, 0x20000, 0x30000000000ULL, 0x20000000000ULL, 0x200, 0x800, 0x100, 0x400);
    UPDATE_COLOR(2, 0x40000, 0x300000000000ULL, 0x200000000000ULL, 0x2000, 0x8000, 0x1000, 0x4000);
    if (s->light == -1) {
        s->light = func_L00_002FCF18(actor + 0x10, s->radius * 0.8f, func_00283CE0(s->intensity) * 0.01f, s->rgb[0], s->rgb[1], s->rgb[2]);
    } else {
        Vector *entry = D_L00_001C6F40[s->light];
        qcopy(&entry[1], (actor + 0x10));
        entry[1].f[3] = s->radius * 0.8f;
        entry[0].f[0] = s->rgb[0]; entry[0].f[1] = s->rgb[1]; entry[0].f[2] = s->rgb[2];
        entry[0].f[3] = func_00283CE0(s->intensity) * 0.01f;
    }
    return;
hidden:
    if (s->light != -1) { func_00291450(s->light); s->light = -1; }
}

/* func_PAL_L00_003A1688 is defined in L00_0039E608-rail.c. */
