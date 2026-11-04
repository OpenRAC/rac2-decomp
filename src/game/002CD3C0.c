#include "common.h"

extern void func_0027C540(int);
extern void func_0027C660(void);
extern s32 func_00288FB8(s32);
extern float D_001B23A4[] __attribute__((sda));
extern void func_0029C1A8(void);
extern char *D_001A8CFC[] __attribute__((sda));

extern int func_0027FAA8(int v, int p7, unsigned long long k, char *r, int m1);

extern void func_002A0250(void);

extern void func_002A01C8(void);

extern void func_002A01F0(void);

extern void func_002A0220(void);

extern int func_002A0380(void);

extern void func_0034EBE0(void *);

extern void func_0034EC70(void *);

extern void func_0034ECB0(char *);

extern void func_0034EDB0(void *, char *);

extern void func_002FC3C0(u64);

extern void func_0029FEE0(void);

int func_002CD3C0(void)
{
    int y;
    float position;

    func_0027C540(0);
    func_0029C1A8();
    position = 367.0f;
    y = (int)(D_001B23A4[0] * position + 0.5f);
    do {
        func_0027FAA8(0x1B5, y, 0x80F0F0F0ULL, (char *)func_00288FB8(0x2D4F), -1);
    } while (0);
    func_0027C660();
    if (D_001A8CFC[0] != 0) {
        if (*(int *)((char *)D_001A8CFC[0] + 0x38000 + 0x7364) != 0) {
            char *owner;
            func_002A0250();
            func_002A01C8();
            func_002A01F0();
            owner = *(char **)(D_001A8CFC[0] + 0x38000 + 0x7364);
            func_0034EBE0(owner);
            func_0034EC70(owner);
            func_0034ECB0(owner);
            func_0034EDB0(owner, owner + 0xC00);
            func_002A0220();
            func_002A0380();
            func_002FC3C0(0x10);
            func_0029FEE0();
        }
    }
    return 0;
}
