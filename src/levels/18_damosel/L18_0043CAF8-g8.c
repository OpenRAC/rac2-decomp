#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_explode_object_into_pieces(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void moby_mark_spawned(void *);
extern int D_L18_001B1BB0 __attribute__((sda));
extern int D_L18_001B1B88 __attribute__((sda));
extern int D_L18_001B1B80 __attribute__((sda));
extern int D_L18_001B1B90 __attribute__((sda));
extern int math_random_int_below(int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void *part_spawn_spark_moby(void *,void *,void *,int,float,float);
/* Updates a breakable object (moby class 4486): when it is hit, it spawns a handful of debris pieces and disappears. */
void breakable_l18_debris_update(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68), *hit;
    int n, i;
    float pointA[4] __attribute__((aligned(16))), pointB[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(moby[0x20]) {
    case 0: moby_set_state(moby,1,-1); break;
    case 1:
        hit=part_find_owned_effect_slot(moby,0x4010000,0);
        if(hit && !*(int *)vars) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=0.75f;
            FastVecScale(pointA,hit+0x10,math_random_float_range(6.0f,8.0f));
            qcopy(pointB,pointA);
            FastVecSub(pointA,pointA,spread);
            FastVecAdd(pointB,pointB,spread);
            part_explode_object_into_pieces(moby,pointA,&D_L18_001B1B88,&D_L18_001B1B80,65535,-1,D_L18_001B1BB0,9,2,255,0);
            moby_set_state(moby,2,-1);
        }
        moby[0xA8]=255;
        break;
    case 2:
        part_explode_object_into_pieces(moby,&D_L18_001B1B90,&D_L18_001B1B88,&D_L18_001B1B80,65535,0,D_L18_001B1BB0,6,61,255,0);
        n=math_random_int_below(5);
        moby_compute_local_point(moby,pointA,0.35f,0.0f,1.8f);
        for(i=0;i<n;i++) {
            float x,y;
            pointB[0]=math_random_float_range(8.0f,12.0f)*(1.0f/60.0f);
            pointB[1]=(2*i-n+1)*(1.0f/15.0f);
            pointB[2]=math_random_float_range(0.0f,2.0f)*(1.0f/60.0f);
            matrix_mul_vec3(pointB,pointB,moby+0xC0);
            x=math_random_float_range(0.75f,1.25f);
            y=math_random_float_range(0.75f,1.25f);
            part_spawn_spark_moby(moby,pointA,pointB,1,x,y);
        }
        moby_mark_spawned(moby);
        break;
    }
}
