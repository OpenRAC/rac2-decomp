#include "include_asm.h"
#include "names.h"
typedef struct {
    unsigned char pad0[0x84];
    int f84;
    int f88;
    char *f8c;
    unsigned char pad1[0x15C - 0x90];
    int f15c;
    int f160;
    unsigned char *f164;
    unsigned char pad2[0x1A0 - 0x168];
    int f1a0;
    unsigned char pad3[0x1B0 - 0x1A4];
    float f1b0;
    unsigned char pad3b[4];
    int f1b8;
    unsigned char pad4[0x2D0 - 0x1BC];
    float f2d0;
} L04_004044B8_Record;
extern int IsPointInCuboid(void *, int);
extern void anim_start_blended(char *, int, int, int);
extern int g_is_pal_video __attribute__((sda));
extern int g_race_time_ticks;

/* Updates the record's flag from the two point tests, prints the message when the
   record has one and its counter runs, then advances the counter and the value. */
void racer_update_checkpoint_progress_pal(void *moby, L04_004044B8_Record *record)
{
    char *point = (char *)moby + 0x10;
    int lap;

    if (IsPointInCuboid(point, record->f88)) {
        record->f15c = 1;
    }
    if (!IsPointInCuboid(point, record->f84)) {
        return;
    }
    if (record->f15c == 0) {
        return;
    }
    lap = record->f160;
    if (record->f8c && lap > 0) {
        anim_start_blended(record->f8c, 9, 0, 0xA);
        lap = record->f160;
    }
    if (lap < 4) {
        float frames = (float)record->f1b8;
        float seconds;
        float time_left;

        if (g_is_pal_video != 0) {
            seconds = frames * 0.02f;
        } else {
            seconds = frames * 0.016666667f;
        }
        time_left = record->f2d0 + record->f1b0 - seconds;
        record->f2d0 = time_left;
        if (time_left < 0.0f) {
            record->f2d0 = 0.0f;
        }
        record->f1b8 = 0;
        record->f15c = 0;
        record->f160 = record->f160 + 1;
        if (record->f160 != 3) {
            return;
        }
        if (*(unsigned char *)(record->f164 + 0x20) == 2) {
            record->f1a0 = g_race_time_ticks;
        }
    }
}
