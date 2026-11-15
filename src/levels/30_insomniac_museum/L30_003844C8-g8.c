#include "common.h"
extern int D_L30_001AEC90 __attribute__((sda));
extern char D_00189EA0[];
extern struct { char pad[0x24]; int pending; char gap[0x40]; int busy; short timer; char gap2[4]; unsigned short mode; } D_001A63A8;
extern int D_00138324 NOT_SDA;
extern void func_002A7750(void *,int,int),func_002B0CE0(int,int,int),func_002B6D28(void);
extern int func_L30_00384768(void *),func_L30_00384980(void *),func_L30_003848B8(void *),func_002ACBC8(void *,int);
extern void func_L08_002F2D10(void *,void *),func_L30_003847F8(char *);
/* Updates the museum exhibit selector (moby class 4878). It finds an active entry, shows it, and steps through the show and wait states. */
void func_L30_003844C8(unsigned char *obj) {
    char *st=*(char **)(obj+0x68);
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; D_L30_001AEC90=0;
        *(int *)(st+0x140)=-1; *(int *)(st+0x144)=0;
        SetMobyState(obj,1,-1); break;
    case 1: if(FindActiveExhibitEntry(obj)!=-1) SetMobyState(obj,2,-1); break;
    case 2:
        if(!IsPointInCuboid(gHeroPosition,*(int *)(st+0x140))) SetMobyState(obj,1,-1);
        else if(D_00138324&0x10) SetMobyState(obj,3,-1);
        else ForceClaimNotice(12,0x2801,1);
        break;
    case 3: if(ScheduleNextExhibitEntry(obj)) SetMobyState(obj,4,-1);
        QueueDrawCallback(DrawSelectedExhibitEntry,obj); break;
    case 4:
        if((short)gMusicState.mode==3 && gMusicState.timer<6000) {ResumeMusicStream();SetMobyState(obj,5,-1);}
        QueueDrawCallback(DrawSelectedExhibitEntry,obj); break;
    case 5:
        if(StartExhibitEntryTimer(obj)) SetMobyState(obj,6,-1);
        QueueDrawCallback(DrawSelectedExhibitEntry,obj); break;
    case 6:
        if((short)gMusicState.mode==3 && gMusicState.timer<6000) {ResumeMusicStream();SetMobyState(obj,7,-1);}
        QueueDrawCallback(DrawSelectedExhibitEntry,obj); break;
    case 7:
        if(*(unsigned short *)(obj+0x96)>=10 && gMusicState.busy==0 && gMusicState.pending==-1) SetMobyState(obj,2,-1);
        QueueDrawCallback(DrawSelectedExhibitEntry,obj); break;
    }
    if(obj[0x20]>=3) {
        ForceClaimNotice(1,0,1);
        if((D_00138324&0x10) && (gMusicState.busy!=0 || gMusicState.pending!=-1)) {
            if((unsigned)(gMusicState.mode-6)>=2) gMusicState.mode=5;
            SetMobyState(obj,2,-1);
        }
    }
    ++*(unsigned short *)(obj+0x96);
}
