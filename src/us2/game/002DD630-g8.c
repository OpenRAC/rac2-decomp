#include "include_asm.h"
#include "names.h"
extern void menu_stream_chunk_table_init(int);
extern char *menu_stream_chunk_claim_free(int);
extern void menu_clear_block_fields(void);
extern void menu_clear_counter(void);
extern void popup_set_flag_on(void *);
extern volatile int g_menu_panel_active;
extern char *g_resident_data_base __attribute__((sda));

int menu_preview_page_init_us2(char *object)
{
    menu_stream_chunk_table_init(1);
    *(int *)(object + 0x48) = menu_stream_chunk_claim_free(0);
    *(int *)(object + 0x4C) = 0;
    menu_clear_block_fields();
    menu_clear_counter();
    if (g_menu_panel_active != 0 && g_resident_data_base != 0)
        popup_set_flag_on(g_resident_data_base + 0x3CEA0);
    return 0;
}

typedef struct {
    int first, second, third, fourth;
    char stamp[8];
    int invalid;
} SlotEntry_002DC900;
typedef struct {
    char pad000[0x8];
    int state;
    char pad00C[0x30 - 0xC];
    SlotEntry_002DC900 entries[4];
    char pad0A0[0x15C - 0xA0];
    int mode;
    int pad160;
    int selected;
} Slots_002DC900;
extern Slots_002DC900 g_memcard_state;
extern char g_pause_menu_state[];
extern int g_menu_text_id_table[];
extern int g_save_location_line_height __attribute__((sda));
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern char *GetLocalizedString(int);
extern char *text_format_location_name(char *, int);
extern int text_draw_centered_small(int, int, unsigned long, char *, int);

/* Menu line for the current slot: prints its name (and the follow-up line)
   while the menu is in its listing state. */
int func_US2_002DD630(int *box)
{
    char buf[64];
    char *g = g_pause_menu_state;
    Slots_002DC900 *s = &g_memcard_state;
    int idx;
    int next;
    int y;

    idx = s->entries[*(int *)(*(char **)(*(char **)(g + 0x14) + 0xE8) + 0x40)].first % 0x1C;
    SetupGifPaging(0);
    if (s->mode < 3 && s->selected < 0 && *(int *)(g + 0x164) >= 11 && s->state == 2) {
        if (idx == -1) {
            text_draw_centered_small(box[6], box[7] + g_save_location_line_height / 2, 0x80F0F0F0, GetLocalizedString(0x2DAA), -1);
        } else {
            next = g_menu_text_id_table[idx * 2 + 1];
            y = 0;
            if (next < 0) y = g_save_location_line_height >> 1;
            text_draw_centered_small(box[6], box[7] + y, 0x80F0F0F0, text_format_location_name(buf, idx), -1);
            if (next >= 0) {
                text_draw_centered_small(box[6], box[7] + g_save_location_line_height, 0x80F0F0F0, GetLocalizedString(g_menu_text_id_table[idx * 2 + 1]), -1);
            }
        }
    }
    DoGifPaging();
    return 2;
}
