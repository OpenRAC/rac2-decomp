#include "include_asm.h"





#include "common.h"
extern void func_324168(s32 a0, s32 a1);
extern void func_30D710(s32 a0, s32 a1);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern void func_30D710(s32 a0, s32 a1);

/* Restores the linked object after the scene: puts the hero state back, shows the object again
   and clears its timer. */
void object_restore_linked_after_scene_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    func_324168(*(s32 *)(vars + 0x18), *(s32 *)(vars + 0x1C));
    func_30D710(0, -1);
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x34) |= 0x41;
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x34) &= ~0x1000;
    *(s32 *)(*(s32 *)(vars + 0x2C) + 0x98) = 0;
    *(u16 *)(*(s32 *)(vars + 0x2C) + 0x96) = 0;
}

extern u8 *g_moby_record_base[] __attribute__((sda));
extern f32  FastAddRotations(f32 moby, f32 a1);
extern void hero_reset_position_and_direction_pal(char *moby, char *a1, s32 a2, s32 a3);
extern void SetHeroMode_pal(s32 moby, s32 a1, char *a2);
extern void cam_reset_entry(s32 moby);
extern void script_queue_keyed_request(s32 moby, s32 a1);
extern char g_hero_state[];
extern u8   g_clank_scene_done_flag;
typedef int TI128 __attribute__((mode(TI)));

/* The actor's per-frame update: the entry's flags are cleared, its record is copied
   and rotated by pi/3, and the resident block's float is turned the other way. */
void clank_scene_finish_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *record = g_moby_record_base[0] + *(s32 *)vars * 0x100;
    u16 flags = *(u16 *)(record + 0x34);
    char *rotation_ptr = record + 0xF0;
    s32 info_ptr = *(s32 *)(record + 0x24);
    TI128 rotation;
    f32 *yaw;
    char *hero_base;

    flags = (flags & 0xFFBE) | 0x1000;
    *(u16 *)(record + 0x34) = flags;
    *(s32 *)(record + 0x98) = *(s32 *)(info_ptr + 0x10);
    qcopy(&rotation, rotation_ptr);
    yaw = (f32 *)((char *)&rotation + 8);
    *yaw = FastAddRotations(*yaw, -1.0471977f);
    hero_reset_position_and_direction_pal(record + 0x10, (char *)&rotation, 0, 1);
    SetHeroMode_pal(1, 0x3F, record);
    hero_base = g_hero_state;
    *(f32 *)(hero_base + 0x98) = FastAddRotations(*(f32 *)(hero_base + 0x98), 1.0471977f);
    cam_reset_entry(*(s32 *)(vars + 0x28));
    script_queue_keyed_request(*(s32 *)(vars + 0x20), -1);
    g_clank_scene_done_flag = 1;
}



