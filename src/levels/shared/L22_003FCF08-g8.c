#include "common.h"

/* -fno-gcse: retail keeps the zero and step constants of the jitter calls in saved
 * FPRs set up inside the count guard; gcse's constant propagation rematerializes
 * them at every call instead. */

typedef int TI128 __attribute__((mode(TI)));

extern int math_random_int_below(int);
extern f32 math_random_float_range(f32, f32);
extern f32 math_random_angle(void);
extern f32 math_random_signed_float_range(f32, f32);
extern void vec_build_spherical_offset(f32 *, f32, f32, f32);
extern void FastVecScale(char *, char *, f32);
extern void add_vectors(char *, char *, char *);
extern void *part_spawn_ground_effect(char *, int, int, int, int, char *, int, f32, f32, f32);

/* The level's spray settings, all read through $gp. */
extern f32 D_L22_001B0D08 __attribute__((sda));
extern f32 D_L22_001B0D0C __attribute__((sda));
extern f32 D_L22_001B0D10 __attribute__((sda));
extern f32 D_L22_001B0D1C __attribute__((sda));
extern f32 D_L22_001B0D20 __attribute__((sda));
extern int D_L22_001B0D2C __attribute__((sda));
extern int D_L22_001B0D30 __attribute__((sda));
extern int D_L22_001B0D34 __attribute__((sda));

/* `count` times: build a random direction (radius, heading, elevation), scale a
 * copy of `base` randomly, jitter a copy of `origin` on three axes and pass both
 * to func_002C2210 twice, once per side.
 * The origin copy is the approved qcopy helper (retail's grouped lq/sq through
 * the saved vector address); the base copy is a plain quadword assignment. */
void part_emit_spray_burst(u8 *origin, u8 *base, int count)
{
    f32 dir[4] __attribute__((aligned(16)));
    f32 v[4] __attribute__((aligned(16)));
    f32 q[4] __attribute__((aligned(16)));
    f32 life;
    f32 tilt;
    f32 heading;
    int side;

    if (count > 0) {
        f32 scale = 0.016666668f;
        f32 zero = 0.0f;
        f32 step = 0.0375f;
        int left = count;

        for (; left != 0; left--) {
            f32 out[4] __attribute__((aligned(16)));

            life = math_random_float_range(D_L22_001B0D1C, D_L22_001B0D20);
            side = math_random_int_below(2);
            if (side == 0)
                side--;
            heading = math_random_angle();
            tilt = math_random_float_range(0.698131799697876f, 1.5358898639678955f);
            vec_build_spherical_offset(dir, math_random_float_range(D_L22_001B0D0C * scale, D_L22_001B0D10 * scale),
                          heading, tilt);
            *(TI128 *)q = *(TI128 *)base;
            FastVecScale((char *)q, (char *)base, math_random_float_range(0.75f, 0.95f));
            add_vectors((char *)out, (char *)dir, (char *)q);
            qcopy(v, origin);
            v[0] += math_random_signed_float_range(zero, step);
            v[1] += math_random_signed_float_range(zero, step);
            v[2] += math_random_signed_float_range(zero, step);
            part_spawn_ground_effect((char *)v, D_L22_001B0D34, D_L22_001B0D2C, 0, side,
                          (char *)dir, 0, life * 0.1f, life, D_L22_001B0D08);
            part_spawn_ground_effect((char *)v, D_L22_001B0D34, D_L22_001B0D30, 1, -side,
                          (char *)dir, 0, life * 0.07f, life * 0.7f, D_L22_001B0D08);
        }
    }
}
