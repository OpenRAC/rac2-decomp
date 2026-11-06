/* func_US2_L01_002A8D48, the USA v2.00 copy of func_L01_002A8C48: the same update, with the pad's
   held and pressed words masked while the player's 0x1E0 timer runs and restored on every exit. */

#include "common.h"

extern char D_00138180[];
extern char D_00189E20[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char D_00189EA0[];

extern void func_L01_002A84D8(void);
extern void func_2C7CA8(void);
extern void func_L00_002B36E0(void);
extern void func_L01_002ADDC8(void);
extern void func_L01_002AE128(char *a0, char *a1, char *a2);
extern void func_US2_L01_002C3B08(void);
extern void func_2C8628(void);
extern void func_L00_002D3068(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void func_L00_002AA178(int a0);
extern void func_L00_002B2120(void);
extern void func_US2_L00_002B2408(void);
extern void func_US2_L00_002B22D0(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void func_US2_L00_002A67F8(void);
extern void func_US2_L00_002D6258(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_30F444(int a0);
extern void func_L01_002A9298(void);
extern void func_2AB328(void);

void func_US2_L01_002A8D48(void) {
    char *pad;
    char *player;
    char *p;
    int held;
    int pressed;
    int timer;
    int masked;
    int masked_pressed;

    pad = D_00138180;
    player = D_00189E20;
    held = *(int *)(pad + 0x1A0);
    pressed = *(int *)(pad + 0x1A4);
    timer = *(short *)(player + 0x1E0);
    /* Tested through the value being built, so jump1 keeps both arms and cse1 stops at their join. */
    masked = timer;
    if (masked != 0)
        masked = 0;
    else
        masked = *(int *)(pad + 0x1A0);
    *(int *)(pad + 0x1A0) = masked;
    masked_pressed = 0;
    if (timer == 0)
        masked_pressed = *(int *)(pad + 0x1A4);
    *(int *)(pad + 0x1A4) = masked_pressed;
    p = D_00189E20;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        func_L01_002A84D8();
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    func_2C7CA8();
    func_L00_002B36E0();
    func_L01_002ADDC8();
    func_L01_002AE128(p + 0x80, p + 0x90, p + 0x550);
    func_US2_L01_002C3B08();
    if (D_L01_001A8F40 == 2 || D_L01_001A8F40 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_2C8628();
        else
            func_L00_002D3068();
        {
            char *q = D_00138180;
            *(int *)(q + 0x1A0) = held;
            *(int *)(q + 0x1A4) = pressed;
        }
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    func_2B9878();
    func_L00_002AC1A0();
    func_L00_002AB1D8();
    func_L00_002AB420();
    func_L00_002ABBA0();
    func_L00_002AB948();
    func_L00_002A5518();
    func_L00_002A5840();
    func_L00_002B7718();
    func_2A7740();
    func_2AB028();
    func_L00_002AA178(0);
    func_L00_002B2120();
    func_US2_L00_002B2408();
    func_US2_L00_002B22D0();
    func_L00_002AFBC0();
    {
        char *q = D_00189E20;
        if (*(unsigned char *)(q + 0x22B5) != 0 || func_L00_002D6418() != 0)
            func_2C8628();
        else
            func_L00_002D3068();
    }
    func_2A9520();
    func_2A9310();
    func_US2_L00_002A67F8();
    func_US2_L00_002D6258();
    func_L00_002A6420();
    func_L00_002D5158();
    {
        char *q = D_00189E20;
        if ((*(int *)(q + 0x229C) != 0x16 && *(int *)(q + 0x229C) != 0x1F
             && *(int *)(q + 0x2294) != 0x31) || func_L00_002A7000() != 0)
            func_L00_003080D0(D_00189EA0);
    }
    {
        char *q = D_00189E20;
        func_30F444(*(int *)(q + 0x2290));
    }
    func_L01_002A9298();
    func_2AB328();
    {
        char *q = D_00138180;
        *(int *)(q + 0x1A0) = held;
        *(int *)(q + 0x1A4) = pressed;
    }
}
