#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char D_00189E20[];
typedef union { u8 b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;
#define H ((Hero *)D_00189E20)
extern int D_001A8CA0 __attribute__((sda)), D_001A8CA4;
extern unsigned int D_00138320 __attribute__((section(".data")));
extern float D_001B5340[];
#define CAMERA_BASIS (&D_001B5340[0x230 / 4])
extern void func_00282D30(void *,void *,float);
extern void func_002AFFD8(char *,char *,int);
extern unsigned int func_PAL_0026F5B8(int,int);
extern void func_00282F20(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern float func_00283198(float), func_00283180(float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern float func_00282DF0(void *);
extern float func_002A7798(float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern int func_002AB1F0(u8 *);

void func_PAL_002FEF98(Vector *output, Vector *origin, char *targetObject,
                   float minimum, float maximum,
                   float speed, float acceleration, char *sourceObject)
{
    Vector projected, temporary, normal, target;
    Vector displacement, correction, originProjection, targetProjection;
    Vector gravity, working, sourcePosition;
    float sourceBasis[12];
    Vector quaternion, axis, forward;
    float orientedBasis[12], rotation[12];
    Vector testVector;
    float duration, reciprocal, angle, projection, planeOffset, factor, reach;
    float *targetData;
    if(sourceObject) {
        qcopy(&sourcePosition,sourceObject+0x10);
        qcopy(sourceBasis+0,sourceObject+0xc0);
        qcopy(sourceBasis+4,sourceObject+0xd0);
        qcopy(sourceBasis+8,sourceObject+0xe0);
    } else {
        char *heroObject=H->ptr[0x2290/4];
        qcopy(&sourcePosition,heroObject+0x10);
        qcopy(sourceBasis+0,&H->q[0x730/16]);
        qcopy(sourceBasis+4,&H->q[0x740/16]);
        qcopy(sourceBasis+8,&H->q[0x750/16]);
    }
    output->f[0]=1.0f; output->f[1]=0.0f; output->f[2]=0.0f; output->f[3]=0.0f;
    if(H->h[0x348/2]!=0 && D_001A8CA4==0)
        func_00282D30(&normal,H->ptr[0x2290/4]+0xe0,-1.0f);
    else func_002AFFD8((char *)&sourcePosition,(char *)&normal,0);
    reach=maximum;
    if(!targetObject) {
        if(H->i[0x2294/4]==1) func_PAL_0026F5B8(29,1);
        if((D_00138320&4)!=0 && H->b[0x22bc]==0) {
            func_00282F20(&forward,CAMERA_BASIS,1.0f);
            projection=func_00282DB0(&forward,&normal);
            func_00282D30(&temporary,&normal,projection);
            func_00282CF0(&projected,&forward,&temporary);
            func_00282F20(&projected,&projected,1.0f);
            func_00282DD8(&axis,&forward,&projected);
            angle=func_00282DB0(&forward,&projected)*0.5f;
            func_00282D30(&quaternion,&axis,func_00283198(angle));
            quaternion.f[3]=func_00283180(angle);
            func_00283958(&quaternion,rotation);
            func_00283738(orientedBasis,rotation,CAMERA_BASIS);
            planeOffset=-func_00282DB0(&sourcePosition,&normal);
            func_00282F20(&testVector,CAMERA_BASIS,1.0f);
            projection=func_00282DB0(&normal,&testVector);
            if(projection>0.0f) {
                factor=(func_00282DB0(&normal,D_001B5340)+planeOffset)/projection;
                func_00282D30(&testVector,&testVector,factor);
                func_00282CF0(&testVector,D_001B5340,&testVector);
                func_00282CF0(&testVector,&testVector,D_001B5340);
                func_00282D30(&temporary,&normal,func_00282DB0(&testVector,&normal));
                func_00282CF0(&projected,&testVector,&temporary);
                reach=func_00282DF0(&projected);
                if(maximum<reach) reach=maximum;
                else if(reach<minimum) reach=minimum;
            }
            reach=maximum*func_002A7798(reach/maximum);
            func_00283098(output,output,orientedBasis);
        } else {
            func_00283098(output,output,sourceBasis);
        }
        func_00282F20(output,output,reach);
        func_00282CC0(&target,output,&sourcePosition);
    } else {
        if((unsigned)(*(unsigned short *)(targetObject+0xaa)-0xa8d)<=1 &&
            (targetData=(float *)func_002AB1F0((u8 *)targetObject))!=0 && targetData[0]>0.0f) {
            if(D_001A8CA0!=0 || H->h[0x348/2]!=0) {
                func_00282D30(&quaternion,targetObject+0xe0,targetData[4]);
                func_00282CC0(&target,targetObject+0x10,&quaternion);
            } else {
                qcopy(&target,targetObject+0x10);
                target.f[2]+=targetData[4];
            }
        } else {
            qcopy(&target,targetObject+0x10);
        }
    }
    func_00282CF0(&displacement,&target,origin);
    func_00282D30(&temporary,&normal,func_00282DB0(&displacement,&normal));
    func_00282CF0(&projected,&displacement,&temporary);
    func_00282F20(output,&projected,speed);
    duration=func_00282DF0(&projected);
    duration=duration/speed;
    reciprocal=1.0f/duration;
    projection=func_00282DB0(origin,&normal);
    func_00282D30(&originProjection,&normal,projection);
    projection=func_00282DB0(&target,&normal);
    func_00282D30(&targetProjection,&normal,projection);
    func_00282D30(&gravity,&normal,acceleration*(duration*duration)*0.5f);
    func_00282CF0(&working,&originProjection,&targetProjection);
    func_00282CC0(&working,&working,&gravity);
    func_00282D30(&working,&working,-1.0f);
    func_00282D30(&correction,&working,reciprocal);
    func_00282CC0(output,output,&correction);
}
