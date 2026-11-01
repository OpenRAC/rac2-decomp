#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
typedef struct { unsigned char pad[0x70]; long f70, f78, f80, f88; } QuadPacket;
typedef union {
    QuadPacket packet;
    struct { Vector corners[4]; unsigned int colours[4]; float uv[8]; } geometry;
} RenderQuad;

extern void func_00282CC0(char *, char *, char *);

extern void func_002A8C00(char *, int, int, void *, float);

extern int func_002761F8(void *, void *, int, int, void *);

extern int func_00282948(void *);

extern void func_002E5DA0(int, int, void *, int);

extern void func_L00_002E6EF8(void *, int);

extern void func_L20_0039C5D0(char *);

extern void func_L20_0039C8C8(char *, int, int);

extern char D_L20_001C0420[];

extern char *D_L20_001FBB20[];

extern char *D_L20_001B2F9C __attribute__((sda));

extern float D_L20_0023E670[];

/* func_L20_0039C448 is defined in L20_0039C448-qcopy.c (its copy needs the grouped-copy profile). */

extern char *func_0029EFD0(int);

/* func_L20_0039C5D0 is defined in L20_0039C5D0.c (grouped-copy profile). */

/* func_L20_0039C8C8 is defined in L20_0039C8C8.c. */


/* func_L20_0039CF58 is defined in L20_0039CF58.c. */

/* func_L20_0039D340 is defined in L20_0039D340-g8.c (it reads data through $gp). */


extern int D_L20_001B2AC8 __attribute__((sda));

extern int func_L20_0039DF18(char *, int);

extern void func_L20_0039D880(char *);

extern void func_L20_0039D680(char *);

extern float func_00283BE0(float, float);

extern float func_002AAA00(char *, char *, float, float, float, float, int);

void func_L20_0039D7B0(char *arg0) {
    char *s0 = arg0;
    char *s1;
    f32 c;
    f32 r;
    u32 v1;
    u16 v2;

    s1 = *(char **)(s0 + 0x68);
    func_L20_0039DF18(s0, 0);
    func_L20_0039D880(s0);
    if ((D_L20_001B2AC8 & 7) == (((s32)s0 >> 8) & 7)) {
        func_L20_0039D680(s0);
    }
    c = 0.009696274995803833f;
    r = func_00283BE0(*(f32 *)(s1 + 0x284), *(f32 *)(s0 + 0xF8));
    {
        f32 c2 = c;
        func_002AAA00(s1 + 0x288, s1 + 0x28C, r, c, c2, 0.58177649974823f, 0);
    }
    *(f32 *)(s1 + 0x284) = *(f32 *)(s0 + 0xF8);
    v2 = *(u16 *)(s0 + 0x96);
    if ((u32)v2 <= 0xFFFEu) {
        *(u16 *)(s0 + 0x96) = v2 + 1;
    }
}

/* func_L20_0039D880 is defined in L20_0039D880.c. */

extern void func_002A7470(void *, int, int, int);

void func_L20_0039DB50(char *arg0, int arg1, int arg2, float f12) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x43) != arg1) {
        func_002A7470(arg0, arg1, (int)f12, arg2);
    }
    func_002A7470(*(char **)(state + 0x254), arg1, (int)f12, arg2);
}

/* func_L20_0039DBC8 is defined in L20_0039DBC8-g8.c (it needs the -G8 profile). */

extern void func_0029F338(int);

extern void func_002A7750(char *, int, int);

void func_L20_0039DE88(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char **p;
    int i;

    func_002A7750(arg0, 6, 2);
    *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
    *(int *)(arg0 + 0x98) = 0;
    if (*(int *)(state + 0x254) != 0) {
        func_0029F338(*(int *)(state + 0x254));
        *(int *)(state + 0x254) = 0;
    }
    p = (char **)(state + 0x258);
    for (i = 1; i >= 0; i--) {
        if (*p != 0) {
            func_0029F338(*p);
            *p = 0;
        }
        p++;
    }
}

extern void *func_00325040(int);
extern void func_0033E708(char *, char *);
extern char *func_00338198(char *);
extern void func_00326528(char *, int, char *);
extern f32 func_00303270(f32, f32);
extern void func_00327AD0(void *);
extern void func_003381E0(void *, void *);
extern void func_00338830(void *, u32, int, int);
extern void func_0032F2D0(void *, int, int, int);

int func_L20_0039DF18(char *arg0, int arg1) {
    char *s0;
    char *s1;
    char *s2 = arg0;
    char *s3;
    char *s4;
    int cnt;
    char *p2;
    int six;
    int v;

    s3 = *(char **)(s2 + 0x68);
    if (arg1 != 0) {
        if (*(char **)(s3 + 0x254) == 0) {
            s0 = (char *)func_00325040(0xD0E);
            if (s0 == 0) {
                v = 0;
                goto out;
            }
            func_0033E708(s0, s2);
            *(u16 *)(s0 + 0x7C) = 0x3FF;
            *(char **)(s3 + 0x254) = s0;
        }
        s4 = 0;
        s1 = s3 + 0x258;
        while ((int)s4 < 2) {
            if (*(u32 *)s1 == 0) {
                s0 = (char *)func_00325040(0xD66);
                if (s0 == 0) {
                    v = 0;
                    goto out;
                }
                func_0033E708(s0, s2);
                *(u32 *)s1 = (u32)s0;
            }
            s4++;
            s1 += 4;
        }
    }
    s4 = (char *)func_00338198(s2);
    if (*(char **)(s3 + 0x254) != 0) {
        func_00326528(s2, 0, *(char **)(s3 + 0x254) + 0x10);
        *(f32 *)(*(char **)(s3 + 0x254) + 0xF8) = func_00303270(*(f32 *)(s2 + 0xF8), *(f32 *)(s3 + 0x288));
        func_00327AD0(*(char **)(s3 + 0x254));
        func_003381E0(*(char **)(s3 + 0x254), s4);
        if (*(u8 *)(*(char **)(s3 + 0x254) + 0x43) != *(u8 *)(s2 + 0x43)) {
            func_0032F2D0(*(char **)(s3 + 0x254), *(u8 *)(s2 + 0x43), *(u8 *)(s2 + 0x41), 0xA);
        }
    }
    cnt = 0;
    six = 6;
    p2 = s3 + 0x258;
    while (cnt < 2) {
        if (*(u32 *)p2 != 0) {
            func_00338830(*(char **)(s3 + 0x254), *(u32 *)p2, cnt, (cnt == 1) ? six : 0);
            func_003381E0(*(u32 *)p2, s4);
        }
        cnt++;
        p2 += 4;
    }
    v = 1;
out:
    return v;
}

extern int D_L20_001B2FB8;

/* func_L20_0039E0A0 is defined in L20_0039E0A0-g8.c (it needs the -G8 profile). */

extern void func_002B3BA8(char *, int, float, float, int, int);

extern char *func_L20_004448A8(char *, char *);

/* func_L20_0039E158 is in L20_0039E158.c with its grouped-copy profile. */

extern f32 func_002A7878(f32, f32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CF0(void *, void *, void *);
extern f32 func_00282DF0(void *);
extern void func_00282F70(char *, char *, f32);
extern f32 func_00282E80(void *, void *);
extern char D_00189E20[];
extern float D_L20_001B9FD8;

/* func_L20_0039E1E8: picks a point state[0x260] 8 to 12 units (in xy) from a target.
 * When the target at state[0x200] is the hero's moby (D_00189E20 + 0x2290), the point
 * is placed around the hero's position (D_00189E20 + 0x80) at an angle within 45
 * degrees of D_L20_001B9FD8.  Otherwise it is the offset from the target to this
 * moby, shortened to that distance when longer, added back to the target's position.
 * state + 0x260 and arg0 + 0x10 are written at each use rather than kept in variables:
 * that is what gives retail's copy of the pointer in a register live after the if. */
void func_L20_0039E1E8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    f32 dist;
    f32 angle;
    char *hero;

    dist = func_002A7878(8.0f, 12.0f);
    hero = D_00189E20;
    if (*(char **)(state + 0x200) == *(char **)(hero + 0x2290)) {
        angle = func_002A7878(-45.0f, 45.0f);
        angle = func_00283B98(angle * 0.017453294f, D_L20_001B9FD8);
        *(f32 *)(state + 0x260) = func_00283180(angle) * dist;
        *(f32 *)(state + 0x264) = func_00283198(angle) * dist;
        *(int *)(state + 0x268) = 0;
        func_00282CC0(state + 0x260, state + 0x260, hero + 0x80);
    } else {
        func_00282CF0(state + 0x260, arg0 + 0x10, *(char **)(state + 0x200) + 0x10);
        if (dist < func_00282DF0(state + 0x260)) {
            func_00282F70(state + 0x260, state + 0x260, dist);
        }
        func_00282CC0(state + 0x260, state + 0x260, *(char **)(state + 0x200) + 0x10);
    }
    *(f32 *)(state + 0x11C) = func_00282E80(arg0 + 0x10, state + 0x260);
}


/* func_L20_0039E5F0 is defined in L20_0039C448-g8.c (it reaches a global through $gp). */
/* func_L20_0039E770 is defined in L20_0039E770.c for its grouped-copy profile. */

/* func_L20_0039E890 is defined in L20_0039C448-g8.c (it reaches a global through $gp). */


/* func_L20_0039EBB8 is defined in L20_0039EBB8-qcopy.c (it needs the grouped-copy profile with -g). */


/* func_L20_0039EEC8 is defined in L20_0039EEC8-g8-qcopy.c (it reaches data through $gp and needs the qcopy profile with -g). */

/* func_L20_0039F210 is in L20_0039F210.c with its grouped-copy scheduling profile. */

extern void func_L20_0039F268(char *);

extern void func_L20_0039F560(char *);

extern void func_L20_0039F968(char *);

void func_L20_0039F230(char *arg0) {
    func_L20_0039F268(arg0);
    func_L20_0039F560(arg0);
    func_L20_0039F968(arg0);
}

INCLUDE_ASM("asm/levels", func_L20_0039F268);

/* func_L20_0039F560 is defined in L20_0039F560-g8.c (it reaches data through $gp and needs the qcopy profile without interblock scheduling). */

INCLUDE_ASM("asm/levels", func_L20_0039F968);


/* func_L20_003AB090 is defined in L20_003AB090.c. */

/* func_L20_003AB4A8 is defined in L20_003AB090.c. */




void func_L20_003C02D0(char *arg0) {
    s32 index = *(s32 *)(*(char **)(arg0 + 0x68));
    u16 *rec = (u16 *)D_L20_001FBB20[index];

    if (rec != 0) {
        char *base = D_L20_001B2F9C;
        f32 twenty = 20.0f;
        f32 *out = D_L20_0023E670;

        do {
            u16 word = *rec;
            char *p = base + ((word & 0x7FFF) << 8);

            *out = *(f32 *)(p + 0x18);
            out++;
            *(u16 *)(p + 0x34) |= 0x41;
            *(f32 *)(p + 0x18) = *(f32 *)(p + 0x18) - twenty;
        } while (*(s16 *)rec++ >= 0);
    }
}

extern float func_00283CE0(int);

extern float func_002A7AA8(float, float, float, float, float);

void func_L20_003C0350(char *arg0) {
    char *s1 = *(char **)(arg0 + 0x68);
    u16 *s0 = (u16 *)D_L20_001FBB20[*(s32 *)s1];
    f32 *out;
    char *base;
    f32 scale;

    if (s0 == 0) {
        return;
    }
    {
        f32 v = func_00283CE0(*(s32 *)(s1 + 4)) * *(f32 *)(s1 + 8);
        scale = func_002A7AA8(-1.0f, 0.0f, 1.0f, 0.0f, 1.0f - v);
    }
    out = D_L20_0023E670;
    base = D_L20_001B2F9C;
    do {
        f32 v = *out;
        u16 w = *s0;
        char *p = base + ((w & 0x7FFF) << 8);
        f32 d = v - 20.0f;

        out++;
        *(u16 *)(p + 0x34) &= 0xFFBE;
        *(f32 *)(p + 0x18) = d + (v - d) * scale;
    } while (*(s16 *)s0++ >= 0);
}

INCLUDE_ASM("asm/levels", func_L20_003E6728);



/* func_L20_00409480 is defined in L20_00409480-g8.c (it needs the -G8 profile). */

/* func_L20_004095D0 is defined in L20_0039C448-g8.c (this unit has no $gp access for it). */

extern s32 func_L09_00329028(char *, s32);

extern f32 func_00282E80(void *, void *);

extern char *D_L20_001FEC80[];

s32 func_L20_00435178(char *arg0, s32 arg1) {
    char *s1 = arg0;
    s32 s0 = arg1;
    char *s3;
    s32 s2;
    f32 f0;

    s3 = *(char **)(s1 + 0x68);
    s2 = func_L09_00329028(s1, s0);
    if (s2 == 0) {
        if (s0 != -1) {
            f0 = func_00282E80(s1 + 0x10,
                               D_L20_001FEC80[s0] + ((*(s16 *)(s3 + 0x1CA) << 4) + 0x10));
            if (!(*(f32 *)(s3 + 0x134) > f0)) {
            } else {
                s2 = 1;
            }
        }
    }
    return s2;
}


/* func_L20_004395B0 is in L20_0039C448-g8.c (it reads three floats through $gp); its
   near miss is in nonmatching/levels/func_L20_004395B0.c. */
/* func_L20_0043D470 is defined in L20_0039C448-qcopy.c (its copy needs the grouped-copy profile). */

/* func_L20_0043D4D8 is defined in L20_0043D4D8.c. */
