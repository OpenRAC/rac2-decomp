#include "include_asm.h"

typedef unsigned char u8;

typedef unsigned int u32;

typedef int s32;

/* Three measured byte-state cases and width-specific field views.
   The correspondence name UpdateMoby_2426 does not establish an original
   class, enumeration, allocation or field-name declaration. */
extern void func_002A7750(u8 *, u8, s32);

extern u32 func_002B38B8(u8 *);

typedef float f32;

typedef struct {
    u32 field00;
    u32 field04;
    f32 field08;
    f32 field0C;
} NativeCallbackTimer;

extern NativeCallbackTimer D_L04_001B98E0;

extern f32 D_L04_001B1C88 __attribute__((sda));

/* Four-byte pointer in the resident image (0x001B2A1C).  The retail reads it
   with a per-site `lui $r,%hi` + `lw $r,%lo($r)` pair, which is gas's expansion
   of the bare-symbol macro cc1 emits only for an `sda` symbol. */
extern u8 *D_L03_001B2A1C __attribute__((sda));

/* func_L03_003C5B28 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5CE8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5DC8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
extern void func_L03_003CAB80(u8 *, void *, f32 *);
extern void func_L03_00419A60(u32, u8 *, s32);
extern s32 func_00277258(void *, s32, void *, f32);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_003294F0(u8 *entity, s32 enabled);
extern char D_00189EA0[];

typedef struct {
    u8 pad0[0x110];
    f32 f110;
    f32 f114;
    u8 pad118[0x220 - 0x118];
    u32 f220;
    u8 pad224[0x340 - 0x224];
    f32 f340[4];
    u8 pad350[0x358 - 0x350];
    u8 *f358;
} L03_5EE8Vars;

typedef struct {
    u8 pad0[0x10];
    s32 f10;
} L03_5EE8Class;

typedef struct {
    u8 pad0[0x24];
    L03_5EE8Class *f24;
    u8 pad28[0x43 - 0x28];
    u8 f43;
    u8 pad44[0x68 - 0x44];
    L03_5EE8Vars *f68;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} L03_5EE8Moby;

void func_L03_003C5EE8(L03_5EE8Moby *m) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 test[4] __attribute__((aligned(16)));
    L03_5EE8Vars *v = m->f68;

    func_L03_00419A60(v->f220, v->f358 + 0x10, 0);
    func_L03_003CAB80(v->f358, D_00189EA0, pos);
    qcopy(test, pos);
    test[2] += v->f110 + v->f114;
    if (func_00277258(test, 0, m, v->f110) == 0) {
        qcopy(v->f340, pos);
        func_L00_003294F0(v->f358, 0);
        v->f358 = 0;
        m->f98 = m->f24->f10;
        func_002A7750((u8 *)m, 0x11, 4);
        if (m->f43 != 0) {
            func_002A7470(m, 0, 0, 0x14);
        }
    } else {
        func_L03_00419A60(v->f220, v->f358 + 0x10, 1);
    }
}

/* func_L03_003C9FB8 lives in L03_003C9FB8.c. */

int func_L03_003CA138(unsigned char *p) { return p[0x20] == 1; }

/* func_L03_003CA148 is matched in its own unit, L03_003CA148.c. */

void func_L03_003CA220(u8 *a0, f32 a1) {
    *(f32 *)(*(u8 **)(a0 + 0x68) + 0xA0) = a1;
}

/* func_L03_003CA230 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1300. */

int func_L03_003CA280(unsigned char *p) { return p[0x20] == 1; }

INCLUDE_ASM("asm/levels", func_L03_003CA290);

INCLUDE_ASM("asm/levels", func_L03_003CA4B0);

void func_L03_003CA9F8(u8 *entity) {
    switch (entity[0x20]) {
    case 0:
        func_002A7750(entity, 1, -1);
        *(u32 *)(entity + 0x98) = 0;
        *(unsigned short *)(entity + 0x34) =
            (*(unsigned short *)(entity + 0x34) | 0x41) & 0xEFFF;
        break;
    case 1:
        if (func_002B38B8(entity) != 0) {
            func_002A7750(entity, 2, -1);
            *(u32 *)(entity + 0x98) =
                *(u32 *)(*(u8 **)(entity + 0x24) + 0x10);
        }
        break;
    case 2:
        if (func_002B38B8(entity) == 0) {
            func_002A7750(entity, 1, -1);
            *(u32 *)(entity + 0x98) = 0;
        }
        break;
    }
}

extern int func_002ACBC8(u8 *, u32);

u32 func_L03_003CAAC8(u8 *a0, u8 *a1) {
    return func_002ACBC8(a1, *(u32 *)(*(u8 **)(a0 + 0x68) + 0x60)) != 0;
}

/* func_L03_003CAAF0 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1354. */

/* func_L03_003CAB80 lives in L03_003CAB80.c. */

extern f32 func_00283B98(f32, f32);

void func_L03_003CC1D8(u8 *a0) {
    if (*(u8 *)(a0 + 0x31) == 0)
        return;
    *(f32 *)(a0 + 0xF4) = func_00283B98(*(f32 *)(a0 + 0xF4),
                                        0.10471977293491364f);
    *(f32 *)(a0 + 0xF8) = func_00283B98(*(f32 *)(a0 + 0xF8),
                                        0.04654212296009064f);
}

/* func_L03_003CC238 lives in L03_003CC238.c. */

/* Defined in L03_003CC478.c. */

INCLUDE_ASM("asm/levels", func_L03_003D04E0);

/* func_L03_003D09D0 is matched in its own unit, src/levels/shared/L03_003D09D0.c (-g). */

INCLUDE_ASM("asm/levels", func_L03_003D0AE0);

extern f32 func_002A7878(f32, f32);

extern s32 func_002A77E0(s32);

extern void func_002A7A00(f32 *, f32, f32);

extern void func_00282CC0(void *, void *, void *);

extern void func_002C2210(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);

void func_L03_003D0FC8(u8 *a0, s32 a1, s32 a2) {
    f32 buf[3];
    f32 f20, f21;
    s32 s1, s2;

    s2 = a2;
    f20 = func_002A7878(0.25f, 1.0f);
    s1 = func_002A77E0(2);
    f21 = func_002A7878(3.0f, 7.0f) * (1.0f / 3600.0f);
    func_002A7A00(buf, 0.0f, 0.1f);
    func_00282CC0(buf, buf, a1);
    func_002C2210(buf, 0x28, 0x7F800000, 0, s1, s2, 0, f20 * 0.2f, f20, f21);
    func_002C2210(buf, 0x3C, 0x7F7F7F7F, 1, -s1, s2, 0, f20 * 0.14f, f20 * 0.7f, f21);
}

INCLUDE_ASM("asm/levels", func_L03_003D9578);

INCLUDE_ASM("asm/levels", func_L03_003D9820);

INCLUDE_ASM("asm/levels", func_L03_003E21B0);

INCLUDE_ASM("asm/levels", func_L03_003E26C8);

INCLUDE_ASM("asm/levels", func_L03_003E2968);

INCLUDE_ASM("asm/levels", func_L03_003E2C08);

INCLUDE_ASM("asm/levels", func_L03_003E2D98);

INCLUDE_ASM("asm/levels", func_L03_003E2EC8);

INCLUDE_ASM("asm/levels", func_L03_003E3018);

extern u32 D_0024A7B0;

extern s32 ref_L03_003E3750_00(u8 *, u32);

/* Copies the six values the record's own row of the shared table holds into the
   record's list, skipping the ones the record does not take, and ends the list
   with 255. */
void func_L03_003E3308(u8 *a0) {
    u32 rec = *(u32 *)(a0 + 0x68);
    u32 v = *(u32 *)((u8 *)&D_0024A7B0 + *(short *)(rec + 0x50) * 24);
    s32 count = 0;
    u32 n = 0;
    u32 ok;

    if (v != 255) {
        u32 flags = rec + 0x20;
        u32 list = rec + 0x40;

        do {
            if (*(short *)(rec + 0x64) == 0 &&
                v == *(u8 *)(*(short *)(rec + 0x62) + flags + 1)) {
                ok = 1;
            } else if (ref_L03_003E3750_00(a0, v)) {
                ok = 1;
            } else {
                ok = 0;
            }
            if (ok) {
                *(u8 *)(list + n) = v;
                n++;
            }
            count++;
            if (count >= 6)
                break;
            v = *(u32 *)((u8 *)&D_0024A7B0 + count * 4 + *(short *)(rec + 0x50) * 24);
        } while (v != 255);
    }
    *(u8 *)(rec + n + 0x40) = 255;
}

INCLUDE_ASM("asm/levels", func_L03_003E3430);

/* func_L03_003E3678 lives in L03_003E3678-g8.c. */


INCLUDE_ASM("asm/levels", func_L03_003E3800);

INCLUDE_ASM("asm/levels", func_L03_003E3A00);

INCLUDE_ASM("asm/levels", func_L03_003E4148);


INCLUDE_ASM("asm/levels", func_L03_003E4680);

extern u8 *func_0029EFD0(s32);

extern void func_002B37E8(u8 *, u8 *);

extern void func_002833F0(u8 *, u8 *);

void func_L03_003E5070(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);
    u8 *p = func_0029EFD0(0xB28);

    if (p == 0)
        return;
    func_002B37E8(p, a0);
    func_002833F0(p + 0xC0, p + 0xF0);
    *(unsigned short *)(p + 0x34) =
        (*(unsigned short *)(p + 0x34) | 0x100);
    *(u32 *)(q + 0x58) = (u32)p;
}

/* func_L03_003E50E0 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x1CB0. */

extern void func_003355A8(int);

extern void func_0026FF08(int, int, f32, f32, f32, f32);

extern void func_0029F338(u8 *);

extern s32 g_activeGadgetItem;

extern f32 D_001B9C14;

/* The retail materialises this one's address with `lui $at`, which is gas's expansion of the
   bare-symbol macro cc1 only emits for an `sda` symbol. */
extern f32 D_001B2464 __attribute__((sda));

/* Hands the entity's gadget class id to the active-gadget global, clears the entity's
 * gadget state and releases the resident class it was holding. */
void func_L03_003E5170(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);
    f32 zero = 0.0f;
    f32 scale = 1.12434113f;    /* bits 0x3F8FEA69 (0x3F8FEA69 != 1.12434f) */

    func_003355A8(3);
    D_001B9C14 = scale;
    func_0026FF08(1, 0, scale, 0.005f, 0.2f, zero);
    *(f32 *)(q + 0x6C) = zero;
    g_activeGadgetItem = *(s32 *)(q + 0x64);
    D_001B2464 = zero;
    if (*(u8 **)(q + 0x58) != 0) {
        func_0029F338(*(u8 **)(q + 0x58));
        *(u32 *)(q + 0x58) = 0;
    }
}

void func_L03_003E5218(u8 *a0) {
    *(u32 *)(*(u8 **)(a0 + 0x68) + 0x60) = 1;
}


INCLUDE_ASM("asm/levels", func_L03_00409248);

/* func_L03_00409AB0 lives in L03_00409AB0-g8.c. */


extern f32 func_00282C48(f32);

int func_L03_00409D28(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);

    return func_00282C48(*(f32 *)(a0 + 0x18) - *(f32 *)(q + 0x8)) < 0.01f;
}

/* func_L03_00419578 lives in L03_00419578-g8.c. */

u32 func_L03_004197A8(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 2)
        return *(u32 *)(p + 0x10);
    return 0;
}

/* func_L03_004197C8 lives in the -g8 sibling: its first call reads a float
   constant through $gp at 0x2AA0. */

void func_L03_00419818(u8 *a0, u32 a1) {
    u8 *p = *(u8 **)(a0 + 0x68);
    s32 n = *(s32 *)(p + 0x10);
    *(u32 *)(p + 0x1C) = a1;
    n--;
    *(s32 *)(p + 0x10) = n;
    if (n == 0)
        func_002A7750(a0, 3, -1);
}


extern void func_0029F338(u8 *);

extern u32 func_L03_00329EF0(u8 *, u8 *, u8 *, s32);

void func_L03_004199F0(u8 *a0) {
    u8 *q = *(u8 **)(a0 + 0x68);

    if (*(u8 *)(a0 + 0x20) == 0) {
        if (q == 0) {
            func_0029F338(a0);
        } else {
            *(u32 *)(q + 0x480) =
                func_L03_00329EF0(a0, q, q + 0x80, 0x20);
            func_002A7750(a0, 1, -1);
        }
    }
}

/* Hands one record of the pool the level index selects to the shared lookup and then sets or
   clears the low bit of the record's tenth halfword flag. */
void func_L03_00419A60(u32 a0, u8 *a1, s32 a2) {
    u8 *rec = (u8 *)D_L03_001B2A1C + (a0 << 8);
    u8 *q = *(u8 **)(rec + 0x68);
    s32 index;

    if (*(u8 *)(rec + 0x20) == 0)
        func_L03_004199F0(rec);
    index = -1;
    if (func_L02_0032EDD8(a1, &q[0x80], ((s32 *)q)[0x120], &index) == 0)
        return;
    if (a2 != 0)
        *(unsigned short *)(q + (index << 5) + 0x8C) &= 0xFFFE;
    else
        *(unsigned short *)(q + (index << 5) + 0x8C) |= 1;
}

extern s32 func_L02_0032E998(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);

s32 func_L03_00419B10(u32 a0, u8 *a1, u8 *a2, u8 *a3, s32 *x4, s32 *x5,
                     float margin, float tolerance) {
    u8 *q = *(u8 **)((u8 *)D_L03_001B2A1C + (a0 << 8) + 0x68);

    return func_L02_0032E998(a1, a2, a3, q + 0x80, *(s32 *)(q + 0x480), x4, x5,
                            margin, tolerance);
}

s32 func_L03_00419B58(u32 a0, s32 a1) {
    u8 *q = *(u8 **)((u8 *)D_L03_001B2A1C + (a0 << 8) + 0x68);
    u8 *p;

    if (a1 != -1) {
        p = q + (a1 << 5);
        return *(s32 *)(p + 0x80);
    }
    return -1;
}

extern s32 func_L02_0032EDD8(u8 *, u8 *, s32, s32 *);

void func_L03_00419B90(u32 a0, u8 *a1, u8 *a2) {
    u8 *q = *(u8 **)((u8 *)D_L03_001B2A1C + (a0 << 8) + 0x68);

    func_L02_0032EDD8(a1, q + 0x80, *(s32 *)(q + 0x480), (s32 *)a2);
}

s32 func_L03_00419C00(u8 *, u8 *, u8 *);

s32 func_L03_00419BD8(u32 a0, u8 *first, u8 *second) {
    return func_L03_00419C00((u8 *)D_L03_001B2A1C + (a0 << 8), first, second);
}

INCLUDE_ASM("asm/levels", func_L03_00419C00);

INCLUDE_ASM("asm/levels", func_L03_00419C58);

INCLUDE_ASM("asm/levels", func_L03_0041B848);

INCLUDE_ASM("asm/levels", func_L03_00424C40);

extern s32 func_002A77E0(s32);

void func_L03_00425030(u8 *a0) {
    u8 *rec = *(u8 **)(a0 + 0x68);
    f32 *p = (f32 *)(rec + 0x10);
    s32 i;

    for (i = 3; i >= 0; i--) {
        *p++ = (f32)func_002A77E0(0xFF);
    }
    *(f32 *)(rec + 0x20) = -1.0f;
    *(f32 *)(rec + 0x24) = -2.25f;
    *(f32 *)(rec + 0x28) = 1.25f;
    *(f32 *)(rec + 0x2C) = 2.5f;
    {
        s32 j = 3;
        u32 *q = (u32 *)(rec + 0x3C);
        u32 v = 0xFF;

        for (; j >= 0; j--) {
            *q = v;
            q--;
            v -= 0x40;
        }
    }
    *(f32 *)(rec + 0x40) = 2.0f;
    *(f32 *)(rec + 0x44) = 2.46f;
    *(f32 *)(rec + 0x4C) = 2.0f;
    *(f32 *)(rec + 0x48) = 2.46f;
}


/* The resident word at 0x001A79F0, below the level base, so its value is the same in every
   program.  The retail reads it absolutely in ordinary flow and through $gp in a delay slot,
   which is what the `sda` declaration's bare-symbol model gives in this unit. */
extern int D_001A79F0 __attribute__((sda));

extern void func_L03_0042B868(u8 *, void *, void *);

extern void func_L03_0042B908(u8 *, u32);

/* Allocates the object's record, copies the two source fields into it, hands the record to
   the two setup helpers, and writes into the resident block the size the word at 0x001A79F0
   selects. */
u8 *func_L03_0042B6F8(void *a0, void *a1, u32 a2, u8 *a3, u32 a4, u32 a5) {
    u8 *s0 = func_0029EFD0(0x13BA);
    u8 *s1;

    if (s0 != 0) {
        *(unsigned short *)(s0 + 0x34) |= 0x100;
        s1 = *(u8 **)(s0 + 0x68);
        *(u8 *)(s0 + 0x30) = (a3 != 0) ? *(u8 *)(a3 + 0x30) : 0x96;
        *(unsigned short *)(s0 + 0x32) = (a3 != 0) ? *(unsigned short *)(a3 + 0x32) : 0x96;
        *(u8 *)(s0 + 0x20) = 0;
        *(u32 *)(s1 + 0x20) = a4;
        *(u32 *)(s1 + 0x44) = (u32)a3;
        func_L03_0042B868(s0, a0, a1);
        func_L03_0042B908(s0, a2);
        if (a5 == 0)
            *(u32 *)(s1 + 0x3C) = 0;
        if (D_001A79F0 == 0)
            *(u32 *)(s1 + 0x48) = 0x48;
        if (D_001A79F0 == 3)
            *(u32 *)(s1 + 0x48) = 0x3F;
        if (D_001A79F0 == 6)
            *(u32 *)(s1 + 0x48) = 0x44;
        if (D_001A79F0 == 9)
            *(u32 *)(s1 + 0x48) = 0x48;
        if (D_001A79F0 == 0x12)
            *(u32 *)(s1 + 0x48) = 0x43;
    }
    return s0;
}


void func_L03_0042B908(u8 *a0, u32 a1) {
    if (a0 != 0) {
        u8 *p = *(u8 **)(a0 + 0x68);
        *(u32 *)(p + 0x2C) = (s32)a1 >> 24;
        *(u32 *)(p + 0x40) = a1 & 0xFFFFFF;
    }
}

/* func_L03_0042B930 lives in the -g8 sibling: its first read is a $gp float. */

typedef struct {
    int a;
    int b;
    float c;
    int d;
    void (*e)(void);
} S_2fa6d8_r0043AC40;

extern S_2fa6d8_r0043AC40 r1_D_L02_00167680_FBB10 __asm__("r1_D_L02_00167680");

extern void r1_func_L02_002FBB48(void);

typedef struct {
    int a;
    int b;
    float c;
    float d;
} S_r0043AC40;

extern S_r0043AC40 r1_D_L02_00167680;

extern void r1_func_L02_002FBB48();

/* rac1-decomp src/overlays/shared/vendor_002A5218.c: func_L02_002FBB10 */
/* Adapted from Lombyte (MIT) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002ec308.c, FUN_L02_002fa6d8. */
void func_L03_0043AC40(void) {
    r1_D_L02_00167680_FBB10.a = 0;
    r1_D_L02_00167680_FBB10.b = 0;
    r1_D_L02_00167680_FBB10.c = 10000.0f;
    r1_D_L02_00167680_FBB10.d = 0;
    r1_D_L02_00167680_FBB10.e = r1_func_L02_002FBB48;
}

extern f32 D_L03_001B9BEC;

extern void func_L00_00424A88(s32, f32, f32);

extern void func_L03_002D84F0(void *);

extern void func_L03_0043ACD8(void);

void func_L03_0043AC78(void) {
    if (D_L03_001B9BEC != 0.0f) {
        func_L00_00424A88(1, D_L03_001B9BEC * 0.35f, 0.005f);
        func_L03_002D84F0(func_L03_0043ACD8);
    }
}

extern void func_L03_0043ACD8(void);


/* rac1-decomp src/game/stub.c: func_001E97C8 */
/* Takes an argument (callers pass one, e.g. r1_func_001EC210) and ignores
   it -- the unused parameter costs no codegen, still 0/8. */
int func_L03_0043AF30(void *arg0) {
    return 0;
}


void func_L03_00456E58(void)
{
}

void func_L03_004586F0(void)
{
}
