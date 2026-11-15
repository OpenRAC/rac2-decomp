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

unsigned long long menu_draw_page_style_a(void);

extern void func_0029C1D8(void);

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

/* Draws one menu page: sets up the draw state, draws the page contents, and finishes. */
unsigned long long menu_draw_page_style_a(void)
{
  SetupGifPaging(0);
  func_0029C1D8();
  DoGifPaging();
  return 0;
}

/* Does nothing and returns 0. */
int menu_return_zero_callback_a(void) {
    return 0;
}

/* Does nothing and returns 0. */
int menu_return_zero_callback_b(void) {
    return 0;
}

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState g_pause_menu_state;
extern int D_00138344;

extern void weapon_menu_sync_slots(void);
extern int func_0029CBE0(int);

/* Handles button input for a menu page: confirm picks the item (or fails if nothing is chosen), back closes the page. */
int menu_handle_input_with_fallback(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value;
        weapon_menu_sync_slots();
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            result = -1;
            goto done;
        }
        result = 0;
done:
        ;
    } else if (flags & 0x900) {
        weapon_menu_sync_slots();
        result = 1;
    } else {
        func_0029CBE0(flags);
    }
    return result;
}

extern void func_0029CC20(void);

/* Draws one menu page in a second style: sets up the draw state, draws the page contents, and finishes. */
int menu_draw_page_style_b(void) {
    SetupGifPaging(0);
    func_0029CC20();
    DoGifPaging();
    return 0;
}

typedef struct {
    char pad0[0x44];
    int f44;
    char pad48[8];
    int f50;
    int f54;
    int f58;
} State_0025E2B8_002CD720;

extern State_0025E2B8_002CD720 D_0025E2B8;
extern char *D_0025E284;
extern int D_0025E464;
extern short D_001A63AC;
extern char *D_001A8CFC[] __attribute__((sda));
extern int menu_get_setting_value(void);
extern int func_0029C480(int);

/* The same flag dispatch as func_002CD660 between two reads of func_00336EF0, then, when
   D_001A8CFC[0] is set, clears bit 2 of the word at D_0025E284 + 0x10 if the two reads agree,
   D_001A63AC is clear and the state at D_0025E2B8 matches one of its two modes, and sets it
   otherwise. The unit is built with -frac2-gcse-unsplit-edges (config/cflags.txt): the high
   half of D_0025E2B8 is computed once before the compare, as in retail. */
/* Handles button input for a menu page like the one above and also keeps the cursor highlight flag and cursor memory up to date. */
int menu_handle_input_with_highlight(void) {
    int result = 0;
    int cursorBefore;
    int cursorAfter;
    int flags;
    int value;

    cursorBefore = menu_get_setting_value();
    flags = D_00138344;
    if (flags & 0x10) {
        value = *(int *)(g_pause_menu_state.source + 0xE0);
        if (value != 0)
            g_pause_menu_state.value = value;
        else if (g_pause_menu_state.fallback == 0) {
            result = -1;
            goto after_first;
        }
        result = 0;
    } else if (flags & 0x900) {
        result = 1;
    } else {
        func_0029C480(flags);
    }
after_first:
    if (D_001A8CFC[0] == 0)
        return result;
    cursorAfter = menu_get_setting_value();
    if (cursorBefore == cursorAfter && D_001A63AC == 0 &&
        ((D_0025E2B8.f50 == cursorBefore && D_0025E2B8.f44 == 2) ||
         (D_0025E2B8.f54 == cursorBefore && D_0025E2B8.f44 == 4)))
        *(int *)(D_0025E284 + 0x10) &= ~4;
    else
        *(int *)(D_0025E284 + 0x10) |= 4;
    if (cursorAfter != cursorBefore)
        D_0025E464 = -0x22C;
    D_0025E2B8.f58 = menu_get_setting_value();
    return result;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern int grid_menu_get_selected_text_id(void *);

/* Points the object at the menu panel data, if a panel exists. */
int menu_set_object_panel_pointer(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = grid_menu_get_selected_text_id(D_001A8CFC[0] + 0x39F38);
    return 0;
}
