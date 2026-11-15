#include "names.h"
/* Manual C reconstruction from verified R5900 retail.
 * Complete vectors/records and observed mixed-bank call inputs are retained.
 */
typedef unsigned int Word128 __attribute__((mode(TI)));
typedef union { Word128 word; float f[4]; } Vector;
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);

/* Place the output on the selected side of the fixed horizontal axis. */
/* Finds a point 6.5 units to one side of the object, across a fixed line on the ground, depending on which side the object is on. */
void func_L04_00412AF8(unsigned char *object,Vector *output)
{
    Vector origin,axis,difference,direction;
    origin.word=0;axis.word=0;
    origin.f[0]=604.7000122070312f;origin.f[1]=812.5f;origin.f[2]=327.95001220703125f;
    axis.f[0]=0.8644319772720337f;axis.f[1]=0.5027499794960022f;
    FastVecSub(&difference,object+0x10,&origin);
    difference.f[2]=0;
    vec_scale_to_length(&direction,&difference,1.0f);
    FastVecDot(&axis,&direction);
    output->f[2]=0;output->f[1]=axis.f[0];output->f[0]=-axis.f[1];
    FastVecCross(&difference,&direction,&axis);
    if(difference.f[2]>0.0f)FastVecScale(output,output,6.5f);
    else FastVecScale(output,output,-6.5f);
    FastVecAdd(output,output,object+0x10);
}
