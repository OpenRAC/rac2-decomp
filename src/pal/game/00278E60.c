#include "include_asm.h"
#include "common.h"

/* func_PAL_00278E60, the PAL copy of func_00278FC0 (src/game/00274128-seq.c): the same C, where case 0
   registers its rows with a running slot n, part of them chosen by the language byte, and the
   timings are scaled to 50 Hz. Each row's frame is n + 1 and its slot n: this compiler evaluates
   the arguments left to right, so the trailing n++ is read after n + 1. */

/* Rows registered by func_PAL_00279B50, ten words each, and the number in use. */
typedef struct {
    int key, first, last, frame, w4, w5, kind, count, w8, delay;
} SeqRow278fc0;
typedef struct {
    SeqRow278fc0 rows[32];
    int count;
} SeqTable278fc0;
extern SeqTable278fc0 g_disc_player_seq_table;

/* State block at 0x1B7F80: disc buffers, the current row and frame, and the timing
   parameters case 0 sets. */
typedef struct {
    int buffers[7];
    short buffer_index, frame, row, subrow, ready, state;
    int timer;
    char pad2c[0x36C - 0x2C];
    int step, base;
    float duration, rate;
    int repeats;
    float speed;
    int limit;
} SeqState278fc0;
extern SeqState278fc0 g_disc_player_seq_state;

/* Part of the disc table of contents at 0x14B540: a base sector and sector/size pairs. */
typedef struct { int offset, size; } TocFile278fc0;
typedef struct {
    char pad0[0x1BDC];
    int base;
    char pad1be0[0x2198 - 0x1BE0];
    TocFile278fc0 intro;
    TocFile278fc0 frames[20];
} Toc278fc0;
extern Toc278fc0 g_copy_setup_data;

extern int g_pad_held_flags;
extern short g_sequence_active_flag;
extern unsigned char g_pal_region_mode MACRO_ADDR;
extern int g_screen_width __attribute__((sda));
extern float g_screen_fade __attribute__((sda));
/* The level's state word, a per-level external (see func_002799A8 in 00274128.c). */
extern int ref_L00_002E38F0_00 __attribute__((sda));
extern int request_end_slot(int, int);
extern void table_set_slot_values_pal(int, int, int, int, int, int, int, int, int, int, unsigned);
extern int load_start_disc_read(int, int, int);
extern int math_fast_float_d(void *);
extern void load_relocate_data_table_offsets(void);
extern int data_advance_to_next_item_group(void);
extern int data_query_shared_block(void);
extern f32 ApproachValue(float *p, float a, float b);
extern s32 UpdateSoundVoices_pal(void);

void seq_update_disc_player_pal(void)
{
    int row_count;

    if (g_pad_held_flags & 2) {
        if (ref_L00_002E38F0_00 == 0) {
            g_disc_player_seq_state.row = 1;
            ref_L00_002E38F0_00 = 1;
        }
        request_end_slot(0, 0);
    }
    switch (g_disc_player_seq_state.state) {
    case 0:
        if (g_sequence_active_flag)
            break;
        row_count = 0;
        table_set_slot_values_pal(0x1CF4, 0x1CF5, 0x1D1E, row_count + 1, 40, 120, 1, 9, 32, 100, row_count++);
        table_set_slot_values_pal(0x1CF4, 0x1D1F, 0x1D41, row_count + 1, 40, 120, 1, 9, 32, 100, row_count++);
        table_set_slot_values_pal(0x1D42, 0x1D43, 0x1D43, row_count + 1, 100, 160, 0, 1, 54, 200, row_count++);
        table_set_slot_values_pal(0x1DBC, 0x1DBD, 0x1DBD, row_count + 1, 100, 160, 0, 1, 36, 200, row_count++);
        table_set_slot_values_pal(0x1D8C, 0x1D8D, 0x1D93, row_count + 1, 40, 120, 0, 4, 75, 300, row_count++);
        table_set_slot_values_pal(0x1D8C, 0x1D9E, 0x1DA6, row_count + 1, 40, 120, 0, 4, 75, 300, row_count++);
        table_set_slot_values_pal(0x1D8C, 0x1DA7, 0x1DAB, row_count + 1, 40, 120, 0, 3, 100, 300, row_count++);
        table_set_slot_values_pal(0x1D94, 0x1D95, 0x1D9D, row_count + 1, 60, 120, 1, 9, 32, 100, row_count++);
        table_set_slot_values_pal(0x1DED, 0x1DED, 0x1DED, row_count + 1, 200, 512, 0, 0, 36, 200, row_count++);
        switch (g_pal_region_mode) {
        case 0:
        case 1:
            table_set_slot_values_pal(0x1DBE, 0x1DBF, 0x1DC0, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC1, 0x1DC1, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC2, 0x1DC3, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC4, 0x1DC7, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC8, 0x1DC8, row_count + 1, 60, 120, 0, 3, 100, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC9, 0x1DCE, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            break;
        case 2:
            table_set_slot_values_pal(0x1DBE, 0x1DBF, 0x1DC0, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC1, 0x1DC1, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC2, 0x1DC2, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC3, 0x1DC4, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC5, 0x1DC5, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC6, 0x1DC7, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC8, 0x1DC8, row_count + 1, 60, 120, 0, 3, 100, 200, row_count++);
            break;
        case 3:
            table_set_slot_values_pal(0x1DBE, 0x1DBF, 0x1DC0, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC1, 0x1DC1, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC2, 0x1DC3, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC4, 0x1DC7, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC8, 0x1DC8, row_count + 1, 60, 120, 0, 3, 100, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC9, 0x1DCD, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            break;
        case 4:
            table_set_slot_values_pal(0x1DBE, 0x1DBF, 0x1DC0, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC1, 0x1DC1, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC2, 0x1DC3, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC4, 0x1DC5, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC6, 0x1DC8, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            break;
        case 5:
            table_set_slot_values_pal(0x1DBE, 0x1DBF, 0x1DC0, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC1, 0x1DC1, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC2, 0x1DC3, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC4, 0x1DC7, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DC8, 0x1DC9, row_count + 1, 60, 120, 0, 2, 130, 200, row_count++);
            table_set_slot_values_pal(0x1DBE, 0x1DCA, 0x1DCA, row_count + 1, 60, 120, 0, 1, 260, 200, row_count++);
            break;
        }
        table_set_slot_values_pal(0x1DCF, 0x1D46, 0x1D46, row_count + 1, 200, 512, 0, 1, 36, 200, row_count++);
        table_set_slot_values_pal(0x1DAC, 0x1DAD, 0x1DAF, row_count + 1, 60, 120, 0, 3, 36, 550, row_count++);
        table_set_slot_values_pal(0x1DD1, 0x1DD2, 0x1DE9, row_count + 1, 60, 120, 1, 8, 32, 100, row_count++);
        table_set_slot_values_pal(0x1DD1, 0x1DEA, 0x1DEA, row_count + 1, 60, 120, 0, 1, 128, 350, row_count++);
        table_set_slot_values_pal(0x1E04, 0x1E04, 0x1E04, 0, 200, 512, 0, 1, 128, 350, row_count++);
        g_disc_player_seq_table.count = row_count;
        g_disc_player_seq_state.frame = 0;
        g_disc_player_seq_state.buffer_index = 0;
        g_disc_player_seq_state.ready = 0;
        g_disc_player_seq_state.row = -1;
        g_disc_player_seq_state.subrow = -1;
        g_disc_player_seq_state.timer = 75;
        g_disc_player_seq_state.step = 8;
        g_disc_player_seq_state.base = 258;
        g_disc_player_seq_state.duration = (float)g_screen_width * 2.64f;
        g_disc_player_seq_state.rate = 0.19379845f;
        g_disc_player_seq_state.repeats = 5;
        g_disc_player_seq_state.speed = 0.03f;
        g_disc_player_seq_state.limit = 18;
        load_start_disc_read(g_disc_player_seq_state.buffers[2], g_copy_setup_data.intro.offset + g_copy_setup_data.base,
                      g_copy_setup_data.intro.size);
        g_disc_player_seq_state.state = 1;
        break;
    case 1:
        if (g_sequence_active_flag)
            break;
        if (math_fast_float_d(&g_disc_player_seq_state.timer)) {
            load_relocate_data_table_offsets();
            g_disc_player_seq_state.state = 2;
        }
        break;
    case 2: {
        SeqState278fc0 *seq = &g_disc_player_seq_state;
        if (seq->frame >= 20)
            seq->frame %= 20;
        load_start_disc_read(seq->buffers[seq->buffer_index],
                      g_copy_setup_data.frames[seq->frame].offset + g_copy_setup_data.base,
                      g_copy_setup_data.frames[seq->frame].size);
        seq->state = 3;
        break;
    }
    case 3: {
        SeqState278fc0 *seq;
        if (g_sequence_active_flag)
            break;
        seq = &g_disc_player_seq_state;
        seq->ready = 1;
        seq->buffer_index ^= 1;
        if (data_advance_to_next_item_group()) {
            seq->state = 4;
            switch (g_disc_player_seq_table.rows[seq->row].kind) {
            case 0:
                seq->timer = g_disc_player_seq_table.rows[seq->row].delay;
                break;
            case 1:
            case 2:
                seq->timer = seq->base + seq->step * (g_disc_player_seq_table.rows[seq->row].count - 1);
                break;
            }
        } else {
            seq->state = 5;
        }
        break;
    }
    case 4: {
        SeqState278fc0 *seq;
        ApproachValue(&g_screen_fade, 0.0f, 0.080000006f);
        if (data_query_shared_block()) {
            seq = &g_disc_player_seq_state;
            seq->state = 2;
            seq->frame = g_disc_player_seq_table.rows[seq->row].frame;
        }
        break;
    }
    case 5:
        request_end_slot(0, 0);
        break;
    }
    UpdateSoundVoices_pal();
}

struct Rac2Native_00169805055547ed_Rec31cd0302 {
    int v[10];
};
extern struct Rac2Native_00169805055547ed_Rec31cd0302 g_slot_l04_value_table[];

/* Store ten integer arguments in the indexed record when the unsigned index is below 32; otherwise leave the table unchanged. */
void table_set_slot_values_pal(int key, int first, int last, int frame, int w4, int w5,
                                      int kind, int count, int w8, int delay, unsigned slot)
{
    if (slot >= 32u)
        return;
    g_slot_l04_value_table[slot].v[0] = key;
    g_slot_l04_value_table[slot].v[1] = first;
    g_slot_l04_value_table[slot].v[2] = last;
    g_slot_l04_value_table[slot].v[3] = frame;
    g_slot_l04_value_table[slot].v[4] = w4;
    g_slot_l04_value_table[slot].v[5] = w5;
    g_slot_l04_value_table[slot].v[6] = kind;
    g_slot_l04_value_table[slot].v[7] = count;
    g_slot_l04_value_table[slot].v[8] = w8;
    g_slot_l04_value_table[slot].v[9] = ((s32)(delay) * 5 + 2) / 6;
}

