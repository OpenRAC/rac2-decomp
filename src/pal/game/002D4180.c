#include "include_asm.h"
#include "names.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int g_menu_input_flags;
extern int func_0029C8B0(int);

/* Handles input for a menu page: confirms the selection, closes on a button press, otherwise passes the buttons on (PAL). */
int menu_page_update_5_pal(void) {
    int result = 0;
    int flags = g_menu_input_flags;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C8B0(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void DoGifPaging(void);
void SetupGifPaging(long);
void DoGifPaging(void);
extern void SetupGifPaging(long arg0);
extern void func_0029C8F0(void);
extern void SetupGifPaging(long param_1);

/* Implementation matching decompiled output */
/* Draws a menu page between the start and end of screen drawing (PAL). */
long menu_page_draw_8_pal(void)
{
  SetupGifPaging(0);
  func_0029C8F0();
  DoGifPaging();
  return 0;
}

extern void func_0029C960(void);

/* Candidate function: FUN_002d3390 */
/* Draws a menu page between the start and end of screen drawing (PAL). */
unsigned long long menu_page_draw_9_pal(void)
{
    SetupGifPaging(0);
    func_0029C960();
    DoGifPaging();
    return 0;
}

extern char *g_resident_data_base[] __attribute__((sda));
extern float ref_L00_002D33C0_00[];
extern void ref_L00_002D33C0_01(unsigned char *, float *);
extern char *g_resident_data_base[] __attribute__((sda));
extern char *g_resident_data_base[] __attribute__((sda));

/* Initialises the preview helper object once the resident data is loaded (PAL). */
int menu_preview_helper_init_pal(void)
{
    if (g_resident_data_base[0] != 0)
        ref_L00_002D33C0_01((unsigned char *)(g_resident_data_base[0] + 0x3F4A0), ref_L00_002D33C0_00);
    return 0;
}

typedef struct {
    char reserved00[0x1C0];
    int message;
    int flags;
} MenuGameState;
extern MenuGameState g_pad_state;
extern int func_0029C5D0(int);

/* Handles input for a menu page: confirms or closes, otherwise passes the buttons and message on (PAL). */
int menu_page_update_pass_message_pal(void)
{
    int flags = g_pad_state.flags;
    int result = 0;
    if (flags & 0x10) {
        int value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900)
        result = 1;
    else
        func_0029C5D0(g_pad_state.message);
    return result;
}

extern void func_0029C5A0(void);

/* Draws a menu page between the start and end of screen drawing (PAL). */
int menu_page_draw_10_pal(void) {
    SetupGifPaging(0);
    func_0029C5A0();
    DoGifPaging();
    return 0;
}

