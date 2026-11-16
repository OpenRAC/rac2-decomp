#include "names.h"
/* func_PAL_L16_003C7820, the PAL copy of func_L16_003C3A10: the same C, where scale func_002A7820(D_L16_001B0410,D_L16_001B0414). */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(void *,void *);
extern float math_random_float_range(float,float);
extern void vec_random_direction(float *,float,float);
extern int math_random_int_range(int,int);
extern float g_debris_l16_scale_min __attribute__((sda));
extern float g_debris_l16_scale_max __attribute__((nosda));
extern float g_debris_l16_angle_min __attribute__((sda));
extern float g_debris_l16_angle_max __attribute__((nosda));
extern float g_debris_spin_min __attribute__((sda));
extern float g_debris_spin_max __attribute__((nosda));
extern int g_debris_l16_life_min __attribute__((sda));
extern int g_debris_l16_life_max __attribute__((nosda));
char *func_PAL_L16_003C7820(char *parent,char *position,char *rotation)
{
    char *object=CreateMoby(0xa80);
    char *state;
    float factor;
    if (object != 0) {
        state=*(char **)(object+0x68);
        moby_init_child_from_parent(object,parent);
        factor=math_random_float_range(g_debris_l16_scale_min,g_debris_l16_scale_max);
        *(float *)(object+0x2c)=*(float *)(*(char **)(object+0x24)+0x24)*factor;
        *(Vector128 *)(object+0x10)=*(Vector128 *)position;
        *(Vector128 *)(object+0xf0)=*(Vector128 *)rotation;
        vec_random_direction((float *)state,0.060000002f,0.14000002f);
        vec_random_direction((float *)(state+0x10),g_debris_l16_angle_min*0.0003490659f,g_debris_l16_angle_max*0.0003490659f);
        *(float *)(state+0x20)=math_random_float_range(g_debris_spin_min,g_debris_spin_max)*0.00040000002f;
        *(int *)(state+0x24)=(((int)(math_random_int_range(g_debris_l16_life_min,g_debris_l16_life_max)) * 5 + 2) / 6);
    }
    return object;
}
