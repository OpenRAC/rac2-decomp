#include "include_asm.h"

#include "common.h"
extern u8 D_L12_001B9E00[];
extern u8 D_L12_00188660[];
extern s32 func_315148();
extern void moby_set_state();
extern s32 flag_is_third_pending_set();
extern s32 func_2F15C8(void *arg0);
extern s32 func_3205F8(void *arg0, s32 arg1, s32 arg2);
extern s32 func_364DF8(s32 arg0, s32 arg1, void *arg2);
extern f32 func_2F2950(f32 x, f32 y);
extern s32 D_L12_001B2E9C __attribute__((sda));
extern s32 D_L12_001B2E9C_2;
extern s32 g_current_map_index __attribute__((sda));
extern s32 GetFirstMobyInGroup(u8 **out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u8 **out, u32 value, s32 arg2, s32 arg3);
extern u8 g_item_owned_flags[] __attribute__((sda));
extern u8 D_001A7A40 MACRO_ADDR;
extern u32 D_001397DC, D_00138324;
extern u8 D_L12_001C0000[];
extern u8 *CreateMoby(int);
extern u8 *GetLocalizedString(int);
extern s32 *D_L12_001FEAC0[];
extern s32 point_in_path_xy(void *, void *, s32);

/* Advances the measured state machine of the given object. */
void func_PAL_L12_004172F0(u8 *object) {
    switch (object[0x20]) {
    case 0:
        if (flag_is_third_pending_set(object) != 0)
            moby_set_state(object, 1, -1);
        break;
    case 1:
        if (*(f32 *)(object + 0x18) < 160.0f)
            *(f32 *)(object + 0x18) = *(f32 *)(object + 0x18) + 0.10000001f;
        break;
    }
}

