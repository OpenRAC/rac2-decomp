/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* sol-high, 2026-10-29; retained near miss, no linked-build credit.
 * Current compiler profile: -O2 -G0 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier, in an isolated movement unit.
 * check.py --diff: 1256/1260 bytes, USA v1.01 0/3 places (levels 18, 19, 20).
 * This task did not check other releases or run a linked build.
 * Signed int mode read after clearing the flag restores the retail -1 test.
 * Separate phase locals, case 5 before case 4, and creating the rotation pointer
 * after vector subtraction restore the entry frame, FP registers and case order.
 * Branch-local scale assignments restore retail's split load/control-flow sequence.
 * Remaining: snapshot address is saved directly in s3 rather than copied v1->s4,
 * displacement takes s4 rather than s3, one object-scale load fills a likely slot
 * rather than occurring after it, and the velocity arm is one instruction short.
 * Three equivalent pointer/lifetime wordings tie at this output; reopen with an
 * explanation for the snapshot pointer's separate live ranges. Declarations below.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern float func_0029F530(char *);
extern int func_L07_00321D68(char *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00283248(float,float);
extern float func_002AAA00(float *,float *,int,float,float,float,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_L01_00321178(char *,char *);
extern void func_002B5278(unsigned char *,float);
extern void func_002B5258(char *);
extern int func_002B4FF0(char *,float *,float);
extern void func_002A7750(unsigned char *,int,int);
extern float func_L00_002EE290(void *);
extern void func_00283028(void *,void *,void *);
extern Vector128 D_L18_001BFC40;
void func_L18_003F6CA8(char *object)
{
    Vector128 local[1];
    char *state=*(char **)(object+0x68);
    int mode;
    float scale,heading;
    *(int *)(state+0x138)&=~2;
    mode=*(unsigned char *)(object+0x42);
    if(mode==-1) mode=*(unsigned char *)(object+0x43);
    switch(mode) {
    case 0: case 1: case 2: case 3: case 6: case 7: case 8: case 10:
        if(*(unsigned char *)(object+0x20)==16 && *(unsigned char *)(object+0x42)==2) {
            float phase=func_0029F530(object);
            if(phase>4.0f && phase<22.0f) {
                func_L07_00321D68(object,state+0x1a0);
                *(float *)(state+0x1a8)-=*(float *)(state+0x12c);
                return;
            }
            if(!(*(float *)(object+0x48)==-1.0f && phase<=4.0f)) return;
            func_002B5258(object);
            return;
        }
        if(*(unsigned char *)(object+0x20)==14) {
            float *rotation;
            if(*(unsigned char *)(object+0xbc)==0) return;
            func_00282CF0(local,state+0x230,object+0x10);
            rotation=(float *)(object+0xf8);
            func_00282F20(local,local,*(float *)(state+0x274)*0.016666668f);
            heading=func_00283248(*(float *)(state+0x230)-*(float *)(object+0x10),*(float *)(state+0x234)-*(float *)(object+0x14));
            func_002AAA00(rotation,(float *)(state+0x1b4),0,heading,*(float *)(state+0x114),*(float *)(state+0x118),*(float *)(state+0x11c));
            func_L07_00321D68(object,local);
            return;
        }
        if(*(unsigned char *)(object+0x20)==9) return;
        if(*(short *)(state+0x290)!=0) func_002B5278((unsigned char *)object,*(float *)(state+0x264));
        else func_002B5258(object);
        return;
    case 5: {
        float phase=func_0029F530(object);
        if(phase>10.0f && phase<17.0f && (*(unsigned int *)(state+0x194)&15)==0 && *(int *)(state+0x180)==0 && *(short *)(state+0x1c2)==0) {

            func_00282D30(local,object+0xc0,10.0f);
            func_00282CC0(local,object+0x10,local);
            func_L01_00321178(object,(char *)local);
            if(!(*(float *)(state+0x190)<=*(float *)(object+0x18))) return;
            if(*(float *)(state+0x1a8)>0.003333333647f) *(float *)(state+0x1a8)=0.003333333647f;
            return;
        }
        if(*(short *)(state+0x290)!=0) func_002B5278((unsigned char *)object,*(float *)(state+0x264));
        else func_002B5258(object);
        return;
    }
    case 4:
        func_002B4FF0(object,(float *)(state+0x230),*(float *)(state+0x24c));
        if(*(float *)(state+0x190)<=*(float *)(object+0x18) && *(float *)(state+0x1a8)>0.003333333647f) *(float *)(state+0x1a8)=0.003333333647f;
        if((unsigned int)(*(unsigned char *)(object+0x20)-11)>1) return;
        if(*(int *)(state+0x180)<16) return;
        if(*(float *)(state+0x1a8)<0.001f && *(int *)(state+0x184)==0) func_002A7750((unsigned char *)object,16,-1);
        return;
    case 9: {
        char *velocity=state+0x1a0;
        char *position;
        if(*(unsigned char *)(object+0x20)==2) return;
        scale=*(float *)(state+0x100);
        local[0]=*(Vector128 *)velocity;
        if(*(short *)(state+0x2a6)==0) {
            *(int *)(state+0x138)|=2;
            *(float *)(state+0x100)=(scale*(*(float *)(object+0x2c)))/(*(float *)(state+0x268));
        } else {
            *(float *)(state+0x100)=(scale*(*(float *)(object+0x2c)))/(*(float *)(state+0x268));
        }
        func_L07_00321D68(object,velocity);
        *(float *)(state+0x100)=scale;
        if(func_L00_002EE290(state+0x170)>0.0f && *(int *)(state+0x184)==0) {
            (*(short *)(state+0x294))++;
            position=object+0x10;
            func_00282CC0(position,position,state+0x170);
            func_00283028(velocity,local,&D_L18_001BFC40);
            func_00282D30(velocity,velocity,0.8f);
            func_00282CC0(position,position,velocity);
        }
        *(float *)(state+0x1a8)-=*(float *)(state+0x12c);
        return;
    }
    case 13:
        if(*(unsigned char *)(object+0x20)!=15) return;
        *(float *)(state+0x1a8)-=*(float *)(state+0x12c);
        func_L07_00321D68(object,state+0x1a0);
        return;
    }
}
