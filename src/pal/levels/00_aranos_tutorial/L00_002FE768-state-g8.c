/* func_PAL_L00_002FE768, the PAL copy of func_L00_002FCBE8: the same C, where the angle becomes
   0.07330384f (6/5 of USA's) and the 4000 moby is skipped when D_001A79F0[0] is 0x33. */
#include "common.h"
typedef struct {
    char pad0[0x30]; int state, timer; char pad38[12]; short count; char pad46[10]; char *out; char pad54[0x138]; struct StateObject { char pad[0x95]; unsigned char alpha; } *objects[1];
} Context;
extern int D_001A79F0[] __attribute__((sda));
extern float D_L00_001B24B0[4] __attribute__((sda));
extern Context D_L00_001BCAC0;
extern void func_00282C88(void *);
extern void func_PAL_002E7270(void *);
extern void func_002ED260(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L00_002FC980(void);
extern void func_L00_00326048(void *, void *, unsigned int, unsigned int, float);
extern void func_L00_003618D8(void *);

void func_PAL_L00_002FE768(void) {
    int i;
    func_L00_002FC980();
    for(i=0;i<D_L00_001BCAC0.count;i++) {
            char *base=(char *)&D_L00_001BCAC0;
            char *obj=*(char **)(base+0x18C+i*4);
            if (obj && *(short *)(obj+0xAA)==0xE29) *(unsigned short *)(obj+0x34)|=0x800;
            if (*(short *)(obj+0xAA)==0xD54) func_PAL_002E7270(obj);
            if (obj && *(short *)(obj+0xAA)==4000 && D_001A79F0[0]!=0x33 && *(char **)(obj+0x68)) {
                func_L00_00326048(obj,*(char **)(obj+0x68)+12,0x80AAAAD2,0x80396464,0.07330384f);
            }
    }
    if(D_001A79F0[0]==0) {
        if(D_L00_001BCAC0.state==0) {
            if(D_L00_001BCAC0.timer<2) func_002ED260(*(char **)((char *)&D_L00_001BCAC0+0x70)+0x24000);
            func_00282C88(D_L00_001B24B0);
            D_L00_001B24B0[0]=-3.0f;
            { struct StateObject *object=D_L00_001BCAC0.objects[2];
              object->alpha=255;
              func_L00_002E6CF0(func_L00_003618D8,object); }
        } else if(D_L00_001BCAC0.state==2) {
            if(D_L00_001BCAC0.timer<2) func_002ED260(*(char **)((char *)&D_L00_001BCAC0+0x70)+0x24000);
            func_00282C88(D_L00_001B24B0);
            { struct StateObject *object=D_L00_001BCAC0.objects[1];
              object->alpha=255;
              func_L00_002E6CF0(func_L00_003618D8,object); }
        }
    }
}
