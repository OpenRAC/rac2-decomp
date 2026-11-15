#include "common.h"

extern const char D_L09_001B10A8[];
extern float D_L09_001B0F0C __attribute__((sda)), D_L09_001B0F10 __attribute__((sda));
extern float D_L09_001B0F14 __attribute__((sda)), D_L09_001B0F18 __attribute__((sda));
extern float D_L09_001B0F1C __attribute__((sda)), D_L09_001B0F20 __attribute__((sda));
extern void func_0026FEB8(const char *, ...);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_002A7470(void *, int, int, int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
/* Switches the enemy and its partner to a new animation and sets how fast it turns and moves in that animation. */
void func_L09_003F7518(char *object, int state, int startFrame, int blendTime) {
    char *data = *(char **)(object+0x68);
    STUB_printf(D_L09_001B10A8, *(short *)(object+0xB2), state);
    if (state == 12) {
        SetControllerSpeedLimits(object, D_L09_001B0F0C * 0.00027777778f, D_L09_001B0F10 * 0.016666667f,
                      D_L09_001B0F1C * 0.0000048481374f, D_L09_001B0F20 * 0.00029088825f);
        F(data,0x118) += F(data,0x118);
    } else {
        SetControllerSpeedLimits(object, D_L09_001B0F14 * 0.00027777778f, D_L09_001B0F18 * 0.016666667f,
                      D_L09_001B0F1C * 0.0000048481374f, D_L09_001B0F20 * 0.00029088825f);
        F(data,0x118) += F(data,0x118);
    }
    if ((unsigned)(state-13)<3) {
        I(data,0x6C)=0; I(data,0x70)=0; I(data,0x74)=0; I(data,0x78)=0; I(data,0x7C)=0;
        B(data,0x61)=15; B(data,0x62)=15; B(data,0x66)=15;
        B(data,0xBC)=7; B(data,0xBD)=19; B(data,0xBE)=7; B(data,0xBF)=19;
        B(data,0xC2)=7; B(data,0xC3)=19; B(data,0xC6)=1;
    } else if (state==16) {
        F(data,0x6C)=0.36666667f; F(data,0x70)=0.116666675f; F(data,0x74)=0.004166667f;
        F(data,0x78)=0.008333334f; F(data,0x7C)=0.004166667f;
        B(data,0x61)=18; B(data,0x62)=17; B(data,0x66)=20;
        B(data,0xBC)=5; B(data,0xBD)=9; B(data,0xBE)=4; B(data,0xBF)=7;
        B(data,0xC2)=10; B(data,0xC3)=17; B(data,0xC6)=0;
    }
    if ((I(data,0x428) || (I(data,0x2DC)!=-1 && I(data,0x2DC)==I(data,0x2B0))) && state!=15) {
        if (B(object,0x43)!=14) StartAnimationBlended(object,14,startFrame,blendTime);
    } else if (B(object,0x43)!=state) StartAnimationBlended(object,state,startFrame,blendTime);
    { char *partner=*(char **)(data+0x2F8);
    if (partner && B(partner,0x43)!=state) StartAnimationBlended(partner,state,startFrame,blendTime); }
}
