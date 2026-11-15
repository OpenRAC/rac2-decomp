#include "names.h"
/* func_PAL_L16_003C7820, the PAL copy of func_L16_003C3A10: the same C, where scale func_002A7820(D_L16_001B0410,D_L16_001B0414). */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *,void *);
extern float math_random_float_range(float,float);
extern void vec_random_direction(float *,float,float);
extern int math_random_int_range(int,int);
extern float D_L16_001B0418 __attribute__((sda));
extern float D_L16_001B041C __attribute__((nosda));
extern float D_L16_001B0408 __attribute__((sda));
extern float D_L16_001B040C __attribute__((nosda));
extern float D_L16_001B0400 __attribute__((sda));
extern float D_L16_001B0404 __attribute__((nosda));
extern int D_L16_001B0410 __attribute__((sda));
extern int D_L16_001B0414 __attribute__((nosda));
char *func_PAL_L16_003C7820(char *parent,char *position,char *rotation)
{
    char *object=CreateMoby(0xa80);
    char *state;
    float factor;
    if (object != 0) {
        state=*(char **)(object+0x68);
        moby_init_child_from_parent(object,parent);
        factor=math_random_float_range(D_L16_001B0418,D_L16_001B041C);
        *(float *)(object+0x2c)=*(float *)(*(char **)(object+0x24)+0x24)*factor;
        *(Vector128 *)(object+0x10)=*(Vector128 *)position;
        *(Vector128 *)(object+0xf0)=*(Vector128 *)rotation;
        vec_random_direction((float *)state,0.060000002f,0.14000002f);
        vec_random_direction((float *)(state+0x10),D_L16_001B0408*0.0003490659f,D_L16_001B040C*0.0003490659f);
        *(float *)(state+0x20)=math_random_float_range(D_L16_001B0400,D_L16_001B0404)*0.00040000002f;
        *(int *)(state+0x24)=(((int)(math_random_int_range(D_L16_001B0410,D_L16_001B0414)) * 5 + 2) / 6);
    }
    return object;
}
