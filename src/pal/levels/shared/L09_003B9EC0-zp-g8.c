#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union EffectVector { Quadword bits; float value[4]; } EffectVector;
extern int func_002A77E0(int);
extern void func_002A7398(void *, int, int);
extern void func_002A7750(void *, int, int);
extern int func_002A9640(void *, int, int);
extern void func_002E5CF8(int, int, void *);
extern u8 *func_L00_00326620(void *, int, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern void func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_PAL_L00_00328480(void *, void *, int, int, void *, unsigned int, void *, float, float, float, float);
extern void func_0029F338(void *);
extern float D_L09_001AF9E0[] SDATA(D_L09_001AF9E0);
extern float D_L09_001AF9D8[] SDATA(D_L09_001AF9D8);
extern float D_L09_001AF9D0[] SDATA(D_L09_001AF9D0);

/* Death of a three-state object: it picks its animation, waits for the hit, then spawns the
   closing effects and retires itself. */
void func_PAL_L09_003B9EC0(u8 *self)
{
    EffectVector v;
    u8 *effect;

    switch (self[0x20]) {
    case 0:
        func_002A7398(self, 0, func_002A77E0(*(u8 *)(*(u8 **)(*(u8 **)(self + 0x24) + 0x48) + 0x10)));
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (*(short *)(self + 0xAA) == 0x852) {
            if (func_002A9640(self, 0x4010000, 0)) {
                func_002E5CF8(0, 0, self);
                func_002A7750(self, 2, -1);
            }
            self[0xA8] = 0xFF;
        }
        break;
    case 2:
        effect = func_L00_00326620(self, 0x12A1, 0);
        if (effect)
            func_PAL_L00_0032C328(effect, D_L09_001AF9E0, D_L09_001AF9D8, D_L09_001AF9D0, 0xFFFF, 0,
                              -1, 0x16, 0xFFFF, 0xFF, 0);
        func_PAL_L00_003FB330(self + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
        v.bits = 0;
        v.value[2] = 0.24000001f;
        func_PAL_L00_00328480(self, self + 0x10, 0x14, 0, &v, 0x80804040, 0, 6.0f, 3.0f, 1.5f, 7.0f);
        func_0029F338(effect);
        func_0029F338(self);
        break;
    }
}
