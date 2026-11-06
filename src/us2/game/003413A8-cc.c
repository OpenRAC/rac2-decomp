/* func_US2_003413A8, the USA v2.00 copy of func_00340498: the same C. */

typedef unsigned char u8;

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

extern ItemDefinition D_00239BA0[];
extern RecentSlot **D_001B18D4[] __attribute__((sda));

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);
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
extern void func_00336390(void *, void *, int);
extern void func_00337210(int *);

static __inline__ void initDescriptor_340498(int *f) { f[20] = 0; f[21] = 1; }

void func_US2_003413A8(char *o)
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
    func_00336390(child, D_001A8CFC + 0x8710, 0x23);
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
    func_00337210(f);
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
extern void func_003407F8(MenuState *, MenuEntry *, int);
/* Puts the selected entry's item in the next slot of a ring of eight, first clearing a slot
   that already holds it, and calls func_002E5E58 with 4. An item that is 0, has no flag in
   D_001A7AF8 or whose definition's label is 0xEA7E only calls it with 5. Either way the ring
   index at 0x7CC moves on, wrapping after 7. The global's first read falls in a branch slot,
   where the assembler makes it $gp-relative; its other reads are absolute macro loads. */
void func_003407F8(MenuState *self, MenuEntry *table, int columns);

/* Moves the selection of a menu's table: the buttons 0x1000 and 0x4000 move the page,
   0x8000 and 0x2000 the column and 0x40 asks for the entry's value, which is then kept
   in the state. The page moves compare against a variable, so that the compiler keeps
   the -1 in a register, as the retail code does. */
extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);
/* func_00340D68 is in 0033F030-grid-g8.c. */

/* Moves the selection of a menu grid and keeps the selected entry's value at
   0x214: the buttons 0x1000 and 0x4000 step the row (0x208, wrapping at the row
   count at 0x210), 0x8000 and 0x2000 the column (0x204, wrapping at 0x20C). A
   step down is stored, read back and stored again after the wrap test. */
/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
/* stores three consecutive words; byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
/* func_00341610 is in 0033F030-g8.c (it reaches small data through $gp). */

