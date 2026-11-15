#include "common.h"
extern void func_L01_003CDEA8(u8 *);
extern void func_L01_003CDE58(u8 *);
extern void func_002A7470(void *,int,int,int);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern void func_L01_003CDD00(u8 *);
extern void func_L01_003CBCD8(u8 *, int, int, int);
extern u8 *D_L01_001FE180[];
extern int func_002A77E0(int);
extern void func_L01_00323310(int,int);
extern void func_002A7750(u8 *,int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282FB8(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern float func_00283248(float,float);
extern float func_00282DF0(void *);
extern void func_002A7CA0(void *,void *,float,float,float,float);
extern int func_002A8AF0(void *,void *,int);
extern void func_L01_00337A60(void *,void *,void *,int);
extern void func_002A8598(int,int);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);

/* Steps the owner state, moving along its path and releasing expired objects.
 * Separate unit for the jump table and small-data entity-base access. */
/* Moby update: Swamp Monster I Eye (class 2702, PS3 name). */
void func_L01_003CE228(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float f;
    func_L01_003CDEA8(a0);
    switch (a0[0x95]) {
    case 0:
        func_L01_003CDD00(a0);
        break;
    case 1:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !func_002A77E0(15)) {
                if (a0[0x43] != 2) func_002A7470(a0,2,0,10);
            } else if (a0[0x43] != 1) func_002A7470(a0,1,0,10);
        }
        if (*(int *)(state+0xBC)) {
            func_L01_00323310(*(int *)(state+0xD0),*(int *)(state+0xD8));
            if (a0[0x43]!=1) func_002A7470(a0,1,0,10);
            func_002A7750(a0,0,5);
        }
        break;
    case 2:
        if (!func_002A77E0(5)) func_L01_003CBCD8(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) &= 0xEFFF;
            if (a0[0x43]) func_002A7470(a0,0,0,10);
            *(float *)(a0+0x48)=0.0f;
            func_002A7750(a0,0,4);
        }
        break;
    case 3:
        if (!func_002A77E0(5)) func_L01_003CBCD8(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) |= 0x1000;
            if (a0[0x43]!=1) func_002A7470(a0,1,0,10);
            func_002A7750(a0,0,5);
        }
        break;
    case 4:
        if (*(int *)(state+0xBC)>0) {
            *(float *)(a0+0x48)=1.0f;
            if (a0[0x43]) func_002A7470(a0,0,0,10);
            func_002A7750(a0,0,3);
        }
        break;
    case 5:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !func_002A77E0(15)) {
                if (a0[0x43] != 2) func_002A7470(a0,2,0,10);
            } else if (a0[0x43] != 1) func_002A7470(a0,1,0,10);
        }
        {
            if (!*(int *)(state+0xBC)) qcopy(state+0x70,state+0x60);
            FastVecSub(v,state+0x70,a0+0x10);
            func_00282FB8(v,v,0.050000004f);
            FastVecAdd(a0+0x10,a0+0x10,v);
            f=func_00283248(*(float *)(state+0x80)-*(float *)(a0+0x10),*(float *)(state+0x84)-*(float *)(a0+0x14));
            MobySpringTurn(a0,state+0xB8,f,0.001163553f,0.1f,0.10471977f);
            if (!*(int *)(state+0xBC)) {
                func_L01_00323310(*(int *)(state+0xD4),*(int *)(state+0xDC));
                *(u16 *)(a0+0x34) &= 0xEFFF;
                if (a0[0x43] != 3) func_002A7470(a0,3,0,20);
                func_002A7750(a0,0,2);
            }
        }
        break;
    case 6:
        FastVecAdd(v,a0+0x10,state+0x90);
        if (point_in_path_xy(v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]))
            qcopy(a0+0x10,v);
        else {
            func_L01_00337A60(a0+0x10,v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]);
            FastVecSub(w,state+0x60,a0+0x10);
            vec_scale_to_length(w,w,0.033333335f);
            FastVecAdd(a0+0x10,a0+0x10,w);
        }
        f=FastVecLength(state+0x90)-0.0030555557f;
        if (f<0.0f) f=0.0f;
        vec_scale_to_length(state+0x90,state+0x90,f);
        if (*(float *)(state+0x20)<=0.0f && !func_002A77E0(4)) func_L01_003CBCD8(a0,3,10,1);
        if (a0[0x60]&2) {
            if (*(float *)(state+0x20)<=0.0f) {
                *(u16 *)(a0+0x34) &= 0xEFFF;
                func_002A7750(a0,0,7);
            } else {
                *(u16 *)(a0+0x34) |= 0x1000;
                if (a0[0x43]!=1) func_002A7470(a0,1,0,10);
                func_002A7750(a0,0,5);
            }
        }
        break;
    case 7:
        func_L01_00323310(*(int *)(state+0xD4),*(int *)(state+0xDC));
        if (*(int *)(state+0xB0)!=-1) func_002A8598(*(int *)(state+0xB0),1);
        SetDeathBits(a0,0x200,3);
        if (*(int *)(state+0xCC)!=-1) func_0029F338(D_L01_001B255C_base[0]+(*(int *)(state+0xCC)<<8));
        *(int *)(state+0xCC)=-1;
        func_0029F338(a0);
        return;
    }
    func_L01_003CDE58(a0);
}
