#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char D_L06_00287AC8[], D_L06_0021E830[], D_0018C750[];
extern unsigned char D_0019B4A8[][0x400];
typedef struct { char pad[0x70]; unsigned int timestamp; } L06Session;

typedef struct { char padding[0x464]; unsigned char flag[0]; } L06TriggerFlags;

typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x2294-0x90];
    int mode2294;
    char pad2298[4];
    int mode229C;
    char pad22A0[0x24B4-0x22A0];
    int mode24B4;
} L06HeroState;
typedef struct {
    unsigned short count;
    unsigned short unknown;
    unsigned int timestamp;
    unsigned int levels;
} L06StatRow;
extern L06StatRow D_0018C958[];
extern L06HeroState D_00189E20;
#define HERO (&D_00189E20)

extern unsigned char D_001A7B1F;
extern unsigned int D_001A7390;
extern int D_001A79F0;
extern char *D_L06_001B2828;
extern int D_L06_001B0BB8 __attribute__((sda));
extern unsigned int L06FrameSda SDATA(D_001A7390);
extern int L06LevelSda SDATA(D_001A79F0);
extern int func_002ACBC8(char *, int);
extern int func_00288E18(int, int);
extern float func_00282E48(void *, void *);
static __inline__ unsigned int L06StatLevelMask(unsigned int flags, int level)
{
    return flags & (1U << level);
}

void func_L06_00430C60(char *obj)
{
    char *s = *(char **)(obj+0x68), *p;
    unsigned short idx;
    int value;
    unsigned int now;
    switch (B(obj,0x20)) {
    case 0:
        B(obj,0x30)=255; B(obj,0x20)=1;
        I(s,0x10)=0; I(s,0x2c)=0;
        break;
    case 1:
        if (IsPointInCuboid((char *)HERO->position,I(s,0)) && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && !D_001A7B1F) {
            now=D_001A7390;
            if (now-D_0018C958[54].timestamp>1080 || !D_0018C958[54].timestamp) func_00288E18(0x9df,0x36);
            else if (D_0018C958[54].timestamp<now) D_0018C958[54].timestamp=now;
        }
        if (IsPointInCuboid((char *)HERO->position,I(s,0))) {
            idx=*(unsigned short *)(obj+0xb2);
            if (!((L06TriggerFlags *)D_L06_0021E830)->flag[(short)idx]) {
                value=D_0019B4A8[D_001A79F0][(short)idx>>1];
                if (!((idx&1) ? (value>>4)&7 : value&7)) {
                    if(HERO->mode24B4==0x27) {
                        unsigned short slot;
                        I(s,0x30)=1;
                        slot=*(unsigned short *)(obj+0xb2);
                        if(slot&1) {
                            if(((D_0019B4A8[L06LevelSda][(short)slot>>1]>>4)&7)!=7) D_0019B4A8[L06LevelSda][(short)slot>>1]+=16;
                        } else {
                            if((D_0019B4A8[L06LevelSda][(short)slot>>1]&7)!=7) D_0019B4A8[L06LevelSda][(short)slot>>1]+=1;
                        }
                    }
                    if(!I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && !I(s,0x30)) {
                        if(D_0018C958[55].count) {
                            now=L06FrameSda;
                            if(now-D_0018C958[55].timestamp>1080 || !D_0018C958[55].timestamp) func_00288E18(0x9e0,0x37);
                            else if(D_0018C958[55].timestamp<now) D_0018C958[55].timestamp=now;
                        } else {
                            now=L06FrameSda;
                            D_0018C958[55].count++;
                            if(D_0018C958[55].timestamp<now) D_0018C958[55].timestamp=now;
                            D_0018C958[55].levels|=(1<<D_001A79F0);
                            D_0018C958[55].levels|=0x80000000u;
                        }
                    }
                }
            }
        }
        if(IsPointInCuboid((char *)HERO->position,I(s,8))) {
            if(HERO->mode2294==0x37) I(s,0x2c)=1;
            if(I(s,0x2c) && HERO->mode2294!=0x37) {
                for(p=D_L06_001B2828;p;p=*(char **)(p+0x28)) {
                    if(*(short *)(p+0xaa)==0xb57 && fast_vec_dist(p+0x10,(char *)HERO->position)<3.0f && F(*(char **)(p+0x68),0)!=1.0f && I(s,0x2c)) {
                        I(s,0x2c)=0;
                        I(s,0x10)++;
                        if(I(s,0x10)==3 || I(s,0x10)==6) func_00288E18(0x9e2,0x39);
                    }
                }
            }
        }
        if(HERO->mode229C==0x12 && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && IsPointInCuboid((char *)HERO->position,I(s,4))) {
            I(s,0x14)++;
            if(IsPointInCuboid((char *)HERO->position,I(s,4)) && I(s,0x14)>240 && !D_0018C958[50].count) func_00288E18(0x9db,0x32);
        } else {
            if(HERO->mode229C==0x11) D_0018C958[50].count=65535;
            else I(s,0x14)=0;
        }
        if(IsPointInCuboid((char *)HERO->position,I(s,0x18))) D_L06_001B0BB8=1;
        if(IsPointInCuboid((char *)HERO->position,I(s,0x1c)) && !I(D_L06_00287AC8,0) && I(D_L06_00287AC8,0x24)==-1 && D_L06_001B0BB8) {
            if(D_0018C958[56].count) func_00288E18(0x9e1,0x38);
            else {
                now=D_001A7390;
                D_0018C958[56].count++;
                if(D_0018C958[56].timestamp<now) D_0018C958[56].timestamp=now;
                D_0018C958[56].levels|=(1<<D_001A79F0);
                D_0018C958[56].levels|=0x80000000u;
            }
        }
        if(D_001A7390-((L06Session *)D_0018C750)->timestamp>324000 && IsPointInCuboid((char *)HERO->position,I(s,0x34)) && !L06StatLevelMask(D_0018C958[12].levels, D_001A79F0)) func_00288E18(0x9b5,0xc);
        break;
    }
}
