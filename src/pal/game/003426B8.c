#include "include_asm.h"
#include "names.h"

/* func_PAL_003426B8, the PAL copy of func_00340638: the same C, where the fields at
   0xA18 and 0x870 move to 0xA78 and 0x880. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340498;
extern const Word2_340498 g_radial_info_shared_word_pair;
extern const Word2_340498 g_radial_info_second_word_pair_a;
extern const Word2_340498 g_radial_info_second_word_pair_b;
extern const Word2_340498 g_radial_info_second_word_pair_c;
extern const Word2_340498 g_info_word_pair_page;
extern char g_menu_item_table_second[];
extern char *g_resident_data_base __attribute__((sda));
extern void object_set_helper_result(void *, void *, int);
extern void DrawItemGrid(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void radial_menu_draw_info_second_pal(char *o)
{
    Word2_340498 q0 = g_radial_info_second_word_pair_a;
    Word2_340498 q1 = g_radial_info_second_word_pair_b;
    Word2_340498 q2 = g_radial_info_second_word_pair_a;
    Word2_340498 q3 = g_radial_info_second_word_pair_c;
    Word2_340498 q4 = g_radial_info_shared_word_pair;
    Word2_340498 q5 = g_info_word_pair_page;
    int f[23];
    char *child;
    initDescriptor_340498(f);
    f[19] = *(int *)(o + 0x820);
    f[21] = *(int *)(o + 0x81C) == 1;
    f[16] = (int)(o + 0xA78);
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    child = o + 0x17C;
    f[9] = (int)&q4;
    f[14] = 1;
    f[13] = 0;
    f[1] = 3;
    f[2] = 2;
    f[0] = (int)g_menu_item_table_second;
    f[17] = (int)(o + 0x880);
    object_set_helper_result(child, g_resident_data_base + 0x8710, 0x5D);
    f[10] = (int)child;
    f[12] = (int)(o + 0x214);
    f[15] = (int)(o + 0x7D0);
    f[8] = (int)&q3;
    f[7] = (int)&q2;
    f[11] = 0;
    f[18] = *(int *)(o + 0x80C);
    f[6] = (int)&q1;
    f[5] = (int)&q0;
    f[20] = (int)&q5;
    f[22] = 0;
    DrawItemGrid(f);
}
