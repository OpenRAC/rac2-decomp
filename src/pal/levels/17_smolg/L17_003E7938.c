#include "include_asm.h"

#include "common.h"
extern s32 D_L17_001FE880[];
extern s32 func_31B160(s32);
extern f32 func_2EF0B0(s32, s32);
extern s32 D_L17_001B2748 __attribute__((sda));
extern s32 func_2F0108(u32, u32, f32);
extern f32 func_00283198(f32);
extern s32 D_L17_001B2C1C __attribute__((sda));
extern s32 D_L17_001C0018;
extern s32 func_2DF570(s32, s32, s32, s32, s32);
extern f32 func_00282C48(f32);
extern f32 D_L17_001B04BC SDATA(D_L17_001B04BC);
extern f32 func_00283248(f32, f32);
extern f32 func_00283C80(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_002AA2E8(void *, f32, f32);
extern u16 *D_L17_001FB720[];
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
extern s32 D_L17_001B2C38[] __attribute__((sda));
typedef struct {
    u8 pad[0x43C];
    s32 group;
    s32 mode;
} L17GroupState;

/* Walks the id list of the state's group and sets the state's mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
void func_PAL_L17_003E7938(u8 *a0)
{
    L17GroupState *state = *(L17GroupState **)(a0 + 0x68);
    u16 *p;
    u8 *e;

    for (p = D_L17_001FB720[state->group];
         (state->group & 0xFF) != 0xFF && state->group <= D_L17_001B2C38[0] && p != 0 &&
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L17_001FB720[state->group]);
         p++) {
        e = D_L17_001B2C1C_base[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        state->mode = 0x3E;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L17_003E79D8);


