#include "names.h"
/* SPDX-License-Identifier: GPL-3.0-only
 * OpenRAC nonmatching d43c3b99b984fb63556c844a21ee99e8e31d2deb; nonmatching/game/func_PAL_002D5C20.c
 */
/* SPDX-License-Identifier: MIT
 * MIT License
 * 
 * Copyright (c) 2026 Forja contributors
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/* func_PAL_002D5C20, the PAL copy of func_002D5048: the same C, where the D_001A7BB4 store goes
   through the table D_PAL_001ABB58. */
#include "common.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
typedef struct { char reserved00[0x1C4]; int flags; } MenuGameState;
extern MenuGameState g_pad_state;
extern CallbackState g_pause_menu_state;
extern unsigned char g_language;
extern int g_menu_selection_input_state __attribute__((nosda));
/* PAL only: indexed by D_001A7BB4, which USA stores directly. Its extent is not established, so it
   stays incomplete behind the GP view retail uses. */
extern int g_ui_value_table[] SDATA(D_PAL_001ABB58);
int menu_check_selection_input_pal(int selection)
{
    CallbackState *state = &g_pause_menu_state;
    g_menu_selection_input_state = g_ui_value_table[g_language];
    if (*(int *)(state->source + 0xE8) != selection)
        return 0;
    if ((g_pad_state.flags & 0x900) && state->fallback == 0)
        return 1;
    if (g_pad_state.flags & 0x10) {
        CallbackState *update = &g_pause_menu_state;
        int value = *(int *)(update->source + 0xE0);
        int result;
        if (value != 0)
            update->value = value;
        else if (update->fallback == 0) {
            result = -1;
            goto return_value;
        }
        result = 0;
return_value:
        return result;
    }
    return 0;
}
