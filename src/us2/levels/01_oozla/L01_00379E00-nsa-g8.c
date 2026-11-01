#include "include_asm.h"

#include "common.h"
extern int D_L01_001AEC38 __attribute__((sda));
extern int D_L01_001B2088 MACRO_ADDR;
extern unsigned char D_001A7A6F __attribute__((nosda));
extern int D_L01_001A907C MACRO_ADDR;
extern int func_002E5E58(int, unsigned int, void *);
extern void func_US2_002B1880(int, int);

/* Once the level's mode word reaches 6 and the timer at D_L01_001AEC38 has run out, raises the
   one-shot flag and starts the sequence (mode 2 first rearms the timer to 0x42). A fresh
   object (state 0) clears its byte at +0x30. */
void func_US2_L01_00379E00(char *arg0) {
    if (*(unsigned char *)(arg0 + 0x20) == 0)
        *(unsigned char *)(arg0 + 0x30) = 0xFF;
    if (D_L01_001B2088 == 2)
        D_L01_001AEC38 = 0x42;
    if (D_L01_001B2088 < 6)
        return;
    if (D_L01_001AEC38 > 0)
        return;
    if (D_001A7A6F != 0)
        return;
    D_001A7A6F = 1;
    func_002E5E58(1, 0, 0);
    func_US2_002B1880(0x1233, -1);
    D_L01_001A907C = 1;
}
