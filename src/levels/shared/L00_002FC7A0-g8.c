#include "include_asm.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_3e18d05650488ad4_FallbackU32;

extern Rac2Native_3e18d05650488ad4_FallbackU32 D_001A7424;

extern int D_001A7420_1;

extern int D_L00_001A904C;

extern void func_0028A2F8(int);

extern int D_L00_001A904C;

extern void func_0028A670(int);

void func_L00_0030DC30(int argument)
{
    if (D_L00_001A904C != 0) {
        func_0028A2F8(argument);
    }
}

void func_L00_0030DC58(int argument)
{
    if (D_L00_001A904C != 0) {
        func_0028A670(argument);
    }
}

struct LoadSlots_L00 {
    char pad00[0x34];
    int slot[4];
};

extern struct LoadSlots_L00 D_00152CD0;
extern int ref_L00_00304AE8_00 __attribute__((sda));

/* The level's copy of the load-slot release: same body as func_00294130 with the slot cursor in the level's small data. */
void func_L00_00304AE8(int *p, int a1)
{
    if (a1 != 0) {
        if (p[1] >= 0) {
            D_00152CD0.slot[p[1]] = p[0];
            if (p[1] != ref_L00_00304AE8_00)
                goto out;
            ref_L00_00304AE8_00 = p[1] ^ 1;
        }
    }
out:
    *p = -1;
}

typedef unsigned char u8;

typedef unsigned int u32;

/* A relocatable pointer block: `count` items whose `ptr` fields hold offsets from the block start. */
typedef struct RelocItem_00300378 {
    int pad00[3];
    int ptr;
} RelocItem_00300378;

typedef struct RelocBlock_00300378 {
    int count;
    int pad04[3];
    RelocItem_00300378 items[1];
} RelocBlock_00300378;

extern u32 D_L00_001BF200[4];

/* The same two pointers under two names: the stores of 0 are absolute `lui $at` stores in retail, the others $gp-relative. */
extern RelocBlock_00300378 *D_L00_001B1AC0 __attribute__((section(".sdata")));

extern RelocBlock_00300378 *D_L00_001B1AC0_1 __attribute__((sda));

extern RelocBlock_00300378 *D_L00_001B1AC4 __attribute__((section(".sdata")));

extern RelocBlock_00300378 *D_L00_001B1AC4_1 __attribute__((sda));

/* Publishes the three blocks a header's offsets select and relocates the second and third. */
void func_L00_00300378(u8 *a0)
{
    if (*(int *)(a0 + 0) != 0)
        D_L00_001BF200[0] = (u32)(a0 + *(int *)(a0 + 0));
    if (*(int *)(a0 + 4) != 0) {
        int i;

        D_L00_001B1AC0_1 = (RelocBlock_00300378 *)(a0 + *(int *)(a0 + 4));
        for (i = 0; i < D_L00_001B1AC0_1->count; i++)
            D_L00_001B1AC0_1->items[i].ptr = (int)D_L00_001B1AC0_1 + D_L00_001B1AC0_1->items[i].ptr;
    } else {
        D_L00_001B1AC0 = 0;
    }
    if (*(int *)(a0 + 8) != 0) {
        int i;

        D_L00_001B1AC4_1 = (RelocBlock_00300378 *)(a0 + *(int *)(a0 + 8));
        for (i = 0; i < D_L00_001B1AC4_1->count; i++)
            D_L00_001B1AC4_1->items[i].ptr = (int)D_L00_001B1AC4_1 + D_L00_001B1AC4_1->items[i].ptr;
    } else {
        D_L00_001B1AC4 = 0;
    }
}
