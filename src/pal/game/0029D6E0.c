#include "include_asm.h"

extern char D_001BAEC0[];
extern int D_00138180[];
extern int D_001A79F0 __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern char *D_001A8CFC __attribute__((sda));
extern void *func_00115484(void *, int, int);
extern void func_0029CD20(int);
extern int *func_00336DA8(int, int);
extern char *func_PAL_003507A8(int *, int);
extern void func_0029C0D0(void);
extern void func_PAL_0029CAA0(void);
extern void func_PAL_0029CA70(void);
extern void func_0029CD18(void);
typedef struct { char pad[0x7A84]; void *cb1; void *cb2; } SubBf;

void func_PAL_0029D6E0(void)
{
    char *state = D_001BAEC0;
    char *obj;

    func_00115484(*(void **)(state + 0x80), 0xCD, 0x40000);
    D_00138180[104] = 0;
    D_00138180[105] = 0;
    D_00138180[106] = 0;
    D_00138180[107] = 0;
    D_00138180[108] = 0;
    D_00138180[109] = 0;
    D_00138180[110] = 0;
    D_00138180[111] = 0;
    D_00138180[112] = 0;
    D_00138180[113] = 0;
    D_00138180[114] = 0;
    D_00138180[115] = 0;
    func_0029CD20(D_001A7B90[0]);
    obj = func_PAL_003507A8(func_00336DA8(0x3FBD0, *(int *)(state + 0x80)), 0x40000);
    D_001A8CFC = obj;
    if (D_001A79F0 == 0x1F5) {
        ((SubBf *)(obj + 0x38000))->cb1 = func_0029C0D0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_0029CD18;
    } else {
        ((SubBf *)(obj + 0x38000))->cb1 = func_PAL_0029CAA0;
        ((SubBf *)(obj + 0x38000))->cb2 = func_PAL_0029CA70;
    }
}


