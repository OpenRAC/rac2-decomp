/* func_PAL_L02_0038CE70, the PAL copy of func_L02_00389F70: the same C with the callee is PAL's
   func_PAL_002B1588. */
#include "include_asm.h"

extern int D_L02_001A9048 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_001A7A6B __attribute__((nosda));
extern int D_L02_001A903C __attribute__((sda));

extern int func_002E5E58(int, int, void *);
extern void func_PAL_002B1588(int, int);

struct TriggerState {
    unsigned char pad00[0x20];
    unsigned char initialized;
    unsigned char pad21[15];
    unsigned char state;
};

void func_PAL_L02_0038CE70(struct TriggerState *self) {
    if (self->initialized == 0) {
        self->state = 0xFF;
        self->initialized = 1;
    }
    if (D_L02_001A9048 < 14)
        return;
    if (D_001A79F0 != 16)
        return;
    if (D_001A7A6B != 0)
        return;
    D_001A7A6B = 1;
    func_002E5E58(1, 0, 0);
    func_PAL_002B1588(0x1233, -1);
    D_L02_001A903C = 1;
}
