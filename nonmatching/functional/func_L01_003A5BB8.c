/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* Retained GPT-6.1 Sol high-effort reconstruction; not linked or counted.
 * Current pinned compiler, -O2 -G8 -ffunction-sections: 1136/1136 bytes,
 * 0/1 USA v1.01 placements (29 October 2026). Other canonical releases absent.
 * Separate state-transition calls and the positive ordered height guard fix
 * the old state-machine topology. The path call interleaves the FP argument
 * before the integer bank without changing its EE interface. Capturing the
 * incremented collision count before the real vertical-velocity store preserves
 * the retail counter load/store sequence without a synthetic reload or volatile.
 * Everything matches except the flag-store setup at +0x29C..+0x2A8:
 * C uses lui v0; a0=1; sb s0,lo(v0); a1=0, while retail uses a0=1;
 * a1=0; lui at; sb s0,lo(at). Both access the same resident byte.
 * Honest read/store extern views keep both absolute accesses; a single
 * MACRO_ADDR/sda declaration puts the store in a GP call delay slot (1132).
 * nosda ties NOT_SDA; G0, strict aliasing and no-split profiles worsen other
 * accesses/scheduling. Reopen with evidence for the absolute byte-store macro
 * without changing the other address forms. Required declarations follow.
 */

#include "common.h"
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern void *D_L01_001FE180[];
extern float D_L01_001AF85C __attribute__((sda));
extern float D_L01_001AF860 __attribute__((sda));
extern int D_L01_001AF864 __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_001A7A6D NOT_SDA;
extern u8 oozla_event_flag __asm__("D_001A7A6D") MACRO_ADDR;
extern int D_L01_001A907C;
extern void func_0029F338(void *);
extern float func_00282E48(void *,void *);
extern float func_00282C48(float);
extern void func_002C9828(float,void *,int,void *,void *,int);
extern void func_002A7470(void *,int,int,int);
extern int func_002A9640(void *,int,int);
extern void func_00283098(void *,void *,void *);
extern void func_002E5E58(int,int,int);
extern void func_002B0A18(int,int);
extern int func_002B3868(void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_002E5CF8(int,int,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_00283B98(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_002A7750(void *,int,int);
extern void func_L01_003A6028(void *);
extern void func_L00_00326110(void *,int,float);
extern int func_00282948(void *);
void func_L01_003A5BB8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *path = D_L01_001FE180[I(state,0x50)];
    float first, last, oldHeight;
    int mode, count;
    switch (object[0x20]) {
    case 0:
        if (I(state,0x50) == -1) { func_0029F338(object); return; }
        D_L01_001AF864 = 0;
        first = func_00282E48(path + 0x10,path + 0x20);
        last = func_00282E48(path + 0x10,path + I(path,0)*16);
        F(state,0x74) = (D_L01_001AF85C * 0.016666668f) / first;
        I(state,0x70) = func_00282C48(first-last) < 0.1f;
        F(state,0x5C) = F(state,0x58) * I(path,0);
        object[0x20] = 1;
        F(object,0x2C) *= D_L01_001AF860;
        object[0x30] = 255;
    case 1:
        oldHeight = F(object,0x18);
        func_002C9828(F(state,0x5C),path,I(state,0x70),object+0x10,object+0xF0,0);
        F(object,0xF4) *= 0.5f;
        F(object,0x18) += F(state,0x54);
        F(state,0x5C) += F(state,0x74);
        if (F(state,0x5C) > I(path,0)) F(state,0x5C) -= I(path,0);
        if (object[0x60] & 2) {
            if (oldHeight < F(object,0x18)) {
                if (object[0x43] != 0) func_002A7470(object,0,0,10);
            } else if (object[0x43] != 1) func_002A7470(object,1,0,10);
        }
        if (!func_002A9640(object,0x10000,0)) return;
        F(state,0x60) = D_L01_001AF85C * 0.008333334f;
        func_00283098(state+0x60,state+0x60,object+0xC0);
        count = D_L01_001AF864 + 1;
        F(state,0x68) = -0.0500000045f;
        if ((D_L01_001AF864 = count) > 3 && (mode = D_001A79F0) == 1 && !oozla_event_flag) {
            D_001A7A6D = 1;
            func_002E5E58(1,0,0);
            func_002B0A18(0x1233,-1);
            D_L01_001A907C = mode;
        }
        func_002A7750(object,2,-1);
        break;
    case 2:
        if (func_002B3868(object)) {
            func_002AC728(object,object+0x10,-1,0.5f,13.0f);
            func_002E5CF8(0,0,object);
        }
        F(object,0x48) = 0.5f;
        func_00282CC0(object+0x10,object+0x10,state+0x60);
        F(state,0x68) -= 0.003f;
        F(state,0x60) *= 0.98f;
        F(state,0x64) *= 0.98f;
        F(object,0xF0) = func_00283B98(-3.1415927f,(F(object,0xF0)+3.1415927f)*0.95f);
        if (func_00282C48(func_002A89A8(object+0x10,0,0.5f)-F(object,0x18)) < 0.5f) {
            I(state,0x78) = 30;
            func_002A7750(object,3,-1);
        }
        break;
    case 3:
        if (func_002B3868(object)) {
            func_L01_003A6028(object);
            func_002E5CF8(1,0,object);
            func_L00_00326110(object,1,0.0f);
        }
        F(object,0x18) += F(state,0x68);
        if (func_00282948(state+0x78)) func_0029F338(object);
        return;
    default:
        return;
    }
}
