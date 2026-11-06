/* func_US2_0033FF68, the USA v2.00 copy of func_0033F0A0: the same C, where swap locals *a *f. */

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
char *func_US2_0033FF68(char *object)
{
    char *cursor;
    int i;
    char *f, *b, *c, *d, *e, *g, *a;
    func_003361A8(object);
    func_003361A8(object + 0x4C);
    func_003361A8(object + 0x98);
    func_003361A8(object + 0xE4);
    func_003361A8(object + 0x130);
    func_003361A8(object + 0x17C);
    func_003361A8(object + 0x1C8);
    func_003361A8(object + 0x214);
    func_003363D0(object + 0x260);
    func_003361A8(object + 0x2A8);
    func_003361A8(object + 0x2F4);
    cursor = object + 0x340;
    for (i = 7; i != -1; i--, cursor += 0x4C) func_003361A8(cursor);
    func_003361A8(object + 0x5A0);
    cursor = object + 0x5EC;
    i = 7;
    f = object + 0x988;
    a = object + 0x7D0;
    b = object + 0x828;
    g = object + 0x9e0;
    c = object + 0x880;
    d = object + 0x8d8;
    e = object + 0x930;
    for (; i != -1; i--, cursor += 0x3C) func_003366D0(cursor);
    func_003366D0(a);
    func_00336968(b);
    func_00336968(c);
    func_00336968(d);
    func_00336968(e);
    func_00336968(f);
    func_00336968(g);
    return object;
}

/* func_0033F218 is in 0033F030-radial-g8.c. */

/* Fills func_00337210's 23-word descriptor in the order of func_00344F98, with the child at
   o + 0x17C set up by func_00336390 just before f[10] takes it. */
typedef struct { unsigned int lo; unsigned int hi; } Word2_340498;
extern const Word2_340498 D_001AE078;
extern const Word2_340498 D_001AE080;
extern const Word2_340498 D_001AE088;
extern const Word2_340498 D_001AE090;
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

