#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
extern char g_hero_state[];
typedef union { u8 b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;
#define H ((Hero *)D_00189E20)
extern int g_ground_check_inhibit __attribute__((sda)), g_hero_effect_inhibit;
extern unsigned int g_pad_pressed_flags __attribute__((section(".data")));
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

/* Works out the launch velocity that carries a thrown object from origin to the aimed target (v2.00 copy). */
void CalculateAimedLaunchVelocity_us2(Vector *output, Vector *origin, char *target_object,
                   float minimum, float maximum,
                   float speed, float acceleration, char *source_object)
{
    Vector projected, temporary, normal, target;
    Vector displacement, correction, origin_projection, target_projection;
    Vector gravity, working, source_position;
    float source_basis[12];
    Vector quaternion, axis, forward;
    float oriented_basis[12], rotation[12];
    Vector test_vector;
    float duration, reciprocal, angle, projection, plane_offset, factor, reach;
    float *target_data;
    if(source_object) {
        qcopy(&source_position,source_object+0x10);
        qcopy(source_basis+0,source_object+0xc0);
        qcopy(source_basis+4,source_object+0xd0);
        qcopy(source_basis+8,source_object+0xe0);
    } else {
        char *hero_object=H->ptr[0x2290/4];
        qcopy(&source_position,hero_object+0x10);
        qcopy(source_basis+0,&H->q[0x730/16]);
        qcopy(source_basis+4,&H->q[0x740/16]);
        qcopy(source_basis+8,&H->q[0x750/16]);
    }
    output->f[0]=1.0f; output->f[1]=0.0f; output->f[2]=0.0f; output->f[3]=0.0f;
    if(H->h[0x348/2]!=0 && g_hero_effect_inhibit==0)
        FastVecScale(&normal,H->ptr[0x2290/4]+0xe0,-1.0f);
    else cam_compute_view_direction((char *)&source_position,(char *)&normal,0);
    reach=maximum;
    if(!target_object) {
        if(H->i[0x2294/4]==1) stub_empty_8(29,1);
        if((g_pad_pressed_flags&4)!=0 && H->b[0x22bc]==0) {
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
            multiply_matrix3x3(oriented_basis,rotation,CAMERA_BASIS);
            plane_offset=-FastVecDot(&source_position,&normal);
            vec_scale_to_length(&test_vector,CAMERA_BASIS,1.0f);
            projection=FastVecDot(&normal,&test_vector);
            if(projection>0.0f) {
                factor=(FastVecDot(&normal,g_camera_eye_state)+plane_offset)/projection;
                FastVecScale(&test_vector,&test_vector,factor);
                FastVecSub(&test_vector,g_camera_eye_state,&test_vector);
                FastVecSub(&test_vector,&test_vector,g_camera_eye_state);
                FastVecScale(&temporary,&normal,FastVecDot(&test_vector,&normal));
                FastVecSub(&projected,&test_vector,&temporary);
                reach=FastVecLength(&projected);
                if(maximum<reach) reach=maximum;
                else if(reach<minimum) reach=minimum;
            }
            reach=maximum*math_ease_out_quad(reach/maximum);
            matrix_mul_vec3(output,output,oriented_basis);
        } else {
            matrix_mul_vec3(output,output,source_basis);
        }
        vec_scale_to_length(output,output,reach);
        FastVecAdd(&target,output,&source_position);
    } else {
        if((unsigned)(*(unsigned short *)(target_object+0xaa)-0xa8d)<=1 &&
            (target_data=(float *)moby_get_private_value_0((u8 *)target_object))!=0 && target_data[0]>0.0f) {
            if(g_ground_check_inhibit!=0 || H->h[0x348/2]!=0) {
                FastVecScale(&quaternion,target_object+0xe0,target_data[4]);
                FastVecAdd(&target,target_object+0x10,&quaternion);
            } else {
                qcopy(&target,target_object+0x10);
                target.f[2]+=target_data[4];
            }
        } else {
            qcopy(&target,target_object+0x10);
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
    FastVecScale(&origin_projection,&normal,projection);
    projection=FastVecDot(&target,&normal);
    FastVecScale(&target_projection,&normal,projection);
    FastVecScale(&gravity,&normal,acceleration*(duration*duration)*0.5f);
    FastVecSub(&working,&origin_projection,&target_projection);
    FastVecAdd(&working,&working,&gravity);
    FastVecScale(&working,&working,-1.0f);
    FastVecScale(&correction,&working,reciprocal);
    FastVecAdd(output,output,&correction);
}
