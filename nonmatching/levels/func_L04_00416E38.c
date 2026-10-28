/* func_L04_00416E38 - 492 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   First-compile draft (472 B vs 492 B). Calls/args all identified
   (func_3092E8, func_32D030, func_30AAB8 with stack arg 3, func_30A9D8,
   func_3153B0, func_30A318).
   Open: retail recomputes (int)(D*263+.5) etc. after each call and keeps
   263/371/0.5 in f22/f21/f20; mine shares the float/int conversions of the
   first call and uses another f-reg order. Nothing else tried. */

extern float D_L04_001B2D44 __attribute__((sda));
extern int D_001A7340;
extern void func_3092E8(int a0, int a1, int a2, int a3, int t0, int t1);
extern void func_32D030(int a0, int a1, float f12, float f13, float f14, float f15);
extern void func_30AAB8(void *a0, int a1, int a2, int a3, int t0, int t1, int t2, int t3, int mode);
extern int func_3153B0(int a0);
extern void func_30A9D8(void *a0, int a1, int a2, int a3);
extern void func_30A318(int a0, int a1, int a2, int a3, int t0);

void func_L04_00416E38(void)
{
    char box[0x50];
    int x;
    int y;

    func_3092E8((int)(D_L04_001B2D44 * 263.0f + 0.5f), (int)(D_L04_001B2D44 * 371.0f + 0.5f), 0x82, 0x180,
                0x60, 0x60442D00);
    func_32D030(0x60, 0x55F0C070, (float)(int)(D_L04_001B2D44 * 263.0f + 0.5f),
                (float)(int)(D_L04_001B2D44 * 371.0f + 0.5f), 130.0f, 384.0f);
    func_30AAB8(box, (int)(D_L04_001B2D44 * 222.0f + 0.5f), (int)(D_L04_001B2D44 * 479.0f + 0.5f), 0x2C,
                0x1D4, 0x100, 0x12B, 0x10, 3);
    func_30A9D8(box, 0x80F0F0F0, func_3153B0(0xA41), -1);
    x = D_001A7340 / 2;
    y = (int)(D_L04_001B2D44 * 349.0f + 0.5f);
    func_30A318(x, y, 0x80F0F0F0, func_3153B0(0x2F2C), -1);
}
