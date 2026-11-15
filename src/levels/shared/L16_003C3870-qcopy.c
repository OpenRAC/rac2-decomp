#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern void func_L00_003253A0(char *,char *,char *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00283B98(float,float);
extern int func_00277258(void *,int,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *,void *,float);
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern Vector128 D_L16_001BFF70[2];
void func_L16_003C3870(char *object)
{
    Vector128 correction[1];
    char *state=*(char **)(object+0x68);
    float speed;
    func_L00_003253A0(object,state,state,*(float *)(state+0x20));
    FastVecAdd(object+0x10,object+0x10,state);
    *(float *)(object+0xf0)=FastAddRotations(*(float *)(object+0xf0),*(float *)(state+0x10));
    *(float *)(object+0xf4)=FastAddRotations(*(float *)(object+0xf4),*(float *)(state+0x14));
    *(float *)(object+0xf8)=FastAddRotations(*(float *)(object+0xf8),*(float *)(state+0x18));
    if (func_00277258(object+0x10,0,object,1.5f)!=0) {
        *(Vector128 *)(object+0x10)=D_L16_001BFF70[0];
        if (FastVecDot(state,&D_L16_001BFF70[1])<0.0f) {
            vec_scale_to_length(&D_L16_001BFF70[1],&D_L16_001BFF70[1],1.0f);
            speed=FastVecLength(state);
            FastVecScale(correction,&D_L16_001BFF70[1],-FastVecDot(state,&D_L16_001BFF70[1])*1.25f);
            FastVecAdd(state,state,correction);
            vec_scale_to_length(state,state,speed*0.5f);
        }
        *(int *)(state+0x24)=0;
        if (*(unsigned char *)(object+0x23)>0x60) object[0x23]=0x60;
    }
    if (func_00282948((int *)(state+0x24))!=0) {
        if (*(unsigned char *)(object+0x23)<5) func_0029F338(object);
        else object[0x23]=*(unsigned char *)(object+0x23)-4;
    }
}
