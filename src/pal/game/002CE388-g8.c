#include "common.h"

extern void func_0027C540(int);
extern void func_0027C660(void);
extern s32 func_00288FB8(s32);
extern void func_PAL_0029CB40(void);
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_PAL_001ABA40 __attribute__((sda));
extern int D_PAL_001ABA44[] __attribute__((sda));

extern int func_0027F980(int v, int p7, unsigned long long k, char *r, int m1);

extern void func_002A0250(void);

extern void func_002A01C8(void);

extern void func_002A01F0(void);

extern void func_002A0220(void);

extern int func_002A0380(void);

extern void func_0034EBE0(void *);

extern void func_0034EC70(void *);

extern void func_PAL_00350E98(char *);

extern void func_0034EDB0(void *, char *);

extern void func_002FC3C0(u64);

extern void func_0029FEE0(void);

/* func_PAL_002CE388, the PAL copy of func_002CD3C0: the same C, where the text
 * position comes from two PAL words (469, 359) in place of 0x1B5 and the scaled
 * 367, the string id becomes 0xB60 and the owner field moves to +0x3FA9C. Retail
 * reads the first word through $gp and the second through lui, as it does the
 * next pair at 0x1ABA48 in func_PAL_002CE9BC, hence the two declaration forms. */
int func_PAL_002CE388(void)
{
    func_0027C540(0);
    func_PAL_0029CB40();
    func_0027F980(D_PAL_001ABA40, D_PAL_001ABA44[0], 0x80F0F0F0ULL, (char *)func_00288FB8(0xb60), -1);
    func_0027C660();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7a9c) != 0) {
            char *owner;
            func_002A0250();
            func_002A01C8();
            func_002A01F0();
            owner = *(char **)(D_001A8CFC[0] + 0x38000 + 0x7a9c);
            func_0034EBE0(owner);
            func_0034EC70(owner);
            func_PAL_00350E98(owner);
            func_0034EDB0(owner, owner + 0xC00);
            func_002A0220();
            func_002A0380();
            func_002FC3C0(0x10);
            func_0029FEE0();
        }
    }
    return 0;
}
