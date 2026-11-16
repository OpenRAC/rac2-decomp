#include "include_asm.h"
#include "names.h"

typedef struct {
    char pad0[0x8];
    int max_value;
    int *value_ptr;
    char pad10[0x38];
    short unk_48;
    short unk_4A;
    char pad4C[0x4];
    int unk_50;
    int unk_54;
    int width;
    int height;
    int flags;
    char pad64[0x8];
    int unk_6C;
    unsigned char counter_bytes[4];
    int shown_value;
    int target_value;
    int show_timer;
    void *unk_80;
} HudElem;
typedef unsigned char u8;

/* Starts a counter element: shows it for 180 frames and sets up its counter values. */
void hud_init_counter_element_pal(HudElem *element) { element->show_timer = 0xB4; element->unk_48 = 0; element->unk_4A = 0; hud_init_counter_values((u8 *)element); }

extern float IntToFloat(int);
extern int FloatToInt(float);
extern float square_root(float);
extern int hud_pick_anim_frame_pal(void *);

/* Moves the shown counter value toward the real one and fades the element in and out (PAL: 50 Hz timings). */
void hud_update_counter_element_pal(HudElem *element)
{
    unsigned char *counter = element->counter_bytes;
    int delta, limit, step;
    if (element->value_ptr) {
        int value = *element->value_ptr;
        if (value < 0) value = 0;
        element->target_value = value;
        if (element->max_value < value) element->target_value = element->max_value;
    }
    if (element->shown_value != element->target_value) {
        element->show_timer = 150;
        if (element->unk_6C >= 24) {
            delta = __builtin_abs(element->shown_value - element->target_value);
            if (delta) {
                step = FloatToInt(square_root(IntToFloat(delta) * 0.04f) * 5.0f);
                limit = delta / 4;
                if (step < limit) step = limit;
                if (step > 121) step = 121;
                else if (step < 1) step = 1;
                counter[3] += step;
                if (counter[3] >= 3) {
                    step = counter[3] / 2;
                    if (element->target_value < element->shown_value) element->shown_value -= step;
                    else element->shown_value += step;
                    counter[3] -= step * 2;
                }
            }
        }
    }
    if (element->show_timer >= 4) {
        if (counter[0] < 7) counter[0]++;
        else if (counter[1] < 7) counter[1]++;
    } else {
        if (counter[1] != 0 || counter[0] != 0) element->unk_6C = 1;
        {
            int fade = counter[1];
            if (fade) counter[1] = fade - 1;
            else {
                if (counter[0]) counter[0]--;
            }
        }
    }
    hud_pick_anim_frame_pal((char *)element + 0x40);
}

