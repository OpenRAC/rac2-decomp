#include "include_asm.h"

#include "common.h"
extern const char D_L09_001B10A8[];
extern float D_L09_001B0F0C __attribute__((sda)), D_L09_001B0F10 __attribute__((sda));
extern float D_L09_001B0F14 __attribute__((sda)), D_L09_001B0F18 __attribute__((sda));
extern float D_L09_001B0F1C __attribute__((sda)), D_L09_001B0F20 __attribute__((sda));
extern void func_0026FEB8(const char *, ...);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))

void func_PAL_L09_003FBDF0(char *object, int state, int a2, int a3) {
    char *data = *(char **)(object+0x68);
    func_0026FEB8(D_L09_001B10A8, *(short *)(object+0xB2), state);
    if (state == 12) {
        func_002B60B0(object, D_L09_001B0F0C * 0.00040000002f, D_L09_001B0F10 * 0.020000001f,
                      D_L09_001B0F1C * 6.981318e-06f, D_L09_001B0F20 * 0.0003490659f);
        F(data,0x118) += F(data,0x118);
    } else {
        func_002B60B0(object, D_L09_001B0F14 * 0.00040000002f, D_L09_001B0F18 * 0.020000001f,
                      D_L09_001B0F1C * 6.981318e-06f, D_L09_001B0F20 * 0.0003490659f);
        F(data,0x118) += F(data,0x118);
    }
    if ((unsigned)(state-13)<3) {
        I(data,0x6C)=0; I(data,0x70)=0; I(data,0x74)=0; I(data,0x78)=0; I(data,0x7C)=0;
        B(data,0x61)=15; B(data,0x62)=15; B(data,0x66)=15;
        B(data,0xBC)=7; B(data,0xBD)=19; B(data,0xBE)=7; B(data,0xBF)=19;
        B(data,0xC2)=7; B(data,0xC3)=19; B(data,0xC6)=1;
    } else if (state==16) {
        F(data,0x6C)=0.44000003f; F(data,0x70)=0.14000002f; F(data,0x74)=0.006f;
        F(data,0x78)=0.012f; F(data,0x7C)=0.006f;
        B(data,0x61)=18; B(data,0x62)=17; B(data,0x66)=20;
        B(data,0xBC)=5; B(data,0xBD)=9; B(data,0xBE)=4; B(data,0xBF)=7;
        B(data,0xC2)=10; B(data,0xC3)=17; B(data,0xC6)=0;
    }
    if ((I(data,0x428) || (I(data,0x2DC)!=-1 && I(data,0x2DC)==I(data,0x2B0))) && state!=15) {
        if (B(object,0x43)!=14) func_PAL_002A7E68(object,14,a2,a3);
    } else if (B(object,0x43)!=state) func_PAL_002A7E68(object,state,a2,a3);
    { char *partner=*(char **)(data+0x2F8);
    if (partner && B(partner,0x43)!=state) func_PAL_002A7E68(partner,state,a2,a3); }
}
