#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    u8 pad0[0x14];
    u16 *f14;
    u8 pad1[4];
    s32 f1C;
} TutorialState;

typedef struct {
    u8 pad0[0x3A];
    s16 f3A;
    u8 pad1[4];
} Rec;

extern TutorialState g_tutorial_points;
extern Rec *g_tfrag_render_data[1] __attribute__((sda));
extern s32 g_tfrag_count[1] __attribute__((sda));

/* Resets the tutorial-controlled value in every record to a default, or remaps it through the tutorial table. */
void tutorial_reset_record_values(void)
{
    Rec *rec;
    s16 *field;
    s32 remaining;
    s32 count;
    TutorialState *state;

    if (g_tutorial_points.f1C == 0) {
        remaining = g_tfrag_count[0];
        if (remaining <= 0)
            return;
        field = &g_tfrag_render_data[0]->f3A;
        do {
            *field = 0x7F80;
            field = (s16 *)((u8 *)field + 0x40);
            remaining--;
        } while (remaining != 0);
    } else {
        remaining = g_tfrag_count[0];
        if (remaining <= 0)
            return;
        rec = g_tfrag_render_data[0];
        state = &g_tutorial_points;
        count = remaining;
        do {
            rec->f3A = state->f14[rec->f3A];
            rec = (Rec *)((u8 *)rec + 0x40);
            count--;
        } while (count != 0);
    }
}
