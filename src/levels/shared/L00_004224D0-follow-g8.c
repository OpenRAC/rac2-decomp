#include "common.h"

extern char D_L00_001B8E20[] NOT_SDA;
extern char D_00189F00[];
extern int D_0018A160 NOT_SDA;
extern float D_L00_001B14C4 __attribute__((sda));

extern void func_00282978(void *timer);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282D08(void *out, void *a, void *b, float t);
extern void func_00282D30(void *out, void *v, float k);
extern float func_00282DB0(void *a, void *b);
extern void func_00282DD8(void *out, void *a, void *b);
extern float func_00282DF0(void *v);
extern void func_00282F20(void *out, void *v, float length);
extern void func_002ACEC0(void *out, void *v, void *axis, float angle);
extern float func_002702C8(void *state, float current, float goal, float a, float b, float c);
extern float func_002703B0(void *state, float current, float goal, float a, float b, float c);
extern float func_002831B0(float x);
extern float func_00283248(float y, float x);
extern float func_00283BE0(float a, float b);
extern float func_00283CE0(int n);

#define F(p, n) (*(float *)((char *)(p) + (n)))

/* Final placement of follow camera CAM's basis for the frame (RAC1: follow_camera_build_view).
   In target mode 0xB it looks along the hero; otherwise it builds the forward row from the
   target-to-eye direction with the view axis at +0x20 projected off, eases the orbit and eye
   heights, pitches by the smoothed look angle clamped to +-70 degrees, blends out the start-up
   timer and re-orthogonalises the right and up rows. */
void func_L00_00425560(char *cam)
{
    char *view, *target, *settings, *state, *owner, *motion, *right, *up, *w;
    float g, r0, g2, d, r, e, t, x, h, g3, l;
    float v0[4], v1[4], v2[4], v3[4], v4[4];

    view = D_L00_001B8E20;
    target = *(char **)(cam + 0x70);
    settings = target + 0x60;
    state = target + 0x20;
    if (*(unsigned char *)(settings + 0xC4) == 0xB) {
        func_00282CF0(cam, D_00189F00, cam + 0x30);
        right = cam + 0x10;
        func_00282F20(cam, cam, 1.0f);
        up = cam + 0x20;
        func_00282978(state);
    } else {
        g = func_00282DB0(target + 0xA0, view + 0x20);
        func_00282D30(v0, view + 0x20, g);
        func_00282CF0(v1, target + 0xA0, v0);
        owner = *(char **)(cam + 0x70);
        motion = owner + 0x160;
        g = func_00282DB0(cam + 0x30, view + 0x20);
        func_00282D30(v0, view + 0x20, g);
        func_00282CF0(v2, cam + 0x30, v0);
        func_00282CF0(v3, v1, v2);
        if (F(state, 0x28) != 0.0f) {
            func_002ACEC0(v3, v3, view + 0x20, F(state, 0x28));
        }
        r0 = func_00282DF0(v3);
        if (0.05f <= r0) {
            func_00282D30(cam, v3, 1.0f / r0);
        } else {
            g = func_00282DB0(cam, view + 0x20);
            func_00282D30(v4, view + 0x20, g);
            func_00282CF0(cam, cam, v4);
        }
        w = cam + 0x10;
        func_00282DD8(w, cam, view + 0x20);
        func_00282F20(w, w, 1.0f);
        right = w;
        t = 0.0f;
        F(state, 0x8) = func_002702C8(state + 0x10, F(state, 0x8), F(motion, 0x30), 0.004f, 0.2f, 0.0f);
        up = cam + 0x20;
        g2 = func_002702C8(state + 0xC, F(state, 0x4), F(settings, 0xB0), 0.004f, 0.2f, 0.0f);
        d = F(state, 0x8) - g2;
        F(state, 0x4) = g2;
        func_00282D30(v0, view + 0x20, -func_00282DB0(motion + 0x10, view + 0x20));
        func_00282CF0(v0, v0, v3);
        w = (char *)v4;
        func_00282CF0(w, cam + 0x30, v0);
        func_00282D30(v0, view + 0x20, -d);
        func_00282CF0(w, w, v0);
        func_00282CF0(v3, w, cam + 0x30);
        r = func_00282DF0(v3);
        if (r != 0.0f) {
            e = func_00282DB0(cam, v3);
            e = 1.5707964f - func_002831B0(e / r);
            func_00282DD8(up, right, cam);
            if (func_00282DB0(up, v3) < 0.0f) {
                e = -e;
            }
            g3 = func_00282DB0(motion, view + 0x20);
            l = func_00282DF0(motion);
            if (D_0018A160) {
                x = func_00283248(l, g3) / D_L00_001B14C4;
                if (x < -0.1f) {
                    x = -x;
                    if (0.5f < x) {
                        x = 1.0f - x;
                    }
                    x = x + x;
                    t = x * 0.2617994248867035f;
                }
            }
            h = func_002703B0(state + 0x18, F(state, 0x14), t, F(state, 0x1C), F(state, 0x20), 0.0f);
            F(state, 0x14) = h;
            e = func_00283BE0(e, h);
            if (1.2217305898666382f < e) {
                e = 1.2217305898666382f;
            } else if (e < -1.2217305898666382f) {
                e = -1.2217305898666382f;
            }
            func_002ACEC0(cam, cam, right, e);
            func_00282F20(cam, cam, 1.0f);
        }
    }
    if (*(short *)state != 0) {
        func_00282978(state);
        x = func_00283CE0(*(short *)state);
        func_00282D08(cam, cam, cam + 0x40, x * F(state, 0x24));
        func_00282F20(cam, cam, 1.0f);
    }
    func_00282DD8(right, cam, view + 0x20);
    func_00282F20(right, right, 1.0f);
    func_00282DD8(up, right, cam);
}
