#include "include_asm.h"
#include "names.h"

/* Qwen draft (branch qwen/autonomy, 2e797515), checked by tools/check.py */
void func_0028A180(int, int);

extern void func_0028B650(char *, int);

/* Update the measured fields of the first matching key among13records. */
typedef struct { unsigned int fields[25]; int key; unsigned int busy; unsigned int tail[9]; } UpdateRecord;

extern UpdateRecord D_L00_0027DD00[13];

typedef struct {
    char pad0[0x8];
    int maxValue;
    int *valuePtr;
    char pad10[0x38];
    short unk48;
    short unk4A;
    char pad4C[0x4];
    int unk50;
    int unk54;
    int w;
    int h;
    int flags;
    char pad64[0x8];
    int unk6C;
    unsigned char cnt[4];
    int shownValue;
    int targetValue;
    int visibleTimer;
    void *unk80;
} HudElem;

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

/* Does nothing (empty stub). */
void func_00288D88(void)
{
}

typedef struct {
    int active;
    int timer;
    char pad08[0x18];
    int entryIndex;
    int pending;
} SubtitleState;

extern SubtitleState D_00254E78;

/* Makes the subtitle on screen start closing, depending on how far along it is. */
void func_00288D90(void)
{
    switch (gSubtitleState.active) {
    case 0:
        gSubtitleState.pending = -1;
        return;
    case 1:
    case 2:
        gSubtitleState.active = 7;
        gSubtitleState.timer = 0;
        return;
    case 3:
        gSubtitleState.active = 7;
        gSubtitleState.timer = 0;
        return;
    case 4:
        gSubtitleState.active = 6;
        gSubtitleState.timer = 4 - gSubtitleState.timer;
        return;
    case 5:
        gSubtitleState.active = 6;
        gSubtitleState.timer = 0;
        return;
    case 7:
        return;
    }
}

typedef struct { int active; char reserved04[0x20]; int key; int selection; char reserved2C[0x14]; int value40; int value44; } SelectorState;
typedef struct { char reserved00[0x24]; int key; char reserved28[0x40]; int active;
                short soundId; char reserved6E[4]; unsigned short soundState; } SelectorOwner;
typedef struct { unsigned short key; char reserved02[10]; } SelectorRow;
extern SelectorState ref_L00_00288E18_00;
extern SelectorOwner D_001A63A8;
extern SelectorRow D_0018C958[];
/* Queues a spoken line with subtitles, but only if no line is playing or waiting. Returns 1 if it was accepted, otherwise 0. */
int func_00288E18(int key, int selection)
{
    SelectorState *state = &ref_L00_00288E18_00;
    if (state->active == 0 && state->key == -1 && gMusicState.active == 0 &&
        gMusicState.key == -1 && gSubtitleHistory[selection].key != 65535) {
        state->key = key;
        state->selection = selection;
        state->value40 = 0;
        state->value44 = 0;
        return 1;
    }
    return 0;
}


typedef struct { int unk00; int unk04; int id; int unk0C; } TextEntry;

typedef struct { char pad00[0x2A20]; int voiceFlags[1]; } DiscToc;

extern TextEntry *D_001B1840 __attribute__((sda));
extern DiscToc D_0014B540;

/* Stops the current subtitle and clears its state. Also marks its voice line as finished if it was playing. */
void func_00288EA0(void)
{
    int voiceId;

    if (gSubtitleState.active == 0)
        return;
    if (gSubtitleState.entryIndex != -1) {
        voiceId = gSubtitleEntries[gSubtitleState.entryIndex].id;
        if (voiceId != -1 && gCopySetupData.voiceFlags[voiceId] != 0 &&
            voiceId == gMusicState.soundId - 6000) {
            if (gMusicState.soundState != 6 && gMusicState.soundState != 7)
                gMusicState.soundState = 5;
        }
    }
    gSubtitleState.active = 0;
    gSubtitleState.pending = -1;
    gSubtitleState.entryIndex = -1;
    gSubtitleState.timer = 0;
}





/* func_00289178 is in 00289178.c. */

/* Does nothing (empty stub). */
void func_00289AA0(void)
{
}

/* func_00289AA8 is in 00288D88-render.c. */

extern short D_00254EC8[][2];

/* Looks a number up in the table of 170 pairs and returns its position, or -1 if missing. It can also hand back the other number of the pair. */
int func_00289FC8(short key, int field, unsigned short *out)
{
    int i;

    for (i = 0; i < 170; i++) {
        if (D_00254EC8[i][field] == key) {
            if (out != 0)
                *out = (unsigned short)D_00254EC8[i][field ? 0 : 1];
            return i;
        }
    }
    return -1;
}

extern unsigned char D_0018D0E8[];
extern int D_001A7C04_sda __attribute__((sda));
extern int D_001A7C04[] __attribute__((sda));

/* Moves a text entry to the end of the recently-used list, adding it if it was missing. */
void func_0028A030(short id)
{
    int tableIndex = FindPairInTextTable(id, 1, 0);
    int i;

    if (tableIndex == -1)
        return;
    for (i = 0; D_0018D0E8[i] != tableIndex && i < D_001A7C04_sda; i++) {
    }
    if (i < D_001A7C04_sda) {
        for (; i < D_001A7C04_sda - 1; i++)
            D_0018D0E8[i] = D_0018D0E8[i + 1];
        D_0018D0E8[i] = 0;
        D_001A7C04[0]--;
    }
    D_0018D0E8[D_001A7C04[0]] = tableIndex;
    D_001A7C04[0]++;
}

/* Queues a pop-up hint when event 0x17 or 0x19 happens. */
void
func_0028A130(int eventId)
{
  if (eventId == 0x17)
    QueueHintMessage(0x9f3, 0x4a);
  if (eventId == 0x19)
    QueueHintMessage(0xa35, 0x8c);
  return;
}

/* A seven-entry ring of key/value pairs: D_001B1866 counts the entries, D_001B1867 is the
 * first one's slot. The incomplete sda arrays give retail's absolute macro forms (`la`,
 * `lui $at` stores) at -G0. */
extern unsigned char D_001B1866[] __attribute__((sda));
extern unsigned char D_001B1867[] __attribute__((sda));
extern short D_001B1848[] __attribute__((sda));
extern short D_001B1858[] __attribute__((sda));

/* Appends key with its value unless the ring is full or already holds key. Every access
 * reads the globals directly: local copies of the count and first slot lose the register
 * copies retail makes around the loop. */
void func_0028A180(int key, int value)
{
    int i;

    if (D_001B1866[0] < 7) {
        for (i = D_001B1866[0] - 1; i >= 0; i--) {
            if (D_001B1848[(D_001B1867[0] + i) % 7] == key)
                return;
        }
        D_001B1848[(D_001B1867[0] + D_001B1866[0]) % 7] = key;
        D_001B1858[(D_001B1867[0] + D_001B1866[0]) % 7] = value;
        D_001B1866[0]++;
    }
}


/* func_0028A278 is defined in 0028A278.c with its qualified address profile. */

typedef struct {
    int value;
    int timer;
    int age;
    short reserved;
    short state;
} CounterRow;
typedef struct {
    CounterRow rows[2];
    int shown;
    int base;
    int pending;
    int active;
    int falling;
} CounterState;
extern CounterState D_001B1928 __attribute__((sda));
extern int D_001A8BB0[] __attribute__((sda));
extern int D_001A79F8[] __attribute__((sda));
extern int func_0029B780(void);
extern void func_0029CBA8(int);
extern void func_0028A278(void);
extern void func_0029B698(int);

/* Moves the shown bolt count (D_001A79F8 is the real one) to the real count: a change opens a
 * transition row, 60 frames without a further change commit it, and the pending amount is then
 * applied over 15 frames. */
void func_0028A2F8(void)
{
    CounterRow *row;
    int index;
    int falling;
    int previous;
    int delta;

    if (HasLevelObjectValuePair())
        return;
    func_0029CBA8((int)&gBoltCounterState.shown);
    if (gCurrentGameMode[0] == 5 && gPlayerBolts[0] < gBoltCounterState.shown) {
        ResetBoltCounterDisplay();
    } else {
        falling = gBoltCounterState.falling;
        if (!falling && gBoltCounterState.active == -1 && gPlayerBolts[0] < gBoltCounterState.shown) {
            index = gBoltCounterState.rows[0].state != 0;
            row = &gBoltCounterState.rows[index];
            falling = 1;
            row->state = falling;
            row->timer = 0;
            row->age = 0;
            row->value = gBoltCounterState.shown - gPlayerBolts[0];
            gBoltCounterState.active = index;
            gBoltCounterState.falling = falling;
        } else if (!falling && gBoltCounterState.active == -1 && gBoltCounterState.shown + gBoltCounterState.pending < gPlayerBolts[0]) {
            index = gBoltCounterState.rows[0].state != 0;
            row = &gBoltCounterState.rows[index];
            row->state = 1;
            row->timer = 0;
            row->age = 0;
            row->value = 0;
            gBoltCounterState.active = index;
            gBoltCounterState.falling = 0;
        }
    }
    index = gBoltCounterState.active;
    if (index != -1) {
        row = &gBoltCounterState.rows[index];
        if (row->state != 3) {
            previous = row->value;
            if (previous >= 0) {
                row->value = gPlayerBolts[0] - gBoltCounterState.shown + gBoltCounterState.pending;
                if (row->value != previous)
                    row->timer = 0;
            }
            row->timer++;
            row->age++;
            if (row->timer > 60) {
                gBoltCounterState.pending = row->value;
                gBoltCounterState.base = gBoltCounterState.shown;
                row->timer = -1;
                row->state = 3;
            }
        }
    }
    if (index != -1 || gBoltCounterState.rows[0].state == 3 || gBoltCounterState.rows[1].state == 3)
        ForwardValueToLevelObject(180);
    for (index = 0; index < 2; index++) {
        row = &gBoltCounterState.rows[index];
        switch (row->state) {
        case 1:
            if (row->age >= 15)
                row->state = 2;
            break;
        case 3:
            row->timer++;
            delta = (int)((float)gBoltCounterState.pending * 0.0714285746f);
            gBoltCounterState.shown += delta;
            row->value -= delta;
            if (gBoltCounterState.falling ? row->value > 0 : row->value < 0)
                row->value = 0;
            if (row->timer >= 15) {
                if (gBoltCounterState.shown != gBoltCounterState.base + gBoltCounterState.pending)
                    gBoltCounterState.shown = gBoltCounterState.base + gBoltCounterState.pending;
                gBoltCounterState.pending = 0;
                gBoltCounterState.active = -1;
                row->state = 0;
                gBoltCounterState.falling = 0;
            }
            break;
        }
    }
}

/* func_0028A670 (1,192 bytes, 28 places): the counters panel. This unit is built with
 * -frac2-reload-lone-class-no-rotate -frac2-reload-reuse-pseudo-reg (config/cflags.txt): draw 2's
 * 0x8710 reload returns to $a2, which loaded the same pseudo in draw 1, and the draw-1 truncation's
 * one-register FP scratch class leaves the reload round robin alone, as retail
 * (docs/build/compiler-notes.md). No other function of this unit changes with them. Owner
 * standard of 12 November 2026; forced on everywhere they change 266 functions. The hud_coord
 * dead-test helper is allowed by owner ruling (7 November 2026). */
typedef struct { float value[7]; } CounterWidths;
extern float D_001A8DE0[];
extern char D_001A8E00[];
extern unsigned char *D_001A8CFC __attribute__((sda));
extern float D_001B23A4 __attribute__((sda));
extern int func_00283D38(int, int, float);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

/* The display mode word beside the HUD scale. */
extern int D_001B23A0 __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel; the display-mode test
   has no effect on the result (as func_00326A10). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && D_001B23A0 == active)
        scaled = 1.0f;
    return result;
}

/* Draws the bolt gain or loss numbers next to the bolt counter. */
void func_0028A670(void)
{
    char text[16];
    unsigned char active;
    CounterWidths widths;
    int firstX, y, secondY, x, firstY, secondX;
    unsigned int color;
    CounterRow *row;
    int i;
    unsigned int first, second;
    float fade, scale, width;
    int len;
    int one, id;

    secondX = 0;
    color = 0;
    y = 0;
    secondY = 0;
    x = 0;
    firstY = 0;
    widths = *(CounterWidths *)D_001A8DE0;
    scale = 0.0f;
    first = 0;
    second = 0;
    for (i = 0; i < 2; i++) {
        row = &gBoltCounterState.rows[i];
        firstX = 0;
        one = 1;
        switch (row->state) {
        case 1:
            fade = (float)row->age * 0.0714285746f;
            first = FastTweenColor(0x00F0C070, 0x55F0C070, fade);
            second = FastTweenColor(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x0029A1FF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 2:
            if (row->timer < 14)
                fade = (float)row->timer * 0.0714285746f;
            else
                fade = 1.0f;
            first = 0x55F0C070;
            second = 0x60442D00;
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x8000FFFF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 3:
            if (row->timer < 7)
                fade = 1.0f;
            else
                fade = 1.0f - ((float)row->timer - 7.0f) * 0.142857149f;
            first = FastTweenColor(0x00F0C070, 0x55F0C070, fade);
            second = FastTweenColor(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = FastTweenColor(0x001010F0, 0x801010F0, fade);
            else
                color = FastTweenColor(0x0029A1FF, 0x6029A1FF, fade);
            x = 442;
            scale = 1.0f;
            y = 36;
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            break;
        }
        if (firstX) {
            Sprintf(text, D_001A8E00, gBoltCounterState.rows[i].value);
            len = strlen_001157AC(text);
            if (len > 0) {
                width = widths.value[len - 1];
                active = one;
                id = FindTableEntryById(D_001A8CFC + 0x8710, 178);
                DrawScaledObjectTwoAxes((char *)id, first,
                    (float)firstX, (float)hud_coord((float)firstY, D_001B23A4, 0.5f, active), scale, scale, width);
                id = FindTableEntryById(D_001A8CFC + 0x8710, 179);
                DrawScaledObjectTwoAxes((char *)id, second,
                    (float)secondX, (float)hud_coord((float)secondY, D_001B23A4, 0.5f, active), scale, scale, width);
                DrawTextRightAlignedSmallFont(x, hud_coord((float)y, D_001B23A4, 0.5f, one), (int)color, (unsigned char *)text, strlen_001157AC(text));
            }
        }
    }
}



/* func_0028AB70 is in 00288D88-init-g8.c. */


/* The HUD arena at D_001B1870, RAC1's HudState at D_0019A4E8 (src/game/hud.c): heap_cur and
 * heap_end are D_001B1880/D_001B1884, the texture tables follow. Its fields are read at an
 * offset from the arena's name: such a macro load has length 2, so reorg leaves it out of slots. */
struct HudTexCounts {
    unsigned char pad0[0x14];
    int mid_ends[8];
    int ends[16];
    int loaded[16];
};
struct HudBank {
    int unk0;
    int off4;
    int off8;
    int offC;
    int off10;
    unsigned char pad14[0x40];
    int has54;
    int size58;
    int has5C;
    int has60;
    int has64;
    unsigned char pad68[0x2C];
    int unk94;
    int unk98;
    int unk9C;
    int unkA0;
    int unkA4;
};
struct HudTexPage {
    unsigned int source_address;
    unsigned short gs_block_offset;
    unsigned char width_log2;
    unsigned char height_log2;
};
struct HudState {
    int serial;
    int unk4;
    int unk8;
    int z;
    int heap_cur;
    int heap_end;
    union {
        struct HudTexCounts *counts;
        struct HudBank *bank;
    } header;
    void *anim_defs;
    void *frame_refs;
    struct HudTexPage *image_pages;
    struct HudTexPage *palette_pages;
};
extern struct HudState D_001B1870 __attribute__((sda));
extern void func_0028AE88(int, int);
typedef struct { char pad[0x20]; int dest; char gap[0xf0]; int offset; } LoadGroupRoot;
extern LoadGroupRoot D_001F2840;
extern int D_001B18B0;
extern int D_001B18B8;
extern int D_001B18BC;
extern int D_001B18C0;
extern int func_002EEED0(int, int, int, int, int);
extern void func_0029D4D0(int, int);
/* Fetches the bank's stashed texture groups (handles at +0x94 on, sizes at +0x54 on) to dest at
 * a running offset and links each one. Groups 3 and 4 depend on mode: 0 takes 3, 1 takes 4, 2
 * takes both. */
void func_0028ACB0(int mode)
{
    int dest, offset;
    {
        int size;
        dest = gPauseMenuState.dest;
        size = gHudState.header.bank->has54;
        offset = gPauseMenuState.offset;
        if (size) {
            UploadRecordsToBufferSlot(dest, gHudState.header.bank->unk94, 0, D_001B18B0/16, 0);
            fast_decompress(dest, offset);
            LinkHudBank(0, offset);
            offset += size;
        }
    }
    {
        int size = gHudState.header.bank->has5C;
        if (size) {
            UploadRecordsToBufferSlot(dest, gHudState.header.bank->unk9C, 0, D_001B18B8/16, 0);
            fast_decompress(dest, offset);
            LinkHudBank(2, offset);
            offset += size;
        }
    }
    if (mode == 0 || mode == 2) {
        int size = gHudState.header.bank->has60;
        if (size) {
            UploadRecordsToBufferSlot(dest, gHudState.header.bank->unkA0, 0, D_001B18BC/16, 0);
            fast_decompress(dest, offset);
            LinkHudBank(3, offset);
            offset += size;
        }
    }
    if (mode == 1 || mode == 2) {
        if (gHudState.header.bank->has64) {
            UploadRecordsToBufferSlot(dest, gHudState.header.bank->unkA4, 0, D_001B18C0/16, 0);
            fast_decompress(dest, offset);
            LinkHudBank(4, offset);
        }
    }
}



extern int D_001A7308 __attribute__((section(".sdata")));
extern void func_0028F948(unsigned int, int, int, int, int, int);

/* Uploads the texture pages of a HUD bank to video memory, linking the first group if it is not loaded yet. */
void func_0028B160(int bank, int base, int immediate)
{
    struct HudTexCounts *counts;
    int address;
    int bank_offset;
    int first;
    int end;
    int i;
    int page;
    int width_log2;
    int height_log2;
    int size;

    if (gHudState.header.counts->loaded[bank] == 0) {
        LinkHudBank(0, base);
        address = D_001A7308;
    } else {
        address = D_001A7308;
    }
    counts = gHudState.header.counts;
    bank_offset = bank << 2;
    first = bank == 0 ? 0 : counts->ends[bank - 1];
    i = first;
    end = *(int *)((unsigned char *)gHudState.header.counts + bank_offset + 0x34); /* ends[bank] */
    do {
        for (; i < end; i++) {
            page = address >> 8;
            width_log2 = gHudState.image_pages[i].width_log2;
            height_log2 = gHudState.image_pages[i].height_log2;
            size = 1 << (width_log2 + height_log2);
            UploadImageToVram(gHudState.image_pages[i].source_address, page, 0x1B, width_log2,
                          height_log2, immediate);
            address += size * 4;
            gHudState.image_pages[i].gs_block_offset = page;
        }
    } while (0);
}

extern char *D_001BAF3C;
extern char * volatile D_001B1880 __attribute__((sda));
extern char * volatile D_001B1884 __attribute__((sda));

/* Sets up the HUD memory pool as one 400 KB block. */
void func_0028B288(void)
{
    char *poolStart = D_001BAF3C;
    D_001B1880 = poolStart;
    D_001B1884 = poolStart + 0x64000;
}

/* Hands out a piece of the HUD memory pool, rounded up to 16 bytes. Returns 0 if there is not enough room. */
char *func_0028B2B8(int size)
{
    char *end;
    char *cursor;

    if (D_001B1880 == 0)
        InitHudMemoryPool();
    end = D_001B1884;
    cursor = D_001B1880;
    if (end - cursor < size)
        return 0;
    size = (size + 15) & 0xFFFFFFF0u;
    D_001B1880 = cursor + size;
    return cursor;
}

/* func_0028B338 is in 00288D88-g8.c. */

/* func_0028B3D0 is in the -G8 sibling. */

/* Calls a callee with (this, word at +32), copies six words from +36..+56 down to +4..+24, calls the function pointer at +48 with this when non-zero, then clears +104. */
/* Finishes setting up a HUD element: copies its settings, runs its setup function and clears its busy flag. */
void func_0028B4D8(char *element)
{
    int callback;

    LoadHudElementFromTable(element, *(int *)(element + 32));
    callback = *(int *)(element + 48);
    *(int *)(element + 4) = *(int *)(element + 36);
    *(int *)(element + 20) = *(int *)(element + 52);
    *(int *)(element + 24) = *(int *)(element + 56);
    *(int *)(element + 12) = *(int *)(element + 44);
    *(int *)(element + 8) = *(int *)(element + 40);
    *(int *)(element + 16) = callback;
    if (callback != 0)
        ((void (*)(char *))callback)(element);
    *(int *)(element + 104) = 0;
}

typedef struct { unsigned char pad00[0x64]; int key; unsigned char pad68[0x28]; } SearchRow_28B5D0;
extern SearchRow_28B5D0 D_00255330[];
extern void func_0028B3D0(int, int, int, int, int, int, int);

/* Resets all 13 HUD elements. */
void func_0028B540(void)
{
    char *row = (char *)gHudElements;
    int *field = (int *)(row + 0x6c);
    int i = 0;
    do {
        SetHudSlotContents(i, 0xffff, 0, 0, 0, 0, 1);
        i++;
        field[4] = 0;
        field[0] = -6;
        FinishHudElementSetup(row);
        row += 0x90;
        field = (int *)((char *)field + 0x90);
    } while (i < 13);
}

/* Starts closing the HUD element that has this key. Returns 1 if it was found. */
int func_0028B5D0(int key)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (gHudElements[i].key == key)
            break;
    }
    if (i < 13) {
        SetHudSlotContents(i, 0xffff, 0, 0, 0, 0, 0);
        return 1;
    }
    return 0;
}



/* findfirstmatchingkey among13records and writefield24 plusfield04 whenword68clear */
/* Sets the target value of the HUD element that has this key. */
void func_0028B6C8(int key, unsigned int value)
{
    int i;
    for (i = 0; i < 13; i++) {
        if (D_L00_0027DD00[i].key == key) break;
    }
    if (i < 13) {
        D_L00_0027DD00[i].fields[9] = value;
        if (D_L00_0027DD00[i].busy == 0)
            D_L00_0027DD00[i].fields[1] = value;
    }
}

/* Shifts a HUD element's draw position so it is centred or lined up the way its flags say. */
int func_0028B740(HudElem *rec, int *x, int *y) {
    int w = rec->w;
    int h = rec->h;
    int flags = rec->flags;

    if ((flags ^ 1) & 1) {
        if (!(flags & 2)) {
            *y -= h >> 1;
        }
    }
    if (!(rec->flags & 4)) {
        if (rec->flags & 8) {
            *x -= w;
        } else {
            *x -= w >> 1;
        }
    }
    return 0;
}

extern float ref_L00_002F6FB8_00[];
extern float ref_L00_002F6FB8_01[];
extern float func_00283CE0(int);
extern int func_00283CF0(float);

/* Slides a HUD element's draw position in or out of view, one animation step at a time. */
void func_0028B7A8(HudElem *element, int *x, int *y, int index, int delta)
{
    float scale;
    int flags;
    int dx = 0;
    int dy = 0;

    if (element->visibleTimer != 0)
        index -= delta;
    else
        index += delta;

    if (index < 0)
        index = 0;
    if (index > 23)
        index = 23;

    if (element->visibleTimer != 0)
        scale = ref_L00_002F6FB8_00[index];
    else
        scale = ref_L00_002F6FB8_01[index];

    flags = element->flags;
    if (flags & 1)
        dy = -FloatToInt(scale * (IntToFloat(element->h) + 52.0f) + 0.5f);
    else if (flags & 2)
        dy = FloatToInt(scale * (IntToFloat(element->h) + 52.0f) + 0.5f);
    else if (flags & 4)
        dx = -FloatToInt(scale * (IntToFloat(element->w) + 20.0f) + 0.5f);
    else if (flags & 8)
        dx = FloatToInt(scale * (IntToFloat(element->w) + 20.0f) + 0.5f);

    *x += dx;
    *y += dy;
}

/* Works out the starting number and the size of a HUD number counter. */
void func_0028B950(u8 *element) {
    s32 *value=*(s32 **)(element+0xc);
    s32 digits;
    s32 remaining;
    if (value!=0 && ((u32)value&3)==0) {
        s32 initial=*value;
        s32 maximum=*(s32 *)(element+8);
        *(volatile s32 *)(element+0x78)=initial;
        if (maximum<initial) *(volatile s32 *)(element+0x78)=maximum;
        *(s32 *)(element+0x74)=*(volatile s32 *)(element+0x78);
    } else {
        *(volatile s32 *)(element+0x74)=99999;
        *(volatile s32 *)(element+0x78)=99999;
    }
    digits=0;
    for (remaining=*(volatile s32 *)(element+8);remaining>9;remaining/=10) digits++;
    if ((*(u32 *)(element+0x60)&3)==0 && (*(u32 *)(element+0x60)&12)!=0) {
        *(s32 *)(element+0x5c)+=(digits+1)*12;
        if (*(volatile s32 *)(element+0x58)<14) { *(s32 *)(element+0x58)=14; return; }
    } else {
        if (*(s32 *)(element+0x5c)<12) *(s32 *)(element+0x5c)=12;
        *(s32 *)(element+0x58)=*(volatile s32 *)(element+0x58)+(digits+1)*14;
    }
}

/* Sets up a HUD counter element. */
void func_0028BA50(HudElem *element) { element->visibleTimer = 0xD2; element->unk48 = 0; element->unk4A = 0; InitHudCounterValues((u8 *)element); }

extern float func_00282C10(float);
extern void func_0028DF80(void *);

/* Per-frame update of a HUD counter: counts the shown number toward the real value and fades it in and out. */
void func_0028BA88(HudElem *element)
{
    unsigned char *fadeBytes = element->cnt;
    int delta, limit, step;
    if (element->valuePtr) {
        int value = *element->valuePtr;
        if (value < 0) value = 0;
        element->targetValue = value;
        if (element->maxValue < value) element->targetValue = element->maxValue;
    }
    if (element->shownValue != element->targetValue) {
        element->visibleTimer = 180;
        if (element->unk6C >= 24) {
            delta = __builtin_abs(element->shownValue - element->targetValue);
            if (delta) {
                step = FloatToInt(square_root(IntToFloat(delta) * 0.04f) * 5.0f);
                limit = delta / 5;
                if (step < limit) step = limit;
                if (step > 121) step = 121;
                else if (step < 1) step = 1;
                fadeBytes[3] += step;
                if (fadeBytes[3] >= 3) {
                    step = fadeBytes[3] / 2;
                    if (element->targetValue < element->shownValue) element->shownValue -= step;
                    else element->shownValue += step;
                    fadeBytes[3] -= step * 2;
                }
            }
        }
    }
    if (element->visibleTimer >= 5) {
        if (fadeBytes[0] < 8) fadeBytes[0]++;
        else if (fadeBytes[1] < 8) fadeBytes[1]++;
    } else {
        if (fadeBytes[1] != 0 || fadeBytes[0] != 0) element->unk6C = 1;
        {
            int fade = fadeBytes[1];
            if (fade) fadeBytes[1] = fade - 1;
            else {
                if (fadeBytes[0]) fadeBytes[0]--;
            }
        }
    }
    func_0028DF80((char *)element + 0x40);
}


extern void func_0029CCD8(int, int);
extern void func_002B0CE0(int, int, int);

/* Calls two sound helpers, the second with sound number 13. */
void func_0028BCA0(int arg) {
    func_0029CCD8(arg, 1);
    ForceClaimNotice(13, 0, 1);
}


