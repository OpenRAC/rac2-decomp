#include "include_asm.h"


typedef unsigned char u8;
typedef unsigned short u16;
extern int func_00282948(void *);
extern void func_L00_002E6EF8(char *, char *);
extern void func_L00_0030CF60(void);
extern char D_L02_004004D8[];
extern u8 D_001395B8[];

void func_PAL_L02_003FF640(char *a0) {
    char *s0 = a0;
    char *obj = *(char **)(s0 + 0x68);
    u16 timer = *(u16 *)(s0 + 0x96);

    if (timer <= 0xFFFE)
        *(u16 *)(s0 + 0x96) = timer + 1;
    func_00282948(obj + 0xE4);
    if (*(u8 *)(s0 + 0x20) > 1)
        func_L00_002E6EF8(D_L02_004004D8, s0);
    func_L00_0030CF60();
}

