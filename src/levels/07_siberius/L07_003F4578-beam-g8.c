#include "include_asm.h"

#include "common.h"

/* func_L07_003F4CC0 (DrawSegmentedBeam) reads its parameters through $gp and
   needs -g, so it has a -G8 -g unit of its own (config/cflags.txt).
   D_L07_001B0EC8[], D_L07_001B0EBC[], D_L07_001B0EAC[] and D_L07_001B0ED4[] are
   incomplete sda arrays: retail reads [0] through $gp and [1] (or the whole
   word) through lui. */

extern void func_L07_003F4C18(void *a, void *start, void *end);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282DD8(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *a, f32 scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern f32 func_00282DF0(void *v);
extern f32 func_00283B98(f32 a, f32 b);
extern s32 func_00283D38(s32 from, s32 to, f32 t);
extern void func_00281DE8(void *packet, s32 a, s32 b, s32 c);
extern void func_00280B90(void *packet, void *a, s32 b);
extern void func_00281EB8(void *pos, s32 id, s32 color, s32 a, f32 size, f32 b, f32 rotation);
extern u8 D_L07_001B9200[] NOT_SDA;
extern s32 D_L07_001B0EB0 __attribute__((sda));
extern s32 D_L07_001B0EA8 __attribute__((sda));
extern s32 D_L07_001B0ED0 __attribute__((sda));
extern s32 D_L07_001B0EAC[] __attribute__((sda));
extern s32 D_L07_001B0ED4[] __attribute__((sda));
extern f32 D_L07_001B0EB8 __attribute__((sda));
extern f32 D_L07_001B0EC0 __attribute__((sda));
extern f32 D_L07_001B0ED8 __attribute__((sda));
extern f32 D_L07_001B0EDC __attribute__((sda));
extern f32 D_L07_001B0EBC[] __attribute__((sda));
extern f32 D_L07_001B0EC8[] __attribute__((sda));
extern f32 D_L07_001B0EE0[] SDATA(D_L07_001B0EE0);
extern f32 D_L07_001B0EE4[] __attribute__((sda));

#define F(p, o) (*(f32 *)((p) + (o)))

void func_L07_003F4CC0(u8 *a)
{
    f32 start[4], end[4], delta[4], side[4], normal[4], base[4];
    struct Vec4 { f32 x, y, z, w; };
    struct {
        struct Vec4 vertices[4];
        s32 colors[4];
        f32 uv[4][2];
        u8 rest[32];
    } draw;
    f32 current[4], step[4];
    u8 *p = *(u8 **)(a + 0x68);
    s32 i, color;
    f32 length, count, alpha, rotation, width;
    f32 uvOffset;

    func_L07_003F4C18(a, start, end);
    func_00282CF0(delta, end, start);
    func_00282CF0(side, D_L07_001B9200, a + 0x10);
    func_00282DD8(normal, side, delta);
    func_00282F20(normal, normal, 1);
    qzero_nc(side);
    qcopy_nc(base, start);
    base[3] = 1;
    func_00281DE8(&draw, D_L07_001B0EB0, 1, 128);
    uvOffset = 0.0f;
    color = func_00283D38(D_L07_001B0EA8 & 0xffffff, D_L07_001B0EA8, F(p, 0x24));
    {
        s32 i;

        for (i = 0; i < 4; i++) {
            struct Vec4 *v;

            draw.uv[i][0] = D_L07_001B0EE0[i * 2] + uvOffset;
            draw.uv[i][1] = D_L07_001B0EE4[i * 2];
            qzero_nc(&draw.vertices[i]);
            v = &draw.vertices[i];
            if (i < 2)
                v->x = 0;
            else
                v->x = 1;
            v->z = D_L07_001B0EB8;
            if (!(i & 1))
                v->z = -v->z;
            v->w = 1;
            draw.colors[i] = color;
        }
    }
    func_00280B90(&draw, delta, 0);
    color = func_00283D38(D_L07_001B0EAC[0] & 0xffffff, D_L07_001B0EAC[0], F(p, 0x24));
    {
        s32 i;

        for (i = 0; i < 4; i++) {
            struct Vec4 *v = &draw.vertices[i];

            v->z = D_L07_001B0EBC[0];
            if (!(i & 1))
                v->z = -D_L07_001B0EBC[0];
            draw.colors[i] = color;
        }
    }
    func_00280B90(&draw, delta, 0);
    length = func_00282DF0(delta) / D_L07_001B0EC0;
    rotation = F(p, 0x28);
    if (a[0x20] == 0) {
        alpha = 1;
        count = (length * F(p, 0x24)) * 2.0f;
        if (count > length + 1)
            count = length + 1;
    } else {
        alpha = F(p, 0x24) * F(p, 0x24);
        count = length + 1;
    }
    qcopy(current, base);
    func_00282F20(step, delta, D_L07_001B0EC0);
    for (i = 0; (f32)i < count; i++) {
        f32 *pos;

        /* The last point and odd points take the first width, even points the second. */
        if ((f32)i == count - 1)
            width = D_L07_001B0EC8[0];
        else if (i & 1)
            width = D_L07_001B0EC8[0];
        else
            width = D_L07_001B0EC8[1];
        color = func_00283D38(D_L07_001B0ED0 & 0xffffff, D_L07_001B0ED0, alpha);
        pos = current;
        func_00281EB8(pos, 49, color, 1, width, 0, rotation);
        color = func_00283D38(D_L07_001B0ED4[0] & 0xffffff, D_L07_001B0ED4[0], alpha);
        func_00281EB8(pos, 49, color, 1, width, 0, func_00283B98(rotation, D_L07_001B0ED8));
        rotation = -func_00283B98(rotation, D_L07_001B0EDC * 0.017453294f);
        if ((f32)i < length - 1)
            func_00282CC0(current, current, step);
        else
            qcopy(current, end);
    }
}
