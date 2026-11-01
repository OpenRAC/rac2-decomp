#include "include_asm.h"

#include "common.h"
extern void func_002830C0(void *, void *, void *);
extern void func_0029FC20(char *, int, void *);
extern void *func_0029FCC0(char *, int, void *);
extern int func_002A77E0(int);
extern float D_L02_001B02C0[4] SDATA(D_L02_001B02C0);
extern float D_L02_001B0200[4] SDATA(D_L02_001B0200);
extern float D_L02_001B02D0 __attribute__((sda));
extern float D_L02_001B02D4 __attribute__((sda));
extern float D_L02_001B02A8 __attribute__((sda));
extern float D_L02_001B02AC __attribute__((sda));
extern int D_L02_001B02B0 __attribute__((sda));
extern char D_L02_001B0290[] SDATA(D_L02_001B0290);
extern float D_L02_001B01EC __attribute__((sda));
extern float D_L02_001B01F0 __attribute__((sda));
extern int D_L02_001B01F4 __attribute__((sda));
extern float D_L02_001B0214 __attribute__((sda));
extern char D_L02_001B0230[] SDATA(D_L02_001B0230);
extern char D_L02_001B0260[] SDATA(D_L02_001B0260);
extern char D_L02_001BA500[];
extern float func_00282DF0(void *);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern void *func_L02_003449D8(void *, void *, void *, int, int);

/* Spawns the particle bursts of one joint (func_L02_003D46B8 calls it for joints 2 and 3, the
 * second mirrored): the joint's position and matrix give the origin and the emission axis,
 * the length of the state's vector at +0x1B0 sets a 0..1 strength, and two offset points (the
 * first pulled horizontally towards D_L02_001BA500) emit D_L02_001B02B0 particles and a
 * strength-scaled number of particle pairs. The random term is an argument of each velocity
 * call, as in retail: hoisted into its own statement, the second loop's preheader copies swap
 * places. */
void func_PAL_L02_003DA038(char *self, int joint, int mirror) {
    float origin[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float offset_a[4] __attribute__((aligned(16)));
    float offset_b[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float strength;
    int i;
    func_0029FCC0(self, joint, origin);
    func_0029FC20(self, joint, matrix);
    qcopy(direction, matrix + 8);
    strength = func_00282DF0(*(char **)(self + 0x68) + 0x1B0) * 2.7777777f +
               func_002A7878(0.0f, 0.1f);
    if (strength > 1.0f) strength = 1.0f;
    else if (strength < 0.0f) strength = 0.0f;
    qcopy(offset_a, D_L02_001B02C0);
    qcopy(offset_b, D_L02_001B0200);
    if (mirror) {
        offset_a[1] = -offset_a[1];
        offset_b[1] = -offset_b[1];
    }
    func_002830C0(position, offset_a, matrix);
    func_00282CC0(position, position, origin);
    func_00282CF0(delta, D_L02_001BA500, position);
    delta[2] = 0.0f;
    func_00282F20(delta, delta, D_L02_001B02D0);
    func_00282CC0(position, position, delta);
    for (i = 0; i < D_L02_001B02B0; i++) {
        func_00282F20(velocity, direction,
                      -((D_L02_001B02A8 + func_002A7878(0.0f, strength * D_L02_001B02AC)) *
                        0.020000001f));
        func_002ACB48(position, D_L02_001B02D4);
        func_L02_003449D8(position, velocity, D_L02_001B0290, func_002A77E0(2), 1);
    }
    func_002830C0(position, offset_b, matrix);
    func_00282CC0(position, position, origin);
    for (i = 0; (float)i < strength * (float)D_L02_001B01F4 + 2.0f; i++) {
        func_00282F20(velocity, direction,
                      -((D_L02_001B01EC + func_002A7878(0.0f, strength * D_L02_001B01F0)) *
                        0.020000001f));
        func_002ACB48(position, D_L02_001B0214);
        func_L02_003449D8(position, velocity, D_L02_001B0230, func_002A77E0(2), 1);
        func_00282F20(velocity, direction,
                      -((D_L02_001B01EC + func_002A7878(0.0f, strength * D_L02_001B01F0)) *
                        0.020000001f));
        func_002ACB48(position, D_L02_001B0214);
        func_L02_003449D8(position, velocity, D_L02_001B0260, func_002A77E0(2), 1);
    }
}
