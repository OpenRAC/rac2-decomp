#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern void func_2F3A80(void *, void *, void *);
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3AF0(void *, void *, f32);
extern s32 func_2F4BE0(f32);
extern void *func_332F58(s32);

/* A halfword read through $gp. */
extern u16 D_L22_001AA5EC __attribute__((sda));

/* Allocates a kind-0x1F record for a handle. Three vector helpers combine the given point
   with the handle's vector at +0x10, one step scaled by 0.25; the record takes the result,
   the point, the colour word and its low 24 bits, a helper's result plus 0x70, a 0x44 byte,
   a 2, a halfword and the handle. Does nothing when the allocation fails. */
void func_L22_003398B8(u32 colour, Vector point, u8 *handle)
{
    Vector target;
    Vector step;
    Vector offset;
    u8 *record;

    *(TI128 *)target = *(TI128 *)point;
    record = func_332F58(0x1F);
    if (record == 0)
        return;
    func_2F3AB0(offset, target, handle + 0x10);
    *(TI128 *)step = *(TI128 *)offset;
    func_2F3AF0(step, step, 0.25f);
    func_2F3A80(offset, handle + 0x10, step);
    *(TI128 *)(record + 0x10) = *(TI128 *)offset;
    *(TI128 *)(record + 0x20) = *(TI128 *)target;
    *(u32 *)(record + 0x4) = colour;
    *(u32 *)(record + 0xC) = colour & 0xFFFFFF;
    record[0x9] = func_2F4BE0(4.0f) + 0x70;
    record[0x3] = 0x44;
    record[0x1] = 2;
    *(u16 *)(record + 0xA) = D_L22_001AA5EC;
    *(u8 **)(record + 0x30) = handle;
}
