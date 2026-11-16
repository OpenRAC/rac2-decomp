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
extern void func_PAL_00279B50(int, int, int, int, int, int, int, int, int, int, unsigned);
extern int load_start_disc_read(int, int, int);
extern int math_fast_float_d(void *);
extern void load_relocate_data_table_offsets(void);
extern int data_advance_to_next_item_group(void);
extern int data_query_shared_block(void);
extern f32 ApproachValue(float *p, float a, float b);
extern s32 UpdateSoundVoices_pal(void);

void func_PAL_00278E60(void)
{
    int n;

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
        n = 0;
        func_PAL_00279B50(0x1CF4, 0x1CF5, 0x1D1E, n + 1, 40, 120, 1, 9, 32, 100, n++);
        func_PAL_00279B50(0x1CF4, 0x1D1F, 0x1D41, n + 1, 40, 120, 1, 9, 32, 100, n++);
        func_PAL_00279B50(0x1D42, 0x1D43, 0x1D43, n + 1, 100, 160, 0, 1, 54, 200, n++);
        func_PAL_00279B50(0x1DBC, 0x1DBD, 0x1DBD, n + 1, 100, 160, 0, 1, 36, 200, n++);
        func_PAL_00279B50(0x1D8C, 0x1D8D, 0x1D93, n + 1, 40, 120, 0, 4, 75, 300, n++);
        func_PAL_00279B50(0x1D8C, 0x1D9E, 0x1DA6, n + 1, 40, 120, 0, 4, 75, 300, n++);
        func_PAL_00279B50(0x1D8C, 0x1DA7, 0x1DAB, n + 1, 40, 120, 0, 3, 100, 300, n++);
        func_PAL_00279B50(0x1D94, 0x1D95, 0x1D9D, n + 1, 60, 120, 1, 9, 32, 100, n++);
        func_PAL_00279B50(0x1DED, 0x1DED, 0x1DED, n + 1, 200, 512, 0, 0, 36, 200, n++);
        switch (g_pal_region_mode) {
        case 0:
        case 1:
            func_PAL_00279B50(0x1DBE, 0x1DBF, 0x1DC0, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC1, 0x1DC1, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC2, 0x1DC3, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC4, 0x1DC7, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC8, 0x1DC8, n + 1, 60, 120, 0, 3, 100, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC9, 0x1DCE, n + 1, 60, 120, 0, 2, 130, 200, n++);
            break;
        case 2:
            func_PAL_00279B50(0x1DBE, 0x1DBF, 0x1DC0, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC1, 0x1DC1, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC2, 0x1DC2, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC3, 0x1DC4, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC5, 0x1DC5, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC6, 0x1DC7, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC8, 0x1DC8, n + 1, 60, 120, 0, 3, 100, 200, n++);
            break;
        case 3:
            func_PAL_00279B50(0x1DBE, 0x1DBF, 0x1DC0, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC1, 0x1DC1, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC2, 0x1DC3, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC4, 0x1DC7, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC8, 0x1DC8, n + 1, 60, 120, 0, 3, 100, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC9, 0x1DCD, n + 1, 60, 120, 0, 2, 130, 200, n++);
            break;
        case 4:
            func_PAL_00279B50(0x1DBE, 0x1DBF, 0x1DC0, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC1, 0x1DC1, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC2, 0x1DC3, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC4, 0x1DC5, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC6, 0x1DC8, n + 1, 60, 120, 0, 1, 260, 200, n++);
            break;
        case 5:
            func_PAL_00279B50(0x1DBE, 0x1DBF, 0x1DC0, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC1, 0x1DC1, n + 1, 60, 120, 0, 1, 260, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC2, 0x1DC3, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC4, 0x1DC7, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DC8, 0x1DC9, n + 1, 60, 120, 0, 2, 130, 200, n++);
            func_PAL_00279B50(0x1DBE, 0x1DCA, 0x1DCA, n + 1, 60, 120, 0, 1, 260, 200, n++);
            break;
        }
        func_PAL_00279B50(0x1DCF, 0x1D46, 0x1D46, n + 1, 200, 512, 0, 1, 36, 200, n++);
        func_PAL_00279B50(0x1DAC, 0x1DAD, 0x1DAF, n + 1, 60, 120, 0, 3, 36, 550, n++);
        func_PAL_00279B50(0x1DD1, 0x1DD2, 0x1DE9, n + 1, 60, 120, 1, 8, 32, 100, n++);
        func_PAL_00279B50(0x1DD1, 0x1DEA, 0x1DEA, n + 1, 60, 120, 0, 1, 128, 350, n++);
        func_PAL_00279B50(0x1E04, 0x1E04, 0x1E04, 0, 200, 512, 0, 1, 128, 350, n++);
        g_disc_player_seq_table.count = n;
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
        ApproachValue(&g_screen_fade, 0.0f, 0.080000006f);
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
    UpdateSoundVoices_pal();
}

struct Rac2Native_00169805055547ed_Rec31cd0302 {
    int v[10];
};
extern struct Rac2Native_00169805055547ed_Rec31cd0302 g_slot_l04_value_table[];

/* Store ten integer arguments in the indexed record when the unsigned index is below 32; otherwise leave the table unchanged. */
void func_PAL_00279B50(int p0, int p1, int p2, int p3, int p4, int p5,
                                      int p6, int p7, int p8, int p9, unsigned idx)
{
    if (idx >= 32u)
        return;
    g_slot_l04_value_table[idx].v[0] = p0;
    g_slot_l04_value_table[idx].v[1] = p1;
    g_slot_l04_value_table[idx].v[2] = p2;
    g_slot_l04_value_table[idx].v[3] = p3;
    g_slot_l04_value_table[idx].v[4] = p4;
    g_slot_l04_value_table[idx].v[5] = p5;
    g_slot_l04_value_table[idx].v[6] = p6;
    g_slot_l04_value_table[idx].v[7] = p7;
    g_slot_l04_value_table[idx].v[8] = p8;
    g_slot_l04_value_table[idx].v[9] = ((s32)(p9) * 5 + 2) / 6;
}

