#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
extern s32 g_moby_list_start __attribute__((sda));
extern s32 g_hero_l12_lock_flag __attribute__((sda));
extern u8 g_path_shooter_state[];
extern u8 g_path_zone_table[];
extern void func_L12_0031E1D0(s32, s32, s32);

/* Tries to take the shared attack slot for this group so only one member attacks at a time. */
void group_try_claim_attack_slot_pal(s32 moby_addr) {
    s32 moby = moby_addr;
    s32 vars = *(u32 *)(moby + 0x68);
    s32 owner_index = *(s32 *)(*(u32 *)(vars + 0x294));

    if (owner_index != -1) {
        s32 moby_base = g_moby_list_start;
        u8 *owner = (u8 *)((u32)moby_base + (owner_index << 8));

        if (owner != 0) {
            u8 state = *(u8 *)(owner + 0x20);

            if (state != 0xFE) {
                if (state != 0xFD) {
                    if (owner_index != ((moby - moby_base) >> 8))
                        return;
                }
            }
        }
    }
    func_L12_0031E1D0(moby, 0xF, 5);
    {
        s32 i = (moby - g_moby_list_start) >> 8;

        *(u16 *)(vars + 0x29C) = 0xFA;
        *(s32 *)(*(u32 *)(vars + 0x294)) = i;
    }
}

