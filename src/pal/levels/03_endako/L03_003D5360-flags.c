#include "include_asm.h"

#include "common.h"
extern int MemcardSave(s32 a0, s32 a1);
extern s32  func_32AB10(char *a0);
extern s32  func_360A80(s32 a0, s32 a1, char *a2);
extern void moby_mark_spawned(void *a0);
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *g_moby_record_base;
extern u8   g_clank_scene_done_flag;
extern void hero_reset_position_and_direction_pal(char *a0, char *a1, s32 a2, s32 a3);
extern void script_queue_keyed_request(s32 a0, s32 a1);
extern char D_00189E20_11[];
extern u8   g_remote_view_done_flag;
extern u8   g_barlow_hint_inside_flag;
extern u8   g_unused_byte_c;
extern u8   g_unused_byte_a;
extern u8   g_unused_byte_d;
extern u8   g_unused_byte_b;
extern u8   g_unused_byte_e;
extern void hero_reset_carried_objects(s32 a0);
extern void moby_mark_table_entry_flagged(s32 a0);
extern void level_capture_checkpoint_state(char *a0, char *a1);
extern int MemcardSave(s32 a0, s32 a1);
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

void console_remote_view_cleanup_pal(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2;
    void *p;

    hero_reset_carried_objects(0);
    s2 = D_00189E20_11;
    *(u16 *)(s2 + 0x24FC) = 0;
    moby_mark_table_entry_flagged(*(u8 *)(s0 + 0xB0));
    g_remote_view_done_flag = 1;
    /* Resident bytes shared by all programs, written at their constant addresses
       (retail's lui $at,0x1A; sb form), as in 0033CB18.c. */
    *(u8 *)0x1A7BBA = 1;
    *(u8 *)0x1A7B83 = 1;
    *(u8 *)0x1A7BBB = 1;
    *(u8 *)0x1A7B84 = 1;
    *(u8 *)0x1A7BBC = 1;
    *(u8 *)0x1A7B82 = 1;
    hero_reset_position_and_direction_pal(s0 + 0x10, s0 + 0xF0, 0, 1);
    p = *(void **)(s1 + 0x2C);
    if (p != 0) {
        moby_mark_spawned(p);
    }
    moby_mark_spawned(D_L03_001B2A1C_tbl[0] + (*(s32 *)s1 << 8));
    *(s32 *)(s0 + 0x78) = 0x80468CDC;
    script_queue_keyed_request(*(s32 *)(s1 + 0x24), -1);
    level_capture_checkpoint_state(s2 + 0x80, s2 + 0x90);
    MemcardSave(0, -1);
}
