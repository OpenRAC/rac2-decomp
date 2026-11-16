#include "include_asm.h"
#include "names.h"

extern int ref_L00_002F3458_00;

/* Sets a global state word to 3. */
void menu_set_state_word_three(void)
{
    ref_L00_002F3458_00 = 3;
}

extern short g_menu_counter __attribute__((nosda));

/* Returns a small saved menu counter. */
int menu_get_counter(void) {
    return g_menu_counter;
}

/* Clears the small saved menu counter. */
void menu_clear_counter(void) {
    g_menu_counter = 0;
}

extern int g_menu_confirm_pending __attribute__((sda));

/* Returns the flag set by the confirm-pending routine. */
int menu_is_confirm_pending(void) {
    return g_menu_confirm_pending;
}
