#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float fast_vec_dist(char *, char *);
extern int *g_ship_path_table[];
extern int list_is_key_missing(int);

/* Finds the lane point closest to a position and copies it to the output. */
void lane_find_nearest_point(char *obj, char *out, char *pos, int flag) {
    char *slots = *(char **)(obj + 0x68) + 0x2A0;
    float best = 30000.0f;
    int i;

    for (i = 0; i < 0x20; i++) {
        if (flag == 0 || list_is_key_missing(i) != 0) {
            int *list = g_ship_path_table[*(int *)(slots + (i << 2))];
            int j;

            for (j = 0; j < *list; j++) {
                char *e = (char *)list + 0x10 + j * 0x10;
                float d = fast_vec_dist(e, pos);

                if (d < best) {
                    best = d;
                    *(TI128 *)out = *(TI128 *)e;
                }
            }
        }
    }
}
