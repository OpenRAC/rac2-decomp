#include "include_asm.h"

typedef short s16;
typedef int s32;
extern s32 func_002F3220(char *, float);
extern int func_00282948(void *);
extern s32 func_003D77F8(char *);
extern s32 func_L02_003D7830(char *);
extern s32 func_L02_00400650(char *, s32);
typedef int TI128 __attribute__((mode(TI)));
extern int D_L02_001B30C8 __attribute__((sda));
extern float D_L02_001B1040[2] __attribute__((sda));
extern char *D_L02_001B3B00 __attribute__((sda));
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002833F0(float *, float *);
extern void func_L02_002F2B88(char *, char *, float *);
extern s32 func_L02_003FB6C0(char *, char *);
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s32 D_L02_001B35B8[] __attribute__((sda));
extern s16 func_L02_004024A0(char *);
extern s32 func_L02_003D7300(char *);

/* Runs func_L02_003F5430 first when bit 0 of D_L02_001B30C8 is set. The angle at +0x88 is stepped
   (func_002AA2E8, 0.05 degree) towards the target at +0x8C when func_00282948 reports the timer at
   +0x90 idle or just run out, and towards zero while it is still counting down. When the target lies
   between zero and the angle, the timer gets a random 30..90 and the target a random size with the
   opposite sign. The angle is then the third word of a vector func_002833F0 turns into a matrix,
   which multiplies the 64-byte records of D_L02_001B3B00 that the entries of the list at +0x40 name,
   for each bit set in the mask at +0x84. */
void func_PAL_L02_003F9B50(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    float m[12];
    float b[4];
    float a[4];
    s32 i;
    s16 *s2;

    if (D_L02_001B30C8 & 1)
        func_L02_003F5430(a0);
    if (func_00282948(state + 0x90) != 0) {
        func_002AA2E8((float *)(state + 0x88), *(float *)(state + 0x8C), 0.0012566373f);
        if ((*(float *)(state + 0x88) >= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) >= 0.0f) ||
            (*(float *)(state + 0x88) <= *(float *)(state + 0x8C) && *(float *)(state + 0x8C) <= 0.0f)) {
            *(s32 *)(state + 0x90) = ((s32)(func_002A7820(0x1E, 0x5A)) * 5 + 2) / 6;
            if (0.0f < *(float *)(state + 0x8C))
                *(float *)(state + 0x8C) =
                    -(func_002A7878(D_L02_001B1040[0], D_L02_001B1040[1]) * 0.0003490659f);
            else
                *(float *)(state + 0x8C) =
                    func_002A7878(D_L02_001B1040[0], D_L02_001B1040[1]) * 0.0003490659f;
        }
    } else {
        func_002AA2E8((float *)(state + 0x88), 0.0f, 0.0012566373f);
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


