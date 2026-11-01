#include "common.h"
extern int D_001A79F8[] __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern int D_L00_001A903C MACRO_ADDR;
extern unsigned char D_001A7A70[] __attribute__((sda));
extern unsigned int D_001A7AF0 MACRO_ADDR;
typedef struct {
 char pad0[0x18c];
 unsigned short f18c;
 char pad18e[0x14e];
 unsigned short f2dc;
 char pad2de[0x142];
 unsigned short f420;
 char pad422[0x22];
 unsigned short f444;
 char pad446[0x172];
 unsigned short f5b8;
 char pad5ba[0xb2];
 unsigned short f66c;
} State_flags;
extern State_flags D_0018C958;
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 unsigned short f1bc;
 char pad1be[0x2];
 unsigned int f1c0;
 unsigned int f1c4;
 char pad1c8[0xc];
 unsigned short f1d4;
 char pad1d6[0xa];
 unsigned short f1e0;
 char pad1e2[0x2];
 unsigned int f1e4;
 unsigned int f1e8;
} State_stats;
extern State_stats D_0018C750;
extern unsigned short D_0018C84C[];
typedef struct {
 char pad0[0xfc]; unsigned short ffc; char padfe[0xbe];
 int f1bc;
 char pad1c0[0x3e];
 short f1fe;
 char pad200[0x20];
 short f220;
 char pad222[0x55e];
 int f780;
 int f784;
 int f788;
 int f78c;
 char pad790[0xab8];
 int f1248;
 char pad124c[0x208];
 short f1454;
 char pad1456[0xe3a];
 char * f2290;
 int f2294;
 char pad2298[0x4];
 int f229c;
 char pad22a0[0x25c];
 short f24fc;
} State_b;
extern State_b D_00189E20;

extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned char D_001A7AF8[] __attribute__((sda));


extern unsigned int D_001A7390 MACRO_ADDR;
extern int D_001B19C8 MACRO_ADDR;
typedef struct { char pad[0x100]; float x,y; } InputState;
extern InputState D_00138180;
extern unsigned char D_00139568[];
typedef struct { char pad[12]; int kind; char rest[0xd0]; } CountedEntry;
extern CountedEntry D_L00_00262570[];
extern int func_002E5E58(int,int,void *);
extern void func_002B0A18(int,int);
extern float func_00282C48(float);
extern int func_00288E18(int,int);
extern int func_0029D830(void);
extern void func_L00_002F59A8(void);
void func_L00_002A67F8(void)
{
    float v[4], mag;
    int sign,i,count;
    State_b *state;
    if((D_001A7AF0&0xbb50)==0xbb50 && !D_001A7A70[0xD]) {
        D_001A7A70[0xD]=1;
        (void)func_002E5E58(1,0,0);
        func_002B0A18(0x1233,-1);
        D_L00_001A903C=1;
    }
    if(!D_0018C958.f18c && D_001A79F0<5 && !D_0018C750.f1d4 && D_00189E20.f2294!=1 && D_00189E20.f2294!=29) {
        qzero_nc(v);
        v[0]=D_00138180.x;
        v[1]=D_00138180.y;
        mag=func_00282C48(v[0]);
        sign=v[0]<0.0f;
        state=&D_00189E20;
        switch(state->f780) {
        case 0:
            if(mag>0.8f) {
                state->f784=sign;
                state->f780=1;
                state->f788=0;
                state->f78c=0;
            }
            break;
        case 1:
            ++state->f788;
            if(mag<0.2f) {
                if(state->f788>=11) { state->f78c=0; state->f780=2; } else
                state->f780=0;
            } else if(state->f784!=sign) {
                if(state->f788>=11) { state->f78c=0; state->f780=3; } else
                state->f780=0;
            }
            break;
        case 2:
            ++state->f78c;
            if(mag>0.8f && sign!=state->f784) {
                state->f78c=0; state->f780=3;
                break;
            }
            if(D_00189E20.f78c>120) D_00189E20.f780=0;
            break;
        case 3:
            ++state->f78c;
            if(state->f78c>40 && state->f78c>state->f788+20) {
                if(D_0018C750.f1e0<65535) ++D_0018C750.f1e0;
                if(D_001A7390>D_0018C750.f1e4) D_0018C750.f1e4=D_001A7390;
                { unsigned int bit = 1u << D_001A79F0; D_0018C750.f1e8=(D_0018C750.f1e8|bit)|0x80000000u; }
                if(D_0018C750.f1e0>=2) func_00288E18(0x9ca,0x21);
                state->f780=0;
            } else if(mag<0.2f || sign==D_00189E20.f784) D_00189E20.f780=0;
            break;
        }
    }
    if(D_001B19C8>0 && (D_001B19C8&127)==0) {
        if(!D_0018C958.f2dc && !D_0018C84C[0]) {
            unsigned char *map=D_00139568;
            CountedEntry *entries=D_L00_00262570;
            count=0;
            for(i=0;i<56;i++) {
                if(!entries[*(unsigned char *)(i+(unsigned int)map)].kind && i!=10 && D_001A7AF8[i]) count++;
            }
            if(count>=9) func_00288E18(0x9e6,0x3d);
        }
        if(D_00189E20.f229c==17 && D_00189E20.f1bc>300 && !D_00189E20.f24fc && !D_0018C958.f5b8 && !D_00189E20.f1fe && *(int *)(*(char **)(D_00189E20.f2290+0x24)+0x134)) func_00288E18(0xa23,0x7a);
        if(D_001A79F8[2]==80 && !D_0018C958.f66c) {
            if(!D_001A7A70[7]) {
                D_001A7A70[7]=1;
                (void)func_002E5E58(1,0,0);
                func_002B0A18(0x1233,-1);
                D_L00_001A903C=1;
            }
            func_00288E18(0xa32,0x89);
        }
        if(!D_0018C958.f420) {
            State_b *hero=&D_00189E20;
            unsigned char *items=D_001A7A80;
            if(items[hero->f1248]&32) func_00288E18(0xa01,0x58);
        }
        if(D_001A79F0==5) D_0018C958.f444=65535;
    }
    if(!D_00189E20.f1454) D_00189E20.f220=0;
    else if(D_00189E20.f2294) ++D_00189E20.f220;
    if(D_00189E20.f220>90) {
        if(D_0018C750.f1bc<65535) ++D_0018C750.f1bc;
        if(D_001A7390>D_0018C750.f1c0) D_0018C750.f1c0=D_001A7390;
        { unsigned int bit = 1u << D_001A79F0; D_0018C750.f1c4=(D_0018C750.f1c4|bit)|0x80000000u; }
    }
    if(D_001B19C8<5 || (D_001B19C8&511)==21) func_0029D830();
    func_L00_002F59A8();
}
