#include "include_asm.h"
#include "names.h"

/* func_L23_0041C6B0 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. It reads $gp data, hence -G8. */

typedef int TI128 __attribute__((mode(TI)));

extern char *g_mothership_boss_moby __attribute__((sda));

extern float fast_vec_dist(char *, char *);

extern int *g_path_lists[];

extern int mothership_is_value_not_in_slots(int);

/* copies the entry nearest to arg1 among the objects the measured slots name into arg0 */
void boss_find_nearest_path_point(char *outPoint, char *nearPos, int onlyAllowed) {
    char *state = *(char **)(g_mothership_boss_moby + 0x68);
    char *slots = state + 0x230;
    float best = 30000.0f;
    int i;

    for (i = 0; i < 0x2F; i++) {
        if (onlyAllowed == 0 || mothership_is_value_not_in_slots(i) != 0) {
            int *list = g_path_lists[*(int *)(slots + (i << 2))];
            int j;

            for (j = 0; j < *list; j++) {
                char *e = (char *)list + 0x10 + j * 0x10;
                float d = fast_vec_dist(e, nearPos);

                if (d < best) {
                    best = d;
                    *(TI128 *)outPoint = *(TI128 *)e;
                }
            }
        }
    }
}
