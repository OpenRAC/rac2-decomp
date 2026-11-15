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
void save_menu_clear_flags_choose_screen(void)
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

extern unsigned int g_save_menu_flags[] __attribute__((sda));
extern int g_save_menu_screen[] __attribute__((sda));

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void save_menu_return_if_not_busy(void) {
    if ((g_save_menu_flags[0] & 0x40) == 0)
        g_save_menu_screen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void save_menu_return_if_not_busy_2(void) {
    if ((g_save_menu_flags[0] & 0x40) == 0)
        g_save_menu_screen[0] = 3;
}

extern int D_001393F0[];

/* Save menu screen step: goes to screen 3 when the first memory card reports a result. */
void save_menu_return_on_card_result(void) {
    if (D_001393F0[0] != 0)
        g_save_menu_screen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void save_menu_return_if_not_busy_3(void) {
    if ((g_save_menu_flags[0] & 0x40) == 0)
        g_save_menu_screen[0] = 3;
}

/* Save menu screen step: goes to screen 3 unless the busy flag is set. */
void save_menu_return_if_not_busy_4(void) {
    if ((g_save_menu_flags[0] & 0x40) == 0)
        g_save_menu_screen[0] = 3;
}

/* When the memory card is idle, moves the save menu to screen 21 if there is an error, or to screen 1 if everything is fine. */
void save_menu_choose_screen_after_check(void)
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

extern int g_memcard_state[];
extern int g_current_game_mode[] __attribute__((sda));
extern int ref_L00_00309C18_00 __attribute__((sda));
extern int request_begin_slot(int, int, unsigned int, unsigned int, unsigned char *);
extern void flag_set_word(void);
/* When the memory card is idle, decides if the save menu should show an error screen, start a save, or ask for confirmation. */
void save_menu_choose_screen_after_card_idle(void)
{
    int nextmode;
    int *state = g_memcard_state;
    if (state[0x15C / 4] == 2 && state[0x164 / 4] < 0) {
        int mode = state[0x16C / 4];
        if (mode != 0 || state[0x10 / 4] != 0) {
            state[0x17C / 4] = 0;
            if (mode != 0) {
                g_save_menu_screen[0] = 21;
                g_save_menu_flags[0] = 0x40;
                if (g_current_game_mode[0] == 0) {
                    request_begin_slot(4, 1, 1, 0, 0);
                    mode = ref_L00_00309C18_00;
                } else {
                    request_begin_slot(4, 2, 1, 0, 0);
                    mode = g_current_game_mode[0];
                }
                if (mode == 6) flag_set_word();
            } else {
                *(volatile int *)g_save_menu_flags = (*(int *)g_save_menu_flags & ~0x40) | 1;
            }
            nextmode = 2;
        } else {
            nextmode = 1;
            state[0x17C / 4] = nextmode;
        }
        g_save_menu_screen[0] = nextmode;
    }
}


/* Save menu screen step: goes to screen 3 unless the selection is -2; a button flag then sends it to screen 5. */
void save_menu_choose_screen_on_button_a(void)
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
void save_menu_choose_screen_on_button_b(void)
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
extern void strncpy(void *, int, int);
/* Builds the save file names from the game ID found in the source data and prepares the six name strings used for the memory card files. */
void save_build_file_names(unsigned char *source)
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
extern void MemcardRestoreData(char *, int, int *);
extern void save_reset_slot_ids(void);
extern void STUB_printf(void *);
extern int D_00256138[];
extern char D_00256368[];
extern int memcard_GetDataSize(int *);

/* Checks that a loaded save packet has the expected sizes, then restores the global block and the 28 slot blocks from it. Shows an error if the sizes do not match. */
void save_load_packet(int *packet)
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
    save_reset_slot_ids();
}


extern int D_00256138[];
extern char D_00256368[];
extern int memcard_GetDataSize(int *);
extern int save_pack_records(char *, int, int *);

/* Writes the save packet: the two block sizes, the global block and the 28 slot blocks. */
void save_build_packet(char *packet)
{
    char *out = packet;
    int i = 0;

    *(int *)(out + 0) = memcard_GetDataSize(D_00256138);
    *(int *)(out + 4) = memcard_GetDataSize((int *)D_00256368);
    out += 8;
    out += save_pack_records(out, 0, D_00256138);
    for (i = 0; i < 0x1C; i++) {
        out += save_pack_records(out, i, (int *)D_00256368);
    }
}

extern int func_00127348(void);
extern char D_001A9A28[];
extern void STUB_printf(void *);

/* Shows a memory card message when the card check reports a problem. */
void mc_show_message_on_problem(void) {
    if (func_00127348() != 0)
        STUB_printf(D_001A9A28);
}
