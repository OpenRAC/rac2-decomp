#include "common.h"

typedef struct { u8 pad[0x80]; u8 data[0x270]; u8 more[0xC]; f32 value; } HeroBDA8;
extern HeroBDA8 g_hero_state;
extern u8 *g_moby_slot_table __attribute__((sda));
extern s32 IsPointInCuboid(u8 *, s32);
extern void vec_scale_to_length(u8 *, u8 *, f32);

/* Checks up to eight trigger boxes. When the player is inside one, it pushes the player along a set direction and sets a speed value. */
void push_zone_update(u8 *moby) {
    s32 *box_ids = *(s32 **)(moby + 0x68);
    s32 i;

    if (moby[0x20] == 0) {
        moby[0x30] = 0xFF;
        moby[0x20] = 1;
    }
    for (i = 0; i < 8; i++) {
        if (box_ids[i] != -1 && IsPointInCuboid(g_hero_state.data, box_ids[i]) != 0) {
            vec_scale_to_length(g_hero_state.data + 0x270, g_moby_slot_table + (box_ids[i] << 7), -1.0f);
            g_hero_state.value = 10.0f;
        }
    }
}
