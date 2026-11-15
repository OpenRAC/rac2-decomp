#include "names.h"
/* func_00278FC0 is kept apart from 00274128.c because it calls func_00279988, which that
   unit defines but which only the boot program places: in the levels the call goes to each
   level's own copy, so it has to stay an external reference here. */

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

/* Runs the disc-streamed picture sequence: loads rows and frames from disc step by step and times each one. */
void func_00278FC0(void)
{
    if (D_00138324 & 2) {
        if (ref_L00_002E38F0_00 == 0) {
            D_001B7F80.row = 1;
            ref_L00_002E38F0_00 = 1;
        }
        EndSlotRequest(0, 0);
    }
    switch (D_001B7F80.state) {
    case 0:
        if (D_001A63AC)
            break;
        SetTableSlotValues(0x33C0, 0x33C1, 0x33EA, 1, 40, 120, 1, 9, 32, 100, 0);
        SetTableSlotValues(0x33C0, 0x33EB, 0x340D, 2, 40, 120, 1, 9, 32, 100, 1);
        SetTableSlotValues(0x340E, 0x340F, 0x340F, 3, 100, 160, 0, 1, 54, 200, 2);
        SetTableSlotValues(0x3488, 0x3489, 0x3489, 4, 100, 160, 0, 1, 36, 200, 3);
        SetTableSlotValues(0x3410, 0x3412, 0x341E, 5, 40, 120, 0, 5, 56, 300, 4);
        SetTableSlotValues(0x3410, 0x3420, 0x3422, 6, 40, 120, 0, 5, 56, 300, 5);
        SetTableSlotValues(0x3410, 0x3424, 0x3426, 7, 40, 120, 0, 5, 56, 300, 6);
        SetTableSlotValues(0x3410, 0x342D, 0x342E, 8, 40, 120, 0, 5, 56, 300, 7);
        SetTableSlotValues(0x342F, 0x3430, 0x3453, 9, 60, 120, 1, 9, 32, 100, 8);
        SetTableSlotValues(0x34B9, 0x34B9, 0x34B9, 10, 200, 512, 0, 0, 36, 200, 9);
        SetTableSlotValues(0x348A, 0x348B, 0x348C, 11, 60, 120, 0, 2, 130, 200, 10);
        SetTableSlotValues(0x348A, 0x348D, 0x348D, 12, 60, 120, 0, 1, 260, 200, 11);
        SetTableSlotValues(0x348A, 0x348E, 0x348F, 13, 60, 120, 0, 2, 130, 200, 12);
        SetTableSlotValues(0x348A, 0x3490, 0x3493, 14, 60, 120, 0, 2, 130, 200, 13);
        SetTableSlotValues(0x348A, 0x3494, 0x3494, 15, 60, 120, 0, 3, 100, 200, 14);
        SetTableSlotValues(0x348A, 0x3495, 0x349A, 16, 60, 120, 0, 2, 130, 200, 15);
        SetTableSlotValues(0x349B, 0x3412, 0x3412, 17, 200, 512, 0, 1, 36, 200, 16);
        SetTableSlotValues(0x34B7, 0x3412, 0x3412, 0, 80, 512, 0, 1, 36, 550, 17);
        SetTableSlotValues(0x349D, 0x349E, 0x34B5, 18, 60, 120, 1, 8, 32, 100, 18);
        SetTableSlotValues(0x349D, 0x34B6, 0x34B6, 19, 60, 120, 0, 1, 128, 350, 19);
        SetTableSlotValues(0x34D0, 0x34D0, 0x34D0, 0, 200, 512, 0, 1, 128, 350, 20);
        D_001B8308.count = 21;
        D_001B7F80.frame = 0;
        D_001B7F80.buffer_index = 0;
        D_001B7F80.ready = 0;
        D_001B7F80.row = -1;
        D_001B7F80.subrow = -1;
        D_001B7F80.timer = 90;
        D_001B7F80.step = 10;
        D_001B7F80.base = 310;
        D_001B7F80.duration = (float)gScreenWidth * 2.2f;
        D_001B7F80.rate = 0.16129032f;
        D_001B7F80.repeats = 5;
        D_001B7F80.speed = 0.03f;
        D_001B7F80.limit = 18;
        StartDiscRead(D_001B7F80.buffers[2], gCopySetupData.intro.offset + gCopySetupData.base,
                      gCopySetupData.intro.size);
        D_001B7F80.state = 1;
        break;
    case 1:
        if (D_001A63AC)
            break;
        if (FastFloatHelperD(&D_001B7F80.timer)) {
            RelocateDataTableOffsets();
            D_001B7F80.state = 2;
        }
        break;
    case 2: {
        SeqState278fc0 *s = &D_001B7F80;
        if (s->frame >= 20)
            s->frame %= 20;
        StartDiscRead(s->buffers[s->buffer_index],
                      gCopySetupData.frames[s->frame].offset + gCopySetupData.base,
                      gCopySetupData.frames[s->frame].size);
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
        if (AdvanceToNextItemGroup()) {
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
        ApproachValue(&gScreenFade, 0.0f, 0.06666667f);
        if (QuerySharedDataBlock()) {
            s = &D_001B7F80;
            s->state = 2;
            s->frame = D_001B8308.rows[s->row].frame;
        }
        break;
    }
    case 5:
        EndSlotRequest(0, 0);
        break;
    }
    UpdateSoundVoices();
}
