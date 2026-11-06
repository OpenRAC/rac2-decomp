/* func_PAL_003287E0, the PAL copy of func_00327038: the same C. */
#include "common.h"

/* The two small constants this probe reads through $gp, and the world axis
   beside them, which is too large for $gp and is reached with a full address. */
extern float D_001B0108 __attribute__((sda)), D_001B010C __attribute__((sda));
extern float D_001B27B0[4] __attribute__((sda));
extern int D_001B27C8;
/* The collision result: the object hit at +0x18, then vectors at +0x20 (the
   hit point), +0x30 and +0x40. */
extern char D_001BAF80[32];
extern float D_001BAFA0[12], D_001BAFB0[4];

extern float func_00282C48(float);
extern void func_00282C88(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282D90(void *, void *, float);
extern int func_00278870(void *, float);
extern float func_00283CE0(int), func_00283180(float), func_00283198(float);
extern void func_002837D0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);

/* The thirty-two-step probe of an object: sweeps a quarter turn, casting a
   line from a point offset along the world axis at each step, and moves the
   object by the average of the hits. A hit on an object whose record has type
   5 changes both states. Keep the pointer locals, in this order: spilled, they
   take the stack slots after count, and only the position's address is left
   to gcse. */
void func_PAL_003287E0(char *self)
{
    float origin[4], total[4], offset[4], rotated[4], quat[4], temp[4];
    float inverse[4], end[4], opposite[4], normal[4], hit[4];
    char *state = *(char **)(self + 0x68);
    int negative, count;
    char *rowD, *rowE;
    float *inverse_ptr, *end_ptr;
    char *result;
    int i;
    float angle, sine;

    if (func_00282C48(*(float *)(state + 0x18)) < 0.0001f)
        return;
    negative = *(float *)(state + 0x18) <= 0.0f;
    func_00282C88(total);
    func_00282F20(origin, D_001B27B0, -D_001B0108);
    count = 0;
    func_00282CC0(origin, origin, self + 0x10);
    if (!D_001B27C8 && func_00278870(origin, D_001B010C)) {
        func_00282CF0(offset, D_001BAFB0, origin);
        func_00282CC0(self + 0x10, offset, self + 0x10);
    }
    end_ptr = end;
    rowD = self + 0xD0;
    rowE = self + 0xE0;
    inverse_ptr = inverse;
    for (i = 0; i < 32; i++) {
        angle = func_00283CE0(i);
        angle /= func_00283CE0(31);
        func_00282F20(offset, rowD, D_001B010C);
        angle *= 1.57079637f;
        sine = func_00283198(angle);
        if (!negative)
            sine = -sine;
        func_00282D30(quat, rowE, sine);
        quat[3] = func_00283180(angle);
        inverse[0] = -quat[0];
        inverse[1] = -quat[1];
        inverse[2] = -quat[2];
        inverse[3] = quat[3];
        func_002837D0(temp, quat, offset);
        func_002837D0(rotated, temp, inverse_ptr);
        func_00282CC0(end, rotated, origin);
        if (func_002761F8(origin, end, 0, self, 0)) {
            count++;
            func_00282D30(opposite, D_001B27B0, -1.0f);
            func_00282D30(normal, D_001BAFA0 + 8, 0.0009765625f);
            func_00282F20(normal, normal, 1.0f);
            func_00282CF0(hit, D_001BAFA0, end_ptr);
            func_00282CC0(total, total, hit);
            result = D_001BAF80;
            if (*(char **)(result + 0x18) != 0
                && *(short *)(*(char **)(*(char **)(result + 0x18) + 0x24) + 0x46) == 5) {
                *(unsigned char *)(self + 0x20) = 9;
                *(int *)(state + 0x20) = 8;
            }
        }
    }
    if (count) {
        func_00282D90(total, total, (float)count);
        func_00282CC0(self + 0x10, self + 0x10, total);
    }
}
