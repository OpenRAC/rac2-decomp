#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern void moby_mix_on_inner_data(char *,char *,char *,float);
extern void FastVecAdd(void *,void *,void *);
extern float FastAddRotations(float,float);
extern int coll_test_point(void *,int,void *,float);
extern float FastVecDot(void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern float FastVecLength(void *);
extern void FastVecScale(void *,void *,float);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern Vector128 D_L16_001BFF70[2];
/* Moves a bouncing object (moby class 2688) by its velocity, bounces it off walls and fades it out when it stops or gets old. */
void bouncing_l16_debris_update(char *object)
{
    Vector128 correction[1];
    char *state=*(char **)(object+0x68);
    float speed;
    moby_mix_on_inner_data(object,state,state,*(float *)(state+0x20));
    FastVecAdd(object+0x10,object+0x10,state);
    *(float *)(object+0xf0)=FastAddRotations(*(float *)(object+0xf0),*(float *)(state+0x10));
    *(float *)(object+0xf4)=FastAddRotations(*(float *)(object+0xf4),*(float *)(state+0x14));
    *(float *)(object+0xf8)=FastAddRotations(*(float *)(object+0xf8),*(float *)(state+0x18));
    if (coll_test_point(object+0x10,0,object,1.5f)!=0) {
        *(Vector128 *)(object+0x10)=D_L16_001BFF70[0];
        if (FastVecDot(state,&D_L16_001BFF70[1])<0.0f) {
            vec_scale_to_length(&D_L16_001BFF70[1],&D_L16_001BFF70[1],1.0f);
            speed=FastVecLength(state);
            FastVecScale(correction,&D_L16_001BFF70[1],-FastVecDot(state,&D_L16_001BFF70[1])*1.25f);
            FastVecAdd(state,state,correction);
            vec_scale_to_length(state,state,speed*0.5f);
        }
        *(int *)(state+0x24)=0;
        if (*(unsigned char *)(object+0x23)>0x60) object[0x23]=0x60;
    }
    if (math_fast_float_d((int *)(state+0x24))!=0) {
        if (*(unsigned char *)(object+0x23)<5) moby_mark_spawned(object);
        else object[0x23]=*(unsigned char *)(object+0x23)-4;
    }
}
