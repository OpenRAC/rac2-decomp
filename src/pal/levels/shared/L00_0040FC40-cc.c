/* func_PAL_L00_0040FC40, the PAL copy of func_L00_0040B098: the same C, where rename func_002C16C0 becomes func_PAL_002C23B8; wrap life (((int)({e}) * 5 + 2) / 6). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { char pad[0x5c]; u8 *texture; } ParticleResources;
extern ParticleResources D_L00_001FE940;
extern char D_0018A0E0[];
extern s32 FloatToInt(float);
extern f32 IntToFloat(s32);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecScale(float *, void *, float);
extern void FastVecSub(float *, void *, float *);
extern void FastVecAdd(float *, float *, float *);
extern float math_random_signed_float_range(float, float);
extern float math_random_float_range(float, float);
extern s32 math_random_int_range(s32, s32);
extern u8 *func_PAL_002C23B8(f32 *pos, f32 *sym, s32 a2, s32 a3, u32 color, s32 alpha, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern s32 func_001163B0(void);

/* Lays a line of grey particles from ORIGIN towards the object's position (+0x10), about
   0.4 units apart over the length at +0x18 of the object's state, each with a random spin,
   size, lifetime and a small velocity against D_0018A0E0. The velocity's scale is computed in
   its own statement, so the vector's address is formed after that call and stays a plain
   stack address there, while the emitter's copy of it is kept in a saved register. */
void func_PAL_L00_0040FC40(u8 *self, Vector *origin)
{
    Vector start;
    Vector velocity;
    Vector position;
    Vector step;
    Vector *from = &start;
    float length;
    float size;
    float speed;
    int count;
    int i;
    int life;
    int spin;
    int alpha;
    u32 color;
    u8 *part;

    start.q = origin->q;
    length = *(float *)(*(u8 **)(self + 0x68) + 0x18);
    count = FloatToInt(length * 10.0f) / 4;
    qcopy(position.f, from);
    FastVecSub(step.f, self + 0x10, start.f);
    size = IntToFloat(count);
    vec_scale_to_length(step.f, step.f, length / size);
    for (i = 0; i < count; i++) {
        spin = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
        speed = -(math_random_float_range(0.2f, 1.0f) * 0.020000001f);
        FastVecScale((float *)&velocity, D_0018A0E0, speed);
        life = math_random_int_range(30, 50);
        size = math_random_float_range(200.0f, 1000.0f);
        if (func_001163B0() & 2) {
            color = 0x404040;
            alpha = 0x50;
        } else {
            color = 0x7F7F7F;
            alpha = 0x50;
        }
        part = func_PAL_002C23B8(position.f, velocity.f, (((int)(life) * 5 + 2) / 6), alpha, color, spin, 21000.0f, size, 1.0f, 0.0f, 1.0f);
        FastVecAdd(position.f, position.f, step.f);
        if (part != 0) {
            part[2] = *D_L00_001FE940.texture;
            part[3] = alpha == 0x40 ? 0x48 : 0x44;
        }
    }
}
