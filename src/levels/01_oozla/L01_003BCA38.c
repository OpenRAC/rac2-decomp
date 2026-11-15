#include "common.h"
extern void *CreateMoby(int);
extern float math_random_angle(void),math_random_float_range(float,float),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int);
extern void func_002A0F48(char *);
extern void FastVecScale(void *,void *,float);
extern float FastVecLength(void *);
extern void euler_rotation_basis(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastAddRotations(float,float);
extern int FloatToInt(float);
typedef struct L01DebrisHeader {
    char pad[0x20];
    unsigned char initialized;
    char pad21[3];
    char *definition;
    int field28;
    float scale;
    unsigned char alpha, flags;
} L01DebrisHeader;
/* Creates one debris piece with a random speed, spin and size, and launches it from the given position. */
char *debris_l01_spawn_piece(char *parent,int kind,void *position,void *rotation,int life,int mode,void *velocity,void *spin,void *dimensions,float speed)
{
    float temp[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float matrix[12] __attribute__((aligned(16)));
    char *piece=CreateMoby(kind);
    char *vars;
    float angle, magnitude;
    if(piece) {
        float scale=((L01DebrisHeader *)parent)->scale / *(float *)(((L01DebrisHeader *)parent)->definition+0x24);
        vars=*(char **)(piece+0x68);
        ((L01DebrisHeader *)piece)->scale=*(float *)(((L01DebrisHeader *)piece)->definition+0x24)*scale;
        ((L01DebrisHeader *)piece)->flags=1;
        *(long long *)(piece+0x38)=*(long long *)(parent+0x38);
        *(unsigned char *)(piece+0x20)=1;
        qcopy(piece+0x10,position);
        qcopy(piece+0xF0,rotation);
        euler_rotation_basis(piece+0xC0,rotation);
        *(unsigned char *)(piece+0x30)=255;
        *(short *)(piece+0x32)=128;
        *(float *)(vars+0x40)=math_random_angle();
        *(float *)(vars+0x38)=speed;
        if(kind==0xA28 /* moby class 2600 */) {
            *(float *)(vars+0x44)=0.349065899848938f;
            if(speed==0.0f) *(float *)(vars+0x38)=math_random_float_range(9.0f,15.0f)*0.0002777777845f;
            *(float *)(vars+0x3C)=math_random_float_range(-3.0f,-1.5f)*0.0166666675f;
        } else {
            *(float *)(vars+0x44)=1.5707964897155762f;
            if(!math_random_int_below(1)) *(float *)(vars+0x44)=-*(float *)(vars+0x44);
            if(*(float *)(vars+0x38)==0.0f) *(float *)(vars+0x38)=math_random_float_range(9.0f,12.0f)*0.0002777777845f;
            *(float *)(vars+0x3C)=math_random_float_range(-100.0f,-200.0f)*0.0166666675f;
        }
        *(int *)(piece+0x98)=0;
        if(!life) *(int *)(vars+0x30)=FloatToInt(math_random_float_range(180.0f,240.0f));
        else *(int *)(vars+0x30)=life;
        *(int *)(vars+0x34)=mode;
        if(FastVecLength(velocity)==0.0f) {
            if(FastVecLength(dimensions)==0.0f && *(float *)((char *)dimensions+12)==0.0f) angle=math_random_angle();
            else {
                euler_rotation_basis(matrix,rotation);
                matrix_mul_vec3(direction,dimensions,matrix);
                angle=mat_fast_helper_a(direction[0],direction[1]);
                angle=FastAddRotations(angle,math_random_float_range(-1.047197699546814f,1.047197699546814f));
            }
            magnitude=math_random_float_range(0.7f,1.8f)*0.0166666675f;
            temp[0]=math_fast_sin_or_cos_a(angle)*magnitude;
            temp[1]=math_fast_sin_or_cos_b(angle)*magnitude;
            temp[2]=0;
            qcopy(vars,temp);
        } else qcopy(vars,velocity);
        if(FastVecLength(spin)==0.0f) {
            temp[2]=math_random_float_range(0.013089971616864204f,0.03199770674109459f);
            qcopy(vars+0x10,temp);
        } else qcopy(vars+0x10,spin);
        if(FastVecLength(dimensions)==0.0f && *(float *)((char *)dimensions+12)==0.0f) {
            qcopy(temp,*(char **)(piece+0x24)+0x30);
            magnitude=*(float *)(piece+0x2C);
            magnitude*=0.0009765625f;
            FastVecScale(temp,temp,magnitude);
            temp[3]*=magnitude;
            qcopy(vars+0x20,temp);
        } else qcopy(vars+0x20,dimensions);
        func_002A0F48(piece);
    }
    return piece;
}
