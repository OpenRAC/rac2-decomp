/* func_L19_00422238 - 488 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Goes in L19_00422178-q.c (needs -frac2-qcopy flags). Only schedule differs
   (6 masked lines):
   retail loads the 0.0033333334f f14 constant (lui/ori/mtc1) before `daddu
   a3,s0`, mul.s f13 and `lw t3,0x2C(s4)`;
   mine puts lw t3, daddu a3, mul.s first and the constant last. Tried: locals
   sz/spd, inline args, mul order. */

extern char D_L19_001A8F20[] __attribute__((sda));
extern int func_00318380(int lo, int hi);
extern float func_003183D8(float lo, float hi);
extern int func_002ECAD0(int a0, int a1, float f12);
extern void func_0033D670(float *a0, float *a1, int a2, int a3, int t0, int t1, int t2, int t3,
                          float f12, float f13, float f14);

void func_L19_00422238(u8 *a0)
{
    u8 *s4 = *(u8 **)(a0 + 0x68);
    float pos[4];
    float vel[4];
    int color;
    int alpha;
    int c1;
    int c2;

    while (1.0f < *(float *)(s4 + 0x24)) {
        *(float *)(s4 + 0x24) -= 1.0f;
        *(TI128 *)vel = *(TI128 *)D_L19_001A8F20;
        func_L19_00422178(a0, pos);
        if (a0[0x20] == 3 && func_00318380(0, 1) != 0)
            pos[2] = *(float *)(s4 + 4);
        else
            vel[2] = *(float *)(s4 + 0xC) * 0.5f;
        pos[2] = pos[2] + 6.0f;
        color = func_002ECAD0(*(int *)(s4 + 0x38), *(int *)(s4 + 0x34), func_003183D8(0.0f, 1.0f));
        alpha = color >> 24;
        c1 = func_00318380(*(int *)(s4 + 0x40) / 2, *(int *)(s4 + 0x40));
        color &= 0xFFFFFF;
        c2 = func_00318380(0, *(int *)(s4 + 0x3C));
        {
            float sz = func_003183D8(0.5f, 1.0f) * *(float *)(s4 + 0x30);
            func_0033D670(pos, vel, c1, color, c2, alpha, 0, *(int *)(s4 + 0x2C), sz,
                          *(float *)(s4 + 0x30) * func_003183D8(0.7f, 1.0f), 0.0033333334f);
        }
    }
}
