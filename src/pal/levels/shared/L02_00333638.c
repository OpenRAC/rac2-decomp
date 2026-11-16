#include "include_asm.h"
#include "names.h"

extern void *moby_get_vars_word_18(char *a0);
extern int moby_step_controller(void *a0, void *a1, float f12);
extern void *moby_get_vars_word_18(char *a0);
extern void *moby_get_vars_word_18(char *a0);

/* Set the record's fields for the call, then put the old ones back. */
int moby_move_to_target_temp_limits_pal(void *a0, void *a1, int a2, float f12, float f13, float f14) {
    char *rec;
    int old38;
    float old28;
    float old20;
    int ret;

    rec = (char *)moby_get_vars_word_18((char *)a0);
    if (rec == 0)
        return 8;
    old38 = *(int *)(rec + 0x38);
    old28 = *(float *)(rec + 0x28);
    *(int *)(rec + 0x38) = a2;
    if (0.0f < f13)
        *(float *)(rec + 0x28) = f13;
    old20 = *(float *)(rec + 0x20);
    if (0.0f < f14)
        *(float *)(rec + 0x20) = f14;
    ret = moby_step_controller(a0, a1, f12);
    *(int *)(rec + 0x38) = old38;
    *(float *)(rec + 0x28) = old28;
    *(float *)(rec + 0x20) = old20;
    return ret;
}

