#include "names.h"
/* func_PAL_L16_004114A0, the PAL copy of func_L16_0040C5F0: the same C, where rename func_002C6DD8 becomes func_PAL_002C7B18; wrap func_002A7820(D_L16_001B15E8,D_L16_001B15EC[0]) (((int). */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 rows[3]; } Triangle;
extern float math_random_float_range(float,float);
extern int math_random_int_range(int,int);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern char *part_spawn_trail_2_pal(void *,void *,int,float);
extern float g_sparkle_l16_speed_min __attribute__((sda));
extern float g_sparkle_l16_speed_max[] __attribute__((sda));
extern int g_sparkle_lifetime_min __attribute__((sda));
extern int g_sparkle_lifetime_max[] __attribute__((sda));
extern int g_sparkle_field_a __attribute__((sda));
extern int g_sparkle_field_b[] __attribute__((sda));
extern Triangle g_sparkle_triangle;
extern char g_particle_template[] __attribute__((sda));
void func_PAL_L16_004114A0(char *object)
{
    float weights[4];
    Vector128 point[1],temporary[1];
    Triangle triangle;
    int lifetime;
    float amount,reciprocal;
    char *effect;
    char *translation, *matrix;
    amount=-(math_random_float_range(g_sparkle_l16_speed_min,g_sparkle_l16_speed_max[0])*0.00040000002f);
    lifetime=(((int)(math_random_int_range(g_sparkle_lifetime_min,g_sparkle_lifetime_max[0])) * 5 + 2) / 6);
    {
        float *weight=weights;
        int i;
        for(i=2;i>=0;i--) *weight++=math_random_float_range(0.0f,1.0f);
    }
    matrix=object+0xc0;
    translation=object+0x10;
    reciprocal=1.0f/(weights[0]+weights[1]+weights[2]);
    {
        float *weight=weights;
        int i;
        for(i=2;i>=0;i--,weight++) *weight *= reciprocal;
    }
    triangle.rows[0]=g_sparkle_triangle.rows[0];
    triangle.rows[1]=g_sparkle_triangle.rows[1];
    triangle.rows[2]=g_sparkle_triangle.rows[2];
    FastVecScale(point,&triangle.rows[0],weights[0]);
    FastVecScale(temporary,&triangle.rows[1],weights[1]);
    FastVecAdd(point,point,temporary);
    FastVecScale(temporary,&triangle.rows[2],weights[2]);
    FastVecAdd(point,point,temporary);
    matrix_mul_vec3(point,point,matrix);
    FastVecAdd(point,point,translation);
    effect=part_spawn_trail_2_pal(point,g_particle_template,lifetime,amount);
    if(effect!=0) {
        *(int *)(effect+4)=g_sparkle_field_a;
        *(int *)(effect+12)=g_sparkle_field_b[0];
    }
}
