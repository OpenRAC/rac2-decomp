#include "include_asm.h"

#include "common.h"
extern void func_L00_002FC980(void);
extern s32 D_001A79F0 MACRO_ADDR;
extern s32 func_002A77E0(s32);
extern void func_00283958(f32 *,f32 *);
extern void func_00282CF0(u8 *,u8 *,u8 *);
extern void func_00282F20(void *,void *,f32);
typedef struct SceneState {
    u8 pad00[0x30];
    s32 active, frame;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} SceneState;
extern SceneState D_L10_001BD380;
extern void func_002E64A0(u8 *);
extern void func_L00_00326048(u8 *,void *,u32,u32,f32);
extern void func_00283AF0(void *,void *);
extern void func_L01_0031A278(u8 *,void *,f32,f32,f32);
extern void func_L10_00425930(void *,s32,f32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern f32 func_002A78D8(f32,f32);
extern void func_L05_00419CC8(u8 *,void *,void *,s32,s32,s32,s32,s32,f32);
extern u8 D_L10_00296F00[];

/*
 * func_PAL_L10_00318FF8, the PAL copy of func_L10_00317528: the same C at 50 Hz (frames 0x195, 0x187,
 * 0x79 and 0x327 become 0x151, 0x146, 0x65 and 0x2A1, the effect's rates grow by 6/5), and the 0xFA0
 * objects are skipped while D_001A79F0 is 0x33. `type` gives 0xFA0 a longer life in the loop, so loop.c
 * hoists it on its first pass, ahead of the object pointer's giv init, and leaves 0x33 for the second.
 */
void func_PAL_L10_00318FF8(void) {
    f32 pos[4] __attribute__((aligned(16)));
    union { f32 matrix[12]; struct { f32 v[4]; f32 d[4]; } vectors; } scratch __attribute__((aligned(16)));
    u8 *p, *state, *entry;
    s32 i;
    f32 sign;
    func_L00_002FC980();
    for(i=0;i<D_L10_001BD380.count;i++) {
        u8 *object=D_L10_001BD380.objects[i];
        if(object && *(s16 *)(object+0xAA)==0xE29) *(u16 *)(object+0x34)|=0x800;
        if(*(s16 *)(object+0xAA)==0xD54) func_002E64A0(object);
        if(object) {
            s32 type=0xFA0;
            if(*(s16 *)(object+0xAA)==type && D_001A79F0!=0x33) {
                state=*(u8 **)(object+0x68);
                if(state) func_L00_00326048(object,state+0xC,0x80AAAAD2,0x80396464,0.07330384f);
            }
        }
    }
    if(D_001A79F0!=10 || D_L10_001BD380.active) return;
    p=D_L10_001BD380.objects[2];
    if(D_L10_001BD380.frame==0x151) {
        func_00283AF0(*(u8 **)(p+0x58)+0x10,scratch.matrix);
        func_00283958(scratch.matrix,(f32 *)(p+0xC0));
        func_L01_0031A278(p,pos,4.0f,3.0f,5.0f);
        func_L10_00425930(pos,1,1.5f,25,20,20,20,45,1,1,1,0);
        func_L01_0031A278(p,pos,9.0f,4.0f,4.0f);
        func_L10_00425930(pos,35,1.0f,50,30,30,30,50,1,1,1,1);
    }
    if(!((u32)(D_L10_001BD380.frame-0x146)<0x65 || D_L10_001BD380.frame>=0x2A1)) return;
    if(func_002A77E0(4)) return;
    sign=1.0f;
    if(func_002A77E0(2)) sign=-1.0f;
    entry=D_L10_00296F00+func_002A77E0(3)*32;
    func_L01_0031A278(p,pos,*(f32 *)entry,*(f32 *)(entry+4),*(f32 *)(entry+8));
    func_L01_0031A278(p,scratch.vectors.v,*(f32 *)(entry+0x10),*(f32 *)(entry+0x14),*(f32 *)(entry+0x18));
    scratch.vectors.v[0]+=func_002A78D8(0.5f,1.5f);
    scratch.vectors.v[1]+=func_002A78D8(0.5f,1.5f);
    scratch.vectors.v[2]+=func_002A78D8(0.5f,1.5f);
    func_00282CF0((u8 *)scratch.vectors.d,(u8 *)scratch.vectors.v,(u8 *)pos);
    func_00282F20(scratch.vectors.d,scratch.vectors.d,1.4000001f);
    /* The two packed RGB colours become the effect's start/end colours. */
    func_L05_00419CC8(p,pos,scratch.vectors.d,0x46BE20,0x327814,1,0,1,sign);
}
