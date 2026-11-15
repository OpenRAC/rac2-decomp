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

extern void func_0029C7A0(void);

/* External functions declared with exact aliases from task.externals */
extern void SetupGifPaging(long param_1);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
unsigned long long menu_page_draw_3(void)
{
    SetupGifPaging(0);
    func_0029C7A0();
    DoGifPaging();
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

extern int func_0029C7D0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int menu_page_update_2(void) {
    int result = 0;
    int flags = D_00138344;
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
        func_0029C7D0(flags);
    return result;
}

extern void func_0029C810(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw_4(void) {
    SetupGifPaging(0);
    func_0029C810();
    DoGifPaging();
    return 0;
}

extern int func_0029CA00(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int menu_page_update_3(void) {
    int result = 0;
    int flags = D_00138344;
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
        func_0029CA00(flags);
    return result;
}

extern void func_0029CA40(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw_5(void) {
    SetupGifPaging(0);
    func_0029CA40();
    DoGifPaging();
    return 0;
}

extern int func_0029C990(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int menu_page_update_4(void) {
    int result = 0;
    int flags = D_00138344;
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
        func_0029C990(flags);
    return result;
}

extern void func_0029C9D0(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw_6(void) {
    SetupGifPaging(0);
    func_0029C9D0();
    DoGifPaging();
    return 0;
}

extern int func_0029C840(int);
extern int menu_process_request(short, int, int *);

/* Handles button input for a menu page and, when the page handler says so, sends a menu request message. */
int menu_page_update_send_request(void) {
    int result = 0;
    int flags = D_00138344;
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
    {
        int request;
        if (func_0029C840(flags)) {
            request = 0;
            menu_process_request(13, 0, &request);
        }
    }
    return result;
}



extern void func_0029C880(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw_7(void) {
    SetupGifPaging(0);
    func_0029C880();
    DoGifPaging();
    return 0;
}

extern int func_0029C8B0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int menu_page_update_5(void) {
    int result = 0;
    int flags = D_00138344;
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
