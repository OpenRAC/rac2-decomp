#include "include_asm.h"

#include "common.h"
typedef int TI __attribute__((mode(TI)));
extern char *CreateMoby(s32);
extern float math_random_float_range(float low, float high);
extern void set_moby_color(void *moby, u8 r, u8 g, u8 b);
extern float IntToFloat(s32 value);
extern void func_002A0F48(void *moby);

char *func_PAL_003096D0(char *parent, char *pos, char *childpos, s32 index, u8 r, u8 g, u8 b, u8 a, f32 scale)
{
    char *moby;
    char *child;
    char tmp[16];
    float dir[3];

    moby = CreateMoby(0x70);
    if (moby != 0) {
        child = *(char **)(moby + 0x68);
        *(TI *)dir = 0;
        dir[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        dir[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        dir[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        *(TI *)tmp = *(TI *)dir;
        *(u8 *)(moby + 0x20) = 0;
        *(u8 *)(moby + 0x23) = a;
        *(u8 *)(moby + 0x30) = 0xFF;
        *(u16 *)(moby + 0x32) = 0xFF;
        *(u8 *)(moby + 0x31) = 1;
        set_moby_color(moby, r, g, b);
        *(f32 *)(child + 0x18) = *(f32 *)(moby + 0x2C) * scale;
        *(s32 *)(moby + 0x2C) = 0;
        *(char **)(child + 0x10) = parent;
        qcopy(moby + 0x10, pos);
        qcopy(child, childpos);
        qcopy(moby + 0xF0, tmp);
        *(s32 *)(child + 0x14) = index;
        *(u16 *)(child + 0x1C) = *(u16 *)(child + 0x14) - 3;
        *(f32 *)(moby + 0x2C) = IntToFloat(index - (short)(*(u16 *)(child + 0x14) - 3))
                * *(f32 *)(child + 0x18) / IntToFloat(*(s32 *)(child + 0x14));
        *(u16 *)(child + 0x1E) = a;
        func_002A0F48(moby);
    }
    return moby;
}
