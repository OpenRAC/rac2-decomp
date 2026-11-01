#include "include_asm.h"

#include "common.h"
typedef struct TodanoPartnerBlock { float x[12]; } TodanoPartnerBlock;
typedef struct TodanoPartnerSlot { u8 pad[0x38]; u8 *object; u32 tail; } TodanoPartnerSlot;
extern TodanoPartnerSlot D_L12_001C44C0[];
extern u8 D_L12_001B9E00[];
extern void func_PAL_L12_004184A0(u8 *);
extern void func_L09_003F8858(u8 *);
extern void func_PAL_L12_00418BD8(u8 *);
extern void func_L09_003F77D0(u8 *);
extern void func_L12_00414028(u8 *);
extern int func_PAL_002B1A50(u8 *, void *, int);
extern void func_PAL_002B3F18(u8 *, void *, void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_00282D30(void *, void *, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(u8 *);
extern int func_002B3BA8(u8 *, int, int, int, float, float);
extern u8 D_L12_00188660[];
extern s32 func_315148();
extern void func_002A7750();
extern s32 func_32D988();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern u16 *D_L12_001FB960[];
extern s32 D_001A79F0 __attribute__((sda));
extern s32 func_002A8600(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 func_002A86E8(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern u8 D_L12_001C0000[];
extern u8 *func_0029EFD0(int);
extern u8 *func_00288FB8(int);
extern s32 *D_L12_001FEAC0[];
extern s32 func_002A8AF0(void *, void *, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);

void func_PAL_L12_00419120(u8 *o) {
    u8 *d = *(u8 **)(o+0x68);
    int old, result;
    if (!o[0x95]) func_PAL_L12_004184A0(o);
    if (o[0xA8] == 255) {
        u8 *partner=*(u8 **)(d+0x2F8);
        if (partner && *(short *)(partner+0xAA)==0x114B && partner[0x20]!=254 && partner[0x20]!=253) {
            int index;
            if (partner[0xA8]!=255) {
                TodanoPartnerSlot *slots=D_L12_001C44C0;
                index=partner[0xA8];
                if (slots[index].object==partner) {
                    o[0xA8]=index;
                    slots[o[0xA8]].object=o;
                }
            }
        }
    }
    old=o[0x20];
    result=func_PAL_002B1A50(o,d+0x50,0);
    if (result) {
        func_L09_003F8858(o);
        if (*(u8 **)(d+0x2F8)) {
            if (result==4) {
                u8 *p; int i; int alive;
                *(u16 *)(o+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(d+0x2F8)+0x34)&=0xEFFF;
                *(u16 *)(*(u8 **)(d+0x2F8)+0x7C)|=0x300;
                *(int *)(d+0x20)=0;
                p=*(u8 **)(*(u8 **)(d+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(d+0x20);
                func_PAL_002B3F18(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_PAL_L12_00418BD8(o);
                func_PAL_002AC718(*(u8 **)(d+0x2F8),d+0xD0,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,0,0x810001);
                func_L09_003F77D0(o);
                if (old>=4 && !func_002A77E0(2)) {
                    if (o[0x43]!=17) func_PAL_002A7E68(o,17,0,5);
                    *(float *)(d+0xB0)=*(s8 *)(d+0xBF);
                    *(float *)(d+0xA4)=*(s8 *)(d+0xBE);
                    *(int *)(d+0xCC)=-1;
                    func_00282D30(d+0xD0,d+0xD0,0.05f);
                } else qzero(d+0xD0);
                alive=1;
                p=d+0x2F0;
                for(i=1;i>=0;i--,p+=4) {
                    if (*(u8 **)p) {
                        *(u16 *)(*(u8 **)p+0x34)&=0xFFFD;
                        *(u16 *)(*(u8 **)p+0x34)&=0xFFFE;
                        (*(u8 **)p)[0x31]=alive;
                        *(u8 **)p=0;
                    }
                }
            } else {
                u8 *p; u8 *other; int i;
                p=*(u8 **)(*(u8 **)(d+0x2F8)+0x68);
                *(TodanoPartnerBlock *)(p+0x20)=*(TodanoPartnerBlock *)(d+0x20);
                func_PAL_002B3F18(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_PAL_002A7E68(*(u8 **)(d+0x2F8),o[0x43],0,2);
                *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
                if (!(*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)&0x80)) {
                    d[0x30F]=1;
                    if(o[0x95]!=9) func_002A7750(o,13,8);
                }
                { u8 *partner=*(u8 **)(d+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x10)) *(u16 *)(partner+0x7C)|=0x100; }
                { u8 *partner=*(u8 **)(d+0x2F8);
                if(!(*(u16 *)(partner+0x7C)&0x20)) *(u16 *)(partner+0x7C)|=0x200; }
                for(i=0;i<2;i++) {
                    p=d+0x2F0+i*4;
                    other=*(u8 **)p;
                    if(other && !((*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)>>(i+4))&1)) {
                        *(u16 *)(other+0x34)&=0xFFFD;
                        *(u8 **)p=0;
                    }
                }
            }
        }
    }
    if(o[0x31] && func_00282E48(o+0x10,D_L12_001B9E00)<24.0f) {
        func_002A93B0(o); o[0x6F]=22;
    }
    func_002B3BA8(o,*(int *)(d+0x2D8),0,0,0,0);
    func_L12_00414028(o);
}


extern int func_0029FCC0(u8 *,int,void *);
extern void func_002AEC48(void *,void *,int,float,float);
extern void func_L09_003F7788(u8 *,u8 *);
extern void func_002AAA00(void *,void *,int,float,float,float,float);
extern void func_PAL_L12_00417F48(u8 *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282E20(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern float func_002A7878(float,float);

void func_PAL_L12_004195E8(u8 *o) {
    u8 *d=*(u8 **)(o+0x68); float v[4]; int i;
    u8 *p=*(u8 **)(d+0x2F8);
    if(p && *(short *)(p+0xAA)==0x114B && p[0x20]!=254 && p[0x20]!=253) {
        func_L09_003F7788(o,p);
        func_0029FCC0(o,0,*(u8 **)(d+0x2F8)+0x10);
        func_002AAA00(*(u8 **)(d+0x2F8)+0xF8,d+0x2FC,0,*(float *)(d+0x2EC),*(float *)(d+0x114),*(float *)(d+0x118),*(float *)(d+0x11C));
        *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
        if(o[0x20]>=1 && o[0x20]<=3) func_PAL_L12_00417F48(o);
        if(*(int *)(d+0x204)==1 && !d[0x30F]) {
            func_0029FCC0(*(u8 **)(d+0x2F8),4,v);
            func_00282CF0(v,d+0x1F0,v);
            *(float *)(d+0x274)=func_00283BE0(-func_00283248(func_00282E20(v),v[2]),*(float *)(*(u8 **)(d+0x2F8)+0xF4));
            *(float *)(d+0x278)=func_00283BE0(func_00283248(v[0],v[1]),*(float *)(*(u8 **)(d+0x2F8)+0xF8));
        }
        func_002AEC48(*(u8 **)(d+0x2F8),d+0x210,3,0.028800001f,0.43200004f);
        if(!d[0x30F] && (*(u8 **)(d+0x2F8))[0x42]>=8 && (*(u8 **)(d+0x2F8))[0x42]<11) {
                for(i=0;i<2;i++) {
                    u8 *r=d+i*0x80;
                    if((*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)>>(i+4))&1) {
                        func_0029FCC0(*(u8 **)(d+0x2F8),i,v);
                        func_00282CF0(v,d+0x1F0,v);
                        *(float *)(r+0x384)=-func_00283248(func_00282E20(v),v[2]);
                        *(float *)(r+0x388)=func_00283BE0(func_00283248(v[0],v[1]),*(float *)(*(u8 **)(d+0x2F8)+0xF8));
                        if(i) { if(*(float *)(r+0x388)>0.087266475f) *(float *)(r+0x388)=0.087266475f; }
                        else { if(*(float *)(d+0x388)<-0.087266475f) *(float *)(d+0x388)=-0.087266475f; }
                    }
                }
        } else if(d[0x30F]) {
            u8 *r=d;
            for(i=1;i>=0;i--,r+=0x80) {
                *(float *)(r+0x384)=func_002A7878(-1.57079637f,1.57079637f)*0.5f;
                *(float *)(r+0x388)=func_002A7878(-1.57079637f,1.57079637f)*0.5f;
            }
        }
        for(i=0;i<2;i++) func_002AEC48(*(u8 **)(d+0x2F8),d+0x320+i*0x80,i+7,0.028800001f,0.43200004f);
    }
}

