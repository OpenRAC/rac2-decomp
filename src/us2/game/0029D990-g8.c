#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void UpdateBoltCounter(void);

/* Updates the bolt counter, if the menu system exists. */
void bolt_counter_update_if_menu_us2(void) {
    if (g_resident_data_base != 0)
        UpdateBoltCounter();
}
