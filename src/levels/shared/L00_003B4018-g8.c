#include "common.h"

typedef struct { int time; short counter,delay,active,pad; } Event;
extern Event D_L00_0023D960[];
extern int D_L00_001AF8F0 __attribute__((sda));
extern int D_L00_001AF8F4 __attribute__((sda));
extern float D_L00_001AF8F8 __attribute__((sda));
extern float D_L00_001AF934 __attribute__((sda));
extern short D_L00_001AF938 __attribute__((sda));
extern int D_L00_001B28A0 MACRO_ADDR;
extern int D_L00_001B28A4;
extern int D_L00_001B28A8;
extern float D_L00_001B28AC;

extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern int func_00282948(int *);
extern int func_00282978(void *);

void func_L00_003B4018(void)
{
    if(D_L00_001AF8F0) {
        int i;
        for(i=9;i>=0;i--) D_L00_0023D960[i].active=0;
        D_L00_001AF8F0=0;
        D_L00_001B28A0=0;
        D_L00_001B28A8=FloatToInt(D_L00_001AF8F8/(D_L00_001AF934*(1.0f/60.0f)));
        D_L00_001B28AC=1.0f/IntToFloat(D_L00_001B28A8);
    }
    if(!D_L00_001B28A4 && FastFloatHelperD(&D_L00_001B28A0)) {
        int time=D_L00_001AF8F4;
        unsigned short counter=*(unsigned short *)&D_L00_001B28A8;
        unsigned short delay=D_L00_001AF938;
        int next=D_L00_001B28A0;
        {
        Event *scan=D_L00_0023D960;
        do {
            if(!scan->active) {
                scan->active=1;
                scan->counter=counter;
                scan->delay=delay;
                next=time;
                break;
            }
            scan++;
        } while ((int)scan<(int)(D_L00_0023D960+10));
        }
        D_L00_001B28A0=next;
    }
    {
    int i;
    for(i=0;i<10;i++) {
        if(D_L00_0023D960[i].active && FastDecTimer(&D_L00_0023D960[i].counter)) D_L00_0023D960[i].active=0;
    }
    }
}
