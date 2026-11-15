#include "include_asm.h"
#include "names.h"

extern int ref_L00_002F3458_00;

/* Sets a global state word to 3. */
void menu_set_state_word_three(void)
{
    ref_L00_002F3458_00 = 3;
}

extern short D_001BAD04 __attribute__((nosda));

/* Returns a small saved menu counter. */
int menu_get_counter(void) {
    return D_001BAD04;
}

/* Clears the small saved menu counter. */
void menu_clear_counter(void) {
    D_001BAD04 = 0;
}

extern int D_001A8A64 __attribute__((sda));

/* Returns the flag set by the confirm-pending routine. */
int menu_is_confirm_pending(void) {
    return D_001A8A64;
}
