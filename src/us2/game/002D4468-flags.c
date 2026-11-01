#include "include_asm.h"

typedef struct {
    char pad00[6];
    short f06;
    char pad08[0x3A];
    short f42;
    char pad44[0x9C];
} ClassRecord;
extern char *D_001A8CFC __attribute__((sda));
extern unsigned char D_00139568[];
extern ClassRecord D_00239BA0[];
extern void func_US2_00342460(void *, int);
extern int func_US2_00344480(unsigned char *);
extern char *func_US2_003444C8(char *);

int func_US2_002D4568(char *object)
{
    char *target;
    int i;

    if (D_001A8CFC != 0) {
        func_US2_00342460(D_001A8CFC + 0x3C160, 1);
        i = func_US2_00344480((unsigned char *)D_001A8CFC + 0x3C480);
        {
            ClassRecord *r = &D_00239BA0[D_00139568[i]];
            int v = r->f42;
            char *a = D_001A8CFC + 0x3C480;
            *(int *)(object + 0x34) = v;
            target = func_US2_003444C8(a);
        }
        i = func_US2_00344480((unsigned char *)D_001A8CFC + 0x3C480);
        *(int *)(target + 0x58) = D_00239BA0[D_00139568[i]].f06;
    }
    return 0;
}
