/* functional: medium. Near-miss draft written from m2c and the assembly (see check below). */
/* Near miss / handoff (Opus big14, 2026-10-26): func_0034B2C8, 6,048 bytes, boot + 27 level
 * places, the ammo/bolt HUD setup (one function: one prologue, one jr $ra). Written from m2c
 * and the assembly; no twin found.
 *
 * Profile: default -O2 -G0 -ffunction-sections in its own unit (src/game/0034B2C8.c).
 * Last verdict: tools/check.py -> 5988 bytes, expected 6048, 0/28. Opcodes match through the
 * first 356 instructions with the same registers; 100 opcode hunks / about 160 instructions.
 * The frame is 0x150 against 0x160 (retail spills 37 pointer slots, this spills 35).
 *
 * Measured so far:
 *   - Writing every widget as an inline self + N expression reproduces retail's shape: gcse
 *     hoists the second-half addresses into the block after the arg check and makes the
 *     copies retail spills (sw 0x9C <- 0x14 and so on), and the f26/f23 copies of 1.0/0.0.
 *   - The *func_00335E20(w) colour stores after the arg check go through one s32 local
 *     (retail keeps it in $s3 across the calls); the first half uses literals.
 *   - Colour words passed as float bits: denormal values stay as int-in-GPR + mtc1 (v0 form),
 *     normal single uses fold to li.s ($at form), both as retail. Normal values used twice
 *     (0x60442D00, 0xF0F0B0, 0x55F0C070) come out li.s/hoisted (union helper) or in a callee-
 *     saved GPR (pointer-cast helper, this draft); retail loads them via $v0 into $f20 right
 *     before the first use. Neither spelling found; the double-use form is the main open item.
 *   - Open as well: the loop's mult temporary (retail builds i*0x4C+0x358 in $s0 itself),
 *     self+0xE94 lands in $s2 here (spilled in retail), and the spill-slot order of the
 *     second-half pointers (it follows pseudo numbers, so it should follow once the
 *     expression set matches).
 *
 * closer3 (2026-10-26), the double-use colour: retail needs one SFmode pseudo set once from
 * an SImode constant (lui/ori $v0, mtc1 $v0,$f20) and read twice. In this cc1 every
 * spelling loses that pseudo: a union read `u.f` expands straight into $f13 and cse's
 * fold_rtx SUBREG case (gen_lowpart_if_possible of the known SImode constant) turns it into
 * a const_double (li.s); `f32 c = u.f` keeps a pseudo but cse folds it to a hoisted li.s; a
 * pointer pun (local or inline, `*(s32 *)&c = X`) is purged to an SImode pseudo that lives in
 * a saved GPR with an mtc1 per use. (Why denormals escape the fold is not checked yet.)
 * Look at whether retail's cse folds a SUBREG of a constant into SFmode at all (patch 0048
 * brings 2.95.2's cse.c), before more spellings. The giv-recombination change
 * (no_recombine_givs.py) does not change this function.
 */
#include "common.h"

typedef union {
    s32 i;
    f32 f;
} HudBits_34B2C8;

extern char D_001AE668[];
extern char D_001AE678[];
extern char D_001AE688[];
extern char D_001AE690[];
extern char D_001AE6A0[];
extern char D_001AE6B0[];
extern char D_001AE6C0[];
extern char D_001AE6D0[];
extern char D_001AE6E0[];
extern char D_001ADFE0[];
extern char D_001ADFF0[];
extern char D_001AE000[];
extern char D_001AE010[];
extern char D_001AE020[];
extern s32 D_001A7B90;
extern s32 D_001A79F8;

extern void func_003361E0(char *o, char *text, s32 arg);
extern void func_00336390(char *o, char *font, s32 n);
extern void func_00335E38(char *o, f32 x, f32 y, f32 z, f32 w);
extern void func_00335F88(char *o, f32 x, f32 y, f32 z, f32 w);
extern s32 *func_00335E20(char *o);
extern s32 *func_00335E18(char *o);
extern s32 *func_00335E10(char *o);
extern void func_00115484(void *dst, s32 c, s32 n);
extern void func_003369A8(char *o, char *text, s32 arg);
extern void func_00336A38(char *o, char *buf);
extern void func_00336A30(char *o, s32 n);
extern void func_00336710(char *o, char *text, s32 arg);
extern void func_00336920(char *o, s32 id, s32 n);
extern s32 func_00336E40(s32 arg);
extern f32 *func_00336DA8(s32 n, s32 a);
extern void func_00335F20(char *o, f32 *v);
extern void func_00335E68(char *o, s32 n);
extern void func_00115DA8(char *buf, char *fmt, s32 n);
extern f32 func_00283B98(f32 a, f32 b);
extern f32 func_00283180(f32 a);
extern f32 func_00283198(f32 a);
extern void func_00335EB0(char *o, s32 *v);
extern void func_00349D58(char *o, char *font, s32 arg);
extern void func_0034AFE8(char *o, f32 x, f32 y);
extern void func_003494D0(char *o, s32 arg);
extern void func_00349628(char *o, s32 n);
extern void func_003495D8(f32 weight, f32 x, f32 y, f32 z, f32 w, char *o, s32 index);
extern void func_00349610(char *o, s32 n, f32 a, f32 b);
extern void func_00349590(char *o, void *v);
extern void func_00349670(char *o, s32 v);
extern void func_003495C0(char *o, char *v);
extern void func_00349630(char *o, s32 v);
extern void func_00349678(char *o, f32 v);
extern s32 func_003495C8(char *o, s32 v);
extern void func_00349970(char *o, s32 arg);
extern void func_00349A60(char *o, s32 n, void *v);
extern void func_00349AA8(char *o, s32 n, s32 v);
extern void func_00349A70(f32 x, f32 y, f32 z, f32 w, char *o, s32 row, s32 group);
extern void func_00349B18(char *o, f32 v);
extern void func_0034CA90(char *o, s32 mode);
extern s32 func_002B0D70(void);

static inline f32 hud_bits_34B2C8(s32 i)
{
    f32 f;

    *(s32 *)&f = i;
    return f;
}

/* The ammo/bolt HUD setup: initialises the HUD's text, sprite and fade widgets. */
void func_0034B2C8(char *self, char *font, s32 arg)
{
    char buf[16];
    s32 i;
    s32 color;
    f32 *v;

    *(s32 *)(self + 0x157C) = 0;
    *(s32 *)(self + 0x1580) = 0;
    func_003361E0(self, D_001AE668, arg);
    func_00336390(self, font + 0x8710, 1);
    func_00335E38(self, 10.0f, 10.0f, 0.0f, 0.0f);
    func_003361E0(self + 0x4C, D_001AE678, arg);
    func_00335E38(self + 0x4C, 10.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x4C, font + 0x8710, 2);
    func_003361E0(self + 0x98, D_001AE688, arg);
    func_00335E38(self + 0x98, 10.0f, 18.5f, 0.0f, 0.0f);
    func_00336390(self + 0x98, font + 0x8710, 5);
    func_00115484(self + 0xE4, 0, 0x18);
    func_003369A8(self + 0x100, D_001AE690, arg);
    func_00335F88(self + 0x100, 0.9f, 0.0f, 0.0f, 0.0f);
    func_00336A38(self + 0x100, self + 0xE4);
    func_00335E38(self + 0x100, 64.0f, 15.0f, 0.0f, 0.0f);
    func_00336A30(self + 0x100, 0);
    func_00336710(self + 0x148, D_001AE6A0, arg);
    func_00335F88(self + 0x148, 32.0f, 32.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x148, 20.0f, 15.0f, 0.0f, 0.0f);
    *func_00335E20(self + 0x148) = 0x60F0F0B0;
    func_003361E0(self + 0x184, D_001AE6B0, arg);
    func_00335E38(self + 0x184, 498.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x184, font + 0x8710, 3);
    func_003361E0(self + 0x1D0, D_001AE6C0, arg);
    func_00335E38(self + 0x1D0, 498.0f, 10.0f, 0.0f, 0.0f);
    func_00336390(self + 0x1D0, font + 0x8710, 4);
    func_00115484(self + 0x21C, 0, 0x18);
    func_003369A8(self + 0x238, D_001AE6D0, arg);
    func_00335F88(self + 0x238, 0.9f, 0.0f, 0.0f, 0.0f);
    func_00336A38(self + 0x238, self + 0x21C);
    func_00335E38(self + 0x238, 440.0f, 15.0f, 0.0f, 0.0f);
    func_00336A30(self + 0x238, 2);
    func_00336710(self + 0x280, D_001AE6E0, arg);
    func_00335F88(self + 0x280, 32.0f, 32.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x280, 457.0f, 15.0f, 0.0f, 0.0f);
    func_00336920(self + 0x280, 0x7567, 0);

    if (arg != 0) {
        v = func_00336DA8(0x10, func_00336E40(arg));
        *(f32 **)(self + 0x7E4) = v;
        v[0] = 0.0f;
        v[1] = 0.0f;
        v[2] = 0.0f;
        v[3] = 0.0f;
    }

    func_003361E0(self + 0x2C0, D_001ADFE0, arg);
    func_00336390(self + 0x2C0, font + 0x8710, 7);
    func_00335F88(self + 0x2C0, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x2C0, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0x442D00;
    *func_00335E20(self + 0x2C0) = color;
    func_00335F20(self + 0x2C0, *(f32 **)(self + 0x7E4));
    func_003361E0(self + 0x30C, D_001ADFF0, arg);
    func_00336390(self + 0x30C, font + 0x8710, 6);
    func_00335F88(self + 0x30C, 1.0f, 1.0f, 0.0f, 0.0f);
    func_00335E38(self + 0x30C, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xF0C070;
    *func_00335E20(self + 0x30C) = color;
    func_00335F20(self + 0x30C, *(f32 **)(self + 0x7E4));
    func_003361E0(self + 0x5B8, D_001AE000, arg);
    func_00336390(self + 0x5B8, font + 0x8710, 0x10);
    func_00335E38(self + 0x5B8, 125.0f, 208.0f, 0.0f, 0.0f);
    color = 0xFFFEED;
    *func_00335E20(self + 0x5B8) = color;
    func_00335E68(self + 0x5B8, 0);

    for (i = 0; i < 8; i++) {
        char *w;
        f32 angle;
        f32 x;

        func_00115DA8(buf, D_001AE010, i);
        w = self + (i * 0x4C + 0x358);
        func_003361E0(w, buf, arg);
        func_00336390(w, font + 0x8710, i + 8);
        func_00335F88(w, 1.0f, 1.0f, 0.0f, 0.0f);
        func_00335E38(w, 125.0f, 208.0f, 0.0f, 0.0f);
        func_00335F20(w, *(f32 **)(self + 0x7E4));
        color = 0x442D00;
        *func_00335E20(w) = color;
        func_00115DA8(buf, D_001AE020, i);
        w = self + (i * 0x3C + 0x604);
        func_00336710(w, buf, arg);
        func_00335E68(w, 0);
        angle = func_00283B98((f32)i * 2.0f * 0.39269909f - 3.14159274f, 1.57079637f);
        x = (s32)(func_00283180(angle) * 82.14f) + 109;
        func_00335E38(w, x, (s32)(func_00283198(angle) * 76.442f) + 189, 0.0f, 0.0f);
        func_00335F88(w, 32.0f, 32.0f, 0.0f, 0.0f);
        color = 0xF0F0B0;
        *func_00335E20(w) = color;
    }
    for (i = 1; i < 8; i++) {
        func_00335EB0(self + 0x358 + i * 0x4C, func_00335E18(self + 0x358));
        func_00335EB0(self + 0x604 + i * 0x3C, func_00335E18(self + 0x604));
    }
    func_00335EB0(self + 0x2C0, func_00335E18(self + 0x358));

    func_00349D58(self + 0x7E8, font, arg);
    func_0034AFE8(self + 0x7E8, 147.0f, 10.0f);
    *(s32 *)(self + 0x7F4) = 0;

    func_003494D0(self + 0xBEC, arg);
    func_00349628(self + 0xBEC, 3);
    func_003495D8(0.0f, hud_bits_34B2C8(0x442D00), 0.0f, 0.0f, 0.0f, self + 0xBEC, 0);
    func_003495D8(0.3f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f, self + 0xBEC, 1);
    func_003495D8(1.0f, hud_bits_34B2C8(0x60442D00), 0.0f, 0.0f, 0.0f, self + 0xBEC, 2);
    func_00349610(self + 0xBEC, 1, 0.0f, 2.0f);
    func_00349590(self + 0xBEC, func_00335E20(self + 0x358));
    func_00349670(self + 0xBEC, 0);
    func_003495C0(self + 0xBEC, self + 0x1448);
    func_00349630(self + 0xBEC, -1);
    func_00349678(self + 0xBEC, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xBEC, 0);

    func_003494D0(self + 0xC74, arg);
    func_00349628(self + 0xC74, 3);
    func_003495D8(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, self + 0xC74, 0);
    func_003495D8(0.3f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xC74, 1);
    func_003495D8(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xC74, 2);
    func_00349590(self + 0xC74, func_00335E18(self + 0x358));
    func_00349670(self + 0xC74, 0);
    func_003495C0(self + 0xC74, self + 0x1444);
    func_00349630(self + 0xC74, -1);
    func_00349678(self + 0xC74, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xC74, 0);

    func_003494D0(self + 0xE0C, arg);
    func_00349628(self + 0xE0C, 3);
    func_003495D8(0.0f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f, self + 0xE0C, 0);
    func_003495D8(0.5f, hud_bits_34B2C8(0xF0F0B0), 0.0f, 0.0f, 0.0f, self + 0xE0C, 1);
    func_00349610(self + 0xE0C, 0, 0.0f, 0.0f);
    func_003495D8(1.0f, hud_bits_34B2C8(0x60F0F0B0), 0.0f, 0.0f, 0.0f, self + 0xE0C, 2);
    func_00349610(self + 0xE0C, 1, 0.0f, 0.0f);
    func_00349590(self + 0xE0C, func_00335E20(self + 0x604));
    func_00349670(self + 0xE0C, 0);
    func_003495C0(self + 0xE0C, self + 0x1448);
    func_00349630(self + 0xE0C, -1);
    func_00349678(self + 0xE0C, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xE0C, 0);

    func_003494D0(self + 0xCFC, arg);
    func_00349628(self + 0xCFC, 3);
    func_003495D8(0.0f, hud_bits_34B2C8(0xF0C070), 0.0f, 0.0f, 0.0f, self + 0xCFC, 0);
    func_003495D8(0.3f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f, self + 0xCFC, 1);
    func_003495D8(1.0f, hud_bits_34B2C8(0x55F0C070), 0.0f, 0.0f, 0.0f, self + 0xCFC, 2);
    func_00349610(self + 0xCFC, 1, 0.0f, 3.0f);
    func_00349590(self + 0xCFC, func_00335E20(self + 0x30C));
    func_00349670(self + 0xCFC, 0);
    func_003495C0(self + 0xCFC, self + 0x1448);
    func_00349630(self + 0xCFC, -1);
    func_00349678(self + 0xCFC, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xCFC, 0);

    func_003494D0(self + 0xD84, arg);
    func_00349628(self + 0xD84, 3);
    func_003495D8(0.0f, 1.2f, 1.2f, 0.0f, 0.0f, self + 0xD84, 0);
    func_003495D8(0.3f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xD84, 1);
    func_003495D8(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xD84, 2);
    func_00349590(self + 0xD84, func_00335E18(self + 0x30C));
    func_00349670(self + 0xD84, 0);
    func_003495C0(self + 0xD84, self + 0x1444);
    func_00349630(self + 0xD84, -1);
    func_00349678(self + 0xD84, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xD84, 0);

    func_003494D0(self + 0xE94, arg);
    func_00349628(self + 0xE94, 3);
    func_003495D8(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, self + 0xE94, 0);
    func_003495D8(0.01f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xE94, 1);
    func_003495D8(1.0f, 1.0f, 1.0f, 0.0f, 0.0f, self + 0xE94, 2);
    func_00349590(self + 0xE94, *(f32 **)(self + 0x7E4));
    func_00349670(self + 0xE94, 0);
    func_003495C0(self + 0xE94, self + 0x1444);
    func_00349630(self + 0xE94, -1);
    func_00349678(self + 0xE94, D_001A7B90 != 0 ? 0.14f : 0.116666675f);
    func_003495C8(self + 0xE94, 0);

    func_00349970(self + 0xF1C, arg);
    func_00349A60(self + 0xF1C, 0, func_00335E20(self));
    func_00349AA8(self + 0xF1C, 0, 0x442D00);
    func_00349AA8(self + 0xF1C, 1, 0x60442D00);
    *(f32 *)(self + 0xF1C + 0xC) = 2.0f;
    *(f32 *)(self + 0xF1C + 0x8) = 0.0f;
    func_00349A60(self + 0xF1C, 1, func_00335E18(self));
    func_00349A70(0.0f, 0.0f, 0.0f, 0.0f, self + 0xF1C, 1, 0);
    func_00349A70(1.0f, 1.0f, 0.0f, 0.0f, self + 0xF1C, 1, 1);
    func_00349A60(self + 0xF1C, 2, func_00335E10(self));
    func_00349A70(50.0f, 25.0f, 0.0f, 0.0f, self + 0xF1C, 2, 0);
    func_00349A70(10.0f, 10.0f, 0.0f, 0.0f, self + 0xF1C, 2, 1);

    func_00349970(self + 0xFB0, arg);
    func_00349A60(self + 0xFB0, 0, func_00335E20(self + 0x4C));
    func_00349AA8(self + 0xFB0, 0, 0xF0C070);
    func_00349AA8(self + 0xFB0, 1, 0x55F0C070);
    *(f32 *)(self + 0xF1C + 0xC) = 3.0f;
    *(f32 *)(self + 0xF1C + 0x8) = 0.0f;
    func_00349A60(self + 0xFB0, 1, func_00335E18(self + 0x4C));
    func_00349A70(1.2f, 1.2f, 0.0f, 0.0f, self + 0xFB0, 1, 0);
    func_00349A70(1.0f, 1.0f, 0.0f, 0.0f, self + 0xFB0, 1, 1);
    func_00349A60(self + 0xFB0, 2, func_00335E10(self + 0x4C));
    func_00349A70(0.0f, 0.0f, 0.0f, 0.0f, self + 0xFB0, 2, 0);
    func_00349A70(10.0f, 10.0f, 0.0f, 0.0f, self + 0xFB0, 2, 1);

    func_00349970(self + 0x1044, arg);
    func_00349A60(self + 0x1044, 0, func_00335E20(self + 0x100));
    func_00349AA8(self + 0x1044, 0, 0xF0F0F0);
    func_00349AA8(self + 0x1044, 1, 0x80F0F0F0);
    *(f32 *)(self + 0x1044 + 0xC) = 3.0f;
    *(f32 *)(self + 0x1044 + 0x8) = 0.0f;

    func_003494D0(self + 0x10D8, arg);
    func_00349628(self + 0x10D8, 3);
    func_003495D8(0.0f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f, self + 0x10D8, 0);
    func_003495D8(0.5f, hud_bits_34B2C8(0x1EFF), 0.0f, 0.0f, 0.0f, self + 0x10D8, 1);
    func_003495D8(1.0f, hud_bits_34B2C8(0x80001EFF), 0.0f, 0.0f, 0.0f, self + 0x10D8, 2);
    func_00349590(self + 0x10D8, func_00335E20(self + 0x98));
    func_00349670(self + 0x10D8, 0);
    func_003495C0(self + 0x10D8, self + 0x1448);
    func_00349630(self + 0x10D8, 1);
    func_00349678(self + 0x10D8, 0.06666f);

    func_00349970(self + 0x1160, arg);
    func_00349A60(self + 0x1160, 0, func_00335E20(self + 0x148));
    func_00349AA8(self + 0x1160, 0, 0xF0F0B0);
    func_00349AA8(self + 0x1160, 1, 0x60F0F0B0);
    *(f32 *)(self + 0x1160 + 0xC) = 3.0f;
    *(f32 *)(self + 0x1160 + 0x8) = 0.0f;
    func_00349B18(self + 0x1160, 0.06666f);

    func_00349970(self + 0x11F4, arg);
    func_00349A60(self + 0x11F4, 0, func_00335E20(self + 0x184));
    func_00349AA8(self + 0x11F4, 0, 0x442D00);
    func_00349AA8(self + 0x11F4, 1, 0x60442D00);
    *(f32 *)(self + 0x11F4 + 0xC) = 2.0f;
    *(f32 *)(self + 0x11F4 + 0x8) = 0.0f;
    func_00349A60(self + 0x11F4, 1, func_00335E18(self + 0x184));
    func_00349A70(0.0f, 0.0f, 0.0f, 0.0f, self + 0x11F4, 1, 0);
    func_00349A70(1.0f, 1.0f, 0.0f, 0.0f, self + 0x11F4, 1, 1);
    func_00349A60(self + 0x11F4, 2, func_00335E10(self + 0x184));
    func_00349A70(458.0f, 25.0f, 0.0f, 0.0f, self + 0x11F4, 2, 0);
    func_00349A70(498.0f, 10.0f, 0.0f, 0.0f, self + 0x11F4, 2, 1);

    func_00349970(self + 0x1288, arg);
    func_00349A60(self + 0x1288, 0, func_00335E20(self + 0x1D0));
    func_00349AA8(self + 0x1288, 0, 0xF0C070);
    func_00349AA8(self + 0x1288, 1, 0x55F0C070);
    *(f32 *)(self + 0x1288 + 0xC) = 3.0f;
    *(f32 *)(self + 0x1288 + 0x8) = 0.0f;
    func_00349A60(self + 0x1288, 1, func_00335E18(self + 0x1D0));
    func_00349A70(1.2f, 1.2f, 0.0f, 0.0f, self + 0x1288, 1, 0);
    func_00349A70(1.0f, 1.0f, 0.0f, 0.0f, self + 0x1288, 1, 1);
    *(f32 *)(self + 0x1288 + 0x4) = 3.0f;
    *(f32 *)(self + 0x1288) = 0.0f;
    func_00349A60(self + 0x1288, 2, func_00335E10(self + 0x1D0));
    func_00349A70(514.0f, 4.0f, 0.0f, 0.0f, self + 0x1288, 2, 0);
    func_00349A70(498.0f, 10.0f, 0.0f, 0.0f, self + 0x1288, 2, 1);

    func_00349970(self + 0x131C, arg);
    func_00349A60(self + 0x131C, 0, func_00335E20(self + 0x238));
    func_00349AA8(self + 0x131C, 0, 0xF0F0F0);
    func_00349AA8(self + 0x131C, 1, 0x80F0F0F0);
    *(f32 *)(self + 0x131C + 0xC) = 3.0f;
    *(f32 *)(self + 0x131C + 0x8) = 0.0f;

    func_00349970(self + 0x13B0, arg);
    func_00349A60(self + 0x13B0, 0, func_00335E20(self + 0x280));
    func_00349AA8(self + 0x13B0, 0, 0xF0F0B0);
    func_00349AA8(self + 0x13B0, 1, 0x60F0F0B0);
    *(f32 *)(self + 0x13B0 + 0xC) = 3.0f;
    *(f32 *)(self + 0x13B0 + 0x8) = 0.0f;

    func_003494D0(self + 0x144C, arg);
    func_00349628(self + 0x144C, 2);
    func_00349590(self + 0x144C, func_00335E20(self));
    func_003495C0(self + 0x144C, self + 0x1448);
    func_00349678(self + 0x144C, 0.02f);
    func_003495D8(0.0f, hud_bits_34B2C8(0x70202080), 0.0f, 0.0f, 0.0f, self + 0x144C, 0);
    func_003495D8(1.0f, hud_bits_34B2C8(0x70242335), 0.0f, 0.0f, 0.0f, self + 0x144C, 1);
    func_00349670(self + 0x144C, 2);
    func_00349630(self + 0x144C, 1);
    func_003495C8(self + 0x144C, 0);

    func_003494D0(self + 0x14D4, arg);
    func_00349628(self + 0x14D4, 2);
    func_00349590(self + 0x14D4, func_00335E20(self + 0x4C));
    func_003495C0(self + 0x14D4, self + 0x1448);
    func_00349678(self + 0x14D4, 0.02f);
    func_003495D8(0.0f, hud_bits_34B2C8(0x606060C0), 0.0f, 0.0f, 0.0f, self + 0x14D4, 0);
    func_003495D8(1.0f, hud_bits_34B2C8(0x60424162), 0.0f, 0.0f, 0.0f, self + 0x14D4, 1);
    func_00349670(self + 0x14D4, 2);
    func_00349630(self + 0x14D4, 1);
    func_003495C8(self + 0x14D4, 0);

    *(s32 **)(self + 0x2BC) = &D_001A79F8;
    *(s32 *)(self + 0x1564) = 0;
    *(s32 *)(self + 0x1568) = -1;
    *(s32 *)(self + 0x156C) = 0;
    *(s32 *)(self + 0x1570) = -1;
    *(s32 *)(self + 0x1574) = 0;
    *(s32 *)(self + 0x1578) = -1;
    func_0034CA90(self, 0);
    *(s32 *)(self + 0x1588) = func_002B0D70();
}
