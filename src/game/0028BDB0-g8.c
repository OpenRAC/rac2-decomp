#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;

extern void hud_reset_elements(void);
extern int g_weapon_menu_entry __attribute__((sda));
extern int g_weapon_menu_prev_slot;
extern int g_weapon_menu_state_word;
/* Resets all HUD elements and puts the weapon menu back to its idle state. */
void weapon_menu_reset(void) {
    hud_reset_elements();
    g_weapon_menu_entry = 1;
    g_weapon_menu_prev_slot = -1;
    g_weapon_menu_state_word = 0;
}
