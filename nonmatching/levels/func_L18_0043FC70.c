/* Complete nonmatching reconstruction; 904/900 bytes.
 * -O2 -G8 -ffunction-sections.
 * Local release results: US 0/1, US2 absent, PAL absent.
 * 2 bounded source hypotheses. Remaining: Pickup gate/epilogue placement and random interval/position lifetimes.
 * Reopen with independent original lifetime/control-flow evidence.
 * Random velocity reserves 16 aligned bytes; 002AF000 initializes XYZ
 * and the actual 002C2210 constructor reads only those three lanes.
 */
#include "common.h"
typedef struct { float v[4]; } PickupVector __attribute__((aligned(16)));
typedef u8 PickupActor[0x100];
extern u8 D_001395B8[], D_001A7B2F;
extern float D_00189EA0[];
extern PickupActor *D_L18_001B281C __attribute__((sda));
extern float func_00283B98(float, float), func_002A7878(float, float), func_002A78D8(float, float);
extern float func_002A7940(void), func_00282E80(void *, void *);
extern int func_002A77E0(int);
extern void func_002AF000(void *, float, float, float);
extern void *func_002C2210(float, float, float, void *, int, u32, int, int, void *, int);
extern void func_002A7750(void *, int, int), func_0029F338(void *), func_002B0A18(int, int);
extern int func_00288E18(int, int);

/* Emit the pickup's paired particles, then complete its linked reward sequence. */
void func_L18_0043FC70(u8 *object)
{
    PickupVector velocity, point;
    u8 *state = *(u8 **)(object + 0x68);
    int i, sign, count;
    float scale, angle, spread;
    if (object[0x20] == 0) {
        if (!D_001395B8[0x86] && !D_001A7B2F) {
        *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.0872664749622345f);
        for (i = 1; i >= 0; i--) {
            scale = func_002A7878(2.0f, 5.0f);
            sign = func_002A77E0(2);
            if (!sign) sign--;
            angle = func_002A7940();
            spread = func_002A7878(0.349065899848938f, 1.5358898639678955f);
            func_002AF000(&velocity, func_002A7878(0.05f, 0.1f), angle, spread);
            qcopy(&point, object + 0x10);
            point.v[0] += func_002A78D8(0.0f, 0.15f);
            point.v[1] += func_002A78D8(0.0f, 0.15f);
            point.v[2] += func_002A78D8(0.0f, 0.15f);
            func_002C2210(scale * 0.1f, scale, 0.006000000052154064f, &point, 3, 0x208020FF, 0, sign, &velocity, 0);
            func_002C2210(scale * 0.03f, scale * 0.3f, 0.006000000052154064f, &point, 3, 0x20FFFFFF, 1, -sign, &velocity, 0);
        }
        if (func_00282E80(object + 0x10, D_00189EA0) < 1.5f) {
            D_001395B8[0x86] = 1;
            if (*(int *)state != -1) {
                D_L18_001B281C[*(int *)state][0xBC] = 1;
                object[0x31] = 0;
                *(u16 *)(object + 0x34) |= 1;
                func_002A7750(object, 1, -1);
            } else func_0029F338(object);
        }
        }
    } else if (*(int *)state == -1 || D_L18_001B281C[*(int *)state][0x20] == 0xFE ||
               D_L18_001B281C[*(int *)state][0x20] == 0xFD) {
        unsigned short old = *(u16 *)(object + 0x96);
        *(u16 *)(object + 0x96) = old + 1;
        if (old >= 41) {
            func_002B0A18(0x1293, 120);
            count = D_001395B8[0x86] ? 1 : 2;
            if (D_001395B8[0x89]) count--;
            if (count > 0) func_00288E18(0xA0F, 0x66);
            else func_00288E18(0xA10, 0x67);
            func_0029F338(object);
        }
    }
}
