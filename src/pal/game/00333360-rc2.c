#include "include_asm.h"

#include "common.h"
extern s32 D_001AFC6C;
extern s32 g_001AFC6C __attribute__((sda));
extern f32 D_001B0A80 __attribute__((sda));
extern f32 D_001B0A84 __attribute__((sda));
extern s8 g_active_camera[];
struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct Obj { s8 pad[0x10]; struct Vec4 pos; };
struct Tab { s8 pad[0x140]; f32 f140; f32 f144; };
f32 math_random_float_range(f32 a, f32 b);
f32 math_random_angle(void);
void vec_build_spherical_offset(struct Vec4 *p, f32 x, f32 y, f32 z);
s32 math_random_int_range(s32 a, s32 b);
void func_PAL_002BE880(struct Vec4 *a, struct Vec4 *b, u32 c, s32 d, s32 e, f32 f);
void FastVecAdd(struct Vec4 *a, struct Vec4 *b, struct Vec4 *c);
f32 mat_fast_helper_a(f32 a, f32 b);
f32 math_random_signed_float_range(f32 a, f32 b);
int FloatToInt(f32 a);
f32 FastAddRotations(f32 a, f32 b);
f32 math_fast_sin_or_cos_a(f32 a);
f32 math_fast_sin_or_cos_b(f32 a);
unsigned char *func_PAL_002C8BD0(struct Vec4 *a, struct Vec4 *b, s32 c);
void moby_release_slot_by_id(struct Obj *a);
void moby_mark_spawned(struct Obj *a);

void func_PAL_00333CD8(struct Obj *arg0)
{
    struct Vec4 b;
    struct Vec4 a;
    struct Tab *tb;
    s32 i;
    s32 j;
    f32 ra;
    f32 rb;
    f32 rc;
    f32 rd;
    f32 re;
    f32 rf;
    f32 rg;
    s32 rh;
    f32 p1;
    f32 p2;
    f32 r3;
    f32 r4;
    f32 r5;
    f32 r6;
    f32 pa;
    f32 pb;
    f32 d80;

    i = 0;
    if (0x21 - D_001AFC6C > 0) {
        do {
            i++;
            ra = math_random_float_range(0.0f, 0.3700000047683716f);
            rb = math_random_angle();
            rc = math_random_angle();
            vec_build_spherical_offset(&a, ra, rb, rc);
            rd = math_random_float_range(0.3499999940395355f, 0.6000000238418579f);
            a.z = a.z + rd;
            FastVecAdd(&a, &a, &arg0->pos);
            re = math_random_float_range(0.002f, 0.020000001f);
            rf = math_random_angle();
            rg = math_random_angle();
            vec_build_spherical_offset(&b, re, rf, rg);
            rh = math_random_int_range(0x19, 0x2F);
            func_PAL_002BE880(&a, &b, 0x4F20507F, 0x102F, rh, 150000.0f);
        } while (i < 0x21 - D_001AFC6C);
    }
    j = 0;
    if (0x32 - D_001AFC6C > 0) {
        tb = (struct Tab *)g_active_camera;
        do {
            j++;
            p1 = mat_fast_helper_a(tb->f140 - arg0->pos.x, tb->f144 - arg0->pos.y);
            FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
            r3 = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            b.x = arg0->pos.x + r3;
            r4 = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            b.y = arg0->pos.y + r4;
            r5 = math_random_signed_float_range(0.0f, 0.15000000596046448f);
            b.z = arg0->pos.z + r5;
            d80 = D_001B0A80;
            r6 = math_random_signed_float_range(0.0f, -1.5707964897155762f);
            p2 = FastAddRotations(p1, r6);
            pa = math_fast_sin_or_cos_a(p2);
            a.x = pa * 0.020000001f * d80;
            pb = math_fast_sin_or_cos_b(p2);
            a.y = pb * 0.020000001f * d80;
            d80 = D_001B0A84;
            a.z = d80 * 0.020000001f;
            func_PAL_002C8BD0(&b, &a, 0xFA);
        } while (j < 0x32 - D_001AFC6C);
    }
    g_001AFC6C = D_001AFC6C - 1;
    moby_release_slot_by_id(arg0);
    moby_mark_spawned(arg0);
}
