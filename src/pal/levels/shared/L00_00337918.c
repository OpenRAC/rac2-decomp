#include "include_asm.h"

#include "common.h"
extern char *part_alloc(int);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern void copy_matrix_rotation(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern int FloatToInt(float);
extern char *g_spark_effect_byte;
#define FI(p, o) (*(int *)((char *)(p) + (o)))
#define FF(p, o) (*(float *)((char *)(p) + (o)))
#define FS(p, o) (*(short *)((char *)(p) + (o)))
#define FB(p, o) (*(unsigned char *)((char *)(p) + (o)))

/* Spawns a spark particle at position with a random colour and velocity (PAL). */
void part_spawn_spark_effect_pal(char *position, char *matrix, float speed)
{
    float local[4], offset[4], velocity[4], inverse[16];

    char *p=part_alloc(28);
    int r,g,b;
    char *q;
    if (p) {
        q=p+32;
        offset[0]=math_random_float_range(-0.03f,0.03f);
        offset[1]=math_random_float_range(-0.03f,0.03f);
        offset[2]=0;
        if (matrix) {
            copy_matrix_rotation(inverse,matrix);
            transform_vector(local,offset,inverse);
            FastVecAdd(p+16,local,position);
        } else FastVecAdd(p+16,offset,position);
        FF(p,24)-=0.05f;
        r=func_001163B0()%96; if (!r) r=1;
        g=(func_001163B0()%r)%64; if (!g) g=1;
        b=(func_001163B0()%g)%48;
        FI(p,4)=(r+143)|((g+143)<<8)|((b+111)<<16);
        FB(p,9)=FloatToInt(4.0f)+64;
        FB(p,3)=72; FB(p,1)=0; FB(p,8)=0;
        FB(p,2)=FB(g_spark_effect_byte,0);
        FF(q,4)=math_random_float_range(0.0f,0.02234560064971447f)+0.00001f;
        FF(p,12)=math_random_float_range(10080.0f,19950.0f);
        FF(q,8)=0.0f; FS(p,10)=210; FF(q,12)=1.0f;
        qzero_nc(velocity);
        if (matrix) {
            velocity[0]=speed; velocity[2]=-0.0025f;
            matrix_mul_vec3(q+16,velocity,matrix);
        } else {
            FF(q,16)=math_random_float_range(-speed,speed);
            FF(q,20)=math_random_float_range(-speed,speed);
            FF(q,24)=-0.0025f;
        }
    }
}


