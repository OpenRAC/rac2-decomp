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
extern void func_0027C540(long);

extern void func_0027C660(void);

unsigned long long func_002CD620(void);

extern void func_0029C1D8(void);

void func_0027C540(long);

void func_0027C660(void);

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

extern void func_0027C540(long arg0);

/* External functions declared with exact aliases from task.externals */
extern void func_0027C540(long param_1);

/* Draws one menu page: sets up the draw state, draws the page contents, and finishes. */
unsigned long long func_002CD620(void)
{
  SetupGifPaging(0);
  func_0029C1D8();
  DoGifPaging();
  return 0;
}

/* Does nothing and returns 0. */
int func_002CD650(void) {
    return 0;
}

/* Does nothing and returns 0. */
int func_002CD658(void) {
    return 0;
}

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;
extern CallbackState D_001F2840;
extern int D_00138344;

extern void func_0028BD68(void);
extern int func_0029CBE0(int);

/* Handles button input for a menu page: confirm picks the item (or fails if nothing is chosen), back closes the page. */
int func_002CD660(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value;
        SyncWeaponMenuSlots();
        value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
            result = -1;
            goto done;
        }
        result = 0;
done:
        ;
    } else if (flags & 0x900) {
        SyncWeaponMenuSlots();
        result = 1;
    } else {
        func_0029CBE0(flags);
    }
    return result;
}

extern void func_0029CC20(void);

/* Draws one menu page in a second style: sets up the draw state, draws the page contents, and finishes. */
int func_002CD6F0(void) {
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
extern int func_00336EF0(void);
extern int func_0029C480(int);

/* The same flag dispatch as func_002CD660 between two reads of func_00336EF0, then, when
   D_001A8CFC[0] is set, clears bit 2 of the word at D_0025E284 + 0x10 if the two reads agree,
   D_001A63AC is clear and the state at D_0025E2B8 matches one of its two modes, and sets it
   otherwise. The unit is built with -frac2-gcse-unsplit-edges (config/cflags.txt): the high
   half of D_0025E2B8 is computed once before the compare, as in retail. */
/* Handles button input for a menu page like the one above and also keeps the cursor highlight flag and cursor memory up to date. */
int func_002CD720(void) {
    int result = 0;
    int cursorBefore;
    int cursorAfter;
    int flags;
    int value;

    cursorBefore = GetUiSettingValue();
    flags = D_00138344;
    if (flags & 0x10) {
        value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
    cursorAfter = GetUiSettingValue();
    if (cursorBefore == cursorAfter && D_001A63AC == 0 &&
        ((D_0025E2B8.f50 == cursorBefore && D_0025E2B8.f44 == 2) ||
         (D_0025E2B8.f54 == cursorBefore && D_0025E2B8.f44 == 4)))
        *(int *)(D_0025E284 + 0x10) &= ~4;
    else
        *(int *)(D_0025E284 + 0x10) |= 4;
    if (cursorAfter != cursorBefore)
        D_0025E464 = -0x22C;
    D_0025E2B8.f58 = GetUiSettingValue();
    return result;
}

extern char *D_001A8CFC[] __attribute__((sda));
extern void *func_00344378(void *);

/* Points the object at the menu panel data, if a panel exists. */
int func_002CD878(char *object) {
    if (D_001A8CFC[0] != 0)
        *(void **)(object + 0x34) = GetGridMenuSelectedTextId(D_001A8CFC[0] + 0x39F38);
    return 0;
}
