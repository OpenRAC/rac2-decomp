/* Nonmatching: US/US2 744/744 bytes, 0/1; absent from PAL.
 * Five checks. Profile -O2 -G0 -ffunction-sections -frac2-zero-ti-por
 * -mno-split-addresses. Only two adjacent words differ: generated SWzero
 * object+0x98 precedes ORIflags,1; retail ORI precedes the SW. Real flag and
 * counter snapshots recover the other tail ordering; three source forms
 * (separate OR, initialized mask, promoted mask) are byte-identical.
 * Stop at the repeated form; reopen with an independently measured narrow
 * scheduling witness. No volatile field, fake dependency or barrier.
 * Complete local extents: three16-byte vectors. Tilt really receives the
 * full TIzero before its y component changes. 324F18 initializes XYZ and
 * its vector helpers preserve the unused original w lane; no new w store
 * is introduced. B0A68 and the spark wrapper consume the real vector extents.
 * Coordinate views are separately addressed unknown owners; no fabricated
 * array/SDA bound. A9640 returns its64-byte hit-record pointer; other ignored
 * integer status results retain their real declarations.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } EffectVector;
extern int D_L01_001AEC38 MACRO_ADDR;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0[] NOT_SDA;
extern float D_L01_001B2090[] NOT_SDA;
extern float D_L01_001B2090_gp[] SDATA(D_L01_001B2090);
extern float D_L01_001B208C[] NOT_SDA;
extern float D_L01_001B208C_gp[] SDATA(D_L01_001B208C);
/* Independently addressed coordinate views; owner extents remain open. */
extern float D_L01_001B1640[] NOT_SDA;
extern float D_L01_001B1640_gp[] SDATA(D_L01_001B1640);
extern float D_L01_001B1644[] NOT_SDA;
extern float D_L01_001B1648[] NOT_SDA;
extern void func_002A7750(void *,int,int);
extern void *func_002A9640(void *,int,int);
extern void func_00282D30(void *,void *,float);
extern void func_002B0A68(void *,int,float *,unsigned char,float,float,float,float);
extern void func_L00_00324F18(void *,void *,float,float,float);
extern void func_00283098(void *,void *,void *);
extern void func_L01_002E1680(float *,float *,int,int,int,float,float,float);
extern void func_L00_00326110(void *,int,float);
extern int func_002E5CF8(int,int,void *);
extern int func_002B3868(void *);
extern int func_00282948(int *);
extern void func_0029F338(void *);

typedef struct { int blocked,timer; } DestructionState;

void func_L01_0040F958(unsigned char *object)
{
    float velocity[4] __attribute__((aligned(16)));
    EffectVector tilt;
    float position[4] __attribute__((aligned(16)));
    DestructionState *state=*(DestructionState **)(object+0x68);
    switch(object[0x20]) {
    case 0:
        D_L01_001AEC38++;
        func_002A7750(object,1,-1);
        break;
    case 1:
        if(func_002A9640(object,0x4010000,0) && !state->blocked) {
            D_L01_001AEC38--;
            func_002A7750(object,2,-1);
        }
        object[0xA8]=255;
        break;
    case 2:
        func_00282D30(velocity,object+0xD0,-0.06666667014360428f);
        if(object[0x31] && D_L01_001B2090_gp[0]<0.9f && D_L01_001B208C_gp[0]<0.9f &&
           D_L01_001B3468<D_L01_001B15E0[0]) {
            func_002B0A68(object,0x3F,velocity,255,1.0f,3.0f,2.0f,5.0f);
            tilt.q=0;
            tilt.f[1]=-0.015000000596046448f;
            func_L00_00324F18(object,position,D_L01_001B1640_gp[0],D_L01_001B1644[0],D_L01_001B1648[0]);
            func_00283098(tilt.f,tilt.f,object+0xC0);
            func_L01_002E1680(position,tilt.f,10,0x3F7FFF3F,0,0.0066666672937572f,1.0f,1.0299999713897705f);
        } else
            func_002B0A68(object,2,velocity,255,1.0f,3.0f,2.0f,5.0f);
        func_L00_00326110(object,1,0.0f);
        func_002E5CF8(0,0,object);
        func_002A7750(object,3,-1);
        break;
    case 3:
        if(func_002B3868(object)) {
            unsigned int flags=*(unsigned short *)(object+0x34)|1;
            int dying;
            object[0x31]=0;
            *(int *)(object+0x98)=0;
            dying=D_L01_001B3468;
            *(unsigned short *)(object+0x34)=flags;
            state->timer=120;
            D_L01_001B3468=dying+1;
        }
        if(func_00282948(&state->timer)) {
            D_L01_001B3468--;
            func_0029F338(object);
        }
        break;
    }
}
