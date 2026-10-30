/* Complete C reconstruction; not linked and no matching credit.
 * 2026-10-30, game -O2 -G0 -ffunction-sections:
 * 808/812 bytes, USA v1.01 0/1 and USA v2.00 0/1. PAL identity absent.
 * The five aligned vectors span 80 bytes and produce the retail 0xB0 frame.
 * Keeping the next frame index across integer-to-float conversion restores the
 * complete saved-register assignment. Remaining differences are the two table
 * address additions, frame-5/frame-15 branch structure, emitter argument setup
 * and the invariant lifetime constant. Five source/call-shape trials; guarded
 * shared-call and switch variants gave 800 and 816 bytes respectively.
 * Reopen with an independently matching animation-event CFG/loop invariant
 * witness. The spawner keeps its real pointer result and both EE argument banks.
 */
#include "common.h"

extern int func_L01_00321178(void *, void *);
extern float func_0029F530(void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283248(float, float);
extern void func_002B5278(void *, float);
extern float func_002A89A8(void *, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_002A7A00(void *, float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern char *func_002BDCE8(void *, int, void *, int, int,
                         float, float, float, float);
extern float D_L04_002AF630[];

void func_L04_003E5B10(u8 *object, float *target)
{
    float motion[4] __attribute__((aligned(16)));
    float origin[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float phase;
    int frame;
    int i;
    int next;

    if (object[0x42] != object[0x43]) {
        func_L01_00321178(object, target);
        return;
    }
    phase = func_0029F530(object);
    frame = func_00283CF0(phase);
    next = frame + 1;
    phase -= func_00283CE0(frame);
    func_00282D30(motion, object + 0xC0,
        D_L04_002AF630[frame] +
        (D_L04_002AF630[next] - D_L04_002AF630[frame]) * phase);
    func_00282CC0(object + 0x10, motion, object + 0x10);
    func_002B5278(object, func_00283248(target[0] - *(float *)(object + 0x10),
                                      target[1] - *(float *)(object + 0x14)));
    *(float *)(object + 0x18) = func_002A89A8(object + 0x10, 0, 0.5f);
    if (frame == 5)
        func_0029FCC0(object, 3, origin);
    else if (frame == 15)
        func_0029FCC0(object, 2, origin);
    else
        return;
    func_00282D30(offset, object + 0xC0, 0.5f);
    func_00282CC0(origin, origin, offset);
    origin[2] -= 0.2f;
    for (i = 9; i >= 0; i--) {
        int spin;
        float size;
        char *particle;
        char *extra;
        func_002A7A00(axis, 0.005000000354f, 0.05000000447f);
        spin = func_00283CF0(func_002A78D8(1.0f, 3.0f));
        size = func_002A7878(0.3f, 1.0f) * 210000.0f;
        point[0] = origin[0] + func_002A78D8(0.0f, 0.3f);
        point[1] = origin[1] + func_002A78D8(0.0f, 0.3f);
        point[2] = origin[2] + func_002A78D8(0.0f, 0.3f);
        particle = func_002BDCE8(point, spin, axis, 0x406080, 0,
                               0.0f, 1.0f, 1.01f, size);
        if (particle != 0) {
            *(short *)(particle + 0xA) = 60;
            particle[3] = 0x44;
            extra = particle + 0x20;
            particle[9] = func_00283CF0(4.0f) + 0x40;
            *(float *)(extra + 0x1C) = func_00283CE0(5);
            *(int *)(extra + 4) = 3;
            extra[0xA] = 0x20;
            extra[0xB] = particle[0xA];
        }
    }
}
