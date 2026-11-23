#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

extern u8 D_00189E20_1[];

typedef struct { u8 prefix[0xaa]; short class_id; } ClassFilterObject;

typedef struct {
    u8 prefix[0x33c];
    ClassFilterObject *fallback;
    u8 middle[0x14f0];
    ClassFilterObject *primary;
    u8 trailing[0xa60];
    s32 mode;
} ClassFilterRoot;

typedef int BatchA_A07_s32;

extern BatchA_A07_s32 g_current_map_index[] __attribute__((sda));

extern s32 level_run_mode_update_three(void);

extern int D_0018C0B4_1;

typedef unsigned int u32;

extern u32 g_game_mode;

extern u8 g_wave_l24_channels[];

/* The controller's vibration (the pad actuators) is made of eight wave channels, which
 * LevelActuatorCalcPower (L00_002D67A8-envelope.c) mixes every frame. g_wave_l00_channels,
 * g_wave_l04_channels and g_wave_l24_channels are that one array, named by the address the code
 * forms in level 00, 04 and 24. The functions below start and stop waves in it. */

/* One wave of a vibration pattern, as the level program stores it: WaveChannel's fields, except
 * that PEAK is the highest level, where WaveChannel keeps AMPLITUDE (PEAK - BIAS). A KIND of 0xFF
 * ends the list. */
struct WaveRecord {
    unsigned char kind;
    unsigned char permanent;
    unsigned char output;
    unsigned char multiply;
    unsigned short delay;
    unsigned short duration;
    unsigned short frame;
    unsigned short rise;
    unsigned short fall;
    unsigned char peak;
    unsigned char bias;
};

/* A wave channel, as in L00_002D67A8-envelope.c. */
typedef struct {
    unsigned char kind, permanent, output, multiply;
    short delay, duration, frame, rise, fall;
    unsigned char amplitude, bias;
} WaveChannel;

extern WaveChannel g_wave_l04_channels[8] __attribute__((nosda));
extern WaveChannel g_wave_l00_channels[8];

/* Filter primary or fallback object's class identifier by mode and signed selection */
/* Checks if the tracked object is a certain kind of object, picked by the selection number. */
s32 level_is_tracked_object_of_selected_class(s32 selection) {
    s32 found = 0;
    ClassFilterObject *primary = ((ClassFilterRoot *)D_00189E20_1)->primary;
    ClassFilterObject *fallback = ((ClassFilterRoot *)D_00189E20_1)->fallback;
    if (((ClassFilterRoot *)D_00189E20_1)->mode == 0x31) {
        if (primary) {
            switch (selection) {
                case 0: found = primary->class_id == 0xfbf /* moby class 4031 */; break;
                case 1: found = primary->class_id == MOBY_CLASS_GLIDER; break;
                case 2: found = primary->class_id == MOBY_CLASS_MINING_VEHICLE; break;
            }
        } else if (fallback && selection == 3) {
            found = fallback->class_id == MOBY_CLASS_TURRET;
        }
    }
    return found;
}

/* A07-sda-multi-eq-44 freshly exact-verified under family reservation */
/* Tells whether a global value is one of three known numbers (0x16, 0x17 or 0x2CE). */
BatchA_A07_s32 level_is_special_global_value(void) {
    BatchA_A07_s32 value = g_current_map_index[0];
    return (value == 0x16) | (value == 0x2CE) | (value == 0x17);
}

/* Always answers 0 (a placeholder check that never passes). */
unsigned int level_return_zero(void)
{
    return 0;
}

/* Reads one global number and returns it. */
/* returns the resident 32-bit field at core address 0x0018c0b4 */
u32 level_get_global_word(void) {
    return g_game_mode;
}


/* The level's vibration patterns: 48 lists of waves (0 to 47), data in the level program. */
extern struct WaveRecord *g_actuator_patterns[];

int actuator_play_waves(struct WaveRecord *src);

/* Plays vibration pattern INDEX, a fixed rumble the game picks by number (18 when the hero is
 * hurt, for example). Returns what actuator_play_waves returns, or -1 when INDEX is 0x62 or more.
 * The table has only 48 patterns, so 48 to 0x61 would read past its end; no caller asks for one. */
int actuator_play_pattern(unsigned int index)
{
    if (index < 0x62)
        return actuator_play_waves(g_actuator_patterns[index]);
    return -1;
}

/* Stops every wave at once by clearing each channel's kind. The hero's set-action functions call
 * it on every change of action unless the hero's halfword at 0x1FA is set, so a new action
 * cuts off the rumble of the last one. */
void actuator_stop_all(void)
{
    s32 i;
    for (i = 7; i >= 0; --i)
        g_wave_l00_channels[i].kind = 0;
}

/* Tells whether wave channel INDEX is playing (its kind byte is not 0). */
s32 actuator_is_channel_active(s32 index) {
 return g_wave_l24_channels[index*16]!=0;
}

/* Starts a list of up to eight waves, each in a free channel. Plays nothing and returns -1 when
 * too few channels are free; otherwise returns the channel of the last wave, which callers keep
 * as a handle. A wave with no period (rise and fall both 0) gets a rise of 1, since the mixer
 * divides by it. */
int actuator_play_waves(struct WaveRecord *src)
{
    int n = 0;
    int i;
    int j;

    while (n < 8 && src[n].kind != 255)
        n++;

    j = 0;
    for (i = 0; i < 8 && j < n; i++) {
        if (g_wave_l04_channels[i].kind == 0)
            j++;
    }

    if (j != n)
        return -1;

    for (j = 0; j < n; j++) {
        i = 0;
        while (i < 8 && g_wave_l04_channels[i].kind != 0)
            i++;
        if (i < 8) {
            g_wave_l04_channels[i].kind = src[j].kind;
            g_wave_l04_channels[i].permanent = src[j].permanent;
            g_wave_l04_channels[i].output = src[j].output;
            g_wave_l04_channels[i].multiply = src[j].multiply;
            g_wave_l04_channels[i].delay = src[j].delay;
            g_wave_l04_channels[i].duration = src[j].duration;
            g_wave_l04_channels[i].frame = src[j].frame;
            g_wave_l04_channels[i].rise = src[j].rise;
            g_wave_l04_channels[i].fall = src[j].fall;
            g_wave_l04_channels[i].amplitude = src[j].peak - src[j].bias;
            g_wave_l04_channels[i].bias = src[j].bias;
            if (g_wave_l04_channels[i].rise + g_wave_l04_channels[i].fall == 0)
                g_wave_l04_channels[i].rise++;
        }
    }
    return i;
}

/* Ends every looping (permanent) wave: with no time left, the mixer stops it on its next frame.
 * Waves with a set duration play on. Callers pass the handle actuator_play_waves gave them, but
 * the function takes no argument and ends all looping waves. */
void actuator_end_looping_waves(void) {
    WaveChannel *slot = g_wave_l00_channels;
    s32 remaining = 7;
    do {
        if (slot->permanent) {
            slot->permanent = 0;
            slot->duration = 0;
        }
        --remaining;
        ++slot;
    } while (remaining >= 0);
}

/* func_L00_002D6BA8 is in L00_002D67A8-envelope.c (jump table). */
