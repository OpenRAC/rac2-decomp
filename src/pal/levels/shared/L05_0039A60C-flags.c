#include "include_asm.h"

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
typedef struct { unsigned char prefix[0x158];float heading;unsigned char gap15C[0x34];char *target; } CameraTargetView;
typedef struct {
    unsigned char prefix[0x80];Vector4 position;unsigned char gap90[8];float heading;
    unsigned char gap9C[0xD8];float speed;unsigned char gap178[0x2118];char *object;
} PlayerTargetView;
extern CameraTargetView D_001B8C80;
extern PlayerTargetView D_00189E20;

void func_PAL_L05_0039A60C(char *object)
{
    Vector4 difference, projected;
    float amount;
    if (D_001B8C80.target) {
        FIELD(Quadword,object,0x10)=FIELD(Quadword,D_001B8C80.target,0x30);
        func_00282CF0(&difference,object+0x10,&D_00189E20.position);
        amount=func_00282DB0(&difference,D_00189E20.object+0xE0);
        func_00282D30(&projected,D_00189E20.object+0xE0,amount);
        func_00282CF0(&difference,&difference,&projected);
        if (func_00282C48(amount)<2.5f) {
            if (func_00282DF0(&difference)<0.1f ||
                func_00283C80(D_00189E20.heading,D_001B8C80.heading)<2.3561947f ||
                D_00189E20.speed<0.002f) {
                FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=15;
            }
            else {
                amount=func_00282DB0(object+0x10,D_00189E20.object+0xE0);
                func_00282D30(&projected,D_00189E20.object+0xE0,amount);
                func_00282CF0(&difference,object+0x10,&projected);
                amount=func_00282DB0(&D_00189E20.position,D_00189E20.object+0xE0);
                func_00282D30(&projected,D_00189E20.object+0xE0,amount);
                func_00282CC0(object+0x10,&difference,&projected);
            }
        }
    } else {
        FIELD(float,object,0x10)=FIELD(float,object,0x14)=FIELD(float,object,0x18)=5;
    }
}
