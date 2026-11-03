#include "common.h"

/* This file holds the bodies of L09_002F8BA0.c that address a global through
   $gp: the level's small-data area. It is compiled with -G8 (tools/build.py
   picks that up from the -g8.c suffix), which is what turns the scalar below
   into a $gp-relative load. Everything absolute stays absolute: the offsets
   from $gp are far outside the 16-bit displacement, so the compiler keeps
   emitting lui/addiu for them. */

/* The level's per-frame step coefficient, reached as 0x1EF8($gp). */
extern f32 D_L09_001B0EE8 __attribute__((sda));

extern void func_00282CF0(f32 *, const f32 *, const f32 *);
extern void func_00282D30(char *, char *, f32);
extern void func_00282CC0(char *, char *, char *);

/* Rescales the object's vector: the sub-object's pair of points is differenced
   into a 16-byte frame local, that difference is scaled by the level's step
   coefficient, and the scaled vector is written back through both points. The
   sub-object itself is left alone. */
void func_L09_003F6AB8(unsigned char *a0) {
    unsigned char *s0 = a0;
    unsigned char *p = *(unsigned char **)(s0 + 0x68);
    unsigned char *s1 = p + 0x10;
    char buf[16];
    func_00282CF0((f32 *)buf, (const f32 *)p, (const f32 *)s1);
    func_00282D30(buf, buf, D_L09_001B0EE8);
    func_00282CC0((char *)s1, (char *)s1, buf);
    func_00282CC0((char *)(s0 + 0x10), (char *)(s0 + 0x10), (char *)s1);
}

/* The pulse table's entry count, reached as 0x21E8($gp). */
extern int D_L09_001B11D8 __attribute__((sda));
extern int D_L09_002A2658[];
extern int D_L09_002A27A0[];
extern int func_00283CF0(float);

/* Advances the object's pulse timer by half a step (wrapping it to zero at 1.0) and adds its integer
   part (FloatToInt, so one step every other frame) to every live phase in the D_L09_002A27A0 table.
   A phase above 0x90 falls back by 0x80; the phase, folded back above 0x50, becomes the alpha byte of
   the matching D_L09_002A2658 colour. */
void func_L09_003FE2D8(unsigned char *a0) {
    unsigned char *state = *(unsigned char **)(a0 + 0x68);
    float *timer = (float *)(state + 0x384);
    float t = *timer + 0.5f;
    int step;
    int i;
    *timer = t;
    step = func_00283CF0(t);
    if (*timer >= 1.0f)
        *timer = 0.0f;
    for (i = 0; i < D_L09_001B11D8; i++) {
        int phase = D_L09_002A27A0[i];
        if (phase != 0) {
            phase += step;
            if (phase >= 0x91)
                phase -= 0x80;
            D_L09_002A27A0[i] = phase;
            if (phase >= 0x51)
                phase = 0xA0 - phase;
            D_L09_002A2658[i] = (D_L09_002A2658[i] & 0xFFFFFF) | (phase << 24);
        }
    }
}

/* The walk below reads the group count through $gp; the group table of id lists is absolute and
   the entity base (the level's record table, D_L09_001B285C) is the bare `lui`/`lw` pair here, a
   second name sized over 8 bytes with `sda` in this -G8 unit. */
extern int D_L09_001B2878 __attribute__((sda));

extern unsigned char *D_L09_001B285C_1[3] __attribute__((sda));

extern unsigned short *D_L09_001FB560[];

/* Flags the peers of the object: sets the byte at +0x440 of the private state of every entity of
   the object's group whose own word at +0x310 equals the object's. Nothing happens when the
   object's group byte (+0x21) or the word at +0x310 of its state is 0xFF. The state pointer is
   loaded ahead of the first test, as retail does. */
void func_L09_003FE978(unsigned char *a0) {
    unsigned char *state;
    unsigned short *p;
    unsigned char *e;
    unsigned char *s;

    state = *(unsigned char **)(a0 + 0x68);
    if (a0[0x21] == 0xFF)
        return;
    if (*(int *)(state + 0x310) == 0xFF)
        return;
    for (p = D_L09_001FB560[a0[0x21]];
         a0[0x21] != 0xFF && a0[0x21] <= D_L09_001B2878 && p != 0 &&
         ((p != 0 && (short)p[-1] >= 0) || p == D_L09_001FB560[a0[0x21]]);
         p++) {
        e = D_L09_001B285C_1[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        s = *(unsigned char **)(e + 0x68);
        if (s != 0) {
            if (*(int *)(s + 0x310) == *(int *)(state + 0x310))
                s[0x440] = 1;
        }
    }
}

/* The level's other per-frame coefficient, reached as 0x1F14($gp). */
extern f32 D_L09_001B0F04 __attribute__((sda));

extern void func_00283698(f32 *, f32 *);
extern void func_002830C0(f32 *, f32 *, f32 *);
extern void func_00283098(f32 *, f32 *, f32 *);
extern f32 func_00282C48(f32);

/* Turns the object's pair of points into a vector, takes the angle of the
   result against the object's own angle and adds the scaled difference to it.
   The frame holds five vectors: the two the body uses and three the retail
   frame leaves unused, which its 0x90 frame size records. */
void func_L09_003F69A0(unsigned char *a0, f32 f) {
    unsigned char *s2 = a0;
    unsigned char *s1 = *(unsigned char **)(s2 + 0x68);
    f32 v[4];
    f32 w[4];
    f32 x[4];
    f32 y[4];
    f32 z[4];
    func_00282CF0(v, (f32 *)(s2 + 0x10), (f32 *)(*(int *)(s1 + 0x20) + 0x10));
    func_00283698(w, (f32 *)(*(int *)(s1 + 0x20) + 0xC0));
    func_002830C0(v, v, w);
    v[1] = v[1] + (v[1] / func_00282C48(v[1])) *
        (*(f32 *)(s1 + 0x28) - func_00282C48(v[1])) * f;
    func_00283098(v, v, (f32 *)(*(int *)(s1 + 0x20) + 0xC0));
    func_00282CC0((char *)(s2 + 0x10), (char *)v, (char *)(*(int *)(s1 + 0x20) + 0x10));
    *(f32 *)(s2 + 0x18) = *(f32 *)(s2 + 0x18) +
        (*(f32 *)(*(int *)(s1 + 0x20) + 0x18) + D_L09_001B0F04 - *(f32 *)(s2 + 0x18)) * f;
}
