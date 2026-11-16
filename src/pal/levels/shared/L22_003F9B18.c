#include "common.h"

/* func_PAL_L22_003F9B18, the PAL copy of func_L22_003F5688: the same C, where the kind and
 * duration take the 50 Hz scale, the constant 60 becomes 50, and the duration's bounds are
 * read as words 1 and 2 of D_L22_001B0A48, absolute, instead of through $gp.
 *
 * -fno-gcse: retail rebuilds the object offsets and the size table's GP base in
 * every iteration, which gcse's PRE would hoist into saved registers. */

typedef int EmissionQuad __attribute__((mode(TI)));
typedef union { EmissionQuad q; float f[4]; } EmissionVector;

/* The level's emitter settings.  The first word of each pair is read through $gp,
 * the other words are absolute; `[1]` keeps a word out of a delay slot, as retail. */
extern float D_L22_001B0A20_gp[] SDATA(D_L22_001B0A20);
extern int g_column_color_table[] __attribute__((sda));
extern int D_L22_001B0A28_gp[] SDATA(D_L22_001B0A28);
extern float D_L22_001B0A38_gp[] SDATA(D_L22_001B0A38);
extern int D_L22_001B0A44_gp[] SDATA(D_L22_001B0A44);
extern int g_column_int_params_b[] __attribute__((sda));
extern int D_L22_001B0A48_gp[] SDATA(D_L22_001B0A48);

extern float IntToFloat(int);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern int math_random_int_below(int);
extern void vec_clear_128(void *);
extern int math_random_int_range(int, int);
/* The EE passes three vectors and five ints in registers, the ninth int on the stack. */
extern void *part_spawn_trail(void *, float *, float *, int, int, int, int, int, int);

/* Spawn func_002BAA28 entries along the object's height: the count scales with the
 * height and the level's density (a fifth of it unless fullDensity), each at a
 * random spread transformed into the object's frame, with random colours and size. */
void part_emit_column_pal(u8 *object, int full_density)
{
    EmissionVector position, scratch, to;
    u8 *state = *(u8 **)(object + 0x68);
    float height = *(float *)(state + 0xA0);
    float count = (height * 7.2900004386901855f) * D_L22_001B0A20_gp[0];
    float step;
    float zero;
    float base_width = 2.7f;
    int i;

    if (!full_density)
        count *= 0.2f;
    i = 0;
    step = height / count;
    if ((float)i < count) {
        zero = (float)i;
        do {
            float progress = IntToFloat(i) * step;
            float spread = base_width + progress * 0.1f;
            int first_color, second_color, kind, duration;
            float size;

            scratch.q = 0;
            scratch.f[0] = math_random_signed_float_range(zero, spread);
            scratch.f[1] = math_random_signed_float_range(zero, spread);
            scratch.f[2] = progress;
            position.q = scratch.q;
            matrix_mul_vec3(position.f, position.f, object + 0xC0);
            FastVecAdd(position.f, position.f, object + 0x10);
            first_color = FastTweenColor(D_L22_001B0A28_gp[0], g_column_color_table[1],
                                       math_random_float_range(zero, 1.0f));
            second_color = FastTweenColor(g_column_color_table[2], g_column_color_table[3],
                                        math_random_float_range(zero, 1.0f));
            size = D_L22_001B0A38_gp[math_random_int_below(2)];
            vec_clear_128(scratch.f);
            scratch.f[3] = size;
            vec_clear_128(to.f);
            to.f[3] = size;
            kind = ((s32)math_random_int_range(1, D_L22_001B0A48_gp[0]) * 5 + 2) / 6;
            duration = ((s32)math_random_int_range(g_column_int_params_b[1], g_column_int_params_b[2]) * 5 + 2) / 6;
            part_spawn_trail(position.f, scratch.f, to.f, first_color, second_color, kind, duration,
                          50, D_L22_001B0A44_gp[0]);
            ++i;
        } while ((float)i < count);
    }
}
