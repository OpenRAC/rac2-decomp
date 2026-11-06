/* func_PAL_L00_002B20F8, the PAL copy of func_L00_002B2200: the same C, where the call ids
 * move up four, 300 becomes 250, and the last call runs once, behind a byte at +0xAB of
 * D_001395B8 that it sets. */
#include "common.h"

extern int D_L00_001A903C;
extern int D_L00_001A7F8C __attribute__((sda));
extern u8 D_001A7BE0;
extern u8 D_001A7A60[] MACRO_ADDR;
extern u8 D_001395B8[];
extern int func_00282948(char *);
extern int func_002B0E90(void);
extern int func_L00_002F43D0(void);
extern void func_PAL_002B1588(int, int);

void func_PAL_L00_002B20F8(void)
{
    int count;
    int selector;
    int flag;
    u8 *state;

    if (D_L00_001A903C == 0)
        return;
    if (func_00282948((char *)&D_L00_001A7F8C) == 0)
        return;
    count = func_002B0E90();
    selector = func_L00_002F43D0();
    flag = D_001A7BE0;
    if (flag != 0 || selector > 0) {
        if (count == 3 || count == 10 || count == 15 || count == 19 || count == 25 || count == 29)
            func_PAL_002B1588(0x1b90, -1);
        else if (count == 18 || count == 26)
            func_PAL_002B1588(0x1b91, -1);
    }
    if (count == 7 || count == 20 || count == 30)
        func_PAL_002B1588(0x1b93, -1);
    state = D_001395B8;
    if (state[0xAB] == 0) {
        if (D_001A7A60[0] != 0) {
            func_PAL_002B1588(0x1b93, -1);
            state[0xAB] = 1;
        }
    }
    D_L00_001A903C = 0;
    D_L00_001A7F8C = 250;
}
