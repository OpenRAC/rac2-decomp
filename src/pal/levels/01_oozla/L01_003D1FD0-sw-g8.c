#include "include_asm.h"

#include "common.h"
extern void func_PAL_L01_003D1FD0(u8 *);
extern void func_L01_003CDE58(u8 *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern u8 *D_L01_001B255C_base[] __asm__("D_L01_001B255C") __attribute__((sda));
extern void func_L01_003CDD00(u8 *);
extern void func_PAL_L01_003CFDB0(u8 *, int, int, int);
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
extern void func_PAL_002A7650(void *,int,int);
extern void func_0029F338(void *);

/* Steps the owner state, moving along its path and releasing expired objects.
 * Separate unit for the jump table and small-data entity-base access. */
void func_PAL_L01_003D2350(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float f;
    func_PAL_L01_003D1FD0(a0);
    switch (a0[0x95]) {
    case 0:
        func_L01_003CDD00(a0);
        break;
    case 1:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !func_002A77E0(15)) {
                if (a0[0x43] != 2) func_PAL_002A7E68(a0,2,0,10);
            } else if (a0[0x43] != 1) func_PAL_002A7E68(a0,1,0,10);
        }
        if (*(int *)(state+0xBC)) {
            func_L01_00323310(*(int *)(state+0xD0),*(int *)(state+0xD8));
            if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
            func_002A7750(a0,0,5);
        }
        break;
    case 2:
        if (!func_002A77E0(5)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) &= 0xEFFF;
            if (a0[0x43]) func_PAL_002A7E68(a0,0,0,10);
            *(float *)(a0+0x48)=0.0f;
            func_002A7750(a0,0,4);
        }
        break;
    case 3:
        if (!func_002A77E0(5)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60] & 2) {
            *(u16 *)(a0+0x34) |= 0x1000;
            if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
            func_002A7750(a0,0,5);
        }
        break;
    case 4:
        if (*(int *)(state+0xBC)>0) {
            *(float *)(a0+0x48)=1.0f;
            if (a0[0x43]) func_PAL_002A7E68(a0,0,0,10);
            func_002A7750(a0,0,3);
        }
        break;
    case 5:
        if (a0[0x60] & 2) {
            if (a0[0x42] != 2 && !func_002A77E0(15)) {
                if (a0[0x43] != 2) func_PAL_002A7E68(a0,2,0,10);
            } else if (a0[0x43] != 1) func_PAL_002A7E68(a0,1,0,10);
        }
        {
            if (!*(int *)(state+0xBC)) qcopy(state+0x70,state+0x60);
            func_00282CF0(v,state+0x70,a0+0x10);
            func_00282FB8(v,v,0.060000002f);
            func_00282CC0(a0+0x10,a0+0x10,v);
            f=func_00283248(*(float *)(state+0x80)-*(float *)(a0+0x10),*(float *)(state+0x84)-*(float *)(a0+0x14));
            func_002A7CA0(a0,state+0xB8,f,0.0016755164f,0.1f,0.12566373f);
            if (!*(int *)(state+0xBC)) {
                func_L01_00323310(*(int *)(state+0xD4),*(int *)(state+0xDC));
                *(u16 *)(a0+0x34) &= 0xEFFF;
                if (a0[0x43] != 3) func_PAL_002A7E68(a0,3,0,20);
                func_002A7750(a0,0,2);
            }
        }
        break;
    case 6:
        func_00282CC0(v,a0+0x10,state+0x90);
        if (func_002A8AF0(v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]))
            qcopy(a0+0x10,v);
        else {
            func_L01_00337A60(a0+0x10,v,D_L01_001FE180[*(int *)(state+0xA8)]+0x10,*(int *)D_L01_001FE180[*(int *)(state+0xA8)]);
            func_00282CF0(w,state+0x60,a0+0x10);
            func_00282F20(w,w,0.040000003f);
            func_00282CC0(a0+0x10,a0+0x10,w);
        }
        f=func_00282DF0(state+0x90)-0.0044f;
        if (f<0.0f) f=0.0f;
        func_00282F20(state+0x90,state+0x90,f);
        if (*(float *)(state+0x20)<=0.0f && !func_002A77E0(4)) func_PAL_L01_003CFDB0(a0,3,10,1);
        if (a0[0x60]&2) {
            if (*(float *)(state+0x20)<=0.0f) {
                *(u16 *)(a0+0x34) &= 0xEFFF;
                func_002A7750(a0,0,7);
            } else {
                *(u16 *)(a0+0x34) |= 0x1000;
                if (a0[0x43]!=1) func_PAL_002A7E68(a0,1,0,10);
                func_002A7750(a0,0,5);
            }
        }
        break;
    case 7:
        func_L01_00323310(*(int *)(state+0xD4),*(int *)(state+0xDC));
        if (*(int *)(state+0xB0)!=-1) func_002A8598(*(int *)(state+0xB0),1);
        func_PAL_002A7650(a0,0x200,3);
        if (*(int *)(state+0xCC)!=-1) func_0029F338(D_L01_001B255C_base[0]+(*(int *)(state+0xCC)<<8));
        *(int *)(state+0xCC)=-1;
        func_0029F338(a0);
        return;
    }
    func_L01_003CDE58(a0);
}
