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

extern u8 D_00188660[];
extern int D_001A7B98 __attribute__((sda));
extern int func_00131DE8(int);
extern void func_00132938(int);
extern void func_00132978(int, int);
extern void func_001329B0(int, int, int);
extern void func_002E4860(void);
extern void func_00132888(int, int);
extern void func_001328C0(int, int *);

#define SOUND ((SoundState_2E48E8 *)D_00188660)

/* Clears the sound state and sets the volume and channel options again. */
void func_002E48E8(void)
{
    int i;
    u8 *slot;
    int settings[5];

    for (i = 0; i < 4; i++)
        qzero(SOUND->blocks[i]);
    SOUND->field40 = 0;
    SOUND->field44 = 0;
    /* 52 slots of 0x70 bytes follow the header. */
    slot = gSoundState;
    do {
        *(int *)(slot + 0x70) = 0;
        slot[0x74] = 0;
        slot += 0x70;
    } while ((int)slot < (int)(gSoundState + 0x16C0));
    snd_StartSoundSystem(2);
    SendSoundCommand11_00132938(!D_001A7B98);
    func_00132978(0, 1);
    SendSoundCommand78(1, 24, 47);
    SendSoundCommand78(2, 24, 47);
    SendSoundCommand78(4, 24, 47);
    SendSoundCommand78(5, 24, 47);
    SendSoundCommand78(6, 24, 47);
    SetDefaultSoundGroupVolumes();
    SendSoundCommand9(0, SOUND->option[0]);
    SendSoundCommand9(1, SOUND->option[1]);
    SendSoundCommand9(2, SOUND->option[2]);
    SendSoundCommand9(3, SOUND->option[3]);
    SendSoundCommand9(4, SOUND->option[4]);
    SendSoundCommand9(5, SOUND->option[5]);
    SendSoundCommand9(6, SOUND->option[2]);
    settings[0] = 6;
    settings[1] = 59;
    settings[2] = 0x6666;
    settings[4] = settings[3] = 0x8000;
    SendSoundCommand96(0, settings);
}
