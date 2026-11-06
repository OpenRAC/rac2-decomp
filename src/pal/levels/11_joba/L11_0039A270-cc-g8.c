/* func_PAL_L11_0039A270, the PAL copy of func_L11_003974A8: the same C, where rename func_L11_00397A30 becomes func_PAL_L11_0039A880; scale (f32)D_L11_001AEC68; scale D_L11_001AEC68; scale (f32)D_L11_001AEC6C; wrap func_00283D38(D_L11_001AEC78[1], D_L11_001AEC78[2], fad; wrap D_L11_001AEC6C (((int)({e}) * 5 + 2) / 6); rewrap (*(u16 *)(obj + 0x96)  becomes  (((int)(D_L11_001AEC6C) * 5 +; rewrap D_L11_001AEC6C; rewrap D_L11_001AEC68. */
#include "common.h"

extern s32 func_00283CF0(f32 value);
extern void func_00282F20(void *out, void *in, f32 scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_PAL_L11_0039A880(void *moby);
extern void func_002A7750(void *moby, s32 state, s32 arg);
extern void func_0029F338(void *moby);
extern void func_L00_002E6EF8(void (*callback)(void *), void *moby);
extern s32 func_002B3868(void *moby);
extern s32 func_00283D38(s32 from, s32 to, f32 t);
extern f32 func_00283CE0(s32 value);
extern void func_L11_003982F0(void *moby);
extern void func_L11_00397820(void *moby);
extern f32 D_L11_001AEC60 __attribute__((sda));
extern f32 D_L11_001AEC64 __attribute__((sda));
extern s32 D_L11_001AEC68 __attribute__((sda));
extern s32 D_L11_001AEC6C __attribute__((sda));
/* Three words interpolated pairwise by func_00283D38. Declared as an incomplete sda array:
   element 0 is a one-instruction load (retail's GP form in a call's delay slot), elements 1
   and 2 are constant-offset macro loads that stay out of delay slots and assemble absolute. */
extern s32 D_L11_001AEC78[] __attribute__((sda));

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[3];
    u8 alpha;
    u8 pad24[0x31 - 0x24];
    u8 drawn;
    u8 pad32[2];
    u16 modeBits;
    u8 pad36[0xC0 - 0x36];
    f32 points[1][4];
} Target_003974A8;

typedef struct {
    f32 velocity[4];
    Target_003974A8 *target;
    s32 savedModeBits;
    f32 scale;
    f32 scaleStep;
    f32 speed;
    s32 point;
    f32 extent;
    f32 curExtent;
    s32 color;
} Grow_003974A8;

/* Three-state controller: saves and sets its target moby's mode bits; then, for
   D_L11_001AEC68 frames, moves the target by its velocity, scales one of the target's
   vectors by a growing factor and raises the target's alpha; then, for D_L11_001AEC6C
   frames, scales back toward 1 before restoring the mode bits and freeing itself. Every
   frame it queues func_L11_003982F0 and func_L11_00397820 with itself. */
void func_PAL_L11_0039A270(u8 *obj) {
    Grow_003974A8 *ctx = *(Grow_003974A8 **)(obj + 0x68);
    f32 t;

    switch (obj[0x20]) {
    case 0:
        ctx->savedModeBits = ctx->target->modeBits;
        ctx->target->modeBits |= 0x100;
        ctx->target->modeBits |= 8;
        ctx->target->modeBits |= 2;
        ctx->curExtent = 0;
        func_PAL_L11_0039A880(obj);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (func_002B3868(obj)) {
            func_00282F20(ctx, ctx->target->points[ctx->point], ctx->speed * 0.020000001f);
            {
                f32 delta = D_L11_001AEC64 - D_L11_001AEC60;
                f32 step = delta / (f32)D_L11_001AEC68;
                ctx->scale = D_L11_001AEC60;
                ctx->scaleStep = step;
            }
            ctx->target->modeBits &= 0xFFFE;
            ctx->target->drawn = 1;
        }
        func_00282CC0(ctx->target->pos, ctx->target->pos, ctx);
        func_00282F20(ctx->target->points[ctx->point], ctx->target->points[ctx->point], ctx->scale);
        ctx->scale += ctx->scaleStep;
        t = func_00283CE0(*(u16 *)(obj + 0x96)) / (f32)(((int)(D_L11_001AEC68) * 5 + 2) / 6);
        ctx->target->alpha = func_00283CF0(t * 128.0f);
        ctx->curExtent = ctx->extent * t;
        ctx->color = func_00283D38(D_L11_001AEC78[0], D_L11_001AEC78[1], t);
        if (*(u16 *)(obj + 0x96) > (((int)(D_L11_001AEC68) * 5 + 2) / 6))
            func_002A7750(obj, 2, -1);
        break;
    case 2: {
        f32 fade;
        if (func_002B3868(obj)) {
            ctx->scaleStep = (ctx->scale - 1.0f) / (f32)D_L11_001AEC6C;
            ctx->target->alpha = 0x80;
            ctx->target->modeBits &= 0xFFF7;
        }
        func_00282F20(ctx->target->points[ctx->point], ctx->target->points[ctx->point], ctx->scale);
        ctx->scale += ctx->scaleStep;
        fade = func_00283CE0(*(u16 *)(obj + 0x96)) / (f32)(((int)(D_L11_001AEC6C) * 5 + 2) / 6);
        ctx->curExtent = ctx->extent + -ctx->extent * fade;
        ctx->color = func_00283D38(D_L11_001AEC78[1], D_L11_001AEC78[2], fade);
        if (((int)((*(u16 *)(obj + 0x96) > (((int)(D_L11_001AEC6C) * 5 + 2) / 6))) * 5 + 2) / 6) {
            ctx->target->modeBits = ctx->savedModeBits;
            ctx->target->modeBits &= 0xFFFE;
            ctx->target->drawn = 1;
            func_00282F20(ctx->target->points[ctx->point], ctx->target->points[ctx->point], 1.0f);
            func_0029F338(obj);
            return;
        }
        break;
    }
    }
    func_L00_002E6EF8(func_L11_003982F0, obj);
    func_L00_002E6EF8(func_L11_00397820, obj);
    if (*(u16 *)(obj + 0x96) < 0xFFFF)
        ++*(u16 *)(obj + 0x96);
}
