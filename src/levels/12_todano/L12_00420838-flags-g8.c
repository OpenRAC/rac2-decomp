#include "include_asm.h"
#include "names.h"


extern double ref_L12_00420838_00 __attribute__((sda));
extern double ref_L12_00420838_01 __attribute__((sda));
extern double ref_L12_00420838_02 __attribute__((sda));
extern void func_3248E0(unsigned char *, int, int);
extern int func_326C70(unsigned char *, int, int);
extern void func_333240(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern int ref_L12_00420838_03 __attribute__((sda));
extern void func_00364DF8(int, int, void *);
extern void func_00329F80(void *, int, int);
extern void func_314008(void *);

/* Hand-adapted from func_L12_00388090. */
/* Waits until the hero hits it, then plays a flash, a sound and an effect. */
void hit_l12_flash_update(unsigned char *self) {
    unsigned char *vars = *(unsigned char **)(self + 0x68);

    switch (self[0x20]) {
    case 0:
        func_3248E0(self, 1, -1);
        break;
    case 1:
        if (func_326C70(self, 0x04010000, 0) != 0 && *(int *)vars == 0) {
            func_3248E0(self, 2, -1);
            func_00364DF8(0, 0, self);
        }
        self[0xA8] = 0xFF;
        break;
    case 2:
        func_333240(self, &ref_L12_00420838_02, &ref_L12_00420838_01, &ref_L12_00420838_00, 0xFFFF, 0, ref_L12_00420838_03, 0,
                    0xFFFF, 0xFF, 0);
        func_00329F80(self, 0x110D, 0);
        func_314008(self);
        break;
    }
}
