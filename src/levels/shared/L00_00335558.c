#include "common.h"

extern char *part_alloc(int);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern void copy_matrix_rotation(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int FloatToInt(float);
extern char *D_L00_001FE9B0;

#define FI(p, o) (*(int *)((char *)(p) + (o)))
#define FF(p, o) (*(float *)((char *)(p) + (o)))
#define FS(p, o) (*(short *)((char *)(p) + (o)))
#define FB(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Spawns a small spark that drifts away from a position with a random color. */
void part_spawn_spark_effect(char *position, char *matrix, float speed)
{
    float local[4], offset[4], velocity[4], inverse[16];

    char *effect=part_alloc(28);
    int r,g,b;
    char *motion;
    if (effect) {
        motion=effect+32;
        offset[0]=math_random_float_range(-0.03f,0.03f);
        offset[1]=math_random_float_range(-0.03f,0.03f);
        offset[2]=0;
        if (matrix) {
            copy_matrix_rotation(inverse,matrix);
            transform_vector(local,offset,inverse);
            FastVecAdd(effect+16,local,position);
        } else FastVecAdd(effect+16,offset,position);
        FF(effect,24)-=0.05f;
        r=func_001163B0()%96; if (!r) r=1;
        g=(func_001163B0()%r)%64; if (!g) g=1;
        b=(func_001163B0()%g)%48;
        FI(effect,4)=(r+143)|((g+143)<<8)|((b+111)<<16);
        FB(effect,9)=FloatToInt(4.0f)+64;
        FB(effect,3)=72; FB(effect,1)=0; FB(effect,8)=0;
        FB(effect,2)=FB(D_L00_001FE9B0,0);
        FF(motion,4)=math_random_float_range(0.0f,0.02234560064971447f)+0.00001f;
        FF(effect,12)=math_random_float_range(10080.0f,19950.0f);
        FF(motion,8)=0.0f; FS(effect,10)=252; FF(motion,12)=1.0f;
        qzero_nc(velocity);
        if (matrix) {
            velocity[0]=speed; velocity[2]=-0.0025f;
            matrix_mul_vec3(motion+16,velocity,matrix);
        } else {
            FF(motion,16)=math_random_float_range(-speed,speed);
            FF(motion,20)=math_random_float_range(-speed,speed);
            FF(motion,24)=-0.0025f;
        }
    }
}
