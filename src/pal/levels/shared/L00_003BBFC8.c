#include "include_asm.h"

#include "common.h"
extern char g_hero_position[];
extern int IsPointInCuboid(char *, int);
extern int moby_count_group_not_in_state(int, int);
extern void *cam_alloc_override_slot_pal(int);
extern void cam_end_override(void *);
extern void field_override_apply_fields(char *);

void field_override_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);

    if (IsPointInCuboid(g_hero_position, *(int *)state) != 0 && *(int *)(state + 0x28) == 0 && moby_count_group_not_in_state(*(int *)(state + 0x40), -1) != 0) {
        *(int *)(state + 0x2C) = (int)cam_alloc_override_slot_pal(5);
        *(int *)(state + 0x28) = 1;
        field_override_apply_fields(object);
    } else if (*(int *)(state + 0x28) != 0) {
        if (!IsPointInCuboid(g_hero_position, *(int *)state) || !moby_count_group_not_in_state(*(int *)(state + 0x40), -1)) {
            cam_end_override(*(void **)(state + 0x2C));
            *(int *)(state + 0x28) = 0;
        }
    }
}


