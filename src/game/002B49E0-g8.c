#include "names.h"
/* func_002B49E0 starts a request for slot `index`. Its result is the first of these that applies:
 * -1 when D_0018C2EC is zero; -3 when index is not negative and D_001A8B88[index] is non-zero; -2
 * when mode is 1 and the stack D_001B1D50 already holds 8 words (D_001AA100); 0 when D_001A8BB8
 * holds -2; -1 otherwise. It clears *flag first when flag is not null. Only a result of 0 goes
 * on: it records a2, a3, flag and index in D_001AA0F8, D_001AA0FC, D_001AA104 and D_001A8BB8,
 * sets D_001B170C to 2 or 3 (and calls func_002858B0 with the same value when index is 4) for
 * index 3 or 4 under the D_001A79F0 / D_001C4F40 conditions below, and, when mode is 1, pushes
 * D_001A8BB0 on the stack.
 *
 * Built with -G8 (the file name says so); see func_002B4B70 (002B4B70-g8.c) for the three kinds
 * of access:
 *   - `sda` is a $gp access in every use (D_001AA100 and the four stores);
 *   - `nosda` is `lui` into a temporary and a load off its `%lo`;
 *   - a plain extern of at most 8 bytes is a bare symbol: `lui $r,%hi ; lw $r,%lo($r)` in
 *     ordinary flow and a one-instruction $gp access in a branch delay slot, which is why retail
 *     reads D_001A79F0 both ways.
 * The two arrays are declared with 2 elements so that their addresses are one `la` (lui + addiu)
 * rather than a high part held in a register of its own.
 */
extern int g_mode_stack_depth __attribute__((sda));
extern int g_pending_mode_arg_a __attribute__((sda));
extern int g_pending_mode_arg_b __attribute__((sda));
extern int g_pending_mode_done_flag __attribute__((sda));
extern int g_vis_fallback_mode;
extern int g_requested_game_mode;
extern int g_current_map_index;
extern int g_current_game_mode;
extern int g_request_enabled_flag __attribute__((nosda));
extern int g_map_mode __attribute__((nosda));
extern int g_request_slot_flags[2];
extern int g_game_mode_stack[2];
extern void menu_set_setting(int);

/* Starts a request for a slot, unless one is already running or the slot is blocked, and returns a code saying whether it started. */
int request_begin_slot(int index, int mode, int argA, int argB, unsigned char *flag)
{
    int result;
    int entry;

    if (flag != 0)
        *flag = 0;
    result = -1;
    if (g_requested_game_mode == -2)
        result = 0;
    if (mode == 1 && !(g_mode_stack_depth < 8))
        result = -2;
    entry = index >= 0 ? g_request_slot_flags[index] : 0;
    if (entry != 0)
        result = -3;
    if (g_request_enabled_flag == 0)
        result = -1;
    if (result != 0)
        return result;
    g_pending_mode_arg_a = argA;
    g_pending_mode_arg_b = argB;
    g_pending_mode_done_flag = (int)flag;
    g_requested_game_mode = index;
    if ((g_current_map_index == 8 && g_map_mode == 1) || (g_current_map_index == 0x13 && g_map_mode == 0)) {
        if ((unsigned)(index - 3) < 2) {
            g_vis_fallback_mode = 2;
            if (index == 4)
                menu_set_setting(2);
        }
    }
    if ((unsigned)(g_current_map_index - 22) < 2) {
        if ((unsigned)(index - 3) < 2) {
            g_vis_fallback_mode = 3;
            if (index == 4)
                menu_set_setting(3);
        }
    }
    if (mode == 1) {
        g_game_mode_stack[g_mode_stack_depth++] = g_current_game_mode;
    }
    return result;
}
