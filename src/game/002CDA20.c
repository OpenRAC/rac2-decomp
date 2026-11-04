#include "common.h"

extern void func_0027C540(int);
extern void func_0029C4C0(void);
extern float D_001B23A4[] __attribute__((sda));
extern s32 func_00288FB8(s32);
extern int func_0027FAA8(int, int, u64, u8 *, int);
extern void func_0027C660(void);

/* Draw the centered panel text in scaled screen coordinates. */
int func_002CDA20(void)
{
    float position;
    int y;

    func_0027C540(0);
    func_0029C4C0();
    position = 293.0f;
    y = (int)(D_001B23A4[0] * position + 0.5f);
    /* One-pass text draw group after coordinate conversion. */
    do {
        func_0027FAA8(0x1A5, y, 0x80F0F0F0ULL, (u8 *)func_00288FB8(0x2D4F), -1);
    } while (0);
    func_0027C660();
    return 0;
}
