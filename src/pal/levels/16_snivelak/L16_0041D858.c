#include "include_asm.h"

#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 position,angles,delta,step; } RotatingMoverWorkspace;
extern char *D_L16_001B2B1C MACRO_ADDR;
extern char D_00188660[];
extern float func_00283BE0(float,float);
extern float func_00283B98(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002E5CF8(int,int,char *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AD6F0(void *,void *,void *,void *);

void func_PAL_L16_0041D858(char *object)
{
    RotatingMoverWorkspace local;
    char *state=*(char **)(object+0x68);
    char *target;
    char *sound;
    qcopy(&local.position,(object+0x10));
    qcopy(&local.angles,(object+0xF0));
    if(*(unsigned char *)(object+0x20)==0) {
        *(unsigned char *)(object+0x30)=0xff;
        object[0x20]=1;
        *(int *)(state+0x70)=-1;
        if(*(short *)(object+0xaa)==0x10fc) {
            *(int *)(object+0x98)=0;
            *(unsigned short *)(object+0x34)=(*(unsigned short *)(object+0x34)|0x41)&0xefff;
        }
    }
    if(*(unsigned char *)(object+0x20)==1 && *(unsigned char *)(D_L16_001B2B1C+(*(int *)(state+0x6C)<<8)+0x20)==2) object[0x20]=2;
    if(*(unsigned char *)(object+0x20)==2) {
        if(*(int *)(state+0x68)==0) {
            if(*(short *)(object+0xaa)==0x10fe) {
                *(float *)(object+0xf8)=func_00283BE0(*(float *)(object+0xf8),0.0054454277f);
                func_00282F20(&local.step,object+0xC0,0.064f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fd) {
                *(float *)(object+0xf8)=func_00283BE0(*(float *)(object+0xf8),0.00540354f);
                func_00282F20(&local.step,object+0xC0,0.040000003f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fc) {
                *(float *)(object+0xf8)=func_00283BE0(*(float *)(object+0xf8),0.0054454277f);
                func_00282F20(&local.step,object+0xC0,0.052f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
                func_00282CC0(D_L16_001B2B1C+*(int *)(state+0x6C)*0x100+0x10,&local.step,D_L16_001B2B1C+*(int *)(state+0x6C)*0x100+0x10);
                sound=D_00188660+0x70**(int *)(state+0x70);
                if((*(char **)(sound+0x88))!=object || (*(unsigned char *)(sound+0x74))==0) *(int *)(state+0x70)=func_002E5CF8(0,4,object);
            }
        } else {
            if(*(short *)(object+0xaa)==0x10fe) {
                *(float *)(object+0xf8)=func_00283B98(*(float *)(object+0xf8),0.0054454277f);
                func_00282F20(&local.step,object+0xC0,-1.0f);
                func_00282F20(&local.step,&local.step,0.064f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fd) {
                *(float *)(object+0xf8)=func_00283B98(*(float *)(object+0xf8),0.0054454277f);
                func_00282F20(&local.step,object+0xC0,-1.0f);
                func_00282F20(&local.step,&local.step,0.040000003f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
            }
            if(*(short *)(object+0xaa)==0x10fc) {
                *(float *)(object+0xf8)=func_00283B98(*(float *)(object+0xf8),0.0054454277f);
                func_00282F20(&local.step,object+0xC0,-1.0f);
                func_00282F20(&local.step,&local.step,0.052f);
                func_00282CC0(object+0x10,&local.step,object+0x10);
                func_00282CC0(D_L16_001B2B1C+*(int *)(state+0x6C)*0x100+0x10,&local.step,D_L16_001B2B1C+*(int *)(state+0x6C)*0x100+0x10);
            }
        }
    }
    func_00282CF0(&local.delta,object+0x10,&local.position);
    func_002AD6F0(state+0x20,&local.delta,&local.angles,object+0xF0);
}


