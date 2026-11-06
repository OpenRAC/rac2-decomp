#include "include_asm.h"
/* func_US2_L03_002AD640, the USA v2.00 copy of func_L03_002AD540: the same update, with the pad's
   held and pressed words masked while the player's 0x1E0 timer runs and restored on every exit. */

#include "common.h"

extern char D_00138180[];
extern char D_00189E20[];
extern int D_L03_001A8F00 MACRO_ADDR;
extern char D_00189EA0[];

extern void ref_L03_002AD540_00(void);
extern void func_L00_002D24E8(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
extern void func_L00_002D2E68(void);
extern void func_L00_002D3068(void);
extern void func_L00_002AE0C8(void);
extern void func_L00_002B9CA8(void);
extern void func_L00_002AC1A0(void);
extern void func_L00_002AB1D8(void);
extern void func_L00_002AB420(void);
extern void func_L00_002ABBA0(void);
extern void func_L00_002AB948(void);
extern void func_L00_002A5518(void);
extern void func_L00_002A5840(void);
extern void func_L00_002B7718(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9460(void);
extern void func_L00_002AA178(int a0);
extern void func_L00_002B2120(void);
extern void func_US2_L00_002B2408(void);
extern void func_US2_L00_002B22D0(void);
extern void func_L00_002AFBC0(void);
extern int func_L00_002D6418(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_US2_L00_002A67F8(void);
extern void func_US2_L00_002D6258(void);
extern void func_L00_002A6420(void);
extern void func_L00_002D5158(void);
extern int func_L00_002A7000(void);
extern void func_L00_003080D0(void *a0);
extern void func_002A677C(int a0);
extern void ref_L03_002AD540_06(void);
extern void func_L00_002A9760(void);

void func_US2_L03_002AD640(void) {
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
        ref_L03_002AD540_00();
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    func_L00_002D24E8();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(p + 0x80, p + 0x90, p + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (D_L03_001A8F00 == 2 || D_L03_001A8F00 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_L00_002D2E68();
        else
            func_L00_002D3068();
        {
            char *q = D_00138180;
            *(int *)(q + 0x1A0) = held;
            *(int *)(q + 0x1A4) = pressed;
        }
        return;
    }
    func_L00_002AE0C8();
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    func_L00_002B9CA8();
    func_L00_002AC1A0();
    func_L00_002AB1D8();
    func_L00_002AB420();
    func_L00_002ABBA0();
    func_L00_002AB948();
    func_L00_002A5518();
    func_L00_002A5840();
    func_L00_002B7718();
    func_L00_002A5368();
    func_L00_002A9460();
    func_L00_002AA178(0);
    func_L00_002B2120();
    func_US2_L00_002B2408();
    func_US2_L00_002B22D0();
    func_L00_002AFBC0();
    {
        char *q = D_00189E20;
        if (*(unsigned char *)(q + 0x22B5) != 0 || func_L00_002D6418() != 0)
            func_L00_002D2E68();
        else
            func_L00_002D3068();
    }
    func_L00_002A7958();
    func_L00_002A7748();
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
        func_002A677C(*(int *)(q + 0x2290));
    }
    ref_L03_002AD540_06();
    func_L00_002A9760();
    {
        char *q = D_00138180;
        *(int *)(q + 0x1A0) = held;
        *(int *)(q + 0x1A4) = pressed;
    }
}
