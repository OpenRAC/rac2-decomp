#include "include_asm.h"
#include "names.h"

typedef struct { unsigned char value; } ResidentFlag;
extern ResidentFlag g_unlock_flag_a;
extern ResidentFlag g_unlock_flag_b;
extern ResidentFlag g_unlock_flag_c;
extern ResidentFlag g_unlock_flag_d;
extern ResidentFlag g_unlock_flag_e;
extern short g_unlock_icon_state_a;
extern short g_unlock_icon_state_b;
extern short g_unlock_icon_state_c;
extern short g_unlock_icon_state_d;
extern short g_unlock_icon_state_e;

/* Updates five menu icon values from five unlock flags: each becomes 3 when unlocked and 0 when not. */
void menu_refresh_unlock_icon_states(void)
{
    g_unlock_icon_state_a = g_unlock_flag_a.value ? 3 : 0;
    g_unlock_icon_state_b = g_unlock_flag_b.value ? 3 : 0;
    g_unlock_icon_state_c = g_unlock_flag_c.value ? 3 : 0;
    g_unlock_icon_state_d = g_unlock_flag_d.value ? 3 : 0;
    g_unlock_icon_state_e = g_unlock_flag_e.value ? 3 : 0;
}
