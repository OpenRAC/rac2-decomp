#include "names.h"
/* func_US2_002DE768, the USA v2.00 copy of func_002DDA10 (src/game/002D5E98-g8.c): the same C, where
   the score line prints the plain number right aligned in a column through func_0027FA10 and then
   draws a separator string every three digits, a comma or, in languages 3 to 5, a full stop. The
   empty-slot text is 0x2DAA. The language byte is element 4 of the byte table at D_001A7BB0: the
   symbol-plus-offset form is the unsplit two-word load, which reorg keeps out of the delay slot of
   the digit-count loop's first test. */
#include "include_asm.h"
#include "common.h"
extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern int g_save_menu_screen;
extern char g_pause_menu_state[];

/* One save-slot summary row of the save context at D_001393E0 (28 bytes). */
typedef struct {
    int state;              /* -1: empty slot */
    int score;
    int extra;
    int ticks;              /* play time, 60 per second */
    unsigned char pad[4];
    unsigned char date[4];
    int unknown;
} SaveRow;

typedef struct {
    int head[12];
    SaveRow records[4];     /* D_00139410 */
    unsigned char gap[0x15C - 0xA0];
    int mode;
    int unknown160;
    int selected;
} SaveData;

extern SaveRow g_save_slot_rows[];

/* GP-relative layout coefficients of the save-slot panel. */
extern int g_save_slot_line_height __attribute__((sda)); /* line height */
extern int g_save_slot_gap __attribute__((sda)); /* slot gap */
extern int g_save_slot_icon_width __attribute__((sda));
extern int g_save_slot_icon_height __attribute__((sda));
extern int g_save_slot_extra_icon_offset __attribute__((sda));
extern int g_save_slot_text_x __attribute__((sda));
extern int g_save_slot_text_y_offset __attribute__((sda));
extern int g_save_slot_icon_x __attribute__((sda));
extern int g_save_slot_icon_y_table[] MACRO_ADDR;
extern int g_save_slot_icon_z __attribute__((sda));
extern int g_save_slot_icon_size_table[] MACRO_ADDR;
extern int g_save_slot_icon_alpha __attribute__((sda));

/* Format strings. */
extern char g_str_save_slot_time_fmt[] NOT_SDA;
extern char g_str_save_slot_score_fmt[] NOT_SDA;
extern char g_str_save_slot_thousands_fmt[] NOT_SDA;
extern char g_str_save_slot_date_fmt[] NOT_SDA;

extern void text_draw_medium(int, int, long, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);

extern unsigned char g_language_settings[] __attribute__((sda));
extern int g_score_x_offset_2 __attribute__((sda));     /* score column width */
extern int g_score_comma_offset_x __attribute__((sda));     /* comma offset */
extern int g_score_comma_offset_y __attribute__((sda));
extern int g_score_plain_offset_x __attribute__((sda));     /* full stop offset */
extern int g_score_plain_offset_y __attribute__((sda));
extern float g_score_digit_spacing_2 __attribute__((sda));   /* digit width */
extern char g_str_score_comma_format_2[] NOT_SDA;               /* "," */
extern char g_str_score_plain_format_2[] NOT_SDA;               /* "." */
extern void text_draw_right_aligned_medium(int, int, long, char *, int);

int func_US2_002DE768(char *menu)
{
    char text[80];
    SaveRow *record;
    SaveData *context;
    int y, hours, minutes, score, extra, color, i;
    int digits, rest, comma, language, offsetX, offsetY;
    float place;

    if (g_save_menu_screen == 10)
        return 2;

    y = *(int *)(menu + 0x1C);
    SetupGifPaging(0);
    hud_draw_sprite(GetIconFrame(0xEAA9, 0), g_save_slot_icon_x, g_save_slot_icon_y_table[0], g_save_slot_icon_z, g_save_slot_icon_size_table[0], g_save_slot_icon_alpha);

    for (i = 0; i < 4; i++) {
        record = &g_save_slot_rows[i];
        context = (SaveData *)((char *)g_save_slot_rows - 0x30);
        if (context->mode >= 3 || context->selected >= 0 || *(int *)(g_pause_menu_state + 0x164) <= 10 || context->head[2] != 2) {
            y += g_save_slot_line_height * 3;
        } else if (record->state == -1) {
            y += g_save_slot_line_height;
            text_draw_centered_medium(*(int *)(menu + 0x18) + *(int *)(menu + 0x20) / 2, y + g_save_slot_text_y_offset, 0x80F0F0F0UL,
                          GetLocalizedString(0x2DAA), -1);
            y += g_save_slot_line_height;
            y += g_save_slot_line_height;
        } else {
            hours = record->ticks / 216000;
            minutes = record->ticks / 3600 - hours * 60;
            color = 0x80F0F0F0;
            if (*(int *)(menu + 0x40) == i)
                color = 0x70FFFEED;
            if (hours > 99) {
                hours = 99;
                minutes = 59;
            }
            sprintf(text, g_str_save_slot_time_fmt, hours, minutes);
            hud_draw_sprite(GetIconFrame(0xE99D, 3), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            text_draw_medium(g_save_slot_text_x + (long)(g_save_slot_icon_height + 6), y + g_save_slot_text_y_offset, color, text, -1);

            if (record->extra) {
                int iconRight, extraX;

                hud_draw_sprite(GetIconFrame(0xE99D, 4), g_save_slot_text_x + g_save_slot_extra_icon_offset, y + g_save_slot_text_y_offset, g_save_slot_icon_width,
                              g_save_slot_icon_height, 128);
                extra = record->extra;
                if (extra > 99)
                    extra = 99;
                sprintf(text, g_str_save_slot_score_fmt, extra);
                iconRight = g_save_slot_icon_height + 2;
                extraX = g_save_slot_text_x + iconRight;
                text_draw_medium((long)extraX + g_save_slot_extra_icon_offset, y + g_save_slot_text_y_offset, color, text, -1);
            }

            score = record->score;
            if (score > 9999999)
                score = 9999999;
            y += g_save_slot_line_height;
            sprintf(text, g_str_save_slot_score_fmt, score);
            hud_draw_sprite(GetIconFrame(0x7567, 0), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            {
                int iconRight, scoreX;

                iconRight = g_save_slot_icon_height + 6;
                scoreX = g_save_slot_text_x + iconRight;
                text_draw_right_aligned_medium((long)scoreX + g_score_x_offset_2, y + g_save_slot_text_y_offset, color, text, -1);
            }
            digits = 1;
            for (rest = score; rest >= 10; rest /= 10)
                digits++;
            language = g_language_settings[4];
            comma = language != 3 && language != 5 && language != 4;
            sprintf(text, comma ? g_str_score_comma_format_2 : g_str_score_plain_format_2);
            offsetY = comma ? g_score_comma_offset_y : g_score_plain_offset_y;
            offsetX = comma ? g_score_comma_offset_x : g_score_plain_offset_x;
            for (place = 3.0f; place < (float)digits; place += 3.0f) {
                text_draw_right_aligned_medium(g_save_slot_text_x + offsetX + (long)(g_save_slot_icon_height + 6) + g_score_x_offset_2 - (int)(g_score_digit_spacing_2 * place),
                              y + g_save_slot_text_y_offset + offsetY, color, text, -1);
            }
            y += g_save_slot_line_height;

            sprintf(text, g_str_save_slot_date_fmt, record->date[2], record->date[1], record->date[3]);
            hud_draw_sprite(GetIconFrame(0xE99D, 2), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            text_draw_medium(g_save_slot_text_x + (long)(g_save_slot_icon_height + 6), y + g_save_slot_text_y_offset, color, text, -1);
            y += g_save_slot_line_height;
        }
        y += g_save_slot_gap;
    }
    DoGifPaging();
    return 2;
}
