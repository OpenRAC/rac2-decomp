#include "common.h"

/* SpawnShockwaveRingMoby: a type-0x70 moby with a random direction and its child state.
 * -g gives the pre-div.s nop (a line label before the multiply). */
typedef int TI __attribute__((mode(TI)));

extern char *CreateMoby(s32);
extern float math_random_float_range(float low, float high);
extern void set_moby_color(void *moby, u8 r, u8 g, u8 b);
extern float IntToFloat(s32 value);
extern void func_002A0F48(void *moby);

/* Creates a ring-shaped shockwave effect at a position. The ring starts with a random spin and grows in size. */
char *part_spawn_shockwave_ring(char *parent, char *pos, char *childpos, s32 index, u8 r, u8 g, u8 b, u8 a, f32 scale)
{
    char *moby;
    char *vars;
    char anglesCopy[16];
    float randomAngles[4];

    moby = CreateMoby(0x70 /* moby class 112 */);
    if (moby != 0) {
        vars = *(char **)(moby + 0x68);
        *(TI *)randomAngles = 0;
        randomAngles[0] = math_random_float_range(-3.1415927f, 3.1415927f);
        randomAngles[1] = math_random_float_range(-3.1415927f, 3.1415927f);
        randomAngles[2] = math_random_float_range(-3.1415927f, 3.1415927f);
        *(TI *)anglesCopy = *(TI *)randomAngles;
        *(u8 *)(moby + 0x20) = 0;
        *(u8 *)(moby + 0x23) = a;
        *(u8 *)(moby + 0x30) = 0xFF;
        *(u16 *)(moby + 0x32) = 0xFF;
        *(u8 *)(moby + 0x31) = 1;
        set_moby_color(moby, r, g, b);
        *(f32 *)(vars + 0x18) = *(f32 *)(moby + 0x2C) * scale;
        *(s32 *)(moby + 0x2C) = 0;
        *(char **)(vars + 0x10) = parent;
        qcopy(moby + 0x10, pos);
        qcopy(vars, childpos);
        qcopy(moby + 0xF0, anglesCopy);
        *(s32 *)(vars + 0x14) = index;
        *(u16 *)(vars + 0x1C) = *(u16 *)(vars + 0x14) - 4;
        *(f32 *)(moby + 0x2C) = IntToFloat(index - (short)(*(u16 *)(vars + 0x14) - 4))
                * *(f32 *)(vars + 0x18) / IntToFloat(*(s32 *)(vars + 0x14));
        *(u16 *)(vars + 0x1E) = a;
        func_002A0F48(moby);
    }
    return moby;
}
