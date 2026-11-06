/* func_PAL_002D1488, the PAL copy of func_002D0568: the same C, with four slots in place
   of five, three rows from y 290 spaced 24 apart and the other text ids. */
#include "common.h"

extern char *D_001A8CFC;
extern int D_001A7340;
extern int D_001ABA1C __attribute__((sda));
extern int D_001ABA04 __attribute__((sda));
extern int D_001ABA08[] SDATA(D_001ABA08);
extern short D_001ABD00[] MACRO_ADDR;
extern float D_001B23A8;
extern void func_0027C540(long);
extern void func_0027C660(void);
extern char *func_00336D50(char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern char *func_00288FB8(int);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern int func_0027FB40(int, int, unsigned long, char *, int);
extern int func_001157AC(char *);
extern int func_0027F198(char *, int);
extern void func_002CEBD0(void);
extern void func_002CF0A0(int, unsigned int);

int func_PAL_002D1488(void)
{
    int i, y = 290;
    float z;

    func_0027C540(0);
    z = 0.0f;
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xD7), 0x60442D00, (float)(D_001A7340 / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xD8), 0x60241700, (float)(D_001A7340 / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xD9), 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    func_00300A00(func_00336D50(D_001A8CFC + 0x8710, 0xDD), 0x55F0C070, (float)(D_001A7340 / 2), (float)D_001ABA1C, 1.0f, D_001B23A8, z);
    func_0027FAA8(179, 27, 0x80F0F0F0UL, func_00288FB8(0x1111), -1);
    func_0027FAA8(353, 375, 0x80F0F0F0UL, func_00288FB8(0xB60), -1);
    func_0027FAA8(181, 375, 0x80F0F0F0UL, func_00288FB8(0xB86), -1);
    func_002CEBD0();
    for (i = 0; i < 3; i++, y += 24) {
        int index = i + D_001ABA04 - 1, key;
        unsigned int color;
        char *text;

        if (index < 0)
            index += 4;
        if (index >= 4)
            index -= 4;
        key = D_001ABA08[index] ? D_001ABD00[index * 2] : 0xBD1;
        text = func_00288FB8(key);
        if (i == 0 || i == 2)
            color = 0x30F0F0F0;
        else {
            color = 0x70F0F0F0;
            func_002CF0A0(func_0027F198(text, func_001157AC(text)), 0x70F0F0F0);
        }
        func_0027FB40(D_001A7340 / 2, y, color, text, -1);
    }
    func_0027C660();
    return 0;
}
