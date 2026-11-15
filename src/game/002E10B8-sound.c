#include "common.h"

/* Resets the sound state at D_00188660 and reapplies its channel settings.
 * The four 16-byte blocks are cleared with the shared qzero helper, which is
 * why this function has a unit of its own (002E10B8.c defines its own types). */

typedef struct {
    u8 blocks[4][16];
    int field40;
    int field44;
    int option[6];
} SoundState_2E48E8;

extern u8 g_sound_state[];
extern int D_001A7B98 __attribute__((sda));
extern int snd_StartSoundSystem(int);
extern void snd_send_cmd11_one_value(int);
extern void func_00132978(int, int);
extern void snd_send_cmd78(int, int, int);
extern void snd_set_default_group_volumes(void);
extern void snd_send_cmd9(int, int);
extern void snd_send_cmd96_with_settings(int, int *);

#define SOUND ((SoundState_2E48E8 *)D_00188660)

/* Clears the sound state and sets the volume and channel options again. */
void ResetSoundState(void)
{
    int i;
    u8 *slot;
    int settings[5];

    for (i = 0; i < 4; i++)
        qzero(SOUND->blocks[i]);
    SOUND->field40 = 0;
    SOUND->field44 = 0;
    /* 52 slots of 0x70 bytes follow the header. */
    slot = g_sound_state;
    do {
        *(int *)(slot + 0x70) = 0;
        slot[0x74] = 0;
        slot += 0x70;
    } while ((int)slot < (int)(g_sound_state + 0x16C0));
    snd_StartSoundSystem(2);
    snd_send_cmd11_one_value(!D_001A7B98);
    func_00132978(0, 1);
    snd_send_cmd78(1, 24, 47);
    snd_send_cmd78(2, 24, 47);
    snd_send_cmd78(4, 24, 47);
    snd_send_cmd78(5, 24, 47);
    snd_send_cmd78(6, 24, 47);
    snd_set_default_group_volumes();
    snd_send_cmd9(0, SOUND->option[0]);
    snd_send_cmd9(1, SOUND->option[1]);
    snd_send_cmd9(2, SOUND->option[2]);
    snd_send_cmd9(3, SOUND->option[3]);
    snd_send_cmd9(4, SOUND->option[4]);
    snd_send_cmd9(5, SOUND->option[5]);
    snd_send_cmd9(6, SOUND->option[2]);
    settings[0] = 6;
    settings[1] = 59;
    settings[2] = 0x6666;
    settings[4] = settings[3] = 0x8000;
    snd_send_cmd96_with_settings(0, settings);
}
