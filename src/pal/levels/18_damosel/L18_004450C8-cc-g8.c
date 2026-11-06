/* func_PAL_L18_004450C8, the PAL copy of func_L18_0043FC70: the same C, where rename func_002B0A18 becomes func_PAL_002B1588; rename func_00288E18 becomes func_PAL_00289730. */
#include "common.h"

extern u8 D_001395B8[], D_00189EA0[];
/* Read as D_001A7AF8[0x37] (0x001A7B2F): an sda incomplete array with a nonzero
 * index gives retail's unsplit `lui; lbu` pair, kept out of the delay slot. */
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 *D_L18_001B281C;
extern float func_00283B98(float, float), func_002A7878(float, float), func_002A7940(void), func_002A78D8(float, float), func_00282E80(void *, void *);
extern int func_002A77E0(int), func_002A7750(void *, int, int);
extern void func_002AF000(void *, float, float, float), func_0029F338(void *), func_PAL_002B1588(int, int), func_PAL_00289730(int, int);
extern void *func_002C2210(void *, int, int, int, int, void *, float, float, float, int);

/* State 0: unless already collected, spin and emit two particle pairs per frame;
 * within 1.5 units of D_00189EA0, set the collected flag and signal the linked
 * moby (or delete itself). Otherwise, once the linked moby is in state 0xFE/0xFD
 * (or there is none), wait 41 frames, make the two closing calls and delete itself. */
void func_PAL_L18_004450C8(u8 *obj) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    int i, sign, n;
    float size, angle, pitch;
    if (obj[0x20] == 0) {
        if (D_001395B8[0x86] || D_001A7AF8[0x37]) {
            func_0029F338(obj);
        } else {
            *(float *)(obj + 0xf8) = func_00283B98(*(float *)(obj + 0xf8), 0.087266475f);
            for (i = 0; i < 2; i++) {
                size = func_002A7878(2.0f, 5.0f);
                sign = func_002A77E0(2);
                if (!sign) sign--;
                angle = func_002A7940();
                pitch = func_002A7878(0.3490659f, 1.5358898639678955f);
                func_002AF000(velocity, func_002A7878(0.05f, 0.1f), angle, pitch);
                qcopy(point, obj + 0x10);
                point[0] += func_002A78D8(0.0f, 0.15f);
                point[1] += func_002A78D8(0.0f, 0.15f);
                point[2] += func_002A78D8(0.0f, 0.15f);
                func_002C2210(point, 2, 0x208020ff, 0, sign, velocity, size * 0.1f, size, 0.006f, 0);
                func_002C2210(point, 2, 0x20ffffff, 1, -sign, velocity, size * 0.03f, size * 0.3f, 0.006f, 0);
            }
            if (func_00282E80(obj + 0x10, D_00189EA0) < 1.5f) {
                D_001395B8[0x86] = 1;
                if (*(int *)state != -1) {
                    D_L18_001B281C[(*(int *)state << 8) + 0xbc] = 1;
                    obj[0x31] = 0;
                    *(u16 *)(obj + 0x34) |= 1;
                    func_002A7750(obj, 1, -1);
                } else {
                    func_0029F338(obj);
                }
            }
        }
    } else if (*(int *)state == -1 || D_L18_001B281C[(*(int *)state << 8) + 0x20] == 0xfe ||
               D_L18_001B281C[(*(int *)state << 8) + 0x20] == 0xfd) {
        u32 timer = *(u16 *)(obj + 0x96);
        u32 old = timer++;
        *(u16 *)(obj + 0x96) = timer;
        if (old > 33) {
            func_PAL_002B1588(0x1293, 100);
            n = D_001395B8[0x86] ? 1 : 2;
            if (D_001395B8[0x89]) n--;
            if (n > 0) func_PAL_00289730(0xa0f, 0x66);
            else func_PAL_00289730(0xa10, 0x67);
            func_0029F338(obj);
        }
    }
}
