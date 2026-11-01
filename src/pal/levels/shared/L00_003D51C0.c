#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003D5AB0);

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
extern int func_L00_002D3FB0(int);
extern int func_L00_002D3FB8(int, int);
extern int D_00139688[];
extern unsigned char D_00139568[];
extern L00PickupSoundEntry D_L00_00262570[];
extern void func_PAL_L00_003282B0(int, int, int);
extern void func_00282C88(void *);
extern int func_00282C30(int);
extern int D_L00_001B19C8[] __attribute__((sda));
extern int ref_L00_003D1B50_00[] __attribute__((sda));
extern int func_002E5CF8(int index, int value, void *object);

/* Defined in L00_003D1258-g8.c. */


/* Checks whether a pickup object has just added to the stock counter of its item kind: plays the
   single or multiple pickup sound, and when the amount exceeds the limit marks the object as
   used up. Returns 1 if the counter grew. */
int func_PAL_L00_003D5AB8(L00PickupObject *object)
{
    L00PickupState *state = object->state;
    int old_count;
    int delta;
    int sound;
    int result;
    float overflow;

    if (object->phase == 2)
        return 0;

    old_count = D_00139688[func_L00_002D3FB0(state->item)];
    overflow = func_L00_002D3FB8(state->item, state->limit);
    if (old_count < D_00139688[func_L00_002D3FB0(state->item)]) {
        delta = D_00139688[func_L00_002D3FB0(state->item)] - old_count;
        if (delta == 1) {
            sound = ((L00PickupSoundEntry *)(D_00139568[func_L00_002D3FB0(state->item)] * 224 +
                                             (unsigned int)D_L00_00262570))->single_sound;
        } else {
            sound = ((L00PickupSoundEntry *)(D_00139568[func_L00_002D3FB0(state->item)] * 224 +
                                             (unsigned int)D_L00_00262570))->multiple_sound;
        }
        func_PAL_L00_003282B0(sound, delta, -1);
        if (overflow < state->limit) {
            int elapsed;

            object->phase = 2;
            object->scale *= 1.24f;
            func_00282C88(state);
            elapsed = D_L00_001B19C8[0] - ref_L00_003D1B50_00[0];
            state->fade_rate = 0.16000001f;
            if (func_00282C30(elapsed) >= 9) {
                func_002E5CF8(0, 0, object);
                ref_L00_003D1B50_00[0] = D_L00_001B19C8[0];
            }
        }
        result = 1;
    } else {
        result = 0;
    }
    return result;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003D5C90);



INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003D6F08);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003D7400);
