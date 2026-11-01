#include "include_asm.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef short s16;

typedef int s32;

extern char *D_L02_001B3AF8 __attribute__((sda));

extern s32 func_002F3220(char *, float);

extern int D_L02_002A5520[];

extern int D_L02_002A5560[];

extern int func_00282948(void *);

extern void func_L00_002E6EF8(char *, char *);

extern void func_L00_0030CF60(void);

extern char D_L02_004004D8[];

extern void func_002A7750(char *, s32, s32);

extern int func_L02_003D77B8(char *);

extern void func_L02_003D7868(char *, char *);

extern s32 func_003D77F8(char *);

extern void func_003D78A8(char *);

extern s32 func_L02_003D7830(char *);

extern char *D_L02_001B359C __attribute__((sda));

extern u32 D_L02_001FC060[];

extern void func_L02_003D2390(char *);

extern void func_L02_003D4900(char *);

extern void func_L02_003DB6D8(char *);

extern void func_L02_003F18E8(char *);

extern void func_L02_0040B980(char *);

extern void func_L02_0040D180(char *);

extern s32 func_L02_00400650(char *, s32);

extern char D_L02_001BA3C0[];

extern char *D_L02_001B368C __attribute__((sda));

extern void func_0029FCC0(char *, s32, char *);

extern float func_00282E80(char *, char *);

extern char D_00189EA0[];

extern int D_L02_002A5600[];

extern char D_001A63A8[];

extern int D_0017A80;

void func_L02_003F5430(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);
    s32 i;
    s16 *s2;
    *(u32 *)(s0 + 0x84) = 0;
    for (i = 0; i < *(s32 *)(s0 + 0x80); i++) {
        char *q;
        s2 = (s16 *)(s0 + 0x40 + i * 2);
        q = D_L02_001B3AF8 + *s2 * 32;
        if (func_002F3220(q, *(float *)(q + 0x10)) != -1)
            *(u32 *)(s0 + 0x84) |= 1 << i;
    }
}

typedef int TI128 __attribute__((mode(TI)));

extern int D_L02_001B30C8 __attribute__((sda));
extern float D_L02_001B1040[2] __attribute__((sda));
extern char *D_L02_001B3B00 __attribute__((sda));
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002833F0(float *, float *);
extern void func_L02_002F2B88(char *, char *, float *);

/* Runs func_L02_003F5430 first when bit 0 of D_L02_001B30C8 is set. The angle at +0x88 is stepped
   (func_002AA2E8, 0.05 degree) towards the target at +0x8C when func_00282948 reports the timer at
   +0x90 idle or just run out, and towards zero while it is still counting down. When the target lies
   between zero and the angle, the timer gets a random 30..90 and the target a random size with the
   opposite sign. The angle is then the third word of a vector func_002833F0 turns into a matrix,
   which multiplies the 64-byte records of D_L02_001B3B00 that the entries of the list at +0x40 name,
   for each bit set in the mask at +0x84. */
void func_L02_003F54D8(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    float m[12];
    float b[4];
    float a[4];
    s32 i;
    s16 *s2;

    if (D_L02_001B30C8 & 1)
        func_L02_003F5430(a0);
    if (func_00282948(state + 0x90) != 0) {
        func_002AA2E8((float *)(state + 0x88), *(float *)(state + 0x8C), 8.726647356525064e-4f);
        if ((*(float *)(state + 0x88) >= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) >= 0.0f) ||
            (*(float *)(state + 0x88) <= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) <= 0.0f)) {
            *(s32 *)(state + 0x90) = func_002A7820(0x1E, 0x5A);
            if (0.0f < *(float *)(state + 0x8C))
                *(float *)(state + 0x8C) =
                    -(func_002A7878(D_L02_001B1040[0], D_L02_001B1040[1]) * 2.908882452175021e-4f);
            else
                *(float *)(state + 0x8C) =
                    func_002A7878(D_L02_001B1040[0], D_L02_001B1040[1]) * 2.908882452175021e-4f;
        }
    } else {
        func_002AA2E8((float *)(state + 0x88), 0.0f, 8.726647356525064e-4f);
    }
    *(TI128 *)a = 0;
    a[2] = *(float *)(state + 0x88);
    *(TI128 *)b = *(TI128 *)a;
    func_002833F0(m, b);
    for (i = 0; i < *(s32 *)(state + 0x80); i++) {
        char *rec;
        s32 skip;

        s2 = (s16 *)(state + 0x40 + i * 2);
        skip = ((*(s32 *)(state + 0x84) >> i) & 1) == 0;
        if (skip)
            continue;
        rec = D_L02_001B3B00 + *s2 * 64;
        func_L02_002F2B88(rec, rec, m);
    }
}

/* func_L02_003F5710 is defined in L02_003F5430-g8.c (three $gp accesses). */

/* Maps the values 0, 1, 3, 5, 6, 7, 8, 10, 11 and 13 to 0..9 (in no regular order) and any other
   value to -1. The dispatch reads the level's own jump table (fourteen words in the level's data
   at 0x2A5520, one per value); `cases` only keeps the labels alive, and each label is named after
   the value that reaches it. */
s32 func_L02_003F9AF0(u32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&dflt, &&c3, &&dflt, &&c5, &&c6, &&c7, &&c8, &&dflt,
                              &&c10, &&c11, &&dflt, &&c13};
    if (a0 < 14)
        goto *D_L02_002A5520[a0];
    goto dflt;
c0:
    return 0;
c6:
    return 1;
c3:
    return 2;
c1:
    return 3;
c5:
    return 4;
c7:
    return 5;
c10:
    return 6;
c11:
    return 7;
c8:
    return 8;
c13:
    return 9;
dflt:
    return -1;
}

/* Maps a value below 14 to an id (0x31 to 0x3B and 0x91 to 0x93, in no regular order) and any
   other value to -1. The dispatch reads the level's own jump table (fourteen words in the level's
   data at 0x2A5560, one per value); `cases` only keeps the labels alive, and each label is named
   after the value that reaches it. */
s32 func_L02_003F9B70(s32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if ((u32)a0 < 14)
        goto *D_L02_002A5560[a0];
    goto dflt;
c0:
    return 0x31;
c2:
    return 0x32;
c3:
    return 0x33;
c1:
    return 0x34;
c4:
    return 0x35;
c5:
    return 0x36;
c6:
    return 0x37;
c7:
    return 0x38;
c9:
    return 0x39;
c10:
    return 0x3A;
c11:
    return 0x3B;
c8:
    return 0x91;
c12:
    return 0x92;
c13:
    return 0x93;
dflt:
    return -1;
}

void func_L02_003FAF28(char *a0) {
    char *s0 = a0;
    char *obj = *(char **)(s0 + 0x68);
    u16 timer = *(u16 *)(s0 + 0x96);

    if (timer <= 0xFFFE)
        *(u16 *)(s0 + 0x96) = timer + 1;
    func_00282948(obj + 0xE4);
    if (*(u8 *)(s0 + 0x20) > 1)
        func_L00_002E6EF8(D_L02_004004D8, s0);
    func_L00_0030CF60();
}

void func_L02_003FAF90(char *a0) {
    char *s0 = *(char **)(a0 + 0x68);
    u32 *p;
    s32 i;
    *(s16 *)(s0 + 0x120) = -1;
    *(s16 *)(s0 + 0x122) = -1;
    *(u16 *)(s0 + 0x118) = 0;
    p = (u32 *)(s0 + 0xBC);
    for (i = 5; i >= 0; i--) {
        *p = 0;
        p--;
    }
    *(u32 *)(s0 + 0xD8) = 0;
    *(u32 *)(s0 + 0xD0) = 0;
    func_002A7750(a0, 1, -1);
    *(u32 *)(s0 + 0xC0) = 0;
}

INCLUDE_ASM("asm/levels", func_L02_003FB000);

/* func_L02_003FB120 is matched in L02_003FB120-g8.c (built with -g). */

extern s32 func_L02_003FB6C0(char *, char *);

/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; records A0 as that entity's owner and returns func_L02_003FB6C0's result for it.
   The walk is func_L02_003FB5A0's `do { ... } while ((s16)*p++ >= 0);`: a `for (;;)` with the
   test and the increment in the body makes this cc1 annul the loop-bottom slot (`bgezl`). */
s32 func_L02_003FB4D8(char *a0, s32 a1, char *a2) {
    char *state = *(char **)(a0 + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    u16 *p;
    char *rec;

    if (index == 0xFF)
        return 0;
    entry = D_L02_001FC060[index];
    if (entry == 0)
        return 0;
    p = (u16 *)entry;
    do {
        rec = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (rec != 0 && *(u8 *)(rec + 0x20) != 0xFE && *(u8 *)(rec + 0x20) != 0xFD
            && *(s16 *)(rec + 0xAA) == a1 && *(u8 *)(rec + 0x20) == 1) {
            *(char **)(rec + 0xB8) = a0;
            return func_L02_003FB6C0(a0, rec);
        }
    } while ((s16)*p++ >= 0);
    return 0;
}

extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern void func_L02_003D47B0(char *, s32);
extern void func_L02_003DB310(char *, s32);

/* Looks through the entity list the object's state names for one of kind A1 whose byte at +0x20
   is 1; for the kinds 0x9F8 and 0xA44 it records A0 as that entity's owner, runs the kind's start
   function, counts it in the state and returns it. */
char *func_L02_003FB5A0(char *a0, s32 a1, s32 a2) {
    char *state = *(char **)(a0 + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    u16 *p;
    char *rec;

    if (index == 0xFF)
        return 0;
    entry = D_L02_001FC060[index];
    if (entry == 0)
        return 0;
    p = (u16 *)entry;
    do {
        rec = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (rec != 0 && *(u8 *)(rec + 0x20) != 0xFE && *(u8 *)(rec + 0x20) != 0xFD
            && *(s16 *)(rec + 0xAA) == a1 && *(u8 *)(rec + 0x20) == 1) {
            *(char **)(rec + 0xB8) = a0;
            switch (a1) {
            case 0x9F8:
                func_L02_003D47B0(rec, *(s16 *)(state + 0x120) == 0xC);
                *(s32 *)(state + 0xA0) += 1;
                return rec;
            case 0xA44:
                func_L02_003DB310(rec, a2);
                *(s32 *)(state + 0xA4) += 1;
                return rec;
            }
        }
    } while ((s16)*p++ >= 0);
    return 0;
}

/* Counts the kind of A1 in the state and sets its scale to one. */
s32 func_L02_003FB6C0(char *a0, char *a1) {
    char *s0 = *(char **)(a0 + 0x68);
    char **list = (char **)(s0 + 0xA8);
    char **slot = list + *(s32 *)(s0 + 0xD8);
    char *e = *slot;

    if (e != 0) {
        if (func_L02_003D77B8(e) != 0) {
            char **cur = list + *(s32 *)(s0 + 0xD8);

            func_L02_003D7868(*cur, a1);
            switch (*(s16 *)(a1 + 0xAA)) {
            case 0x9CA:
                *(s32 *)(s0 + 0x90) += 1;
                *(float *)(*(char **)(a1 + 0x68) + 0x20) = 1.0f;
                break;
            case 0xB22:
                *(s32 *)(s0 + 0x94) += 1;
                *(float *)(*(char **)(a1 + 0x68) + 0x20) = 1.0f;
                break;
            case 0xC3B:
                *(s32 *)(s0 + 0x98) += 1;
                *(float *)(*(char **)(a1 + 0x68) + 0x20) = 1.0f;
                break;
            case 0xC3E:
                *(s32 *)(s0 + 0x9C) += 1;
                *(float *)(*(char **)(a1 + 0x68) + 0x20) = 1.0f;
                break;
            default:
                return 1;
            }
            return 1;
        }
    }
    return 0;
}

/* func_L02_003FB7E0 is defined in L02_003F5430-g8.c ($gp accesses). */

void func_L02_003FBA58(char *a0) {
    char **p;
    char *s1 = *(char **)(a0 + 0x68);
    s32 i;
    for (i = 0; i <= *(s32 *)(s1 + 0xD8); i++) {
        p = (char **)(s1 + 0xA8 + i * 4);
        if (*p != 0) {
            if (func_003D77F8(*p) != 0)
                func_003D78A8(*p);
        }
    }
}

/* True when every occupied slot of the list at +0xA8 has content; then the list is cleared. */
void func_L02_003FBAD0(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    char **p = (char **)(s1 + 0xA8);
    s32 i;
    s32 j;
    s32 ok = 1;

    for (i = 0; i <= *(s32 *)(s1 + 0xD8); i++) {
        if (*p != 0) {
            if (func_L02_003D7830(*p) == 0) {
                ok = 0;
                break;
            }
        }
        p++;
    }
    if (ok) {
        for (j = 0; j <= *(s32 *)(s1 + 0xD8); j++)
            *(s32 *)(s1 + 0xA8 + j * 4) = 0;
        *(s32 *)(s1 + 0xD8) = 0;
    }
}

extern char *D_L02_001B359C __attribute__((sda));
extern u32 D_L02_001FC060[];
extern void func_L02_003D2390(char *);
extern void func_L02_003D4900(char *);
extern void func_L02_003DB6D8(char *);
extern void func_L02_003F18E8(char *);
extern void func_L02_0040B980(char *);
extern void func_L02_0040D180(char *);

/* Walks the 16-bit stream the object's table entry points at and calls the handler of the
   entity type each word names; a negative word ends the stream. */
void func_L02_003FBB90(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    short *p;
    char *rec;
    s16 type;

    if (index == 0xFF)
        return;
    entry = D_L02_001FC060[index];
    if (entry == 0)
        return;
    p = (short *)entry;
    do {
        rec = D_L02_001B359C + ((*(u16 *)p & 0x7FFF) << 8);
        type = *(s16 *)(rec + 0xAA);
        switch (type) {
        case 0x9CA:
            func_L02_003D2390(rec);
            break;
        case 0xB22:
            func_L02_003F18E8(rec);
            break;
        case 0xC3B:
            func_L02_0040B980(rec);
            break;
        case 0xC3E:
            func_L02_0040D180(rec);
            break;
        case 0x9F8:
            func_L02_003D4900(rec);
            break;
        case 0xA44:
            func_L02_003DB6D8(rec);
            break;
        }
    } while (*p++ >= 0);
}

extern s32 D_L02_001B35B8[] __attribute__((sda));
extern void func_L02_003FC1B0(char *, s32);

/* The test of the entity walks below: the group word at +0x40 is read again for every condition,
   as the handlers may change it. */
#define GROUP_LEFT(p) \
    ((*(s32 *)(state + 0x40) & 0xFF) != 0xFF && *(s32 *)(state + 0x40) <= D_L02_001B35B8[0] && \
     p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[*(s32 *)(state + 0x40)]))

/* Clears the flag (+0x2F6 of a 0x9CA entity's block, +0x4EA of a 0xB22 one) of every entity of
   the group that has it set and passes the entity's kind to func_L02_003FC1B0; then, twice, picks
   among the group's entities of those two kinds that are not 0xFE/0xFD, have a state byte (+0x20)
   of 4 or more and the flag not set, the one nearest to D_00189EA0, sets its flag and takes one
   off its kind's count (+0x50, +0x54). */
void func_L02_003FBCF8(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    char *best;
    float bestd;
    float d;
    s32 i;
    u16 kind;
    s16 flag;

    for (p = (u16 *)D_L02_001FC060[*(s32 *)(state + 0x40)]; GROUP_LEFT(p); p++) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        switch (*(s16 *)(e + 0xAA)) {
        case 0x9CA: {
            char *q = *(char **)(e + 0x68);

            if (*(s16 *)(q + 0x2F6) == 1) {
                *(s16 *)(q + 0x2F6) = 0;
                func_L02_003FC1B0(a0, *(s16 *)(e + 0xAA));
            }
            break;
        }
        case 0xB22: {
            char *q = *(char **)(e + 0x68);

            if (*(s16 *)(q + 0x4EA) == 1) {
                *(s16 *)(q + 0x4EA) = 0;
                func_L02_003FC1B0(a0, *(s16 *)(e + 0xAA));
            }
            break;
        }
        }
    }
    for (i = 0; i < 2; i++) {
        best = 0;
        bestd = 10000.0f;
        for (p = (u16 *)D_L02_001FC060[*(s32 *)(state + 0x40)]; GROUP_LEFT(p); p++) {
            e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            flag = -1;
            kind = *(u16 *)(e + 0xAA);
            switch (*(s16 *)(e + 0xAA)) {
            case 0x9CA:
                flag = *(s16 *)(*(char **)(e + 0x68) + 0x2F6);
                break;
            case 0xB22:
                flag = *(s16 *)(*(char **)(e + 0x68) + 0x4EA);
                break;
            }
            if (e != 0 && *(u8 *)(e + 0x20) != 0xFE && *(u8 *)(e + 0x20) != 0xFD &&
                ((s16)kind == 0x9CA || (s16)kind == 0xB22) && flag != 1 &&
                *(u8 *)(e + 0x20) >= 4) {
                if (best == 0) {
                    best = e;
                    bestd = func_00282E80(best + 0x10, D_00189EA0);
                } else {
                    d = func_00282E80(e + 0x10, D_00189EA0);
                    if (d < bestd) {
                        best = e;
                        bestd = d;
                    }
                }
            }
        }
        if (best != 0) {
            switch (*(s16 *)(best + 0xAA)) {
            case 0x9CA:
                *(s16 *)(*(char **)(best + 0x68) + 0x2F6) = 1;
                *(s32 *)(state + 0x50) -= 1;
                break;
            case 0xB22:
                *(s16 *)(*(char **)(best + 0x68) + 0x4EA) = 1;
                *(s32 *)(state + 0x54) -= 1;
                break;
            }
        }
    }
}

void func_L02_003FC020(char *a0, char *a1) {
    char *a3 = *(char **)(a0 + 0x68);
    char *g = D_L02_001BA3C0;
    s16 t;
    if (*(u32 *)(g + 0x284) == *(u32 *)(a3 + 0xD0))
        *(u32 *)(g + 0x284) = 0;
    if (*(u32 *)(g + 0x284) == 0) {
        *(u32 *)(g + 0x284) = (u32)a1;
        *(u32 *)(g + 0x288) = 0;
    }
    *(u32 *)(a3 + 0xD0) = (u32)a1;
    t = *(s16 *)(a1 + 0xAA);
    if (t == 0x9F8)
        func_L02_00400650(a0, 0xF);
    else if (t == 0xA44)
        func_L02_00400650(a0, 0x15);
}

char *func_L02_003FC098(char *a0) {
    char *a1 = *(char **)(a0 + 0x68);
    return D_L02_001B368C + *(u32 *)(a1 + 0x88) * 128 + 0x30;
}

s32 func_L02_003FC0B8(char *a0) {
    char *v1 = *(char **)(a0 + 0x68);
    return *(s32 *)(v1 + 0x84);
}

/* Counts down one of the four timers named by a1; true when it was still running. */
s32 func_L02_003FC0D0(char *a0, s32 a1) {
    char *p = *(char **)(a0 + 0x68);

    switch (a1) {
    case 0x9CA:
        if (*(s32 *)(p + 0x50) > 0) {
            *(s32 *)(p + 0x50) -= 1;
            return 1;
        }
        break;
    case 0xB22:
        if (*(s32 *)(p + 0x54) > 0) {
            *(s32 *)(p + 0x54) -= 1;
            return 1;
        }
        break;
    case 0xC3B:
        if (*(s32 *)(p + 0x58) > 0) {
            *(s32 *)(p + 0x58) -= 1;
            return 1;
        }
        break;
    case 0xC3E:
        if (*(s32 *)(p + 0x5C) > 0) {
            *(s32 *)(p + 0x5C) -= 1;
            return 1;
        }
        break;
    case 0x9F8:
    case 0xA44:
        return 0;
    default:
        break;
    }
    return 0;
}

void func_L02_003FC1B0(char *a0, s32 a1) {
    s32 *v1 = *(s32 **)(a0 + 0x68);
    s32 result = 0xA44;
    if (a1 == result)
        goto low_return;
    if (a1 >= 0xA45)
        goto high;
    result = 0x9CA;
    if (a1 == result)
        goto inc50;
low_return:
    return;
high:
    result = 0xC3B;
    if (a1 == result)
        goto inc58;
    if (a1 >= 0xC3C)
        goto highest;
    result = 0xB22;
    if (a1 == result)
        goto inc54;
    return;
highest:
    result = 0xC3E;
    if (a1 == result)
        goto inc5c;
    return;
inc50:
    ++v1[0x14];
    return;
inc54:
    ++v1[0x15];
    return;
inc58:
    ++v1[0x16];
    return;
inc5c:
    ++v1[0x17];
    return;
}

extern char *D_L02_001B359C __attribute__((section(".sdata")));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s16 func_L02_004024A0(char *);
extern void func_L02_004024B0(char *);
extern void func_L02_004024C0(char *);

#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = (u16 *)D_L02_001FC060[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L02_001B35B8[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(off)]); \
         p++)

/* Counts the entities of the object's group (state word 0x48) for which func_L02_004024A0 holds, then
   sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count equals A1. */
void func_L02_003FC268(char *a0, s32 a1) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    s32 n = 0;

    FOR_EACH_ID(p, 0x48) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (func_L02_004024A0(e))
            n++;
    }
    if (n < a1) {
        FOR_EACH_ID(p, 0x48) {
            e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (!func_L02_004024A0(e)) {
                func_L02_004024B0(e);
                n++;
                if (n >= a1)
                    break;
            }
        }
    } else if (n > a1) {
        FOR_EACH_ID(p, 0x48) {
            e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (func_L02_004024A0(e)) {
                func_L02_004024C0(e);
                n--;
                if (n <= a1)
                    break;
            }
        }
    }
}

extern s32 func_L02_003D7300(char *);
extern void func_L02_003D7310(char *);
extern void func_L02_003D7320(char *);

/* Counts the entities of the object's group (state word 0x4C) for which func_L02_003D7300 holds, then
   sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count equals A1. */
void func_L02_003FC518(char *a0, s32 a1) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    s32 n = 0;

    FOR_EACH_ID(p, 0x4C) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (func_L02_003D7300(e))
            n++;
    }
    if (n < a1) {
        FOR_EACH_ID(p, 0x4C) {
            e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (!func_L02_003D7300(e)) {
                func_L02_003D7310(e);
                n++;
                if (n >= a1)
                    break;
            }
        }
    } else if (n > a1) {
        FOR_EACH_ID(p, 0x4C) {
            e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (func_L02_003D7300(e)) {
                func_L02_003D7320(e);
                n--;
                if (n <= a1)
                    break;
            }
        }
    }
}

extern void func_L02_003D2488(char *, int, int);
extern void func_L02_003FC248(char *, int, int);
extern int func_L00_003206B8(void *, int);
extern void func_L00_002B30E8(void);

/* Walks the entities of the group the object names (the group word is re-read for every
   test: the handlers may change it).  Each live, unflagged one that passes the screen
   against the two bounds is handed to the handler of its type.  Afterwards the follow-up is
   called unless the resident record passes the screen. */
void func_L02_003FC7C8(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    char *e;
    u8 c;

    FOR_EACH_ID(p, 0x40) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        c = *(u8 *)(e + 0x20);
        if (c == 0xFE)
            continue;
        if (c == 0xFD)
            continue;
        if (c < 3)
            continue;
        if (*(u16 *)(e + 0x34) & 2)
            continue;
        if (func_L00_003206B8(e + 0x10, *(s32 *)(state + 0x80)) == 0 &&
            func_L00_003206B8(e + 0x10, *(s32 *)(state + 0x7C)) != 0)
            continue;
        switch (*(s16 *)(e + 0xAA)) {
        case 0x9CA:
            func_L02_003D2488(e, 0, 0);
            break;
        case 0xB22:
            func_L02_003FC248(e, 0, -1);
            func_L02_003F18E8(e);
            break;
        case 0xC3B:
            func_L02_003FC248(e, 0, -1);
            func_L02_0040B980(e);
            break;
        case 0xC3E:
            func_L02_003FC248(e, 0, -1);
            func_L02_0040D180(e);
            break;
        }
    }
    if (func_L00_003206B8(D_00189EA0, *(s32 *)(state + 0x7C)) == 0)
        func_L00_002B30E8();
}

/* func_L02_003FC9C0 is matched in L02_003F5430-g8.c. */

extern int func_002A77E0(int);
extern void func_L00_002D7140(char *);
extern void func_L00_00303530(int, int);
extern void func_00282C88(void *);
extern int func_L02_003F9B70(int);
extern void func_L00_002B9D60(char *, float *, int, int);
extern void func_002DF3F8(void *, void *);
extern void func_L01_00323310(int, int);
extern int D_L02_001CAA80;
extern u8 D_001395B8[];
extern char *D_L02_001B369C __attribute__((sda));
extern int D_L02_001AA1B0 __attribute__((sda));

/* Starts the actor: calls func_L02_00400650 with 0x25 plus a random pick below 2, sets state 1,
   releases the object held at +0xC0 and, by a per-slot flag, hands a vector whose third float
   is -1.59 or 2.16, with the matching 128-byte record, to func_L00_002B9D60; ends by setting
   D_L02_001AA1B0 to -1. */
void func_L02_003FCA80(char *a0) {
    char *s1 = *(char **)(a0 + 0x68);
    float v[4];

    func_L02_00400650(a0, func_002A77E0(2) + 0x25);
    func_002A7750(a0, 1, -1);
    if (*(char **)(s1 + 0xC0) != 0) {
        func_L00_002D7140(*(char **)(s1 + 0xC0));
        *(s32 *)(s1 + 0xC0) = 0;
    }
    if (D_L02_001CAA80 != 0)
        func_L00_00303530(0, *(s32 *)(s1 + 0x224));
    func_00282C88(v);
    if (D_001395B8[func_L02_003F9B70(0)] != 0) {
        v[2] = -1.59f;
        func_L00_002B9D60(D_L02_001B369C + *(s32 *)(s1 + 0x74) * 128 + 0x30, v, 0, 1);
    } else {
        v[2] = 2.16f;
        func_L00_002B9D60(D_L02_001B368C + *(s32 *)(s1 + 0x78) * 128 + 0x30, v, 0, 1);
    }
    func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
    func_L02_003FBB90(a0);
    func_L02_003FC268(a0, 0);
    func_L02_003FC518(a0, 0);
    func_L01_00323310(*(s32 *)(s1 + 0x224), *(s32 *)(s1 + 0x22C));
    D_L02_001AA1B0 = -1;
}

/* func_L02_003FCBF0 is defined in L02_003F5430-g8.c (this unit has no $gp access for it). */

/* func_L02_003FCCA0 is defined in L02_003F5430-g8.c (D_001A79F8 is a $gp access in a delay slot). */

s32 func_L02_003FD000(char *a0) {
    char buf[16];
    s32 r = 0;
    func_0029FCC0(a0, 0, buf);
    if (*(u8 *)(a0 + 0x31) != 0) {
        if (func_00282E80(buf, D_00189EA0) > 25.0f)
            r = 1;
    }
    return r;
}

extern void func_L02_003A6F78(char *);

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0xC8 and
   0xC4); an empty group, or a group word of 0xFF, ends the function. */
void func_L02_003FD070(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *p;
    u16 *q;
    char *e;

    if (GROUP(0xC8) == 0xFF)
        return;
    q = (u16 *)D_L02_001FC060[GROUP(0xC8)];
    if (q == 0)
        return;
    for (p = q; (GROUP(0xC8) & 0xFF) != 0xFF && GROUP(0xC8) <= D_L02_001B35B8[0] && p != 0 &&
                ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(0xC8)]);
         p++) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_L02_003A6F78(e);
    }
    if (GROUP(0xC4) == 0xFF)
        return;
    q = (u16 *)D_L02_001FC060[GROUP(0xC4)];
    if (q == 0)
        return;
    for (p = q; (GROUP(0xC4) & 0xFF) != 0xFF && GROUP(0xC4) <= D_L02_001B35B8[0] && p != 0 &&
                ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L02_001FC060[GROUP(0xC4)]);
         p++) {
        e = D_L02_001B359C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_L02_003A6F78(e);
    }
}

/* func_L02_003FD228 is defined in L02_003F5430-g8.c (it reads its globals through $gp). */

/* func_L02_003FD7C8 is defined in L02_003F5430-g8.c ($gp accesses). */


INCLUDE_ASM("asm/levels", func_L02_003FDDE8);

/* Maps a value below 14 to an id (0x2F48 to 0x2F51, 0x2F6E and 0x3240 to 0x3242, in no regular
   order); any other value gives 0x2F48. The dispatch reads the level's own jump table (fourteen
   words in the level's data at 0x2A5600, one per value); `cases` only keeps the labels alive, and
   each label is named after the value that reaches it. */
s32 func_L02_003FE1B0(u32 a0) {
    static void *cases[14] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7, &&c8, &&c9, &&c10,
                              &&c11, &&c12, &&c13};
    if (a0 < 14)
        goto *D_L02_002A5600[a0];
    goto dflt;
c0:
    return 0x2F48;
c2:
    return 0x2F49;
c4:
    return 0x2F4A;
c9:
    return 0x2F4B;
c6:
    return 0x2F4C;
c3:
    return 0x2F4D;
c1:
    return 0x2F4E;
c5:
    return 0x2F4F;
c7:
    return 0x2F6E;
c10:
    return 0x2F50;
c11:
    return 0x2F51;
c8:
    return 0x3240;
c12:
    return 0x3241;
c13:
    return 0x3242;
dflt:
    return 0x2F48;
}

INCLUDE_ASM("asm/levels", func_L02_003FE250);

INCLUDE_ASM("asm/levels", func_L02_003FE8B8);

INCLUDE_ASM("asm/levels", func_L02_003FF6E8);

/* func_L02_003FF9A0 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_003FFDB0 is defined in L02_003FFDB0-g8.c ($gp accesses). */

/* func_L02_004002E0 is matched in L02_004002E0-g8.c (built with -g). */

/* func_L02_004004D0 is matched in its own unit, src/levels/shared/L02_004004D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Timer for one of the thirty-nine messages, refused while one is running. */
s32 func_L02_00400650(char *a0, s32 a1) {
    char *p = *(char **)(a0 + 0x68);
    s32 v;

    if ((u32)a1 >= 0x27)
        return 0;
    if (a1 < 0x14) {
        s32 i = a1;
        char *q = p + 0x130;
        v = *(s32 *)(q + i * 4);
    } else {
        s32 i = a1 - 0x14;
        char *q = p + 0x180;
        v = *(s32 *)(q + i * 4);
    }
    {
        char *g = D_001A63A8;

        if (*(s32 *)(g + 0x68) != 0)
            goto fail;
        if (*(s32 *)(g + 0x24) != -1)
            goto fail;
        *(s32 *)(g + 0x28) = 0;
        *(s32 *)(g + 0x24) = (v & 0x3FFF) + 0x7D0;
    }
    {
        char *q = p + 0x1D0;
        *(u16 *)(q + a1 * 2) = 1;
    }
    return 1;
fail:
    return 0;
}

/* func_L02_00400720 is defined in L02_003F5430-g8.c ($gp accesses). */

/* func_L02_00400948 is defined in L02_003F5430-g8.c ($gp accesses). */

extern char *D_L02_001B35A8 __attribute__((sda));
extern void func_003320F0(char *);
extern void func_00333048(char *);
extern void func_L02_00414D48(char *);
extern void func_L02_003F0628(char *);
extern void func_L02_00392C70(char *);
extern void func_L02_003948D0(char *);
extern void func_L02_003AA650(char *);
extern void func_L02_003DED08(char *);
extern void func_0029F338(char *);

/* Walks the list of objects at D_L02_001B35A8 (linked through +0x28) and hands each one to the
   handler of its kind, the half-word at +0xAA. */
void func_L02_00400B10(void) {
    char *e;

    for (e = D_L02_001B35A8; e != 0; e = *(char **)(e + 0x28)) {
        switch (*(s16 *)(e + 0xAA)) {
        case 0xE7D:
            func_003320F0(e);
            break;
        case 0xEB0:
            func_00333048(e);
            break;
        case 0xCB2:
            func_L02_00414D48(e);
            break;
        case 0xB02:
            func_L02_003F0628(e);
            break;
        case 0x1366:
            func_L02_00392C70(e);
            break;
        case 0x1367:
            func_L02_003948D0(e);
            break;
        case 0x326:
            func_L02_003AA650(e);
            break;
        case 0xA5C:
        case 0x1192:
            func_L02_003DED08(e);
            break;
        case 0xAE0:
        case 0xAE1:
        case 0xAE2:
        case 0xAEC:
        case 0xB06:
        case 0xB09:
        case 0xCC0:
        case 0xCC1:
        case 0xCC2:
        case 0xCC3:
        case 0xCC4:
        case 0xCC5:
        case 0xCC6:
        case 0xCC7:
        case 0xCC8:
        case 0xCC9:
        case 0xCDB:
            func_0029F338(e);
            break;
        }
    }
}

/* True when the field at +0xAA is 0xB59, the global at D_0017A80 is 1 and bit 3 of the
   byte at +0x20 is clear. */
s32 func_L02_00400CC8(char *a0) {
    s32 r = 0;
    if (*(s16 *)(a0 + 0xAA) == 0xB59 && D_0017A80 == 1)
        r = (*(u8 *)(a0 + 0x20) ^ 8) ? 0 : D_0017A80;
    return r;
}



/* func_L02_00401BF8 is matched in L02_00401BF8.c (built with -frac2-qcopy -frac2-qcopy-barrier). */

/* func_L02_00401D38 is defined in L02_003F5430-g8.c ($gp accesses). */

