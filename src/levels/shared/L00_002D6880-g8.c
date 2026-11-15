#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern s32 g_current_map_index;
extern int D_0018C0B4_1 __attribute__((nosda));
extern int level_run_mode_update_three(void);

/* returns 1 when a global state word is 49 and a global mode word is 4 or 11, otherwise 0; a callee returning nonzero short-circuits the result to 0 */
/* Says whether the game is in one particular mode: a state value of 49 together with a second value of 4 or 11. */
int level_is_special_mode_active(void)
{
    int is_active = 0;
    int mode;
    if (level_run_mode_update_three() != 0) goto out;
    if (D_0018C0B4_1 != 49) goto out;
    mode = g_current_map_index;
    if (mode != 4 && mode != 11) goto out;
    is_active = 1;
out:
    return is_active;
}
