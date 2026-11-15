#include "include_asm.h"
#include "names.h"

typedef unsigned int u32;

typedef int s32;

extern s32 D_L24_001B1B70[] __attribute__((sda));

extern u32 D_L24_001B1B74[] __attribute__((sda));

typedef unsigned char u8;

/* func_002DDEC8 is in 002DDEC8-g8.c (-G8 small data). */

/* func_002DE0D0 is in 002DDEC8-animation.c. */

/* The chunk table: a key and its flags, one pair per chunk. */
typedef struct {
    u32 key;
    u32 flags;
} Chunk;

extern int D_001B1F50[] __attribute__((sda));
extern s32 D_001F2840[];

/* Fills the chunk table at D_001B1F50 with (key, flags) pairs: the keys step
   by 0x11800 for the small chunks and by 0x4F000 for the large ones, and the
   flags say which. With a parameter it lays out four groups of chunks, without
   one only the first; the rest of the table is cleared. The retail function
   returns nothing, so it is void here (002D5E98.c declares it int and drops
   the result). */
void func_002DE3A0(s32 param)
{
    s32 *state = gPauseMenuState;
    u32 key1 = state[0x118 / 4];
    u32 key2 = state[0x11C / 4];
    s32 n1, n2, n3, n4;
    s32 idx, lim;

    if (!param) {
        n1 = 1;
        n2 = 0;
        n3 = 0;
        n4 = 0;
    } else {
        n1 = 2;
        n2 = 1;
        n3 = 2;
        n4 = 1;
    }
    idx = 0;
    lim = n1;
    while (idx < lim) {
        ((Chunk *)D_001B1F50)[idx].key = key1;
        ((Chunk *)D_001B1F50)[idx].flags = 0;
        key1 += 0x11800;
        idx++;
    }
    lim += n2;
    while (idx < lim) {
        ((Chunk *)D_001B1F50)[idx].key = key2;
        ((Chunk *)D_001B1F50)[idx].flags = 0;
        key2 += 0x11800;
        idx++;
    }
    lim += n3;
    while (idx < lim) {
        ((Chunk *)D_001B1F50)[idx].key = key1;
        ((Chunk *)D_001B1F50)[idx].flags = 1;
        key1 += 0x4F000;
        idx++;
    }
    lim += n4;
    while (idx < lim) {
        ((Chunk *)D_001B1F50)[idx].key = key2;
        ((Chunk *)D_001B1F50)[idx].flags = 1;
        key2 += 0x4F000;
        idx++;
    }
    while (idx < 5) {
        ((Chunk *)D_001B1F50)[idx].flags = 0;
        ((Chunk *)D_001B1F50)[idx].key = 0;
        idx++;
    }
}


extern void func_002B7AD0(void);

/* The chunk table again, as signed (key, flags) pairs indexed directly: read
   through a Chunk cast of the int array, the loop compiles to another shape. */
typedef struct {
    int key;
    int flags;
} ChunkSlot;
extern ChunkSlot D_001B1F50_slots[] __asm__("D_001B1F50") __attribute__((sda));

/* rac1-decomp src/game/pause.c: release_menu_stream_buffer */
/* Releases the chunk whose key matches. Bit 1 means taken; bit 2 on top of it
   means the chunk also holds the latch at byte 0xDB of D_001F2840, which is
   handed back through func_002B7AD0 first. Always returns 0. */
int func_002DE618(int key)
{
    int i;
    unsigned char *state;

    for (i = 0; i < 5; i++) {
        if (D_001B1F50_slots[i].key == key) {
            if ((D_001B1F50_slots[i].flags & 2) != 0) {
                if ((D_001B1F50_slots[i].flags & 4) != 0) {
                    state = (unsigned char *)gPauseMenuState;
                    D_001B1F50_slots[i].flags ^= 4;
                    if (state[0xDB] != 0) {
                        RequestDiscReadBreak();
                        state[0xDB] = 0;
                    }
                }
                D_001B1F50_slots[i].flags &= ~2;
                return 0;
            }
        }
    }
    return 0;
}

extern int D_001B1F50[] __attribute__((sda));
extern int D_001B1F54[] __attribute__((sda));

/* Finds the stream chunk with this key and returns its size (large or small), or -1 if there is none. */
int func_002DE6F0(int key)
{
    int count = 0;
    unsigned int large = 0x4F000;
    int *flags = D_001B1F54;
    int *keys = D_001B1F50;
    do {
        count++;
        if (*keys == key)
            return (*flags & 1) ? large : 0x11800;
        flags += 2;
        keys += 2;
    } while (count < 5);
    return -1;
}

/* authored C for independently verified level-native body */
/* Marks the stream chunk with this key as holding the latch. Returns 0 if found, 1 if not. */
s32 func_002DE750(s32 key) {
 s32 count=0;
 u32 *flags=D_L24_001B1B74;
 s32 *keys=D_L24_001B1B70;
 do {
  count++;
  if(*keys!=key) {flags+=2;keys+=2;continue;}
  *flags|=4;return 0;
 }while(count<5);
 return 1;
}

/* Clears the latch mark of the stream chunk with this key. Returns 0 if found, 1 if not. */
int func_002DE7A0(int key)
{
    int count = 0;
    int mask = -5;
    int *flags = D_001B1F54;
    int *keys = D_001B1F50;
    do {
        count++;
        if (*keys != key) {
            flags += 2;
            keys += 2;
            continue;
        }
        *flags &= mask;
        return 0;
    } while (count < 5);
    return 1;
}

/* Sets up a menu text box rectangle that covers the whole menu, with the text centred. */
void func_002DE810(unsigned short *box,u8 *menu) {
 box[0]=0;
 box[1]=*(unsigned short *)(menu+0x24);
 box[2]=0;
 box[3]=*(unsigned short *)(menu+0x20);
 box[4]=*(s32 *)(menu+0x20)>>1;
 box[5]=*(s32 *)(menu+0x24)>>1;
 box[8]=0x10;box[9]=0;
}


typedef struct {
    char b[8];
} CdClock;

extern int func_001256D8(CdClock *);
extern void func_00131A98(unsigned char *);
extern void func_002980D0(void);
extern void func_00297670(void *);
extern void func_0029ADA0(int);
extern unsigned char D_001A7360[8] __attribute__((sda));
extern unsigned char D_0018D278[];
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_001393E0[];
extern void func_00298E08(int, int);

/* Starts saving the game into a slot: stores the time, queues the save job and remembers which slot is used. */
void func_002DE858(int saveName, int slotIndex)
{
    unsigned char *state = gMemcardState;
    ReadCdClock((CdClock *)D_001A7360);
    ClockToLocalTime(D_001A7360);
    CopyMapBandColours();
    FillMapBuffer(D_0018D278 + (gCurrentMapIndex << 11));
    BuildSavePacket(saveName);
    *(int *)(state + 0x174) = saveName;
    *(short *)(state + 0x18) = slotIndex;
    *(int *)(state + 0x148) = 0;
    if (*(int *)(state + 0x164) < 0) {
        *(int *)(state + 0x168) = 0;
        *(int *)(state + 0x164) = 19;
    }
}

/* Clears the chosen slot, then starts saving the game into it. */
void func_002DE900(int saveName, int slotIndex)
{
    unsigned char *state;
    LoadGameDataAndResetSaveMenu(saveName, slotIndex);
    ReadCdClock((CdClock *)D_001A7360);
    ClockToLocalTime(D_001A7360);
    BuildSavePacket(saveName);
    state = gMemcardState;
    *(int *)(state + 0x148) = 0;
    *(short *)(state + 0x18) = slotIndex;
    *(int *)(state + slotIndex * 0x1C + 0x30) = 0;
    *(int *)(state + 0x174) = saveName;
    if (*(int *)(state + 0x164) < 0) {
        *(int *)(state + 0x168) = 0;
        *(int *)(state + 0x164) = 0x13;
    }
}



/* If scoring is switched on, adds an amount to the running total and passes it on. */
void func_002DF158(s32 object, s32 amount)
{
    extern s32 D_001F2840[];
    extern void func_002A0300(s32, s32);
    if (gPauseMenuState[0x168 / 4] != 0) {
        gPauseMenuState[0x16C / 4] += amount;
        UploadObjectTextures(object, amount);
    }
}

/* func_002DF190 is matched in 002DDEC8-g8.c (-G8 small data). */
