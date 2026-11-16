#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

extern int func_00115DA8_1(char *, char *, ...);

extern char g_str_number_millions_format[];

extern char g_str_number_thousands_format[];

extern char g_str_number_plain_format[];

extern void Fbbb7bee1_FUN_00282A38(int value);

extern int g_packet_l06_buffer_index __attribute__((sda));

extern int g_packet_l06_buffer_size __attribute__((sda));

extern int g_packet_l06_buffer_offset __attribute__((sda));

extern int g_packet_buffer_starts[];

extern int D_L06_001B2F88_5 __attribute__((sda));

extern int g_packet_buffer_cursor __attribute__((sda));

extern int g_packet_buffer_limit __attribute__((sda));

/* shared native body of family bc82131e */
/* Writes a number as text, with a space or comma between each group of three digits. */
void text_format_number_with_separators(char *dst, int value)
{
    if (value > 999999)
        func_00115DA8_1(dst, g_str_number_millions_format, value / 1000000, (value / 1000) % 1000, value % 1000);
    else if (value >= 1000)
        func_00115DA8_1(dst, g_str_number_thousands_format, value / 1000, value % 1000);
    else
        func_00115DA8_1(dst, g_str_number_plain_format, value);
}

/* func_002F9C80 is in 002F9C80.c. */

/* func_002FA270 is defined in 002FA270-ammo-g8.c. */

/* func_002FA880 is matched in 002F9BC0-vendor-g8.c. */



extern volatile int g_special_items_bought_flags[] __attribute__((sda));
extern void shop_mark_item_owned(int);

/* Marks each special weapon bought this visit as owned in the shop list, then clears the
   flag that triggered it. */
void shop_mark_bought_special_items_owned(void)
{
    if (g_special_items_bought_flags[0] & 1) shop_mark_item_owned(12);
    if (g_special_items_bought_flags[0] & 2) shop_mark_item_owned(53);
    if (g_special_items_bought_flags[0] & 4) shop_mark_item_owned(17);
    if (g_special_items_bought_flags[0] & 8) shop_mark_item_owned(14);
    if (g_special_items_bought_flags[0] & 16) shop_mark_item_owned(18);
    g_special_items_bought_flags[0] &= ~128;
}


extern void load_request_disc_read_break(void);
extern int ref_L00_002FB170_00[];

/* Stops the shop preview and clears its two active flags. */
void shop_clear_preview(void) { load_request_disc_read_break(); ref_L00_002FB170_00[0x23] = 0; ref_L00_002FB170_00[0x22] = 0; }


typedef struct { int key; int value; } Func002FBFB8Entry;
extern Func002FBFB8Entry g_lookup_key_table[];

/* Looks up a key in the table and returns its matching value, or -1 if it is not there. */
int game_lookup_table_value_by_key(int key)
{
    if (g_lookup_key_table[0].key >= 0) {
        Func002FBFB8Entry *entry = g_lookup_key_table;
        Func002FBFB8Entry *end = entry + 28;
        do {
            if (key == entry->key)
                return entry->value;
            entry++;
        } while (((int)entry < (int)end) & (entry->key >= 0));
    }
    return -1;
}


extern int game_lookup_table_value_by_key(int);
extern unsigned char g_game_flag_table[];
/* Checks one bit of the save byte that belongs to a key; returns 1 if it is set. */
int save_test_flag_bit_2(int key, int bit)
{
    int index = game_lookup_table_value_by_key(key);
    if (index >= 0) {
        unsigned char value = g_game_flag_table[index] & (1 << bit);
        g_game_flag_table[index] = value;
        return value != 0;
    }
    return 0;
}

/* Starts a transfer on DMA channel 0 from the given list address and waits until it is done. */
void gfx_start_dma_channel0_and_wait(int listAddress)
{
    while (((int)D0_CHCR) & 0x100)
        Fbbb7bee1_FUN_00282A38(16);
    D0_QWC = 0;
    D0_TADR = listAddress & 0x0FFFFFFF;
    D0_CHCR = 325;
    while (((int)D0_CHCR) & 0x100)
        Fbbb7bee1_FUN_00282A38(16);
}

/* func_002FC138 is matched in 002F9BC0-g8.c (-G8 small data). */

/* func_002FC190 is matched in 002F9BC0-g8.c (-G8 small data). */

/* func_002FC1D8 is matched in 002F9BC0-g8.c (-G8 small data). */

/* shared native body of family 74e6a904f3b4f71c (default profile) */
/* Switches to the other of the two packet buffers and works out where drawing into it starts. */
void gfx_swap_packet_buffer(void)
{
    int nextBuffer;
    int target;
    int offset;
    int bufferStart;

    nextBuffer = 1 - g_packet_l06_buffer_index;
    target = g_packet_l06_buffer_size;
    offset = g_packet_l06_buffer_offset;
    g_packet_l06_buffer_index = nextBuffer;
    bufferStart = g_packet_buffer_starts[nextBuffer];
    target = bufferStart + g_packet_l06_buffer_size;
    D_L06_001B2F88_5 = bufferStart;
    target = target - offset;
    g_packet_buffer_cursor = target;
    g_packet_buffer_limit = target - 8192;
}

/* func_002FC280 is matched in 002F9BC0-packet-g8.c. */
