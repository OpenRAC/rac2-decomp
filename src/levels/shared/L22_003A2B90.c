#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_00282E48(char *, char *);
extern int *D_L22_001FE940[];
extern int func_L22_003A48F8(int);

/* Finds the lane point closest to a position and copies it to the output. */
void func_L22_003A2B90(char *obj, char *out, char *pos, int flag) {
    char *slots = *(char **)(obj + 0x68) + 0x2A0;
    float best = 30000.0f;
    int i;

    for (i = 0; i < 0x20; i++) {
        if (flag == 0 || IsKeyMissingFromList(i) != 0) {
            int *list = D_L22_001FE940[*(int *)(slots + (i << 2))];
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
