/* func_PAL_L05_00328198, the PAL copy of func_L05_003263F8: the same store of value + 1,
   scaled to 50 Hz, with a new test that skips it while D_0018A000 is positive. */
typedef int s32;

extern short D_0018A000[];
extern int D_L05_001A9CD0 __attribute__((sda));

void func_PAL_L05_00328198(int value) {
    if (D_0018A000[0] <= 0) {
        D_L05_001A9CD0 = ((s32)(value + 1) * 5 + 2) / 6;
    }
}
