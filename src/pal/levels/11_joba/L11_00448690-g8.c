#include "include_asm.h"
#include "names.h"
typedef int s32;
typedef unsigned char u8;
extern s32 D_L11_001B1530 __attribute__((sda));
extern s32 D_L11_001B1540 __attribute__((sda));
extern s32 D_L11_001B1550 __attribute__((sda));
extern s32 D_L11_001B1560 __attribute__((sda));
extern void func_3004A8(void *);
extern void func_4882F0(void *, void *, s32, s32, s32);
extern void func_488268(s32, s32);
extern void func_4881A8(void *);
extern void func_488200(void *);
extern u8 D_L11_001BA8C0[];
extern u8 *g_moby_l11_table[3] __attribute__((sda));
extern u8 *g_group_id_lists[];
extern s32 D_L11_001B35B8 __attribute__((sda));
extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));
extern s32 arena_is_entity_far_in_direction(u8 *);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern u8 *arena_get_center_point(u8 *);
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);

/* arms the script bridge over the measured buffers and starts it on the shared slot */
void func_PAL_L11_00448BD8(void) {
    s32 buffer[4];
    func_3004A8(buffer);
    func_4882F0(&D_L11_001B1550, &D_L11_001B1560, 1, 0, 0);
    func_488268(2, 0x12C);
    func_4881A8(&D_L11_001B1530);
    func_488200(&D_L11_001B1540);
}
