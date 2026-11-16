#include "names.h"

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
#include "common.h"

/* func_PAL_002CC7B8, the PAL copy of func_002CB950: the same C, where the
 * stored 10 becomes 8 and case 4 also sets a PAL-only flag. */

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_0026CCE0[];

struct S18A000 {
    s16 a;
    s8 pad[10];
};
extern struct S18A000 g_menu_command_flag;
extern s32 g_menu_action_callback_a;
extern s32 g_menu_action_callback_b;
extern s8 g_menu_request_screen_data[];
extern s32 g_pal_flag_words[];
extern void select_moby_context(s32);
extern void request_set_setting_b_pal(s32);
extern s32 request_begin_slot(s32, s32, s32, s32, s32);
extern s32 menu_send_request_pal(s32, s8 *);

s32 menu_handle_command_pal(s32 action) {
    s32 result;

    result = 0;
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4};
    u32 rc2_selector = (u32)(action);
    if (rc2_selector > 4U) goto rc2_switch_end;
goto *D_0026CCE0[rc2_selector];

    rc2_case_0:
        g_menu_command_flag.a = 8;
        result = 1;
        goto rc2_switch_end;
    rc2_case_1:
        result = 1;
        g_menu_command_flag.a = 8;
        if (g_menu_action_callback_a != 0) {
            select_moby_context(0);
            ((void (*)(s32))g_menu_action_callback_a)(0);
            select_moby_context(1);
        }
        goto rc2_switch_end;
    rc2_case_2:
        result = 1;
        g_menu_command_flag.a = 8;
        if (g_menu_action_callback_b != 0) {
            select_moby_context(0);
            ((void (*)(s32))g_menu_action_callback_b)(0);
            select_moby_context(1);
        }
        goto rc2_switch_end;
    rc2_case_3:
        result = menu_send_request_pal(3, g_menu_request_screen_data);
        goto rc2_switch_end;
    rc2_case_4:
        if (request_begin_slot(4, 2, 8, 4, 0) == 0) {
            request_set_setting_b_pal(3);
            g_pal_flag_words[0] = 1;
            result = 1;
        }
        goto rc2_switch_end;
    
rc2_switch_end: ;
}
    return result;
}
