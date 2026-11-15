#include "common.h"

extern char D_L00_001B8E20[] NOT_SDA;
extern char D_00189F00[];
extern int D_0018A160 NOT_SDA;
extern float D_L00_001B14C4 __attribute__((sda));

extern int FastDecTimer(void *timer);
extern void FastVecSub(void *out, void *a, void *b);
extern void lerp_vector(void *out, void *a, void *b, float t);
extern void FastVecScale(void *out, void *v, float k);
extern float FastVecDot(void *a, void *b);
extern void FastVecCross(void *out, void *a, void *b);
extern float FastVecLength(void *v);
extern void vec_scale_to_length(void *out, void *v, float length);
extern void math_apply_axis_rotation_to_quat(void *out, void *v, void *axis, float angle);
extern float math_step_spring_damper_clamped(void *state, float current, float goal, float a, float b, float c);
extern float math_step_spring_damper_stored(void *state, float current, float goal, float a, float b, float c);
extern float math_fast_angle_helper(float x);
extern float mat_fast_helper_a(float y, float x);
extern float fast_subtract_rotations(float a, float b);
extern float IntToFloat(int n);

#define F(p, n) (*(float *)((char *)(p) + (n)))

/* Final placement of follow camera CAM's basis for the frame (RAC1: follow_camera_build_view).
   In target mode 0xB it looks along the hero; otherwise it builds the forward row from the
   target-to-eye direction with the view axis at +0x20 projected off, eases the orbit and eye
   heights, pitches by the smoothed look angle clamped to +-70 degrees, blends out the start-up
   timer and re-orthogonalises the right and up rows. */
void follow_camera_build_view(char *cam)
{
    char *view, *target, *settings, *state, *owner, *motion, *right, *up, *w;
    float g, r0, g2, d, r, e, t, x, h, g3, l;
    float v0[4], v1[4], v2[4], v3[4], v4[4];

    view = D_L00_001B8E20;
    target = *(char **)(cam + 0x70);
    settings = target + 0x60;
    state = target + 0x20;
    if (*(unsigned char *)(settings + 0xC4) == 0xB) {
        FastVecSub(cam, D_00189F00, cam + 0x30);
        right = cam + 0x10;
        vec_scale_to_length(cam, cam, 1.0f);
        up = cam + 0x20;
        FastDecTimer(state);
    } else {
        g = FastVecDot(target + 0xA0, view + 0x20);
        FastVecScale(v0, view + 0x20, g);
        FastVecSub(v1, target + 0xA0, v0);
        owner = *(char **)(cam + 0x70);
        motion = owner + 0x160;
        g = FastVecDot(cam + 0x30, view + 0x20);
        FastVecScale(v0, view + 0x20, g);
        FastVecSub(v2, cam + 0x30, v0);
        FastVecSub(v3, v1, v2);
        if (F(state, 0x28) != 0.0f) {
            math_apply_axis_rotation_to_quat(v3, v3, view + 0x20, F(state, 0x28));
        }
        r0 = FastVecLength(v3);
        if (0.05f <= r0) {
            FastVecScale(cam, v3, 1.0f / r0);
        } else {
            g = FastVecDot(cam, view + 0x20);
            FastVecScale(v4, view + 0x20, g);
            FastVecSub(cam, cam, v4);
        }
        w = cam + 0x10;
        FastVecCross(w, cam, view + 0x20);
        vec_scale_to_length(w, w, 1.0f);
        right = w;
        t = 0.0f;
        F(state, 0x8) = math_step_spring_damper_clamped(state + 0x10, F(state, 0x8), F(motion, 0x30), 0.004f, 0.2f, 0.0f);
        up = cam + 0x20;
        g2 = math_step_spring_damper_clamped(state + 0xC, F(state, 0x4), F(settings, 0xB0), 0.004f, 0.2f, 0.0f);
        d = F(state, 0x8) - g2;
        F(state, 0x4) = g2;
        FastVecScale(v0, view + 0x20, -FastVecDot(motion + 0x10, view + 0x20));
        FastVecSub(v0, v0, v3);
        w = (char *)v4;
        FastVecSub(w, cam + 0x30, v0);
        FastVecScale(v0, view + 0x20, -d);
        FastVecSub(w, w, v0);
        FastVecSub(v3, w, cam + 0x30);
        r = FastVecLength(v3);
        if (r != 0.0f) {
            e = FastVecDot(cam, v3);
            e = 1.5707964f - math_fast_angle_helper(e / r);
            FastVecCross(up, right, cam);
            if (FastVecDot(up, v3) < 0.0f) {
                e = -e;
            }
            g3 = FastVecDot(motion, view + 0x20);
            l = FastVecLength(motion);
            if (D_0018A160) {
                x = mat_fast_helper_a(l, g3) / D_L00_001B14C4;
                if (x < -0.1f) {
                    x = -x;
                    if (0.5f < x) {
                        x = 1.0f - x;
                    }
                    x = x + x;
                    t = x * 0.2617994248867035f;
                }
            }
            h = math_step_spring_damper_stored(state + 0x18, F(state, 0x14), t, F(state, 0x1C), F(state, 0x20), 0.0f);
            F(state, 0x14) = h;
            e = fast_subtract_rotations(e, h);
            if (1.2217305898666382f < e) {
                e = 1.2217305898666382f;
            } else if (e < -1.2217305898666382f) {
                e = -1.2217305898666382f;
            }
            math_apply_axis_rotation_to_quat(cam, cam, right, e);
            vec_scale_to_length(cam, cam, 1.0f);
        }
    }
    if (*(short *)state != 0) {
        FastDecTimer(state);
        x = IntToFloat(*(short *)state);
        lerp_vector(cam, cam, cam + 0x40, x * F(state, 0x24));
        vec_scale_to_length(cam, cam, 1.0f);
    }
    FastVecCross(right, cam, view + 0x20);
    vec_scale_to_length(right, right, 1.0f);
    FastVecCross(up, right, cam);
}
