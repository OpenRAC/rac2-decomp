#include "include_asm.h"
#include "common.h"
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern int g_menu_panel_fill_color __attribute__((sda));

/* Draws a small check box at the given spot, with a tick mark inside when it is on. */
void DrawMenuCheckBox(int x, int y, int show)
{
    AppendScreenRectPacket(x - 5, y - 5, x + 5, y + 5, 0x80FFA888UL, 0);
    AppendScreenRectPacket(x - 4, y - 4, x + 4, y + 4, g_menu_panel_fill_color, 0);
    if (show)
        hud_draw_sprite(GetIconFrame(0xE99D, 1), x - 13, y - 18, 30, 30, 128);
}

extern int ref_L00_002D68D8_00 __attribute__((sda));
extern int FastTweenColor(int, int, float);
/* Gives a highlight color that fades from one color to another as a timer counts up. */
int menu_blend_highlight_color(int start, int first, int second)
{
    int count;
    float fraction;
    if (start < 0) start = 0;
    if (first == -1) first = (int)0x80FFA888u;
    if (second == -1) second = (int)0x8020FFFFu;
    count = ref_L00_002D68D8_00;
    if (count >= start)
        fraction = 1.0f - (float)(count - start) / (float)count;
    else
        fraction = 1.0f;
    return FastTweenColor(first, second, fraction);
}

extern void menu_stream_chunk_table_init(int);
extern char *menu_stream_chunk_claim_free(int);
extern void menu_clear_block_fields(void);
extern void menu_clear_counter(void);
extern void popup_set_flag_on(void *);
extern volatile int g_menu_panel_active;
extern char *g_resident_data_base __attribute__((sda));

/* Prepares a menu page when it opens and clears its two image slots. */
int menu_preview_page_init(char *object)
{
    menu_stream_chunk_table_init(1);
    *(int *)(object + 0x48) = menu_stream_chunk_claim_free(0);
    *(int *)(object + 0x4C) = 0;
    menu_clear_block_fields();
    menu_clear_counter();
    if (g_menu_panel_active != 0 && g_resident_data_base != 0)
        popup_set_flag_on(g_resident_data_base + 0x3CAA8);
    return 0;
}

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern unsigned long long load_texture_file(int);
extern void DrawTexturedQuad(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern int g_menu_texture_a_width __attribute__((sda));
extern char *g_menu_texture_a_data;
extern int g_menu_texture_a_height;
extern int g_menu_texture_a_extra;
extern int g_menu_texture_b_width __attribute__((sda));
extern char *g_menu_texture_b_data;
extern int g_menu_texture_b_height;
extern int g_menu_texture_b_extra;

/* Draws two see-through pictures on a menu page once it has been open a few frames. */
int menu_texture_pair_draw(char *object)
{
    unsigned long long color;
    unsigned long long packet;
    if (*(int *)(object + 0x44) < 4)
        return 0;
    color = 0x60A09080ULL;
    SetupGifPaging(0);
    packet = load_texture_file(*(int *)(object + 0x48));
    DrawTexturedQuad(g_menu_texture_a_width, g_menu_texture_a_data, g_menu_texture_a_height, g_menu_texture_a_extra, 0, 0, 0x100, 0x100, color, packet);
    packet = load_texture_file(*(int *)(object + 0x4C));
    DrawTexturedQuad(g_menu_texture_b_width, g_menu_texture_b_data, g_menu_texture_b_height, g_menu_texture_b_extra, 0, 0, 0x100, 0x100, color, packet);
    DoGifPaging();
    return 8;
}

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
extern char g_str_save_slot_score_millions_fmt[] NOT_SDA;
extern char g_str_save_slot_date_fmt[] NOT_SDA;

extern void text_draw_medium(int, int, long, char *, int);
extern int text_draw_centered_medium(int, int, u64, char *, int);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);

/* Draws the four save slots with play time, extra count, score and date, or an empty-slot message. */
int save_slot_list_draw(char *menu)
{
    char text[80];
    SaveRow *record;
    SaveData *context;
    int y, hours, minutes, score, extra, color, i;

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
                          GetLocalizedString(0x2F14), -1);
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
            if (score < 1000)
                sprintf(text, g_str_save_slot_score_fmt, score);
            else if (score < 1000000)
                sprintf(text, g_str_save_slot_thousands_fmt, score / 1000, score % 1000);
            else
                sprintf(text, g_str_save_slot_score_millions_fmt, score / 1000000, (score % 1000000) / 1000, score % 1000);
            hud_draw_sprite(GetIconFrame(0x7567, 0), g_save_slot_text_x + 4, y + g_save_slot_text_y_offset, g_save_slot_icon_width, g_save_slot_icon_height, 128);
            text_draw_medium(g_save_slot_text_x + (long)(g_save_slot_icon_height + 6), y + g_save_slot_text_y_offset, color, text, -1);
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

/* The game state at D_001F2840, as far as the page menu uses it. */
typedef struct {
    u8 pad0[8];
    int field8;             /* 0x08 */
    u8 padC[8];
    u8 *owner;              /* 0x14: active menu screen */
    int current;            /* 0x18 */
    u8 pad1C[0xC];
    int saved;              /* 0x28 */
    u8 pad2C[0xAF];
    u8 active;              /* 0xDB */
    u8 padDC[0x18];
    int page;               /* 0xF4 */
    u8 padF8[8];
    u8 *savedOwner;         /* 0x100 */
    int savedCurrent;       /* 0x104 */
    u8 pad108[0x2C];
    int lock;               /* 0x134 */
    u8 pad138[8];
    int savedMode;          /* 0x140 */
} PageRoot;

typedef struct {
    u8 pad[0x230];
    int page;               /* 0x230: current page, 0..27 */
} PageMap;

typedef struct {
    u8 pad[0x1C4];
    u32 buttons;            /* 0x1C4 */
} PagePad;

typedef struct {
    u8 pad[0x30];
    int selection[28];      /* 0x30: selected row per page */
    int count;              /* 0xA0: rows on the current page */
} PageMenu;

typedef struct {
    char pad[0x34];
    int item;               /* 0x34 */
    int pad38;
    int timer;              /* 0x3C */
} PagePreview;

extern char g_map_overlay_state[];
extern char g_pad_state[];

extern PagePreview g_page_preview;
extern u8 g_level_page_root[];
extern u8 g_map_visited_flags[] MACRO_ADDR;  /* page available, one byte per page */
extern int g_request_flag_table[];            /* flag bits: bit (n & 31) of word n >> 2 */
extern int g_level_page_entry_value[];
extern int g_loader_state_word;
extern int g_current_map_index __attribute__((sda));
extern int g_vram_frame_base __attribute__((sda));
extern char g_loader_movie[];

extern int map_find_table_index(int);
extern void map_set_current_and_refresh(int);
extern int snd_play_from_global_bank(int, int, void *);
extern int menu_update_entry_states(void);
extern int menu_list_active_entries(int *, int *, int *, int);
extern void menu_restore_saved_screen_image(int);
extern int req_push_queue(char *, int);
extern int req_launch_queued(char *);

/* Handles buttons on the page list: moves between pages and rows, goes back, or opens the page's own screen. */
int level_page_menu_update_input(PageMenu *menu)
{
    int previous, count, old, next, mapped;

    previous = ((PageMap *)g_map_overlay_state)->page;
    if (*(PageMenu **)(((PageRoot *)g_pause_menu_state)->owner + 0xE8) != menu) {
        if (((PageMap *)g_map_overlay_state)->page < 28)
            menu->selection[((PageMap *)g_map_overlay_state)->page] = -1;
        return 0;
    }
    if ((((PagePad *)g_pad_state)->buttons & 0xD00) && !((PageRoot *)g_pause_menu_state)->lock && ((PageRoot *)g_pause_menu_state)->owner != g_level_page_root)
        return 1;

    /* Next and previous available page. */
    if (((PagePad *)g_pad_state)->buttons & 8) {
        for (next = ((PageMap *)g_map_overlay_state)->page + 1; next < 28; next++) {
            if (g_map_visited_flags[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PagePad *)g_pad_state)->buttons & 4) {
        for (next = ((PageMap *)g_map_overlay_state)->page - 1; next >= 0; next--) {
            if (g_map_visited_flags[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PageMap *)g_map_overlay_state)->page != previous) {
        snd_play_from_global_bank(3, 0, 0);
        menu_update_entry_states();
    }

    /* Rows of the page, written to the scratchpad. */
    count = menu_list_active_entries((int *)0x70000000, 0, (int *)0x70000100, 1);
    menu->count = count;
    if (count) {
        u32 buttons = ((PagePad *)g_pad_state)->buttons;
        int *selections = menu->selection;
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            old = *entry;
            if (buttons & 0x1000)
                *entry = (old + count - 1) % count;
        }
        if (buttons & 0x4000) {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            *entry = (*entry + 1) % menu->count;
        }
        {
            int *entry = &selections[((PageMap *)g_map_overlay_state)->page];
            if (*entry != old)
                snd_play_from_global_bank(3, 0, 0);
        }
        if ((buttons & 0x5000) || ((PageMap *)g_map_overlay_state)->page != previous) {
            int *entry;
            g_page_preview.timer = -576;
            entry = &selections[((PageMap *)g_map_overlay_state)->page];
            g_page_preview.item = ((int *)0x70000000)[*entry];
            *g_level_page_entry_value = ((int *)0x70000100)[*entry];
        }
    } else {
        g_page_preview.item = 0;
        *g_level_page_entry_value = -1;
    }

    /* Back. */
    if ((((PagePad *)g_pad_state)->buttons & 0x10) && ((PageRoot *)g_pause_menu_state)->owner != g_level_page_root) {
        int back = *(int *)(((PageRoot *)g_pause_menu_state)->owner + 0xE0);
        int status;
        if (back)
            ((PageRoot *)g_pause_menu_state)->current = back;
        else if (!((PageRoot *)g_pause_menu_state)->lock) {
            status = -1;
            goto done;
        }
        status = 0;
done:
        return status;
    }

    /* Open the page's special screen. */
    if ((((PagePad *)g_pad_state)->buttons & 0x20) && ((PageMap *)g_map_overlay_state)->page >= 0) {
        if (((PageRoot *)g_pause_menu_state)->active)
            return 0;
        if (((PageMap *)g_map_overlay_state)->page == 0)
            mapped = 21;
        else if (((PageMap *)g_map_overlay_state)->page == 24)
            mapped = 0;
        else
            mapped = ((PageMap *)g_map_overlay_state)->page;
        if (((PageMap *)g_map_overlay_state)->page >= 0) {
            unsigned int word = (unsigned)mapped >> 2;
            int bit = 1 << (mapped & 0x1F);
            if (g_request_flag_table[word] & bit) {
                g_vram_frame_base = ((PageRoot *)g_pause_menu_state)->saved;
                menu_restore_saved_screen_image(0);
                ((PageRoot *)g_pause_menu_state)->savedMode = g_loader_state_word;
                ((PageRoot *)g_pause_menu_state)->savedOwner = ((PageRoot *)g_pause_menu_state)->owner;
                ((PageRoot *)g_pause_menu_state)->page = ((PageMap *)g_map_overlay_state)->page;
                ((PageRoot *)g_pause_menu_state)->savedCurrent = ((PageRoot *)g_pause_menu_state)->field8;
                g_loader_state_word = 2;
                req_push_queue(g_loader_movie, mapped);
                req_launch_queued(g_loader_movie);
                return 1;
            }
        }
    }
    return 0;
}
