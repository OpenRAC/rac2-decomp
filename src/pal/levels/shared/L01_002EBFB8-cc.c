#include "names.h"
/* func_PAL_L01_002EBFB8, the PAL copy of func_L01_002EABA8: the same C, where each read of the
   frame counter goes through the 50 Hz scale, ((s32)x * 5 + 2) / 6, 1080 becomes 900 and the
   queueing call is func_PAL_00289730. Own unit for -frac2-gcse-unsplit-edges, like the template. */
typedef struct {
    unsigned short count, pad;
    unsigned int time;
    int levels;
} SubtitleHistory;

extern SubtitleHistory g_subtitle_history[];
extern unsigned int D_001A7390[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern char g_hero_position[];
extern int IsPointInCuboid(void *, int);
extern int func_PAL_00289730(int, int);

void func_PAL_L01_002EBFB8(int key, int selection, int mode, int area, int exclude)
{
    int limit = mode == 0 ? 1 : 65535;
    SubtitleHistory *entry = &g_subtitle_history[selection];

    if (entry->count < limit) {
        if (exclude != -1 && IsPointInCuboid(g_hero_position, exclude)) {
            entry->count = 65535;
            return;
        }
        if (IsPointInCuboid(g_hero_position, area)) {
            switch (mode) {
            case 0:
                func_PAL_00289730(key, selection);
                break;
            case 1:
                if (((int)D_001A7390[0] * 5 + 2) / 6 - g_subtitle_history[selection].time > 900 || g_subtitle_history[selection].time == 0)
                    func_PAL_00289730(key, selection);
                else if (g_subtitle_history[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                    g_subtitle_history[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                break;
            case 2:
                if (g_subtitle_history[selection].count != 0) {
                    if (((int)D_001A7390[0] * 5 + 2) / 6 - g_subtitle_history[selection].time > 900 || g_subtitle_history[selection].time == 0)
                        func_PAL_00289730(key, selection);
                    else if (g_subtitle_history[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                        g_subtitle_history[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                    break;
                }
                g_subtitle_history[selection].count++;
                if (g_subtitle_history[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                    g_subtitle_history[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                g_subtitle_history[selection].levels = (g_subtitle_history[selection].levels | (1 << g_current_map_index[0])) | 0x80000000;
                break;
            case 3:
                if (g_subtitle_history[selection].levels >= 0)
                    func_PAL_00289730(key, selection);
                break;
            }
        }
    }
}
