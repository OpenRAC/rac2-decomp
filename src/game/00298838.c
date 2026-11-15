#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout {
    unsigned char unknown_00[0x10];
    int selector_10;
    unsigned char unknown_14[0x168];
    int value_17c;
} Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout;

extern Rac2Native_60904fd170c92806_SDataMoreCleanup184Layout ref_L00_00309A30_00;

extern int ref_L00_00309A30_01;

extern int ref_L00_00309A30_02;

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout {
    unsigned char unknown_00[0x24];
    int word_24;
    unsigned char unknown_28[0x134];
    int mode_15c;
    unsigned char unknown_160[0x4];
    int selected_164;
    unsigned char unknown_168[0x4];
    int extra_16c;
    unsigned char unknown_170[0xc];
    int value_17c;
} Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout;

extern Rac2Native_8391b53329533f81_SDataGuardedFlags112Layout ref_L00_00309BA8_00;

extern unsigned int ref_L00_00309BA8_01;

extern int ref_L00_00309BA8_02;

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout;

extern Rac2Native_83cf4a65b6159c6c_SDataRootClear72Layout ref_L00_00309D20_01;

extern int ref_L00_00309D20_00;

extern int ref_L00_00309D20_02;

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_25b7bae55e05d925_SDataRootClear68Layout {
    unsigned char unknown_00[0x8];
    int mode_08;
    unsigned char unknown_0c[0x4];
    int selector_10;
} Rac2Native_25b7bae55e05d925_SDataRootClear68Layout;

extern Rac2Native_25b7bae55e05d925_SDataRootClear68Layout ref_L00_00309D68_01;

extern int ref_L00_00309D68_00;

extern int ref_L00_00309D68_02;

/* Save menu screen step: clears two flags, then moves to screen 21, 20, 3 or 1 depending on the other flags and the selection. */
void func_00298838(void)
{
    if ((ref_L00_00309A30_01 & 4) != 0)
        ref_L00_00309A30_01 &= ~4;
    if ((ref_L00_00309A30_01 & 2) != 0)
        ref_L00_00309A30_01 &= ~2;
    if ((ref_L00_00309A30_01 & 0x80) != 0) {
        ref_L00_00309A30_02 = 21;
        ref_L00_00309A30_01 = (ref_L00_00309A30_01 ^ 0x80) | 0x40;
        return;
    }
    if ((ref_L00_00309A30_01 & 0x100) != 0) {
        ref_L00_00309A30_02 = 20;
        ref_L00_00309A30_01 = (ref_L00_00309A30_01 ^ 0x100) | 0x40;
        return;
    }
    if (ref_L00_00309A30_00.selector_10 != 0) {
        ref_L00_00309A30_02 = 3;
        return;
    }
    if (ref_L00_00309A30_00.value_17c != 0)
        ref_L00_00309A30_02 = 1;
}

extern unsigned int D_001A7424[] __attribute__((sda));
extern int D_001A7420[] __attribute__((sda));

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void func_002988F0(void) {
    if ((gSaveMenuFlags[0] & 0x40) == 0)
        gSaveMenuScreen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void func_00298918(void) {
    if ((gSaveMenuFlags[0] & 0x40) == 0)
        gSaveMenuScreen[0] = 3;
}

extern int D_001393F0[];

/* Save menu screen step: goes to screen 3 when the first memory card reports a result. */
void func_00298940(void) {
    if (D_001393F0[0] != 0)
        gSaveMenuScreen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void func_00298960(void) {
    if ((gSaveMenuFlags[0] & 0x40) == 0)
        gSaveMenuScreen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void func_00298988(void) {
    if ((gSaveMenuFlags[0] & 0x40) == 0)
        gSaveMenuScreen[0] = 3;
}

/* When the memory card is idle, moves the save menu to screen 21 if there is an error, or to screen 1 if everything is fine. */
void func_002989B0(void)
{
    if (ref_L00_00309BA8_00.mode_15c != 2 || ref_L00_00309BA8_00.selected_164 >= 0)
        return;
    if (ref_L00_00309BA8_00.extra_16c != 0 || ref_L00_00309BA8_00.word_24 != 0) {
        ref_L00_00309BA8_00.value_17c = 0;
        ref_L00_00309BA8_02 = 21;
        ref_L00_00309BA8_01 |= 0x440u;
        return;
    }
    ref_L00_00309BA8_00.value_17c = 1;
    ref_L00_00309BA8_02 = 1;
}

extern int D_001393E0[];
extern int D_001A8BB0[] __attribute__((sda));
extern int ref_L00_00309C18_00 __attribute__((sda));
extern int func_002B49E0(int, int, unsigned int, unsigned int, unsigned char *);
extern void func_00288D70(void);
/* When the memory card is idle, decides if the save menu should show an error screen, start a save, or ask for confirmation. */
void func_00298A20(void)
{
    int nextmode;
    int *state = gMemcardState;
    if (state[0x15C / 4] == 2 && state[0x164 / 4] < 0) {
        int mode = state[0x16C / 4];
        if (mode != 0 || state[0x10 / 4] != 0) {
            state[0x17C / 4] = 0;
            if (mode != 0) {
                gSaveMenuScreen[0] = 21;
                gSaveMenuFlags[0] = 0x40;
                if (gCurrentGameMode[0] == 0) {
                    BeginSlotRequest(4, 1, 1, 0, 0);
                    mode = ref_L00_00309C18_00;
                } else {
                    BeginSlotRequest(4, 2, 1, 0, 0);
                    mode = gCurrentGameMode[0];
                }
                if (mode == 6) SetFlagWord();
            } else {
                *(volatile int *)gSaveMenuFlags = (*(int *)gSaveMenuFlags & ~0x40) | 1;
            }
            nextmode = 2;
        } else {
            nextmode = 1;
            state[0x17C / 4] = nextmode;
        }
        gSaveMenuScreen[0] = nextmode;
    }
}


/* Save menu screen step: goes to screen 3 unless the selection is -2; a button flag then sends it to screen 5. */
void func_00298B28(void)
{
    if (ref_L00_00309D20_01.selector_10 != -2) {
        ref_L00_00309D20_02 = 3;
        return;
    }
    if ((ref_L00_00309D20_00 & 0x20) != 0) {
        ref_L00_00309D20_00 ^= 0x20;
        ref_L00_00309D20_02 = 5;
    }
}

/* Save menu screen step: goes to screen 3 when something is selected; a button flag then sends it to screen 12. */
void func_00298B70(void)
{
    if (ref_L00_00309D68_01.selector_10 != 0) {
        ref_L00_00309D68_02 = 3;
        return;
    }
    if ((ref_L00_00309D68_00 & 0x20) != 0) {
        ref_L00_00309D68_00 ^= 0x20;
        ref_L00_00309D68_02 = 12;
    }
}

extern unsigned char D_001A7930[];
extern unsigned char D_001A7948[];
extern unsigned char D_001A7960[];
extern unsigned char D_001A7980[];
extern unsigned char D_001A79A0[];
extern unsigned char D_001A79D0[];
extern void func_00115AC0(void *, int, int);
/* Builds the save file names from the game ID found in the source data and prepares the six name strings used for the memory card files. */
void func_00298BB8(unsigned char *source)
{
    int i;
    int value = source[0x12];
    if (value == 0x45)
        D_001A7930[2] = value;
    else if (value == 0x50)
        D_001A7930[2] = 0x49;
    for (i = 3; i < 7; i++)
        D_001A7930[i] = source[i + 0xd];
    for (i = 8; i < 11; i++)
        D_001A7930[i] = source[i + 0xd];
    for (i = 11; i < 13; i++)
        D_001A7930[i] = source[i + 0xe];
    strncpy(D_001A7948, (int)D_001A7930, 13);
    strncpy(D_001A7960, (int)D_001A7930, 13);
    strncpy(D_001A7980, (int)D_001A7930, 13);
    strncpy(D_001A79A0, (int)D_001A7930, 13);
    strncpy(D_001A79A0 + 0x14, (int)D_001A7930, 13);
    strncpy(D_001A79D0, (int)D_001A7930, 13);
}

extern char D_001A9970[];
extern void func_0029B168(char *, int, int *);
extern void func_0029B628(void);
extern void func_0026FEB8(void *);
extern int D_00256138[];
extern char D_00256368[];
extern int func_0029AE78(int *);

/* Checks that a loaded save packet has the expected sizes, then restores the global block and the 28 slot blocks from it. Shows an error if the sizes do not match. */
void func_00298D28(int *packet)
{
    int len1 = memcard_GetDataSize(D_00256138);
    int len2 = memcard_GetDataSize((int *)D_00256368);
    int size = packet[0];
    int i;

    if (size != len1 || packet[1] != len2) {
        STUB_printf(D_001A9970);
        return;
    }
    packet = (int *)((char *)packet + 8);
    MemcardRestoreData((char *)packet, 0, D_00256138);
    packet = (int *)((char *)packet + size);
    for (i = 0; i < 0x1C; i++) {
        MemcardRestoreData((char *)packet, i, (int *)D_00256368);
        packet = (int *)((char *)packet + len2);
    }
    ResetSaveSlotIds();
}


extern int D_00256138[];
extern char D_00256368[];
extern int func_0029AE78(int *);
extern int func_0029AF98(char *, int, int *);

/* Writes the save packet: the two block sizes, the global block and the 28 slot blocks. */
void func_0029ADA0(char *packet)
{
    char *out = packet;
    int i = 0;

    *(int *)(out + 0) = memcard_GetDataSize(D_00256138);
    *(int *)(out + 4) = memcard_GetDataSize((int *)D_00256368);
    out += 8;
    out += PackSaveRecords(out, 0, D_00256138);
    for (i = 0; i < 0x1C; i++) {
        out += PackSaveRecords(out, i, (int *)D_00256368);
    }
}

extern int func_00127348(void);
extern char D_001A9A28[];
extern void func_0026FEB8(void *);

/* Shows a memory card message when the card check reports a problem. */
void func_0029AE48(void) {
    if (func_00127348() != 0)
        STUB_printf(D_001A9A28);
}
