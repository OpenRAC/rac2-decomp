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
/* Creates a new object (moby class 2688) at the given spot with a random size, spin and lifetime. */
char *bouncing_debris_create(char *parent,char *position,char *rotation)
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
        vec_random_direction((float *)state,0.05000000447f,0.1166666746f);
        vec_random_direction((float *)(state+0x10),D_L16_001B0408*0.0002908882452f,D_L16_001B040C*0.0002908882452f);
        *(float *)(state+0x20)=math_random_float_range(D_L16_001B0400,D_L16_001B0404)*0.0002777777845f;
        *(int *)(state+0x24)=math_random_int_range(D_L16_001B0410,D_L16_001B0414);
    }
    return object;
}
