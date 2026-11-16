#include "include_asm.h"
#include "names.h"



extern int math_random_int_below(int mode);
extern float coll_get_ground_height_at_position(char *object, char *local);
extern void func_00282D30_7(char *local, int value, float scale);
extern float func_002A7878_1(float low, float high);
extern void *part_spawn_bubble(char *object, char *local, float amount, float base);

/* Family 6eb4f363e5305bed: seed body at func_PAL_L00_0038A408. */
void part_l00_spawn_object_effect_burst_pal(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (math_random_int_below(4))
        return;
    base = coll_get_ground_height_at_position(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    part_spawn_bubble(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

