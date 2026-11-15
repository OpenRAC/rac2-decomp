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

extern s32  D_001B2208;

extern s32  D_001B221C;

extern s32  D_001B220C;

extern s32  D_001B2210;

extern s32  D_001B2214;

extern s32 D_001B2218 __attribute__((sda));
extern u8 g_sound_state[];
extern s16 D_001A63F0[];
extern void FlushCache(s32 a);
extern void func_00133710(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void FadeToBlack(s32 a);
extern void subtitle_clear_state(void);
extern void snd_wait_for_music_idle(void);
extern void snd_clear_all_voices(void);

/* Starts playing a movie: remembers where it is on the disc and fades out to begin it. */
void mpeg_begin_movie_playback(s32 sector, s32 size, s32 fileEntry, s32 mode, s32 flag)
{
    u8 *flags;

    flags = g_sound_state;
    flags[0x6B] = flags[0x6B] | 8;
    func_00133710(2, 0, 0, 0, 0);
    FlushCache(0);
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    D_001B2208 = sector;
    D_001B221C = (s32) D_001A63F0[0];
    D_001B220C = size;
    D_001B2210 = fileEntry;
    D_001B2214 = mode;
    D_001B2218 = flag;
    FadeToBlack(4);
    subtitle_clear_state();
}
