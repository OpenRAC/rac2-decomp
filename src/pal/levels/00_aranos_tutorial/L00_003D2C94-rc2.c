#include "include_asm.h"

#include "common.h"
extern s8 D_00189EA0[];
extern s32 ref_L00_003CF438_00(s32, s32);
extern void ref_L00_003CF438_01(s32, s32, void *);
extern f32 ref_L00_003CF438_02(f32);
extern f32 ref_L00_003CF438_03(f32);
extern void ref_L00_003CF438_04(void *, void *, void *);
extern void ref_L00_003CF438_05(void *);
typedef struct { f32 first; f32 second; s32 flag; s32 pad; } StackArgs;

void func_PAL_L00_003D3380(void *object) {
    s32 *state  = *(s32 **)((s8 *)object + 0x68);
    f32 angle ;
    f32 pi ;
    f32 ratio ;
    StackArgs args;
    s32 count;
    if (*(volatile u8 *)((s8 *)object + 0x20) == 0 && ref_L00_003CF438_00((s32)D_00189EA0, state[0]) != 0) {
        *(volatile u8 *)((s8 *)object + 0x20) = 1;
        state[1] = 0;
        ref_L00_003CF438_01(0, 0, object);
    }
    if (*(volatile u8 *)((s8 *)object + 0x20) == 1) {
        angle = *(volatile f32 *)((s8 *)object + 0xF8);
        pi = 3.141593f;
        ratio = 0.50000006f;
        args.first = ref_L00_003CF438_02(angle + pi) * ratio;
        args.second = ref_L00_003CF438_03(*(volatile f32 *)((s8 *)object + 0xF8) + pi) * ratio;
        args.flag = 0;
        ref_L00_003CF438_04((s8 *)object + 0x10, (s8 *)object + 0x10, &args);
        count = state[1] + 1;
        state[1] = count;
        if (count >= 0x65) {
            ref_L00_003CF438_05(object);
        }
    }
}
