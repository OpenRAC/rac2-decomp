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

/* func_PAL_L00_003B7A10, the PAL copy of func_L00_003B4018: the same C, with the frame time 1/50 and the next time scaled to 50 Hz. */
void func_PAL_L00_003B7A10(void)
{
    if(D_L00_001AF8F0) {
        int i;
        for(i=9;i>=0;i--) D_L00_0023D960[i].active=0;
        D_L00_001AF8F0=0;
        D_L00_001B28A0=0;
        D_L00_001B28A8=func_00283CF0(D_L00_001AF8F8/(D_L00_001AF934*0.020000001f));
        D_L00_001B28AC=1.0f/func_00283CE0(D_L00_001B28A8);
    }
    if(!D_L00_001B28A4 && func_00282948(&D_L00_001B28A0)) {
        int time=D_L00_001AF8F4;
        short on;
        unsigned short counter=*(unsigned short *)&D_L00_001B28A8;
        unsigned short delay=D_L00_001AF938;
        int next=D_L00_001B28A0;
        {
        Event *scan=D_L00_0023D960;
        do {
            if(!scan->active) {
                next=((s32)(time)*5+2)/6;
                on=1;
                scan->active=on;
                scan->counter=counter;
                scan->delay=delay;
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
        if(D_L00_0023D960[i].active && func_00282978(&D_L00_0023D960[i].counter)) D_L00_0023D960[i].active=0;
    }
    }
}
