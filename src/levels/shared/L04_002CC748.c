#include "include_asm.h"

typedef int s32;

typedef unsigned int u32;

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned long u64;

typedef short s16;

typedef float f32;

typedef struct {
    u32 unknown;
    s32 data_offset;
    s32 length;
    s32 extra;
} PackedHeaderCountView;


typedef struct {
    u8 pad00[0x7A8];
    f32 field7A8;
    f32 field7AC;
    f32 field7B0;
    f32 field7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 field2290;
    u32 field2294;
} D00189E20;
extern D00189E20 D_00189E20;
extern void func_002AEE70(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
extern void func_002AEF28(u32 a0, void *a1, void *a2, f32 f0, f32 f1, f32 f2);
void func_L04_002CE810(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEE70(D_00189E20.field2290, &D_00189E20.field7A8, &D_00189E20.field7AC,
                  0.3f, 0.116355299949646f, -1.0f);
}

void func_L04_002CE870(void) {
    if (D_00189E20.field2294 != 0x7C)
        return;
    func_002AEF28(D_00189E20.field2290, &D_00189E20.field7B0, &D_00189E20.field7B4,
                  0.174532949924469f, 0.02617994323372841f, 0.03490659222006798f);
}

INCLUDE_ASM("asm/levels", func_L04_002D91B8);


INCLUDE_ASM("asm/levels", func_L04_002DB970);

INCLUDE_ASM("asm/levels", func_L04_002DBE70);

INCLUDE_ASM("asm/levels", func_L04_002DCE78);

#define NOT_SDA __attribute__((section(".data")))

extern int r1_D_0012FCF0 NOT_SDA;

/* rac1-decomp src/core/00118A40.c: func_00118EC0 */
void func_L04_002FB920(void) {
    r1_D_0012FCF0 = 0;
}

typedef int L04Quad __attribute__((mode(TI)));

/* the record the level's spawner builds: flag bytes, a halfword, a float,
   two sixteen-byte blocks and the fields that follow them */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u8  pad04[4];
    u8  field08;
    u8  field09;
    u16 field0A;
    f32 field0C;
    L04Quad field10;
    L04Quad field20;
    f32 field30;
    f32 field34;
    u16 field38;
} L04Record;

/* the second half of the record, at +0x20 */
typedef struct {
    u8  pad00[0xC];
    u32 field0C;
    f32 field10;
    f32 field14;
    u16 field18;
} L04RecordTail;

/* the record the level's other spawner builds: the same flag bytes, a word
   and a colour, then a sixteen-byte block and the fields that follow it */
typedef struct {
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    u32 field0C;
    L04Quad field10;
    u8  pad20[0xC];
    f32 field2C;
    L04Quad field30;
} L04Spawned;

/* the block at +0x30: a sixteen-byte vector and the float inside its last word */
typedef struct {
    L04Quad v;
} L04Vector;

extern void *func_002B9030(s32 kind);
extern s32 func_00283CF0(f32 value);
extern s32 func_002A77E0(s32 limit);
extern void func_00282F20(f32 *dst, f32 *a, f32 len);
extern void func_00282CF0(f32 *dst, f32 *a, f32 *b);

/* the level's pointer to the byte the record carries in its second flag byte */
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;

/* func_L04_0030C4C0 is matched in L04_0030C4C0.c (built with -frac2-qcopy and -g). */

INCLUDE_ASM("asm/levels", func_L04_0030C948);

ASM_FUNC("asm/levels", func_L04_0030EDE0);

ASM_FUNC("asm/levels", func_L04_0030FA30);

typedef struct {
    u8 pad00[0x34];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    u32 p68;
    u8 pad6C[0xAA - 0x6C];
    s16 type;
} MobStruct;

typedef struct {
    u8 pad00[0x44];
    s16 count;
    u8 pad46[0x18C - 0x46];
    u32 mobs[1];          /* the array the count field bounds */
} MobListStruct;

/* the list of mobs: level 04 has it at 0x001BD380, every level at its own address */
extern MobListStruct ref_L04_0031D630_00;

/* shared callee, named by its catalogue row (04:0031D3C8) */
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *mob);
extern void func_L00_00326048(void *mob, void *p, s32 a2, s32 a3, f32 alpha);

/* Walks the list of mobs: the ones of type 0xE29 get the 0x800 flag, the ones of type
   0xD54 are handed to func_002E64A0, and the ones of type 0xFA0 with a 0x68 pointer
   get that pointer's block (from +0xC) to func_L00_00326048. */
void func_L04_0031D630(void) {
    s32 i;

    func_L00_002FC980();
    for (i = 0; i < ref_L04_0031D630_00.count; i++) {
        MobStruct *mob = (MobStruct *)ref_L04_0031D630_00.mobs[i];

        if (mob != 0 && mob->type == 0xE29) {
            mob->flags |= 0x800;
        }
        if (mob->type == 0xD54) {
            func_002E64A0(mob);
        }
        if (mob != 0 && mob->type == 0xFA0 && mob->p68 != 0) {
            func_L00_00326048(mob, (void *)((u8 *)mob->p68 + 0xC), 0x80AAAAD2, 0x80396464, 0.0610865355f);
        }
    }
}

ASM_FUNC("asm/levels", func_L04_0032F1D8);

ASM_FUNC("asm/levels", func_L04_0032F340);

ASM_FUNC("asm/levels", func_L04_0032F3C0);

INCLUDE_ASM("asm/levels", func_L04_0032F62C);

INCLUDE_ASM("asm/levels", func_L04_0032F994);


/* sched1 hoists the last statement of */
void func_L04_0033CB88(char *p)
{
    *(int *)(p + 0) = 640;
    *(float *)(p + 8) = 0.5f;
    *(int *)(p + 20) = 0;
    *(float *)(p + 4) = 1.0f;
    *(float *)(p + 12) = 0.5f;
    *(int *)(p + 16) = 0;
    *(float *)(p + 36) = 2.7f;
    *(int *)(p + 24) = 0;
    *(float *)(p + 32) = 0.3f;
    *(float *)(p + 28) = 0.3f;
    *(float *)(p + 40) = 1.57f;
    *(float *)(p + 44) = 0.1f;
}

INCLUDE_ASM("asm/levels", func_L04_0033CC00);

INCLUDE_ASM("asm/levels", func_L04_0033D0C0);

extern s32 func_002A8600(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u32 *out, u32 value, s32 arg2, s32 arg3);
s32 func_L04_0033D4B0(u8 *a0) {
    u32 out = 0;
    if (func_002A8600(&out, *(u8 *)(a0 + 0x21), 0, 0) == -1)
        return 0;
    if (out != (u32)a0)
        return out;
    if (func_002A86E8(&out, out, 0, 0) != -1)
        return out;
    return 0;
}

INCLUDE_ASM("asm/levels", func_L04_003429F8);

extern void func_00282D60(void *buf, u32 value, float scale);
extern void func_00283DB8(void *buf, float value);
void func_L04_00343498(u32 value, float f) {
    u8 buf[16];
    func_00282D60(buf, value, 0.0009765625f);
    func_00283DB8(buf, f);
}

INCLUDE_ASM("asm/levels", func_L04_00344568);

extern void func_00283658(void *dst, void *src);
extern f32 func_00282DB0(void *a, void *b);
extern f32 func_00282C10(f32 x);
extern f32 func_00283248(f32 a, f32 b);
extern void func_00282DD8(void *dst, void *a, void *b);
extern void func_00283430(void *dst, void *src);
extern void func_00283788(void *a, void *b, void *c);
extern void func_002830C0(void *a, void *b, void *c);
extern f32 func_002AA898(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
extern void func_002AB6D8(f32 *src, f32 *out);

/* Copies the caller's matrix into a local one, takes the two aim angles off
   the target vector, springs one of them, and turns the copy by the three
   angles before handing its axes to the caller. */
void func_L04_00347AB8(void *a0, void *a1, void *a2, void *a3, f32 f1, f32 f2, f32 f3)
{
    f32 pos;
    f32 buf0[16];
    f32 buf1[16];
    f32 mat[16];
    f32 vec[4];
    f32 res[4];
    f32 v;
    f32 d;
    f32 ang;
    f32 base;

    v = *(f32 *)((u8 *)a1 + 8);
    pos = 0.0f;
    func_00283658(mat, a0);
    d = func_00282DB0(a3, mat + 8);
    base = func_00283248(d, func_00282C10(1.0f - d * d));
    func_00282DD8(res, a3, mat + 8);
    if (res[2] < 0.99f) {
        ang = func_00283248(res[0], res[1]);
        vec[0] = 0.0f;
        vec[1] = 0.0f;
        vec[2] = -ang;
        func_00283430(buf1, vec);
        func_00283788(mat, buf1, mat);
        func_002830C0(res, res, buf1);
        d = func_00283248(res[2], res[0]);
        vec[0] = 0.0f;
        vec[1] = -d;
        vec[2] = 0.0f;
        func_00283430(buf0, vec);
        func_00283788(mat, buf0, mat);
        func_002830C0(res, res, buf0);
    } else {
        ang = 0.0f;
        d = 0.0f;
    }
    func_002AA898(&pos, base, (f32 *)a2, f1, f2, f3, 0);
    vec[0] = 0.0f;
    vec[1] = 0.0f;
    vec[2] = pos;
    func_00283430(buf1, vec);
    func_00283788(mat, buf1, mat);
    vec[1] = d;
    vec[2] = 0.0f;
    func_00283430(buf0, vec);
    func_00283788(mat, buf0, mat);
    vec[1] = 0.0f;
    vec[2] = ang;
    func_00283430(buf1, vec);
    func_00283788(mat, buf1, mat);
    func_002AB6D8(mat, (f32 *)a1);
    *(f32 *)((u8 *)a1 + 8) = v;
}

INCLUDE_ASM("asm/levels", func_L04_003524D0);

INCLUDE_ASM("asm/levels", func_L04_00358868);


/* func_L04_0035F3E0 is defined in L04_0035F3E0-qcopy.c. */

void *func_L04_00362768(void *a0, void *a1, u32 a2, f32 f3) {
    L04Record *p = (L04Record *)(u32)func_002B9030(0x5E);
    L04RecordTail *q;
    L04Quad t;

    if ((u32)p != 0) {
        p->field10 = *(L04Quad *)a0;
        q = (L04RecordTail *)((u8 *)p + 0x20);
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x40);
        p->field03 = 0x48;
        p->field01 = 0;
        p->field02 = *(u8 *)ref_L04_00362768_00;
        p->field0C = f3 * 105000.0f;
        p->field08 = (u8)func_002A77E0(0xFF);
        p->field0A = (u16)a2;
        t = *(L04Quad *)a1;
        p->field20 = t;
        q->field0C = 0;
        q->field10 = 0.5f;
        q->field14 = f3;
        q->field18 = (u16)(func_002A77E0(2) - 1);
    }
    return (u32)p;
}

void *func_L04_00362940(void *a0, void *a1, u32 a2, f32 f3) {
    L04Spawned *p = (L04Spawned *)(u32)func_002B9030(0x5F);
    L04Vector *q;
    f32 v[4];

    if ((u32)p != 0) {
        p->field04 = 0x7F003CFF;
        p->field0C = 0x7F003CFF;
        p->field09 = (u8)(func_00283CF0(2.0f) + 0x20);
        p->field03 = 0x48;
        p->field01 = 3;
        q = (L04Vector *)((u8 *)p + 0x30);
        p->field02 = *(u8 *)ref_L04_00362940_00;
        q->v = *(L04Quad *)a1;
        *(f32 *)((u8 *)q + 0xC) = f3;
        p->field10 = *(L04Quad *)a0;
        func_00282F20(v, (f32 *)q, 0.5f);
        func_00282CF0((f32 *)((u8 *)p + 0x20), (f32 *)a0, v);
        p->field0A = (u16)a2;
        *(f32 *)((u8 *)p + 0x1C) = 0.005f;
        p->field08 = (u8)(*(u8 *)&p->field0A - 5);
        p->field2C = 1.0f;
    }
    return (u32)p;
}

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 word; float values[4]; } Vec4;
extern int func_00282978_2a50(void *);
extern void func_002B9180(void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20_2a50(void *, void *, float);
extern void func_00282CF0_2a50(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0_2a50(float);

/* Same body as func_002C7620, with this function's own callees. */
void func_L04_00362A50(char *self) {
    Vec4 buf, offset;
    char *s0;
    char *s2 = self + 0x30;
    float t;
    int color;

    if (func_00282978_2a50(self + 0xA) != 0) {
        func_002B9180(self);
        return;
    }
    s0 = self + 0x10;
    buf.word = *(TI128 *)s0;
    func_00282CC0(s0, s0, s2);
    *(float *)(s2 + 8) = *(float *)(s2 + 8) - *(float *)(s2 + 0xC);
    t = func_00282DF0(s2);
    func_00282F20_2a50(&offset, s2, t * 0.4f);
    func_00282CF0_2a50(self + 0x20, s0, &offset);
    *(float *)(self + 0x2C) = 1.0f;
    if (*(short *)(self + 0xA) < *(unsigned char *)(self + 8)) {
        t = func_00283CE0(*(short *)(self + 0xA)) / func_00283CE0(*(unsigned char *)(self + 8));
        color = (func_00283CF0_2a50(t * 127.0f) << 24) | 0x00FFFFFF;
        *(int *)(self + 0xC) = color;
        *(int *)(self + 4) = color;
    }
}

/* func_L04_00363690 is defined in L04_00363690-qcopy.c. */

/* func_L04_00363CA0 is matched in L04_00363CA0.c (built with -frac2-qcopy). */

INCLUDE_ASM("asm/levels", func_L04_00365300);

INCLUDE_ASM("asm/levels", func_L04_00378838);

extern void func_00115484(void *dst, s32 value, s32 size);

/* the header of one 0x1190-byte ripple patch */
typedef struct {
    u8 pad00[0x20];
    s32 field20;
    s32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    s32 field44;
} RipplePatch;

/* clears the three grids of every ripple patch and sets the patch's header fields */
void func_L04_0039FA08(u8 *base, s32 count) {
    s32 i;
    s32 j;
    u8 *g1;
    u8 *g2;
    u8 *g3;
    u8 *g4;
    u8 *g5;
    u8 *g6;
    u8 *g7;
    u8 *g8;
    f32 small;

    for (i = 0; i < count; i++) {
        g8 = base + (i * 0x1190 + 0x5D0);
        g7 = base + (i * 0x1190 + 0x590);
        g6 = base + (i * 0x1190 + 0x510);
        g5 = base + (i * 0x1190 + 0x550);
        g4 = base + (i * 0x1190 + 0x4D0);
        g3 = base + (i * 0x1190 + 0x490);
        g2 = base + (i * 0x1190 + 0x450);
        g1 = base + (i * 0x1190 + 0x50);
        small = -0.0016f;
        for (j = 0; j < 3; j++) {
            func_00115484(g1, 0, 0x400);
            g1 += 0x5C0;
            func_00115484(g2, 0, 0x40);
            g2 += 0x5C0;
            func_00115484(g3, 0, 0x40);
            g3 += 0x5C0;
            func_00115484(g4, 0, 0x40);
            g4 += 0x5C0;
            func_00115484(g5, 0, 0x40);
            g5 += 0x5C0;
            func_00115484(g6, 0, 0x40);
            g6 += 0x5C0;
            func_00115484(g7, 0, 0x40);
            g7 += 0x5C0;
            func_00115484(g8, 0, 0x18);
            g8 += 0x5C0;
        }
        {
            RipplePatch *q = (RipplePatch *)(base + i * 0x1190);

            q->field30 = 1.5707964f;
            q->field34 = -1.5707964f;
            q->field38 = 0.02f;
            q->field3C = -0.031f;
            q->field40 = 0.03f;
            q->field20 = 0;
            q->field24 = 0;
            q->field28 = small;
            q->field2C = small;
            q->field44 = 0;
        }
    }
}


/* func_L04_0039FEA8 is matched in L04_0039FEA8.c (built with -g). */

/* func_L04_0039FEF0 is matched in L04_0039FEF0-g8.c (built with -G8). */


typedef struct {
    u8 pad00[0x20];
    f32 field20;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
} D002A00E8Self;
extern f32 D_002A7A40[];
extern f32 D_002A7BC0[];
extern s32 D_002A7D90[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);

void func_L04_003A00E8(D002A00E8Self *p) {
    f32 a, b, c, d;
    s32 i;
    p->field20 = p->field20 + p->field28;
    if (p->field20 > 1.0f)
        p->field20 = p->field20 - 1.0f;
    if (p->field20 < 0.0f)
        p->field20 = p->field20 + 1.0f;
    p->field24 = p->field24 + p->field2C;
    if (p->field24 > 1.0f)
        p->field24 = p->field24 - 1.0f;
    if (p->field24 < 0.0f)
        p->field24 = p->field24 + 1.0f;
    p->field30 = func_30FE40(p->field30, p->field38);
    p->field34 = func_30FE40(p->field34, p->field3C);
    a = p->field20 + func_30F3A0(p->field30) * p->field40;
    b = p->field24 + func_30F3B8(p->field30) * p->field40;
    c = p->field20 + func_30F3A0(p->field34) * p->field40;
    d = p->field24 + func_30F3B8(p->field34) * p->field40;
    for (i = 0; i < 0x5C; i += 2) {
        if (D_002A7D90[i >> 1] == 0) {
            D_002A7A40[i] = D_002A7BC0[i] + a;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + b;
        } else {
            D_002A7A40[i] = D_002A7BC0[i] + c;
            D_002A7A40[i + 1] = D_002A7BC0[i + 1] + d;
        }
    }
}

extern void func_002FD1B8(u32 a0, u32 a1, void *a2);
void func_L04_003A02A0(u32 a0, u32 a1) {
    func_002FD1B8(a0, a1, 0);
}


INCLUDE_ASM("asm/levels", func_L04_003A0CE8);

INCLUDE_ASM("asm/levels", func_L04_003A0FC8);

INCLUDE_ASM("asm/levels", func_L04_003A1240);

INCLUDE_ASM("asm/levels", func_L04_003A14B8);

/* returns the packed header's signed rounded sixteen-byte block count in word units */
s32 func_L04_003A1540(const PackedHeaderCountView *header) {
    s32 fixed = header->extra + 16;
    s32 total = header->data_offset + fixed + header->length;
    return ((total + 15) / 16) * 4;
}

INCLUDE_ASM("asm/levels", func_L04_003A15C0);

INCLUDE_ASM("asm/levels", func_L04_003A1868);

void func_L04_003A1A48(u8 *dst, u16 *src, s32 count) {
    if (count <= 0)
        return;
    dst += 0x1E;
    do {
        *(u16 *)dst = *src;
        src++;
        dst += 0x1190;
        count--;
    } while (count != 0);
}

INCLUDE_ASM("asm/levels", func_L04_003A1C98);

extern u32 func_00282978(u8 *ptr);
void func_L04_003A1FA0(u8 *self) {
    if (func_00282978((u8 *)(*(u32 *)(*(u32 *)(self + 0x28) + 0x68) + 0x16)) != 0)
        *(u8 *)(*(u32 *)(self + 0x28) + 0x20) = 1;
}

/* func_L04_003A1FE0 is matched in L04_002CC748-g8.c (built with -G8). */

INCLUDE_ASM("asm/levels", func_L04_003A21F8);

typedef struct {
    u32 value;
    float factor;
    u32 pad[2];
} TblEntry;
typedef struct {
    TblEntry entries[64];
    u32 count;
} Tbl;
extern Tbl D_L04_00231E00;
void func_L04_003A5C08(u32 value, float factor) {
    D_L04_00231E00.entries[D_L04_00231E00.count].value = value;
    D_L04_00231E00.entries[D_L04_00231E00.count].factor = factor;
    D_L04_00231E00.count++;
}

INCLUDE_ASM("asm/levels", func_L04_003B3168);

INCLUDE_ASM("asm/levels", func_L04_003B3580);

INCLUDE_ASM("asm/levels", func_L04_003C3BA0);

INCLUDE_ASM("asm/levels", func_L04_003C4050);

/* Initialises particle i of this emitter: a random unit-cube direction, a random
   speed, size and lifetime from the emitter's three ranges, a zero age, the current
   colour, cleared flags and a start delay staggered by the particle's index. */
typedef struct {
    short first;
    u8 pad2[6];
    float life_min;
    float life_max;
    float speed_min;
    float speed_max;
    float size_min;
    float size_max;
} ParticleRanges3C4858;
typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} L04SpawnRecord;

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
#ifndef MACRO_ADDR
#define MACRO_ADDR __attribute__((section(".sdata")))
#endif
extern s32 D_L04_001B2E70 MACRO_ADDR;
extern u16 D_L04_001B2E74 MACRO_ADDR;
extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);

void func_L04_003C4858(void *emitter, s32 i)
{
    ParticleRanges3C4858 *ranges = *(ParticleRanges3C4858 **)((u8 *)emitter + 0x68);
    L04SpawnRecord *rec;
    f32 v;

    v = func_002A78D8(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[i];
    rec->x = v;
    rec->y = func_002A78D8(0.0f, 1.0f);
    rec->z = func_002A78D8(0.0f, 1.0f);
    D_L04_0023CA50[i] = func_002A7878(ranges->speed_min, ranges->speed_max);
    D_L04_0023CD70[i] = func_002A7878(ranges->size_min, ranges->size_max);
    D_L04_0023D220[i] = 0.0f;
    D_L04_0023D540[i] = func_002A7878(ranges->life_min, ranges->life_max);
    D_L04_0023D860[i] = D_L04_001B2E74;
    D_L04_0023D9F0[i] = 0;
    D_L04_0023DB80[i] = (i - ranges->first + 1) * D_L04_001B2E70;
    D_L04_0023D158[i] = 0;
}

/* A sixteen-byte record per spawn slot (L04SpawnRecord, above). */

extern L04SpawnRecord D_L04_0023BDD0[];
extern f32 D_L04_0023CA50[];
extern f32 D_L04_0023CD70[];
extern f32 D_L04_0023D220[];
extern f32 D_L04_0023D540[];
extern u8 D_L04_0023D158[];
extern u16 D_L04_0023D860[];
extern u16 D_L04_0023D9F0[];
extern u16 D_L04_0023DB80[];
extern s32 D_L04_001B2E70;
extern u16 D_L04_001B2E74;

extern f32 func_002A78D8(f32 a0, f32 a1);
extern f32 func_002A7878(f32 a0, f32 a1);

extern void func_L04_003C4858(void *a0, s32 a1);

void func_L04_003C49C0(void *a0, u32 a1) {
    f32 *obj = *(f32 **)((u8 *)a0 + 0x68);
    L04SpawnRecord *rec;
    f32 v;

    v = func_002A78D8(0.0f, 1.0f);
    rec = &D_L04_0023BDD0[a1];
    rec->x = v;
    rec->y = func_002A78D8(0.0f, 1.0f);
    rec->z = func_002A78D8(0.0f, 1.0f);
    {
        f32 v44 = obj[0x11];
        f32 v4c = obj[0x13];

        D_L04_0023CA50[a1] = func_002A7878(v44, v44 + 2.0f);
        D_L04_0023CD70[a1] = func_002A7878(v4c, v4c + 4.0f);
    }
    D_L04_0023D220[a1] = 0.0f;
    D_L04_0023D540[a1] = func_002A7878(0.003f, 0.005f);
    D_L04_0023D158[a1] = 1;
}

INCLUDE_ASM("asm/levels", func_L04_003C6FE8);

extern u32 D_L04_001B2E84 __attribute__((sda));

/* adds VALUE to the running total and returns the total as it was before */
u32 func_L04_003C70C8(u32 value) {
    u32 old = D_L04_001B2E84;
    D_L04_001B2E84 = old + value;
    return old;
}
