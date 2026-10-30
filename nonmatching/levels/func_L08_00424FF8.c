/* func_L08_00424FF8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Complete four-vector reconstruction; preserves all three GPR and six FPR inputs, nine arguments of the particle constructor and its pointer return. Allocation/spilling gives a 0x100 frame against retail 0x110. Existing opaque vector W storage is retained without a synthetic initialization.
   No linked match is claimed.
*/

#include "common.h"
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern f32 func_002A7878(f32, f32), func_00283180(f32), func_00283198(f32);
extern void func_00283098(void *, void *, void *), func_00282F20(void *, void *, f32);
extern void func_00282D30(void *, void *, f32), func_00282CC0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern s32 func_00283CF0(f32), func_001163B0(void);
extern u8 *func_002BAA28(void *, void *, void *, s32, s32, s32, s32, s32, s32);

/* Emit a randomized batch while retaining the complete position/velocity slots. */
void func_L08_00424FF8(u8 *object, void *origin, s32 count,
                     f32 force, f32 lift, f32 maximum, f32 minimum,
                     f32 velocityW, f32 driftW)
{
    Vector position, velocity, drift, motion;
    u8 *state = *(u8 **)(object + 0x68), *particle;
    f32 component, amount;
    s32 a, b, c;
    while (count > 0) {
        component = func_00283180(func_002A7878(-3.1415927f, 3.1415927f));
        position.f[0] = component * func_002A7878(minimum, maximum);
        component = func_00283198(func_002A7878(-3.1415927f, 3.1415927f));
        position.f[1] = component * func_002A7878(minimum, maximum);
        position.f[2] = 0.0f;
        func_00283098(&position, &position, object + 0xC0);
        amount = force * ((maximum - func_00282DF0(&position)) * (1.0f / 60.0f)) / maximum;
        amount = func_002A7878(amount * 0.25f, amount);
        func_00282F20(&velocity, &position, amount);
        velocity.f[2] += func_002A7878(lift * 0.25f, lift) * (1.0f / 60.0f);
        if (object[0x20] == 5) {
            qcopy(&motion, state + 0xD0);
            motion.f[2] = 0.0f;
            func_00282D30(&motion, state + 0xD0, 0.8f);
            func_00282CC0(&velocity, &velocity, &motion);
            func_00282D30(&drift, &motion, 0.4f);
        } else {
            qzero(&drift);
        }
        func_00282CC0(&position, &position, origin);
        position.f[2] -= 0.75f;
        velocity.f[3] = velocityW;
        drift.f[3] = driftW;
        a = func_00283CF0(func_002A7878(15.0f, 25.0f));
        b = func_00283CF0(func_002A7878(20.0f, 40.0f));
        c = func_00283CF0(func_002A7878(50.0f, 70.0f));
        particle = func_002BAA28(&position, &velocity, &drift, 0x70204050, 0x7F7F7F, a, b, c, -1);
        if (particle && (func_001163B0() & 1)) particle[3] = 0x48;
        count--;
    }
}
