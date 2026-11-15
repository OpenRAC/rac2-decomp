#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned int u32;
typedef int TI128 __attribute__((mode(TI)));

/* The resident word the hero's key is read from; an array so the load keeps the
 * two-instruction `lui`/`lw` form instead of reusing the destination as the base. */
extern u32 g_hero_moby[];

/* The two resident slots this object can own; the hero's key selects the lower one.
 * Both addresses differ between the level-22 and level-23 placements, so they are
 * per-placement externals rather than level names. */
extern int ref_L22_003B8FE8_00 __attribute__((sda));

extern int ref_L22_003B8FE8_01 __attribute__((sda));

/* The level block the object arms, written as bare symbols through $at: each is sized past
 * the $gp limit so it keeps the absolute `lui`/`sw` form. */
extern s32 D_L22_001A8AB4[3] __attribute__((sda));

extern s32 D_L22_001A8AC4[3] __attribute__((sda));

extern long long D_L22_001A8AC8[2] __attribute__((sda));

extern long long D_L22_001A8AB8[2] __attribute__((sda));

extern s32 D_L22_001A8AB0;

extern s32 D_L22_001A8AC0;

/* a plain small extern: $gp in the delay slot reorg copies it into, absolute where it stays */
extern s32 D_L22_001A8FF0;

extern s16 gfx_add_point_light(TI128 *, s32, float, float);

extern u8 *CreateMoby(s32);

/* Allocates the object, records it in the word its key selects and fills its fields and the
 * level block; the caller's record is copied in when the level word is set. */
u8 *keyed_object_create(u8 *hero, TI128 *position) {
    u8 *obj;
    u8 *payload;
    s32 *slot;

    obj = CreateMoby(0x5F3 /* moby class 1523 */);
    slot = &ref_L22_003B8FE8_00;
    if (hero == (u8 *)g_hero_moby[0]) {
        slot = &ref_L22_003B8FE8_01;
    }
    if (obj != 0 && *slot == 0) {
        *(u8 *)(obj + 0x30) = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        *(u8 *)(obj + 0x31) = 1;
        *(u8 **)(obj + 0xB8) = hero;
        *(u8 *)(obj + 0x20) = 0;
        payload = *(u8 **)(obj + 0x68);
        *(TI128 *)(obj + 0x10) = *position;
        *slot = (s32)obj;
        D_L22_001A8AB4[0] = 0xFF;
        D_L22_001A8AC4[0] = 0x00FFFFFF;
        D_L22_001A8AC8[0] = 0x1F00000042LL;
        D_L22_001A8AB8[0] = 0;
        D_L22_001A8AB0 = 0;
        D_L22_001A8AC0 = 0;
        *(s32 *)(payload + 0x10) = 0;
        *(s16 *)(payload + 0x2C) = gfx_add_point_light(position, 0, 0.0f, 0.0f);
    }
    if (D_L22_001A8FF0 != 0) {
        *(u16 *)(obj + 0x34) = *(u16 *)(obj + 0x34) | 0x100;
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(hero + 0xC0);
        *(TI128 *)(obj + 0xD0) = *(TI128 *)(hero + 0xD0);
        *(TI128 *)(obj + 0xE0) = *(TI128 *)(hero + 0xE0);
    }
    return obj;
}
