#include "include_asm.h"
#include "names.h"

extern void func_0033AF48_2();

extern int func_002DAF68_1();

extern void func_00336A78_5();

extern void hud_draw_colored_quad_widget();

extern void func_00336320_4();

extern void info_panel_draw_counters();

typedef unsigned char u8;

extern char *func_L00_0042BAD0_6(u8 *);

extern char *func_L00_0042BFF8_5(u8 *);

extern char *func_L00_0042C290_6(u8 *);

extern unsigned long long func_00347EA0_1(u8 *);

typedef int s32;

/* a slot of a ring of eight chosen items: 0x1C bytes, the item's label first and the item last */
typedef struct {
    unsigned int label;
    int state;
    char reserved08[16];
    int item;
} RecentSlot;

/* an item's definition: 0xE0 bytes, the label at 0x3C */
typedef struct {
    char reserved00[0x3C];
    unsigned short label;
    char reserved3E[0xA2];
} ItemDefinition;

extern unsigned char g_item_owned_flags[] __attribute__((sda));
extern unsigned char g_item_slot_to_record[];
extern ItemDefinition g_weapon_table[];
extern RecentSlot **g_radial_menu_pages[] __attribute__((sda));

extern void *object_construct_derived_a(void *);
extern char *hud_construct_widget_base(char *);
extern void *object_construct_derived_b(void *);
extern void *object_construct_derived_c(void *);

/* func_0033F218 is in 0033F030-radial-g8.c. */



/* Fills func_00337210's 23-word descriptor in the order of func_00344F98, with the child at
   o + 0x17C set up by func_00336390 just before f[10] takes it. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340498;
extern const Word2_340498 g_radial_info_left_word_pair_a;
extern const Word2_340498 g_radial_info_left_word_pair_b;
extern const Word2_340498 g_radial_info_left_word_pair_c;
extern const Word2_340498 g_radial_info_shared_word_pair;
extern char g_menu_item_table_first[];
extern char *g_resident_data_base __attribute__((sda));
extern void object_set_helper_result(void *, void *, int);
extern void DrawItemGrid(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

/* Draws the left item grid of the radial menu by filling in a descriptor for DrawItemGrid (PAL: text widgets moved). */
void radial_menu_draw_info_left_pal(char *self)
{
    Word2_340498 pair_a = g_radial_info_left_word_pair_a;
    Word2_340498 pair_b = g_radial_info_left_word_pair_b;
    Word2_340498 pair_c = g_radial_info_left_word_pair_a;
    Word2_340498 pair_d = g_radial_info_left_word_pair_c;
    Word2_340498 pair_shared = g_radial_info_shared_word_pair;
    int desc[23];
    char *child;

    initDescriptor_340498(desc);
    desc[19] = *(int *)(self + 0x820);
    desc[21] = *(int *)(self + 0x81C) == 0;
    desc[3] = *(int *)(self + 0x814);
    desc[4] = *(int *)(self + 0x818);
    desc[16] = (int)(self + 0xa78);
    desc[9] = (int)&pair_shared;
    desc[1] = 4;
    desc[2] = 6;
    desc[0] = (int)g_menu_item_table_first;
    desc[17] = (int)(self + 0x880);
    desc[13] = (int)(self + 0x260);
    desc[14] = 0;
    child = self + 0x17C;
    object_set_helper_result(child, g_resident_data_base + 0x8710, 0x23);
    desc[10] = (int)child;
    desc[12] = (int)(self + 0x214);
    desc[11] = (int)(self + 0x98);
    desc[15] = (int)(self + 0x7D0);
    desc[18] = *(int *)(self + 0x80C);
    desc[8] = (int)&pair_d;
    desc[7] = (int)&pair_c;
    desc[6] = (int)&pair_b;
    desc[5] = (int)&pair_a;
    desc[22] = 0;
    DrawItemGrid(desc);
}




/* func_003407F8 follows the menu types below. */


/* a menu's table entry: ten bytes, the value a signed short at offset six */
typedef struct {
    char reserved00[6];
    short value;
    char reserved08[2];
} MenuEntry;

/* a menu's state: the selected entry's column and page, a flag and the entry's value */
typedef struct {
    char reserved00[0x814];
    int column;
    int page;
    int flag;
    int value;
} MenuState;

/* the table, in the memory a program replaces from 0x1A7C80 on: every program has
   its own copy of it at that address */
extern MenuEntry D_001FCE0[];
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void AddMenuItemToRing(MenuState *, MenuEntry *, int);
extern void *memset(void *, int, unsigned int);
extern void object_set_first_float4(void *, float, float, float, float);

extern void *object_construct_derived_a(void *);
extern char *hud_construct_widget_base(char *);
extern void *object_construct_derived_b(void *);
extern void *object_construct_derived_c(void *);