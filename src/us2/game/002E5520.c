#include "include_asm.h"

/* func_US2_002E5520, the USA v2.00 copy of func_002E4708: the same C, where adding the yaw at
   D_L00_001B8DC0[6] to the angle becomes rotating buf by func_002836E8 of the matrix at +0x230. */

extern float D_L00_001B8DC0[];

extern void func_00282CF0(void *dst, void *src, void *arg);
extern void func_002836E8(void *dst, void *src);
extern void func_00283098(void *dst, void *src, void *m);
extern float func_00283248(float a, float b);
extern float func_00283B98(float a, float b);
extern float func_00282E20(void *p);
extern float func_00283BE0(float a, float b);
extern int func_00283CF0(float a);

void func_US2_002E5520(void *self, void *other)
{
    struct AngleState { char reserved[0x40]; float angle; };
    struct AngleState *state = (struct AngleState *)self;
    float buf[4];
    float m[12];
    float w;
    float r;

    func_00282CF0(buf, other, D_L00_001B8DC0);
    func_002836E8(m, (char *)D_L00_001B8DC0 + 0x230);
    func_00283098(buf, buf, m);
    w = -func_00283248(buf[0], buf[1]);
    if (w < 0.0f)
        w += 6.283185307179586f;
    if (func_00282E20(buf) < 2.0f) {
        if (state->angle >= 0.0f) {
            r = func_00283BE0(w, state->angle);
            if (r > 0.2f) {
                w = func_00283B98(state->angle, 0.2f);
            } else if (r < -0.2f) {
                w = func_00283BE0(state->angle, 0.2f);
            }
            state->angle = w;
        } else {
            state->angle = w;
        }
    } else {
        state->angle = -1.0f;
    }
    func_00283CF0(w * 57.2957763671875f);
}
