#include "include_asm.h"

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
extern SeqTable278fc0 D_001B8308;

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
extern SeqState278fc0 D_001B7F80;

/* Part of the disc table of contents at 0x14B540: a base sector and sector/size pairs. */
typedef struct { int offset, size; } TocFile278fc0;
typedef struct {
    char pad0[0x1BDC];
    int base;
    char pad1be0[0x2198 - 0x1BE0];
    TocFile278fc0 intro;
    TocFile278fc0 frames[20];
} Toc278fc0;
extern Toc278fc0 D_0014B540;

extern int D_00138324;
extern short D_001A63AC;
extern unsigned char D_001A7BB4 __attribute__((sda));
extern int D_001A7340 __attribute__((sda));
extern float D_001B15A0 __attribute__((sda));
/* The level's state word, a per-level external (see func_002799A8 in 00274128.c). */
extern int ref_L00_002E38F0_00 __attribute__((sda));
extern void func_002B4B70(int, int);
extern void func_00279790(int, int, int, int, int, int, int, int, int, int, unsigned);
extern int func_002B7B18(int, int, int);
extern int func_00282948(void *);
extern void func_00279828(void);
extern int func_002799A8(void);
extern int func_00279988(void);
extern void func_002AA2E8(float *p, float a, float b);
extern void func_002E4AC8(void);

void func_US2_00278FD0(void)
{
    int i;
    int frame;

    if (D_00138324 & 2) {
        if (ref_L00_002E38F0_00 == 0) {
            D_001B7F80.row = 1;
            ref_L00_002E38F0_00 = 1;
        }
        func_002B4B70(0, 0);
    }
    switch (D_001B7F80.state) {
    case 0:
        if (D_001A63AC)
            break;
        /* The running index `i` numbers the rows; most rows' frame (the fourth argument) is the
           next index, which after the language arms depends on the arm taken. */
        i = 0;
        func_00279790(0x3478, 0x3479, 0x34A2, 1, 40, 120, 1, 9, 32, 100, i++);
        func_00279790(0x3478, 0x34A3, 0x34C5, 2, 40, 120, 1, 9, 32, 100, i++);
        func_00279790(0x34C6, 0x34C7, 0x34C7, 3, 100, 160, 0, 1, 54, 200, i++);
        func_00279790(0x3540, 0x3541, 0x3541, 4, 100, 160, 0, 1, 36, 200, i++);
        func_00279790(0x34C8, 0x34CA, 0x34D6, 5, 40, 120, 0, 5, 56, 300, i++);
        func_00279790(0x34C8, 0x34D8, 0x34DA, 6, 40, 120, 0, 5, 56, 300, i++);
        func_00279790(0x34C8, 0x34DC, 0x34DE, 7, 40, 120, 0, 5, 56, 300, i++);
        func_00279790(0x34C8, 0x34E5, 0x34E6, 8, 40, 120, 0, 5, 56, 300, i++);
        func_00279790(0x34E7, 0x34E8, 0x350B, 9, 60, 120, 1, 9, 32, 100, i++);
        func_00279790(0x3571, 0x3571, 0x3571, 10, 200, 512, 0, 0, 36, 200, i++);
        switch (D_001A7BB4) {
        case 0:
        case 1:
            func_00279790(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354C, 0x354C, 15, 60, 120, 0, 3, 100, 200, i++);
            func_00279790(0x3542, 0x354D, 0x3552, 16, 60, 120, 0, 2, 130, 200, i++);
            break;
        case 2:
            func_00279790(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3546, 0x3546, 13, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3547, 0x3548, 14, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3549, 0x3549, 15, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x354A, 0x354B, 16, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354C, 0x354C, 17, 60, 120, 0, 3, 100, 200, i++);
            break;
        case 3:
            func_00279790(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354C, 0x354C, 15, 60, 120, 0, 3, 100, 200, i++);
            func_00279790(0x3542, 0x354D, 0x3551, 16, 60, 120, 0, 2, 130, 200, i++);
            break;
        case 4:
            func_00279790(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3548, 0x3549, 14, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354A, 0x354C, 15, 60, 120, 0, 1, 260, 200, i++);
            break;
        case 5:
            func_00279790(0x3542, 0x3543, 0x3544, 11, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3545, 0x3545, 12, 60, 120, 0, 1, 260, 200, i++);
            func_00279790(0x3542, 0x3546, 0x3547, 13, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x3548, 0x354B, 14, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354C, 0x354D, 15, 60, 120, 0, 2, 130, 200, i++);
            func_00279790(0x3542, 0x354E, 0x354E, 16, 60, 120, 0, 1, 260, 200, i++);
            break;
        }
        frame = i + 1;
        func_00279790(0x3553, 0x34CA, 0x34CA, frame, 200, 512, 0, 1, 36, 200, i++);
        frame = i + 1;
        func_00279790(0x356F, 0x34CA, 0x34CA, frame, 80, 512, 0, 1, 36, 550, i++);
        frame = i + 1;
        func_00279790(0x3555, 0x3556, 0x356D, frame, 60, 120, 1, 8, 32, 100, i++);
        frame = i + 1;
        func_00279790(0x3555, 0x356E, 0x356E, frame, 60, 120, 0, 1, 128, 350, i++);
        func_00279790(0x3588, 0x3588, 0x3588, 0, 200, 512, 0, 1, 128, 350, i++);
        D_001B8308.count = i;
        D_001B7F80.frame = 0;
        D_001B7F80.buffer_index = 0;
        D_001B7F80.ready = 0;
        D_001B7F80.row = -1;
        D_001B7F80.subrow = -1;
        D_001B7F80.timer = 90;
        D_001B7F80.step = 10;
        D_001B7F80.base = 310;
        D_001B7F80.duration = (float)D_001A7340 * 2.2f;
        D_001B7F80.rate = 0.16129032f;
        D_001B7F80.repeats = 5;
        D_001B7F80.speed = 0.03f;
        D_001B7F80.limit = 18;
        func_002B7B18(D_001B7F80.buffers[2], D_0014B540.intro.offset + D_0014B540.base,
                      D_0014B540.intro.size);
        D_001B7F80.state = 1;
        break;
    case 1:
        if (D_001A63AC)
            break;
        if (func_00282948(&D_001B7F80.timer)) {
            func_00279828();
            D_001B7F80.state = 2;
        }
        break;
    case 2: {
        SeqState278fc0 *s = &D_001B7F80;
        if (s->frame >= 20)
            s->frame %= 20;
        func_002B7B18(s->buffers[s->buffer_index],
                      D_0014B540.frames[s->frame].offset + D_0014B540.base,
                      D_0014B540.frames[s->frame].size);
        s->state = 3;
        break;
    }
    case 3: {
        SeqState278fc0 *s;
        if (D_001A63AC)
            break;
        s = &D_001B7F80;
        s->ready = 1;
        s->buffer_index ^= 1;
        if (func_002799A8()) {
            s->state = 4;
            switch (D_001B8308.rows[s->row].kind) {
            case 0:
                s->timer = D_001B8308.rows[s->row].delay;
                break;
            case 1:
            case 2:
                s->timer = s->base + s->step * (D_001B8308.rows[s->row].count - 1);
                break;
            }
        } else {
            s->state = 5;
        }
        break;
    }
    case 4: {
        SeqState278fc0 *s;
        func_002AA2E8(&D_001B15A0, 0.0f, 0.06666667f);
        if (func_00279988()) {
            s = &D_001B7F80;
            s->state = 2;
            s->frame = D_001B8308.rows[s->row].frame;
        }
        break;
    }
    case 5:
        func_002B4B70(0, 0);
        break;
    }
    func_002E4AC8();
}
