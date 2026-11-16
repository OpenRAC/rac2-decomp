#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base[] __attribute__((sda));
extern void menu_set_flag_restart_fades(void *, int);

/* Passes a value on to another part of the level object, if one is loaded. */
void level_forward_value_b_pal(int value) {
    if (g_resident_data_base[0] != 0)
        menu_set_flag_restart_fades(g_resident_data_base[0] + 0x37ED0, value);
}

typedef int BatchA_A08_s32;
extern BatchA_A08_s32 g_bolt_counter_base[] __attribute__((sda));

/* A08-sda-offset-40 freshly exact-verified under family reservation */
void level_store_value_pair_pal(BatchA_A08_s32 first, BatchA_A08_s32 second) {
    BatchA_A08_s32 base = g_bolt_counter_base[0];
    BatchA_A08_s32 *values;
    if (base == 0) return;
    values = (BatchA_A08_s32 *)(base + 0x38000);
    values[0x7AA0/4] = first;
    values[0x7AA4/4] = second;
}

/* Returns 1 if either of the two stored level values is non-zero. */
int level_has_value_pair_pal(void) {
    int base = g_bolt_counter_base[0];
    if (base != 0) {
        int *state = (int *)(base + 0x38000);
        if (state[0x7AA0 / 4] != 0 || state[0x7AA4 / 4] != 0)
            return 1;
    }
    return 0;
}

