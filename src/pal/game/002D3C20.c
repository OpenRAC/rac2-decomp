#include "include_asm.h"
#include "common.h"

/* func_PAL_002D3C20, the PAL copy of func_002D2CE8: the same C, where D_001A7390 is scaled to 50 Hz in both maximum tests and their stores. */
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
extern int func_PAL_0029D088(int);

int func_PAL_002D3C20(void)
{
    int result = 0;
    unsigned int flags = D_00138344;
    if (flags & 0x10) {
        Statistics_2D2CE8 *stats = &g_progress_statistics;
        char *root;
        int value, status;
        if (stats->count < 0xffff) stats->count++;
        if (((s32)D_001A7390 * 5 + 2) / 6 > stats->maximum) stats->maximum = ((s32)D_001A7390 * 5 + 2) / 6;
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
        if (((s32)D_001A7390 * 5 + 2) / 6 > stats->maximum) stats->maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        stats->levels = (stats->levels | (1u << g_current_map_index)) | 0x80000000u;
        result = 1;
    } else func_PAL_0029D088(flags);
    return result;
}

extern void SetupGifPaging(long);
extern void func_PAL_0029D0C8(void);
extern void DoGifPaging(void);

int func_PAL_002D3DB8(void)
{
  SetupGifPaging(0);
  func_PAL_0029D0C8();
  DoGifPaging();
  return 0;
}

