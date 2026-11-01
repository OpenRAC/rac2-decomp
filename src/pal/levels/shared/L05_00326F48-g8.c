#include "include_asm.h"

extern int ref_L00_0030CDB0_00[] __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
extern void func_PAL_L05_00326D78(void);
extern unsigned int func_L00_002F0E38(void);
extern void func_PAL_L00_0030E780(void);
typedef int (*Fn)(void);
typedef struct { void *cb; int pad; } Slot;
typedef struct {
    char pad0[0x7A88];
    void *cb1;
    char pad1[0x7368 - 0x7354];
    void *cb2;
    char pad2[0x7370 - 0x736C];
    Slot slot[4];
    Slot slot2[2];
} Sub;

void func_PAL_L05_00326F48(void)
{
    int i;
    int result;
    Sub *sub;
    Fn fn;
    char *g;

    if (ref_L00_0030CDB0_00[0] != 0)
        return;

    if (D_001A8CFC[0] == 0)
        goto states;
    func_PAL_L05_00326D78();
    fn = (Fn)((Sub *)(D_001A8CFC[0] + 0x38000))->cb2;
    if (fn != 0) {
        if (fn() != 0)
            return;
    }
    result = 0;
    for (i = 0; i < 4; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3FAA8))[i * 2]();
    }
    if (result != 0)
        return;
    for (i = 0; i < 2; i++) {
        sub = (Sub *)(D_001A8CFC[0] + 0x38000);
        if (sub->slot2[i].cb != 0)
            result |= ((Fn *)(D_001A8CFC[0] + 0x3FAC8))[i * 2]();
    }
    if (result != 0)
        return;
states:
    if (D_001A8BB0[0] != 0 && D_001A8BB0[0] != 5) {
        if (D_001A8BB0[0] == 4) {
            if (func_L00_002F0E38() != 7)
                return;
        }
    }
    g = D_001A8CFC[0];
    if (g != 0) {
        char *b = g + 0x38000;
        g = (char *)((Sub *)b)->cb1;
        ((Fn)g)();
        func_PAL_L00_0030E780();
    }
}
