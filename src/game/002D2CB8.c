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

extern void func_0029C680(void);

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

/* Draws one menu page by calling its page-specific draw routine between the common start and end of menu drawing. */
int menu_page_draw(void)
{
    SetupGifPaging(0);
    func_0029C680();
    DoGifPaging();
    return 0;
}

extern unsigned int D_00138344;
extern unsigned int D_001A7390 __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern char g_pause_menu_state[];
typedef struct {
    char pad[0x1d4];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_2D2CE8;
extern Statistics_2D2CE8 g_progress_statistics;
extern int func_0029C6F0(int);

/* Handles button input for a menu page: counts the visit in the statistics and either accepts, cancels or passes the button to the page. */
int menu_page_update_count_stats(void)
{
    int result = 0;
    unsigned int flags = D_00138344;
    if (flags & 0x10) {
        Statistics_2D2CE8 *stats = &g_progress_statistics;
        char *root;
        int value, status;
        if (stats->count < 0xffff) stats->count++;
        if (D_001A7390 > stats->maximum) stats->maximum = D_001A7390;
        stats->levels = (stats->levels | (1u << g_current_map_index)) | 0x80000000u;
        root = g_pause_menu_state;
        value = *(int *)(*(char **)(root + 0x14) + 0xe0);
        if (value != 0) *(int *)(root + 0x18) = value;
        else {
            switch (*(int *)(root + 0x134)) {
            case 0: status = -1; goto finish;
            default: break;
            }
        }
        status = 0;
finish:
        return status;
    }
    if (flags & 0x900) {
        Statistics_2D2CE8 *stats = &g_progress_statistics;
        if (stats->count < 0xffff) stats->count++;
        if (D_001A7390 > stats->maximum) stats->maximum = D_001A7390;
        stats->levels = (stats->levels | (1u << g_current_map_index)) | 0x80000000u;
        result = 1;
    } else func_0029C6F0(flags);
    return result;
}
