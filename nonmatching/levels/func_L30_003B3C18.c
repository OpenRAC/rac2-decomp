/* func_L30_003B3C18 - 580 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Draft = split num/den variant for a -g unit. Without -g (in the
   L30_0032AAF0-g8.c sibling, calls nested, angle temp in-place `angle *= K`):
   572 vs 580 bytes, only diffs: no `nop; nop` before the div.s (retail has
   them) and f2/f0 reg choice in the angle multiply.
   The nop pair needs a code label right before div.s (docs/COMPILER-NOTES.md
   "Division/root scheduling": -g line label). With -g (statement split num =
   D93C*angle; den = D8C8*1/60; rot = f(num/den, ...)) the nop pair appears,
   but -g line notes stop the delay-slot fill of `daddu s1,v0` (retail has it
   in the jal delay slot, so retail has no line note there) and add an extra
   jal-result move: 596 bytes.
   Calls/types: func_0027C878 returns long,
   27E018(int,int,int,int,int,int,int,int,long long,long long), 27E4A8(float
   x5,int,int,long,int,int,int,int,float,float). gp names
   D_L30_001AF92C..AF94C, AF8C8. */

#include "common.h"

/* Needs the small-data profile (-G8) and -g, which gives the nop pair before div.s. */

extern int D_L30_001AF930 __attribute__((sda));
extern int D_L30_001AF934 __attribute__((sda));
extern int D_L30_001AF938 __attribute__((sda));
extern int D_L30_001AF92C __attribute__((sda));
extern float D_L30_001AF93C __attribute__((sda));
extern float D_L30_001AF940 __attribute__((sda));
extern float D_L30_001AF944 __attribute__((sda));
extern float D_L30_001AF948 __attribute__((sda));
extern float D_L30_001AF94C __attribute__((sda));
extern float D_L30_001AF8C8 __attribute__((sda));
extern int D_001A7344;

extern long func_0027C878(int);
extern void func_0027E018(int, int, int, int, int, int, int, int, long long, long long);
extern float func_00282DF0(void *);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_0027E4A8(float, float, float, float, float, int, int, long, int, int, int, int, float, float);

void func_L30_003B3C18(char *object) {
    char *state = *(char **)(object + 0x68);
    long tex;
    float rot;
    float angle;
    float num;
    float den;

    tex = func_0027C878(D_L30_001AF930 + 0x12); func_0027E018(func_00283CF0(D_L30_001AF94C), D_001A7344 - 0x80, 0x80, 0x80, 0, 0, 0x80, 0x80, D_L30_001AF92C, tex); tex = func_0027C878(D_L30_001AF934 + 0x12); func_0027E018(func_00283CF0(D_L30_001AF94C) + 0x80, D_001A7344 - 0x80, 0x80, 0x80, 0, 0, 0x80, 0x80, D_L30_001AF92C, tex); tex = func_0027C878(D_L30_001AF938 + 0x12); angle = func_00282DF0(state); angle *= 0.01745329424738884f; num = D_L30_001AF93C * angle; den = D_L30_001AF8C8 * 0.016666668f;
    rot = func_00283B98(num / den, D_L30_001AF940 * 0.01745329424738884f);
    func_0027E4A8(D_L30_001AF94C + 64.0f, (float)(D_001A7344 - 0x40), 64.0f, 64.0f, rot, 0x40, 0x40,
                  tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
    angle = func_00282C48(*(float *)(state + 0x4C));
    angle *= 0.01745329424738884f;
    rot = func_00283B98(D_L30_001AF948 * 0.01745329424738884f, D_L30_001AF944 * angle);
    func_0027E4A8(D_L30_001AF94C + 128.0f + 64.0f, (float)(D_001A7344 - 0x40), 64.0f, 64.0f, rot,
                  0x40, 0x40, tex, 0xFFFFF3, 0x60808080, 0, 0, 0.5f, 0.35f);
}
