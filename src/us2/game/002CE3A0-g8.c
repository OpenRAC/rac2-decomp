#include "common.h"

/* func_US2_002CE3A0, the USA v2.00 copy of func_002CD3C0: the same C, where the text position
   (437, 367 in the data) comes from a pair of globals, the string becomes 0x2BE5 and the owner
   field moves by 0x688. */

extern void func_0027C540(int);
extern void func_0027C660(void);
extern s32 func_00288FB8(s32);
extern int D_US2_001AB9D8 __attribute__((sda));
extern int D_US2_001AB9DC[] __attribute__((sda));
extern void func_US2_0029CFE0(void);
extern char *D_001A8CFC[] __attribute__((sda));

extern int func_0027FAA8(int v, int p7, unsigned long long k, char *r, int m1);

extern void func_002A0250(void);

extern void func_002A01C8(void);

extern void func_002A01F0(void);

extern void func_002A0220(void);

extern int func_002A0380(void);

extern void func_0034EBE0(void *);

extern void func_0034EC70(void *);

extern void func_US2_0034F9F8(char *);

extern void func_0034EDB0(void *, char *);

extern void func_002FC3C0(u64);

extern void func_0029FEE0(void);

int func_US2_002CE3A0(void)
{
    func_0027C540(0);
    func_US2_0029CFE0();
    func_0027FAA8(D_US2_001AB9D8, D_US2_001AB9DC[0], 0x80F0F0F0ULL, (char *)func_00288FB8(0x2BE5), -1);
    func_0027C660();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x79EC) != 0) {
            char *owner;
            func_002A0250();
            func_002A01C8();
            func_002A01F0();
            owner = *(char **)(D_001A8CFC[0] + 0x38000 + 0x79EC);
            func_0034EBE0(owner);
            func_0034EC70(owner);
            func_US2_0034F9F8(owner);
            func_0034EDB0(owner, owner + 0xC00);
            func_002A0220();
            func_002A0380();
            func_002FC3C0(0x10);
            func_0029FEE0();
        }
    }
    return 0;
}
