/* func_L01_003D68C0 - 572 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   2 masked diff lines (case 3): retail `lhu; sb 0x31; ori; sw 0x98`, draft
   `lhu; sb; sw 0x98; ori`. Everything else matches.
   Key finds: all five globals are `extern T X[] __attribute__((sda))` read as
   X[0] (tied absolute macro form; loads/stores in delay slots become $gp);
   counter read must come BEFORE the stores that precede it in retail
   (explicit `cnt = D[0]` / `fl = flags` locals) - plain D[0]++ keeps lhu
   below sw D.
   Tried for the last swap: sb/sw98 source order, fl computed before/after the
   cnt read, fl|1 computed early. */

/* in L01_003CAFE0.c, needs common.h include (its u8..f32 typedefs removed), func_00282948 declared s32-returning. Decls: */
extern s32 D_L01_001AEC38[] __attribute__((sda));
extern s32 D_L01_001B3468[] __attribute__((sda));
extern s32 D_L01_001B15E0[] __attribute__((sda));
extern f32 D_L01_001B208C[] __attribute__((sda));
extern f32 D_L01_001B2090[] __attribute__((sda));
extern s32 func_002E5CF8(s32 a0, s32 a1, void *a2);
extern s32 func_002B3868(void *a0);
extern void func_L00_00326110(void *a0, s32 a1, f32 a2);
extern void func_L00_00326620(void *a0, s32 a1, s32 a2);
extern void func_L01_003D6B00(void *a0, s32 a1, f32 a2, f32 a3, f32 a4, f32 a5);
void func_L01_003D68C0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0: {
        s32 cnt = D_L01_001AEC38[0];
        u16 fl = *(u16 *)(a0 + 0x34);
        D_L01_001AEC38[0] = cnt + 1;
        *(u16 *)(a0 + 0x34) = fl | 0x800;
        func_002A7750(a0, 1, -1);
        break;
    }
    case 1:
        if (func_002A9640(a0, 0x04010000, 0) != 0 && *(s32 *)state == 0) {
            D_L01_001AEC38[0] = D_L01_001AEC38[0] - 1;
            func_002A7750(a0, 2, -1);
        }
        a0[0xA8] = 0xFF;
        break;
    case 2:
        if (a0[0x31] != 0 && D_L01_001B2090[0] < 0.9f && D_L01_001B208C[0] < 0.9f &&
            D_L01_001B3468[0] < D_L01_001B15E0[0])
            func_L01_003D6B00(a0, 0xF, 1.5f, 6.5f, 1.5f, 0.06666667f);
        else
            func_L01_003D6B00(a0, 6, 1.5f, 6.5f, 1.5f, 0.06666667f);
        func_002E5CF8(0, 0, a0);
        func_L00_00326110(a0, 1, 0.0f);
        func_L00_00326620(a0, 0xF94, 0);
        func_002A7750(a0, 3, -1);
        break;
    case 3:
        if (func_002B3868(a0) != 0) {
            s32 cnt;
            u16 fl;

            fl = *(u16 *)(a0 + 0x34);
            a0[0x31] = 0;
            *(s32 *)(a0 + 0x98) = 0;
            cnt = D_L01_001B3468[0];
            *(u16 *)(a0 + 0x34) = fl | 1;
            *(s32 *)(state + 4) = 0x78;
            D_L01_001B3468[0] = cnt + 1;
        }
        if (func_00282948(state + 4) != 0) {
            D_L01_001B3468[0] = D_L01_001B3468[0] - 1;
            func_0029F338(a0);
        }
        break;
    }
}
