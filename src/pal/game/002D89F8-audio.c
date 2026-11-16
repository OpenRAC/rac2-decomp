#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned long long u64;
extern int g_effects_volume, g_music_volume, g_audio_mode_option;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern char *GetLocalizedString(int);
extern int GetIconFrame(int, int);
extern void text_draw_right_aligned_small(int, int, u64, u8 *, int);
extern void text_draw_small(int, int, u64, u8 *, int);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern void hud_draw_quad_uv(int, int, int, int, int, int, int, int, int, int);
typedef struct {
    char pad0[0x20];
    int width;
    int height;
    char pad28[0x18];
    int selection;
} Menu;

/* Draws the sound menu: sound and music volume sliders, then the stereo/mono mode row. */
int DrawSoundMenu_pal(Menu *menu)
{
    int center_x;
    int row_height;
    int label_right;
    int border_left;
    int slider_left;
    int slider_padding;
    int slider_length;
    int row_y;

    row_height = menu->height >> 2;
    center_x = menu->width >> 1;
    SetupGifPaging(0);
    label_right = center_x - 8;
    border_left = center_x + 7;
    slider_left = center_x + 9;
    slider_padding = center_x + 0x4A;

    /* Row 1: sound volume. */
    text_draw_right_aligned_small(label_right, row_height - 8,
                  menu->selection == 0 ? 0x8020FFFF : 0x80FFA888,
                  (u8 *)GetLocalizedString(0xE34), -1);
    AppendScreenRectPacket(border_left, row_height - 8, menu->width - 0x3F, row_height + 8,
                  0x80696969, 0);
    AppendScreenRectPacket(slider_left, row_height - 6, menu->width - 0x41, row_height + 6,
                  0x80383838, 0);
    slider_length = (menu->width - slider_padding) * g_effects_volume / 1024;
    hud_draw_quad_uv(GetIconFrame(0xE99D, 8), slider_left << 4,
                  (row_height - 6) << 4, (center_x + 8 + slider_length) << 4,
                  (row_height + 5) << 4, 0, 0xA0, 0x1F0, 0x150, 0x80);

    /* Row 2: music volume. */
    row_y = row_height + row_height;
    text_draw_right_aligned_small(label_right, row_y - 8,
                  menu->selection == 1 ? 0x8020FFFF : 0x80FFA888,
                  (u8 *)GetLocalizedString(0xE35), -1);
    AppendScreenRectPacket(border_left, row_y - 8, menu->width - 0x3F, row_y + 8,
                  0x80696969, 0);
    AppendScreenRectPacket(slider_left, row_y - 6, menu->width - 0x41, row_y + 6,
                  0x80383838, 0);
    slider_length = (menu->width - slider_padding) * g_music_volume / 1024;
    hud_draw_quad_uv(GetIconFrame(0xE99D, 9), slider_left << 4,
                  (row_y - 6) << 4, (center_x + 8 + slider_length) << 4,
                  (row_y + 5) << 4, 0, 0xA0, 0x1F0, 0x150, 0x80);

    /* Row 3: playback mode. */
    row_y += row_height;
    text_draw_right_aligned_small(label_right, row_y - 8,
                  menu->selection == 2 ? 0x8020FFFF : 0x80FFA888,
                  (u8 *)GetLocalizedString(0xE36), -1);
    text_draw_small(center_x + 8, row_y - 8, 0x80FFA888,
                  (u8 *)GetLocalizedString(g_audio_mode_option != 0 ? 0xE38 : 0xE37), -1);
    DoGifPaging();
    return 2;
}
