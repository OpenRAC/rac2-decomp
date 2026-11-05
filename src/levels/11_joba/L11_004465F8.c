#include "common.h"
#include "include_asm.h"

extern char *func_0029EFD0(int id);
extern float func_002A7878(float a, float b);
extern float func_002A7940(void);
extern void func_002C2210(void *, unsigned int, int, unsigned int, int, char *, float, float, float, int);
extern char D_L11_001A8F20[] __attribute__((sda));


extern void func_002B60B0(char *, float, float, float, float);
extern void func_002A7470(char *, int, int, int);
extern void func_002A7750(char *, int, int);
extern void func_002A05A8(char *);
extern void func_002A0488(char *, int, int, int);
extern int func_002B3380(char *, char *, char *);
extern void func_L11_003973F8(char *, int, float, float);

extern void func_002A04B8(char *, int *, int *, int *);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_32C9E0();
extern void func_32C700();
extern void func_324560(char *a0);
extern void func_L11_00441978(s32 a0, int a1);
extern void func_323688(char *a0, char *a1);
extern void func_00282A60(char *a0, int a1, int a2);
typedef int TI128 __attribute__((mode(TI)));
extern void func_L11_00449330(char *self, TI128 *pos);
extern char *func_3224B0(int a0);
extern void func_324F00(char *a0);
extern void func_3362A8(char *a0, s32 a1, int a2, int a3);
extern void func_300180(void *a0);
extern void func_L00_003D7250(char *a0, char *a1, float a2, int a3, int a4, int a5);
extern void func_338398(char *a0, char *a1, float a2, int a3, int a4);
extern void func_32E480(char *a0, char *a1, float f12, float f13, float f14,
                        int a2, int a3, int a4, int a5);
extern void func_2FD7E8(void *a0, int a1, void *a2, void *a3, int a4, int a5,
                        int a6, int a7, float f12);
extern void func_32EB98(void *a0, void *a1);
extern s32 func_441868(s32 a0, s32 a1);
extern s32 func_33C800(char *a0, s32 a1, s32 a2, s32 a3, float f12, float f13);


INCLUDE_ASM("asm/levels", func_L11_004465F8);

/* func_L11_00446C78 is defined in L11_00446C78-g16.c. */

/* func_L11_00446EB8 is defined in L11_004465F8-loop-g8.c. */


/* func_L11_004471A8 is defined in L11_004465F8-g8.c. */


/* func_L11_004475A0 is defined in L11_004475A0-g8.c. */

/* func_L11_004484A8 is defined in L11_004465F8-g8.c. */

void func_L11_00448848(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);

    func_300180(s1 + 0x364);
    if (*(s32 *)(s1 + 0x354) != 0) {
        func_3362A8(a0, *(s32 *)(s1 + 0x354), 2, 0);
        *(u16 *)((char *)(long)*(s32 *)(s1 + 0x354) + 0x34) &= 0xFFFD;
    }
    if (*(u16 *)(a0 + 0x96) < 0xFFFF)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    func_338398(a0, s1 + 0x230, 3.5f, 4, 1);
    func_32E480(a0, a0 + 0x10, 1.5f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

void func_L11_00448908(char *a0)
{
    if (*(s32 *)(*(char **)(a0 + 0x68) + 0x354) != 0) {
        func_32C9E0(a0, 4, 2);
        if (*(u8 *)(a0 + 0x43) != 0)
            func_32C700(a0, 0, 0, 0xA);
    } else {
        func_32C9E0(a0, 5, 2);
        if (*(u8 *)(a0 + 0x43) != 1)
            func_32C700(a0, 1, 0, 0xA);
    }
}

/* func_L11_00448AA8 is in L11_00448AA8.c. */

s32 func_L11_00448CE0(char *a0)
{
    s32 r = 0;
    u8 x;

    if (*(s32 *)(*(char **)(a0 + 0x68) + 0x354) != 0) {
        x = *(u8 *)(a0 + 0x20);
        if (x == 0xF || x == 4 || *(u8 *)(a0 + 0x95) == 4 || x == 0xE)
            r = 1;
    }
    return r;
}

/* The id lists: halfwords whose low 15 bits index the 256-byte records of D_L11_001B359C, the
   last one with its sign bit set; a walk stops when the object's group byte (+0x21) is 0xFF or
   above the limit at D_L11_001B35B8. The records' base is read bare (`lui`/`lw` in one register:
   `sda` in this -G0 unit), the limit is a $gp word. */
extern u16 *D_L11_001FC420[];
extern u8 *D_L11_001B359C __attribute__((sda));
extern s32 D_L11_001B35B8[] __attribute__((sda));
extern f32 func_00282E80(u8 *, u8 *);
extern s32 func_L11_00441868(u8 *, s32);
/* Runs what the id in its second argument names on the object and returns a value the caller
   keeps; the arguments are read in this order (object, id, two floats, two ints). */
extern s32 func_002B3BA8(u8 *, s32, f32, f32, s32, s32);

/* The pairing step of a kind-0xD98 object (state block at +0x68: partner +0x350, phase +0x366,
   the halfword at +0x36A). Below state 4 it forgets its partner and its phase. In phase 1 it
   runs func_002B3BA8 (result to +0x36A) and takes its partner from +0x220; from any other phase
   it enters phase 1 (and does the same) when func_L11_00441868 grants a counter of its kind from
   the owner at +0xB8. In phase 2 with a partner it stays paired (+0x36A of both set to 2) while
   the partner is alive (state byte not 0xFE or 0xFD, byte +0x95 above 1), is in the same phase
   and points back at it; otherwise it drops the partner and goes back to phase 0. Without a
   partner it walks the id list of its group for the nearest other kind-0xD98 object (state byte
   3 or more, not 0xFE or 0xFD, phase 0) closer than 1000.0 and pairs with it: partner pointers,
   phase 2 and +0x36A = 2 on both sides. The state block of the partner being checked and that
   of the object chosen are two variables (one per role), and the group byte goes through a
   halfword local so that each loop test loads it once. */
void func_L11_00448DF8(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    u16 *p;
    u8 *e;
    u8 *best;
    u8 *partner;
    u8 *pb;
    u8 *bb;
    f32 best_d;
    u16 g;

    if (self[0x20] < 4) {
        *(u8 **)(state + 0x350) = 0;
    } else {
        if (*(s16 *)(state + 0x366) == 1) {
            *(s16 *)(state + 0x36A) =
                func_002B3BA8(self, *(s32 *)(state + 0x360), 100.0f, 100.0f, 0, 0);
            *(u8 **)(state + 0x350) = *(u8 **)(state + 0x220);
            return;
        } else if (func_L11_00441868(*(u8 **)(self + 0xB8), *(s16 *)(self + 0xAA))) {
            *(s16 *)(state + 0x366) = 1;
            *(s16 *)(state + 0x36A) =
                func_002B3BA8(self, *(s32 *)(state + 0x360), 100.0f, 100.0f, 0, 0);
            *(u8 **)(state + 0x350) = *(u8 **)(state + 0x220);
            return;
        }
        if (*(s16 *)(state + 0x366) == 2 && *(u8 **)(state + 0x350) != 0) {
            partner = *(u8 **)(state + 0x350);
            pb = *(u8 **)(partner + 0x68);
            if (partner[0x20] != 0xFE) {
                if (partner[0x20] != 0xFD) {
                    if (partner[0x95] != 0) {
                        if (partner[0x95] != 1) {
                            if (*(s16 *)(pb + 0x366) == *(s16 *)(state + 0x366)) {
                                if (*(u8 **)(pb + 0x350) == self) {
                                    *(s16 *)(state + 0x36A) = 2;
                                    *(s16 *)(pb + 0x36A) = 2;
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            *(u8 **)(state + 0x350) = 0;
            *(s16 *)(state + 0x366) = 0;
            return;
        }
        best = 0;
        best_d = 1000.0f;
        for (p = D_L11_001FC420[self[0x21]];
             (g = self[0x21]) != 0xFF && g <= D_L11_001B35B8[0] && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L11_001FC420[g]);
             p++) {
            e = D_L11_001B359C + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (e[0x20] != 0xFE) {
                if (e[0x20] != 0xFD) {
                    if (e != self && e[0x20] >= 3 && *(s16 *)(e + 0xAA) == 0xD98 &&
                        *(s16 *)(*(u8 **)(e + 0x68) + 0x366) == 0) {
                        if (func_00282E80(self + 0x10, e + 0x10) < best_d) {
                            best = e;
                            best_d = func_00282E80(self + 0x10, e + 0x10);
                        }
                    }
                }
            }
        }
        if (best != 0) {
            *(u8 **)(state + 0x350) = best;
            *(s16 *)(state + 0x366) = 2;
            *(s16 *)(state + 0x36A) = 2;
            bb = *(u8 **)(best + 0x68);
            *(u8 **)(bb + 0x350) = self;
            *(s16 *)(bb + 0x366) = 2;
            *(s16 *)(bb + 0x36A) = 2;
            return;
        }
    }
    *(s16 *)(state + 0x366) = 0;
}

extern float func_0029F530(char *);
extern void func_0029FCC0(char *, int, void *);
extern void func_L00_0031BDC0(void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_002A8C28(char *, void *, int, float, float, float, int, int, int);
extern int func_002E5CF8(int, int, char *);

void func_L11_00449098(char *object)
{
    float start[4], end[4], closest[4], remaining[4], span[4];
    char *state;
    float time, fraction;

    time = func_0029F530(object);
    state = *(char **)(object + 0x68);
    if (19.0f <= time && time <= 31.0f) {
        func_0029FCC0(object, 0, start);
        func_0029FCC0(object, 1, end);
        func_L00_0031BDC0(closest, start, end,
                         *(char **)(state + 0x350) + 0x10);
        func_00282CF0(remaining, closest, end);
        func_00282CF0(span, start, end);
        fraction = func_00282DF0(remaining);
        fraction /= func_00282DF0(span);
        if (fraction < 0.0f)
            fraction = 0.0f;
        if (fraction > 1.0f)
            fraction = 1.0f;
        if (func_002A8C28(object, closest, 0x10001,
                         fraction * 0.35f + 0.15f,
                         (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0)
            && *(short *)(state + 0x368) == 0) {
            func_002E5CF8(5, 0, object);
            *(short *)(state + 0x368) = 1;
        }
        func_002A8C28(object, end, 0x10001, 0.5f,
                      (float)*(unsigned char *)(state + 0x34), 1.0f, 0, 1, 0);
    }
}

void func_L11_004492A0(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);
    s32 p = (s32)(long)func_3224B0(0x9D8);

    *(s32 *)(s0 + 0x354) = p;
    if (p == 0)
        return;
    *(u8 *)((char *)(long)p + 0x30) = *(u8 *)(a0 + 0x30);
    *(u16 *)((char *)(long)*(s32 *)(s0 + 0x354) + 0x32) = *(u16 *)(a0 + 0x32);
    *(u8 *)((char *)(long)*(s32 *)(s0 + 0x354) + 0x31) = 1;
    *(u64 *)((char *)(long)*(s32 *)(s0 + 0x354) + 0x38) = *(u64 *)(a0 + 0x38);
    func_324F00((char *)(long)*(s32 *)(s0 + 0x354));
    *(s32 *)((char *)(long)*(s32 *)(s0 + 0x354) + 0x98) = 0;
    *(s32 *)(*(char **)((char *)(long)*(s32 *)(s0 + 0x354) + 0x68) + 0x3C) = 1;
}

/* func_L11_00449330 is in L11_00449330.c: PAL's level 11 has other code at its place,
   so the calls to it from this unit go through its symbol. */

void func_L11_004496A0(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    int colors[3];
    int green, blue;

    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x366) = 0;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x36E) = active;
    func_002B60B0(object, 0.0055555556900799274f, 0.10333333909511566f,
                  0.0034906589426100254f, 0.41887909173965454f);
    *(u8 *)(state + 0x6A) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x36E) != 0) {
        func_002A7750(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_002A7470(object, 0, 0, 0);
        func_002A05A8(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        if (*(u8 *)(object + 0x43) != 0)
            func_002A7470(object, 0, 0, 10);
        func_002A7750(object, 3, 1);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    func_L11_004492A0(object);
    *(short *)(state + 0x36C) = mode;
    *(int *)(state + 0x200) = 0;
    func_002B3380(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
    if (*(char **)(state + 0x354) != 0) {
        func_002A04B8(object, &colors[0], &colors[1], &colors[2]);
        green = colors[1];
        blue = colors[2];
        func_002A0488(*(char **)(state + 0x354), colors[0], green, blue);
    }
}

void func_L11_00449878(char *a0)
{
    char *s2 = a0;
    char *s1;
    TI128 tmp;

    func_32C9E0(a0, 1, 0);
    func_32C700(a0, 0, 0, 3);
    func_324560(a0);
    *(u16 *)(s2 + 0x34) = (*(u16 *)(s2 + 0x34) & 0xEFFF) | 0x47;
    *(u8 *)(s2 + 0x31) = 0;
    *(s32 *)(s2 + 0x98) = 0;
    s1 = *(char **)(s2 + 0x68);
    if (*(s16 *)(s1 + 0x366) == 1)
        func_L11_00441978(*(s32 *)(s2 + 0xB8), 0xD98);
    *(s16 *)(s1 + 0x366) = 0;
    *(s32 *)(s1 + 0x350) = 0;
    if (*(s32 *)(s1 + 0x354) != 0) {
        tmp = *(TI128 *)((char *)(long)*(s32 *)(s1 + 0x354) + 0x10);
        func_L11_00449330(s2, &tmp);
    }
    if (*(u8 *)(s1 + 0x2B1) != 0) {
        f32 one = 1.0f;

        *(u8 *)(s1 + 0x2B2) = 0;
        *(f32 *)(s1 + 0x2D8) = one;
        *(f32 *)(s1 + 0x2D4) = one;
        *(f32 *)(s1 + 0x2D0) = one;
        func_323688(s2, s1 + 0x2B0);
        func_00282A60(s1 + 0x2B0, 0, 0x40);
    }
}

extern void func_0029F978(char *a0, int a1, char *a2);
extern void func_002A7A00(void *a0, float f12, float f13);
extern void func_002B0A68(char *a0, int a1, void *a2, float f12, float f13, float f14,
                        float f15, int a3);
extern void func_L02_003FC248(char *a0, int a1, int a2);
extern void func_L01_003E9CF8(char *a0, int a1, char *a2);

/* The moby's death path: clears the spawn flags, hands the last position to the scene
   manager, resets the 0x2B0 rig and leaves the object in its dead state. */
void func_L11_00449970(char *a0, int a1, int a2)
{
    char *s1 = *(char **)(a0 + 0x68);
    char *s0;
    TI128 tmp;
    float f0;

    *(s32 *)(s1 + 0x20) = 0;
    if (*(s16 *)(s1 + 0x366) == 1)
        func_L11_00441978(*(s32 *)(a0 + 0xB8), 0xD98);
    *(s16 *)(s1 + 0x366) = 0;
    *(s32 *)(s1 + 0x350) = 0;
    if (*(s32 *)(s1 + 0x354) != 0) {
        tmp = *(TI128 *)((char *)(long)*(s32 *)(s1 + 0x354) + 0x10);
        func_L11_00449330(a0, &tmp);
    }
    if (*(u8 *)(s1 + 0x2B1) == 0) {
        s0 = s1 + 0x2B0;
        func_00282A60(s0, 0, 0x40);
        func_0029F978(a0, 3, s0);
        f0 = 1.0e-4f;
        *(u8 *)(s1 + 0x2B2) = 1;
        *(f32 *)(s1 + 0x2D8) = f0;
        *(f32 *)(s1 + 0x2D4) = f0;
        *(f32 *)(s1 + 0x2D0) = f0;
        func_002A7A00((char *)&tmp, 1.0f / 60.0f, 0.0500000045f);
        func_002B0A68(a0, 0x20, (char *)&tmp, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(s32 *)(a0 + 0x98) = 0;
    if (a1 == 0)
        func_L02_003FC248(a0, 0, -1);
    if (a2 == 0)
        func_L01_003E9CF8(a0, 0, (char *)func_L11_00449878);
    else
        func_L11_00449878(a0);
}

/* func_L11_00449AD8 is defined in L11_00449AD8-helpers.c. */

/* func_L11_00449C70 is defined in L11_004465F8-aim-g8.c. */

/* func_L11_0044AFC8 is defined in L11_0044AFC8-g8.c. */

/* func_L11_0044BD68 is in L11_0044BD68-g8.c. */

void func_L11_0044C0F0(char *a0)
{
    char *p = *(char **)(a0 + 0x68);

    if (*(u16 *)(a0 + 0x96) < 0xFFFF)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    func_338398(a0, p + 0x4E0, 4.0f, 7, 1);
    func_32E480(a0, a0 + 0x10, 1.3f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

/* advances the sub-object's ring cursor, hands the new slot of the 0x370 table to the scene
   manager, and refreshes the matching slot of the 0x270 table from the live 0x4A4 record */
/* func_L11_0044C180 is defined in L11_0044C180-helpers.c. */

/* func_L11_0044C220 is defined in L11_004465F8-g8.c (its globals are reached through $gp). */

/* state handler: clears the 0x490 word while the frame byte is out of the 0..3 window, otherwise
   arms the 0x4CA gate through the 0xB8 handle and runs the 100-unit smash into it */
/*W23B*/
/* Same body as func_L02_003F16F0, with this function's own callees. */
void func_L11_0044C268(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (*(unsigned char *)(arg0 + 0x20) < 4) {
        *(int *)(state + 0x490) = 0;
        goto done;
    }

    if (*(short *)(state + 0x4CA) == 1) {
        *(short *)(state + 0x4C8) =
            func_002B3BA8(arg0, *(int *)(state + 0x4C4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x490) = *(int *)(state + 0x220);
    } else {
        if (func_L11_00441868(*(int *)(arg0 + 0xB8), *(short *)(arg0 + 0xAA)) == 0)
            goto done;
        *(short *)(state + 0x4CA) = 1;
        *(short *)(state + 0x4C8) =
            func_002B3BA8(arg0, *(int *)(state + 0x4C4), 100.0f, 100.0f, 0, 0);
        *(int *)(state + 0x490) = *(int *)(state + 0x220);
    }
    return;

done:
    *(short *)(state + 0x4CA) = 0;
}
/*W23E*/


void func_L11_0044C328(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);
    char **slot;
    char *collision, *health;
    int i;

    *(short *)(state + 0x4CA) = 0;
    *(short *)(state + 0x88) = 0;
    *(u8 *)(state + 0x2E) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x4D2) = active;
    func_002B60B0(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x4D2) != 0) {
        func_002A7750(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_002A7470(object, 2, 0, 0);
        func_002A05A8(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(u8 *)(state + 0x6A) = 0;
    collision = state + 0x1F0;
    health = state + 0x20;
    for (i = 0; i < 2; i++) {
        slot = (char **)(state + 0x4A0 + i * 4);
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) &= 0xFFFE;
            *(u8 *)(*slot + 0x31) = 1;
            *(int *)(*slot + 0x98) = *(int *)(*(char **)(*slot + 0x24) + 0x10);
        }
    }
    *(short *)(state + 0x4D0) = mode;
    *(int *)(state + 0x200) = 0;
    func_002B3380(object, collision, health);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

extern void func_L11_00441978(int, int);
extern void func_0032C700(char *, int, int, int, int, int, int, int,
                         float, float, int, int, int, int);
extern void func_002E5DA0(int, int, char *, int);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002B0A68(char *, int, void *, float, float, float, float, int);

void func_L11_0044C4F0(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];
    char **slot;
    int i;

    if (*(short *)(state + 0x4CA) == 1)
        func_L11_00441978(*(int *)(object + 0xB8), 0xDCF);
    *(short *)(state + 0x4CA) = 0;
    *(int *)(state + 0x490) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        func_0032C700(object + 0x10, 0, 0x1E, 5, 5, 5, 0x2D, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        func_002E5DA0(0, 0, object, 0xDF7);
        func_002A7A00(direction, 0.033333335071802139f, 0.083333335816860199f);
        func_00282CC0(direction, direction, state + 0xD0);
        func_002B0A68(object, 0x7F0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    slot = (char **)(state + 0x4A0);
    for (i = 1; i >= 0; i--) {
        if (*slot != 0) {
            *(u16 *)(*slot + 0x34) |= 1;
            *(u8 *)(*slot + 0x31) = 0;
            *(int *)(*slot + 0x98) = 0;
        }
        slot++;
    }
    func_002A7470(object, 0, 0, 3);
    func_002A05A8(object);
    func_002A7750(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}

/* func_L11_0044C688 is defined in L11_0044C688-helpers.c. */

void func_L11_0044C818(char *a0)
{
    char *p = *(char **)(a0 + 0x68);

    *(u16 *)(p + 0x4CC) = *(u8 *)(a0 + 0x20);
    *(u16 *)(p + 0x4CE) = *(u8 *)(a0 + 0x95);
    func_32C9E0(a0, 6, 4);
}

/* func_L11_0044C850 is defined in L11_004465F8-aim-0044C850-g8.c. */

char *func_L11_00450328(char *a0, TI128 *a1, TI128 *a2, float f12)
{
    char *obj = func_0029EFD0(0xDD9);

    if (obj != 0) {
        char *st;
        float f20;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(short *)(obj + 0x32) = 0xFF;
        obj[0x31] = 1;
        obj[0x20] = 0;
        *(long long *)(obj + 0x38) = *(long long *)(a0 + 0x38);
        qcopy(obj + 0x10, a2);
        st = *(char **)(obj + 0x68);
        qcopy(st, a1);
        *(float *)(st + 0x14) = f12;
        *(char **)(st + 0x10) = a0;
        *(float *)(st + 0x18) = func_002A7940();
        *(float *)(st + 0x1C) = func_002A7878(0.20943954586982727f, 0.6283186078071594f);
        *(float *)(st + 0x20) = 0.15f;
        *(unsigned char *)(obj + 0x23) = 0x80;
        *(unsigned short *)(obj + 0x34) |= 0x100;
        *(float *)(obj + 0x2C) = func_002A7878(0.005f, 0.00625f);
        *(int *)(st + 0x24) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x200;
        f20 = func_002A7878(2.0f, 4.0f);
        *(unsigned short *)(obj + 0x34) |= 0x41;
        func_002C2210(obj + 0x10, 4, 0x801060E0, 0, 10, D_L11_001A8F20, f20 * 0.3f, f20, 0.0f, 0);
        func_002C2210(obj + 0x10, 4, -1, 1, -10, D_L11_001A8F20, f20 * 0.04f, f20 * 0.4f, 0.0f, 0);
    }
    return obj;
}


/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L11_00450748(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* func_L11_00451178 is in L11_00451178-gu-g8.c. */

/* func_L11_00452450 is defined in L11_004465F8-g8.c. */

void func_L11_00452810(char *a0)
{
    char *p = *(char **)(a0 + 0x68);

    if (*(u16 *)(a0 + 0x96) < 0xFFFF)
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
    func_338398(a0, p + 0x2E0, 4.0f, 5, 1);
    func_32E480(a0, a0 + 0x10, 1.3f, 1.0f, 1.0f, 0x4000000, 0, 1, 0);
}

void func_L11_004528A0(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    float f;

    if (*(u8 *)(a0 + 0x95) != 0) {
        func_L00_003D7250(a0, s1 + 0x270, 0.125f, 0x36F6, 0x20000000, 0x20000000);
        f = 0.15f;
        func_L00_003D7250(a0, s1 + 0x280, f, 0x1050B0, 0x30000000, 0x20000000);
        func_L00_003D7250(a0, s1 + 0x290, f, 0x1050B0, 0x10000000, 0x30000000);
    }
}

void func_L11_00452C58(char *object, int mode, int active) {
    char *state = *(char **)(object + 0x68);

    *(u8 *)(state + 0x2E) = 1;
    *(short *)(state + 0x88) = 0;
    *(short *)(state + 0x2D2) = 1;
    *(float *)(state + 0x20) = *(short *)(state + 0x24);
    *(short *)(state + 0x2D8) = active;
    func_002B60B0(object, 0.004444444552063942f, 0.13333334028720856f,
                  0.0011635529808700085f, 0.10471977293491364f);
    if (*(u8 *)(object + 0x43) != 2)
        func_002A7470(object, 2, 0, 0);
    *(u8 *)(object + 0x7F) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) | 0x1000) & 0xFFB9;
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    if (*(short *)(state + 0x2D8) != 0) {
        func_002A7750(object, 4, 2);
        *(u16 *)(object + 0x34) |= 0x100;
        func_002A7470(object, 2, 0, 0);
        func_002A05A8(object);
        func_L11_003973F8(object, 0, 2.0f, 2.0f);
    } else {
        func_002A7750(object, 3, 0);
        *(u8 *)(object + 0x31) = 1;
        *(u16 *)(object + 0x34) &= 0xFEFE;
    }
    *(short *)(state + 0x2D4) = mode;
    *(u8 *)(state + 0x6A) = 0;
    *(int *)(state + 0x200) = 0;
    func_002B3380(object, state + 0x1F0, state + 0x20);
    if (*(short *)(state + 0x50) != 0) {
        *(short *)(state + 0x50) = 0;
        func_002A0488(object, *(u8 *)(state + 0x54), *(u8 *)(state + 0x55),
                      *(u8 *)(state + 0x56));
        *(short *)(state + 0x52) = 1;
    }
}

void func_L11_00452DF8(char *object) {
    char *state = *(char **)(object + 0x68);
    float direction[4];

    *(short *)(state + 0x2D2) = 0;
    *(int *)(state + 0x2C4) = 0;
    if (*(u8 *)(object + 0x31) != 0) {
        func_0032C700(object + 0x10, 0, 5, 5, 25, 20, 10, 1,
                     0.5f, 0.0f, 1, 0, 0, 0);
        func_002E5DA0(0, 0, object, 0xDF7);
        func_002A7A00(direction, 0.083333335816860199f, 0.11666667461395264f);
        func_00282CC0(direction, direction, state + 0xD0);
        func_002B0A68(object, 0xFF0, direction, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    func_002A7470(object, 0, 0, 3);
    func_002A05A8(object);
    func_002A7750(object, 1, 0);
    *(u8 *)(object + 0x31) = 0;
    *(int *)(object + 0x98) = 0;
    *(u16 *)(object + 0x34) = (*(u16 *)(object + 0x34) & 0xEFFF) | 0x47;
}


/* func_L11_00452F30 is defined in L11_00452F30-helpers.c. */

void func_L11_004530C0(char *a0)
{
    func_32C9E0(a0, 6, 3);
}

/* func_L11_004530E0 is defined in L11_004465F8-aim-004530E0-g8.c. */
