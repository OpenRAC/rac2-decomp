#include "include_asm.h"

#include "common.h"
typedef struct { int id, sector, a, b, sound; } Slot;
typedef struct { char pad[0x4b40]; Slot slots[48]; } Disc;
extern Disc D_0014B540;
typedef struct { char pad[20]; short current, active; char pad24[24]; int sound; int slots[3]; } Cache;
extern Cache D_00152CD0 NOT_SDA;
typedef struct { char pad[0x17b0]; int sound; } SoundGlobals;
extern SoundGlobals D_00188660 NOT_SDA;
extern char D_001A9370[];
extern int D_001A93B0[8] __attribute__((sda));
extern char *D_001A7278[] __attribute__((sda));
extern int D_001B22A0 NOT_SDA;
extern int D_001B22B0[] __attribute__((sda));
extern void func_002FC3C0(int),func_PAL_00294EF8(int,int),func_0029CFB0(void *,void *,int),func_00132858(int),func_00132818(void);
extern int func_00132028(void),func_001326D8(char *);
extern void func_0026FEB8(char *,int),func_002946C0(int,int,void *);

void func_PAL_00295298(int id)
{
    int index=0,slot;
    char *data;
    int i;
    if(D_0014B540.slots[0].id==id) goto found;
    while(++index<48) {
        if(D_0014B540.slots[index].id==id) break;
    }
found:
    if(index==48)return;
    if(index==D_00152CD0.current) return;
    slot=0;
    D_00152CD0.current=index;
    if(D_00152CD0.slots[0]==index)goto slotfound;
    while(++slot<3) {
        if(D_00152CD0.slots[slot]==index)break;
    }
slotfound:
    func_002FC3C0(1);
    if(slot==3) {
        func_0026FEB8(D_001A9370,id);
        slot=0;
        func_PAL_00294EF8(id,0);
    }
    D_00152CD0.active=slot;
    data=(char *)((int)&D_00152CD0+slot*0xc800)+64;
    if((int)data<0x100000) {
        char *dst=(char *)(D_001B22A0+D_001B22B0[0]-0xc800);
        func_0029CFB0(dst,data,0xc80);
        data=dst;
    }
    for(i=0;i<52;i++) {
        char *e=(char *)&D_00188660+i*0x70;
        int *q=*(int **)(e+0x78);
        if(q && q[7]==4) *(int **)(e+0x78)=D_001A93B0;
    }
    if(D_00152CD0.sound) {
        func_00132858(D_00152CD0.sound);
        while(func_00132028()) {}
    }
    if(D_0014B540.slots[index].sound) {
        D_00152CD0.sound=func_001326D8(D_001A7278[0]+slot*0xc800);
        D_00188660.sound=D_00152CD0.sound;
    } else D_00152CD0.sound=0;
    func_00132818();
    func_002946C0(id,index,data);
}
