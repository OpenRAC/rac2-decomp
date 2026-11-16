#include "common.h"

/* Advances the 0-6 cursor and counts down the pending count once the check call accepts the current pair. */


extern int subtitle_request_voice_line(int, int);
extern s16 g_voice_line_ids[] MACRO_ADDR;
extern s16 g_voice_line_subtitle_ids[];
extern u8 g_voice_line_delay_timer __attribute__((section(".sdata")));
extern u8 g_voice_line_cursor __attribute__((section(".sdata")));

void level_advance_checked_cursor(void)
{
    if (g_voice_line_delay_timer == 0)
        return;
    if (subtitle_request_voice_line(g_voice_line_ids[g_voice_line_cursor],
                    g_voice_line_subtitle_ids[g_voice_line_cursor]) == 0)
        return;
    g_voice_line_cursor = (g_voice_line_cursor + 1) % 7;
    g_voice_line_delay_timer = g_voice_line_delay_timer - 1;
}
