#include "include_asm.h"
#include "names.h"

extern int D_001A8C88[] __attribute__((sda));
extern int D_001A8C8C[] __attribute__((sda));

extern int *D_001AA4F0 __attribute__((section(".sdata")));
extern int *D_001AA4F0_1 __attribute__((sda));
extern unsigned char D_001A7AFD __attribute__((section(".sdata")));
extern int func_00295870(int);

extern char D_0014B540_1[];

extern short D_00152CE4[];

void func_002942A0(int, int, int, int);

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

/* --- verbatim preprocessed fp-bit.c ends here --- */

extern u8 BOOT_D_001395B8[];

typedef struct {
    u8 prefix[0xa7];
    u8 fielda7;
} OrbitalBitmapView;

extern u8 D_001395B8[];

extern int D_L03_001CA2A8[];

/* 28-entry table scan.  The table is reached through the resident pointer at
   0x1AA7F0; the caller's id is looked up from index 0, the first hit wins, and
   an index is rejected when its slot is empty while the small-data flag at
   0x1A79F0 is set.  The flag is read through $gp and the load sits in the delay
   slot of the bail-out branch, so the body needs the -G8 small-data profile.

   Measured shape note: the table pointer must be reached through the global
   itself (`D_L01_001AA7F0[i]`), not through a local `int *` copy.  With a local the
   allocator keeps one register for the whole live range (26 instructions);
   with the global gcc loads it into $v1, hoists the loop-invariant value and
   emits the retail `move $a2,$v1` copy at the block boundary (28 instructions,
   byte-identical). */
extern int *D_L01_001AA7F0 __attribute__((sda));

extern int D_001A79F0_3 __attribute__((sda));

extern int D_001C4FA0[];

extern void F6df9730c_FUN_00282B50(char *dst, int *src, int count);

/* Find a mapped record by its unsigned halfword class and return its opaque word. */
typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;

extern unsigned char D_00139568[];

extern MappedClassEntry D_L00_00262570[];

/* Substitute the first percent selector in a record's localized text. */
typedef struct {
    unsigned char gap0[10];
    short text_id;
    short mapped_key;
    unsigned char gap0e[26];
} DobboFormatRow396;

typedef struct {
    unsigned char gap0[32];
    DobboFormatRow396 *rows;
} DobboFormatRoot396;

typedef struct {
    unsigned char gap0[0x80];
    int amount;
    unsigned char gap84[0x5c];
} DobboFormatMapped396;

extern DobboFormatRoot396 D_L00_001C93A0;

extern const char D_L00_001A9AA0[];

extern const char D_L00_001A9AA8[];

extern const unsigned char *func_00288FB8(int);

extern void func_00115DA8(char *, const char *, ...);

/* scans a 48-entry table of 20-byte records for a record whose first word equals an argument, and when the scan succeeds stores the found index into a short counter and calls a helper with (index, -1, second argument, 1). */
void func_00294BC8(int id, int destBuffer)
{
    int i;
    int *table = (int *)D_0014B540_1;

    for (i = 0; i < 48; i++) {
        if (table[i * 5 + 4816] == id)
            break;
    }
    if (i != 48) {
        D_00152CE4[0] = (short)i;
        StartDiscEntryLoad(i, -1, destBuffer, 1);
    }
}

extern int func_00282A18(int);

extern int D_001A72D0[] __attribute__((sda));

extern int D_001B15FC[] __attribute__((sda));

typedef struct {
    int addr;
    short unk4;
    short cbp;
    int unk8;
    unsigned char tw;
    unsigned char th;
    short tbp;
} TexSlot;

extern TexSlot D_001B9340[];

typedef struct {
    char *clut;
    char *pix;
    char pad08[0xC];
    int clutSize;
    char pad18[0x34];
    int tw;
    int th;
    char pad54[0xC];
} TexDesc;

/* Loads a 256-colour texture file p (width at +8, height at +0xC, CLUT at +0x20,
   pixels after it): the CLUT and the pixels take the next VRAM space, the texture
   is queued in the 64-entry upload table and its GS TEX0 value is returned.  The
   TEX0 value is written with RAC1's mixed signed/unsigned grouping (loaders.c):
   the casts stop fold's tree flattening, which keeps retail's term order. */
long func_00294C40(char *p)
{
    TexDesc t;
    int w;
    int cbp;
    int tbp;
    int addr;
    long reg;

    t.clut = p + 0x20;
    t.clutSize = 0x400;
    t.tw = log2dim(*(int *)(p + 8));
    t.th = log2dim(*(int *)(p + 0xC));
    t.pix = p + 0x20 + t.clutSize;
    addr = D_001A72D0[0];
    cbp = addr >> 8;
    addr += 0x400;
    tbp = addr >> 8;
    D_001A72D0[0] = addr + (1 << (t.tw + t.th));
    w = t.tw - 6;
    if (w < 0) {
        w = 0;
    }
    w = 1 << w;
    reg = (long)((unsigned long)((long)tbp | ((long)w << 14) | ((long)0x13 << 20)
                                 | ((long)t.tw << 26))
                 | ((unsigned long)t.th << 30) | ((unsigned long)1 << 34)
                 | ((unsigned long)cbp << 37))
        | ((long)4 << 61);
    if (D_001B15FC[0] < 0x40) {
        D_001B9340[D_001B15FC[0]].addr = (int)t.clut;
        D_001B9340[D_001B15FC[0]].cbp = cbp;
        D_001B9340[D_001B15FC[0]].unk4 = 0;
        D_001B9340[D_001B15FC[0]].unk8 = (int)t.pix;
        D_001B9340[D_001B15FC[0]].tw = t.tw;
        D_001B9340[D_001B15FC[0]].th = t.th;
        D_001B9340[D_001B15FC[0]].tbp = tbp;
        D_001B15FC[0]++;
    }
    return reg;
}


/* Sets one bit in the saved-flags bitmap and returns whether it was already set. */
s32 func_00294E48(s32 index)
{
    s32 byteIndex = index / 8;
    s32 bit = index % 8;
    s32 wasSet;

    if ((u32)bit < 8) {
        wasSet = (BOOT_D_001395B8[byteIndex + 0xA7] >> bit) & 1;
    } else {
        wasSet = 0;
    }
    if ((u32)bit < 8) {
        BOOT_D_001395B8[byteIndex + 0xA7] |= 1 << bit;
    }
    return wasSet;
}

/* returns the indexed resident bit using signed division by eight and an unsigned remainder validity guard */
u32 func_00294EC8(s32 index) {
    s32 byteIndex=index/8;
    u32 bit=index%8;
    u32 previous=0;
    if(bit<8) {
        OrbitalBitmapView *state=(OrbitalBitmapView *)(D_001395B8+byteIndex);
        previous=((s32)state->fielda7>>bit)&1;
    }
    return previous;
}

/* func_00294F10 is defined in 00294BC8-map-setup-g64.c. */

/* shared native body of family 9306cc1f965a5c85 */
/* Finds the first used map slot out of five that is still unassigned, scanning forward or backward. */
int func_00295680(int reverse)
{
    int *usedTable = D_L03_001CA2A8;
    int *assignTable = usedTable + 5;
    int i;

    for (i = 0; i < 5; i++) {
        int slot = reverse ? 4 - i : i;
        if (usedTable[slot] == 0)
            continue;
        if (assignTable[slot] != -1)
            continue;
        return slot;
    }
    return -1;
}


/* Moves the cached map data from one of the five slots into another and frees the first one. */
void func_00295788(int dstSlot, int srcSlot)
{
    extern int D_001C4FA0[];
    extern void func_00282B50(void *, void *, int);
    int *base = gMapOverlayState;
    int *bufferPtrs = (int *)((char *)base + 0x288);
    int *sizes = (int *)((char *)base + 0x2B4);
    int *ids;

    FastMemoryHelperC((void *)bufferPtrs[dstSlot], (void *)bufferPtrs[srcSlot], sizes[srcSlot] << 4);
    ids = (int *)((char *)base + 0x29C);
    ids[dstSlot] = ids[srcSlot];
    sizes[dstSlot] = sizes[srcSlot];
    ids[srcSlot] = -1;
}

/* Returns which of the five map cache slots holds the given map id, or -1. */
int func_00295828(int id) {
    extern int D_001C4FA0[];
    int *base = gMapOverlayState;
    int *p = base + 0x29C / 4;
    int i = 0;
    do {
        if (p[-5] != 0 && p[0] == id) return i;
        i++;
        p++;
    } while (i < 5);
    return -1;
}

/* looks the level up in the map's table and then walks the levels next to it */
int func_002958B8(void)
{
    int flag = D_001A7AFD ? 0x100 : 0;
    unsigned int id = gMapOverlayState[0x230 / 4] + flag;
    int level;
    int *p;
    int index;
    unsigned int delta;
    int notfound;
    int limit;
    int one;
    int offset;
    int entry;

    if ((int)FindMapCacheSlotById(id) == -1) {
        if (IsMapEntryAvailable(id) != 0)
            return id;
    }
    level = gMapOverlayState[0x230 / 4];
    index = 0;
    if (level < 0x1C) {
        p = D_001AA4F0;
        while (*p != level) {
            p++;
            index++;
        }
    }
    delta = 1;
    notfound = -1;
    one = 1;
    limit = 4;
    do {
        offset = index + delta;
        if (offset < 0) goto update;
        if (offset >= 0x1C) goto update;
        {
            entry = D_001AA4F0_1[offset];
            if (entry != 0) {
                id = entry + flag;
                if (FindMapCacheSlotById(id) == notfound && IsMapEntryAvailable(id) != 0)
                    return id;
            }
        }
update:
        delta = ((int)delta > 0) ? -(int)delta : (one - delta);
    } while (delta != limit);
    return -1;
}

/* shared native body of family 490e2c59eb9d7105 */
/* Looks up a map's position in the 28-entry level table, or -1 if it is not there. */
int func_00295A10(int mapId)
{
    int index = -1;
    int i;

    for (i = 0; i < 28; i++)
        if (D_L01_001AA7F0[i] == mapId) { index = i; break; }

    if (D_L01_001AA7F0[index] == 0)
        index = D_001A79F0_3 ? -1 : index;

    return index;
}

extern int func_00295A10(int);

extern int func_00282C30(int);

/* Chooses which of the five map cache slots to reuse: a free one if there is one, otherwise the one farthest from the current map. */
int func_00295A80(void)
{
    int i;
    int currentIndex;
    int bestDistance = 0;
    int best = -1;

    if (gMapOverlayState[0x8C] == 0) {
        int j;

        for (j = 4; j >= 0; j--) {
            if (gMapOverlayState[0xA2 + j] != 0 &&
                j != gMapOverlayState[0xAC] &&
                gMapOverlayState[0xA7 + j] == -1)
                return j;
        }
    }
    currentIndex = FindMapTableIndex(gMapOverlayState[0x8C]);
    if (currentIndex == -1)
        return 1;
    for (i = 0; i < 5; i++) {
        int distance;

        if (gMapOverlayState[0xA2 + i] == 0)
            continue;
        if (i == gMapOverlayState[0xAC])
            continue;
        if (gMapOverlayState[0xA7 + i] == -1)
            return i;
        distance = subtract_integer_with_clamp(FindMapTableIndex(gMapOverlayState[0xA7 + i] & 0xFF) - currentIndex);
        if (bestDistance < distance) {
            bestDistance = distance;
            best = i;
        }
    }
    if (best == -1)
        best = 0;
    {
        int off = 0x29C;
        char *base = (char *)gMapOverlayState;
        *(int *)(base + off + best * 4) = -1;
    }
    return best;
}



/* Builds a bitmap by taking each byte from one of two sources depending on the bits of a mask. */
void func_00295BE8(u8 *out,u8 *sourceSet,u8 *sourceClear,u8 *maskBits) {
 s32 i=0;
 do {
  s32 next=i+1;
  u32 mask=1;
  u8 *nextp=maskBits+1;
  s32 j=7;
  do {
   u8 value;
   j--;
   if(*maskBits&mask) value=*sourceSet; else value=*sourceClear;
   mask<<=1;
   *out=value;
   sourceSet++;sourceClear++;out++;
  } while(j>=0);
  i=next;
  maskBits=nextp;
 } while(i<0x8000);
}

extern int D_001C51D0;
extern int func_00295C70(void);

/* Stores the current map number and refreshes the map-ready flag. */
void func_00295C50(int mapId) {
    D_001C51D0 = mapId;
    RefreshMapReadyFlag();
}

extern int func_00295870(int);

/* Picks the next free slot of the resident table and reports whether that
   slot is in use.  The resident flag at D_001A79F0_3 vetoes the slot while
   the table's counter is still empty.  The counter sits at the table's +0x230
   and the slot's own flag at its +0x24, so both are reached through the one
   base the retail uses (the array's indices 0x8C and 0x9). */
int func_00295C70(void)
{
    if (gMapOverlayState[0x8C] >= 0x1C)
        gMapOverlayState[0x8C] = 0x1B;
    if (IsMapEntryAvailable(gMapOverlayState[0x8C]))
        gMapOverlayState[0x9] = 1;
    else
        gMapOverlayState[0x9] = 0;
    if (gMapOverlayState[0x8C] == 0) {
        if (D_001A79F0_3 != 0)
            gMapOverlayState[0x9] = 0;
    }
    return gMapOverlayState[0x9] != 0;
}

/* func_00295D00 is defined in 00295D00-g8.c (-G8 -g). */

/* func_00295F60 is defined in 00295F60-map-g8.c (-G8 -Wa,-G64 -ffast-math -g). */

/* func_00297218 is defined in its sibling unit. */

extern void func_00297550(u8 *, s32, u8 *, short *);

/* packs a mask of the non-zero nibbles of every 32-nibble group of the
   4-bit-per-pixel bitmap that func_00297550 leaves at 0x70000000 */
void func_00297400(u8 *out, u8 *base, short *offsets)
{
    int i;
    int group;
    int bit;
    int tileX;
    int tileRowOffset;
    u32 *dst;
    u8 *src = (u8 *)0x70000000;

    for (i = 0; i < 0x100; i++) {
        decode_map_rle_row((u8 *)0x70000000, i, base, offsets);
        tileX = i % 16;
        tileRowOffset = (i / 16) << 9;
        dst = (u32 *)(out + ((tileX + tileRowOffset) << 2));
        for (group = 0; group < 0x20; group++) {
            u32 mask = 0;
            for (bit = 0; bit < 0x20; bit++) {
                u8 pixel = src[group * 16 + (bit >> 1)];
                u8 value = (bit & 1) ? (pixel >> 4) : (pixel & 0xF);
                if (value != 0)
                    mask |= 1 << bit;
                if ((bit & 0x1F) == 0x1F) {
                    *dst = mask;
                    dst++;
                    mask = 0;
                }
            }
            dst += 15;
        }
    }
}

/* Unpacks one run-length coded row of the map picture into 4-bit pixels. */
void func_00297550(u8 *out,s32 index,u8 *base,short *offsets) {
    s32 pending=0;
    u8 *start;
    short *table;
    s32 records,i;
    if (index!=0) start=base+(offsets+index)[-1];
    else start=base+0x200;
    table=(short *)(index*2+(s32)offsets);
    records=((base+*table-start)*2)/3;
    for(i=0;i<records;i++) {
        s32 position=i*2+i;
        u8 *p=start+(position>>1);
        u8 color=p[0],runByte=p[1],fill;
        s32 run;
        if ((position&1)!=0) color>>=4;
        else {
            runByte=(u8)((runByte<<4)|(color>>4));
            color&=15;
        }
        run=256;
        if(runByte!=0) run=runByte;
        fill=(u8)(color|(color<<4));
        if(pending) {
            pending=0;run--;
            *out |= color<<4;
            out++;
        }
        if(run!=0) {
            do {*out++=fill;run-=2;} while(run>0);
            if(run!=0) {out--;pending=1;*out=color;}
        }
    }
}


extern int D_001A79F0_4[] __attribute__((sda));

extern int D_001399B8[];

extern void func_00282A60(void *, int, int);

extern int func_00283EF0(void *, int, int, int);

extern void func_00297BB0(void *);

/* Passes the 0x800-byte buffer to func_00282A60 when the table's field at +0x28 is
   clear or its field at +0x238 is negative.  Otherwise goes through func_00283EF0
   and keeps the largest count per flag value.  The flag has no size here, so it is
   a macro load: $gp in a delay slot, absolute elsewhere. */
void func_00297670(void *buffer)
{
    int *table = gMapOverlayState;
    int count;

    if (table[0x10 / 4] == 0)
        return;
    if (table[0x28 / 4] == 0 || table[0x238 / 4] < 0) {
        ClearMemory(buffer, 0, 0x800);
        return;
    }
    TestAndSetSavedFlagBit(D_001A79F0_4[0]);
    count = FastMathHelperC(buffer, 0x800, table[0x14 / 4], table[0xC / 4]);
    if (count == -1)
        BuildOcclusionMapFromImage(buffer);
    if (D_001399B8[D_001A79F0_4[0]] < count)
        D_001399B8[D_001A79F0_4[0]] = count;
}



/* func_002977A8 is defined in 002977A8.c. */



/* func_002977A8 is defined in its sibling unit. */

/* Expands a 1-bit mask picture into 4-bit pixels and writes it out in repeated 64-byte pieces. */
void func_002979D8(char *dst, unsigned char *src)
{
    int nibbleTable[256];
    int chunk[16];
    int *chunkPtr;
    int i, j, k;

    for (i = 0; i < 256; i++) {
        nibbleTable[i] = 0;
        if (i & 0x01) nibbleTable[i] = 0x0000000f;
        if (i & 0x02) nibbleTable[i] |= 0x000000f0;
        if (i & 0x04) nibbleTable[i] |= 0x00000f00;
        if (i & 0x08) nibbleTable[i] |= 0x0000f000;
        if (i & 0x10) nibbleTable[i] |= 0x000f0000;
        if (i & 0x20) nibbleTable[i] |= 0x00f00000;
        if (i & 0x40) nibbleTable[i] |= 0x0f000000;
        if (i & 0x80) nibbleTable[i] |= 0xf0000000;
    }
    for (j = 0; j < 128; j++) {
        char *next;
        chunkPtr = chunk;
        next = dst + 64;
        for (k = 15; k >= 0; k--) {
            *chunkPtr++ = nibbleTable[*src++];
        }
        F6df9730c_FUN_00282B50(dst, chunk, 64);
        dst = next;
        F6df9730c_FUN_00282B50(dst, chunk, 64);
        dst += 64;
        F6df9730c_FUN_00282B50(dst, chunk, 64);
        dst += 64;
        F6df9730c_FUN_00282B50(dst, chunk, 64);
        dst += 64;
    }
}



/* localized row40 textID10 firstpercent selector b formats signedmappedword80 with original decimalformatter; other selector formats original error string, preserve prefix/tail */
void func_00297E00(int index, unsigned char *output)
{
    unsigned char temporary[80];
    const unsigned char *source = GetLocalizedString(D_L00_001C93A0.rows[index].text_id);
    unsigned char *p = temporary;
    if (!source)
        return;
    while (*source && *source != '%')
        *output++ = *source++;
    if (!*source) {
        *output = *source;
        return;
    }
    ++source;
    if (*source == 'b') {
        int key = D_L00_001C93A0.rows[index].mapped_key;
        DobboFormatMapped396 *record = (DobboFormatMapped396 *)&gWeaponTable_L00[gItemSlotToRecord[key]];
        Sprintf((char *)temporary, D_L00_001A9AA0, record->amount);
    } else {
        Sprintf((char *)temporary, D_L00_001A9AA8);
    }
    ++source;
    while (*p)
        *output++ = *p++;
    while (*source)
        *output++ = *source++;
    *output = 0;
}



extern int D_L00_0028D890[];
extern void *D_L00_001C5620[];
extern float D_00139A28[];

/* Copies the colour entries of one band of the resident table.
   The two base addresses are taken in the retail's order - the source
   table's first - and the two pointers in the retail's order, the
   destination's first: that is what puts the two lui/addiu pairs and the
   two argument registers where the retail has them. */
void func_002980D0(void)
{
    int band = D_001A79F0_3;
    int first;
    int last;
    float *colours;
    void **table;
    float *dst;
    void **src;

    if ((unsigned)band >= 0x13)
        return;
    first = D_L00_0028D890[band];
    last = D_L00_0028D890[band + 1];
    if (first >= last)
        return;
    table = D_L00_001C5620;
    colours = D_00139A28;
    dst = &colours[first * 4];
    src = &table[first];
    first = last - first;
    do {
        float *entry = (float *)src[0];
        if (entry != 0) {
            dst[0] = entry[4];
            dst[1] = entry[5];
            dst[2] = entry[0x3E];
        }
        dst += 4;
        src += 1;
    } while (--first != 0);
}

/* Does nothing. */
void func_00298170(void)
{
}

typedef struct {
    char reserved00[0x10];
    int field10;
    char reserved14[0x150];
    int field164;
    int field168;
    char reserved16c[0x10];
    int field17c;
} SharedState;
extern SharedState D_001393E0;
extern int D_001A7420[] __attribute__((sda));

extern unsigned int D_001A7424[] __attribute__((sda));
extern int D_001B1A3C __attribute__((sda));
extern int D_001B1A38 __attribute__((sda));
extern void (*D_002560D0[])(void);
/* Runs the current state's update function once per frame and counts how long the state has lasted; flag bits can first switch to state 20 or 21. */
void func_00298178(void)
{
    int prevState;
    int flags;
    char *state = (char *)&gMemcardState;
    if (*(int *)(state + 0x16c) != 0 ||
        *(int *)(state + 0x10) != 0 || *(int *)(state + 0x24) > 0)
        D_001B1A3C = 1;
    flags = *(int *)gSaveMenuFlags;
    prevState = gSaveMenuScreen[0];
    if (flags & 0x80) {
        gSaveMenuScreen[0] = 21;
        *(int *)gSaveMenuFlags = (flags & ~0x80) | 0x40;
    }
    flags = *(int *)gSaveMenuFlags;
    if (flags & 0x100) {
        gSaveMenuScreen[0] = 20;
        *(int *)gSaveMenuFlags = (flags & ~0x100) | 0x40;
    }
    D_002560D0[gSaveMenuScreen[0]]();
    D_001B1A38++;
    if (gSaveMenuScreen[0] != prevState)
        D_001B1A38 = 0;
}

/* Goes back to the default state 3 and clears the shared state fields. */
void func_00298278(void) {
    gSaveMenuScreen[0] = 3;
    gMemcardState.field17c = 0;
    gMemcardState.field10 = 0;
}

/* Resolve pending state requests after clearing the two transient flag bits. */
void func_00298298(void)
{
    int flags = gSaveMenuFlags[0];
    int cleared = flags & ~4;
    int mask = cleared & ~2;
    int v0, v1;
    SharedState *state = &gMemcardState;

    gSaveMenuFlags[0] = mask;
    if (state->field17c == 0) {
        gSaveMenuScreen[0] = 3;
        return;
    }
    if ((flags & 0x80) || *(int *)((char *)state + 0x16C) != 0) {
        int v = mask & ~0x80;
        gSaveMenuScreen[0] = 21;
        gSaveMenuFlags[0] = v | 0x40;
        return;
    }
    if (flags & 0x100) {
        int w = (mask ^ 0x100) | 0x40;
        gSaveMenuScreen[0] = 20;
        gSaveMenuFlags[0] = w;
        return;
    }
    if (state->field10 != 0) {
        state->field17c = 0;
        if (D_001A8C88[0] != 0 || D_001A8C8C[0] != 0) {
            gSaveMenuScreen[0] = 3;
            return;
        }
        v0 = mask | 1;
        v1 = 2;
    } else if (flags & 0x200) {
        v0 = mask ^ 0x200;
        v1 = 25;
    } else {
        return;
    }
    gSaveMenuFlags[0] = v0;
    gSaveMenuScreen[0] = v1;
}


extern unsigned int D_001A7424[] __attribute__((sda));
extern int D_001A7420[] __attribute__((sda));

/* Goes to state 3 when bit 0 of the flags is clear. */
void func_00298380(void) {
    if (((gSaveMenuFlags[0] ^ 1) & 1) != 0)
        gSaveMenuScreen[0] = 3;
}

/* Enters state 4 and sets two shared fields to -1. */
void func_002983A8(void) {
    gMemcardState.field164 = -1;
    gSaveMenuScreen[0] = 4;
    gMemcardState.field168 = -1;
}
