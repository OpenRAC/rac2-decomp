/* Initial source form, 30 October 2026. Profile -O2 -G8 -ffunction-sections.
 * US and US2: 0/1, 1824/1888 bytes, complete retail-sized 0x40 frame.
 * PAL lacks this catalogue function. Ordinary entity-base loads lower GP-relative,
 * unlike retail's absolute loads. Preserve this allocation witness only;
 * the canonical retained form has truthful absolute/GP address views.
 */
#include "common.h"
typedef float SequenceVector[4] __attribute__((aligned(16)));
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern unsigned char *D_L14_001B268C;
extern unsigned char D_00189E20[],D_0019B2E8[],D_L14_001B17A0[];
extern u8 D_001A7B33[],D_001A7AFA[],D_001A7B32[],D_001A7AFB[],D_001395E1[];
extern int D_001A79F0,D_001A7A00,D_00138324,D_L14_001FF4A4;
extern short D_001A63F0;
extern int D_L14_001A8FA0;
extern int D_L14_001A8FB4 __attribute__((sda));
extern int D_L14_001A8F00 MACRO_ADDR;
extern int func_002ACBC8(void *,int),func_002B3868(void *);
extern void func_002A7750(void *,int,int);
extern void func_L00_002B9D60(void *,void *,int,int),func_L00_003294F0(void *,int);
extern void func_L14_00426D18(void *),func_L14_00426E60(void *);
extern int func_L14_00427210(void *),func_L14_003DE8E8(void *);
extern void func_L14_003DE8F8(void *),func_L14_003DE990(void *);
extern int func_L00_0030DDB0(int,int);
extern void func_L00_002B2A40(int,int,void *);
extern void func_L01_00323310(int,int),func_L02_002B5F50(int);
extern void func_002A0430(int),func_002DF3F8(void *,void *),func_0029F338(void *);
extern int func_L00_002C42E0(int,int);
extern int func_00282948(void *);
extern float func_00283198(float);
extern void func_L00_002E6EF8(void *,void *),func_L14_00426DE8(void);
#define I(o) (*(int *)(p+(o)))
#define F(o) (*(float *)(p+(o)))

/* Prison sequence controller. The checkpoint vector is deliberately not
 * initialized here: retail fills its stack slot only on entry to state 5.
 * The state-4 checkpoint call therefore needs a source/lifetime witness
 * before this reconstruction can claim semantic equivalence. */
void func_L14_004265B8(unsigned char *m)
{
    SequenceVector checkpoint;
    unsigned char *p=*(unsigned char **)(m+0x68);
    unsigned char *first=D_L14_001B259C+I(0x3c)*256;
    unsigned char *second=D_L14_001B259C+I(0x40)*256;
    unsigned char *third=D_L14_001B259C+I(0x48)*256;
    unsigned char *pose,*other;
    int next;
    switch(m[0x20]) {
    case 0:
        m[0x30]=255; I(0x78)=125;
        if(D_0019B2E8[I(0x5c)+D_001A79F0*16]&128) {
            if(func_002ACBC8(D_00189E20+0x80,I(0x1c))) {
                pose=D_L14_001B268C+I(0x34)*128;
                func_L00_002B9D60(pose+0x30,pose+0x70,0,1);
                *(short *)(D_00189E20+0x247c)=0;
                D_001A7B33[0]=D_001A7AFA[0]=D_001A7B32[0]=D_001A7AFB[0]=1;
            }
            if(D_0019B2E8[I(0x60)+D_001A79F0*16]&128) {
                func_L14_00426D18(m);
                func_L00_003294F0(D_L14_001B259C+I(0x50)*256,1);
                next=7; goto state;
            }
        } else {
            *(short *)(D_00189E20+0x247c)=1;
            D_001A7AFA[0]=D_001A7B32[0]=D_001A7AFB[0]=D_001A7B33[0]=0;
        }
        if(D_0019B2E8[I(0x58)+D_001A79F0*16]&128) { func_L14_00426D18(m); next=5; goto state; }
        if(D_0019B2E8[I(0x64)+D_001A79F0*16]&128) { func_L14_00426D18(m); next=4; goto state; }
        if(D_0019B2E8[I(0x54)+D_001A79F0*16]&128) { next=3; goto state; }
        next=D_L14_001FF4A4?1:2; goto state;
    case 1:
        if(func_002ACBC8(D_00189E20+0x80,I(0x1c))) {
            func_L00_0030DDB0((int)D_L14_001B17A0,1);
            D_L14_001A8FA0=2; D_L14_001A8FB4=8;
            if(D_00138324&16) { next=6; goto state; }
        }
        break;
    case 2:
        if(func_002B3868(m)) {
            first=D_L14_001B259C+I(0x3c)*256;
            func_L00_002B9D60(first+0x10,first+0xf0,0x6f,1);
            func_L00_002B2A40(1,0x3f,first);
            if(D_001A63F0!=I(0x7c)) func_L01_00323310(I(0x7c),I(0x88));
            func_L14_00426E60(m);
        }
        if(func_L14_00427210(third)) {
            D_001395E1[0]=1; func_002A0430(I(0x54));
            func_002DF3F8(m+0xf0,m+0xf0);
            I(0x70)=3; next=6; goto state;
        }
        break;
    case 3:
        if(func_002B3868(m)) {
            func_L02_002B5F50(0); func_L00_002B9D60(m+0x10,m+0xf0,0,1);
            func_L14_00426D18(m); *(int *)(D_00189E20+0x24cc)=D_001A7A00;
            if(D_001A63F0!=I(0x80)) func_L01_00323310(I(0x80),I(0x88));
        }
        if(func_L14_003DE8E8(D_L14_001B259C+I(0x40)*256)) {
            func_002A0430(I(0x64)); func_002DF3F8(third+0x10,third+0xf0);
            I(0x70)=4; next=6; goto state;
        }
        break;
    case 4:
        if(func_002B3868(m)) {
            func_L14_003DE8F8(second);
            if(third && third[0x20]!=0xfe && third[0x20]!=0xfd) func_0029F338(third);
            other=D_L14_001B259C+I(0x44)*256;
            *(int *)(other+0x98)=0; *(u16 *)(other+0x34)=(*(u16 *)(other+0x34)|0x41)&0xefff;
            func_L00_002B9D60(third+0x10,third+0xf0,0x6f,1);
            func_L00_002B2A40(1,0x3f,first);
            if(D_001A63F0!=I(0x7c)) func_L01_00323310(I(0x7c),I(0x88));
            func_L14_00426E60(m);
        }
        if(func_002ACBC8(D_00189E20+0x80,I(0x18))) {
            func_002A0430(I(0x58)); func_002DF3F8(checkpoint,second+0xf0);
            I(0x70)=5; next=6; goto state;
        }
        break;
    case 5:
        if(func_002B3868(m)) {
            func_0029F338(first);
            other=D_L14_001B259C+I(0x44)*256;
            *(u16 *)(other+0x34)=(*(u16 *)(other+0x34)&0xffbe)|0x1000;
            *(int *)(other+0x98)=*(int *)(*(unsigned char **)(other+0x24)+0x10);
            pose=D_L14_001B268C+I(0x30)*128; qcopy(checkpoint,pose+0x30);
            if(D_00189E20[0x22b4]==1) func_L02_002B5F50(0);
            func_L00_002B9D60(checkpoint,D_L14_001B268C+I(0x30)*128+0x70,0,1);
            func_L14_003DE990(second);
            *(int *)(D_00189E20+0x24cc)=D_001A7A00;
            if(D_001A63F0!=I(0x80)) func_L01_00323310(I(0x80),I(0x88));
        }
        if(D_L14_001A8F00!=2 && D_L14_001B259C[I(0x4c)*256+0x20]>128) {
            func_002A0430(I(0x5c)); pose=D_L14_001B268C+I(0x34)*128;
            func_002DF3F8(pose+0x30,pose+0x70);
            D_001A7B33[0]=D_001A7AFA[0]=D_001A7B32[0]=D_001A7AFB[0]=1;
            *(short *)(D_00189E20+0x247c)=0;
            next=7; goto state;
        }
        break;
    case 6:
        if(func_002B3868(m)) { I(0x74)=I(0x78); I(0x6c)=I(0x78)*2; func_L00_002C42E0(0x6f,1); }
        if(func_00282948(p+0x74)) { next=I(0x70); goto state; }
        break;
    case 7:
        if(func_002B3868(m)) I(0x8c)=0;
        if(D_L14_001A8F00!=2 && I(0x8c)>=6 && D_001A63F0!=I(0x84)) func_L01_00323310(I(0x84),I(0x88));
        ++I(0x8c);
        break;
    }
    goto tail;
state:
    func_002A7750(m,next,-1);
tail:
    if(I(0x6c)) {
        func_00282948(p+0x6c);
        F(0x68)=func_00283198((float)I(0x6c)*1.5707964f/(float)I(0x78));
        func_L00_002E6EF8(func_L14_00426DE8,m);
    }
}
