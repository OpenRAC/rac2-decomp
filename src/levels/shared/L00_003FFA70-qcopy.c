#include "include_asm.h"
#include "names.h"

/* func_L00_00403D58 and func_L00_00404DD8 are a unit of their own: both need the opt-in
   quadword-copy profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt), which give retail's grouped `lq`/`sq` with register addresses and
   keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void FastVecAdd(char *a, int *b, char *c);
extern void vec_transform_or_copy(char *a, char *b);
extern void part_steer_effect_direction(int a, int *b, int c);
extern int math_fast_float_d(char *a);
/* The callback dispatcher differs from the catalogue pairing in four levels. */
extern void ref_L00_00403D58_00(void (*f)(char *), char *arg);
extern void smoky_spark_effect_update(char *arg);
extern void sheep_shot_resolve_hit(char *arg, void *p);
extern void table_clear_entry_flag(int a);
extern void moby_mark_spawned(char *arg);

/* Per-frame update of a flying shot: it moves along its velocity until a timer ends, then removes itself. */
void flying_l00_shot_update(char *arg)
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
        sheep_shot_resolve_hit(arg, &tmp);
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

extern void snd_play_from_class_bank(int a, int b, void *c, int d);
extern int CollLine(void *a, void *b, int c, void *d, int e);
extern void moby_mark_spawned(char *arg);
extern TI128 D_L00_001BF220;

/* Removes the object if it leaves the map; if it hits something it snaps to a saved spot, plays a sound and enters its end state. */
void shot_handle_impact(char *arg, void *a1)
{
    char *p;

    if (*(float *)(arg + 16) < 2.0f || *(float *)(arg + 16) > 1021.0f ||
        *(float *)(arg + 20) < 2.0f || *(float *)(arg + 20) > 1021.0f ||
        *(float *)(arg + 24) < 2.0f || *(float *)(arg + 24) > 1021.0f) {
        moby_mark_spawned(arg);
        return;
    }
    p = arg + 16;
    if (CollLine(a1, p, 0, arg, 0) != 0) {
        *(TI128 *)p = D_L00_001BF220;
        arg[32] = 2;
        snd_play_from_class_bank(5, 0, arg, 3705);
    }
}
