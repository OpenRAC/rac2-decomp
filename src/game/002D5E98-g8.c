#include "include_asm.h"
#include "common.h"
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern int D_001AA43C __attribute__((sda));

/* Draws a small check box at the given spot, with a tick mark inside when it is on. */
void DrawMenuCheckBox(int x, int y, int show)
{
    AppendScreenRectPacket(x - 5, y - 5, x + 5, y + 5, 0x80FFA888UL, 0);
    AppendScreenRectPacket(x - 4, y - 4, x + 4, y + 4, D_001AA43C, 0);
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

extern int menu_stream_chunk_table_init(int);
extern int menu_stream_chunk_claim_free(int);
extern int menu_clear_block_fields(void);
extern void menu_clear_counter(void);
extern void popup_set_flag_on(void *);
extern volatile int D_001A8C88;
extern char *D_001A8CFC __attribute__((sda));

/* Prepares a menu page when it opens and clears its two image slots. */
int menu_preview_page_init(char *object)
{
    menu_stream_chunk_table_init(1);
    *(int *)(object + 0x48) = menu_stream_chunk_claim_free(0);
    *(int *)(object + 0x4C) = 0;
    menu_clear_block_fields();
    menu_clear_counter();
    if (D_001A8C88 != 0 && D_001A8CFC != 0)
        popup_set_flag_on(D_001A8CFC + 0x3CAA8);
    return 0;
}

extern void SetupGifPaging(int);
extern void DoGifPaging(void);
extern unsigned long long load_texture_file(int);
extern void DrawTexturedQuad(int, char *, int, int, int, int, int, int, unsigned long long, unsigned long long);
extern int D_001ABB48 __attribute__((sda));
extern char *D_001ABB4C;
extern int D_001ABB50;
extern int D_001ABB54;
extern int D_001ABB58 __attribute__((sda));
extern char *D_001ABB5C;
extern int D_001ABB60;
extern int D_001ABB64;

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
    DrawTexturedQuad(D_001ABB48, D_001ABB4C, D_001ABB50, D_001ABB54, 0, 0, 0x100, 0x100, color, packet);
    packet = load_texture_file(*(int *)(object + 0x4C));
    DrawTexturedQuad(D_001ABB58, D_001ABB5C, D_001ABB60, D_001ABB64, 0, 0, 0x100, 0x100, color, packet);
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

extern SaveRow D_00139410[];

/* GP-relative layout coefficients of the save-slot panel. */
extern int D_001ABBF0 __attribute__((sda)); /* line height */
extern int D_001ABBF4 __attribute__((sda)); /* slot gap */
extern int D_001ABBF8 __attribute__((sda));
extern int D_001ABBFC __attribute__((sda));
extern int D_001ABC00 __attribute__((sda));
extern int D_001ABC04 __attribute__((sda));
extern int D_001ABC08 __attribute__((sda));
extern int D_001ABC10 __attribute__((sda));
extern int D_001ABC14[] MACRO_ADDR;
extern int D_001ABC18 __attribute__((sda));
extern int D_001ABC1C[] MACRO_ADDR;
extern int D_001ABC20 __attribute__((sda));

/* Format strings. */
extern char D_001ABC28[] NOT_SDA;
extern char D_001ABAF0[] NOT_SDA;
extern char D_001ABB20[] NOT_SDA;
extern char D_001ABC38[] NOT_SDA;
extern char D_001ABC48[] NOT_SDA;

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
    hud_draw_sprite(GetIconFrame(0xEAA9, 0), D_001ABC10, D_001ABC14[0], D_001ABC18, D_001ABC1C[0], D_001ABC20);

    for (i = 0; i < 4; i++) {
        record = &D_00139410[i];
        context = (SaveData *)((char *)D_00139410 - 0x30);
        if (context->mode >= 3 || context->selected >= 0 || *(int *)(g_pause_menu_state + 0x164) <= 10 || context->head[2] != 2) {
            y += D_001ABBF0 * 3;
        } else if (record->state == -1) {
            y += D_001ABBF0;
            text_draw_centered_medium(*(int *)(menu + 0x18) + *(int *)(menu + 0x20) / 2, y + D_001ABC08, 0x80F0F0F0UL,
                          GetLocalizedString(0x2F14), -1);
            y += D_001ABBF0;
            y += D_001ABBF0;
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
            sprintf(text, D_001ABC28, hours, minutes);
            hud_draw_sprite(GetIconFrame(0xE99D, 3), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            text_draw_medium(D_001ABC04 + (long)(D_001ABBFC + 6), y + D_001ABC08, color, text, -1);

            if (record->extra) {
                int iconRight, extraX;

                hud_draw_sprite(GetIconFrame(0xE99D, 4), D_001ABC04 + D_001ABC00, y + D_001ABC08, D_001ABBF8,
                              D_001ABBFC, 128);
                extra = record->extra;
                if (extra > 99)
                    extra = 99;
                sprintf(text, D_001ABAF0, extra);
                iconRight = D_001ABBFC + 2;
                extraX = D_001ABC04 + iconRight;
                text_draw_medium((long)extraX + D_001ABC00, y + D_001ABC08, color, text, -1);
            }

            score = record->score;
            if (score > 9999999)
                score = 9999999;
            y += D_001ABBF0;
            if (score < 1000)
                sprintf(text, D_001ABAF0, score);
            else if (score < 1000000)
                sprintf(text, D_001ABB20, score / 1000, score % 1000);
            else
                sprintf(text, D_001ABC38, score / 1000000, (score % 1000000) / 1000, score % 1000);
            hud_draw_sprite(GetIconFrame(0x7567, 0), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            text_draw_medium(D_001ABC04 + (long)(D_001ABBFC + 6), y + D_001ABC08, color, text, -1);
            y += D_001ABBF0;

            sprintf(text, D_001ABC48, record->date[2], record->date[1], record->date[3]);
            hud_draw_sprite(GetIconFrame(0xE99D, 2), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            text_draw_medium(D_001ABC04 + (long)(D_001ABBFC + 6), y + D_001ABC08, color, text, -1);
            y += D_001ABBF0;
        }
        y += D_001ABBF4;
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

extern PagePreview D_0025A6E0;
extern u8 D_0025E680[];
extern u8 D_001A7BC8[] MACRO_ADDR;  /* page available, one byte per page */
extern int D_00139768[];            /* flag bits: bit (n & 31) of word n >> 2 */
extern int D_0025A620[];
extern int D_001A7478;
extern int g_current_map_index __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern char D_001BAD40[];

extern int map_find_table_index(int);
extern void map_set_current_and_refresh(int);
extern int snd_play_from_global_bank(int, int, void *);
extern void menu_update_entry_states(void);
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
    if ((((PagePad *)g_pad_state)->buttons & 0xD00) && !((PageRoot *)g_pause_menu_state)->lock && ((PageRoot *)g_pause_menu_state)->owner != D_0025E680)
        return 1;

    /* Next and previous available page. */
    if (((PagePad *)g_pad_state)->buttons & 8) {
        for (next = ((PageMap *)g_map_overlay_state)->page + 1; next < 28; next++) {
            if (D_001A7BC8[next] || g_current_map_index == next) {
                if (map_find_table_index(next) < 0)
                    return 0;
                map_set_current_and_refresh(next);
                break;
            }
        }
    }
    if (((PagePad *)g_pad_state)->buttons & 4) {
        for (next = ((PageMap *)g_map_overlay_state)->page - 1; next >= 0; next--) {
            if (D_001A7BC8[next] || g_current_map_index == next) {
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
            D_0025A6E0.timer = -576;
            entry = &selections[((PageMap *)g_map_overlay_state)->page];
            D_0025A6E0.item = ((int *)0x70000000)[*entry];
            *D_0025A620 = ((int *)0x70000100)[*entry];
        }
    } else {
        D_0025A6E0.item = 0;
        *D_0025A620 = -1;
    }

    /* Back. */
    if ((((PagePad *)g_pad_state)->buttons & 0x10) && ((PageRoot *)g_pause_menu_state)->owner != D_0025E680) {
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
            if (D_00139768[word] & bit) {
                D_001A72D4 = ((PageRoot *)g_pause_menu_state)->saved;
                menu_restore_saved_screen_image(0);
                ((PageRoot *)g_pause_menu_state)->savedMode = D_001A7478;
                ((PageRoot *)g_pause_menu_state)->savedOwner = ((PageRoot *)g_pause_menu_state)->owner;
                ((PageRoot *)g_pause_menu_state)->page = ((PageMap *)g_map_overlay_state)->page;
                ((PageRoot *)g_pause_menu_state)->savedCurrent = ((PageRoot *)g_pause_menu_state)->field8;
                D_001A7478 = 2;
                req_push_queue(D_001BAD40, mapped);
                req_launch_queued(D_001BAD40);
                return 1;
            }
        }
    }
    return 0;
}
