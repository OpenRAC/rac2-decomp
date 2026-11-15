#include "common.h"

extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern f32  FastAddRotations(f32 moby, f32 a1);
extern void hero_reset_position_and_direction(char *moby, char *a1, s32 a2, s32 a3);
extern void SetHeroMode(s32 moby, s32 a1, char *a2);
extern void cam_reset_entry(s32 moby);
extern void script_queue_keyed_request(s32 moby, s32 a1);
extern char g_hero_state[];
extern u8   D_001395BF;

typedef int TI128 __attribute__((mode(TI)));

/* The actor's per-frame update: the entry's flags are cleared, its record is copied
   and rotated by pi/3, and the resident block's float is turned the other way. */
void clank_scene_finish(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *entry = D_L03_001B2A1C[0] + *(s32 *)vars * 0x100;
    u16 flags = *(u16 *)(entry + 0x34);
    char *recordPtr = entry + 0xF0;
    s32 classData = *(s32 *)(entry + 0x24);
    TI128 copy;
    f32 *zValue;
    char *base;

    flags = (flags & 0xFFBE) | 0x1000;
    *(u16 *)(entry + 0x34) = flags;
    *(s32 *)(entry + 0x98) = *(s32 *)(classData + 0x10);
    qcopy(&copy, recordPtr);
    zValue = (f32 *)((char *)&copy + 8);
    *zValue = FastAddRotations(*zValue, -1.0471977f);
    hero_reset_position_and_direction(entry + 0x10, (char *)&copy, 0, 1);
    SetHeroMode(1, 0x3F, entry);
    base = g_hero_state;
    *(f32 *)(base + 0x98) = FastAddRotations(*(f32 *)(base + 0x98), 1.0471977f);
    cam_reset_entry(*(s32 *)(vars + 0x28));
    script_queue_keyed_request(*(s32 *)(vars + 0x20), -1);
    D_001395BF = 1;
}
