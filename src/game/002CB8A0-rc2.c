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

/* The resident table already holds the retail label addresses. The unused
 * label list keeps each C branch available; it is not read by the program. */
extern void *D_0026CCC0[];

extern s32 D_001AA6B8 __attribute__((sda));
extern s32 D_001AA6D0 __attribute__((sda));
extern s32 D_001AA6E8 __attribute__((sda));
extern s32 D_001AA700 __attribute__((sda));
extern s32 D_001AA718 __attribute__((sda));
extern s32 D_001AA730 __attribute__((sda));
extern s32 D_001AA748 __attribute__((sda));
extern s8 g_hero_state[];
extern s32 menu_process_entry_request(void *, void *);

/* Runs one of seven menu actions chosen by number. Each one passes a different settings block to a shared handler. */
s32 menu_run_action_by_index(u32 action) {
    void *target;
    void *result;
    s32 local = 0;
    s8 *table;

    result = 0;
    if (action < 7) {
        {
    static void *volatile rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    u32 rc2_selector = (u32)(action);
    if (rc2_selector > 6U) goto rc2_switch_end;
goto *D_0026CCC0[rc2_selector];

        rc2_case_0:
            result = &local;
            table = g_hero_state;
            (*(s32 *)((char *)(table) + (0x22C8))) = (*(s32 *)((char *)(table) + (0x1248)));
            target = &D_001AA6B8;
            goto rc2_switch_end;
        rc2_case_1:
            result = &local;
            target = &D_001AA6D0;
            goto rc2_switch_end;
        rc2_case_2:
            result = &local;
            target = &D_001AA6E8;
            goto rc2_switch_end;
        rc2_case_3:
            result = &local;
            target = &D_001AA700;
            goto rc2_switch_end;
        rc2_case_4:
            result = &local;
            target = &D_001AA718;
            goto rc2_switch_end;
        rc2_case_5:
            result = &local;
            target = &D_001AA730;
            goto rc2_switch_end;
        rc2_case_6:
            result = &local;
            target = &D_001AA748;
            goto rc2_switch_end;
        
rc2_switch_end: ;
}
        result = (void *) menu_process_entry_request(target, result);
    }
    return (s32) result;
}
