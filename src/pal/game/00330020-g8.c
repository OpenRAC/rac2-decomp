#include "common.h"

/* func_PAL_00330020, the PAL copy of func_0032E4F0: the same C with the 50 Hz scale
   on the copied count; the count is stored first and the block's stores come in another order. */
typedef struct {
    unsigned char pad_000[0x218];
    int field_218;
    float field_21C;
    unsigned char pad_220[8];
    float field_228;
    float field_22C;
    int field_230;
    int field_234;
    int field_238;
} Ref_L00_0032E4F0_Block;

extern Ref_L00_0032E4F0_Block ref_L00_0032E4F0_00;
extern float D_001B0870 __attribute__((sda));
extern int D_001B0820 __attribute__((sda));
extern int D_001B0824 __attribute__((sda));
extern float ref_L00_0032E4F0_04;
extern void func_0027AB40(void);

void func_PAL_00330020(float size)
{
    Ref_L00_0032E4F0_Block *block;
    float zoom;

    D_001B0824 = ((s32)(D_001B0820) * 5 + 2) / 6;
    zoom = size * (D_001B0870 * 1024.0f);
    block = &ref_L00_0032E4F0_00;
    block->field_22C = 100.0f;
    block->field_218 = 0;
    block->field_230 = 0xFF;
    block->field_234 = 0xFF;
    block->field_238 = 0xFF;
    block->field_21C = zoom;
    ref_L00_0032E4F0_04 = size;
    block->field_228 = 255.0f;
    func_0027AB40();
}
