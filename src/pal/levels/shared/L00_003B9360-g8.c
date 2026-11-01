#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;
typedef struct {Vector position,angles;} PartialCameraPose;
extern PartialCameraPose D_L00_001B8DC0;
typedef struct {unsigned char reserved[0x1A0];unsigned int held,pressed;} PartialInput;
extern PartialInput D_00138180;
typedef struct {unsigned char reserved[0x1FB0];float pitch,yaw;unsigned char middle[0x24B8-0x1FB8];float delta;} PartialRoot;
extern PartialRoot D_00189E20;
typedef struct { short vector[4]; int active; } PartialCameraLock;
extern PartialCameraLock D_L00_001B1BE0 __attribute__((sda));
extern int D_L00_001A8FF0;
extern Vector D_L00_001B1B10 MACRO_ADDR;
extern float D_L00_001AFA30 __attribute__((sda));
extern void func_002A7750(unsigned char *,int,int),func_003355A8(int);
extern void func_PAL_L00_002C4480(int,int),func_PAL_L00_002F5D28(void),func_002B0CE0(int,int,int);
extern void func_002833F0(float *,float *),func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern float func_002AA2E8(float *,float,float),func_00282E48(void *,void *),func_00282DB0(void *,void *),func_00282C48(float),func_00283248(float,float);
extern void func_002AFFD8(void *,void *,int),func_00282DD8(void *,void *,void *),func_002ACE78(void *,void *,float);
extern void func_00283958(void *,void *),func_00283738(void *,void *,void *);
extern void func_00335370(void *),func_002AB6D8(float *,float *),func_003353C8(void *);

void func_PAL_L00_003B9360(unsigned char *object)
{
    Vector position,angles;
    float matrix[12] __attribute__((aligned(16)));
    Vector movement,turn,cross,forward;
    float rotation[12] __attribute__((aligned(16)));
    float *state=*(float **)(object+0x68);
    float step,pitch,distance,projection;
    switch(object[0x20]) {
    case 0:
        func_002A7750(object,1,-1);
        break;
    case 1:
        break;
    case 2:
        if(D_00138180.pressed&0x200) {func_003355A8(0);func_PAL_L00_002C4480(0,1);func_002A7750(object,1,-1);}
        func_PAL_L00_002F5D28();
        object[0x31]=0;*(unsigned short *)(object+0x34)|=1;
        D_L00_001B1BE0.active=1;
        func_002B0CE0(6,0,1);
        qcopy(&position,&D_L00_001B8DC0.position);
        qcopy(&angles,&D_L00_001B8DC0.angles);
        func_002833F0(matrix,angles.v);
        if(D_00138180.held&0x10)func_002AA2E8(state,-0.8000001f,0.0028000001f);
        else if(D_00138180.held&0x40)func_002AA2E8(state,0.8000001f,0.0028000001f);
        func_00282F20(&movement,matrix,state[0]);
        func_00282CC0(&position,&position,&movement);
        step=D_L00_001AFA30*6.981318e-06f;
        if(D_00189E20.delta>0.1f)step*=D_00189E20.delta;
        func_002AA2E8(state+1,-D_00189E20.pitch*0.062831864f,step);
        func_002AA2E8(state+2,-D_00189E20.yaw*0.062831864f,step);
        func_002AFFD8(&position,&forward,1);
        func_00282DD8(&cross,matrix,&forward);
        pitch=state[2];
        if(D_L00_001A8FF0) {
            distance=func_00282E48(&position,&D_L00_001B1B10);
            projection=func_00282C48(func_00282DB0(&forward,&movement));
            pitch=state[2]+func_00283248(distance,state[0]-projection);
        }
        func_002ACE78(&turn,&forward,state[1]*0.5f);
        func_002ACE78(&cross,&cross,pitch*0.5f);
        func_00283958(&turn,rotation);
        func_00283738(matrix,rotation,matrix);
        func_00283958(&cross,rotation);
        func_00283738(matrix,rotation,matrix);
        func_00335370(&position);
        func_002AB6D8(matrix,angles.v);
        func_003353C8(&angles);
        break;
    }
}
