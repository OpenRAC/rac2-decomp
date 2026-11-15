#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
typedef struct { char reserved00[0x1C4]; int flags; } MenuGameState;
typedef struct { short reserved00, key; int value; } MenuMessage;
extern MenuGameState g_pad_state;
extern CallbackState g_pause_menu_state;
extern char *D_001A8CFC[] __attribute__((sda));
extern int menu_get_counter(void);
extern int menu_get_mode(void);
extern void menu_clear_counter(void);
extern void data_set_small_value_and_refresh(int, int);
extern int func_0029C560(int);
extern char *tab_menu_get_selected_entry(void *);
extern void menu_start_action(int);
extern int D_001ABA88 __attribute__((sda));
extern int D_001ABA8C;
extern int D_001ABA90 __attribute__((sda));
extern int D_001ABA94;
extern int D_001ABA98 __attribute__((sda));
extern int D_001ABA9C;
extern float D_001B23A8;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(int, int);
extern void gfx_draw_scaled_object(char *, int, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(long long, long long, long long, char *, long long);
extern void text_draw_right_aligned_small(long long, long long, long long, char *, long long);

/* Draws a small pop-up menu box with three layered title images and two lines of text with button hints. */
int menu_popup_box_draw(void)
{
    SetupGifPaging(0);
    if (D_001A8CFC[0] != 0) {
        gfx_draw_scaled_object(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x96), 0x60442D00,
                      (float)D_001ABA90, (float)D_001ABA94, D_001B23A8, 0.0f);
        gfx_draw_scaled_object(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x97), 0x60241700,
                      (float)D_001ABA90, (float)D_001ABA94, D_001B23A8, 0.0f);
        gfx_draw_scaled_object(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x98), 0x55F0C070,
                      (float)D_001ABA90, (float)D_001ABA94, D_001B23A8, 0.0f);
        text_draw_centered_small(D_001ABA90 + D_001ABA88, D_001ABA94 + D_001ABA8C, 0x80F0F0F0,
                      GetLocalizedString(0x2D62), -1);
        text_draw_right_aligned_small(D_001ABA90 + D_001ABA98, D_001ABA94 + D_001ABA9C, 0x80F0F0F0,
                      GetLocalizedString(0x2D4F), -1);
    }
    DoGifPaging();
    return 0;
}

/* Handles input for a pop-up menu: leaves at once if the game is in a special state, otherwise reports cancel or accept and sends the preview message. */
int menu_popup_update(void)
{
    MenuMessage message;
    int result = 0;
    MenuGameState *state;
    int flags;
    if (menu_get_counter() == 2 && menu_get_mode() == 9) {
        menu_clear_counter();
        data_set_small_value_and_refresh(-1, 0);
        return 1;
    }
    menu_clear_counter();
    state = &g_pad_state;
    flags = state->flags;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && D_001A8CFC[0] != 0) {
            char *data = tab_menu_get_selected_entry(D_001A8CFC[0] + 0x3BE08);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            menu_start_action((int)&message);
        }
    }
    return result;
}
