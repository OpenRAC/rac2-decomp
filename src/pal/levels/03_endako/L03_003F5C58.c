#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef int s32;
extern u8 *g_moby_record_base __attribute__((sda));
extern u8 *g_entity_id_lists[];
extern void part_start_record_effect_by_index(s32, s32);
extern void help_unlock_entry(s32);
extern s32 moby_handle_request_slot_state(s32);
extern void moby_mark_spawned(u8 *);
extern int MemcardSave(s32, s32);
extern u8 g_status_flag_b[0x40] __attribute__((sda));
extern s32 g_object_group_count[] __attribute__((sda));

/* Raises the two flags, sets the entity up from the state's words 0x58 and 0x5C, runs the two
 * boot steps with 13 (func_002AD860 returns a value that the caller drops; declaring it that way
 * is what fixes the register choice of the table address), then hands every entity of the
 * state's group (word 0x80) to func_0029F338 and ends with func_0029B3E0(0, -1). */
void endako_boss_start_area_objects_pal(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u16 *p;
    u8 *e;

    part_start_record_effect_by_index(*(s32 *)(state + 0x58), *(s32 *)(state + 0x5C));
    g_status_flag_b[0x04] = 1;
    g_status_flag_b[0x3C] = 1;
    help_unlock_entry(13);
    moby_handle_request_slot_state(13);
    for (p = (u16 *)g_entity_id_lists[*(s32 *)(state + 0x80)];
         (*(s32 *)(state + 0x80) & 0xFF) != 0xFF && *(s32 *)(state + 0x80) <= g_object_group_count[0] &&
         p != 0 && ((p != 0 && (s16)p[-1] >= 0) || p == (u16 *)g_entity_id_lists[*(s32 *)(state + 0x80)]);
         p++) {
        e = g_moby_record_base + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        moby_mark_spawned(e);
    }
    MemcardSave(0, -1);
}




typedef unsigned int u32;
extern void func_320318(void *entity, void *target);
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern float func_2F0148(int a);
extern void func_2FD088(int a, int b, float f);
extern void func_2E77F0(void *fn, void *entity);
extern void endako_boss_move_along_path(u8 *entity);
extern void endako_boss_update_attachment(u8 *entity);
extern void endako_boss_ease_view_angle(u8 *entity);
extern void endako_boss_blend_parts(u8 *entity);
extern void endako_wake_objects_low_counters(u8 *entity);
extern void endako_boss_draw_target_markers(u8 *entity);
extern void gfx_draw_beam_quad_packets(u8 *entity);

/* ticks the entity's sub-states, feeds the 0x95 counter to the engine and
 * re-arms its 200-second timer */
void endako_boss_update_helpers_pal(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u32 timer;

    func_320318(entity, state + 0x70);
    endako_boss_move_along_path(entity);
    endako_boss_ease_view_angle(entity);
    endako_boss_blend_parts(entity);
    endako_wake_objects_low_counters(entity);
    endako_boss_update_attachment(entity);
    if (*(u8 *)(entity + 0x95) >= 2)
        func_2FD088(5, 0, *(float *)(state + 0x20) / func_2F0148(*(s16 *)(state + 0x24)));
    if (*(s32 *)(state + 0x3BC) != 0)
        func_2E77F0(endako_boss_draw_target_markers, entity);
    if (*(u8 *)(entity + 0x31) != 0)
        func_2E77F0(gfx_draw_beam_quad_packets, entity);
    timer = *(u16 *)(entity + 0x96);
    if (timer <= 0xFFFE) *(u16 *)(entity + 0x96) = (u16)(timer + 1);
}


