#include "common.h"

extern void moby_set_state(char *, int, int);
extern int subtitle_request_voice_line(int, int);

extern int g_hero_tether_enabled[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda)) NOT_SDA;
typedef struct {
    unsigned short count, pad;
    unsigned int time, levels;
} SubtitleHistory;
extern SubtitleHistory g_subtitle_history[];
extern int g_game_mode NOT_SDA;
extern int g_frame_l26_counter[] __attribute__((sda));
extern unsigned int g_frame_counter[] __attribute__((sda));

typedef struct {
    int f0;
    char pad[0x20];
    int f24;
} D_L26_0027D5C8_t;

typedef struct {
    char pad[0x1A4];
    unsigned short f1a4;
    int f1a8;
} D_0018C750_t;

extern D_L26_0027D5C8_t g_level_state_block;
extern D_0018C750_t g_progress_statistics;

/* Per-frame update for the moby of class 4712: it plays a hint voice line (with subtitle) when the
   conditions are met and the line has not already been played in this level. */
void UpdateJammingArraySubtitleTriggers(char *moby) {
    char *obj = moby;
    char *vars = *(char **)(obj + 0x68);
    u8 kind = *(u8 *)(obj + 0x20);
    unsigned int mask;

    switch (kind) {
    case 0:
        *(u8 *)(obj + 0x30) = 0xFF;
        *(int *)(vars + 0x4) = 0;
        *(int *)(vars + 0x10) = 0;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (g_hero_tether_enabled[0] != 0) {
            if (g_level_state_block.f0 == 0 && g_level_state_block.f24 == -1) {
                unsigned int flags = g_subtitle_history[28].levels;
                flags &= (unsigned int)kind << g_current_map_index[0];
                if (flags == 0) {
                    subtitle_request_voice_line(0x9C5, 0x1C);
                }
            }
        }
        if (g_progress_statistics.f1a4 == 0 ||
            0x1A5E0u <
                (unsigned int)(g_frame_counter[0] - g_progress_statistics.f1a8)) {
            if (g_game_mode == 0 && g_frame_l26_counter[0] >= 0x4B1) {
                unsigned int flags = g_subtitle_history[12].levels;
                mask = 1u << g_current_map_index[0];
                if ((flags & mask) == 0) {
                    subtitle_request_voice_line(0x9B5, 0xC);
                }
            }
        }
        break;
    }
}
