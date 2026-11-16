#include "names.h"
/* func_PAL_002DE710, the PAL copy of func_002DDA10 (src/game/002D5E98-g8.c): the same C, where the empty
   slot's string is 0xE39, the date prints day first, and the score is printed plain and right-aligned through
   func_0027FA10, with its thousands separators drawn over it one at a time: ',' or '.' chosen by the language
   byte, none for language 2. Compiled with the template unit's flags (-O2 -G8 -ffunction-sections, from its -g8 name). */
#include "include_asm.h"
#include "common.h"

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern int GetIconFrame(int, int);
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
extern char g_str_save_slot_date_fmt[] NOT_SDA;
extern char g_str_score_comma_format[] NOT_SDA; /* "," */
extern char g_str_score_plain_format[] NOT_SDA; /* "." */

/* The settings bytes at D_001A7BB0 (0x1A7C38 in PAL): [4] is the language, written by func_PAL_002914E0 as
   D_001A7BB0[4] and read the same way by func_US2_002DE768 and func_PAL_0034FD60. The symbol-plus-offset
   form is the unsplit two-word load, which reorg keeps out of the delay slot of the digit-count loop's
   first test, as retail does. */
extern unsigned char g_language_settings[] __attribute__((sda));

/* The right-aligned score: column width, the offsets of ',' and of '.', the width of a digit. */
extern int g_score_x_offset __attribute__((sda));
extern int g_score_comma_dx __attribute__((sda));
extern int g_score_comma_dy __attribute__((sda));
extern int g_score_plain_dx __attribute__((sda));
extern int g_score_plain_dy __attribute__((sda));
extern float g_score_digit_spacing __attribute__((sda));

extern void text_draw_medium(int, int, long, char *, int);
extern void text_draw_right_aligned_medium(int, int, long, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);

/* Draws the four save slot rows: play time, extra count, score and date, or a message for an empty slot. */
int save_slot_list_draw_pal(char *menu)
{
    char text[80];
    SaveRow *record;
    SaveData *context;
    int y, hours, minutes, score, extra, color, i;
    int digits, value, comma, dx, dy, icon_width, score_x;

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
                          GetLocalizedString(0xE39), -1);
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
                int icon_right, extra_x;

                hud_draw_sprite(GetIconFrame(0xE99D, 4), g_save_slot_text_x + g_save_slot_extra_icon_offset, y + g_save_slot_text_y_offset, g_save_slot_icon_width,
                              g_save_slot_icon_height, 128);
                extra = record->extra;
                if (extra > 99)
                    extra = 99;
                sprintf(text, g_str_save_slot_score_fmt, extra);
                icon_right = g_save_slot_icon_height + 2;
                extra_x = g_save_slot_text_x + icon_right;
                text_draw_medium((long)extra_x + g_save_slot_extra_icon_offset, y + g_save_slot_text_y_offset, color, text, -1);
            }

            score = record->score;
            if (score > 9999999)
                score = 9999999;
            y += g_save_slot_line_height;
            sprintf(text, g_str_save_slot_score_fmt, score);
            hud_draw_sprite(GetIconFrame(0x7567, 0), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            icon_width = g_save_slot_icon_height + 6;
            score_x = g_save_slot_text_x + icon_width;
            text_draw_right_aligned_medium((long)score_x + g_score_x_offset, y + g_save_slot_text_y_offset, color, text, -1);
            digits = 1;
            for (value = score; value >= 10; value /= 10)
                digits++;
            comma = !(g_language_settings[4] == 3 || g_language_settings[4] == 5 || g_language_settings[4] == 4);
            sprintf(text, comma ? g_str_score_comma_format : g_str_score_plain_format);
            dy = comma ? g_score_comma_dy : g_score_plain_dy;
            dx = comma ? g_score_comma_dx : g_score_plain_dx;
            if (g_language_settings[4] != 2) {
                float place;
                for (place = 3.0f; place < digits; place += 3.0f)
                    text_draw_right_aligned_medium(g_save_slot_text_x + dx + (long)(g_save_slot_icon_height + 6) + g_score_x_offset - (int)(g_score_digit_spacing * place),
                                  y + g_save_slot_text_y_offset + dy, color, text, -1);
            }
            y += g_save_slot_line_height;

            sprintf(text, g_str_save_slot_date_fmt, record->date[1], record->date[2], record->date[3]);
            hud_draw_sprite(GetIconFrame(0xE99D, 2), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            text_draw_medium(g_save_slot_text_x + (long)(g_save_slot_icon_height + 6), y + g_save_slot_text_y_offset, color, text, -1);
            y += g_save_slot_line_height;
        }
        y += g_save_slot_gap;
    }
    DoGifPaging();
    return 2;
}
