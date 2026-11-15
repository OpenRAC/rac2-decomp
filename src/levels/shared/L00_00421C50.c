#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; } Hero;
extern char g_hero_state[];
typedef struct {
    float pos[4];
    float vel[4];
    char pad20[0x30];
    float aim[4];
    char pad60[0x20];
    float size;
    char pad84[0x10];
    float near[4];
} Cam;
typedef struct {
    float base[4];
    float step[4];
    float mid[4];
    char pad30[0x20];
    float look[4];
    float target[4];
    float o70[4];
    float rate;
    char pad84[0x24];
    float a0;
    char padB4[0x20];
    short o;
} Dummy;
extern float math_step_spring_damper_clamped(void *, float, float, float, float, float);
extern int CollLine(void *, void *, int, int, int);
extern int FastDecTimer(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern float FastVecLength(void *);
extern void hero_copy_vector_to_out(void *, void *);
extern void weapon_update_held_anim_state(void *);
extern void cam_follow_compute_position(void *, void *);
extern void weapon_update_anim_blend(void *, void *);
extern void follow_camera_set_height(float, float);
extern float D_L00_001B14D0 __attribute__((sda));
extern int D_L00_001B184C MACRO_ADDR;
extern char *g_follow_camera_object[];
extern char D_L00_001B8E20[];
extern char D_L00_001BF220[];
#define HERO ((Hero *)D_00189E20)
/* Updates the follow camera each frame: eases its eye position and look-at point toward the target and pulls the camera in when a wall is in the way. */
void cam_follow_update_collision(char *moby)
{
    float out[4], a[4], b[4], c[4], d[4], e[4], f[4], g[4], h[4], i[4];
    float midpoint[4];
    char *camData = *(char **)(moby + 0x70);
    char *settings = camData + 0x60;
    char *motion = camData + 0x160;
    char *outVec = camData + 0x70;
    char *eyeOffset;
    char *cam = D_L00_001B8E20;
    char *pi;
    char *vp;
    float dist, scale, r, r2, dd;
    hero_copy_vector_to_out(moby, a);
    weapon_update_held_anim_state(moby);
    cam_follow_compute_position(moby, out);
    qcopy(camData + 0x70, out);
    qcopy(b, settings);
    eyeOffset = camData + 0xC0;
    dist = FastVecDot(cam + 0x30, eyeOffset);
    FastVecScale(c, cam + 0x30, dist);
    FastVecSub(d, eyeOffset, c);
    *(float *)(settings + 0xF0) = fast_vec_dist(c, outVec);
    c[0] = math_step_spring_damper_clamped(camData + 0xE0, c[0], *(float *)(settings + 0x10), *(float *)(settings + 0xE4), *(float *)(settings + 0xE8), 0.0f);
    c[1] = math_step_spring_damper_clamped(camData + 0xE4, c[1], *(float *)(settings + 0x14), *(float *)(settings + 0xE4), *(float *)(settings + 0xE8), 0.0f);
    c[2] = math_step_spring_damper_clamped(camData + 0xE8, c[2], *(float *)(settings + 0x18), *(float *)(settings + 0xE4), *(float *)(settings + 0xE8), 0.0f);
    d[0] = math_step_spring_damper_clamped(camData + 0xD0, d[0], *(float *)(settings + 0x0), *(float *)(settings + 0xDC), *(float *)(settings + 0xE0), 0.0f);
    d[1] = math_step_spring_damper_clamped(camData + 0xD4, d[1], *(float *)(settings + 0x4), *(float *)(settings + 0xDC), *(float *)(settings + 0xE0), 0.0f);
    d[2] = math_step_spring_damper_clamped(camData + 0xD8, d[2], *(float *)(settings + 0x8), *(float *)(settings + 0xDC), *(float *)(settings + 0xE0), 0.0f);
    FastVecAdd(settings, settings, outVec);
    FastVecAdd(eyeOffset, d, c);
    FastVecScale(e, cam + 0x20, *(float *)(settings + 0xB0));
    if (*(u8 *)(settings + 0xD6)) {
        *(short *)(settings + 0xD8) += 1;
        if (*(short *)(settings + 0xEC) < *(short *)(settings + 0xD8))
            *(short *)(settings + 0xD8) = *(short *)(settings + 0xEC);
        r = IntToFloat(*(short *)(settings + 0xD8));
        r = r / IntToFloat(*(short *)(settings + 0xEC));
        lerp_vector(f, settings, eyeOffset, r);
        FastVecAdd(camData + 0xA0, e, f);
    } else {
        FastDecTimer(camData + 0x138);
        if (*(short *)(settings + 0xD8) < 0)
            *(short *)(settings + 0xD8) = 0;
        r = IntToFloat(*(short *)(settings + 0xD8));
        r = r / IntToFloat(*(short *)(settings + 0xEC));
        lerp_vector(f, settings, eyeOffset, r);
        FastVecAdd(camData + 0xA0, e, f);
    }
    weapon_update_anim_blend(moby, e);
    if (HERO->b[0x22B4] == 2)
        FastVecScale(e, cam + 0x20, 3.0f);
    else if (HERO->b[0x22B4] == 1)
        FastVecScale(e, cam + 0x20, 0.4f);
    else if (HERO->i[0x8A7] == 0x11)
        qzero(e);
    else
        FastVecScale(e, cam + 0x20, 0.5f);
    FastVecAdd(f, a, e);
    FastVecScale(e, cam + 0x20, *(float *)(motion + 0x30));
    FastVecAdd(settings + 0x50, e, settings);
    {
        char *o = *(char **)(g_follow_camera_object[0] + 0x70);
        scale = D_L00_001B14D0 + *(float *)(o + 0x234) * *(float *)(o + 0x22C) * (*(float *)(o + 0x230) - 1.0f);
    }
    FastVecScale(g, cam + 0x20, 20.0f);
    FastVecAdd(g, f, g);
    if (CollLine(f, g, D_L00_001B184C, HERO->i[0x8A4], 0))
        qcopy(h, D_L00_001BF220);
    else
        qcopy(h, g);
    FastVecScale(g, cam + 0x20, 20.0f);
    FastVecSub(g, f, g);
    if (CollLine(f, g, D_L00_001B184C, HERO->i[0x8A4], 0))
        qcopy(g, D_L00_001BF220);
        FastVecSub(i, g, h);
    if (FastVecLength(i) < 2.0f * scale) {
        FastVecAdd(midpoint, h, g);
        FastVecScale(midpoint, midpoint, 0.5f);
        qcopy(settings + 0x50, midpoint);
        FastVecSub(i, midpoint, settings);
        follow_camera_set_height(FastVecDot(i, cam + 0x20), 0.006f);
        return;
    }
    FastVecSub(i, h, settings);
    dd = FastVecLength(i);
    r2 = *(float *)(motion + 0x30);
    if (dd <= r2 + scale) {
        FastVecScale(midpoint, cam + 0x20, scale);
        FastVecSub(midpoint, h, midpoint);
        qcopy(settings + 0x50, midpoint);
        FastVecSub(i, midpoint, settings);
        follow_camera_set_height(FastVecDot(i, cam + 0x20), 0.006f);
        return;
    }
    dd = FastVecDot(settings, cam + 0x30);
    if (FastVecDot(g, cam + 0x30) < dd)
        qcopy(g, settings);
    FastVecScale(e, cam + 0x20, r2);
    FastVecAdd(settings + 0x50, e, g);
}
