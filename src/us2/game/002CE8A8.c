#include "include_asm.h"

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_00341550(void *, int);
extern char *D_001A8CFC[] __attribute__((sda));
extern void *func_00341558(void *);
extern char *D_001A8CFC[] __attribute__((sda));

int func_US2_002CE8A8(void *object) { char *root=D_001A8CFC[0]; if (root != 0) { func_00341550(root+0x3C160,1); *(void **)((char *)object+0x34)=func_00341558(D_001A8CFC[0]+0x3C160); } return 0; }

INCLUDE_ASM("asm/us2/game", func_US2_002CE9D4);

extern void func_US2_00342460(void *, int);
extern void func_US2_00342450(char *, char *, char *, char *);
extern void func_US2_00342520(char *, int);
extern char D_002615F8[];
extern char D_00261698[];
extern char D_00261750[];

int func_US2_002CEA38(void)
{
    if (D_001A8CFC[0] != 0) {
        func_US2_00342460(D_001A8CFC[0] + 0x3C160, 1);
        func_US2_00342450(D_001A8CFC[0] + 0x3C160, D_002615F8, D_00261698, D_00261750);
        func_US2_00342520(D_001A8CFC[0] + 0x3C160, 0);
    }
    return 0;
}

