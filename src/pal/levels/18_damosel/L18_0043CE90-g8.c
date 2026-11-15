#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_L00_0032C328(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void moby_mark_spawned(void *);
extern int D_L18_001B1BB0 __attribute__((sda));
extern int D_L18_001B1B88 __attribute__((sda));
extern int D_L18_001B1B80 __attribute__((sda));
extern int D_L18_001B1B90 __attribute__((sda));
extern int math_random_int_below(int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void *func_PAL_L06_00469110(void *,void *,void *,int,float,float);

void func_PAL_L18_00441F00(u8 *o) {
    u8 *s=*(u8 **)(o+0x68), *hit;
    int n, i;
    float a[4] __attribute__((aligned(16))), b[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(o[0x20]) {
    case 0: moby_set_state(o,1,-1); break;
    case 1:
        hit=part_find_owned_effect_slot(o,0x4010000,0);
        if(hit && !*(int *)s) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=0.75f;
            FastVecScale(a,hit+0x10,math_random_float_range(6.0f,8.0f));
            qcopy(b,a);
            FastVecSub(a,a,spread);
            FastVecAdd(b,b,spread);
            func_PAL_L00_0032C328(o,a,&D_L18_001B1B88,&D_L18_001B1B80,65535,-1,D_L18_001B1BB0,9,2,255,0);
            moby_set_state(o,2,-1);
        }
        o[0xA8]=255;
        break;
    case 2:
        func_PAL_L00_0032C328(o,&D_L18_001B1B90,&D_L18_001B1B88,&D_L18_001B1B80,65535,0,D_L18_001B1BB0,6,61,255,0);
        n=math_random_int_below(5);
        moby_compute_local_point(o,a,0.35f,0.0f,1.8f);
        for(i=0;i<n;i++) {
            float x,y;
            b[0]=math_random_float_range(8.0f,12.0f)*(0.020000001f);
            b[1]=(2*i-n+1)*(0.080000006f);
            b[2]=math_random_float_range(0.0f,2.0f)*(0.020000001f);
            matrix_mul_vec3(b,b,o+0xC0);
            x=math_random_float_range(0.75f,1.25f);
            y=math_random_float_range(0.75f,1.25f);
            func_PAL_L06_00469110(o,a,b,1,x,y);
        }
        moby_mark_spawned(o);
        break;
    }
}
