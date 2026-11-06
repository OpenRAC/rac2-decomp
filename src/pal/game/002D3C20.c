#include "include_asm.h"
#include "common.h"

/* func_PAL_002D3C20, the PAL copy of func_002D2CE8: the same C, where D_001A7390 is scaled to 50 Hz in both maximum tests and their stores. */
extern unsigned int D_00138344;
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern char D_001F2840[];
typedef struct {
    char pad[0x1d4];
    unsigned short count;
    unsigned short unused;
    unsigned int maximum;
    unsigned int levels;
} Statistics_2D2CE8;
extern Statistics_2D2CE8 D_0018C750;
extern int func_PAL_0029D088(int);

int func_PAL_002D3C20(void)
{
    int result = 0;
    unsigned int flags = D_00138344;
    if (flags & 0x10) {
        Statistics_2D2CE8 *stats = &D_0018C750;
        char *root;
        int value, status;
        if (stats->count < 0xffff) stats->count++;
        if (((s32)D_001A7390 * 5 + 2) / 6 > stats->maximum) stats->maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        stats->levels = (stats->levels | (1u << D_001A79F0)) | 0x80000000u;
        root = D_001F2840;
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
        Statistics_2D2CE8 *stats = &D_0018C750;
        if (stats->count < 0xffff) stats->count++;
        if (((s32)D_001A7390 * 5 + 2) / 6 > stats->maximum) stats->maximum = ((s32)D_001A7390 * 5 + 2) / 6;
        stats->levels = (stats->levels | (1u << D_001A79F0)) | 0x80000000u;
        result = 1;
    } else func_PAL_0029D088(flags);
    return result;
}

extern void func_0027C540(long);
extern void func_PAL_0029D0C8(void);
extern void func_0027C660(void);

int func_PAL_002D3DB8(void)
{
  func_0027C540(0);
  func_PAL_0029D0C8();
  func_0027C660();
  return 0;
}

