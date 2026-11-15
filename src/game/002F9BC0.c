#include "ps2_hw.h"
#include "names.h"
#include "include_asm.h"

extern int func_00115DA8_1(char *, char *, ...);

extern char D_L00_001AD6B0[];

extern char D_L00_001AD6C0[];

extern char D_L00_001AD6C8[];

extern void Fbbb7bee1_FUN_00282A38(int value);

extern int D_L06_001B2F94 __attribute__((sda));

extern int D_L06_001B2F90 __attribute__((sda));

extern int D_L06_001A8F10 __attribute__((sda));

extern int D_L06_001B2F80[];

extern int D_L06_001B2F88_5 __attribute__((sda));

extern int D_L06_001B2370 __attribute__((sda));

extern int D_L06_001B2374 __attribute__((sda));

/* shared native body of family bc82131e */
/* Writes a number as text, with a space or comma between each group of three digits. */
void func_002F9BC0(char *dst, int value)
{
    if (value > 999999)
        func_00115DA8_1(dst, D_L00_001AD6B0, value / 1000000, (value / 1000) % 1000, value % 1000);
    else if (value >= 1000)
        func_00115DA8_1(dst, D_L00_001AD6C0, value / 1000, value % 1000);
    else
        func_00115DA8_1(dst, D_L00_001AD6C8, value);
}

/* func_002F9C80 is in 002F9C80.c. */

/* func_002FA270 is defined in 002FA270-ammo-g8.c. */

/* func_002FA880 is matched in 002F9BC0-vendor-g8.c. */



extern volatile int D_001A7A20[] __attribute__((sda));
extern void func_002FAD68(int);

/* Marks each special weapon bought this visit as owned in the shop list, then clears the
   flag that triggered it. */
void func_002FADB0(void)
{
    if (D_001A7A20[0] & 1) MarkShopItemOwned(12);
    if (D_001A7A20[0] & 2) MarkShopItemOwned(53);
    if (D_001A7A20[0] & 4) MarkShopItemOwned(17);
    if (D_001A7A20[0] & 8) MarkShopItemOwned(14);
    if (D_001A7A20[0] & 16) MarkShopItemOwned(18);
    D_001A7A20[0] &= ~128;
}


extern void func_002B7AD0(void);
extern int ref_L00_002FB170_00[];

/* Stops the shop preview and clears its two active flags. */
void func_002FB170(void) { RequestDiscReadBreak(); ref_L00_002FB170_00[0x23] = 0; ref_L00_002FB170_00[0x22] = 0; }


typedef struct { int key; int value; } Func002FBFB8Entry;
extern Func002FBFB8Entry D_00264F70[];

/* Looks up a key in the table and returns its matching value, or -1 if it is not there. */
int func_002FBFB8(int key)
{
    if (D_00264F70[0].key >= 0) {
        Func002FBFB8Entry *entry = D_00264F70;
        Func002FBFB8Entry *end = entry + 28;
        do {
            if (key == entry->key)
                return entry->value;
            entry++;
        } while (((int)entry < (int)end) & (entry->key >= 0));
    }
    return -1;
}


extern int func_002FBFB8(int);
extern unsigned char D_001395B8[];
/* Checks one bit of the save byte that belongs to a key; returns 1 if it is set. */
int func_002FC010(int key, int bit)
{
    int index = LookupTableValueByKey(key);
    if (index >= 0) {
        unsigned char value = D_001395B8[index] & (1 << bit);
        D_001395B8[index] = value;
        return value != 0;
    }
    return 0;
}

/* Starts a transfer on DMA channel 0 from the given list address and waits until it is done. */
void func_002FC070(int listAddress)
{
    while (((int)D0_CHCR) & 0x100)
        Fbbb7bee1_FUN_00282A38(16);
    D0_QWC = 0;
    D0_TADR = listAddress & 0x0FFFFFFF;
    D0_CHCR = 325;
    while (((int)D0_CHCR) & 0x100)
        Fbbb7bee1_FUN_00282A38(16);
}

/* func_002FC138 is matched in 002F9BC0-g8.c (-G8 small data). */

/* func_002FC190 is matched in 002F9BC0-g8.c (-G8 small data). */

/* func_002FC1D8 is matched in 002F9BC0-g8.c (-G8 small data). */

/* shared native body of family 74e6a904f3b4f71c (default profile) */
/* Switches to the other of the two packet buffers and works out where drawing into it starts. */
void func_002FC220(void)
{
    int nextBuffer;
    int target;
    int offset;
    int bufferStart;

    nextBuffer = 1 - D_L06_001B2F94;
    target = D_L06_001B2F90;
    offset = D_L06_001A8F10;
    D_L06_001B2F94 = nextBuffer;
    bufferStart = D_L06_001B2F80[nextBuffer];
    target = bufferStart + D_L06_001B2F90;
    D_L06_001B2F88_5 = bufferStart;
    target = target - offset;
    D_L06_001B2370 = target;
    D_L06_001B2374 = target - 8192;
}

/* func_002FC280 is matched in 002F9BC0-packet-g8.c. */
