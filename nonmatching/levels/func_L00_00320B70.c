/* func_L00_00320B70 - 572 bytes.  Worker attempt, 27 October 2026 (draft below).

   Size and structure right (nop pair before div.s and everything else came
   out natively). 5 masked diff lines only:
   1) prologue: retail daddu s1,t0 before mov.s f24,f15 (schedule)
   2) branch1 second call func_002EE220(axis,quat,vec): retail a1=s0 (quat)
   after daddu s1,s0; mine a1=s1 (cse picks the param reg). Tried side=quat
   before/after, tmp pointer, one work[] array.
   3) before func_002EE3D0: retail daddu a1,s5 then mov.s f12,f0; mine
   swapped.
   Logic: align vec to direction (to-from) with a quaternion limited by
   func_002D7BB8 (angle), 0.5 half angle, func_002EE6F8/6E0 sin/cos,
   func_L00_003208B0 applies it, qcopy to out. */

/* new file src/levels/shared/L00_00320B70.c (default flags -O2 -G0 so far; check cflags for a default line); remove INCLUDE_ASM from L00_00316F60.c. Only level 00 compiled. */
#include "common.h"

extern void func_002EE138(char *, char *, char *);
extern float func_002EE238(char *);
extern void func_002EE220(char *, char *, char *);
extern float func_002EE1F8(char *, char *);
extern float func_002EE710(float);
extern float func_002D7BB8(int, float, float, float, float, float);
extern float func_002EE6F8(float);
extern void func_002EE3D0(float, char *, char *);
extern float func_002EE6E0(float);
extern void func_L00_003208B0(char *, char *, char *);

void func_L00_00320B70(char *from, char *vec, char *to, int mode, float p0, float p1, float p2, float p3,
                       char *side, char *out)
{
    char delta[16];
    char axis[16];
    char quat[16];
    float length;
    float dot;
    float norm;
    float angle;
    float half;

    func_002EE138(delta, to, from);
    length = func_002EE238(delta);
    if (length == 0.0f)
        return;
    func_002EE220(axis, delta, vec);
    dot = func_002EE1F8(vec, delta);
    norm = func_002EE238(vec);
    norm *= func_002EE238(delta);
    if (norm == 0.0f)
        return;
    angle = 1.5707964f - func_002EE710(dot / norm);
    if (angle > 2.8798f) {
        char *tmp = quat;

        func_002EE220(tmp, vec, side);
        side = tmp;
        func_002EE220(axis, tmp, vec);
    } else {
        side = quat;
        if (length < p3 && angle < 1.5707965f) {
            p1 = 1.0f;
            p0 = 0.5f;
        }
    }
    half = func_002D7BB8(mode, 0.0f, angle, p0, p1, p2) * 0.5f;
    func_002EE3D0(func_002EE6F8(half), side, axis);
    *(float *)(quat + 12) = func_002EE6E0(half);
    func_L00_003208B0(vec, vec, side);
    if (out != 0)
        qcopy(out, side);
}
