/* func_L03_003D0300 - 480 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   Goes at the end of L03_00399230-g8.c. First draft 468 B vs 480 B. Logic
   decoded (states 0, 1, 2/3 with movz step 2 or 8; ring scan over
   D_L03_001C3E40 of func_2E1C70 results).
   Open: retail lays the case 2/3 block (movz) LAST and case 0 right after the
   dispatch tree; mine puts the 2/3 block first. Try separate case 2 / case 3
   or if-chain; also missing the `addiu a1,gp,0x1590` form (address of a gp
   variable). */

extern int D_L03_001B2548[] __attribute__((sda));
extern float D_L03_001B0580[4] __attribute__((sda));
extern char *D_L03_001C3E40[];
extern s32 func_2DC9B0(char *a0);
extern void func_31B920(char *a0, s32 a1, s32 a2);
extern s32 func_2E1C70(char *a0, s32 a1, char *a2, s32 a3, float f12);
extern float func_2EF190(char *a0, float *a1);

void func_L03_003D0300(char *a0)
{
    s32 n;
    s32 step;
    char **p;
    char *pos;

    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        if (func_2DC9B0(a0) != 0) {
            func_31B920(a0, 1, -1);
            *(u16 *)(a0 + 0x34) |= 0x2000;
        }
        break;
    case 1:
        pos = a0 + 0x10;
        if ((D_L03_001B2548[0] & 0xF) == (((s32)a0 >> 8) & 0xF)) {
            n = func_2E1C70(pos, 0, a0, 0, 0.2f);
            p = D_L03_001C3E40;
            for (; n > 0; n--, p++) {
                if (*(s16 *)(*p + 0xAA) == 0xFF3 || *(s16 *)(*p + 0xAA) == 0xFFD)
                    func_31B920(a0, 3, -1);
            }
        }
        if (func_2EF190(pos, D_L03_001B0580) < 0.3f)
            func_31B920(a0, 3, -1);
        if ((*(u16 *)(a0 + 0x96))++ >= 0x259) {
            if (*(u8 *)(a0 + 0x31) == 0)
                func_31B920(a0, 2, -1);
        }
        break;
    case 2:
    case 3:
        step = *(u8 *)(a0 + 0x20) == 2 ? 2 : 8;
        if (*(u8 *)(a0 + 0x23) < step)
            func_311758(a0);
        else
            *(u8 *)(a0 + 0x23) -= step;
        break;
    }
}
