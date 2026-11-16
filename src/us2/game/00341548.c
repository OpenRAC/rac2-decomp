#include "include_asm.h"
#include "names.h"

/* func_US2_00341548, the USA v2.00 copy of func_00340638: the same C, where the fields at
   0x870 and 0xA18 move to 0x880 and 0xA78. */

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

static __inline__ void initDescriptor_340498(int *desc) { desc[20] = 0; desc[21] = 1; }

void radial_menu_draw_info_second_us2(char *menu)
{
    Word2_340498 q0 = g_radial_info_second_word_pair_a;
    Word2_340498 q1 = g_radial_info_second_word_pair_b;
    Word2_340498 q2 = g_radial_info_second_word_pair_a;
    Word2_340498 q3 = g_radial_info_second_word_pair_c;
    Word2_340498 q4 = g_radial_info_shared_word_pair;
    Word2_340498 q5 = g_info_word_pair_page;
    int desc[23];
    char *child;
    initDescriptor_340498(desc);
    desc[19] = *(int *)(menu + 0x820);
    desc[21] = *(int *)(menu + 0x81C) == 1;
    desc[16] = (int)(menu + 0xA78);
    desc[3] = *(int *)(menu + 0x814);
    desc[4] = *(int *)(menu + 0x818);
    child = menu + 0x17C;
    desc[9] = (int)&q4;
    desc[14] = 1;
    desc[13] = 0;
    desc[1] = 3;
    desc[2] = 2;
    desc[0] = (int)g_menu_item_table_second;
    desc[17] = (int)(menu + 0x880);
    object_set_helper_result(child, g_resident_data_base + 0x8710, 0x5D);
    desc[10] = (int)child;
    desc[12] = (int)(menu + 0x214);
    desc[15] = (int)(menu + 0x7D0);
    desc[8] = (int)&q3;
    desc[7] = (int)&q2;
    desc[11] = 0;
    desc[18] = *(int *)(menu + 0x80C);
    desc[6] = (int)&q1;
    desc[5] = (int)&q0;
    desc[20] = (int)&q5;
    desc[22] = 0;
    DrawItemGrid(desc);
}
