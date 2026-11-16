#include "include_asm.h"
#include "common.h"
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_explode_object_into_pieces(void *, void *, void *, void *, int, int, int, int,
                               int, int, int);
extern void moby_compute_local_point(char *, float *, float, float, float);
extern void part_emit_rings(char *);
extern void moby_mark_spawned(void *);
extern float g_spark_explode_param_c __attribute__((sda));
extern float g_spark_explode_param_b __attribute__((sda));
extern float g_spark_explode_param_a __attribute__((sda));
extern int g_spark_explode_color __attribute__((sda));

/* a moby's three states: idle, hit, and gone */
void spark_burst_on_hit_update_pal(char *obj)
{
    char *moby = obj;
    char *state;
    float point[4];

    state = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0)
            *(unsigned short *)(moby + 0x34) |= 0x8000;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) != 0) {
            if (*(int *)state == 0)
                moby_set_state(moby, 2, -1);
        }
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces(moby, &g_spark_explode_param_a, &g_spark_explode_param_b, &g_spark_explode_param_c,
                          0xFFFF, 0, g_spark_explode_color, 6, 0xFFFF, 0xFF, 0);
        moby_compute_local_point(moby, point, 1.0f, 1.0f, 3.0f);
        part_emit_rings(moby);
        moby_mark_spawned(moby);
        break;
    }
}
