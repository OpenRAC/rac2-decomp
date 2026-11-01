#include "include_asm.h"

extern void func_0033AF48_2();

extern void func_002DAF68_1();

extern void func_00336A78_5();

extern void func_00336828();

extern void func_00336320_4();

extern void func_0033ED88();

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

extern unsigned char D_001A7AF8[] __attribute__((sda));
extern unsigned char D_00139568[];
extern ItemDefinition D_00239BA0[];
extern RecentSlot **D_001B18D4[] __attribute__((sda));

/* Forwards one object pointer, eight pointer-plus-constant arguments and a null to ten calls in a fixed order. */
void func_0033F030(char *p)
{
    func_0033AF48_2(p + 8);
    func_002DAF68_1(0);
    func_00336A78_5(p + 744);
    func_00336A78_5(p + 816);
    func_00336A78_5(p + 888);
    func_00336828(p + 684);
    func_00336320_4(p + 960);
    func_00336A78_5(p + 1400);
    func_00336A78_5(p + 1328);
    func_0033ED88(p);
}

extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);
char *func_0033F0A0(char *object)
{
    char *cursor;
    int i;
    char *a, *b, *c, *d, *e, *g, *f;
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
    f = object + 0x948;
    a = object + 0x7D0;
    b = object + 0x828;
    g = object + 0x990;
    c = object + 0x870;
    d = object + 0x8B8;
    e = object + 0x900;
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



INCLUDE_ASM("asm/game", func_00340498);

INCLUDE_ASM("asm/game", func_00340638);

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
extern int func_002E5E58(int, unsigned int, void *);
extern void func_003407F8(MenuState *, MenuEntry *, int);
extern void *func_00115484(void *, int, unsigned int);
extern void func_00335E38(void *, float, float, float, float);

/* Puts the selected entry's item in the next slot of a ring of eight, first clearing a slot
   that already holds it, and calls func_002E5E58 with 4. An item that is 0, has no flag in
   D_001A7AF8 or whose definition's label is 0xEA7E only calls it with 5. Either way the ring
   index at 0x7CC moves on, wrapping after 7. The global's first read falls in a branch slot,
   where the assembler makes it $gp-relative; its other reads are absolute macro loads. */
void func_003407F8(MenuState *self, MenuEntry *table, int columns)
{
    int item = table[self->column + self->page * columns].value;

    if (item && D_001A7AF8[item] && (D_00139568[item] + D_00239BA0)->label != 0xEA7E) {
        int next = *(int *)((char *)self + 0x7CC) == 7 ? 0 : *(int *)((char *)self + 0x7CC) + 1;
        int i;
        for (i = 0; i < 8; i++) if ((*D_001B18D4[0])[i].item == item) break;
        if (i < 8) {
            RecentSlot **list = D_001B18D4[0];
            (*list)[i].item = 0;
            (*list)[i].label = (D_00139568[(*list)[i].item] + D_00239BA0)->label;
        }
        {
            RecentSlot **list = D_001B18D4[0];
            (*list)[next].label = (D_00139568[item] + D_00239BA0)->label;
            (*list)[next].item = item;
            (*list)[next].state = 0;
        }
        func_002E5E58(4, 0, 0);
    } else func_002E5E58(5, 0, 0);
    {
        int n = *(int *)((char *)self + 0x7CC) + 1;
        int limit = 7;
        *(int *)((char *)self + 0x7CC) = n > limit ? 0 : n;
    }
}

/* Moves the selection of a menu's table: the buttons 0x1000 and 0x4000 move the page,
   0x8000 and 0x2000 the column and 0x40 asks for the entry's value, which is then kept
   in the state. The page moves compare against a variable, so that the compiler keeps
   the -1 in a register, as the retail code does. */
void func_00340B70(MenuState *state, unsigned int buttons)
{
    if (buttons & 0x1000) {
        int v = state->page - 1;
        int lower = -1;
        v = (v > lower) ? v : 1;
        state->page = state->column ? v : 0;
        func_002E5E58(3, 0, 0);
    } else if (buttons & 0x4000) {
        int v = state->page + 1;
        v = (v > 1) ? 0 : v;
        state->page = state->column ? v : 0;
        func_002E5E58(3, 0, 0);
    } else if (buttons & 0x8000) {
        state->column = state->column - 1;
        func_002E5E58(3, 0, 0);
        if (state->column < 0 || (state->column == 0 && state->page == 1)) {
            state->column = 3;
            state->page += 4;
            state->flag = 0;
        }
    } else if (buttons & 0x2000) {
        state->column = state->column + 1;
        func_002E5E58(3, 0, 0);
        if (state->column >= 3) {
            state->column = 0;
            state->page += 4;
            state->flag = 0;
        }
    } else if (buttons & 0x40) {
        func_003407F8(state, D_001FCE0, 3);
    }
    state->value = D_001FCE0[state->column + 3 * state->page].value;
}

extern void *func_003361A8(void *);
extern char *func_00336968(char *);
extern void *func_003363D0(void *);
extern void *func_003366D0(void *);
u8 *func_00340D18(u8 *self)
{
    func_003361A8(self);
    func_003361A8(self + 76);
    func_00336968((char *)self + 152);
    func_003361A8(self + 224);
    func_003363D0(self + 300);
    func_003366D0(self + 372);
    return self;
}

/* func_00340D68 is in 0033F030-grid-g8.c. */

/* Moves the selection of a menu grid and keeps the selected entry's value at
   0x214: the buttons 0x1000 and 0x4000 step the row (0x208, wrapping at the row
   count at 0x210), 0x8000 and 0x2000 the column (0x204, wrapping at 0x20C). A
   step down is stored, read back and stored again after the wrap test. */
int func_00341030(char *self, unsigned int buttons, MenuEntry *table)
{
    float offset[2];
    func_00115484(offset, 0, 8);
    if (table) {
        float *position;
        *(int *)(self + 0x214) = 0;
        position = *(float **)(self + 0x1B0);
        func_00335E38(self, offset[0] + position[0], offset[1] + position[1], 0.0f, 0.0f);
        if (buttons & 0x1000) {
            int n;
            func_002E5E58(3, 0, 0);
            *(int *)(self + 0x208) -= 1;
            n = *(int *)(self + 0x208);
            if (n < 0) n = *(int *)(self + 0x210) - 1;
            *(int *)(self + 0x208) = n;
        } else if (buttons & 0x4000) {
            int n;
            func_002E5E58(3, 0, 0);
            n = *(int *)(self + 0x208) + 1;
            *(int *)(self + 0x208) = n < *(int *)(self + 0x210) ? n : 0;
        } else if (buttons & 0x8000) {
            int n;
            func_002E5E58(3, 0, 0);
            *(int *)(self + 0x204) -= 1;
            n = *(int *)(self + 0x204);
            if (n < 0) n = *(int *)(self + 0x20C) - 1;
            *(int *)(self + 0x204) = n;
        } else if (buttons & 0x2000) {
            int n;
            func_002E5E58(3, 0, 0);
            n = *(int *)(self + 0x204) + 1;
            *(int *)(self + 0x204) = n < *(int *)(self + 0x20C) ? n : 0;
        }
        *(int *)(self + 0x214) = table[*(int *)(self + 0x204) + *(int *)(self + 0x208) * *(int *)(self + 0x20C)].value;
    }
    return 0;
}

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_003411C0(u8 *a0) {
    func_L00_0042BAD0_6(a0);
    func_L00_0042BAD0_6(a0 + 76);
    func_L00_0042BAD0_6(a0 + 152);
    func_L00_0042BAD0_6(a0 + 228);
    func_L00_0042BAD0_6(a0 + 304);
    func_L00_0042BFF8_5(a0 + 380);
    func_L00_0042C290_6(a0 + 464);
    func_00347EA0_1(a0 + 552);
    return a0;
}


/* stores three consecutive words; byte-identical across all 27 levels. */
void func_00341540(u8 *a0, s32 a1, s32 a2, s32 a3) { *(s32 *)(a0 + 0x2F0) = a1; *(s32 *)(a0 + 0x2F4) = a2; *(s32 *)(a0 + 0x2F8) = a3; }

/* Measured target: byte-identical across all 27 levels. */
void func_00341550(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x220) = a1; }



/* func_00341610 is in 0033F030-g8.c (it reaches small data through $gp). */



void func_003417C8(void)
{
}
