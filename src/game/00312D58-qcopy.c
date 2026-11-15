/* func_00312D58 in its own unit (flags in config/cflags.txt: -O2 -G0 -ffunction-sections -frac2-qcopy). */
#include "include_asm.h"
#include "names.h"

typedef int TI128_00312D58 __attribute__((mode(TI)));

extern void *func_0029EFD0(int id);
extern void func_002AB650(void *object);
extern void func_002A0488(void *object, int a1, int a2, int a3);
extern float func_002A7940(void);
extern void func_002A0F48(void *object);

typedef struct {
    char pad0[0x10];
    TI128_00312D58 data;
    char pad20[0x0C];
    float scale;
    unsigned char byte30;
    unsigned short half32;
    char pad34[0xC4];
    float valueF8;
} Object_00312D58;

/* Creates an effect object at the given spot, scaled by the given amount, with a random value set on it. */
void *func_00312D58(TI128_00312D58 *data, float scale)
{
    Object_00312D58 *object = (Object_00312D58 *)CreateMoby(0x307 /* moby class 775 */);

    if (object != 0) {
        CopyHeroField38ToMoby(object);
        set_moby_color(object, 0x28, 0x28, 0x46);
        object->scale = object->scale * scale;
        object->byte30 = 0xFF;
        object->half32 = 0x40;
        object->data = *data;
        object->valueF8 = RandomAngle();
        func_002A0F48(object);
    }
    return object;
}
