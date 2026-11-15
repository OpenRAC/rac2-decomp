#include "common.h"
extern u8 *D_L07_001B22DC __attribute__((sda));
extern void func_002AD5F8(u8 *,u8 *,u8 *,u8 *,u8 *,u8 *);
/* Places each of the four attached parts relative to the object. */
void func_L07_0040F6B8(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *outB = vars + 0x160;
    u8 *outA = vars + 0x120;
    s32 *ids = (s32 *)(vars + 0xA8);
    s32 i = 3;

    while (i >= 0) {
        if (*ids != -1) {
            u8 *part = gMobyArray_L07 + (*ids << 8);
            GetAttachmentRotationAngles(part, moby, part + 0x10, part + 0xF0, outA, outB);
        }
        outB += 0x10;
        outA += 0x10;
        i--;
        ids++;
    }
}
