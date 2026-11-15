#include "include_asm.h"
#include "names.h"
typedef int V4_F876460d6 __attribute__((mode(TI)));
extern char *moby_get_private_value_0(void *);
extern float moby_measure_target_reach(char *,char *,float,float,float,float,int *);
extern unsigned int ref_002AF460_00[];

/* Selects the eligible list entry with the smallest reach score. */
void *FindBestTargetByReach(V4_F876460d6 *pos, float p1, float p2, float p3, float p4)
{
    V4_F876460d6 copy = *pos;
    char *cbuf = (char *)&copy;
    float best = 1.0e8f;
    float d;
    int bestnode = 0;
    int flag;
    unsigned int node = ref_002AF460_00[0];
    int index = 0;
    void *v;

    while (node) {
        v = (void *)moby_get_private_value_0((void *)node);
        if (v == 0)
            goto next;
        if (*(float *)v == 0.0f)
            goto next;
        d = moby_measure_target_reach(cbuf, (char *)node, p1, p2, p3, p4, &flag);
        if (flag)
            goto next;
        if (d < best) {
            best = d;
            bestnode = (int)node;
        }
    next:
        node = ref_002AF460_00[++index];
    }
    return bestnode;
}
