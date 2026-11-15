#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(char *a, int *b, char *c);
extern void vec_transform_or_copy(char *a, char *b);
extern void part_steer_effect_direction(int a, int *b, int c);
extern int math_fast_float_d(char *a);
extern void ref_L00_00403D58_00(void (*f)(char *), char *arg);
extern void smoky_spark_effect_update(char *arg);
extern void func_PAL_L00_00408978(char *arg, void *p);
extern void table_clear_entry_flag(int a);
extern void moby_mark_spawned(char *arg);
extern void moby_mark_spawned(char *arg);
extern TI128 D_L00_001BF220;

void func_PAL_L00_00408740(char *arg)
{
    int *o = *(int **)(arg + 104);
    unsigned char state = *(unsigned char *)(arg + 32);
    TI128 tmp;
    char *p;

    switch (state) {
    case 0:
        arg[32] = 1;
    case 1:
        p = arg + 16;
        *(TI128 *)&tmp = *(TI128 *)p;
        FastVecAdd(p, o, p);
        vec_transform_or_copy(p, p);
        part_steer_effect_direction(o[7], o, 0);
        func_PAL_L00_00408978(arg, &tmp);
        if (math_fast_float_d((char *)o + 16) != 0)
            arg[32] = 2;
        break;
    case 2:
        table_clear_entry_flag(o[7]);
        moby_mark_spawned(arg);
        return;
    default:
        break;
    }
    ref_L00_00403D58_00(smoky_spark_effect_update, arg);
}
