#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern void FastVecAdd(char *a, int *b, char *c);
extern void vec_transform_or_copy(char *a, char *b);
extern void part_steer_effect_direction(int a, int *b, int c);
extern int math_fast_float_d(char *a);
extern void ref_L00_00403D58_00(void (*f)(char *), char *arg);
extern void smoky_spark_effect_update(char *arg);
extern void sheep_shot_resolve_hit_pal(char *arg, void *p);
extern void table_clear_entry_flag(int a);
extern void moby_mark_spawned(char *arg);
extern void moby_mark_spawned(char *arg);
extern TI128 g_hero_l00_position;

/* Per-frame update of a flying shot: it moves along its velocity until a timer ends, then removes itself. (PAL: 50 Hz timings) */
void flying_l00_shot_update_pal(char *moby)
{
    int *vars = *(int **)(moby + 104);
    unsigned char state = *(unsigned char *)(moby + 32);
    TI128 old_position;
    char *position;

    switch (state) {
    case 0:
        moby[32] = 1;
    case 1:
        position = moby + 16;
        *(TI128 *)&old_position = *(TI128 *)position;
        FastVecAdd(position, vars, position);
        vec_transform_or_copy(position, position);
        part_steer_effect_direction(vars[7], vars, 0);
        sheep_shot_resolve_hit_pal(moby, &old_position);
        if (math_fast_float_d((char *)vars + 16) != 0)
            moby[32] = 2;
        break;
    case 2:
        table_clear_entry_flag(vars[7]);
        moby_mark_spawned(moby);
        return;
    default:
        break;
    }
    ref_L00_00403D58_00(smoky_spark_effect_update, moby);
}
