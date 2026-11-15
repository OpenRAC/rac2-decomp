#include "names.h"
/* SPDX-License-Identifier: MIT
 * MIT License
 *
 * Copyright (c) 2026 RC2 decomp contributions
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

extern s16 g_music_state[];
extern void snd_update_music_system(void);
extern void snd_clear_flag_and_update(void);
extern void snd_Pump(void);
extern void snd_set_current_buffer_flag(void);
extern void mem_fast_helper_a(s32);

/* Runs the music and disc read steps once, or repeatedly until the disc read is idle when asked. Returns the read state. */
s16 snd_pump_music_and_disc_read(s32 wait_until_idle) {
    s16 *state;

    if (wait_until_idle != 0) {
        while (1) {
            snd_update_music_system();
            snd_clear_flag_and_update();
            snd_Pump();
            snd_set_current_buffer_flag();
            if (g_music_state[2] == 0) {
                break;
            }
            mem_fast_helper_a(10000);
            if (g_music_state[2] == 0) {
                break;
            }
        }
    } else {
        snd_update_music_system();
        snd_clear_flag_and_update();
        snd_Pump();
        snd_set_current_buffer_flag();
    }
    state = g_music_state;
    return state[2];
}
