/* func_L23_0041CA58: the level-22 routine func_L22_003A36A0 without its second probe loop. Its `% 3` result is unused, as in L22: retail keeps only the zero-divisor guard. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad[0x230];
    int ids[47];
} State;

typedef struct {
    int count;
    int pad[3];
    TI128 pts[1];
} Rec;

extern Rec *g_path_lists[];

extern void part_reset_effect_pools(char *);
extern void part_spawn_random_row_effect(void *, int);
extern int math_random_int_below(int);
extern void *memset(void *, int, unsigned int);

/* Picks seven random points along the paths and spawns an effect at each of them. */
void part_spawn_random_path_effects(char *obj) {
    int cumulative[47];
    int selected[7];
    struct {
        TI128 point, low, normal;
    } v;
    State *st = *(State **)(obj + 0x68);
    int total = 0, i, j, next, unused, chosen, duplicate;

    part_reset_effect_pools(obj);
    math_random_int_below(3);
    memset(selected, -1, 28);
    for (i = 0; i < 47; i++) {
        cumulative[i] = total;
        total += g_path_lists[st->ids[i]]->count - 1;
    }
    for (i = 0; i < 7; i++) {
        duplicate = 1;
        do {
            chosen = math_random_int_below(total);
            for (j = 0; j < 7; j++) {
                if (chosen == selected[j]) {
                    duplicate = 1;
                    break;
                }
                if (j == 6) duplicate = 0;
            }
        } while (duplicate == 1);
        selected[i] = chosen;
        for (j = 0; j < 47; j = next) {
            if (j == 46) {
                qcopy_nc(&v.point, (char *)((chosen - cumulative[46]) * 16 + (int)g_path_lists[st->ids[46]]) + 16);
                break;
            }
            next = j + 1;
            if (chosen >= cumulative[j] && chosen < cumulative[next]) {
                qcopy_nc(&v.point, (char *)((chosen - cumulative[j]) * 16 + (int)g_path_lists[st->ids[j]]) + 16);
                break;
            }
        }
        if (j != 10 && j != 27 && j != 28 && j != 31 && j != 15) {
            unused = i % 3;
            part_spawn_random_row_effect(&v.point, 0);
        }
    }
}
