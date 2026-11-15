#include "names.h"
/* Own unit for -frac2-gcse-unsplit-edges: PRE puts j + 1 at the end of the first test's block
   and the test's body keeps its own copy. The if/else arms end cse's block, so 0.5f is loaded
   again and j + 1 is not reused. PRE makes its registers in hash order, so j is declared first
   for j + 1 to take the lower stack slot. */
extern char *D_L02_001FF1C0[];
extern float func_00282E80(const void *, const void *);

/* Checks whether two polygons touch by comparing their corners. Returns 1 and the touching corner numbers if they do, otherwise 0. */
int func_L02_00349BD8(int first, int second, int *firstIndex, int *secondIndex) {
    char *a = gRoutePolygons[first];
    char *b = gRoutePolygons[second];
    int j, i, previousA, previousB;
    char *nextA, *nextB, *priorA, *priorB;
    for (i = 0; i < *(int *)a - 1; ++i) {
        for (j = 0; j < *(int *)b - 1; ++j) {
            if (vec_distance_xy(a + ((i << 4) + 0x10), b + ((j << 4) + 0x10)) < 0.5f) {
                if (i == 0) previousA = *(int *)a - 2;
                else previousA = i - 1;
                if (j == 0) previousB = *(int *)b - 2;
                else previousB = j - 1;
                nextA = a + (((i + 1) << 4) + 0x10);
                nextB = b + (((j + 1) << 4) + 0x10);
                if (vec_distance_xy(nextA, nextB) < 0.5f) {
                    *firstIndex = i; *secondIndex = j; return 1;
                }
                priorA = a + ((previousA << 4) + 0x10);
                if (vec_distance_xy(priorA, nextB) < 0.5f) {
                    *firstIndex = previousA; *secondIndex = j; return 1;
                }
                priorB = b + ((previousB << 4) + 0x10);
                if (vec_distance_xy(nextA, priorB) < 0.5f) {
                    *firstIndex = i; *secondIndex = previousB; return 1;
                }
                if (vec_distance_xy(priorA, priorB) < 0.5f) {
                    *firstIndex = previousA; *secondIndex = previousB; return 1;
                }
            }
        }
    }
    return 0;
}
