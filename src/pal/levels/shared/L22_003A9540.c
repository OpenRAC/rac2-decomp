#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];

/* shared native body of family cbc1388ebe801e68 */
/* Starts the animation in the given slot on an object, unless another one is already running, and sets its timer. (PAL: 50 Hz timings) */
void anim_start_slot_pal(u8 *moby, int slot) {
    u8 *state = D_001A63A8_4;
    u8 *vars = *(u8 **)(moby + 104);
    int bit;
    if (*(int *)(state + 104) != 0) return;
    if (*(int *)(state + 36) != -1) return;
    if (slot == *(int *)(vars + 1256)) return;
    bit = 1 << slot;
    { u8 *entry = vars + slot * 4; *(int *)(state + 36) = (*(int *)(entry + 1152) & 0x3fff) + 2000; }
    *(int *)(state + 40) = 0;
    *(int *)(vars + 1256) = slot;
    *(int *)(vars + 1252) = 1500;
    *(int *)(vars + 1248) |= bit;
}

extern int math_random_int_below(int a0);
extern void anim_start_free_slot_in_range(u8 *a0, int a1, int a2);
extern int math_random_int_below(int a0);

/* Arm one animation slot in the range [a1, a2]: a random slot of the range is
 * tried first and the next one after it, wrapping around, until a free slot
 * is found; when every slot of the range is taken, the range is cleared and
 * the last slot tried is armed.
 *
 * The mask lives in the controller at +0x4E0 of the object at +0x68.
 */
void anim_start_free_slot_in_range_pal(u8 *moby, int first, int last) {
    u8 *vars = *(u8 **)(moby + 0x68);
    int count;
    int offset;
    int i;

    if (last < first)
        return;
    count = last - first + 1;
    offset = math_random_int_below(count);
    for (i = 0; i < count; i++) {
        int slot = first + offset;
        if (((*(int *)(vars + 0x4E0) >> slot) ^ 1) & 1) {
            anim_start_slot(moby, slot);
            return;
        }
        offset = (offset + 1) % count;
    }
    i = 0;
    if (count > 0) {
        int mask = *(int *)(vars + 0x4E0);
        for (; i < count; i++) {
            mask &= ~(1 << (first + i));
        }
        *(int *)(vars + 0x4E0) = mask;
    }
    anim_start_slot(moby, first + offset);
}

