/* func_US2_L10_00426130, the v2.00 copy of func_L10_00424448: the same C, plus destroying the two
 * path markers func_US2_L10_00426260 may have left behind. Its own unit for -G8. */
#include "common.h"

extern int D_L10_001B13A4 __attribute__((sda));
typedef struct { char pad[0x34]; unsigned short flags; } GateObject;
extern GateObject *D_L10_001B1400 __attribute__((sda)), *D_L10_001B1404 __attribute__((sda));
extern void func_0029F338(void *);
extern int D_L10_00221CFC __attribute__((section(".data")));
extern void func_002B7320(void);
extern void func_L05_0037B210(void);
extern void func_L05_00379F18(int);
extern unsigned char **func_L05_00379EB8(void);
extern int func_L00_004272A0(void);
extern void func_L05_0037B280(void *, int);
extern void func_L10_00425798(void);
extern void func_L10_00425410(int, void *);
extern void *func_L05_00379ED0(int);
extern int func_L05_0037B3A0(void *);
extern void func_US2_L10_00425A78(void *, int);

void func_US2_L10_00426130(void *object)
{
    unsigned char **entries;
    int i, count;

    if (!D_L10_001B13A4) {
        D_L10_00221CFC = 0;
        D_L10_001B13A4 = 1;
        func_002B7320();
        func_L05_0037B210();
        func_L05_00379F18(0);
        entries = func_L05_00379EB8();
        count = func_L00_004272A0();
        for (i = 0; i < count; i++) {
            if (*(short *)(entries[i] + 0xAA) == 0xF8E)
                func_L05_0037B280(entries[i], 1);
        }
        func_L10_00425798();
        func_L10_00425410(0x32, (void *)0xC);
        if (D_L10_001B1400 && D_L10_001B1400->flags) {
            func_0029F338(D_L10_001B1400);
            D_L10_001B1400 = 0;
        }
        if (D_L10_001B1404 && D_L10_001B1404->flags) {
            func_0029F338(D_L10_001B1404);
            D_L10_001B1404 = 0;
        }
    }
    if (!func_L05_0037B3A0(func_L05_00379ED0(0xF8E)))
        func_US2_L10_00425A78(object, 2);
}
