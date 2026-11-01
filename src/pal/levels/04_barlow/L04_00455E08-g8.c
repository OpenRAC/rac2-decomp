#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(int *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 *D_L04_001B24DC;
extern u16 *D_L04_001FB1E0[] NOT_SDA;
struct Resident502D0 { u8 pad[0x2290]; u8 *target; };
extern struct Resident502D0 D_00189E20 NOT_SDA;
extern u8 D_L04_001B18A0[] NOT_SDA, D_L04_002CA650[] NOT_SDA, D_L04_001B9680[] NOT_SDA;
extern int D_L04_001B24F8;
extern float func_002A89A8(void *, int, float);
extern int func_L02_0032E508(void *, int, void *, int);
extern void func_0026FEB8(void *, ...);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int), func_00283CF0(float), func_002A7820(int,int);
extern void func_L00_003294F0(void *, int), func_002B60B0(void *,float,float,float,float);
extern void func_002A7750(void *,int,int), func_PAL_002A7E68(void *,int,int,int);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(void *), func_002AF1D0(void *,void *,int,int),func_0029F338(void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *),func_L04_00450268(void *),func_PAL_002AD288(void *,void *,int,float,float);
extern int func_PAL_002B1A50(void *,void *,int);
extern void func_0029FCC0(void *,int,void *),func_PAL_L04_00456C90(void *,int),func_002E5CF8(int,int,void *);
extern void func_PAL_002AC290(void *,void *),func_L04_004510C8(void *),func_PAL_002A7650(void *,int,int);
extern int func_002A8508(int,int),func_002B3670(void *,void *,int,int,int,float,float);
extern int func_002B3BA8(void *,void *,float,float,int,int);

int func_PAL_L04_00455E08(u8 *object) {
    u8 *data = P(object,0x68);
    int result;

    u8 position[16] __attribute__((aligned(16)));
    if (object[0x20] == 0) {
        P(data,0x18) = data+0x140;
        F(object,0x18) = func_002A89A8(object+0x10,0,0.5f);
        if (I(data,0x560)) { H(object,0x34) |= 0x41; I(object,0x98)=0; }
        if (I(data,0x548)) {
            I(data,0x540) = func_L02_0032E508(object,I(data,0x544),data+0x340,16);
            func_0026FEB8(D_L04_001B18A0,I(data,0x540));
        }
        if (F(data,0x2A8)==0.0f) F(data,0x2A8)=0.01745329424738884f*func_002A78D8(15.0f,25.0f);
        else F(data,0x2A8)*=0.01745329424738884f;
        if (I(data,0x2B4)) F(data,0x2A8)=func_002A78D8(5.0f,30.0f)*0.01745329424738884f;
        if (func_002A77E0(2)==1) { H(object,0x34)|=0x8000; func_L00_003294F0(object,1); }
        data[0x48]=func_00283CF0(20.0f);
        data[0x4A]=func_00283CF0(14.0f);
        data[0x70]=25; I(data,0xA8)=4;
        data[0x71]=21; data[0x72]=16; data[0x76]=18; data[0x77]=19;
        F(data,0x7C)=0.24000001f; F(data,0x80)=0.15f;
        F(data,0x84)=0.008f; F(data,0x88)=0.014f; F(data,0x8C)=0.006f;
        data[0xCC]=5; data[0xCD]=10; data[0xCE]=8; data[0xCF]=15; data[0xD2]=6; data[0xD3]=11;
        F(data,0x10C)=1.0f; F(data,0xB8)=0.18000000715255737f; P(data,0x188)=data+0x2C0;
        F(data,0x90)=0.75f; F(data,0x94)=0.75f; F(data,0x9C)=0.4f;
        F(data,0x140)=0.75f; F(data,0x144)=0.75f; F(data,0x148)=0.4f; F(data,0x14C)=0.4f;
        if (I(data,0x2B4)) { F(data,0x148)=0.6f; F(data,0x14C)=0.6f; }
        if (I(data,0x2B8)!=-1) I(data,0x17C)=I(data,0x2B8);
        F(data,0x150)=0.9599311947822571f; F(data,0x170)=1.4835299849510193f;
        F(data,0x16C)=0.002f; F(data,0x174)=1.5f;
        func_002B60B0(object,0.0024f,0.060000002f,0.0016755164f,0.12566373f);
        if (I(data,0x560)) { F(data,0x148)=0.7f; F(data,0x150)=1.3089970350265503f; F(data,0x14C)=0.7f; }
        data[0x28]=3; data[0x29]=1; F(data,0x30)=0.75f; F(data,0x2BC)=data[0x34]; data[0x2E]=1;
        if (I(data,0x27C)) {
            func_002A7750(object,1,5);
            if (I(data,0x280)!=-1) {
                u8 *other=D_L04_001B24DC+(I(data,0x280)<<8);
                P(data,0x284)=other;
                qcopy(object+0x10,other+0x10); qcopy(object+0xF0,other+0xF0);
                I(object,0x98)=0; H(object,0x34)&=0xAFFF;
                P(P(P(data,0x284),0x68),0x2AC)=object;
                P(data,0x290)=func_0029EFD0(0x911);
                if (!P(data,0x290)) return 1;
                P(data,0x290)[0x30]=object[0x30]; P(data,0x290)[0x31]=0;
                func_002A0F48(P(data,0x290));
                { u8 *child=P(data,0x290); qcopy(child+0x10,object+0x10); F(child,0x18)+=0.75f; }
                P(data,0x288)=func_0029EFD0(0xFF9);
                if (!P(data,0x288)) return 1;
                P(data,0x288)[0x30]=object[0x30]; H(P(data,0x288),0x32)=H(object,0x32);
                P(data,0x288)[0x31]=1; *(u64 *)(P(data,0x288)+0x38)=*(u64 *)(object+0x38);
                func_002A0F48(P(data,0x288)); func_002AF1D0(object,P(data,0x288),1,0);
                I(data,0x2A0)=0;
            } else {
                func_0026FEB8(D_L04_002CA650); I(data,0x27C)=0; func_002A7750(object,4,0); return 1;
            }
        } else {
            func_002A7750(object,4,0);
            if (object[0x43]!=10) func_PAL_002A7E68(object,10,0,0);
            if (I(data,0x564)==1) {
                P(data,0x56C)=D_L04_001B24DC+(I(data,0x568)<<8); func_002A7750(object,5,0);
                if (object[0x43]!=28) func_PAL_002A7E68(object,28,0,0);
            } else if (I(data,0x564)==2) {
                P(data,0x56C)=D_L04_001B24DC+(I(data,0x568)<<8); func_002A7750(object,5,0);
                if (object[0x43]!=30) func_PAL_002A7E68(object,30,5,0);
            } else if (I(data,0x564)==3) {
                P(data,0x56C)=D_L04_001B24DC+(I(data,0x568)<<8); func_002A7750(object,5,0);
                if (object[0x43]!=30) func_PAL_002A7E68(object,30,0,0);
            }
            P(data,0x2AC)=func_0029EFD0(0x9AC);
            if (!P(data,0x2AC)) return 1;
            P(data,0x2AC)[0x30]=object[0x30]; H(P(data,0x2AC),0x32)=H(object,0x32);
            P(data,0x2AC)[0x31]=1; *(u64 *)(P(data,0x2AC)+0x38)=*(u64 *)(object+0x38);
            func_002A0F48(P(data,0x2AC)); I(P(data,0x2AC),0x98)=0;
            func_002AF1D0(object,P(data,0x2AC),3,0);
        }
        qcopy(data+0x110,object+0x10);
        F(data,0x120)=1.0f; F(data,0x12C)=F(data,0x298); F(data,0x130)=10.0f;
        I(data,0x294)=func_002A7820(100,583);
    }
        if (object[0x31] && func_00282E48(object+0x10,D_L04_001B9680)<24.0f) { func_002A93B0(object); object[0x6F]=22; }
    if (data[0x2E]==2) { func_L04_00450268(object); return 1; }
    if (P(data,0x2AC)) func_002AF1D0(object,P(data,0x2AC),3,0);
    if (F(data,0x20)<=1.0f) {
        if (P(data,0x2AC)) {
            func_PAL_002AD288(object,P(data,0x2AC)+0x10,-1,0.5f,3.0f);
            func_0029F338(P(data,0x2AC)); P(data,0x2AC)=0;
        }
        I(data,0x2A0)=0;
    }
    if (I(data,0x1C0)>=16 && object[0x95]==2) {
        F(data,0x2A8)=func_002A78D8(15.0f,25.0f)*0.01745329424738884f; I(data,0x1C0)=0;
        if (object[0x43]!=11) func_PAL_002A7E68(object,11,0,8);
        func_002A7750(object,17,-1);
    }
    result=func_PAL_002B1A50(object,data+0x60,I(data,0x2A0));
    if (result) {

        if (F(object,0x48)!=1.0f) F(object,0x48)=1.0f;
        if (I(data,0x2A0)) { func_0029FCC0(object,3,position); func_PAL_L04_00456C90(position,8); }
        if (result==4) func_002E5CF8(24,0,object);
        I(data,0x2A0)=0; data[0x57]=210; func_PAL_002AC290(object,data+0x50); func_L04_004510C8(object);
        if ((unsigned)(result-4)<2 && D_L04_001B24F8>=object[0x21] && func_002A8508(object[0x21],-1)>=2) {
            u16 *ids=D_L04_001FB1E0[object[0x21]];
            do {
                u8 *other=P(D_L04_001B24DC+((*ids&0x7FFF)<<8),0x68);
                if (!I(other,0x2A4)) { I(other,0x2A4)=1; break; }
            } while ((s16)*ids++>=0);
        }
    }
    { u8 *oldTarget; u8 *stateTimer=data+0x278;
        H(data,0x274)=func_002B3670(object,stateTimer,I(data,0x260),I(data,0x264),0,F(data,0x268),F(data,0x26C));
        I(data,0x258)=func_002B3BA8(object,P(data,0x250),F(data,0x268),10.0f,0,0);
        oldTarget=P(data,0x240);
        I(data,0x25C)=func_002B3BA8(object,P(data,0x254),F(data,0x26C),10.0f,0,0);
        if (oldTarget!=D_00189E20.target && P(data,0x240)==D_00189E20.target) {
            P(data,0x240)=oldTarget; *(Quad *)(data+0x230)=*(Quad *)(oldTarget+0x10);
        }
    }
    if (object[0x95]!=4) {
        float floor=func_002A89A8(object+0x10,0,0.5f);
        F(object,0x18)-=0.37600002f;
        if (F(object,0x18)<floor) F(object,0x18)=floor;
    }
    if (F(object,0x18)<40.0f) {
        func_PAL_002A7650(object,0,3);
        if (P(data,0x288)) { func_0029F338(P(data,0x288)); P(data,0x288)=0; }
        if (P(data,0x2AC)) {
            func_PAL_002AD288(object,P(data,0x2AC)+0x10,-1,0.5f,3.0f);
            func_0029F338(P(data,0x2AC)); P(data,0x2AC)=0;
        }
        return 1;
    }
    return 0;
}
