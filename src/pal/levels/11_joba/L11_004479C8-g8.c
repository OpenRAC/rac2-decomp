#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef float f32;
extern s32 D_L11_001B1530 __attribute__((sda));
extern s32 D_L11_001B1540 __attribute__((sda));
extern s32 D_L11_001B1550 __attribute__((sda));
extern s32 D_L11_001B1560 __attribute__((sda));
extern u8 D_L11_001BA8C0[];
extern u8 *g_moby_l11_table[3] __attribute__((sda));
extern u8 *g_group_id_lists[];
extern s32 D_L11_001B35B8 __attribute__((sda));
extern u8 *D_L11_001B359C_abs[3] __attribute__((sda));
extern s32 arena_is_entity_far_in_direction(u8 *);
extern s32 moby_has_free_child_slot_state2(u8 *);
extern f32 D_L11_001B15AC __attribute__((sda));
extern f32 D_L11_001B15B0 __attribute__((sda));
extern f32 D_L11_001B15B4 __attribute__((sda));
extern f32 D_L11_001B15B8 __attribute__((sda));
extern u8 *arena_get_center_point(u8 *);
extern s32 D_L11_001B35B8_1[] __attribute__((sda));
extern f32 D_L11_001B1614 __attribute__((sda));
extern f32 D_L11_001B1618 __attribute__((sda));
extern s32 moby_is_state_six(u8 *);
extern s32 moby_is_state_one_cleared_vars(u8 *);
extern s32 math_random_int_below(s32);
extern const f32 D_L11_001B15BC __attribute__((sda));
extern const f32 D_L11_001B15C0 __attribute__((sda));
extern const f32 D_L11_001B15C4 __attribute__((sda));
extern const f32 D_L11_001B15C8 __attribute__((sda));
extern const f32 D_L11_001B15CC __attribute__((sda));
extern const f32 D_L11_001B15D0 __attribute__((sda));
extern const f32 D_L11_001B15D4 __attribute__((sda));
extern const f32 D_L11_001B15D8 __attribute__((sda));
extern const f32 D_L11_001B15DC __attribute__((sda));
extern const f32 D_L11_001B15E0 __attribute__((sda));
extern const f32 D_L11_001B15E4 __attribute__((sda));
extern const f32 D_L11_001B15E8 __attribute__((sda));
extern const f32 D_L11_001B15EC __attribute__((sda));
extern const f32 D_L11_001B15F0 __attribute__((sda));
extern const f32 D_L11_001B15F4 __attribute__((sda));
extern u8 g_hero_state[];
extern void *func_PAL_L00_002D7850(s32);
extern void cam_end_override(void *);
extern void cam_set_strength_and_steer_target(void *, f32, f32);
#define GUIDE (*(f32 **)(s + 0x170))
#define SET_GUIDE(x, y, z) (GUIDE[0] = (x), GUIDE[1] = (y), GUIDE[2] = (z))

void func_PAL_L11_00447C50(u8 *obj) {
    u8 *s = *(u8 **)(obj + 0x68);

    if (obj[0x20] == 8 || obj[0x20] == 9) {
        if (GUIDE == 0) {
            GUIDE = func_PAL_L00_002D7850(5);
        } else if (*(void **)(s + 0x180) != 0) {
            if (*(u8 **)(s + 0x184) == 0) {
                SET_GUIDE(D_L11_001B15BC, D_L11_001B15C0, D_L11_001B15C4);
                return;
            }
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4A)
                SET_GUIDE(D_L11_001B15D4, D_L11_001B15D8, D_L11_001B15DC);
            if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xD4B)
                SET_GUIDE(D_L11_001B15EC, D_L11_001B15F0, D_L11_001B15F4);
            else if (*(s16 *)(*(u8 **)(s + 0x184) + 0xAA) == 0xB3A)
                SET_GUIDE(D_L11_001B15E0, D_L11_001B15E4, D_L11_001B15E8);
        } else if (obj[0x20] == 9) {
            u8 *player = g_hero_state;
            SET_GUIDE(D_L11_001B15C8, D_L11_001B15CC, D_L11_001B15D0);
            if (*(f32 *)(player + 0x88) > ((f32 *)arena_get_center_point(obj))[2] + 16.0f) {
                if (*(u16 *)(obj + 0x96) < 417)
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.17453295f, 0.0f);
                else
                    cam_set_strength_and_steer_target(arena_get_center_point(obj), 0.008726647f, 0.0f);
            }
        } else {
            SET_GUIDE(D_L11_001B15BC, D_L11_001B15C0, D_L11_001B15C4);
        }
    } else {
        cam_end_override(GUIDE);
        GUIDE = 0;
    }
}
