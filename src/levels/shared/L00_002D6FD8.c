#include "include_asm.h"
#include "names.h"

/* The first pad's state (ref_L00_002D6FD8_03 is g_pad_state in every program) as far as the
 * vibration goes: the two motor bytes the pad's actuator command is built from. */
typedef struct {
    unsigned char prefix[0x188];
    unsigned char small_motor;
    unsigned char large_motor;
} PadMotors;

/* [2]: the motors are only set while it is non-zero (the vibration option, by its use). */
extern unsigned char ref_L00_002D6FD8_01[3];

/* The small motor's running sum. */
extern int ref_L00_002D6FD8_00;

extern PadMotors ref_L00_002D6FD8_03;

/* LevelActuatorCalcPower. */
extern int ref_L00_002D6FD8_02(int words[2]);

/* Mixes the vibration's wave channels (LevelActuatorCalcPower) and, with vibration on, sets the
 * pad's motors: the large one to its mixed value, the small one (only on or off) on each time its
 * value's running sum reaches 256, which then drops by 255, so its value says how often it is on. */
void actuator_update(void)
{
    int words[4];
    ref_L00_002D6FD8_02(words);
    if (ref_L00_002D6FD8_01[2] != 0) {
        ref_L00_002D6FD8_00 += words[0];
        if (ref_L00_002D6FD8_00 >= 256) {
            ref_L00_002D6FD8_03.small_motor = 1;
            ref_L00_002D6FD8_00 -= 255;
        } else {
            ref_L00_002D6FD8_03.small_motor = 0;
        }
        ref_L00_002D6FD8_03.large_motor = ((unsigned char *)words)[4];
    } else {
        words[0] = 0;
        words[1] = 0;
    }
}


/* Clears one byte of each of the 32 64-byte records that end at the level pool root plus
   0x7DD, walking down one record at a time; the stored -1 is the function's return value. */
extern unsigned char g_cam_l00_override_slots[];
extern int g_cam_override_selected_slot;

/* Switches off all 32 camera override slots and marks that none is selected. */
int cam_clear_override_slots(void)
{
    unsigned char *slot = g_cam_l00_override_slots;
    int i;
    int no_selection = -1;

    slot += 0x7DD;
    for (i = 31; i >= 0; i--) {
        *slot = 0;
        slot -= 64;
    }
    g_cam_override_selected_slot = no_selection;
    return no_selection;
}

/* Partial 64-byte pool record, measured from the retail loads and stores. */
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    float f20;
    unsigned char f24;
    unsigned char f25;
    short f26;
    unsigned char f28;
    unsigned char f29;
    unsigned char f30;
    unsigned char f31;
    unsigned char pad32[16];
    short f48;
    short f50;
    int f52;
    int f56;
    int f60;
} PoolRecord64;

extern PoolRecord64 g_cam_l16_override_slots[];

/* Finds a free camera override slot, fills it with starting values and returns it, or returns 0 if all are used. */
PoolRecord64 *cam_alloc_override_slot(int kind)
{
    PoolRecord64 *slot = g_cam_l16_override_slots;
    int i;

    for (i = 0; i < 32; i++) {
        if (slot->f29 == 0) {
            slot->f0 = -1.0f;
            slot->f4 = -1.0f;
            slot->f8 = -1.0f;
            slot->f12 = -1.0f;
            slot->f16 = -1.0f;
            slot->f20 = -1.0f;
            slot->f28 = kind;
            slot->f52 = 6;
            slot->f50 = 120;
            slot->f29 = 1;
            slot->f56 = -1;
            slot->f24 = 0;
            slot->f25 = 0;
            slot->f26 = 0;
            slot->f30 = 0;
            slot->f31 = 0;
            slot->f60 = 0;
            slot->f48 = 0;
            return slot;
        }
        slot++;
    }
    return 0;
}

