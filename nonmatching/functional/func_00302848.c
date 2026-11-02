/* functional: high. Same calls, arguments and stores as retail; the puff's third byte is read through the exact pointer slot. */
/* func_00302848 (468 bytes, 28 places), closer M2: 464 bytes under
 *     -O2 -G8 -ffunction-sections   (no -mno-split-addresses needed)
 * Fixed against the earlier draft: func_002A77E0 takes one argument (every caller passes
 * one; the a1 load in retail's bnez slot is the later D_001AE900 argument); the vertical
 * speed goes into the second (velocity) vector at sp+0, not the position vector; the zero
 * vector is qzero(), which puts the D_001AE930 argument in the jal slot; func_002C2210
 * takes (char *, float, float, s32, s32, float, s32, s32, char *, s32), found by trying all
 * 84 float positions; the macro-form words are sized sda arrays. Head, the spawn calls
 * and the epilogue match. Left: retail copies the func_002A7820 result into $s0 and masks
 * it in place (daddu + andi, 4 bytes more); this cc1 combines them into one andi, and the
 * callee-saved roles then rotate (tint/colour/vector s0/s1/s2 against s2/s0/s1). Twelve
 * spellings of the mask (u8 local, separate &=, (u8) cast, colour argument split out), with
 * and without -g, all compile to the same code.
 * M16: func_002C3150 is (void *, void *, int, u8, u8, int, float) as its matched callers in
 * L01_00397110 declare it (float last, the two bytes promoted at the call): that gives
 * retail's daddu + andi and the register roles, 468/468 bytes. D_001AE8EC as a plain
 * incomplete array keeps its load out of the jal slot. Left (12 lines, order only): cc1
 * counts the 16-byte sda arrays' loads as one instruction, so it puts them in jal slots
 * (the assembler expands them to two) and sched1 orders the func_002C2210 a1/a2/t1 setup,
 * the func_002A7878 f12/f13 loads and the func_00283D38 a0/f12 setup differently from
 * retail. Under -mno-split-addresses those three spots match but the head does not. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F302848;

extern s32 D_001AE930 __attribute__((sda));
extern s32 D_001AE900 __attribute__((sda));
extern s32 D_001AE928 __attribute__((sda));
extern float D_001AE920 __attribute__((sda));
extern s32 D_001AE92C __attribute__((sda));
extern float D_001AE8F0 __attribute__((sda));
extern float D_001AE8E8 __attribute__((sda));
extern s32 D_001AE904[4] __attribute__((sda));
extern float D_001AE924[4] __attribute__((sda));
extern char D_001A8BD0[16] __attribute__((sda));
extern u8 *D_001F2638;
extern s32 D_001B1688[4] __attribute__((sda));
extern float D_001AE8EC[];
extern s32 D_001AE914[4] __attribute__((sda));
extern s32 D_001AE918[4] __attribute__((sda));
extern s32 D_001AE908[4] __attribute__((sda));
extern s32 D_001AE90C[4] __attribute__((sda));
extern float D_001AE8F8[4] __attribute__((sda));

extern s32 func_002A77E0(s32);
extern void func_002C2210(char *, float, float, s32, s32, float, s32, s32, char *, s32);
extern char *func_002C2FD8(char *, s32, s32, s32, s32, s32, s32, float);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, char *);
extern float func_002A7878(float, float);
extern s32 func_002A7820(s32, s32);
extern s32 func_00283D38(s32, s32, float);
extern void func_002C3150(void *, void *, int, unsigned char, unsigned char, int, float);

/* Spawns the object's trail puff; when not suppressed and flag one of the resident word is set it also emits the tinted streak. */
void func_00302848(char *obj, s32 quiet)
{
    V4_F302848 zero;
    V4_F302848 vec;
    char *rec = *(char **)(obj + 0x68);
    char *puff;
    char *pos;
    s32 tint, color, k;

    qzero(&zero);
    if (func_002A77E0(D_001AE930) == 0) {
        char *first = obj + 0x10;
        if (func_002A77E0(1) != 0)
            k = -D_001AE928;
        else
            k = D_001AE928;
        func_002C2210(first, D_001AE920, D_001AE924[0], D_001AE92C, D_001AE904[0], 0.0f, 2, k, D_001A8BD0, 0);
    }
    pos = obj + 0x10;
    puff = func_002C2FD8(pos, D_001AE900, *(u8 *)(rec + 0x41), 0, 0, 2, 0, D_001AE8F0);
    if (puff != 0)
        puff[2] = *D_001F2638;
    if (quiet == 0 && (D_001B1688[0] & 1)) {
        func_002A7A00(&vec, 0.0f, 0.05f);
        func_00282CC0(&vec, &vec, pos);
        zero.f[2] = -(func_002A7878(D_001AE8E8, D_001AE8EC[0]) * 0.016666668f);
        tint = func_002A7820(D_001AE914[0], D_001AE918[0]);
        color = func_00283D38(D_001AE908[0], D_001AE90C[0], func_002A7878(0.0f, 1.0f));
        func_002C3150(&vec, &zero, color, tint, func_002A77E0(0xFF), 0, D_001AE8F8[0]);
    }
}
