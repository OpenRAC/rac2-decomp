#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern char *func_L22_003FB1F8(char *, TI128 *, s32, float);
extern char *func_L22_003FC780(char *, TI128 *, s32, float);
extern char *func_L22_003FD1E8(char *, TI128 *, s32, float);

/* The level's spawned-object rows (three kinds of 60 words), their counts and the total. */
extern s32 ref_L22_003A39C8_00[3][60];
extern s32 ref_L22_003A39C8_01[3] MACRO_ADDR;
extern s32 ref_L22_003A39C8_02 MACRO_ADDR;
extern float ref_L22_003A39C8_03 __attribute__((sda));
extern float ref_L22_003A39C8_04 __attribute__((sda));
extern float ref_L22_003A39C8_05 __attribute__((sda));

/* Spawns an object of kind TYPE at POS in the first free slot of its row, counts it, and gives
 * it the position as it was on entry. Returns the slot index, or -1 when the row is full.
 * The level 22/23 copy of func_L23_0041C8C0, with a five-way switch. */
/* Creates a pickup of the given kind at a position, in the first free place of its row. Returns the place number or -1 when the row is full. */
s32 func_L22_003A39C8(char *obj, TI128 *pos, s32 type, s32 spawnArg)
{
    float saved[4] __attribute__((aligned(16)));
    char *slot;
    s32 i;

    do {
        *(TI128 *)saved = *pos;
    } while (0);
    for (i = 0; i < 50; i++) {
        if (ref_L22_003A39C8_00[type][i] == 0)
            break;
        if (i == 49) {
            i = -1;
            break;
        }
    }
    if (i != -1) {
        switch (type) {
        case 0:
            ref_L22_003A39C8_00[type][i] = (s32)SpawnLinkedScaledObject(obj, pos, spawnArg, ref_L22_003A39C8_03);
            break;
        case 1:
            ref_L22_003A39C8_00[type][i] = (s32)SpawnLinkedScaledObjectB(obj, pos, spawnArg, ref_L22_003A39C8_04);
            break;
        case 3:
            ref_L22_003A39C8_00[type][i] = (s32)SpawnLinkedScaledObjectB(obj, pos, spawnArg, ref_L22_003A39C8_04);
            break;
        case 2:
        case 4:
            ref_L22_003A39C8_00[type][i] = (s32)SpawnLinkedScaledObjectC(obj, pos, spawnArg, ref_L22_003A39C8_05);
            break;
        }
        slot = (char *)ref_L22_003A39C8_00[type][i];
        if (slot != 0) {
            ref_L22_003A39C8_02++;
            ref_L22_003A39C8_01[type]++;
            *(TI128 *)(slot + 0x10) = *(TI128 *)saved;
        }
    }
    return i;
}
