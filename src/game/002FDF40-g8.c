#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char g_hero_state[];
typedef union { u8 b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;
#define H ((Hero *)D_00189E20)
extern int D_001A8CA0 __attribute__((sda)), D_001A8CA4;
extern unsigned int D_00138320 __attribute__((section(".data")));
extern float g_camera_eye_state[];
#define CAMERA_BASIS (&D_001B5340[0x230 / 4])
extern void FastVecScale(void *,void *,float);
extern void cam_compute_view_direction(char *,char *,int);
extern unsigned int stub_empty_8(int,int);
extern void vec_scale_to_length(void *,void *,float);
extern float FastVecDot(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern float FastVecLength(void *);
extern float math_ease_out_quad(float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern char *moby_get_private_value_0(u8 *);

/* Works out the launch velocity to throw something from a start point to a target (or where the player aims). */
void CalculateAimedLaunchVelocity(Vector *output, Vector *origin, char *targetObject,
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
        FastVecScale(&normal,H->ptr[0x2290/4]+0xe0,-1.0f);
    else cam_compute_view_direction((char *)&sourcePosition,(char *)&normal,0);
    reach=maximum;
    if(!targetObject) {
        if(H->i[0x2294/4]==1) stub_empty_8(29,1);
        if((D_00138320&4)!=0 && H->b[0x22bc]==0) {
            vec_scale_to_length(&forward,CAMERA_BASIS,1.0f);
            projection=FastVecDot(&forward,&normal);
            FastVecScale(&temporary,&normal,projection);
            FastVecSub(&projected,&forward,&temporary);
            vec_scale_to_length(&projected,&projected,1.0f);
            FastVecCross(&axis,&forward,&projected);
            angle=FastVecDot(&forward,&projected)*0.5f;
            FastVecScale(&quaternion,&axis,math_fast_sin_or_cos_b(angle));
            quaternion.f[3]=math_fast_sin_or_cos_a(angle);
            quaternion_to_rotation_basis(&quaternion,rotation);
            multiply_matrix3x3(orientedBasis,rotation,CAMERA_BASIS);
            planeOffset=-FastVecDot(&sourcePosition,&normal);
            vec_scale_to_length(&testVector,CAMERA_BASIS,1.0f);
            projection=FastVecDot(&normal,&testVector);
            if(projection>0.0f) {
                factor=(FastVecDot(&normal,g_camera_eye_state)+planeOffset)/projection;
                FastVecScale(&testVector,&testVector,factor);
                FastVecSub(&testVector,g_camera_eye_state,&testVector);
                FastVecSub(&testVector,&testVector,g_camera_eye_state);
                FastVecScale(&temporary,&normal,FastVecDot(&testVector,&normal));
                FastVecSub(&projected,&testVector,&temporary);
                reach=FastVecLength(&projected);
                if(maximum<reach) reach=maximum;
                else if(reach<minimum) reach=minimum;
            }
            reach=maximum*math_ease_out_quad(reach/maximum);
            matrix_mul_vec3(output,output,orientedBasis);
        } else {
            matrix_mul_vec3(output,output,sourceBasis);
        }
        vec_scale_to_length(output,output,reach);
        FastVecAdd(&target,output,&sourcePosition);
    } else {
        if((unsigned)(*(unsigned short *)(targetObject+0xaa)-0xa8d /* Swamp Monster I Arm or Eye */)<=1 &&
            (targetData=(float *)moby_get_private_value_0((u8 *)targetObject))!=0 && targetData[0]>0.0f) {
            if(D_001A8CA0!=0 || H->h[0x348/2]!=0) {
                FastVecScale(&quaternion,targetObject+0xe0,targetData[4]);
                FastVecAdd(&target,targetObject+0x10,&quaternion);
            } else {
                qcopy(&target,targetObject+0x10);
                target.f[2]+=targetData[4];
            }
        } else {
            qcopy(&target,targetObject+0x10);
        }
    }
    FastVecSub(&displacement,&target,origin);
    FastVecScale(&temporary,&normal,FastVecDot(&displacement,&normal));
    FastVecSub(&projected,&displacement,&temporary);
    vec_scale_to_length(output,&projected,speed);
    duration=FastVecLength(&projected);
    duration=duration/speed;
    reciprocal=1.0f/duration;
    projection=FastVecDot(origin,&normal);
    FastVecScale(&originProjection,&normal,projection);
    projection=FastVecDot(&target,&normal);
    FastVecScale(&targetProjection,&normal,projection);
    FastVecScale(&gravity,&normal,acceleration*(duration*duration)*0.5f);
    FastVecSub(&working,&originProjection,&targetProjection);
    FastVecAdd(&working,&working,&gravity);
    FastVecScale(&working,&working,-1.0f);
    FastVecScale(&correction,&working,reciprocal);
    FastVecAdd(output,output,&correction);
}
