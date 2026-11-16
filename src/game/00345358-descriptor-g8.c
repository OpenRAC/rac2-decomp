#include "names.h"
/* Build the menu descriptor, retaining its default initialization before overrides. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_462A8;

extern void DrawItemGrid(int *);

extern char g_menu_item_table_second[];

extern Word2_462A8 g_info_word_pair_page __attribute__((nosda));

extern int g_item_grid_page_desc_a __attribute__((sda));

extern int g_item_grid_page_desc_b __attribute__((sda));

extern int g_item_grid_page_desc_c __attribute__((sda));

extern int g_item_grid_page_desc_d __attribute__((sda));

extern int g_item_grid_page_desc_e __attribute__((sda));

extern int g_item_grid_page_desc_f __attribute__((sda));

extern int g_item_grid_page_desc_g __attribute__((sda));

static __inline__ void initDescriptor_462A8(int *f) { f[20] = 0; f[21] = 1; }

void item_grid_draw_page(char *menu)
{
    struct { Word2_462A8 q; int f[23] __attribute__((aligned(16))); } local;

    local.q = g_info_word_pair_page;

    initDescriptor_462A8(local.f);
    local.f[19] = *(int *)(menu + 0x494);
    local.f[21] = (*(int *)(menu + 0x498) == 0);
    local.f[3] = *(int *)(menu + 0x48C);
    local.f[4] = *(int *)(menu + 0x490);
    local.f[16] = (int)(menu + 0x448);
    local.f[9] = (int)&g_item_grid_page_desc_g;
    local.f[1] = g_item_grid_page_desc_a;
    local.f[2] = g_item_grid_page_desc_b;
    local.f[0] = (int)g_menu_item_table_second;
    local.f[17] = (int)(menu + 0x210);
    local.f[10] = (int)(menu + 0x130);
    local.f[12] = (int)(menu + 0x17C);
    local.f[15] = (int)(menu + 0x258);
    local.f[18] = *(int *)(menu + 0x400);
    local.f[8] = (int)&g_item_grid_page_desc_f;
    local.f[7] = (int)&g_item_grid_page_desc_e;
    local.f[6] = (int)&g_item_grid_page_desc_d;
    local.f[5] = (int)&g_item_grid_page_desc_c;
    local.f[14] = 0;
    local.f[11] = 0;
    local.f[13] = 0;
    local.f[20] = (int)&local.q;
    local.f[22] = 1;
    DrawItemGrid(local.f);
}
