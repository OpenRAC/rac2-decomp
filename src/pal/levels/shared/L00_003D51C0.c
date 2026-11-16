#include "include_asm.h"
#include "names.h"


typedef struct {
    char pad_00[0x38];
    short multiple_sound;
    short single_sound;
    char pad_3C[0xA4];
} L00PickupSoundEntry;
typedef struct {
    char pad_00[0x60];
    int limit;
    char pad_64[4];
    int item;
    char pad_6C[8];
    float fade_rate;
    char pad_78[0x14];
} L00PickupState;
typedef struct {
    char pad_00[0x20];
    unsigned char phase;
    char pad_21[0xB];
    float scale;
    char pad_30[0x38];
    L00PickupState *state;
} L00PickupObject;
extern int math_l00_return_argument_2(int);
extern int weapon_add_ammo(int, int);
extern int g_item_ammo_counts[];
extern unsigned char g_item_slot_to_record[];
extern L00PickupSoundEntry g_weapon_l00_table[];
extern void part_reset_effects_pal(int, int, int);
extern void vec_clear_128(void *);
extern int subtract_integer_with_clamp(int);
extern int g_frame_l00_counter[] __attribute__((sda));
extern int ref_L00_003D1B50_00[] __attribute__((sda));
extern int PlayMobySound(int index, int value, void *object);

/* Defined in L00_003D1258-g8.c. */


/* Checks whether a pickup object has just added to the stock counter of its item kind: plays the
   single or multiple pickup sound, and when the amount exceeds the limit marks the object as
   used up. Returns 1 if the counter grew. */
int pickup_check_stock_increase_pal(L00PickupObject *object)
{
    L00PickupState *state = object->state;
    int old_count;
    int delta;
    int sound;
    int result;
    float overflow;

    if (object->phase == 2)
        return 0;

    old_count = g_item_ammo_counts[math_l00_return_argument_2(state->item)];
    overflow = weapon_add_ammo(state->item, state->limit);
    if (old_count < g_item_ammo_counts[math_l00_return_argument_2(state->item)]) {
        delta = g_item_ammo_counts[math_l00_return_argument_2(state->item)] - old_count;
        if (delta == 1) {
            sound = ((L00PickupSoundEntry *)(g_item_slot_to_record[math_l00_return_argument_2(state->item)] * 224 +
                                             (unsigned int)g_weapon_l00_table))->single_sound;
        } else {
            sound = ((L00PickupSoundEntry *)(g_item_slot_to_record[math_l00_return_argument_2(state->item)] * 224 +
                                             (unsigned int)g_weapon_l00_table))->multiple_sound;
        }
        part_reset_effects_pal(sound, delta, -1);
        if (overflow < state->limit) {
            int elapsed;

            object->phase = 2;
            object->scale *= 1.24f;
            vec_clear_128(state);
            elapsed = g_frame_l00_counter[0] - ref_L00_003D1B50_00[0];
            state->fade_rate = 0.16000001f;
            if (subtract_integer_with_clamp(elapsed) >= 9) {
                PlayMobySound(0, 0, object);
                ref_L00_003D1B50_00[0] = g_frame_l00_counter[0];
            }
        }
        result = 1;
    } else {
        result = 0;
    }
    return result;
}






