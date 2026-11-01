#include "include_asm.h"

#include "common.h"
typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *D_L01_001B255C __attribute__((sda));
extern u8 *D_L01_001FE180[] NOT_SDA;
extern f32 func_00282E80(void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282FB8(void *, void *, f32);
extern s32 func_002A8AF0(void *, void *, s32);
extern f32 func_002A7878(f32,f32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern f32 func_00283B98(f32, f32);
extern s32 func_002A8C28(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 func_L01_003120A8(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32);
extern u8 *func_002BAA28(void *, void *, void *, u32, u32, s32, s32, s32, s32);
extern void func_L01_003DC9E0(void *, void *);
extern s32 func_L01_00321178(void *, void *);
extern s32 func_310648();
extern f32 func_310580(f32 x, f32 y);
extern s32 func_310528(s32 a, s32 b);
extern f32 func_2E3A48(f32 x);
extern f32 func_2E3A60(f32 x);
extern s32 func_00277F48(f32 radius, void *pos, s32 flag, void *obj, s32 arg);
extern u32 D_L01_001C3980[];
extern s32 func_00282948(void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern s32 func_00283CF0(f32);
extern s32 func_002E5DA0(s32, s32, void *, s32);
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_0019B4A8[];
extern u8 *D_L01_001B1F04 __attribute__((sda));
extern s32 func_L00_004290C0(void *);

void func_PAL_L01_003E10E8(void *arg, void *fallback) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *obj = arg;
    u8 *state = *(u8 **)(obj+0x68);
    u8 *target;
    u8 *path;
    s32 index = *(s32 *)(state+0x410);
    if (index != -1) {
        target = (u8 *)&D_L01_001B255C[index];
        if (!target) return;
        if (*(s16 *)(target+0xAA) == 0xA56) {
            if (func_00282E80(obj+0x10,target+0x10)>1.0f) {
                func_00282CF0(delta,obj+0x10,target+0x10);
                func_00282F20(delta,delta,1.0f);
                func_00282CC0(pos,target+0x10,delta);
            } else qcopy(pos,obj+0x10);
            if (pos[2] < *(f32 *)(target+0x18)+0.01f)
                pos[2] = *(f32 *)(target+0x18)+0.011f;
        } else if (*(s16 *)(target+0xAA) == 0xA53) {
            func_00283698(matrix,target+0xC0);
            func_00282CF0(delta,obj+0x10,target+0x10);
            func_002830C0(delta,delta,matrix);
            if (delta[0]>2.0f) delta[0]=2.0f;
            else if (delta[0]<-2.0f) delta[0]=-2.0f;
            if (delta[1]>5.0f) delta[1]=5.0f;
            else if(delta[1]<-5.0f) delta[1]=-5.0f;
            if (delta[2]<0.01f) delta[2]=0.01f;
            func_00283098(delta,delta,target+0xC0);
            func_00282CC0(pos,target+0x10,delta);
        } else qcopy(pos,obj+0x10);
        func_00282CF0(delta,pos,obj+0x10);
        func_00282FB8(delta,delta,0.120000005f);
        func_00282CC0(obj+0x10,obj+0x10,delta);
        if (*(f32 *)(obj+0x18)<pos[2]) *(f32 *)(obj+0x18)=pos[2]+0.001f;
    } else {
        s32 pathIndex=*(s32 *)(state+0x1FC);
        if(pathIndex!=-1) {
            path=D_L01_001FE180[pathIndex];
            if(path && !func_002A8AF0(obj+0x10,path+0x10,*(s32 *)path)) qcopy(obj+0x10,fallback);
        }
        {
            u8 *other = *(u8 **)(state + 0x248);
            if (other && (*(s16 *)(other + 0xAA) == 0xA56 ||
                          *(s16 *)(other + 0xAA) == 0xA53))
                *(s32 *)(state + 0x410) = (AttachObject *)other - D_L01_001B255C;
        }
    }
}



