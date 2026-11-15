#include "include_asm.h"
#include "names.h"

/*
 * Disassembled at 0x002cd220
 * Signature: int FUN_002cd220(void)
 * Behavior:
 *   - Saves RA on stack
 *   - Calls func_0027C540(0)
 *   - Calls func_0029C138()
 *   - Calls func_0027C660()
 *   - Restores RA from stack
 *   - Returns 0
 */
extern void SetupGifPaging(long);

extern void DoGifPaging(void);

void SetupGifPaging(long);

void DoGifPaging(void);

/*
 * Function: func_002D2EE0
 *
 * Disassembly summary:
 * - Saves return address on stack
 * - Calls func_0027C540(0) (with zero argument)
 * - Calls func_0029C7A0()
 * - Calls func_0027C660()
 * - Restores return address
 * - Returns 0
 *
 * Notes:
 * - The function follows standard MIPS ABI prologue/epilogue.
 * - Delay slots are filled with NOP or argument setup as seen in disassembly.
 * - No local variables used.
 * - All external function addresses come from the assigned externals list.
 */

extern void SetupGifPaging(long arg0);

/* External functions declared with exact aliases from task.externals */
extern void SetupGifPaging(long param_1);

extern void func_0029C960(void);

extern char F7cb419c1_D_001F2840[];

extern int F7cb419c1_FUN_002DE618(int arg);

/* Candidate function: FUN_002d3390 */
/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
unsigned long long menu_page_draw_9(void)
{
    SetupGifPaging(0);
    func_0029C960();
    DoGifPaging();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern float ref_L00_002D33C0_00[];
extern void ref_L00_002D33C0_01(unsigned char *, float *);

/* Sets up the model preview helper object for the menu if the menu is open. */
int menu_preview_helper_init(void)
{
    if (D_001A8CFC[0] != 0)
        ref_L00_002D33C0_01((unsigned char *)(D_001A8CFC[0] + 0x3EDB8), ref_L00_002D33C0_00);
    return 0;
}

typedef struct {
    char reserved00[0x1C0];
    int message;
    int flags;
} MenuGameState;

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;

extern MenuGameState g_pad_state;
extern CallbackState g_pause_menu_state;
extern void func_0029C5D0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the current message to the page handler. */
int menu_page_update_pass_message(void)
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

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw_10(void) {
    SetupGifPaging(0);
    func_0029C5A0();
    DoGifPaging();
    return 0;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern void item_menu_set_title_mode(char *, int);
extern void item_menu_fill_list(char *, char *);
extern void item_menu_clear_selection_state(char *);
extern void item_menu_set_extra_value(char *, char *);
extern char D_00259F58[];
extern char D_0025D0E0[];

/* Sets up the first model preview object of the menu with its model data. */
int menu_preview_object_init_first(void)
{
    if (D_001A8CFC[0] != 0) {
        item_menu_set_title_mode(D_001A8CFC[0] + 0x3C108, 0);
        item_menu_fill_list(D_001A8CFC[0] + 0x3C108, D_00259F58);
        item_menu_clear_selection_state(D_001A8CFC[0] + 0x3C108);
        item_menu_set_extra_value(D_001A8CFC[0] + 0x3C108, D_0025D0E0);
    }
    return 0;
}

extern char D_00259CE0[];
extern char D_0025D288[];

/* Sets up the second model preview object of the menu with its model data. */
int menu_preview_object_init_second(void)
{
    if (D_001A8CFC[0] != 0) {
        item_menu_set_title_mode(D_001A8CFC[0] + 0x3C108, 1);
        item_menu_fill_list(D_001A8CFC[0] + 0x3C108, D_00259CE0);
        item_menu_clear_selection_state(D_001A8CFC[0] + 0x3C108);
        item_menu_set_extra_value(D_001A8CFC[0] + 0x3C108, D_0025D288);
    }
    return 0;
}



/* func_002D36A0 is in its -G8 sibling. */

extern int GetIconFrame(int, int);
extern double __extendsfdf2(float);
extern int __cmpdf2(double, double);
extern double __subdf3(double, double);
extern double __muldf3(double, double);
extern int __fixdfsi(double);
extern int hud_draw_sprite_gradient(int, int, int, int, int, int *);
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
} PreviewChoice;
extern PreviewChoice D_0026CFD0[];
extern int D_001B23A0[] __attribute__((sda));
extern float D_001B23A4[] __attribute__((sda));
/* A screen coordinate scaled for the display; mode 1 also takes an offset in unscaled pixels. */
static __inline__ int scaled_screen_coord(int mode, float value, float offset)
{
    float scaled = value * D_001B23A4[0] + 0.5f;
    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}
/* A size scaled for the display; any mode but 0 also takes a whole-pixel adjustment. */
static __inline__ int scaled_screen_size(int mode, float value, int adjust)
{
    if (mode != 0)
        return (int)(value * D_001B23A4[0] + 0.5f) + adjust;
    return (int)(value * D_001B23A4[0] + 0.5f);
}

/* Draws the icon of preview choice `index` at column `x`, fading its left and right edges by their
   distance from the middle of the 512-wide screen. */
int DrawPreviewChoiceIcon(int index, int x)
{
    int colors[4];
    int leftAlpha;
    int rightAlpha;
    int right;
    int texture;
    int y;
    int height;
    int left = x + 2;
    int baseColor = 0xf0f0b0;
    double distance;
    int mode;

    texture = GetIconFrame(0xea97, D_0026CFD0[index].icon);
    distance = __extendsfdf2(256.0f - (float)left);
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    leftAlpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    distance = __extendsfdf2(256.0f - (float)(x + 40));
    if (__cmpdf2(distance, 0.0) < 0)
        distance = __subdf3(0.0, distance);
    rightAlpha = 128 - __fixdfsi(__muldf3(distance, 0.75));
    if (leftAlpha < 0)
        leftAlpha = 0;
    if (rightAlpha < 0)
        right = 0;
    else
        right = rightAlpha;
    leftAlpha <<= 24;
    right <<= 24;
    colors[2] = colors[0] = leftAlpha | baseColor;
    colors[3] = colors[1] = right | baseColor;
    mode = D_001B23A0[0];
    y = scaled_screen_coord(mode, 334.0f, 4.0f);
    height = scaled_screen_size(mode, 40.0f, 0);
    return hud_draw_sprite_gradient(texture, left, y, 40, height, colors);
}

/* func_002D3FA0 is defined in 002D3FA0-options-g8.c. */

/* func_002D4948 is defined in 002D4948-options-g8.c. */

/* Updates the saved choice number in the menu state using a helper. */
int menu_update_choice_number(void)
{
    char *p = F7cb419c1_D_001F2840;

    *(int *)(p + 460) = F7cb419c1_FUN_002DE618(*(int *)(p + 460));
    return 0;
}

/* func_002D4E48 is in the -G8 sibling. */


extern int D_0025BA80;

/* Clears the menu counter back to zero. */
int menu_clear_counter_2(void) {
    D_0025BA80 = 0;
    return 0;
}



extern char *D_001A8CFC[] __attribute__((sda));
extern void *tab_menu_get_selected_value(void *);

/* Stores the preview object of the open menu into the given menu item. */
int menu_item_set_preview(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = tab_menu_get_selected_value(D_001A8CFC[0] + 0x3BE08);
    return 0;
}

/* func_002D52D8 is in the -G8 sibling. */

/* func_002D53F0 is defined in 002D53F0.c. */

extern void menu_clear_counter(void);
extern void tab_menu_set_tables(char *, char *, char *, char *);
extern void tab_menu_switch_tab(char *, int);
extern char D_002615F8[], D_00261698[], D_00261750[];

/* Sets up the preview object of the open menu with its data tables and turns it on. */
int menu_preview_data_init(void)
{
    menu_clear_counter();
    if (D_001A8CFC[0] != 0) {
        tab_menu_set_tables(D_001A8CFC[0] + 0x3BE08, D_002615F8, D_00261698, D_00261750);
        tab_menu_switch_tab(D_001A8CFC[0] + 0x3BE08, 1);
    }
    return 0;
}

extern int D_00138344;
extern void func_0029CF08(int);

/* Runs the common menu button handling with the current pressed buttons. */
int menu_handle_buttons(void) {
    func_0029CF08(D_00138344);
    return 0;
}

extern int D_00138344;
extern void func_0029CF08(int);

/* Runs the common menu button handling with the current pressed buttons. */
int menu_handle_buttons_alt(void) {
    func_0029CF08(D_00138344);
    return 0;
}
