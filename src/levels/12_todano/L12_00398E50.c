#include "common.h"

extern int func_0029FCC0(u8 *,int,void *);
extern void func_002AEC48(void *,void *,int,float,float);
extern void func_L09_003F7788(u8 *,u8 *);
extern void func_002AAA00(void *,void *,int,float,float,float,float);
extern void func_L12_00413108(u8 *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00282E20(void *);
extern float func_00283248(float,float);
extern float func_00283BE0(float,float);
extern float func_002A7878(float,float);

typedef struct TodanoPartnerBlock { float x[12]; } TodanoPartnerBlock;
typedef struct TodanoPartnerSlot { u8 pad[0x38]; u8 *object; u32 tail; } TodanoPartnerSlot;
extern TodanoPartnerSlot D_L12_001C44C0[];
extern u8 D_L12_001B9E00[];
extern void func_L12_004135A8(u8 *);
extern void func_L09_003F8858(u8 *);
extern void func_L12_00413CE0(u8 *);
extern void func_L09_003F77D0(u8 *);
extern void func_L12_00414028(u8 *);
extern int func_002B0ED8(u8 *, void *, int);
extern void func_002B3380(u8 *, void *, void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int func_002A77E0(int);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_00282D30(void *, void *, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(u8 *);
extern int func_002B3BA8(u8 *, int, int, int, float, float);

extern u8 D_L12_00188660[];

extern s32 func_315148();

extern void func_31E1D0();

extern s32 func_32D988();

extern s32 func_2F15C8(void *arg0);

extern void func_2F0A60(void *buf, s32 arg1, u32 arg2, s32 arg3, f32 x, f32 y, f32 z);

extern void func_322AF8(void *arg0, void *arg1);

extern void func_326948(void *arg0, void *arg1, s32 arg2, f32 x, f32 y);

extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);

extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);

extern void func_314008(void *arg0);

extern f32 func_2F2950(f32 x, f32 y);

extern s32 D_L12_001B2E9C __attribute__((sda));

extern s32 D_L12_001B2E9C_2;

extern u16 *D_L12_001FB960[];

extern s32 D_001A79F0 __attribute__((sda));

extern s32 func_002A8600(u8 **out, s32 kind, s32 arg2, s32 arg3);

extern s32 func_002A86E8(u8 **out, u32 value, s32 arg2, s32 arg3);

extern void func_L00_00325AE8(void *arg0, s32 arg1, f32 arg2, f32 arg3);

typedef struct UpdateVars {
    u8 pad[0x100];
    float direction[4];
    int pad110;
    int timer114;
    int timer118;
    int timer11C;
    u8 *partner;
} UpdateVars;
/* An offset from a small symbol is retail's tied lui/load and lui $at/store, kept out of delay
   slots: these globals are read and written as elements, not as bare symbols. */
extern u8 D_001A7AF8[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern int D_L12_001A8EFC[] __attribute__((sda));
extern int D_L12_001B2BE4[] __attribute__((sda));
extern u8 D_L12_001C0000[];
typedef struct HeroUpdateView {
    u8 pad[0x80];
    float pos[4];
    u8 pad90[0x50];
    float target[4];
    u8 padF0[0x20];
    float velocity[4];
} HeroUpdateView;
extern HeroUpdateView D_00189E20;
extern void func_L04_00423178(u8 *);
extern u8 *func_0029EFD0(int);
extern void func_002A0F48(u8 *);
extern void func_002A7750(void *, s32, s32);
extern void func_L01_003128C0(u8 *);
extern int func_L01_003245E0(u8 *, int, float);
extern void func_L01_003246D0(u8 *);
extern int func_00288AA0(void *, int);
extern void func_00288BE8(void *);
extern u8 *func_00288FB8(int);
extern void func_L00_0030DD70(void *,int);
extern void func_L01_00324550(int,int);
extern int func_002F5D10(void);
extern void func_0029F338(u8 *);
extern void func_002A8598(int,int);
extern void func_00288308(int);
extern void func_002B0A18(int,int);
extern void func_0029B3E0(int,int);
extern int func_00282948(int *);
extern int func_00283CF0(float);
extern float func_00282E80(void *,void *);
extern float func_00283C80(float,float);
extern float func_00282DF0(void *);
extern float func_00283B98(float,float);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AF1D0(u8 *,u8 *,int,int);


/* func_L12_003A0F00 is defined in L12_00398E50-mirror.c. */

/* func_L12_003A6F48 is defined in L12_00398E50-color-g8.c. */

/* Scales the tracked object's field by the level's own rate, for every match. */
void func_L12_003A6E18(u8 *object) {
    s32 mode = D_001A79F0;
    f32 scale = 1.2f;
    u8 *out;

    if (mode == 0 || mode == 0x12) {
        scale = 1.0f;
    }
    func_002A8600(&out, object[0x21], 0, 0);
    while (out != 0) {
        u8 *cur = out;

        if (cur[0x31] != 0) {
            u32 *f68 = *(u32 **)(cur + 0x68);

            if (*(s16 *)(cur + 0xAA) == *(s16 *)(object + 0xAA)) {
                f32 ratio = *(f32 *)(object + 0x2C) / *(f32 *)(*(u32 *)(object + 0x24) + 0x24);

                func_L00_00325AE8(cur + 0x10, f68[1], scale * ratio, 0.5f);
            }
        }
        func_002A86E8(&out, (u32)out, 0, 0);
    }
}

/* Inlined, so its 0.3f is a constant loaded at each call rather than a pseudo shared across
   the first call. */
static __inline__ void TurnJoint(void *self, void *joint, int index, float rate) {
    func_002AEC48(self,joint,index,rate,0.3f);
}

void func_L12_003B5240(u8 *self) {
    UpdateVars *v = *(UpdateVars **)(self + 0x68);
    float target[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float pitch, turn;
    float rate;
    int active;
    u8 *partner;
    func_L04_00423178(self);
    switch (self[0x20]) {
    case 0:
        if (!D_001A7AF8[7]) {
            partner = func_0029EFD0(0x127B);
            v->partner = partner;
            if (partner) {
                *(u16 *)(partner+0x32) = *(u16 *)(self+0x32);
                v->partner[0x30] = self[0x30];
                *(u64 *)(v->partner+0x38) = *(u64 *)(self+0x38);
                *(u32 *)(v->partner+0x78) = *(u32 *)(self+0x78);
                v->partner[0x31] = 1;
                func_002A0F48(v->partner);
                if (D_001397DC & 0x200000) func_002A7750(self,2,-1);
                else func_002A7750(self,1,-1);
            }
            func_L01_003128C0(self);
        } else {
            func_0029F338(self);
            return;
        }
        break;
    case 1:
        if (func_L01_003245E0(self,10,2.5f)) {
            func_L01_003246D0(self);
            if (func_00288AA0(D_L12_001C0000,0x75)) {
                func_00288BE8(D_L12_001C0000);
                func_002A7750(self,2,-1);
            }
        }
        break;
    case 2:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!func_002F5D10()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            *(u16 *)(v->partner+0x34) &= ~1;
            v->partner[0x31] = 1;
            if (D_001A7AF8[0x31]) func_002A7750(self,4,-1);
            else func_002A7750(self,3,-1);
        }
        break;
    case 3:
        if (D_001A7AF8[0x31]) func_002A7750(self,4,-1);
        else if (func_L01_003245E0(self,10,2.5f)) {
            func_L00_0030DD70(func_00288FB8(0x27D3),2);
            func_L01_003246D0(self);
        }
        break;
    case 4:
        if (!D_001A7AF8[0x31]) func_002A7750(self,3,-1);
        else if (func_L01_003245E0(self,10,2.5f)) {
            func_L01_00324550(0x27D4,-1);
            func_L01_003246D0(self);
            if ((D_00138324 & 0x10) && func_00288AA0(D_L12_001C0000,0x76)) {
                func_00288BE8(D_L12_001C0000);
                func_002A7750(self,5,-1);
            }
        }
        break;
    case 5:
        D_L12_001B2BE4[1] = 1;
        if (D_L12_001A8EFC[1] == 2) {
            self[0x31] = 0;
            {
                u16 flags = *(u16 *)(self+0x34) | 1;
                int partnerMode = D_L12_001A8EFC[1];
                *(u16 *)(self+0x34) = flags;
                if (partnerMode == 2) {
                    *(u16 *)(v->partner+0x34) |= 1;
                    v->partner[0x31] = 0;
                }
            }
        }
        if (!func_002F5D10()) {
            D_L12_001B2BE4[1] = 0;
            self[0x31] = 1;
            *(u16 *)(self+0x34) &= ~1;
            func_0029F338(v->partner);
            v->partner = 0;
            if (self[0x21] != 0xFF) func_002A8598(self[0x21],1);
            if (!D_001A7AF8[7]) {
                D_001A7AF8[0x31] = 0;
                D_001A7AF8[0x69] = 0;
                func_00288308(7);
                func_002B0A18(0x1245,-1);
                func_0029B3E0(0,-1);
                func_0029F338(self);
                return;
            }
        }
        break;
    }
    if (self[0x20] != 0) {
        if (self[0x43] < 2 && func_00282948(&v->timer11C)) {
            v->timer11C = func_00283CF0(func_002A7878(1200.0f,2400.0f));
            if (self[0x43] != 2) func_002A7470(self,2,0,10);
        }
        else if ((self[0x60] & 2) && self[0x43] == func_002A77E0(2))
            func_002A7470(self,func_002A77E0(2)==0,0,10);
    }
    rate = 0.02f;
    active = 0;
    if (self[0x43] == 0 || self[0x43] == 2) {
        active = 1;
        if (func_00282E80(self+0x10,D_00189E20.pos) < 8.0f &&
            func_00283C80(*(float *)(self+0xF8),func_00283248(D_00189E20.target[0]-*(float *)(self+0x10),D_00189E20.target[1]-*(float *)(self+0x14))) < 1.5707964897155762f) {
                if (func_00282DF0(D_00189E20.velocity) > 0.01f) v->timer114 = 120;
                else func_00282948(&v->timer114);
        } else if (v->timer114) {
            v->timer114 = 0;
            qcopy(v->direction,D_00189E20.target);
        }
        if (func_00282948(&v->timer118)) {
            float randomTurn;
            v->timer118 = func_00283CF0(func_002A7878(180.0f,300.0f));
            randomTurn = func_00283B98(*(float *)(self+0xF8),func_002A7878(-90.0f,90.0f)*0.01745329424738884f);
            pitch = func_002A7878(0.0f,30.0f)*0.01745329424738884f;
            func_002AF000(v->direction,6.0f,randomTurn,pitch);
            func_00282CC0(v->direction,v->direction,self+0x10);
        }
        if (v->timer114) {
            qcopy(target,D_00189E20.target);
            rate = 0.04f;
        } else qcopy(target,v->direction);
    }
    if (active) {
        qcopy(position,self+0x10);
        position[2] += 2.0f;
        func_00282CF0(delta,target,position);
        turn = func_00283BE0(func_00283248(delta[0],delta[1]),*(float *)(self+0xF8));
        pitch = -func_00283248(func_00282E20(delta),delta[2]);
        if (turn > 1.5707964897155762f) turn = 1.5707964897155762f;
        else if (turn < -1.5707964897155762f) turn = -1.5707964897155762f;
        if (pitch > 0.523598849773407f) pitch = 0.523598849773407f;
        else if (pitch < -0.523598849773407f) pitch = -0.523598849773407f;
        *(float *)((u8 *)v+0x64) = pitch;
        *(float *)((u8 *)v+0x68) = turn*0.6f;
        *(float *)((u8 *)v+0xE8) = turn*0.4f;
    }
    if (D_001A7A40) *(float *)((u8 *)v+0x70) = 2.75f;
    TurnJoint(self,v,0,rate);
    TurnJoint(self,(u8 *)v+0x80,1,rate);
    if (v->partner) func_002AF1D0(self,v->partner,2,0);
}

/* func_L12_003BE7D0 is defined in L12_003BE7D0-g8.c. */



/* func_L12_003D4110 is defined in L12_00398E50-spring-g8.c. */

/* func_L12_003DE4B0 is defined in L12_00398E50-g8.c (this unit has no $gp access for it). */

/* func_L12_003DF9A0 is defined in L12_00398E50-waypoint-g8.c. */

/* func_L12_003E04B8 is defined in L12_003E04B8-g8.c. */


/* func_L12_003E0858 is defined in L12_00398E50-launch-qcopy.c. */


/* func_L12_003E0BF0 is defined in L12_003E0BF0-g16.c. */

/* func_L12_003E1638 is defined in L12_00398E50-g8.c. */


/* Raises the measured flag on every record of the object's own table. */
void func_L12_003E1AA8(s32 a0) {
    s32 base;
    s16 *p;
    s16 *q;

    if (*(u8 *)(a0 + 0x21) == 0xFF)
        return;
    q = D_L12_001FB960[*(u8 *)(a0 + 0x21)];
    if (q == 0)
        return;
    p = q;
    base = D_L12_001B2E9C;
    do {
        u32 v = (*(u16 *)p & 0x7FFF) << 8;

        if (*(s8 *)(base + v + 0x20) >= 0) {
            if (*(s16 *)(base + v + 0xAA) == 0xFB4)
                *(u16 *)(*(u32 *)(base + v + 0x68) + 0x366) = 1;
        }
    } while (*p++ >= 0);
}

extern s32 *D_L12_001FEAC0[];
extern s32 func_002A8AF0(void *, void *, s32);
extern void func_002A7470(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);

u8 *func_L12_003E1B28(s32 index, u8 *obj)
{
    u16 *list = D_L12_001FB960[index];
    u16 *entry;
    u8 *found = 0;

    if (list == 0) {
        return 0;
    }
    entry = list;
    do {
        u8 *rec = (u8 *)D_L12_001B2E9C + (*entry & 0x7FFF) * 0x100;

        if (*(s16 *)(rec + 0xAA) == 0xFB4) {
            u8 *vars = *(u8 **)(rec + 0x68);
            s32 *zone = D_L12_001FEAC0[*(s32 *)(vars + 0x138)];

            if (func_002A8AF0(obj + 0x10, zone + 4, zone[0]) != 0) {
                if (rec[0x20] == 9) {
                    *(u16 *)(rec + 0x34) = (*(u16 *)(rec + 0x34) & 0xFFBE) | 0x1000;
                    *(s32 *)(rec + 0x98) = *(s32 *)(*(u8 **)(rec + 0x24) + 0x10);
                    if (rec[0x43] != 5) {
                        func_002A7470(rec, 5, 0, 10);
                    }
                    func_002A7750(rec, 10, -1);
                } else if (rec != 0 && rec[0x20] != 0xFE && rec[0x20] != 0xFD) {
                    func_002A7750(rec, 11, 4);
                    if (rec[0x43] != 7) {
                        func_002A7470(rec, 7, 0, 0x14);
                    }
                }
                *(u8 **)(vars + 0x374) = obj;
                found = rec;
                break;
            }
        }
    } while ((s16)*entry++ >= 0);
    return found;
}

/* func_L12_003EB470 is defined in L12_00398E50-g8.c. */

/* func_L12_00402B48 is defined in L12_00402B48-g16.c. */

/* func_L12_00402DF8 is defined in L12_00402DF8-g8.c. */

/* func_L12_00404778 is defined in L12_00398E50-g8.c (it reads a pointer through $gp). */


/* func_L12_00412548 is defined in L12_00398E50-collision.c. */

/* func_L12_00412898 is defined in L12_00412898-g8.c. */


/* func_L12_00412E50 is defined in L12_00412E50-g8.c. */

/* func_L12_00413108 is defined in L12_00413108-por.c. */

INCLUDE_ASM("asm/levels", func_L12_004135A8);


void func_L12_004141A8(u8 *o) {
    u8 *d = *(u8 **)(o+0x68);
    int old, result;
    if (!o[0x95]) func_L12_004135A8(o);
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
    result=func_002B0ED8(o,d+0x50,0);
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
                func_002B3380(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_L12_00413CE0(o);
                func_002ABBB8(*(u8 **)(d+0x2F8),d+0xD0,0,0,0,4,0,0,2,1,9,1,-1,0,0,0,-1,0,0x810001);
                func_L09_003F77D0(o);
                if (old>=4 && !func_002A77E0(2)) {
                    if (o[0x43]!=17) func_002A7470(o,17,0,5);
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
                func_002B3380(*(u8 **)(d+0x2F8),p+0x50,p+0x20);
                func_002A7470(*(u8 **)(d+0x2F8),o[0x43],0,3);
                *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
                if (!(*(u16 *)(*(u8 **)(d+0x2F8)+0x7C)&0x80)) {
                    d[0x30F]=1;
                    if(o[0x95]!=9) func_31E1D0(o,13,8);
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

void func_L12_00414670(u8 *o) {
    u8 *d=*(u8 **)(o+0x68); float v[4]; int i;
    u8 *p=*(u8 **)(d+0x2F8);
    if(p && *(short *)(p+0xAA)==0x114B && p[0x20]!=254 && p[0x20]!=253) {
        func_L09_003F7788(o,p);
        func_0029FCC0(o,0,*(u8 **)(d+0x2F8)+0x10);
        func_002AAA00(*(u8 **)(d+0x2F8)+0xF8,d+0x2FC,0,*(float *)(d+0x2EC),*(float *)(d+0x114),*(float *)(d+0x118),*(float *)(d+0x11C));
        *(float *)(*(u8 **)(d+0x2F8)+0x48)=*(float *)(o+0x48);
        if(o[0x20]>=1 && o[0x20]<=3) func_L12_00413108(o);
        if(*(int *)(d+0x204)==1 && !d[0x30F]) {
            func_0029FCC0(*(u8 **)(d+0x2F8),4,v);
            func_00282CF0(v,d+0x1F0,v);
            *(float *)(d+0x274)=func_00283BE0(-func_00283248(func_00282E20(v),v[2]),*(float *)(*(u8 **)(d+0x2F8)+0xF4));
            *(float *)(d+0x278)=func_00283BE0(func_00283248(v[0],v[1]),*(float *)(*(u8 **)(d+0x2F8)+0xF8));
        }
        func_002AEC48(*(u8 **)(d+0x2F8),d+0x210,3,0.02f,0.3f);
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
        for(i=0;i<2;i++) func_002AEC48(*(u8 **)(d+0x2F8),d+0x320+i*0x80,i+7,0.02f,0.3f);
    }
}

/* Clears the measured state word and, for the tracked object, the mirror. */
void func_L12_00412DA0(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u8 *tracked;

    *(s32 *)(object + 0x98) = 0;
    tracked = *(u8 **)(state + 0x2F8);
    if (tracked != 0) {
        if (*(s16 *)(tracked + 0xAA) == 0x114B) {
            if (*(u8 *)(tracked + 0x20) != 0xFE) {
                if (*(u8 *)(tracked + 0x20) != 0xFD)
                    *(s32 *)(tracked + 0x98) = 0;
            }
        }
    }
}

/* Copies the tracked object's timer into the state word, for both objects. */
void func_L12_00412DE0(u8 *object) {
    if (object != 0) {
        if (*(u8 *)(object + 0x20) != 0xFE) {
            if (*(u8 *)(object + 0x20) != 0xFD) {
                u8 *tracked;
                *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
                tracked = *(u8 **)(*(u8 **)(object + 0x68) + 0x2F8);
                if (tracked != 0) {
                    if (*(s16 *)(tracked + 0xAA) == 0x114B) {
                        if (*(u8 *)(tracked + 0x20) != 0xFE) {
                            if (*(u8 *)(tracked + 0x20) != 0xFD)
                                *(s32 *)(tracked + 0x98) = *(s32 *)(*(u8 **)(tracked + 0x24) + 0x10);
                        }
                    }
                }
            }
        }
    }
}

/* Registers the measured two-slot primitive on the given object. */
void func_L12_003E0B68(u8 *object) {
    s32 buffer[4];

    func_315148(object, 2, buffer);
    func_2F0A60(buffer, 0x2E, 0x8080FFFF, 1, 0.25f, 0.0f, 0.0f);
    func_2F0A60(buffer, 0xC, 0x8020F020, 1, 0.25f, 0.0f, 0.0f);
}

/* Advances the measured state machine of the given object. */
void func_L12_004124B0(u8 *object) {
    switch (object[0x20]) {
    case 0:
        if (func_32D988(object) != 0)
            func_31E1D0(object, 1, -1);
        break;
    case 1:
        if (*(f32 *)(object + 0x18) < 160.0f)
            *(f32 *)(object + 0x18) = *(f32 *)(object + 0x18) + 0.0833333358f;
        break;
    }
}

/* Re-arms the measured two-slot primitive after the counter step. */
void func_L12_003E07B0(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_322AF8(object, state + 0x50);
    func_326948(object, state + 0x6C0, 1, 0.03f, 0.3f);
    func_326948(object, state + 0x640, 0, 0.03f, 0.3f);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
}

/* Resets the measured slot state and re-arms the primitive. */
void func_L12_003E19F0(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    func_322AF8(object, state + 0x50);
    func_2F15C8(state + 0x360);
    func_2F15C8(state + 0x362);
    counter = *(u16 *)(object + 0x96);
    if (counter <= 0xFFFE)
        *(u16 *)(object + 0x96) = counter + 1;
    func_326948(object, state + 0x240, 1, 0.03f, 0.3f);
    func_326948(object, state + 0x2C0, 0, 0.03f, 0.3f);
}

/* Opens the measured window and starts the sub-object. */
void func_L12_003BF7D0(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u8 *record;
    s32 index;

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0x20;
        *(u16 *)(object + 0x32) = 0x20;
        *(s32 *)(state + 0) = -1;
    }
    *(f32 *)(object + 0xF8) = func_2F2950(*(f32 *)(object + 0xF8), 0.017453294f);
    index = *(s32 *)(state + 0);
    record = D_L12_00188660 + index * 0x70;
    if (*(u8 **)(record + 0x88) != object || *(u8 *)(record + 0x74) == 0)
        *(s32 *)(state + 0) = func_364DF8(0, 4, object);
    if (func_3205F8(object, 0x10000, 0) != 0)
        func_314008(object);
}
