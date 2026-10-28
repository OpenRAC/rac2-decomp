#include "include_asm.h"

#include "common.h"

extern f32 func_2E5318(f32 a, f32 b);

extern f32 func_2E4918(f32 a, f32 b);

extern f32 D_L07_001B0F84 __attribute__((sda));

extern u8 *D_L07_001B22DC __attribute__((sda));

extern void func_317520(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);

extern void func_421288(s32 a, f32 b, f32 c);

extern void func_4212D0(f32 a, f32 b);

extern u8 *func_2CD050(s32 a);

extern void func_3109C8(u8 *a, s32 b, s32 c);

extern s32 func_312FA8(u8 *a, s32 b, s32 c);

extern f32 func_313008(u8 *a, s32 b);

extern void func_313DD8(void *a, f32 b, f32 c);

extern f32 D_L07_001B10B8 __attribute__((sda));

extern f32 D_L07_001B10BC __attribute__((sda));

extern u32 D_L07_001B10C0 __attribute__((sda));

extern f32 D_L07_001B0FD0 __attribute__((sda));

extern f32 D_L07_001B0E98 __attribute__((sda));

extern f32 D_L07_001B0E9C __attribute__((sda));

extern f32 D_L07_001B0EA0 __attribute__((sda));

extern f32 func_002AA2E8(f32 *value, f32 target, f32 step);

extern void func_002A7750(u8 *a, u8 b, s32 c);

extern void func_0029F338(void *a);

extern f32 func_00283B98(f32 a, f32 b);

extern void func_L00_002E6CF0(void *a, void *b);

extern void func_L07_003F4C18(void *a, void *b, void *c);

extern s32 func_L01_003120A8(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);

extern char func_L07_003F4CC0[];

/* Advances the object's own state: three step kinds by the 0x20 flag, then the shared
   spin and the two sampled vectors. */
void func_L07_003F4970(u8 *a0)
{
    u8 *s1 = a0;
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 v1 = *(u8 *)(a0 + 0x20);
    f32 v[4];
    f32 w[4];

    switch (v1) {
    case 0:
        {
            u32 n = *(u16 *)(s1 + 0x96) + 1;

            *(u16 *)(s1 + 0x96) = n;
            if ((u16)n == 1) {
                break;
            }
            func_002AA2E8((f32 *)(s2 + 0x24), 1.0f, D_L07_001B0E98 * (1.0f / 60.0f));
            if (1.0f <= *(f32 *)(s2 + 0x24)) {
                func_002A7750(s1, 1, -1);
            }
        }
        break;
    case 1:
        func_002AA2E8((f32 *)(s2 + 0x24), 0.0f, D_L07_001B0E9C * (1.0f / 60.0f));
        if (*(f32 *)(s2 + 0x24) <= 0.0f) {
            func_0029F338(s1);
            return;
        }
        break;
    }
    *(f32 *)(s2 + 0x28) = func_00283B98(*(f32 *)(s2 + 0x28), D_L07_001B0EA0 * 0.00029088825f);
    func_L00_002E6CF0(func_L07_003F4CC0, s1);
    if (0.333f < *(f32 *)(s2 + 0x24)) {
        func_L07_003F4C18(s1, v, w);
        func_L01_003120A8(*(u32 *)(s1 + 0xB8), v, w, 1, *(f32 *)(s2 + 0x2C), 1.0f, 0, 1, 0);
    }
}


typedef int TI128 __attribute__((mode(TI)));

/* The object up to its flag word, its state pointer and its counter. */
typedef struct {
    u8 pad00[0x34];
    u16 flags34;
    u8 pad36[0x68 - 0x36];
    u8 *state;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} SibObj;

/* The state record up to its two group words. */
typedef struct {
    u8 pad00[0xCC];
    s32 groupCC;
    s32 groupD0;
} SibGroups;

extern f32 D_L07_001B173C;

extern u8 D_L07_001B1730 __attribute__((sda));

extern u16 **D_L07_001A9014;

extern u8 *D_L07_001B2954;

extern u8 *D_L07_001B295C;

extern s32 D_L07_001B1E90;

extern void func_L00_002B9D60(void *obj, void *pos, s32 a2, s32 a3);

extern void func_L00_0036AE00(s32 id, s32 a1);

/* Switches the object to its second phase. */
void func_L07_00410930(SibObj *a0)
{
    f32 arg[4];
    f32 v[4];
    SibGroups *state;
    u16 *p;
    u16 *q;
    u8 *e;

    *(TI128 *)v = 0;
    v[2] = D_L07_001B173C;
    *(TI128 *)arg = *(TI128 *)v;
    state = (SibGroups *)a0->state;
    func_L00_002B9D60(&D_L07_001B1730, arg, 0, 1);
    a0->flags34 |= 2;
    a0->f98 = 0;
    for (p = D_L07_001A9014[state->groupD0];
         p != 0 && ((s16)p[-1] >= 0 || p == D_L07_001A9014[state->groupD0]) &&
         (e = D_L07_001B2954 + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] &= 0xFB;
    }
    for (p = D_L07_001A9014[state->groupCC];
         p != 0 && ((s16)p[-1] >= 0 || p == D_L07_001A9014[state->groupCC]) &&
         (e = D_L07_001B2954 + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] |= 4;
    }
    for (q = D_L07_001A9014[state->groupCC];
         q != 0 && ((s16)q[-1] >= 0 || q == D_L07_001A9014[state->groupCC]) &&
         (e = D_L07_001B295C + ((*q & 0x7FFF) << 6)) != 0;
         q++) {
        *(f32 *)(e + 0x38) -= 100.0f;
        func_L00_0036AE00(*q & 0x7FFF, 1);
    }
    D_L07_001B1E90 = 2;
}


/* Seeds the two shared field defaults, then fills the 0x450 record once. */
INCLUDE_ASM("asm/levels", func_L07_003F8780);

/* Arms the spinner on the first pass, otherwise steers its 0x20 angle down. */
INCLUDE_ASM("asm/levels", func_L07_003F6CF0);

/* Steers the 0x54 yaw toward the argument and refreshes the two 0xF8 angles. */

/* Feeds the four 0xA8 ids to the shared geometry pass. */
INCLUDE_ASM("asm/levels", func_L07_0040F6B8);

extern f32 func_2E49C8(f32 a, f32 b);

extern f32 func_2E5360(f32 a, f32 b);

extern void func_3144F0(void *a0, void *a1, f32 a2, f32 a3, f32 a4, f32 a5, s32 a6);

/* The two level floats the scaling uses; the pointers are reached absolutely. */
extern f32 D_L07_001B17D4 __attribute__((sda));

extern f32 D_L07_001B17D8 __attribute__((sda));

extern u8 *D_L07_001B9250 __attribute__((nosda));

extern u8 *D_L07_001ADAAC MACRO_ADDR;

extern u8 D_L07_001B31A9;

/* Steers the object's two angles: the yaw toward the argument, the pitch from the shared
   record, and the two scaled fields of the state record. */
void func_L07_0040F468(u8 *a0)
{
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *v1;
    u8 *v0;
    f32 *p;
    f32 t;
    f32 r;
    f32 q;
    f32 f20;
    f32 f21;
    f32 f22;

    v1 = D_L07_001B9250;
    if (*(s16 *)(v1 + 0x86) != 0) {
        return;
    }
    v0 = D_L07_001ADAAC;
    if (v0 == 0) {
        return;
    }
    f22 = 3.14159274f;
    s0 = *(u8 **)(v1 + 0x70);
    s1 = *(u8 **)(a0 + 0x68);
    p = (f32 *)(s0 + 0x160);
    r = func_2E5318(*(f32 *)(v0 + 0xF8), f22);
    s2 = s0 + 0x1C0;
    q = func_2E49C8(p[0], p[1]);
    t = func_2E5360(r, q);
    f21 = D_L07_001B17D4 * 0.0000048481375f;
    f20 = D_L07_001B17D8 * 0.000290888245f;
    if (D_L07_001B31A9 == 0) {
        t = func_2E5318(t, f22);
    }
    func_3144F0(&t, s1 + 0x1A8, 0.0f, f21, f21, f20, 0);
    *(f32 *)(s2 + 0x1C) = 1.0f;
    *(f32 *)(s2 + 0x14) = -*(f32 *)(s1 + 0x1A8);
}

extern u8 D_00189E20[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern void func_002AD470(u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f);
extern f32 func_002A0F48(u8 *a);
extern f32 func_00282E48(u8 *a, u8 *b);

typedef struct { u8 pad[0xA8]; s32 ids[4]; } Rec;

void func_L07_0040F760(u8 *a0)
{
    u8 *s7 = *(u8 **)(a0 + 0x68);
    u32 frame = ((s32)a0 >> 8) & 7;
    s32 i;

    for (i = 0; i < 4; i++) {
        s32 id = ((Rec *)s7)->ids[i];
        u8 *o;
        if (id == -1)
            continue;
        o = D_L07_001B22DC + (id << 8);
        func_002AD470(o, a0, s7 + 0x120 + i * 0x10, s7 + 0x160 + i * 0x10, o + 0x10, o + 0xF0);
        func_002A0F48(o);
        if (*(s16 *)(o + 0xAA) == 0x2F6) {
            u8 *p = D_00189E20;
            if (*(s32 *)(p + 0x229C) == 13 && *(u8 **)(p + 0xAA4) == o && *(u8 **)(p + 0x3A0) != a0) {
                if (func_00282E48(p + 0x80, o + 0x10) < 8.0f)
                    *(u8 **)(p + 0x3A0) = a0;
                continue;
            }
        }
        if ((D_L07_001B1E08 & 7) == frame && *(s16 *)(o + 0xAA) == 0x2F6) {
            u8 *q = D_00189E20;
            if (*(s32 *)(q + 0x229C) != 13) {
                if (D_L07_001ADAAC == a0)
                    *(u16 *)(o + 0x34) &= 0xEFFF;
                else
                    *(u16 *)(o + 0x34) |= 0x1000;
            }
        }
    }
}

extern f32 D_L07_001B0FD0 __attribute__((sda));
extern char D_00189EA0[];
extern char D_L07_001B9200[];
extern u8 *D_L07_001C36C0[];
extern int func_00277F48(void *, float, int, char *, void *);
extern int func_002E5DA0(int, int, char *, int);
extern int func_002A8C28(char *, char *, int, float, float, float, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_0032DA58(char *, char *, char *, float);
extern void func_L07_003F6CF0(u8 *a);
extern void func_L07_003F6DC0(u8 *self, float *target);
extern void func_L07_003F6F00(u8 *a0);

void func_L07_003F6960(u8 *a0)
{
    u8 *state;
    u8 *p;
    char *pos;
    char *tune;
    f32 dir[4];
    s32 n, k;

    state = *(u8 **)(a0 + 0x68);
    if (a0[0x20] != 1)
        func_L07_003F6CF0(a0);
    switch (a0[0x20]) {
    case 2:
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L07_001B0FD0;
        func_L07_003F6DC0(a0, (float *)D_00189EA0);
        func_L07_003F6F00(a0);
        n = func_00277F48(a0 + 0x10, 0.333f, 0, (char *)a0, 0);
        if (n > 0) {
            p = (u8 *)D_L07_001C36C0;
            for (k = n; k != 0; k--, p += 4) {
                u8 *other = *(u8 **)p;
                if (other == a0)
                    continue;
                if (other != *(u8 **)(a0 + 0xB8))
                    func_002A7750(a0, 3, -1);
            }
        }
        break;
    case 3:
        func_002E5DA0(6, 0, (char *)a0, 0xE5F);
        pos = (char *)a0 + 0x10;
        func_002A8C28((char *)a0, pos, 0x10000, 6.0f, 5.0f, 1.0f, 0, 1, 0);
        func_002A8C28((char *)a0, pos, 1, 4.0f, (f32)state[0x34], 1.0f, 0, 1, 0);
        func_00282CF0(dir, D_L07_001B9200, pos);
        func_00282F20(dir, dir, 1.0f);
        func_0032DA58((char *)a0, pos, (char *)dir, 0.0f);
        tune = D_L07_001B9200 - 0x140;
        *(f32 *)(tune + 0x180) = 0.1f;
        *(s32 *)(tune + 0x188) = 0x5A;
        *(f32 *)(tune + 0x160) = 0.2f;
        *(s32 *)(tune + 0x168) = 0x3C;
        *(s32 *)(tune + 0x16C) = 0;
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        func_002A7750(a0, 1, -1);
        break;
    }
}
