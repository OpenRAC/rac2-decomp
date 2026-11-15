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

extern void func_0029C7A0(void);

/* External functions declared with exact aliases from task.externals */
extern void func_0027C540(long param_1);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
unsigned long long func_002D2EE0(void)
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
extern CallbackState D_001F2840;
extern int D_00138344;

extern void func_0029C7D0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int func_002D2F10(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
int func_002D2F98(void) {
    SetupGifPaging(0);
    func_0029C810();
    DoGifPaging();
    return 0;
}

extern void func_0029CA00(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int func_002D2FC8(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
int func_002D3050(void) {
    SetupGifPaging(0);
    func_0029CA40();
    DoGifPaging();
    return 0;
}

extern void func_0029C990(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int func_002D3080(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
int func_002D3108(void) {
    SetupGifPaging(0);
    func_0029C9D0();
    DoGifPaging();
    return 0;
}

extern int func_0029C840(int);
extern void func_002D5B58(short, int, int *);

/* Handles button input for a menu page and, when the page handler says so, sends a menu request message. */
int func_002D3138(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
            ProcessMenuRequest(13, 0, &request);
        }
    }
    return result;
}



extern void func_0029C880(void);

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int func_002D31D8(void) {
    SetupGifPaging(0);
    func_0029C880();
    DoGifPaging();
    return 0;
}

extern void func_0029C8B0(int);

/* Handles button input for a menu page: reports cancel or accept, and otherwise passes the buttons to the page handler. */
int func_002D3208(void) {
    int result = 0;
    int flags = D_00138344;
    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
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
