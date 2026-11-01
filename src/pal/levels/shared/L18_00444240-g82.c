#include "include_asm.h"

typedef unsigned char u8;
typedef signed int s32;
typedef int TI128 __attribute__((mode(TI)));
extern s32 D_L18_001B2348;
extern u8 D_L18_002BD9B0[];
extern s32 func_002A77E0(s32);
extern void func_00283098(void *, const void *, const void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L18_0043F040(u8 *);

void func_PAL_L18_00444398(u8 *obj) {
    u8 *state;
    u8 *dst;
    u8 *src;
    TI128 scratch;
    s32 i;
    s32 v = D_L18_001B2348;
    s32 r = v % 50;

    state = *(u8 **)(obj + 0x68);
    if (r) {
        /* the level's frame counter has not reached its turn yet */
    } else {
        *(s32 *)(state + 0x160) = func_002A77E0(6);
        *(s32 *)(state + 0x164) = func_002A77E0(6);
    }
    dst = obj + 0x10;
    src = obj + 0xC0;
    i = *(s32 *)(state + 0x160);
    func_00283098(&scratch, D_L18_002BD9B0 + i * 16, src);
    func_00282CC0(&scratch, dst, &scratch);
    *(TI128 *)(state + 0x10) = *(TI128 *)&scratch;
    i = *(s32 *)(state + 0x164);
    func_00283098(&scratch, D_L18_002BD9B0 + i * 16, src);
    func_00282CC0(&scratch, dst, &scratch);
    *(TI128 *)(state + 0xB0) = *(TI128 *)&scratch;
    func_L18_0043F040(obj);
}
