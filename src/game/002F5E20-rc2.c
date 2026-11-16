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

extern s32  g_movie_sector;

extern s32  g_movie_music_stream;

extern s32  g_movie_size;

extern s32  g_movie_file_entry;

extern s32  g_movie_mode;

extern s32 g_movie_flag __attribute__((sda));
extern u8 g_sound_state[];
extern s16 g_current_music_id[];
extern void FlushCache(s32 a);
extern void func_00133710(s32 a, s32 b, s32 c, s32 d, s32 e);
extern void FadeToBlack(s32 a);
extern void subtitle_clear_state(void);
extern void snd_wait_for_music_idle(void);
extern void snd_clear_all_voices(void);

/* Starts playing a movie: remembers where it is on the disc and fades out to begin it. */
void mpeg_begin_movie_playback(s32 sector, s32 size, s32 file_entry, s32 mode, s32 flag)
{
    u8 *flags;

    flags = g_sound_state;
    flags[0x6B] = flags[0x6B] | 8;
    func_00133710(2, 0, 0, 0, 0);
    FlushCache(0);
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    g_movie_sector = sector;
    g_movie_music_stream = (s32) g_current_music_id[0];
    g_movie_size = size;
    g_movie_file_entry = file_entry;
    g_movie_mode = mode;
    g_movie_flag = flag;
    FadeToBlack(4);
    subtitle_clear_state();
}
