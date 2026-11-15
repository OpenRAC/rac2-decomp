#include "include_asm.h"
#include "names.h"

typedef struct { char prefix[0x14]; char *source; int value; char gap[0x118]; int fallback; } SelectionCallback;

typedef struct { char reserved[0x1C4]; int flags; } CallbackMenuState;

extern char *D_001A8CFC;

extern volatile unsigned char D_001A7A0A;

extern int ref_L00_002D1CB0_01;

extern int ref_L00_002D1CB0_02;

extern int ref_L00_002D1CB0_03 __attribute__((sda));

extern int ref_L00_002D1CB0_04;

extern int ref_L00_002D1CB0_05 __attribute__((sda));

extern int ref_L00_002D1CB0_06;

extern int ref_L00_002D1CB0_07 __attribute__((sda));

extern int ref_L00_002D1CB0_08 __attribute__((sda));

extern int D_00138344[];

extern int D_001ABA68 __attribute__((sda));

extern SelectionCallback g_pause_menu_state;

extern int D_0025CCE8[];

extern int snd_play_from_global_bank(int, unsigned int, void *);

extern CallbackMenuState g_pad_state;

extern int func_0029C560(int);

extern int func_0029C4F0(int);

extern char *tab_menu_get_selected_entry(void *);

extern void menu_start_action(int);

/* Turns on a few menu setting flags when the panel exists and the matching options are set. */
int menu_apply_setting_flags(void)
{
    if (D_001A8CFC != 0) {
        if (D_001A7A0A != 0) {
            *(volatile int *)&ref_L00_002D1CB0_01 = 1;
            *(volatile int *)&ref_L00_002D1CB0_02 = 1;
        }
        if (ref_L00_002D1CB0_03 != 0)
            *(volatile int *)&ref_L00_002D1CB0_04 = 1;
        if (ref_L00_002D1CB0_05 != 0)
            *(volatile int *)&ref_L00_002D1CB0_06 = 1;
        if (ref_L00_002D1CB0_07 != 0)
            ref_L00_002D1CB0_08 = 1;
    }
    return 0;
}

/* Handles input for a scrolling list of seven entries: up and down move the choice with a click sound, confirm and back leave. */
int menu_handle_scroll_list_input(void)
{
    int flags = D_00138344[0];
    int result = 0;
    if (flags & 0x10) {
        int value;
        int status;
        D_001ABA68 = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        D_001ABA68 = 0;
        result = 1;
    } else if (flags & 0x8000) {
        if (--D_001ABA68 >= 0)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (D_001ABA68 < 0)
            D_001ABA68 = 0;
    } else if (flags & 0x2000) {
        if (++D_001ABA68 < 7)
            snd_play_from_global_bank(3, 0, 0);
        else
            snd_play_from_global_bank(5, 0, 0);
        if (D_001ABA68 >= 7)
            D_001ABA68 = 6;
    }
    D_0025CCE8[0] = D_001ABA68;
    return result;
}

/* Handles menu input: confirm or back leave, otherwise it passes the buttons on and sends the chosen entry's key and value to the menu. */
int menu_handle_input_send_selection(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        int status;
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
    finish:
        return status;
    }
    if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C4F0(flags);
        if ((state->flags & 0x40) && D_001A8CFC != 0) {
            char *data = tab_menu_get_selected_entry(D_001A8CFC + 0x3BE08);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            menu_start_action((int)&message);
        }
    }
    return result;
}

/* Like the menu input above, but plays a refusal sound when the chosen entry has no value. */
int menu_handle_input_send_selection_or_refuse(void)
{
    struct { short reserved; unsigned short key; int value; } message;
    CallbackMenuState *state = &g_pad_state;
    int flags = state->flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        int status;
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C560(flags);
        if ((state->flags & 0x40) && D_001A8CFC != 0) {
            char *data = tab_menu_get_selected_entry(D_001A8CFC + 0x3BE08);
            message.key = *(unsigned short *)(data + 8);
            message.value = *(int *)(data + 0xC);
            if (message.value == 0)
                snd_play_from_global_bank(5, 0, 0);
            menu_start_action((int)&message);
        }
    }
    return result;
}

extern int D_001ABA28 __attribute__((sda));
extern unsigned char D_001ABA30[8] __attribute__((sda));
extern int D_001A7904 __attribute__((sda));
extern short D_001A63AC[];
extern void data_set_small_value_and_refresh(int, int);

typedef struct { char reserved00[0x10]; int flags; } FlagTarget;
typedef struct { char reserved00[0x44]; int f44; int f48; int f4c; int f50; int f54; int f58; } MenuFields;
extern FlagTarget *D_0025C540[];
extern MenuFields D_0025C580;
extern int D_0026CD20[];

/* Handles input for an eight entry menu: moves the choice, plays sounds, and starts the screen for the chosen entry if it is available. */
int menu_handle_eight_entry_input(void)
{
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    int flags = ((CallbackMenuState *)&g_pad_state)->flags;
    int old = D_001ABA28;
    int result = 0;

    if (flags & 0x10) {
        int value;
        int status;
        D_001ABA28 = 0;
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            status = -1;
            goto finish;
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        D_001ABA28 = 0;
        result = 1;
    } else {
        if (flags & 0x1000) {
            snd_play_from_global_bank(3, 0, 0);
            if (--D_001ABA28 < 0)
                D_001ABA28 = 7;
        } else if (flags & 0x4000) {
            snd_play_from_global_bank(3, 0, 0);
            if (++D_001ABA28 >= 8)
                D_001ABA28 = 0;
        }
        if (((CallbackMenuState *)&g_pad_state)->flags & 0x40) {
            if (D_001ABA30[D_001ABA28] != 0) {
                snd_play_from_global_bank(4, 0, 0);
                if ((unsigned)D_001ABA28 < 8)
                    goto *D_0026CD20[D_001ABA28];
                goto cont;
c0:            D_001A7904 = 2; data_set_small_value_and_refresh(2, 1); goto cont;
c1:            D_001A7904 = 3; data_set_small_value_and_refresh(4, 1); goto cont;
c2:            D_001A7904 = 3; data_set_small_value_and_refresh(11, 1); goto cont;
c3:            D_001A7904 = 2; data_set_small_value_and_refresh(11, 1); goto cont;
c4:            D_001A7904 = 1; data_set_small_value_and_refresh(26, 1); goto cont;
c5:            D_001A7904 = 1; data_set_small_value_and_refresh(22, 1); goto cont;
c6:            D_001A7904 = 1; data_set_small_value_and_refresh(23, 1); goto cont;
c7:            data_set_small_value_and_refresh(21, 1); goto cont;
            } else {
                snd_play_from_global_bank(5, 0, 0);
            }
        }
cont:
        {
            MenuFields *menu = &D_0025C580;
            menu->f58 = D_001ABA28;
            if (D_001ABA30[D_001ABA28] != 0) {
                if (old == D_001ABA28) {
                    if (D_001A63AC[0] == 0) {
                        if (menu->f50 == old && menu->f44 == 2) {
                            D_0025C540[0]->flags &= -5;
                        } else if (menu->f54 == old && menu->f44 == 4) {
                            D_0025C540[0]->flags &= -5;
                        }
                    }
                }
            } else {
                D_0025C540[0]->flags |= 4;
            }
        }
    }
    return result;
}
