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

extern void func_0029C8F0(void);

/* External functions declared with exact aliases from task.externals */
extern void SetupGifPaging(long param_1);

/* Implementation matching decompiled output */
/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
long menu_page_draw_8(void)
{
  SetupGifPaging(0);
  func_0029C8F0();
  DoGifPaging();
  return 0;
}

extern int g_pad_state[];
extern char g_pause_menu_state[];
extern int D_001A8CFC __attribute__((sda));
extern int func_0029C920(int);
extern int list_page_get_selected_record(int);
extern void menu_start_action(int);

/* Handles button input for a menu page and, if the preview button is pressed, sends the selected entry as a menu message. */
int menu_page_update_with_preview(void)
{
    int result = 0;
    int *state = g_pad_state;
    int flags = state[0x1C4 / 4];
    if (flags & 0x10) {
        char *root = g_pause_menu_state;
        int value = *(int *)(*(char **)(root + 0x14) + 0xE0);
        int status;
        if (value != 0) {
            *(int *)(root + 0x18) = value;
        } else {
            switch (*(int *)(root + 0x134)) {
            case 0:
                status = -1;
                goto finish;
            default:
                break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900)
        result = 1;
    else {
        func_0029C920(flags);
        if ((state[0x1C4 / 4] & 0x40) && D_001A8CFC) {
            char *entry = (char *)list_page_get_selected_record(D_001A8CFC + 0x3EDB8);
            struct { short unused; unsigned short id; int value; } request;
            request.id = *(unsigned short *)(entry + 8);
            request.value = *(int *)(entry + 12);
            menu_start_action((int)&request);
        }
    }
    return result;
}
