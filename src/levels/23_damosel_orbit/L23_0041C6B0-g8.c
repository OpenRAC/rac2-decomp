#include "include_asm.h"
#include "names.h"

/* func_L23_0041C6B0 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. It reads $gp data, hence -G8. */

typedef int TI128 __attribute__((mode(TI)));

extern char *D_L23_001B1484 __attribute__((sda));

extern float func_00282E48(char *, char *);

extern int *D_L23_001FF300[];

extern int func_L23_00419CA0(int);

/* copies the entry nearest to arg1 among the objects the measured slots name into arg0 */
void func_L23_0041C6B0(char *outPoint, char *nearPos, int onlyAllowed) {
    char *state = *(char **)(gMothershipBossMoby + 0x68);
    char *slots = state + 0x230;
    float best = 30000.0f;
    int i;

    for (i = 0; i < 0x2F; i++) {
        if (onlyAllowed == 0 || IsValueNotInSlotTable(i) != 0) {
            int *list = gPathLists[*(int *)(slots + (i << 2))];
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
