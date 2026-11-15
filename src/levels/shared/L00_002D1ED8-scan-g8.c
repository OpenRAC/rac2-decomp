/* func_L00_002D2E68 in its own unit: the mode word is read through $gp, so the unit needs -G8
   (given by its name). */
#include "common.h"

/* Word, byte and pointer views of the resident hero state at the offsets read here. */
typedef union { u8 b[0x2600]; s32 i[0x980]; u8 *ptr[0x980]; } Hero2E68;
#define H ((Hero2E68 *)D_00189E20)

extern u8 D_00189E20[];
extern u8 D_00152C00[];
/* A level object list: its count and its entry pointers. */
typedef struct { u8 pad[0x44]; s16 count; u8 pad46[0x18C - 0x46]; u8 *entries[1]; } ObjectTable;
extern ObjectTable D_L00_001BCAC0;
extern s32 D_L00_001A8F00;
extern s32 func_L00_002D6418(void);

/* Sets bit 0 of the halfword flags at +0x34 of the hero's main object, of the three objects of
   each of the seven hero slots (slot 0 is skipped when func_L00_002D6418 says so; in mode 2 a
   slot is skipped while a listed object has a zero +0xAA, in mode 6 slots 1 and 2 while the
   guard state is 0 or 3) and of the trailing objects; then clears bits 0x41 of the first slot
   object when the word at +0x1248 is 10, the mode is 0 and the object's +0x20 byte is set.
   func_L00_002D3068 clears bit 0 of the same objects. */
/* Turns on the same flag bit for the hero and all the objects attached to it, with a few exceptions for some modes. */
void func_L00_002D2E68(void)
{
    u8 *base;
    u8 *guard;
    u8 *slot;
    u8 *obj;
    u8 *hero;
    u8 *tail;
    s32 i;
    s32 count;
    s32 found;
    s32 mode;

    hero = H->ptr[0xC18 / 4];
    *(u16 *)(hero + 0x34) |= 1;
    guard = gHeroMoby_00152C00;
    for (i = 0; i < 7; i++) {
        base = gHeroState;
        if (i == 0 && IsHeroActionAllowed())
            continue;
        mode = D_L00_001A8F00;
        if (mode == 2) {
            found = 0;
            for (count = 0; count < D_L00_001BCAC0.count; count++) {
                if (*(s16 *)(D_L00_001BCAC0.entries[count] + 0xAA) == 0)
                    found = 1;
            }
            if (found)
                continue;
        }
        if (mode == 6 && (*(s16 *)(guard + 0x20) == 0 || *(s16 *)(guard + 0x20) == 3)
            && (u32)(i - 1) < 2)
            continue;
        slot = base + i * 0x50;
        obj = *(u8 **)(slot + 0x1220);
        if (obj) *(u16 *)(obj + 0x34) |= 1;
        obj = *(u8 **)(slot + 0x1224);
        if (obj) *(u16 *)(obj + 0x34) |= 1;
        obj = *(u8 **)(slot + 0x1228);
        if (obj) *(u16 *)(obj + 0x34) |= 1;
    }
    tail = H->ptr[0x131C / 4];
    if (tail) *(u16 *)(tail + 0x34) |= 1;
    if (H->b[0x22B4] == 1) {
        tail = H->ptr[0x1864 / 4];
        if (tail) *(u16 *)(tail + 0x34) |= 1;
    }
    if (H->i[0x1248 / 4] == 10) {
        tail = H->ptr[0x1220 / 4];
        if (tail && D_L00_001A8F00 == 0 && tail[0x20])
            *(u16 *)(tail + 0x34) &= ~0x41;
    }
}
