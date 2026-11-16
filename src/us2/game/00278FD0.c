#include "include_asm.h"
#include "names.h"

/* func_US2_00278FD0, the USA v2.00 copy of func_00278FC0: the same C, with the row table's text
   ids moved and the middle rows chosen by language (g_currentLanguage, D_001A7BB4). The arms
   register different numbers of rows, so a running counter indexes them, and the rows after the
   arms take their frame numbers from it. */

/* Rows registered by func_00279790, ten words each, and the number in use. */
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
extern unsigned char g_language __attribute__((sda));
extern int g_screen_width __attribute__((sda));
extern float g_screen_fade __attribute__((sda));
/* The level's state word, a per-level external (see func_002799A8 in 00274128.c). */
extern int ref_L00_002E38F0_00 __attribute__((sda));
extern int request_end_slot(int, int);
extern void table_set_slot_values(int, int, int, int, int, int, int, int, int, int, unsigned);
extern int load_start_disc_read(int, int, int);
extern int math_fast_float_d(void *);
extern void load_relocate_data_table_offsets(void);
extern int data_advance_to_next_item_group(void);
extern int data_query_shared_block(void);
extern float ApproachValue(float *p, float a, float b);
extern int UpdateSoundVoices(void);

/* Plays the disc player sequence: registers the row table, then streams each row's frames from disc and advances until the sequence ends (USA v2.00: text ids moved, rows chosen by language). */
void seq_update_disc_player_us2(void)
{
    int i;
    int frame;

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
        /* The running index `i` numbers the rows; most rows' frame (the fourth argument) is the
           next index, which after the language arms depends on the arm taken. */
        i = 0;
        table_set_slot_values(0x3478, 0x3479, 0x34A2, 1, 40, 120, 1, 9, 32, 100, i++);
        table_set_slot_values(0x3478, 0x34A3, 0x34C5, 2, 40, 120, 1, 9, 32, 100, i++);
        table_set_slot_values(0x34C6, 0x34C7, 0x34C7, 3, 100, 160, 0, 1, 54, 200, i++);
        table_set_slot_values(0x3540, 0x3541, 0x3541, 4, 100, 160, 0, 1, 36, 200, i++);
        table_set_slot_values(0x34C8, 0x34CA, 0x34D6, 5, 40, 120, 0, 5, 56, 300, i++);
        table_set_slot_values(0x34C8, 0x34D8, 0x34DA, 6, 40, 120, 0, 5, 56, 300, i++);
        table_set_slot_values(0x34C8, 0x34DC, 0x34DE, 7, 40, 120, 0, 5, 56, 300, i++);
        table_set_slot_values(0x34C8, 0x34E5, 0x34E6, 8, 40, 120, 0, 5, 56, 300, i++);
        table_set_slot_values(0x34E7, 0x34E8, 0x350B, 9, 60, 120, 1, 9, 32, 100, i++);
        table_set_slot_values(0x3571, 0x3571, 0x3571, 10, 200, 512, 0, 0, 36, 200, i++);
        switch (g_language) {
        case 0:
        case 1:
            table_set_slot_values(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354C, 0x354C, 15, 60, 120, 0, 3, 100, 200, i++);
            table_set_slot_values(0x3542, 0x354D, 0x3552, 16, 60, 120, 0, 2, 130, 200, i++);
            break;
        case 2:
            table_set_slot_values(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3546, 0x3546, 13, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3547, 0x3548, 14, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3549, 0x3549, 15, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x354A, 0x354B, 16, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354C, 0x354C, 17, 60, 120, 0, 3, 100, 200, i++);
            break;
        case 3:
            table_set_slot_values(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354C, 0x354C, 15, 60, 120, 0, 3, 100, 200, i++);
            table_set_slot_values(0x3542, 0x354D, 0x3551, 16, 60, 120, 0, 2, 130, 200, i++);
            break;
        case 4:
            table_set_slot_values(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3548, 0x3549, 14, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354A, 0x354C, 15, 60, 120, 0, 1, 260, 200, i++);
            break;
        case 5:
            table_set_slot_values(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            table_set_slot_values(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354C, 0x354D, 15, 60, 120, 0, 2, 130, 200, i++);
            table_set_slot_values(0x3542, 0x354E, 0x354E, 16, 60, 120, 0, 1, 260, 200, i++);
            break;
        }
        frame = i + 1;
        table_set_slot_values(0x3553, 0x34CA, 0x34CA, frame, 200, 512, 0, 1, 36, 200, i++);
        frame = i + 1;
        table_set_slot_values(0x356F, 0x34CA, 0x34CA, frame, 80, 512, 0, 1, 36, 550, i++);
        frame = i + 1;
        table_set_slot_values(0x3555, 0x3556, 0x356D, frame, 60, 120, 1, 8, 32, 100, i++);
        frame = i + 1;
        table_set_slot_values(0x3555, 0x356E, 0x356E, frame, 60, 120, 0, 1, 128, 350, i++);
        table_set_slot_values(0x3588, 0x3588, 0x3588, 0, 200, 512, 0, 1, 128, 350, i++);
        g_disc_player_seq_table.count = i;
        g_disc_player_seq_state.frame = 0;
        g_disc_player_seq_state.buffer_index = 0;
        g_disc_player_seq_state.ready = 0;
        g_disc_player_seq_state.row = -1;
        g_disc_player_seq_state.subrow = -1;
        g_disc_player_seq_state.timer = 90;
        g_disc_player_seq_state.step = 10;
        g_disc_player_seq_state.base = 310;
        g_disc_player_seq_state.duration = (float)g_screen_width * 2.2f;
        g_disc_player_seq_state.rate = 0.16129032f;
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
        SeqState278fc0 *s = &g_disc_player_seq_state;
        if (s->frame >= 20)
            s->frame %= 20;
        load_start_disc_read(s->buffers[s->buffer_index],
                      g_copy_setup_data.frames[s->frame].offset + g_copy_setup_data.base,
                      g_copy_setup_data.frames[s->frame].size);
        s->state = 3;
        break;
    }
    case 3: {
        SeqState278fc0 *s;
        if (g_sequence_active_flag)
            break;
        s = &g_disc_player_seq_state;
        s->ready = 1;
        s->buffer_index ^= 1;
        if (data_advance_to_next_item_group()) {
            s->state = 4;
            switch (g_disc_player_seq_table.rows[s->row].kind) {
            case 0:
                s->timer = g_disc_player_seq_table.rows[s->row].delay;
                break;
            case 1:
            case 2:
                s->timer = s->base + s->step * (g_disc_player_seq_table.rows[s->row].count - 1);
                break;
            }
        } else {
            s->state = 5;
        }
        break;
    }
    case 4: {
        SeqState278fc0 *s;
        ApproachValue(&g_screen_fade, 0.0f, 0.06666667f);
        if (data_query_shared_block()) {
            s = &g_disc_player_seq_state;
            s->state = 2;
            s->frame = g_disc_player_seq_table.rows[s->row].frame;
        }
        break;
    }
    case 5:
        request_end_slot(0, 0);
        break;
    }
    UpdateSoundVoices();
}
