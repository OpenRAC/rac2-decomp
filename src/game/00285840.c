#include "include_asm.h"
#include "names.h"

/* Owner-reviewed Qwen backlog: observed operations, not recovered original object boundaries. */

/* func_00285840: owner ABI/declaration review retained. */
/* extern declaration for global variable referenced in func_00285840 */
extern unsigned int g_menu_saved_state;

/* func_00285850: owner ABI/declaration review retained. */
extern unsigned int g_menu_second_value;

/* func_002858B0: owner ABI/declaration review retained. */
extern int g_menu_setting;

/* Returns the saved menu state value. */
unsigned int menu_get_saved_state(void)
{
    return g_menu_saved_state;
}

/* Returns the second saved menu value. */
unsigned int menu_get_second_value(void)
{
    return g_menu_second_value;
}

extern int request_is_current_slot(int);
extern void snd_send_cmd23(int);
extern void music_Unpause(void);
extern int snd_Pump(void);
extern void pad_clear_port_state(void);

/* Ends the menu: undoes the pause sounds when needed and clears the saved menu state. */
void menu_end(void)
{
    if (request_is_current_slot(3) == 0) {
        snd_send_cmd23(0x5D);
        music_Unpause();
        snd_Pump();
    }
    pad_clear_port_state();
    g_menu_saved_state = 0;
}

/* Stores a number into a global menu setting. */
void menu_set_setting(int value)
{
  g_menu_setting = value;
}

/* func_002859C8 is defined in 002859C8-panel-g8.c. */


