#include "names.h"
extern unsigned char g_tweak_item_types[] __attribute__((sda));
extern void *g_tweak_item_ptrs[];
extern char *g_tweak_item_labels[];
extern int g_tweak_item_ranges[][2];

/* Adds an entry to the tuning menu: the first free slot of the four parallel 32-entry tables
   gets the value pointer, label, type and value range, and the menu's entry count goes up.
   The byte table lies in the GP window (GP + 0x4D40 in USA v1.01). Declared sda, its address
   is one macro instruction instead of a high/low pair, which gives retail's setup order and
   registers. */
void MuseumTweakMenuAddItem(char *menu, void *value, char *label, int type, int low, int high) {
    int *vars = *(int **)(menu + 0x68);
    int i;
    for (i = 0; i < 32; i++) {
        if (g_tweak_item_ptrs[i] == 0) {
            g_tweak_item_ptrs[i] = value;
            g_tweak_item_labels[i] = label;
            g_tweak_item_types[i] = type;
            g_tweak_item_ranges[i][0] = low;
            g_tweak_item_ranges[i][1] = high;
            vars[1]++;
            return;
        }
    }
}
