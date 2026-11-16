#include "include_asm.h"





#include "common.h"
extern void func_324168(s32 a0, s32 a1);
extern void func_30D710(s32 a0, s32 a1);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern void func_30D710(s32 a0, s32 a1);

void object_restore_linked_after_scene_pal(char *a0)
{
    char *s0 = *(char **)(a0 + 0x68);

    func_324168(*(s32 *)(s0 + 0x18), *(s32 *)(s0 + 0x1C));
    func_30D710(0, -1);
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) |= 0x41;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x34) &= ~0x1000;
    *(s32 *)(*(s32 *)(s0 + 0x2C) + 0x98) = 0;
    *(u16 *)(*(s32 *)(s0 + 0x2C) + 0x96) = 0;
}

extern u8 *g_moby_record_base[] __attribute__((sda));
extern f32  FastAddRotations(f32 a0, f32 a1);
extern void hero_reset_position_and_direction_pal(char *a0, char *a1, s32 a2, s32 a3);
extern void SetHeroMode_pal(s32 a0, s32 a1, char *a2);
extern void cam_reset_entry(s32 a0);
extern void script_queue_keyed_request(s32 a0, s32 a1);
extern char g_hero_state[];
extern u8   g_clank_scene_done_flag;
typedef int TI128 __attribute__((mode(TI)));

/* The actor's per-frame update: the entry's flags are cleared, its record is copied
   and rotated by pi/3, and the resident block's float is turned the other way. */
void clank_scene_finish_pal(char *a0)
{
    char *s1 = *(char **)(a0 + 0x68);
    char *s0 = g_moby_record_base[0] + *(s32 *)s1 * 0x100;
    u16 v1 = *(u16 *)(s0 + 0x34);
    char *p = s0 + 0xF0;
    s32 v0 = *(s32 *)(s0 + 0x24);
    TI128 v2;
    f32 *f;
    char *base;

    v1 = (v1 & 0xFFBE) | 0x1000;
    *(u16 *)(s0 + 0x34) = v1;
    *(s32 *)(s0 + 0x98) = *(s32 *)(v0 + 0x10);
    qcopy(&v2, p);
    f = (f32 *)((char *)&v2 + 8);
    *f = FastAddRotations(*f, -1.0471977f);
    hero_reset_position_and_direction_pal(s0 + 0x10, (char *)&v2, 0, 1);
    SetHeroMode_pal(1, 0x3F, s0);
    base = g_hero_state;
    *(f32 *)(base + 0x98) = FastAddRotations(*(f32 *)(base + 0x98), 1.0471977f);
    cam_reset_entry(*(s32 *)(s1 + 0x28));
    script_queue_keyed_request(*(s32 *)(s1 + 0x20), -1);
    g_clank_scene_done_flag = 1;
}



