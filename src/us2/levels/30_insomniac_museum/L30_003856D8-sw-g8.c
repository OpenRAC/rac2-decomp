#include "include_asm.h"

#include "common.h"
extern int D_L30_001AEC90 __attribute__((sda));
extern char D_00189EA0[];
extern struct { char pad[0x24]; int pending; char gap[0x40]; int busy; short timer; char gap2[4]; unsigned short mode; } D_001A63A8;
extern int D_00138324 NOT_SDA;
extern void func_002A7750(void *,int,int),func_002B0CE0(int,int,int),func_002B6D28(void);
extern int func_L30_00384768(void *),func_L30_00384980(void *),func_L30_003848B8(void *),func_002ACBC8(void *,int);
extern void func_L08_002F2D10(void *,void *),func_US2_L30_00385A08(char *);

void func_US2_L30_003856D8(unsigned char *obj) {
    char *st=*(char **)(obj+0x68);
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; D_L30_001AEC90=0;
        *(int *)(st+0x140)=-1; *(int *)(st+0x144)=0;
        func_002A7750(obj,1,-1); break;
    case 1: if(func_L30_00384768(obj)!=-1) func_002A7750(obj,2,-1); break;
    case 2:
        if(!func_002ACBC8(D_00189EA0,*(int *)(st+0x140))) func_002A7750(obj,1,-1);
        else if(D_00138324&0x10) func_002A7750(obj,3,-1);
        else func_002B0CE0(12,0x1BC7,1);
        break;
    case 3: if(func_L30_003848B8(obj)) func_002A7750(obj,4,-1);
        func_L08_002F2D10(func_US2_L30_00385A08,obj); break;
    case 4:
        if((short)D_001A63A8.mode==3 && D_001A63A8.timer<6000) {func_002B6D28();func_002A7750(obj,5,-1);}
        func_L08_002F2D10(func_US2_L30_00385A08,obj); break;
    case 5:
        if(func_L30_00384980(obj)) func_002A7750(obj,6,-1);
        func_L08_002F2D10(func_US2_L30_00385A08,obj); break;
    case 6:
        if((short)D_001A63A8.mode==3 && D_001A63A8.timer<6000) {func_002B6D28();func_002A7750(obj,7,-1);}
        func_L08_002F2D10(func_US2_L30_00385A08,obj); break;
    case 7:
        if(*(unsigned short *)(obj+0x96)>=10 && D_001A63A8.busy==0 && D_001A63A8.pending==-1) func_002A7750(obj,2,-1);
        func_L08_002F2D10(func_US2_L30_00385A08,obj); break;
    }
    if(obj[0x20]>=3) {
        func_002B0CE0(1,0,1);
        if((D_00138324&0x10) && (D_001A63A8.busy!=0 || D_001A63A8.pending!=-1)) {
            if((unsigned)(D_001A63A8.mode-6)>=2) D_001A63A8.mode=5;
            func_002A7750(obj,2,-1);
        }
    }
    ++*(unsigned short *)(obj+0x96);
}
