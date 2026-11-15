#include "common.h"
#define F(p,T,o) (((struct { char pad[o]; T v; } *)(p))->v)
typedef int B971Quad __attribute__((mode(TI)));
/* Only the first pointer slot at each absolute symbol is described here. */
extern char *D_L04_001B25CC[] __attribute__((sda)) NOT_SDA, *D_L04_001B24E8[] __attribute__((sda)) NOT_SDA, *D_L04_001B24DC[] __attribute__((sda)) NOT_SDA;
extern char D_L04_001B9540[] NOT_SDA, D_00189E20[] NOT_SDA;
extern int D_L04_001A8FE4, D_L04_001A8FE8;
extern int D_L04_001B0918 __attribute__((sda));
extern char *D_L04_001B08F4 __attribute__((sda));
extern void func_L04_0040E248(char *,char *),func_L04_0040A3B8(char *,int),func_L04_004195E0(char *);
extern void func_L00_002B9D60(void *,void *,int,int),func_0029F338(char *);
extern void func_L04_0040A310(char *),func_L04_0040A5C0(char *),func_0029B758(int,int);
/* Puts the race back at the start: moves the controller to its start spot, clears the race counters and hides or shows the racers. */
void func_L04_0040A958(char *controller,int hidden)
{
    float point[4] __attribute__((aligned(16))), rotation[4] __attribute__((aligned(16)));
    char *vars=F(controller,char *,0x68), *obj;
    *(B971Quad *)point=F((F(vars,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x30);
    *(B971Quad *)rotation=F((F(vars,volatile int,0x198)<<7)+(unsigned int)D_L04_001B25CC[0],B971Quad,0x70);
    F(D_L04_001B9540,int,0x16c)=F(D_L04_001B9540,int,0x188)=F(D_L04_001B9540,int,0x180)=F(D_L04_001B9540,int,0x168)=F(D_L04_001B9540,int,0x160)=0;
    ReleaseRacerSoundHandles(controller,vars);
    ResetRacerState(controller,0);
    InitHoverbikeRaceCourse(controller);
    ResetHeroPositionAndDirection(point,rotation,0x31,1);
    F(controller,unsigned char,0x20)=2;
    F(controller,B971Quad,0x10)=*(B971Quad *)point;F(controller,B971Quad,0xf0)=*(B971Quad *)rotation;
    F(controller,unsigned short,0x34)=(F(controller,unsigned short,0x34)&0xffbe)|0x400;
    F(vars,int,0x394)=150;
    F(controller,unsigned char,0x30)=255;
    F(vars,int,0x270)=0;
    gCurrentLap=0;gRaceTimeTicks=0;D_L04_001B0918=0;
    obj=D_L04_001B24E8[0];
    F(vars,int,0x31c)=0;
    for(;obj;obj=F(obj,char *,0x28)) {
        unsigned short type=F(obj,unsigned short,0xaa);
        if ((unsigned int)(type-0xabd /* moby class 2749 */)<2 || (short)type==0xb3d /* moby class 2877 */ || (short)type==0xb3e /* moby class 2878 */ || (short)type==0xb3f /* moby class 2879 */ || (short)type==0xb40 /* moby class 2880 */ || (short)type==0x27f /* moby class 639 */ || (short)type==0x70 /* moby class 112 */ || (short)type==0x7a /* moby class 122 */) MarkMobySpawned(obj);
    }
    RefreshActiveEffectRecords(controller);ActivateLinkedRacers(controller);
    F(gHeroState,int,0x24a0)=26;
    F(D_L04_001B9540,int,0x400)=0;
    F(gHeroState,unsigned char,0x22b7)=1;
    F(gHeroState,unsigned char,0x22b5)=1;
    F(F(gHeroState,char *,0x2290),int,0x98)=0;
    F(gHeroState,unsigned char,0x22c2)=1;
    if (hidden) {
        char *hiddenObj;
        F(controller,unsigned char,0xbc)=0;
        F(controller,unsigned short,0x34)|=0x41;
        StoreLevelObjectValuePair(0,0);
        if (F(vars,int,0x1dc)!=-1) {
            char *child;
            hiddenObj=gMobyPool_L04[0]+(F(vars,int,0x1dc)<<8);
            child=D_L04_001B08F4;
            F(hiddenObj,unsigned short,0x34)|=0x41;
            if(child) F(child,unsigned short,0x34)|=0x41;
        }
        { char *base=gMobyPool_L04[0];
        int noChild=-1;
        int i, *slot;
        for(slot=(int *)(vars+0x1e4),i=20;i>=0;i--,slot++) {
            if(*slot!=noChild) {
                char *child;
                hiddenObj=base+(*slot<<8);
                F(hiddenObj,unsigned short,0x34)|=0x41;
                child=F(F(hiddenObj,char *,0x68),char *,0x8c);
                if(child) F(child,unsigned short,0x34)|=0x41;
            }
        }
        }
    } else F(controller,unsigned char,0xbc)=2;
}
