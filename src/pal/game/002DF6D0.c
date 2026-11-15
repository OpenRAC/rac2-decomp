#include "include_asm.h"
#include "names.h"

typedef struct {
    char b[8];
} CdClock;
extern int sceCdReadClock(CdClock *);
extern void clock_to_local_time(unsigned char *);
extern void save_build_packet(int);
extern unsigned char D_001A7360[8] __attribute__((sda));
extern unsigned char g_memcard_state[];
extern void save_load_game_data_reset_menu(int, int);

void func_PAL_002DF6D0(int value, int mode)
{
    unsigned char *state;
    save_load_game_data_reset_menu(value, mode);
    sceCdReadClock((CdClock *)D_001A7360);
    clock_to_local_time(D_001A7360);
    save_build_packet(value);
    state = g_memcard_state;
    *(int *)(state + 0x148) = 0;
    *(short *)(state + 0x18) = mode;
    *(int *)(state + mode * 0x1C + 0x30) = 0;
    *(int *)(state + 0x174) = value;
    if (*(int *)(state + 0x164) < 0) {
        *(int *)(state + 0x168) = 0;
        *(int *)(state + 0x164) = 0x13;
    }
}


#include "common.h"
typedef struct {
    short f0;
    short f2;
    char pad4[8];
} Slot;
extern Slot D_0025EBD0[];
extern int D_001AB29C[4] MACRO_ADDR;
extern int D_001A7318 MACRO_ADDR;
extern int save_count_nonzero_flags(void);
extern int save_count_entries_above_threshold(void);

/* Unlock levels for the counts the player has collected. */
void func_PAL_002DFE20(void)
{
    int a = save_count_nonzero_flags() >= 15;
    int b = save_count_nonzero_flags() >= 30;
    int c = save_count_entries_above_threshold() >= 10;
    D_0025EBD0[5].f2 = a ? 3 : 2;
    D_0025EBD0[6].f2 = b ? 3 : 2;
    D_0025EBD0[7].f2 = c ? 10 : 2;
    D_0025EBD0[8].f2 = c ? 3 : 2;
    D_001AB29C[0] = a ? 0xC2F : 0xC35;
    D_001AB29C[1] = b ? 0xC30 : 0xC36;
    D_001AB29C[2] = c ? 0xC33 : 0xC37;
    D_001AB29C[3] = c ? 0xC34 : 0xC37;
    if (D_001A7318) D_0025EBD0[8].f0 = 0;
}

