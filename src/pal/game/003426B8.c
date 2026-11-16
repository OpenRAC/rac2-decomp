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

/* Draws the second item grid of the radial menu by filling in a descriptor for DrawItemGrid (PAL). */
void radial_menu_draw_info_second_pal(char *self)
{
    Word2_340498 pair_a = g_radial_info_second_word_pair_a;
    Word2_340498 pair_b = g_radial_info_second_word_pair_b;
    Word2_340498 pair_c = g_radial_info_second_word_pair_a;
    Word2_340498 pair_d = g_radial_info_second_word_pair_c;
    Word2_340498 pair_shared = g_radial_info_shared_word_pair;
    Word2_340498 pair_page = g_info_word_pair_page;
    int desc[23];
    char *child;
    initDescriptor_340498(desc);
    desc[19] = *(int *)(self + 0x820);
    desc[21] = *(int *)(self + 0x81C) == 1;
    desc[16] = (int)(self + 0xA78);
    desc[3] = *(int *)(self + 0x814);
    desc[4] = *(int *)(self + 0x818);
    child = self + 0x17C;
    desc[9] = (int)&pair_shared;
    desc[14] = 1;
    desc[13] = 0;
    desc[1] = 3;
    desc[2] = 2;
    desc[0] = (int)g_menu_item_table_second;
    desc[17] = (int)(self + 0x880);
    object_set_helper_result(child, g_resident_data_base + 0x8710, 0x5D);
    desc[10] = (int)child;
    desc[12] = (int)(self + 0x214);
    desc[15] = (int)(self + 0x7D0);
    desc[8] = (int)&pair_d;
    desc[7] = (int)&pair_c;
    desc[11] = 0;
    desc[18] = *(int *)(self + 0x80C);
    desc[6] = (int)&pair_b;
    desc[5] = (int)&pair_a;
    desc[20] = (int)&pair_page;
    desc[22] = 0;
    DrawItemGrid(desc);
}
