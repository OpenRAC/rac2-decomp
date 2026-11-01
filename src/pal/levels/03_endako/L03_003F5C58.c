#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern u8 *D_L03_001FB5A0[];
extern void func_L02_00327350(s32, s32);
extern void func_00288308(s32);
extern s32 func_002AD860(s32);
extern void func_0029F338(u8 *);
extern void func_0029B3E0(s32, s32);
extern u8 D_001A7B08[0x40] __attribute__((sda));
extern s32 D_L03_001B2A38[] __attribute__((sda));

/* Raises the two flags, sets the entity up from the state's words 0x58 and 0x5C, runs the two
 * boot steps with 13 (func_002AD860 returns a value that the caller drops; declaring it that way
 * is what fixes the register choice of the table address), then hands every entity of the
 * state's group (word 0x80) to func_0029F338 and ends with func_0029B3E0(0, -1). */
void func_PAL_L03_003F5C58(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u16 *p;
    u8 *e;

    func_L02_00327350(*(s32 *)(state + 0x58), *(s32 *)(state + 0x5C));
    D_001A7B08[0x04] = 1;
    D_001A7B08[0x3C] = 1;
    func_00288308(13);
    func_002AD860(13);
    for (p = (u16 *)D_L03_001FB5A0[*(s32 *)(state + 0x80)];
         (*(s32 *)(state + 0x80) & 0xFF) != 0xFF && *(s32 *)(state + 0x80) <= D_L03_001B2A38[0] &&
         p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)D_L03_001FB5A0[*(s32 *)(state + 0x80)]);
         p++) {
        e = D_L03_001B2A1C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        func_0029F338(e);
    }
    func_0029B3E0(0, -1);
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003F8E58);



typedef unsigned int u32;
extern void func_320318(void *entity, void *target);
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern float func_2F0148(int a);
extern void func_2FD088(int a, int b, float f);
extern void func_2E77F0(void *fn, void *entity);
extern void func_L03_003F5B70(u8 *entity);
extern void func_L03_003F6158(u8 *entity);
extern void func_L03_003F64E8(u8 *entity);
extern void func_L03_003F6610(u8 *entity);
extern void func_L03_003F6748(u8 *entity);
extern void func_L03_003F6948(u8 *entity);
extern void func_L03_003F6BA8(u8 *entity);

/* ticks the entity's sub-states, feeds the 0x95 counter to the engine and
 * re-arms its 200-second timer */
void func_PAL_L03_003FA8D8(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u32 timer;

    func_320318(entity, state + 0x70);
    func_L03_003F5B70(entity);
    func_L03_003F64E8(entity);
    func_L03_003F6610(entity);
    func_L03_003F6748(entity);
    func_L03_003F6158(entity);
    if (*(u8 *)(entity + 0x95) >= 2)
        func_2FD088(5, 0, *(float *)(state + 0x20) / func_2F0148(*(s16 *)(state + 0x24)));
    if (*(s32 *)(state + 0x3BC) != 0)
        func_2E77F0(func_L03_003F6948, entity);
    if (*(u8 *)(entity + 0x31) != 0)
        func_2E77F0(func_L03_003F6BA8, entity);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE) *(u16 *)(entity + 0x96) = (u16)(timer + 1);
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003FAB20);
