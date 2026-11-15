#include "include_asm.h"
#include "names.h"

extern unsigned int D_001A7AF0 __attribute__((sda));
extern int D_L05_002A1800[];

/* func_L05_003008C0 is defined in L05_003008C0-quad.c. */

/* func_L05_00302CE8 is defined in L05_00302CE8-g8.c. */

extern int func_002FEF40(int);

typedef struct L05Glyph L05Glyph;
extern int func_L05_00302CE8(int, int, int, int, unsigned long long, unsigned char *, int,
                             unsigned long long, L05Glyph *);

extern L05Glyph D_L05_002A2DB0[];

/* Word-wrapped text in a box with a fresh texture and the shared font; returns the height used. */
int func_L05_00303000(int x, int y, int width, int height, unsigned long long color,
                      unsigned char *text, int count)
{
    int step = func_002FEF40(2);

    return FontPrintWrapped(x, y, width, height, color, text, count, step, D_L05_002A2DB0);
}


extern int D_L05_00293D48[];

/* Stores the pair and steps the second half of the counter. */
/* Stores a pair of numbers in a shared block, adding one to the second. */
void func_L05_0030C930(int first, int second) {
    int *pair = D_L05_00293D48;
    pair[0x11] = second + 1;
    pair[0x10] = first;
}

/* func_L05_00324DB8 is defined in L05_003008C0-g8.c (this unit has no $gp access for it). */








/* func_L05_0033D3A0 is in L05_003008C0-reaction-g8.c. */




/* func_L05_00352B28 lives in L05_00352B28.c:
   its grouped vector copy and debug division labels need a per-file profile. */

/* Fills the slot table from the hero's equipment bits (the word func_002E6178 reads).
 * The table holds 15 entries of 0x28 bytes; each bit group sets the +0x00 and +0x18
 * words of a few entries; bits 7-8, 10-11 and 14-15 are read as two-bit fields. */
void func_L05_00379968(void)
{
    if (gEquipmentBits & 0x40) {
        D_L05_002A1800[0x158/4] = 1;
        D_L05_002A1800[0x140/4] = 1;
        D_L05_002A1800[0] = 0;
    } else {
        D_L05_002A1800[0] = 1;
        D_L05_002A1800[0x140/4] = 0;
    }
    {
        int *state = D_L05_002A1800;
        int flags;
        state[0x18/4] = 1;
        flags = gEquipmentBits;
        if (flags & 0x100) {
            state[0x1D0/4] = 1;
            state[0x90/4] = 1;
        } else if (flags & 0x80) {
            state[0x1D0/4] = 0;
            state[0x90/4] = 1;
        } else {
            state[0x1D0/4] = 0;
            state[0x90/4] = 0;
        }
    }
    {
        int *state = D_L05_002A1800;
        int flags = gEquipmentBits;
        state[0x78/4] = 0;
        state[0x1B8/4] = 0;
        if (flags & 0x200) {
            state[0x28/4] = 0;
            state[0x180/4] = 1;
            state[0x168/4] = 1;
        } else {
            state[0x168/4] = 0;
            state[0x28/4] = 1;
        }
    }
    {
        int *state = D_L05_002A1800;
        int flags;
        state[0x40/4] = 1;
        flags = gEquipmentBits;
        if (flags & 0x800) {
            state[0x1A8/4] = 1;
            state[0x68/4] = 1;
        } else if (flags & 0x400) {
            state[0x1A8/4] = 0;
            state[0x68/4] = 1;
        } else {
            state[0x1A8/4] = 0;
            state[0x68/4] = 0;
        }
    }
    {
        int *state = D_L05_002A1800;
        int flags = gEquipmentBits;
        state[0x50/4] = 0;
        state[0x190/4] = 0;
        if (flags & 0x1000) state[0xB8/4] = 1;
        else state[0xB8/4] = 0;
    }
    {
        int *state = D_L05_002A1800;
        int flags = gEquipmentBits;
        state[0xA0/4] = 0;
        if (flags & 0x2000) state[0xE0/4] = 1;
        else state[0xE0/4] = 0;
    }
    {
        int *state = D_L05_002A1800;
        int flags = gEquipmentBits;
        state[0xC8/4] = 0;
        if (flags & 0x8000) {
            state[0x1E0/4] = 0;
            state[0x230/4] = 1;
            state[0xF0/4] = 0;
            state[0x248/4] = 1;
            state[0x1F8/4] = 1;
        } else if (flags & 0x4000) {
            state[0x1E0/4] = 1;
            state[0x1F8/4] = 1;
            state[0xF0/4] = 0;
            state[0x248/4] = 0;
            state[0x230/4] = 0;
        } else {
            state[0xF0/4] = 1;
            state[0x230/4] = 0;
            state[0x1E0/4] = 0;
            state[0x248/4] = 0;
            state[0x1F8/4] = 0;
        }
    }
    {
        int *state = D_L05_002A1800;
        int flags;
        state[0x108/4] = 1;
        flags = gEquipmentBits;
        if (flags & 0x10) {
            state[0x118/4] = 0;
            state[0x220/4] = 1;
            state[0x208/4] = 1;
        } else {
            state[0x118/4] = 1;
            state[0x208/4] = 0;
        }
    }
    D_L05_002A1800[0x130/4] = 1;
}

/* func_L05_00379B60 is defined in L05_00379B60-g8.c. */

extern char *func_002ED688(int, int);

/* Finds an object's state and stores a value in it. */
void func_L05_00379C68(int objectId, int value) {
    char *state = GetMobyMotionData(objectId, value);
    if (state != 0)
        *(int *)(state + 0x150) = value;
}

extern int D_L05_00225DD0[];

/* Returns the live object list. */
int *func_L05_00379EB8(void) {
    return D_L05_00225DD0;
}

/* func_L05_00379ED0 is defined in L05_003008C0-g8.c (this unit has no $gp access for it). */

extern int D_L05_00221D10[];

/* Stores a value in the shared player state. */
void func_L05_00379F18(int value) {
    D_L05_00221D10[13] = value;
}

/* Stores a value in the shared player state. */
void func_L05_00379F28(int value) {
    D_L05_00221D10[15] = value;
}

/* Returns a value from the shared player state. */
int func_L05_00379F38(void) {
    return D_L05_00221D10[15];
}

/* Stores a value in the shared player state. */
void func_L05_00379F48(int value) {
    D_L05_00221D10[18] = value;
}

/* Returns a value from the shared player state. */
int func_L05_00379F58(void) {
    return D_L05_00221D10[18];
}

/* Clears a field in each of 128 records of the shared state. */
void func_L05_00379F68(void) {
    char *base = (char *)D_L05_00221D10 + 0xC0;
    int *entry = (int *)(base + 0x3FD0);
    int i = 0x7F;
    do {
        *entry = 0;
        entry -= 0x20;
        i--;
    } while (i >= 0);
}

/* func_L05_00379FA0 is defined in L05_00379FA0-qcopy.c. */

/* func_L05_0037A218 is defined in L05_0037A218-g8.c. */


typedef struct L05Slot40 {
    int state;      /* 0x00 */
    int next;       /* 0x04, the index the chain moves to */
    int pad08[2];
    int limit;      /* 0x10 */
    int value;      /* 0x14 */
    int pad18[4];
} L05Slot40;

extern L05Slot40 D_002A1800[];

extern int func_L05_0037AAC8(int index);


/* Takes a step off the stored value, never below zero. */
void func_L05_0037AB18(int index, int step)
{
    int slot = FindActiveSlotInChain(index);

    if (slot < 0)
        slot = func_L05_0037AAC8(index);
    D_002A1800[slot].value -= step;
    if (D_002A1800[slot].value <= 0)
        D_002A1800[slot].value = 0;
}

/* Adds a step to the stored value, never above the stored limit. */
void func_L05_0037AB88(int index, int step)
{
    int slot = FindActiveSlotInChain(index);

    if (slot < 0)
        slot = func_L05_0037AAC8(index);
    D_002A1800[slot].value += step;
    if (D_002A1800[slot].limit < D_002A1800[slot].value)
        D_002A1800[slot].value = D_002A1800[slot].limit;
}

/* func_L05_0037AC00 is matched in its own unit, src/levels/shared/L05_0037AC00.c (default flags). */

/* func_L05_0037AC40 is matched in its own unit, src/levels/shared/L05_0037AC40.c (default flags). */

/* func_L05_0037AC80 lives in L05_0037AC80.c:
   its state and damage flow are kept in a separate unit. */

/* Add an argument to the stored value and clamp it into [8, 15]. */
/* Adds to the stored value and keeps it between 8 and 15. */
void func_L05_0037ADD8(float amount)
{
    float *values = (float *)D_L05_00221D10;
    float total = values[12] + amount;
    float limit = 15.0f;

    values[12] = total;
    if (total > limit) {
        values[12] = limit;
    } else {
        limit = 8.0f;
        if (total < limit)
            values[12] = limit;
    }
}

/* Returns the stored value that is kept between 8 and 15. */
float func_L05_0037AE28(void) {
    return ((float *)D_L05_00221D10)[12];
}


extern char *func_L05_00379CA0(char *);

extern void func_L05_0037B838(char *);

/* Hand the object over, then clear its action state and step the shared counter. */
void func_L05_0037AE40(char *moby)
{
    char *state = func_L05_00379CA0(moby);

    if (state == 0)
        return;
    func_L05_0037B838(moby);
    *(unsigned short *)(moby + 0x32) = 0;
    *(unsigned short *)(moby + 0x34) = *(unsigned short *)(moby + 0x34) | 3;
    *(unsigned char *)(moby + 0x30) = 0;
    *(int *)(moby + 0x98) = 0;
    *(int *)(state + 0x110) = 0;
    if (D_L05_00221D10[4] != 0)
        D_L05_00221D10[4] = D_L05_00221D10[4] - 1;
}
