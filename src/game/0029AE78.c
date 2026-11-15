#include "include_asm.h"
#include "names.h"

typedef struct {
    int first, second, third, fourth;
    char stamp[8];
    int invalid;
} SaveInfoEntry;

typedef struct {
    char header[0x30];
    SaveInfoEntry entries[4];
} SaveInfoSlot;

extern SaveInfoSlot D_001393E0[];
extern void *memcpy(void *, const void *, unsigned int);

typedef int s32;

extern void F2d5993bb_FUN_00282A60(char *p, int a1, int a2);

extern void F2d5993bb_FUN_00282AB0(char *p, int a1, int a2);

extern int F2d5993bb_FUN_0029AEB0(char *p, int a1);

typedef int BatchA_A08_s32;

extern BatchA_A08_s32 D_L00_001A904C[] __attribute__((sda));

extern int D_L00_001A904C_6 __attribute__((sda));

extern void func_003380B0(int *p, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9, int a10);

/* Works out how many bytes the save data needs by walking a list of records, with each one padded to 4 bytes. */
s32 func_0029AE78(s32 *records) {
 s32 size=8;
 while(records[0]!=0) {
  size+=8; size+=records[1]; size=(size+3)&-4;
  records+=4;
 }
 return size+8;
}

extern int D_00256138[];

/* Makes a 16-bit checksum of a block of save data. Returns 0 if the block is too long. */
int func_0029AEB0(char *data, int length)
{
    char *end;
    unsigned int crc;
    if (memcard_GetDataSize(D_00256138) < length)
        return 0;
    end = data + length;
    crc = 0xEDB88320;
    while (data < end) {
        int bit;
        char *next = data + 1;
        crc ^= (unsigned char)*data << 8;
        for (bit = 7; bit >= 0; bit--) {
            if (crc & 0x8000)
                crc = (crc << 1) ^ 0x1F45;
            else
                crc <<= 1;
        }
        data = next;
    }
    return crc & 0xFFFF;
}

/* Checks that a save block matches the checksum stored in its header. */
int func_0029AF58(char *block)
{
    extern int func_0029AEB0(char *, int);
    int storedChecksum = *(int *)(block + 4);
    int length = *(int *)block;
    int result = 0;
    if (storedChecksum != 0)
        result = ComputeSaveChecksum(block + 8, length) == storedChecksum;
    return result;
}

/* Packs all the save records into one buffer and adds the end marker and checksum. Returns the total size. */
int func_0029AF98(char *saveBuf, int slotIndex, int *records)
{
    int size = 0;
    char *dst = saveBuf + 8;
    char *rec;
    int srcOffset;
    int recSize;

    if (*(int *)records != 0) {
        rec = (char *)records;
        do {
            size += 8;
            srcOffset = *(int *)(rec + 0) + slotIndex * *(int *)(rec + 4);
            *(int *)(dst + 0) = *(int *)(rec + 8);
            *(int *)(dst + 4) = *(int *)(rec + 4);
            dst += 8;
            if (*(int *)(rec + 8) == 6000)
                F2d5993bb_FUN_00282A60(dst, 0, *(int *)(rec + 4));
            else
                F2d5993bb_FUN_00282AB0(dst, srcOffset, *(int *)(rec + 4));
            recSize = *(int *)(rec + 4);
            rec += 16;
            dst += recSize;
            size += recSize;
            dst = (char *)(((int)dst + 3) & ~3);
            size = (size + 3) & ~3;
        } while (*(int *)rec != 0);
    }
    size += 8;
    *(int *)(dst + 4) = 0;
    *(int *)(dst + 0) = -1;
    srcOffset = F2d5993bb_FUN_0029AEB0(saveBuf + 8, size);
    *(int *)(saveBuf + 4) = srcOffset;
    *(int *)(saveBuf + 0) = size;
    return size + 8;
}

/* Reads one save-slot header from memory-card data into the slot info table and marks it bad if the checksum fails. */
/* Slot indexing follows RAC1 memcard_RestoreInfo (src/game/memcard.c). */
void func_0029B0B0(char *src, int slot, int entry)
{
    gMemcardState[slot].entries[entry].invalid = VerifySaveBlockChecksum(src) == 0;
    src += 0x10;
    gMemcardState[slot].entries[entry].first = *(int *)src;
    src += 0xC;
    gMemcardState[slot].entries[entry].second = *(int *)src;
    gMemcardState[slot].entries[entry].third = *(unsigned char *)(src + 0x12);
    src += 0x48;
    gMemcardState[slot].entries[entry].fourth = *(int *)src;
    memcpy(gMemcardState[slot].entries[entry].stamp, src + 0xC, 8);
}






/* The existing implementation is in 0029B658-rc2.c. */

extern char *D_001A8CFC[] __attribute__((sda));
extern void func_0034CE28(void *, int);

/* Passes a value on to the level object, if one is loaded. */
void func_0029B698(int value) {
    if (D_001A8CFC[0] != 0)
        SetScreenValueAndRestartFourFades(D_001A8CFC[0] + 0x376C8, value);
}

extern void func_0034CAE8(void *, int, int);

/* Passes two values on to the level object, if one is loaded. */
void func_0029B6D0(int first, int second) {
    if (D_001A8CFC[0] != 0)
        SetScreenValueAndRestartFades(D_001A8CFC[0] + 0x376C8, first, second);
}


extern void func_0034B000(void *, int);

/* Passes a value on to another part of the level object, if one is loaded. */
void func_0029B720(int value) {
    if (D_001A8CFC[0] != 0)
        SetMenuFlagAndRestartFades(D_001A8CFC[0] + 0x37EB0, value);
}

/* A08-sda-offset-40 freshly exact-verified under family reservation */
/* Stores two values in the level object, if one is loaded. */
void func_0029B758(BatchA_A08_s32 first, BatchA_A08_s32 second) {
    BatchA_A08_s32 base = D_L00_001A904C[0];
    BatchA_A08_s32 *values;
    if (base == 0) return;
    values = (BatchA_A08_s32 *)(base + 0x38000);
    values[0x7368/4] = first;
    values[0x736C/4] = second;
}

/* Returns 1 if either of the two stored level values is non-zero. */
int func_0029B780(void) {
    int base = D_L00_001A904C[0];
    if (base != 0) {
        int *state = (int *)(base + 0x38000);
        if (state[0x7368 / 4] != 0 || state[0x736C / 4] != 0)
            return 1;
    }
    return 0;
}



extern void func_0034E4B8(void *);

/* Runs the level object update routine, if a level object is loaded. */
void func_0029B858(void) {
    if (D_001A8CFC[0] != 0)
        UpdateHudSubobjectAt1D6C(D_001A8CFC[0] + 0x36F28);
}

/* Loads a 32-bit global pointer from a fixed data address; if non-null, tail-forwards it (offset by 0x36F28) plus ten incoming arguments to an overlay-local callee. */
void func_0029B888(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
    int value = D_L00_001A904C_6;

    if (value != 0)
        DrawTextInFramedBox((int *)(value + 0x36F28), a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

