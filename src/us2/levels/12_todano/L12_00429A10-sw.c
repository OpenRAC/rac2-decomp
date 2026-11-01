#include "include_asm.h"

#include "common.h"
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void func_L12_00429868(void *);
extern void func_002B0A68(void *,s32,void *,f32,f32,f32,f32,s32);
extern f32 func_002A89A8(void *, s32, f32);
extern void *func_002A9640(void *, u32, s32);
extern f32 func_002A96A0(void *, void *);
extern void func_002AB800(void *, void *), func_002AB8C0(void *, void *);
extern void func_002A7750(void *, s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern s32 func_002E5E58(s32, u32, void *);
extern void func_002E59F8(s32);
extern void func_US2_002B1880(s32, s32);
extern s32 func_002B3868(void *), func_00282948(void *);
extern void *func_0032C700(void *,s32,s32,s32,s32,s32,s32,s32,f32,f32,s32,s32,s32,s32);
extern void func_L01_0031A278(void *,void *,f32,f32,f32);
extern s32 func_002A8C28(void *,f32,void *,s32,f32,f32,s32,s32,s32);
extern void func_L12_004293A0(void *), func_L12_00429610(void *,s32);
extern f32 func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,s32);
extern void func_L00_0032A258(void *,void *,void *,void *,s32,s32,s32,s32,s32,s32,void *);
extern void func_L00_00326110(void *,s32,f32);
extern void func_00282CC0(void *,void *,void *), func_00282D30(void *,void *,f32), func_002833F0(void *,void *);
extern u8 *func_0029EFD0(s32);
extern void func_0029F338(void *);
extern u8 D_00188660[], D_00189EA0[];
extern u8 D_001A7A60[] __attribute__((sda));
typedef struct {
    u8 pad[0x160];
    f32 value160;
    s32 value164, value168, value16c;
    u8 gap[0x10];
    f32 value180;
    s32 value184, value188;
} L12EffectState;
extern L12EffectState D_L12_001B9CC0;
extern s32 D_L12_001B3DB4, D_001A903C;
extern u8 *D_L12_001B2EA0, *D_L12_001B2E9C;
extern u8 D_L12_001B2290 __attribute__((sda)), D_L12_001B2288 __attribute__((sda)), D_L12_001B2280 __attribute__((sda));
extern s32 D_L12_001B22D0 __attribute__((sda));
extern f32 D_L12_001B2260[4] __attribute__((sda));
extern s32 D_L12_001B2270[4] __attribute__((sda));
typedef struct { u8 pad[0x74]; u8 active; u8 gap[0x13]; u8 *owner; } L12Sound;

void func_US2_L12_00429A10(u8 *self) {
    typedef u32 Q __attribute__((mode(TI)));
    union { Q q; f32 f[4]; } posv, vecv;
#define pos posv.f
#define vec vecv.f
    u8 *st = P(self,0x68), *p;
    f32 damage;
    s32 count;
    switch (self[0x20]) {
    case 0:
        H(st,0x24)=100;
        F(st,0x20)=100.0f;
        F(st,0x70)=F(self,0x18)+50.0f;
        F(st,0x7c)=func_002A89A8(self+0x10,0,0.5f);
        I(st,0x80)=-1;
        D_L12_001B3DB4=0;
        func_002A7750(self,1,-1);
        break;
    case 1: {
        s32 i;
        damage=func_002A96A0(self,func_002A9640(self,0x230000,0));
        if (damage>0.0f) {
            st[0x57]=255; st[0x58]=128; st[0x59]=128;
            func_002AB800(self,st+0x50);
            F(st,0x20)-=damage;
        }
        if (F(st,0x20)<0.0f) {
            u8 *p;
            count=0;
            for (p=D_L12_001B2E9C;p<D_L12_001B2EA0;p+=0x100)
                if (*(s16 *)(p+0xaa)==*(s16 *)(self+0xaa) && p[0x20]<2 && p!=self) count++;
            if (!count && !D_001A7A60[9]) {
                D_001A7A60[9]=1;
                func_002E5E58(1,0,0);
                func_US2_002B1880(0x1233,-1);
                D_001A903C=1;
            }
            i=D_L12_001B3DB4;
            if (i==0) func_002A7750(self,2,-1);
            else if (i==1) func_002A7750(self,7,-1);
            else if (i==2) func_002A7750(self,3,-1);
            else if (i==3) func_002A7750(self,4,-1);
            else func_002A7750(self,7,-1);
            D_L12_001B3DB4++;
        }
        self[0xa8]=255;
        break;
    }
    case 2: {
        s32 i;
        if (func_002B3868(self)) {
            I(self,0x98)=0;
            func_0032C700(self+0x10,1,20,20,20,20,20,0,2.5f,20.0f,1,1,1,0);
            func_002E5CF8(0,0,self);
        }
        F(self,0xf0)+=F(st,0x64);
        F(st,0x64)+=0.0002181661839131266f;
        if (F(self,0xf0)>0.7853982448577881f) {
            for (i=0;i<8;i++) {
                func_L01_0031A278(self,pos,0.0f,0.0f,(f32)i*2.033750057220459f);
                func_002A8C28(self,1.2f,pos,0x30008,12.0f,1.0f,0,1,0);
            }
        }
        if (F(self,0xf0)>1.431170105934143f) {
            D_L12_001B9CC0.value180=0.2f; D_L12_001B9CC0.value188=90;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=60; D_L12_001B9CC0.value16c=0;
            func_002A7750(self,8,-1);
        }
        break;
    }
    case 4:
        if (func_002B3868(self)) {
            I(st,0x68)=260; I(st,0x6c)=0;
            D_L12_001B9CC0.value180=0.1f; D_L12_001B9CC0.value188=90;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=60; D_L12_001B9CC0.value16c=0;
            self[0x30]=255;
        }
        func_L12_00429610(self,0);
        {
            L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(st,0x80)=func_002E5CF8(3,4,self);
        }
        if (!func_00282948(st+0x68) && I(st,0x68)<220) func_L12_004293A0(self);
        F(self,0x18)+=F(st,0x6c); F(st,0x6c)+=0.00022222222469281405f;
        if (F(self,0x18)>F(st,0x70) && !self[0x31]) {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) func_002E59F8(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            func_002A7750(self,5,-1);
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            I(st,0x68)=180; I(st,0x6c)=0;
            D_L12_001B9CC0.value180=0.1f; D_L12_001B9CC0.value188=90;
            D_L12_001B9CC0.value160=0.2f; D_L12_001B9CC0.value168=60; D_L12_001B9CC0.value16c=0;
        }
        if (I(st,0x68)) {
            {
                L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
                if (slot->owner!=self || !slot->active) I(st,0x80)=func_002E5CF8(3,4,self);
            }
            func_L12_00429610(self,0);
            if (!func_00282948(st+0x68) && I(st,0x68)<140) func_L12_004293A0(self);
            F(self,0x18)+=F(st,0x6c); F(st,0x6c)+=0.00022222222469281405f;
        } else {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) func_002E59F8(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            F(self,0x18)+=F(st,0x6c); F(st,0x6c)-=0.0027222223579883575f;
            if (F(self,0x18)<F(st,0x7c)) func_002A7750(self,8,-1);
        }
        break;
    case 5: {
        u8 *p;
        p=D_L12_001B2E9C+(I(st,0x74)<<8);
        if (p && p[0x20]!=254 && p[0x20]!=253) {
            if (func_00282E80(p+0x10,D_00189EA0)<45.0f && p[0x31]) {
                H(self,0x34)=(H(self,0x34)&0xffbe)|0x1000;
                I(self,0x98)=I(P(self,0x24),0x10);
                F(st,0x78)=F(p,0x18);
                qcopy(self+0x10,p+0x10);
                F(self,0x18)+=60.0f; F(self,0xf0)=3.1415927410125732f;
                F(st,0x6c)=-0.25f;
                func_L00_003294F0(p,1);
                func_002A7750(self,6,-1);
                break;
            }
        }
        I(self,0x98)=0;
        H(self,0x34)=(H(self,0x34)|0x41)&0xefff;
        break;
    }
    case 6:
        vecv.q=0; vec[0]=F(self,0x10); vec[1]=F(self,0x14); vec[2]=F(st,0x78);
        posv.q=vecv.q;
        F(self,0x18)+=F(st,0x6c);
        {
            L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
            if (slot->owner!=self || !slot->active) I(st,0x80)=func_002E5CF8(3,4,self);
        }
        if (F(self,0x18)<F(st,0x78)+6.44f && (H(self,0x7c)&4)) {
            if (I(st,0x80)!=-1) {
                {
                    L12Sound *slot=(L12Sound *)(D_00188660+I(st,0x80)*0x70);
                    if (slot->owner==self && slot->active) func_002E59F8(I(st,0x80));
                }
            }
            I(st,0x80)=-1;
            func_0032C700(pos,1,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
            func_L00_0032A258(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,4,255,func_L12_00429868);
            func_L00_00326110(self,25,0.0f);
            func_0029F338(self);
            return;
        }
        if (F(self,0x18)<F(st,0x78)+11.2f && (H(self,0x7c)&2)) {
            func_0032C700(pos,1,25,20,20,20,45,1,2.0f,20.0f,1,1,0,0);
            func_L00_0032A258(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,2,255,func_L12_00429868);
            H(self,0x7c)=0x8004;
        } else if (F(self,0x18)<F(st,0x78)+16.27f && !H(self,0x7c)) {
            func_002E5CF8(1,0,self);
            func_0032C700(pos,1,25,20,20,20,45,1,3.0f,20.0f,1,1,0,0);
            func_L00_0032A258(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,1,255,func_L12_00429868);
            H(self,0x7c)=0x8006;
        } else {
        vecv.q=0; vec[2]=-12.27f;
        func_00282CC0(vec,self+0x10,vec);
        func_002A8C28(self,4.0f,vec,0x10000,1000.0f,1.0f,0,1,0);
        }
        func_L12_00429610(self,1);
        break;
    case 7:
        if (func_002B3868(self)) func_002E5CF8(4,0,self);
        qcopy(pos,self+0x10);
        func_0032C700(pos,1,25,20,20,20,45,1,4.0f,20.0f,1,1,0,0);
        func_L00_0032A258(self,&D_L12_001B2290,&D_L12_001B2288,&D_L12_001B2280,255,-1,D_L12_001B22D0,15,255,255,func_L12_00429868);
        func_L00_00326110(self,25,0.0f);
        func_0029F338(self);
        return;
    case 8: {
        s32 i; u8 *p;
        for (i=0;i<3;i++) {
            p=func_0029EFD0(0x12e2-i);
            if (p) {
                func_00282D30(p+0x10,self+0xe0,D_L12_001B2260[i]);
                func_00282CC0(p+0x10,p+0x10,self+0x10);
                qcopy_nc(p+0xf0,self+0xf0);
                func_002833F0(p+0xc0,self+0xf0);
                F(p,0x2c)=F(P(p,0x24),0x24)*(F(self,0x2c)/F(P(self,0x24),0x24));
                posv.q=0; pos[2]=0.13333334028720856f;
                func_002B0A68(p,D_L12_001B2270[i],pos,6.0f,12.0f,6.0f,12.0f,255);
                func_0032C700(p+0x10,0,25,20,20,20,45,1,1.0f,20.0f,1,1,0,0);
                func_0029F338(p);
            }
        }
        func_L00_00326110(self,25,0.0f);
        func_002E5CF8(1,0,self);
        func_0029F338(self);
        return;
    }
    }
    func_002AB8C0(self,st+0x50);
}
