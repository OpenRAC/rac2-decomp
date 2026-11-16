#include "include_asm.h"
#include "names.h"

/* func_PAL_002D5A04, the PAL copy of func_002D4E48: the same C, where func_00300968 becomes the
   seven-argument func_00300A00 (1.0f added, 0.0f in a local), and strings 0x2D62, 0x2D4F become
   0xB73, 0xB60. Built with the flags of func_00300A00's other callers in 002D0568-rc2.c: without
   -fno-expensive-optimizations, 1.0f stays in $f21 across the calls instead of being reloaded. */
extern char *g_resident_data_base[] __attribute__((sda));
extern int g_popup_text_offset_x __attribute__((sda));
extern int g_popup_text_offset_y;
extern int g_popup_box_x __attribute__((sda));
extern int g_popup_box_y;
extern int g_popup_right_text_offset_x __attribute__((sda));
extern int g_popup_right_text_offset_y;
extern float g_menu_alpha_scale;
extern void SetupGifPaging(long);
extern void DoGifPaging(void);
extern void *table_find_by_id(int, int);
extern void gfx_draw_scaled_object_two_axes(char *, int, float, float, float, float, float);
extern char *GetLocalizedString(int);
extern int text_draw_centered_small(long long, long long, long long, char *, long long);
extern void text_draw_right_aligned_small(long long, long long, long long, char *, long long);

int menu_popup_box_draw_pal(void)
{
    float z;

    SetupGifPaging(0);
    if (g_resident_data_base[0] != 0) {
        z = 0.0f;
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base[0] + 0x8710, 0x96), 0x60442D00,
                      (float)g_popup_box_x, (float)g_popup_box_y, 1.0f, g_menu_alpha_scale, z);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base[0] + 0x8710, 0x97), 0x60241700,
                      (float)g_popup_box_x, (float)g_popup_box_y, 1.0f, g_menu_alpha_scale, z);
        gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base[0] + 0x8710, 0x98), 0x55F0C070,
                      (float)g_popup_box_x, (float)g_popup_box_y, 1.0f, g_menu_alpha_scale, z);
        text_draw_centered_small(g_popup_box_x + g_popup_text_offset_x, g_popup_box_y + g_popup_text_offset_y, 0x80F0F0F0,
                      GetLocalizedString(0xb73), -1);
        text_draw_right_aligned_small(g_popup_box_x + g_popup_right_text_offset_x, g_popup_box_y + g_popup_right_text_offset_y, 0x80F0F0F0,
                      GetLocalizedString(0xb60), -1);
    }
    DoGifPaging();
    return 0;
}
