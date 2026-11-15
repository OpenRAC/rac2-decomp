#include "include_asm.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0xC];
    void *buf;
    int used;
    char pad14[0x30 - 0x14];
} Slot_2FCF18;

typedef struct {
    float f0;
    float f4;
    float f8;
    float fC;
    float v10[4];
} Info_2FCF18;

extern Slot_2FCF18 D_L00_001C7040[];
extern Info_2FCF18 D_L00_001C6F40[];
extern char D_L00_001C71C0[][0x400];
extern void mem_fast_helper_b(void *, int);

/* Finds a free slot out of eight, stores a position and five values in it, and returns the slot number (or -1 if all are used). */
int part_l00_alloc_effect_slot_2(void *pos, float a, float b, float c, float d, float e)
{
    int i;
    Info_2FCF18 *info;
    Slot_2FCF18 *slot;

    for (i = 0; i < 8; i++) {
        if (D_L00_001C7040[i].used == 0)
            break;
    }
    if (i == 8)
        return -1;
    slot = &D_L00_001C7040[i];
    info = &D_L00_001C6F40[i];
    *(Q128 *)info->v10 = *(Q128 *)pos;
    info->v10[3] = a;
    info->f0 = c;
    info->f4 = d;
    info->f8 = e;
    info->fC = b;
    mem_fast_helper_b(slot, 0x30);
    slot->used = 1;
    slot->buf = D_L00_001C71C0[i];
    return i;
}
