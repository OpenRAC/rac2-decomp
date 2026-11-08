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
    slot = D_00188660;
    do {
        *(int *)(slot + 0x70) = 0;
        slot[0x74] = 0;
        slot += 0x70;
    } while ((int)slot < (int)(D_00188660 + 0x16C0));
    func_00131DE8(2);
    func_00132938(!D_001A7B98);
    func_00132978(0, 1);
    func_001329B0(1, 24, 47);
    func_001329B0(2, 24, 47);
    func_001329B0(4, 24, 47);
    func_001329B0(5, 24, 47);
    func_001329B0(6, 24, 47);
    func_002E4860();
    func_00132888(0, SOUND->option[0]);
    func_00132888(1, SOUND->option[1]);
    func_00132888(2, SOUND->option[2]);
    func_00132888(3, SOUND->option[3]);
    func_00132888(4, SOUND->option[4]);
    func_00132888(5, SOUND->option[5]);
    func_00132888(6, SOUND->option[2]);
    settings[0] = 6;
    settings[1] = 59;
    settings[2] = 0x6666;
    settings[4] = settings[3] = 0x8000;
    func_001328C0(0, settings);
}
