#include "include_asm.h"
#include "names.h"
extern void menu_stream_chunk_table_init(int);
extern char *menu_stream_chunk_claim_free(int);
extern void menu_clear_block_fields(void);
extern void menu_clear_counter(void);
extern void popup_set_flag_on(void *);
extern volatile int g_menu_panel_active;
extern char *g_resident_data_base __attribute__((sda));

/* Prepares a menu page when it opens and clears its two image slots. */
int menu_preview_page_init_us2(char *menu)
{
    menu_stream_chunk_table_init(1);
    *(int *)(menu + 0x48) = menu_stream_chunk_claim_free(0);
    *(int *)(menu + 0x4C) = 0;
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
int save_slot_location_text_draw_us2(int *box)
{
    char name_buffer[64];
    char *menu_state = g_pause_menu_state;
    Slots_002DC900 *slots = &g_memcard_state;
    int location_index;
    int second_line_id;
    int y_offset;

    location_index = slots->entries[*(int *)(*(char **)(*(char **)(menu_state + 0x14) + 0xE8) + 0x40)].first % 0x1C;
    SetupGifPaging(0);
    if (slots->mode < 3 && slots->selected < 0 && *(int *)(menu_state + 0x164) >= 11 && slots->state == 2) {
        if (location_index == -1) {
            text_draw_centered_small(box[6], box[7] + g_save_location_line_height / 2, 0x80F0F0F0, GetLocalizedString(0x2DAA), -1);
        } else {
            second_line_id = g_menu_text_id_table[location_index * 2 + 1];
            y_offset = 0;
            if (second_line_id < 0) y_offset = g_save_location_line_height >> 1;
            text_draw_centered_small(box[6], box[7] + y_offset, 0x80F0F0F0, text_format_location_name(name_buffer, location_index), -1);
            if (second_line_id >= 0) {
                text_draw_centered_small(box[6], box[7] + g_save_location_line_height, 0x80F0F0F0, GetLocalizedString(g_menu_text_id_table[location_index * 2 + 1]), -1);
            }
        }
    }
    DoGifPaging();
    return 2;
}
