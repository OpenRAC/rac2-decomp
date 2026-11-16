#include "common.h"
typedef int TaboraReplacementQuad __attribute__((mode(TI)));
extern char *g_moby_array SDATA(D_L08_001B29DC);
extern void *CreateMoby(int);
extern void func_002A0F48(void *), moby_mark_spawned(void *);

/* Replaces a tracked object with a fresh one of another kind that copies its position, rotation and size, then removes the old one. */
void moby_replace_tracked(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *source, *replacement;
    float scale, numerator, denominator, ratio;
    if (*(int *)(state + 0x2c) != -1) {
        source = g_moby_array + *(int *)(state + 0x2c) * 256;
        replacement = CreateMoby(0x131d /* moby class 4893 */);
        scale = *(float *)(replacement + 0x2c);
        *(unsigned short *)(replacement + 0x32) = *(unsigned short *)(source + 0x32);
        replacement[0x30] = source[0x30];
        *(long long *)(replacement + 0x38) = *(long long *)(source + 0x38);
        *(int *)(replacement + 0x78) = *(int *)(source + 0x78);
        numerator = *(float *)(source + 0x2c);
        denominator = *(float *)(*(char **)(source + 0x24) + 0x24);
        replacement[0x31] = 1;
        ratio = numerator / denominator;
        *(float *)(replacement + 0x2c) = scale * ratio;
        *(TaboraReplacementQuad *)(replacement + 0xf0) = *(TaboraReplacementQuad *)(source + 0xf0);
        *(TaboraReplacementQuad *)(replacement + 0x10) = *(TaboraReplacementQuad *)(source + 0x10);
        func_002A0F48(replacement);
        if (*(int *)(state + 0x2c) != -1)
            moby_mark_spawned(g_moby_array + *(int *)(state + 0x2c) * 256);
        *(int *)(state + 0x2c) = -1;
    }
}
