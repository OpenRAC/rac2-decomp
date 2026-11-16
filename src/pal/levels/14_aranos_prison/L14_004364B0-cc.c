#include "names.h"
/* func_PAL_L14_004364B0, the PAL copy of func_L14_00430B70: the same C, where rename func_L14_004308D0 becomes func_PAL_L14_00436790; wrap func_00282948(s+0x50+i*4) (((int)({e}) * 5 + 2) / 6); wrap (((int)(func_00282948(s+0x50+i*4)) * 5 + 2) / 6) (((int; wrap (int)((float)*(int *)(s+0x10) / ((PrisonVisualState *)s; wrap ((int)((((int)(func_00282948(s+0x50+i*4)) * 5 + 2) / 6); lit 5 becomes 6; lit 6 becomes 5; rewrap (int)((float)*(int *)(s+0x10) / ((PrisonVisualState *; rename func_PAL_L14_00436790 becomes func_L14_004308D0; rename func_L14_00430E08 becomes func_PAL_L14_00436790. */
#include "common.h"
typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void gfx_draw_rotated_billboard(void *, int, int, int, float, float, float);
extern float math_wrap_angle_full_turn(float);
extern void part_draw_spark_quads_pal(void *);
extern int math_fast_float_d(void *);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern float FastAddRotations(float, float);

/* Draws the pulse effect's billboards: the base, two rotating fading sprites and the spark quads. (PAL: 50 Hz timings) */
void prison_animated_quads_draw_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int i;
    unsigned int color;
    float progress, scale, angle;
    gfx_draw_rotated_billboard(moby + 0x10, *(int *)(vars+0xb8), *(int *)(vars+0xc0), 1,
        *(float *)(vars+0xbc) * *(float *)(vars+0x80), *(float *)(vars+0x80)*0.5f, 0.0f);
    for (i=0; i<2; i++) {
        if (((((int)(((int)(math_fast_float_d(vars+0x50+i*4)) * 6 + 2)) * 5 + 2) / 6) / 5))
            ((PrisonVisualState *)vars)->timer[i] = (((int)((int)((float)*(int *)(vars+0x10) / ((PrisonVisualState *)vars)->rate[i])) * 5 + 2) / 6);
        progress = 1.0f - (float)((PrisonVisualState *)vars)->timer[i] /
            (float)(((int)((int)((float)*(int *)(vars+0x10) / ((PrisonVisualState *)vars)->rate[i])) * 5 + 2) / 6);
        if (*(float *)(vars+0x14) < progress) {
            color = ((PrisonVisualState *)vars)->end[i];
            color = (color & 0xffffff) + (((int)((1.0f-progress)/(1.0f-*(float *)(vars+0x14))*80.0f)+48)<<24);
        } else {
            color = FastTweenColor(((PrisonVisualState *)vars)->start[i], ((PrisonVisualState *)vars)->end[i], progress / *(float *)(vars+0x14));
            color = (color & 0xffffff) + (((int)(progress / *(float *)(vars+0x14)*80.0f)+48)<<24);
        }
        scale = *(float *)(vars+0x80) * *(float *)(vars+0x18);
        angle = math_wrap_angle_full_turn(progress * (((PrisonVisualState *)vars)->angle[i] * 6.2831855f));
        gfx_draw_rotated_billboard(moby+0x10, *(int *)(vars+0x1c), color, 1, scale, *(float *)(vars+0x80)*0.5f, angle + -3.1415927f);
    }
    *(float *)vars = FastAddRotations(*(float *)vars, 0.007f);
    gfx_draw_rotated_billboard(moby+0x10, *(int *)(vars+4), *(int *)(vars+12), 1,
        *(float *)(vars+8)* *(float *)(vars+0x80), *(float *)(vars+0x80)*0.5f, *(float *)vars);
    part_draw_spark_quads_pal(moby);
}

void part_draw_spark_quads_pal(void *arg);
