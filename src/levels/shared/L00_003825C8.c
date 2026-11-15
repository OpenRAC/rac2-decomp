#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_00282C48(float);
extern float func_00283C80(float,float);
/* Partial external field views; original complete object sizes are unknown. */
typedef struct { unsigned char prefix[0x158];float heading;unsigned char gap15C[0x34];char *target; } CameraTargetView;
typedef struct {
    unsigned char prefix[0x80];Vector4 position;unsigned char gap90[8];float heading;
    unsigned char gap9C[0xD8];float speed;unsigned char gap178[0x2118];char *object;
} PlayerTargetView;
extern CameraTargetView D_001B8C80;
extern PlayerTargetView D_00189E20;
/* Updates a marker object that follows the camera's target, and pushes it far away when the player is moving past it. */
void func_L00_003825C8(char *object)
{
    Vector4 difference, projected;
    float amount;
    if (D_001B8C80.target) {
        FIELD(Quadword,object,0x10)=FIELD(Quadword,D_001B8C80.target,0x30);
        FastVecSub(&difference,object+0x10,&gHeroState.position);
        amount=FastVecDot(&difference,gHeroState.object+0xE0);
        FastVecScale(&projected,gHeroState.object+0xE0,amount);
        FastVecSub(&difference,&difference,&projected);
        if (FloatAbs(amount)<2.5f) {
            if (FastVecLength(&difference)<0.1f ||
                FastDiffRots(gHeroState.heading,D_001B8C80.heading)<2.3561947f ||
                gHeroState.speed<0.0016666668f) {
                FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=15;
            }
            else {
                amount=FastVecDot(object+0x10,gHeroState.object+0xE0);
                FastVecScale(&projected,gHeroState.object+0xE0,amount);
                FastVecSub(&difference,object+0x10,&projected);
                amount=FastVecDot(&gHeroState.position,gHeroState.object+0xE0);
                FastVecScale(&projected,gHeroState.object+0xE0,amount);
                FastVecAdd(object+0x10,&difference,&projected);
            }
        }
    } else {
        FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=5;
    }
}
