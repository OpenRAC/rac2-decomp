#include "common.h"

extern char g_hero_position[];
extern char *D_L16_001B2B1C;

extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(char *, int);
extern int moby_count_group_not_in_state(int, int);

/* Waits for its linked object or trigger, then wakes the eight targets it lists. */
void UpdateCuboidTrigger(char *obj) {
    int *vars = *(int **)(obj + 0x68);
    int i;
    char *linkedMoby;

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        if (vars[1] == -1 && vars[2] == -1) {
            moby_set_state(obj, 4, -1);
        } else if (vars[1] != -1) {
            moby_set_state(obj, 1, -1);
        } else {
            moby_set_state(obj, 2, -1);
        }
        break;
    case 1:
        linkedMoby = D_L16_001B2B1C + (vars[0] << 8);
        if (linkedMoby == 0 || *(u8 *)(linkedMoby + 0x20) == 0xFE || *(u8 *)(linkedMoby + 0x20) == 0xFD) {
            if (IsPointInCuboid(g_hero_position, vars[1]) != 0) {
                for (i = 0; i < 8; i++) {
                    if (vars[4 + i] != -1) {
                        char *entry = D_L16_001B2B1C + (vars[4 + i] << 8);
                        if (*(s16 *)(entry + 0xAA) == 0xEA3) {
                            *(int *)(*(char **)(entry + 0x68) + 0x24C) = 1;
                        } else {
                            *(u8 *)(entry + 0xBC) = 1;
                        }
                    }
                }
                moby_set_state(obj, 4, -1);
            }
        }
        break;
    case 2:
        if (moby_count_group_not_in_state(vars[2], -1) == 0) {
            for (i = 0; i < 8; i++) {
                if (vars[4 + i] != -1) {
                    char *entry = D_L16_001B2B1C + (vars[4] << 8);
                    if (*(s16 *)(entry + 0xAA) == 0xEA3) {
                        *(int *)(*(char **)(entry + 0x68) + 0x24C) = 1;
                    } else {
                        *(u8 *)(entry + 0xBC) = 1;
                    }
                }
            }
            moby_set_state(obj, 4, -1);
        }
        break;
    case 3:
    case 4:
        break;
    }
}
