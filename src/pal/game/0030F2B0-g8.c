/* func_PAL_0030F2B0, the PAL copy of func_0030DE88: the same C, where 15 becomes 12 (the 50 Hz scale of a
 * count), the spread is multiplied by 1.2 (6/5, per-frame speed at 50 Hz), and 0.3f is written in the product. */
#include "common.h"

typedef int Quadword_0030F2B0 __attribute__((mode(TI)));
typedef union {
    Quadword_0030F2B0 bits;
    float f[4];
} Vec4_0030F2B0;

extern float D_001AF044 __attribute__((sda));
extern char D_0018A550[];

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7A00(void *, float, float);
extern float func_00282C48(float);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern int func_0030CAA0(void);
extern void func_002C2210(void *, float, float, s32, s32, s32, s32, void *, float, s32);

void func_PAL_0030F2B0(u8 *obj, int count)
{
    Vec4_0030F2B0 v;
    Vec4_0030F2B0 w;
    int i;

    v.bits = 0;
    v.f[1] = -0.9f;
    func_00283098(&v, &v, obj + 0xC0);
    func_00282CC0(&v, &v, obj + 0x10);
    for (i = 0; i < count; i++) {
        int spin;
        int colour;
        float size;
        float life;
        func_002A7A00(&w, 0.0f, D_001AF044 * 1.2f);
        w.f[0] = func_00282C48(w.f[0]);
        func_00283098(&w, &w, D_0018A550);
        spin = func_002A7820(-8, 8);
        size = func_002A7878(0.2f, 0.6f);
        life = size * 0.3f;
        colour = func_0030CAA0() | 0x7F000000;
        func_002C2210(&v, life, size, 12, colour, 0, spin, &w, 0.0f, 0);
        colour = 0x307F7F7F;
        func_002C2210(&v, size * 0.15f, size * 0.5f, 12, colour, 0, -spin, &w, 0.0f, 0);
    }
}
