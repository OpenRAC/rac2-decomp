#include "include_asm.h"
#include "names.h"

extern void func_0033AF48_2();

extern void func_002DAF68_1();

extern void func_00336A78_5();

extern void hud_draw_colored_quad_widget();

extern void func_00336320_4();

extern void info_panel_draw_counters();

typedef unsigned char u8;

extern void func_L00_0042BAD0_6(u8 *);

extern void func_L00_0042BFF8_5(u8 *);

extern void func_L00_0042C290_6(u8 *);

extern void func_00347EA0_1(u8 *);

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
extern const Word2_340498 D_001AE078;
extern const Word2_340498 D_001AE080;
extern const Word2_340498 D_001AE088;
extern const Word2_340498 D_001AE090;
extern char D_00259F58[];
extern char *D_001A8CFC __attribute__((sda));
extern void object_set_helper_result(void *, void *, int);
extern void DrawItemGrid(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void func_PAL_00342518(char *o)
{
    Word2_340498 q0 = D_001AE078;
    Word2_340498 q1 = D_001AE080;
    Word2_340498 q2 = D_001AE078;
    Word2_340498 q3 = D_001AE088;
    Word2_340498 q4 = D_001AE090;
    int f[23];
    char *child;

    initDescriptor_340498(f);
    f[19] = *(int *)(o + 0x820);
    f[21] = *(int *)(o + 0x81C) == 0;
    f[3] = *(int *)(o + 0x814);
    f[4] = *(int *)(o + 0x818);
    f[16] = (int)(o + 0xa78);
    f[9] = (int)&q4;
    f[1] = 4;
    f[2] = 6;
    f[0] = (int)D_00259F58;
    f[17] = (int)(o + 0x880);
    f[13] = (int)(o + 0x260);
    f[14] = 0;
    child = o + 0x17C;
    object_set_helper_result(child, D_001A8CFC + 0x8710, 0x23);
    f[10] = (int)child;
    f[12] = (int)(o + 0x214);
    f[11] = (int)(o + 0x98);
    f[15] = (int)(o + 0x7D0);
    f[18] = *(int *)(o + 0x80C);
    f[8] = (int)&q3;
    f[7] = (int)&q2;
    f[6] = (int)&q1;
    f[5] = (int)&q0;
    f[22] = 0;
    DrawItemGrid(f);
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