#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; struct { f32 x, y, z, w; } f; } V;
typedef struct { V rows[8]; } Transform;

/* The moby's variables (at +0x68). */
typedef struct {
    s32 transform;          /* 0x00: index into D_L12_001B2F8C[0] */
    u8 pad04[0x34 - 0x04];
    f32 depth;              /* 0x34 */
    u8 pad38[0x48 - 0x38];
    s32 base;               /* 0x48 */
    s32 hit;                /* 0x4C */
    s32 done;               /* 0x50 */
    u8 pad54[0x58 - 0x54];
    s32 other;              /* 0x58 */
    s32 mode;               /* 0x5C */
} Vars7CA8;

typedef struct {
    u8 pad00[0x10];
    V position;             /* 0x10 */
    u8 state;               /* 0x20 */
    u8 pad21[0x68 - 0x21];
    Vars7CA8 *vars;         /* 0x68 */
    u8 pad6C[0xB2 - 0x6C];
    u16 uid;                /* 0xB2 */
    u8 padB4[0xF0 - 0xB4];
    V rotation;             /* 0xF0 */
} Moby7CA8;

typedef struct { u8 pad[0x18]; u8 *hit; s32 count; V point; } Collision;
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;

extern Transform *D_L12_001B2F8C[] __attribute__((sda));
extern Transform *D_L12_001B2F8C_gp SDATA(D_L12_001B2F8C) __attribute__((sda));
extern u8 *D_L12_001B090C[] __attribute__((sda));
extern V D_00189EA0 NOT_SDA;
extern LevelSaveState D_L12_0021EDF0;
extern Collision D_L12_001C0240;
extern u8 D_0019B4A8[];
extern s32 D_001A79F0[] __attribute__((sda));
extern s32 D_001A79F0_gp SDATA(D_001A79F0) __attribute__((sda));
extern s32 D_001A7A00[] __attribute__((sda));
extern void *D_0018C0B0 NOT_SDA;
extern f32 D_L12_001B1BB0 __attribute__((sda));
extern f32 D_L12_001B1BB4 __attribute__((sda));
extern f32 D_L12_001B1BC0 __attribute__((sda));
extern f32 D_L12_001B1BC4 __attribute__((sda));
extern V D_L12_001B1BD0 __attribute__((sda));

extern void func_002A7750(void *, s32, s32);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern f32 func_00282C48(f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_002ACBC8(void *, s32);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern void func_00282D30(void *, void *, f32);
extern void func_002A8C00(void *, void *, s32, void *, f32);
extern void func_002A8E20(void *, void *);
extern s32 func_L12_003DE4B0(void);
extern s32 func_L00_003DE260(void);
extern void func_L00_003DF6B0(s32, s32);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L12_00418418(void);

void func_L12_00417CA8(Moby7CA8 *self)
{
    V v, direction, rotation[3], matrix[4], hit, a, b, c, point, normal, tmp;
    u8 impulse[0x30] __attribute__((aligned(16)));
    Vars7CA8 *s = self->vars;
    f32 length;
    s32 index;
    u16 rawIndex;

    switch (self->state) {
    case 0:
        rawIndex = self->uid;
        index = (s16)rawIndex;
        if (D_L12_0021EDF0.collected[index])
            goto active;
        {
            /* One 3-bit count per nibble; the low bit of the id picks the nibble. */
            s32 bits = D_0019B4A8[(index >> 1) + (D_001A79F0[0] << 10)];
            if (rawIndex & 1) {
                if ((bits >> 4) & 7)
                    goto active;
                func_002A7750(self, 1, -1);
            } else {
                if (bits & 7) {
active:
                    func_002A7750(self, 2, -1);
                } else {
                    func_002A7750(self, 1, -1);
                }
            }
        }
        break;
    case 1:
        direction.q = 0;
        direction.f.z = 1;
        direction.f.w = 1;
        matrix_mul_vec3(&direction, &direction, &D_L12_001B2F8C[0][s->transform]);
        length = FastVecLength(&direction);
        {
            V *transform = &D_L12_001B2F8C[0][s->transform].rows[7];
            s->depth = 1;
            euler_rotation_basis(rotation, transform);
        }
        matrix_from_basis_rows(matrix, rotation);
        matrix_mul_vec3(&hit, &D_L12_001B1BD0, &D_L12_001B2F8C[0][s->base].rows[4]);
        a.q = 0;
        b.q = 0;
        a.f.x = 1;
        a.f.w = 1;
        b.f.x = 1;
        b.f.w = 1;
        FastVecAdd(&a, &a, &hit);
        matrix_mul_vec3(&a, &a, &D_L12_001B2F8C[0][s->base]);
        FastVecSub(&b, &D_L12_001B2F8C[0][s->base].rows[3], &a);
        FastVecAdd(&a, &D_L12_001B2F8C[0][s->base].rows[3], &a);
        a.f.z += 2.5f;
        b.f.z += 2.5f;
        s->hit = 0;
        c.q = 0;
        if (CollLine(&a, &b, 0x12, 0, 0)) {
            V *collision = &D_L12_001C0240.point;
            V *transform = &D_L12_001B2F8C[0][s->transform].rows[3];
            s->hit = 1;
            FastVecSub(&v, collision, transform);
            transform_vector(&v, &v, matrix);
            {
                f32 numerator = -v.f.z;
                f32 denominator = -length;
                s->depth = numerator / denominator;
            }
            if (*(s16 *)(D_L12_001C0240.hit + 0xAA) == 0xFC4) {
                func_002AD0E0(self, D_L12_001C0240.hit, &self->position, &self->rotation, &point, &normal);
                point.f.z = 0;
                FastVecSub(&tmp, &point, &self->position);
                point.q = tmp.q;
                point.f.z = 0;
                qcopy(&c, &point);
                FastVecScale(&c, &c, D_L12_001B1BC4);
            }
        }
        qcopy(&point, &D_00189EA0);
        point.f.z += D_L12_001B1BC0;
        if (IsPointInCuboid(&point, s->transform)) {
            FastVecSub(&v, &D_00189EA0, &D_L12_001B2F8C[0][s->transform].rows[3]);
            transform_vector(&v, &v, matrix);
            v.f.z = -v.f.z / -length;
            if (v.f.z < s->depth - (D_L12_001B1BB0 / length) * 1.5f ||
                v.f.z >= s->depth + (D_L12_001B1BB4 / length) * 0.5f ||
                !s->hit || s->mode == 1) {
                normal.q = 0;
                normal.f.z = -3;
                FastVecSub(&normal, &normal, &c);
                make_hit_descriptor(&impulse, self, 0x10001, &normal, (f32)(D_001A7A00[0] / 2));
                QueueMobyImpact(D_0018C0B0, &impulse);
            }
        }
        point.f.z = D_L12_001B2F8C[0][s->transform].rows[3].f.z;
        if (IsPointInCuboid(&point, s->transform)) {
            FastVecSub(&v, &point, &D_L12_001B2F8C[0][s->transform].rows[3]);
            transform_vector(&v, &v, matrix);
            {
                f32 numerator = -v.f.z;
                f32 denominator = -length;
                v.f.z = numerator / denominator;
            }
            if (func_00282C48(v.f.z + 1) < 0.01f && !s->done) {
                u16 uid;
                s->done = 1;
                uid = self->uid;
                if (uid & 1) {
                    s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                    if (((D_0019B4A8[tableIndex] >> 4) & 7) != 7)
                        D_0019B4A8[tableIndex] += 16;
                } else {
                    s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                    if ((D_0019B4A8[tableIndex] & 7) != 7)
                        ++D_0019B4A8[tableIndex];
                }
            }
        }
        if (s->other != -1 && IsPointInCuboid(&point, s->other) && !s->done) {
            u16 uid;
            s->done = 1;
            uid = self->uid;
            if (uid & 1) {
                s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                if (((D_0019B4A8[tableIndex] >> 4) & 7) != 7)
                    D_0019B4A8[tableIndex] += 16;
            } else {
                s32 tableIndex = ((s16)uid >> 1) + (D_001A79F0_gp << 10);
                if ((D_0019B4A8[tableIndex] & 7) != 7)
                    ++D_0019B4A8[tableIndex];
            }
        }
        if (func_L12_003DE4B0() && !func_L00_003DE260()) {
            u8 *player = D_L12_001B090C[0];
            qcopy_nc(&normal, player + 0x10);
            if (func_00282C48(*(f32 *)(player + 0x18) - D_L12_001B2F8C[0][s->transform].rows[3].f.z) < 2)
                normal.f.z = D_L12_001B2F8C_gp[s->transform].rows[3].f.z;
            if (IsPointInCuboid(&normal, s->transform))
                func_L00_003DF6B0(1, -1);
        }
        func_L00_002E6CF0(func_L12_00418418, self);
        break;
    }
}
