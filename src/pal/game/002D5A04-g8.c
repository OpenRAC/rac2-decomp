#include "include_asm.h"
#include "names.h"

/* func_PAL_002D5A04, the PAL copy of func_002D4E48: the same C, where func_00300968 becomes the
   seven-argument func_00300A00 (1.0f added, 0.0f in a local), and strings 0x2D62, 0x2D4F become
   0xB73, 0xB60. Built with the flags of func_00300A00's other callers in 002D0568-rc2.c: without
   -fno-expensive-optimizations, 1.0f stays in $f21 across the calls instead of being reloaded. */
extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001ABA88 __attribute__((sda));
extern int D_001ABA8C;
extern int D_001ABA90 __attribute__((sda));
extern int D_001ABA94;
extern int D_001ABA98 __attribute__((sda));
extern int D_001ABA9C;
extern float D_001B23A8;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern int table_find_by_id(int, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern void text_draw_centered_small(long long, long long, long long, char *, long long);
extern void text_draw_right_aligned_small(long long, long long, long long, char *, long long);

int func_PAL_002D5A04(void)
{
    float z;

    SetupGifPaging(0);
    if (D_001A8CFC[0] != 0) {
        z = 0.0f;
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x96), 0x60442D00,
                      (float)D_001ABA90, (float)D_001ABA94, 1.0f, D_001B23A8, z);
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x97), 0x60241700,
                      (float)D_001ABA90, (float)D_001ABA94, 1.0f, D_001B23A8, z);
        gfx_draw_scaled_object_two_axes(table_find_by_id(D_001A8CFC[0] + 0x8710, 0x98), 0x55F0C070,
                      (float)D_001ABA90, (float)D_001ABA94, 1.0f, D_001B23A8, z);
        text_draw_centered_small(D_001ABA90 + D_001ABA88, D_001ABA94 + D_001ABA8C, 0x80F0F0F0,
                      GetLocalizedString(0xb73), -1);
        text_draw_right_aligned_small(D_001ABA90 + D_001ABA98, D_001ABA94 + D_001ABA9C, 0x80F0F0F0,
                      GetLocalizedString(0xb60), -1);
    }
    DoGifPaging();
    return 0;
}
