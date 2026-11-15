#include "common.h"
extern u8 *g_moby_l07_array __attribute__((sda));
extern void moby_get_attachment_rotation_angles(u8 *,u8 *,u8 *,u8 *,u8 *,u8 *);
/* Places each of the four attached parts relative to the object. */
void boss_place_attached_parts(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 *outB = vars + 0x160;
    u8 *outA = vars + 0x120;
    s32 *ids = (s32 *)(vars + 0xA8);
    s32 i = 3;

    while (i >= 0) {
        if (*ids != -1) {
            u8 *part = g_moby_l07_array + (*ids << 8);
            moby_get_attachment_rotation_angles(part, moby, part + 0x10, part + 0xF0, outA, outB);
        }
        outB += 0x10;
        outA += 0x10;
        i--;
        ids++;
    }
}
