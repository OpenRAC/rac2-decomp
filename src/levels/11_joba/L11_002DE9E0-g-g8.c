#include "common.h"

extern s32 func_00283CF0(f32 value);
extern void func_00282F20(void *out, void *in, f32 scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_L11_00397A30(void *moby);
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
/* Makes a target object swell and glow, then fade back to normal, as a short effect. */
void func_L11_003974A8(u8 *moby) {
    Grow_003974A8 *vars = *(Grow_003974A8 **)(moby + 0x68);
    f32 progress;

    switch (moby[0x20]) {
    case 0:
        vars->savedModeBits = vars->target->modeBits;
        vars->target->modeBits |= 0x100;
        vars->target->modeBits |= 8;
        vars->target->modeBits |= 2;
        vars->curExtent = 0;
        SpawnParticleBurst_L11(moby);
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        if (SetFirstPendingFlag(moby)) {
            vec_scale_to_length(vars, vars->target->points[vars->point], vars->speed * 0.016666668f);
            {
                f32 delta = D_L11_001AEC64 - D_L11_001AEC60;
                f32 step = delta / (f32)D_L11_001AEC68;
                vars->scale = D_L11_001AEC60;
                vars->scaleStep = step;
            }
            vars->target->modeBits &= 0xFFFE;
            vars->target->drawn = 1;
        }
        FastVecAdd(vars->target->pos, vars->target->pos, vars);
        vec_scale_to_length(vars->target->points[vars->point], vars->target->points[vars->point], vars->scale);
        vars->scale += vars->scaleStep;
        progress = IntToFloat(*(u16 *)(moby + 0x96)) / (f32)D_L11_001AEC68;
        vars->target->alpha = FloatToInt(progress * 128.0f);
        vars->curExtent = vars->extent * progress;
        vars->color = FastTweenColor(D_L11_001AEC78[0], D_L11_001AEC78[1], progress);
        if (*(u16 *)(moby + 0x96) > D_L11_001AEC68)
            SetMobyState(moby, 2, -1);
        break;
    case 2: {
        f32 fade;
        if (SetFirstPendingFlag(moby)) {
            vars->scaleStep = (vars->scale - 1.0f) / (f32)D_L11_001AEC6C;
            vars->target->alpha = 0x80;
            vars->target->modeBits &= 0xFFF7;
        }
        vec_scale_to_length(vars->target->points[vars->point], vars->target->points[vars->point], vars->scale);
        vars->scale += vars->scaleStep;
        fade = IntToFloat(*(u16 *)(moby + 0x96)) / (f32)D_L11_001AEC6C;
        vars->curExtent = vars->extent + -vars->extent * fade;
        vars->color = FastTweenColor(D_L11_001AEC78[1], D_L11_001AEC78[2], fade);
        if (*(u16 *)(moby + 0x96) > D_L11_001AEC6C) {
            vars->target->modeBits = vars->savedModeBits;
            vars->target->modeBits &= 0xFFFE;
            vars->target->drawn = 1;
            vec_scale_to_length(vars->target->points[vars->point], vars->target->points[vars->point], 1.0f);
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    }
    AddDrawCallbackToList3(DrawRandomRibbon, moby);
    AddDrawCallbackToList3(DrawFacingQuad, moby);
    if (*(u16 *)(moby + 0x96) < 0xFFFF)
        ++*(u16 *)(moby + 0x96);
}
