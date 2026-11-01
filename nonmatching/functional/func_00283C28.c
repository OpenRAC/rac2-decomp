/* functional: high. Same operations in the same order; only the compiler's register choice and the trapping add differ. */
typedef float f32;
typedef int s32;

typedef union { f32 f; s32 i; } FloatInt;

/* An angle wrapped to [-pi, pi]: the whole turns are taken out, the rest is scaled back to radians. */
f32 func_00283C28(f32 a0) {
    f32 t = a0 * 0.15915494f + 0.5f;
    FloatInt u;
    s32 i;

    u.f = t;
    i = (s32)t;
    i += u.i >> 31;
    return (t - (f32)i - 0.5f) * 6.2831855f;
}
