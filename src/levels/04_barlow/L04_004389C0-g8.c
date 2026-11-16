#include "include_asm.h"
#include "common.h"

extern int g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern char *g_pHeroMoby[];
extern s32 moby_count_group_not_in_state(u32, s32);
extern int flag_is_byte_set(void);
extern int PlayMobySound(int, int, char *);

/* A pickup's states: 0 takes the hero's flags, 1 waits until none of its four
   links is alive (or the zone byte says go), 2 fades it out, 4 is done. */
void barlow_linked_fade_out_update(u8 *obj)
{
    u8 *links = *(u8 **)(obj + 0x68);
    s32 i;

    if (obj[0x20] == 0) {
        *(u64 *)(obj + 0x38) = *(u64 *)(g_pHeroMoby[0] + 0x38);
        *(u16 *)(obj + 0x34) |= 0x800;
        obj[0x20] = 1;
    }
    if (obj[0x20] == 1) {
        s32 found = 0;
        for (i = 0; i < 4; i++) {
            if (moby_count_group_not_in_state(*(u32 *)(links + 4 * i), -1))
                found = 1;
        }
        if (*(u32 *)(links + 0x10) != 0) {
            if (flag_is_byte_set() != 0) {
                if (moby_count_group_not_in_state(*(u32 *)links, -1) == 0)
                    found = 0;
            }
        }
        if (found == 0 || (g_moby_group_flags[obj[0xB0] + (g_current_map_index << 4)] & 0x80)) {
            PlayMobySound(0, 0, (char *)obj);
            obj[0x20] = 2;
        }
    }
    if (obj[0x20] == 2) {
        f32 height = *(f32 *)(obj + 0x18);
        if (height >= 30.0f)
            *(f32 *)(obj + 0x18) = height - 0.28333336f;
        if (*(f32 *)(obj + 0x18) < 30.0f)
            obj[0x20] = 4;
    }
}
