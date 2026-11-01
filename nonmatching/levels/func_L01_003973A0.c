/* Closer C, 1 November 2026: -O2 -G8 -ffunction-sections -g -frac2-hazard-labels, 3 rows off:
 * retail mul x,y,z then stores x,y,z; here mul y,z,x and stores y,z,x. Registers and loads now agree.
 */
/*
 * GPT-6.1 Sol high, task v0752, USA v1.01: 1232/1232 bytes, 0/20 places.
 * Profile: -O2 -G8 -ffunction-sections -g -frac2-hazard-labels.
 * Nine non-relocation instructions differ, all in the initial angular-rate
 * loads/multiplies/stores at +0xC8..+0xF8 (f3/f4/f2 versus f4/f2/f3).
 * Required declarations are below. No linked match is claimed.
 *
 * Corrects two older-draft control-flow errors: state 0's -1/already-collected
 * test branches directly to deletion at 00397670, not to the p+0x78 test;
 * the inactive p+0x78==0 path branches directly to initialization at 003976B8,
 * bypassing state 3's D_0018A16E test.
 * Scoped player-copy pointers reproduce retail's s2/s3 moby/pvars allocation,
 * s0/s1 player-base lifetimes and both copy operand sequences. Pipeline each
 * angular step load before the preceding store to reproduce state 1 exactly.
 * Plain MACRO_ADDR CurrentLevel reproduces its mixed absolute/GP accesses.
 *
 * Initial-rate snapshot, pre-multiplied locals, incomplete-array GP view,
 * and reversed independent stores tie on the same nine instruction differences.
 * Direct global-to-field stores worsen scheduling. Next: independently justified
 * original vector/aggregate source shape; do not repeat scalar permutations.
 */
#include "common.h"
extern int D_001A79F0 MACRO_ADDR;
extern short D_0018A16E NOT_SDA;
extern unsigned char D_0019B278[];
extern char D_00189E20[];
extern int D_L01_001B22A8;
extern float D_L01_001AF50C __attribute__((sda));
extern float D_L01_001AF510 __attribute__((sda));
extern float D_L01_001AF514 __attribute__((sda));
extern float D_L01_001AF51C __attribute__((sda));
extern float D_L01_001AF528 __attribute__((sda));
extern float D_L01_001AF520 __attribute__((sda));
extern float D_L01_001AF524 __attribute__((sda));
extern int D_L01_001AF54C __attribute__((sda));
extern int D_L01_001AF550 __attribute__((sda));
extern int D_L01_001B21B0 __attribute__((sda));
extern int D_L01_001B1FA8 __attribute__((sda));
extern float func_002A7940(void);
extern float func_00283198(float);
extern float func_00283B98(float,float);
extern float func_00282E80(void*,void*);
extern float func_00282C48(float);
extern int func_002A77E0(int);
extern void func_L01_00397950(void*),func_L01_00397A28(void*),func_L01_00397EB0(void*),func_L01_00397110(void*),func_L01_00397C98(void*),func_L01_00397870(void*);
extern void func_002B0A18(int,int),func_0029B3E0(int,int),func_002E5CF8(int,int,void*),func_0029F338(void*),func_002A7750(void*,int,int),func_002A7470(void*,int,int,int);
extern void func_L00_002D2168(int,int,float),func_L00_002B9D60(void*,void*,int,int),func_003355A8(int);
extern int func_00282948(void*);

void func_L01_003973A0(unsigned char *m)
{
    char *p = *(char **)(m+0x68);
    int i;
    switch ((unsigned char)m[0x20]) {
    case 0:
        if (*(int *)p == -1 || D_0019B278[*(int *)p + (D_001A79F0 << 2)]) goto remove;
        {
            qcopy_nc(p+0x10,m+0x10);
            *(float *)(p+0x1C)=*(float *)(m+0xF8);
            *(float *)(m+0xF0)=func_002A7940();
            *(float *)(m+0xF4)=func_002A7940();
            *(float *)(m+0xF8)=func_002A7940();
            {
                float a=func_002A7940();
                float x=D_L01_001AF51C;
                float y=D_L01_001AF520;
                float z=D_L01_001AF524;
                *(float *)(m+0xFC)=a;
                z*=0.0002908882452175021f;
                x*=0.0002908882452175021f;
                y*=0.0002908882452175021f;
                *(float *)(p+0x68)=x;
                *(float *)(p+0x64)=y;
                *(float *)(p+0x60)=z;
            }
            if (*(short *)(m+0x32)<64) *(short *)(m+0x32)=64;
            m[0x20]=1;
            func_L01_00397950(m);
        }
        break;
    case 1: {
        char *player;
        *(float *)(m+0x2C)=*(float *)(*(char **)(m+0x24)+0x24)*D_L01_001AF50C;
        {
            float phase = func_00283198(*(float *)(m+0xFC));
            float height = *(float *)(p+0x18)+D_L01_001AF510+D_L01_001AF514*phase;
            float step = D_L01_001AF51C*0.0002908882452175021f;
            float angle;
            *(float *)(m+0x18)=height;
            angle=func_00283B98(*(float *)(m+0xF0),step);
            step=D_L01_001AF520*0.0002908882452175021f;
            *(float *)(m+0xF0)=angle;
            angle=func_00283B98(*(float *)(m+0xF4),step);
            step=D_L01_001AF524*0.0002908882452175021f;
            *(float *)(m+0xF4)=angle;
            angle=func_00283B98(*(float *)(m+0xF8),step);
            step=D_L01_001AF528*0.0002908882452175021f;
            *(float *)(m+0xF8)=angle;
            *(float *)(m+0xFC)=func_00283B98(*(float *)(m+0xFC),step);
        }
        func_L01_00397A28(m);
        if (!func_002A77E0(D_L01_001AF54C)) func_L01_00397EB0(m);
        player=D_00189E20+0x80;
        if (!(func_00282E80(m+0x10,player)<3.0f)) break;
        player -= 0x80;
        if (func_00282C48(*(float *)(m+0x18)-*(float *)(player+0x88))<2.0f &&
            *(int *)(player+0x24CC) &&
            ((unsigned char)player[0x22B4]==3 || !player[0x22B4])) {
            if (!*(short *)(p+0xC) && *(int *)(player+0x2294)!=0x31) goto inactive;
            D_L01_001B21B0=180;
            func_002B0A18(0x124B,-1);
            D_0019B278[*(int *)p+(D_001A79F0<<2)]=1;
            D_L01_001AF550++;
            func_0029B3E0(0,-1);
            func_002E5CF8(1,0,m);
        remove:
            func_0029F338(m);
        }
        break;
    }
    inactive:
        if (*(int *)(p+0x78)) {
            *(unsigned short *)(m+0x34) |= 0x41;
            func_002A7750(m,3,-1);
            break;
        }
        goto initialize;
    case 3:
        if (D_0018A16E) break;
    initialize:
        func_L01_00397110(m);
        break;
    case 2: {
        {
            char *player = D_00189E20;
            D_L01_001B22A8=1;
            *(short *)(player+0x1DC)=3;
            func_L01_00397C98(m);
            qcopy_nc(m+0x10,player+0x80);
            player += 0x90;
            qcopy_nc(m+0xF0,player);
        }
        if ((unsigned char)m[0x42]==1) {
            func_L01_00397870(m);
            if (!func_002A77E0(10)) func_L01_00397EB0(m);
            if (m[0x60]&2) {
                if (m[0x43]) func_002A7470(m,0,0,0);
                *(unsigned short *)(m+0x34)|=1;
                m[0x31]=0;
                for (i=3;i>=0;i--) func_L01_00397EB0(m);
            }
        }
        {
        char *player = D_00189E20;
        if (*(int *)(player+0xC28)&2) func_L00_002D2168(0,0,30.0f);
        if (!m[0x42] && func_00282948(p+0x6C)) {
            D_L01_001B21B0=180;
            func_002B0A18(0x124B,-1);
            D_0019B278[*(int *)p+(D_001A79F0<<2)]=1;
            D_L01_001AF550++;
            D_L01_001B1FA8=0;
            func_L00_002B9D60(player+0x80,player+0x90,0,0);
            func_003355A8(0);
            func_0029B3E0(0,-1);
            func_0029F338(m);
        }
        }
        break;
    }
    }
}
