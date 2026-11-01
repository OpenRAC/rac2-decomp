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
extern void func_PAL_003435D0(void *, int);
extern int func_PAL_003455D8(unsigned char *);
extern char *func_PAL_00345620(char *);

int func_PAL_002D4530(char *object)
{
    char *target;
    int i;

    if (D_001A8CFC != 0) {
        func_PAL_003435D0(D_001A8CFC + 0x3C210, 1);
        i = func_PAL_003455D8((unsigned char *)D_001A8CFC + 0x3C530);
        {
            ClassRecord *r = &D_00239BA0[D_00139568[i]];
            int v = r->f42;
            char *a = D_001A8CFC + 0x3C530;
            *(int *)(object + 0x34) = v;
            target = func_PAL_00345620(a);
        }
        i = func_PAL_003455D8((unsigned char *)D_001A8CFC + 0x3C530);
        *(int *)(target + 0x58) = D_00239BA0[D_00139568[i]].f06;
    }
    return 0;
}
