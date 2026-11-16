#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern u8 *g_moby_record_base __attribute__((sda));
extern u8 *g_entity_id_lists[];
extern s32 moby_handle_request_slot_state(s32);
extern u8 g_status_flag_b[0x40] __attribute__((sda));
extern s32 g_object_group_count[] __attribute__((sda));
typedef struct {
    u8 pad00[0x24];
    s32 key;
    s32 unk28;
    u8 pad2C[0x3C];
    s32 active;
} L03VoiceState;
extern L03VoiceState g_music_state;

/* Picks the free voice slot the entity asks for, unless the engine is busy
   or already holds that slot. */
void endako_boss_start_voice_line_pal(u8 *a0, s32 a1) {
    L03VoiceState *st = &g_music_state;
    s32 sel = a1;
    u8 *a3 = *(u8 **)(a0 + 0x68);
    u8 *slot;
    s32 *row;
    u32 v;

    if (st->active != 0) return;
    if (st->key != -1) return;
    if (sel == *(s32 *)(a3 + 0x40C)) return;
    slot = a3 + sel;
    row = (s32 *)(a3 + sel * 4);
    v = *(u32 *)((u8 *)row + 0x3D0);
    st->unk28 = 0;
    st->key = (v & 0x3FFF) + 0x7D0;
    *(u8 *)(slot + 0x410) = 1;
    *(s32 *)(a3 + 0x408) = 0x1F4;
    *(s32 *)(a3 + 0x40C) = sel;
}

