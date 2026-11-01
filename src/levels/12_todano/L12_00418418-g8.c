#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; struct { f32 x, y, z, w; } f; } V;
typedef struct { V rows[8]; } Transform;

/* A GS sprite packet: four corners, their colours and texture coordinates, then its registers. */
typedef struct {
    V v[4];            /* 0x00 */
    u32 color[4];      /* 0x40 */
    f32 uv[4][2];      /* 0x50 */
    u64 reg[4];        /* 0x70 */
} Packet;

typedef struct {
    s32 transform;     /* 0x00: index into D_L12_001B2F8C[0] */
    f32 phase;         /* 0x04 */
    u8 pad08[0x34 - 0x08];
    f32 position;      /* 0x34 */
    u8 pad38[0x4C - 0x38];
    s32 hit;           /* 0x4C */
    u8 pad50[0x54 - 0x50];
    s32 target;        /* 0x54 */
} Vars;

typedef struct {
    u8 pad00[0x68];
    Vars *vars;        /* 0x68 */
} Moby;

extern Transform *D_L12_001B2F8C[] __attribute__((sda));
extern u32 D_L12_001B1B5C __attribute__((sda));
extern f32 D_L12_001B1B30[4][2] MACRO_ADDR;
extern f32 D_L12_001B1B30_gp[4][2] SDATA(D_L12_001B1B30) __attribute__((sda));
extern s32 D_L12_001B1B20 __attribute__((sda));
extern s32 D_L12_001B1B24 __attribute__((sda));
extern s32 D_L12_001B1B28 __attribute__((sda));
extern f32 D_L12_001B1BE0 __attribute__((sda));
extern f32 D_L12_001B1BE4 __attribute__((sda));
extern f32 D_L12_001B1BBC __attribute__((sda));
extern f32 D_L12_001B1BB8 __attribute__((sda));
extern u32 D_L12_001B1B60 __attribute__((sda));
extern V D_L12_001C0260;
extern V D_L12_001B9E00;

extern void func_00283410(void *, void *);
extern u64 func_0027C878(s32);
extern void func_00283098(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern f32 func_L00_002EE290(void *);
extern s32 func_002761F8(void *, void *, s32, s32, s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_00280B90(void *, s32, s32);
extern void func_00282D08(void *, void *, void *, f32);

static __inline__ void CopyVector(V *dst, V *src)
{
    qcopy(dst, src);
}

void func_L12_00418418(Moby *self)
{
    Packet quad;
    V matrix[4], initial, low, high, axis;
    V p0, p1, p2, p3, saved, cross, delta, view, measure;
    Packet next;
    Vars *st = self->vars;
    s32 i, j, collision;
    f32 phase, step, t, len, speed, retreat, advance, oldDistance;

    initial.q = 0;
    initial.f.w = 1.0f;
    func_00283410(matrix, &initial);
    CopyVector(&matrix[3], &D_L12_001B2F8C[0][st->transform].rows[3]);
    for (i = 0; i < 4; i++) {
        quad.color[i] = D_L12_001B1B5C;
        quad.uv[i][0] = D_L12_001B1B30_gp[i][0];
        quad.uv[i][1] = D_L12_001B1B30[i][1];
        if (i < 2)
            quad.v[i].f.y = -quad.v[i].f.y;
        if (i & 1)
            quad.v[i].f.z = -quad.v[i].f.z;
        quad.v[i].f.z += 0.25f;
    }
    quad.reg[1] = func_0027C878(D_L12_001B1B20);
    low.q = 0;
    high.q = 0;
    quad.reg[2] = 0xFF9000000260ULL;
    quad.reg[0] = 0;
    quad.reg[3] = ((u64)D_L12_001B1B24 << 2) | ((u64)D_L12_001B1B28 << 6) | 0x8000000000ULL;
    low.f.y = -1.0f;
    low.f.w = 1.0f;
    high.f.y = 1.0f;
    high.f.w = 1.0f;
    if (st->position > 1.0f)
        st->position = 1.0f;
    else if (st->position < -1.0f)
        st->position = -1.0f;
    phase = st->phase;
    st->phase = phase + 0.008333334f;
    if (st->phase > 1.0f)
        st->phase -= 1.0f;
    step = 0.5f / D_L12_001B2F8C[0][st->transform].rows[2].f.x;
    for (i = 3; i >= 0; i--)
        quad.v[i].f.w = 0.0f;
    for (t = -1.0f; t <= 1.0f; t += 0.05f) {
        collision = 0;
        axis.q = 0;
        axis.f.z = 1.0f;
        axis.f.w = 1.0f;
        func_00283098(&axis, &axis, &D_L12_001B2F8C[0][st->transform]);
        len = func_00282DF0(&axis);
        if (st->target != -1) {
            retreat = 2.3f;
            advance = 7.0f;
        } else {
            retreat = D_L12_001B1BE0;
            advance = D_L12_001B1BE4;
        }
        if (st->hit) {
            if (st->position - retreat / len * 1.5f <= t) {
                if (st->position + advance / len * 0.5f > t) {
                    if (st->target == -1)
                        continue;
                    collision = 1;
                }
            }
        }
        CopyVector(&p0, &low);
        CopyVector(&p1, &low);
        CopyVector(&p2, &high);
        CopyVector(&p3, &high);
        p0.f.z = t;
        p2.f.z = t;
        p1.f.z = t + 0.01f;
        p3.f.z = t + 0.01f;
        func_00283098(&p0, &p0, &D_L12_001B2F8C[0][st->transform]);
        func_00283098(&p1, &p1, &D_L12_001B2F8C[0][st->transform]);
        func_00283098(&p2, &p2, &D_L12_001B2F8C[0][st->transform]);
        func_00283098(&p3, &p3, &D_L12_001B2F8C[0][st->transform]);
        func_002830C0(&p0, &p0, matrix);
        func_002830C0(&p1, &p1, matrix);
        func_002830C0(&p2, &p2, matrix);
        func_002830C0(&p3, &p3, matrix);
        if (collision) {
            CopyVector(&saved, &p2);
            if (func_002761F8(&p0, &p2, 2, 0, 0)) {
                CopyVector(&p2, &D_L12_001C0260);
                CopyVector(&p3, &D_L12_001C0260);
            }
        }
        func_00282CF0(&delta, &D_L12_001B9E00, &p0);
        oldDistance = 0.0f;
        func_00282CF0(&view, &p2, &p0);
        func_00282DD8(&cross, &delta, &view);
        func_00282F20(&cross, &cross, 1.0f);
        func_00282F20(&quad.v[0], &cross, D_L12_001B1BBC);
        func_00282F20(&quad.v[1], &cross, -D_L12_001B1BBC);
        func_00282F20(&quad.v[2], &cross, D_L12_001B1BBC);
        func_00282F20(&quad.v[3], &cross, -D_L12_001B1BBC);
        func_00282CC0(&quad.v[0], &quad.v[0], &p0);
        func_00282CC0(&quad.v[1], &quad.v[1], &p0);
        func_00282CC0(&quad.v[2], &quad.v[2], &p2);
        func_00282CC0(&quad.v[3], &quad.v[3], &p2);
        func_00280B90(&quad, 0, 1);
        if (collision) {
            func_00282CF0(&measure, &quad.v[2], &quad);
            oldDistance = func_L00_002EE290(&measure);
            CopyVector(&p2, &saved);
            func_00282F20(&quad.v[0], &cross, D_L12_001B1BBC);
            func_00282F20(&quad.v[1], &cross, -D_L12_001B1BBC);
            func_00282F20(&quad.v[2], &cross, D_L12_001B1BBC);
            func_00282F20(&quad.v[3], &cross, -D_L12_001B1BBC);
            func_00282CC0(&quad.v[0], &quad.v[0], &p0);
            func_00282CC0(&quad.v[1], &quad.v[1], &p0);
            func_00282CC0(&quad.v[2], &quad.v[2], &p2);
            func_00282CC0(&quad.v[3], &quad.v[3], &p2);
        }
        speed = phase + step;
        next = quad;
        func_00282D08(&next.v[0], &quad.v[0], &quad.v[2], st->phase);
        func_00282D08(&next.v[2], &quad.v[0], &quad.v[2], st->phase + D_L12_001B1BB8);
        func_00282D08(&next.v[1], &quad.v[1], &quad.v[3], st->phase);
        func_00282D08(&next.v[3], &quad.v[1], &quad.v[3], st->phase + D_L12_001B1BB8);
        for (j = 3; j >= 0; j--)
            next.color[j] = D_L12_001B1B60;
        phase = speed;
        if (speed > 0.0f)
            phase = speed - 1.0f;
        if (collision) {
            func_00282CF0(&measure, &next, &quad);
            if (oldDistance <= func_L00_002EE290(&measure))
                continue;
        }
        func_00280B90(&next, 0, 1);
    }
}
