#include "names.h"
/* func_L16_0041F360: own -G8 unit (default game profile by name). */
#include "common.h"

extern f32 g_ribbon_inner_uv_start __attribute__((sda));
extern u32 g_ribbon_l16_inner_color __attribute__((sda));
extern s32 g_ribbon_l16_param_a __attribute__((sda));
extern u32 g_ribbon_l16_outer_color[] MACRO_ADDR;
extern s32 g_ribbon_l16_param_b[] MACRO_ADDR;
extern f32 g_ribbon_inner_uv_end[] MACRO_ADDR;
extern f32 g_ribbon_outer_uv_start[] MACRO_ADDR;
extern f32 g_ribbon_outer_uv_end[] MACRO_ADDR;
extern char g_particle_template[] MACRO_ADDR;
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecAdd(char *, char *, char *);
extern void make_hit_descriptor(char *, char *, s32, char *, f32);
extern s32 CollLine(char *, char *, s32, char *, char *);
extern u32 FastTweenColor(u32, u32, f32);
extern void DrawTwoLayerPolylineRibbon(char *, s32, s32, s32, u32, u32, f32, f32, f32);

/* Constructs and clips the expanding ring, then draws its two surfaces. */
