#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern u8 *g_moby_record_base __attribute__((sda));
extern s32 g_endako_boss_forced_behaviour __attribute__((sda));
extern u8 *SpawnSpinningSparkParticle(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern s32 flag_is_third_pending_set();
extern u8 *g_entity_id_lists[];
typedef struct {
    u8 pad00[0x30];
    s32 field30;
    s32 field34;
    u8 pad38[0x158];
    u8 *field190;
    u8 *field194;
} L03Block;
extern L03Block g_endako_state;
extern s32 g_hero_l03_mode __attribute__((sda));
extern void set_moby_color(u8 *a0, s32 a1, s32 a2, s32 a3);
extern s32 moby_pack_handle(u8 *a0);
extern void moby_set_light_color(u8 *a0, s32 a1);

/* Flashes a scripted light on the target moby during the boss cutscene timeline (PAL). */
void scripted_light_update_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    s32 old_count, new_count, rounded, phase;
    s32 red, green, blue;

    switch (moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        moby[0x20] = 1;
        return;
    case 1: {
        s32 hero_mode = g_hero_l03_mode;

        if (hero_mode == 2) {
            if (g_endako_state.field30 == 5) {
                if (g_endako_state.field34 < 10) {
                    *(u16 *)(g_endako_state.field194 + 0x7C) = 0x3F;
                }
            }
            if (g_endako_state.field30 == 7) {
                u8 *target = g_endako_state.field190;
                if (g_endako_state.field34 < 0x376) goto other;
                if (g_endako_state.field34 >= 0x3B3) goto other;
                old_count = *(s32 *)state;
                new_count = old_count + 1;
                *(s32 *)state = new_count;
                rounded = (new_count > -1) ? new_count : old_count + 4;
                rounded = (rounded >> 2) << 2;
                phase = new_count - rounded;
                if (phase < 3) {
                    red = 0;
                    green = 0;
                    blue = 0;
                } else {
                    red = 0xB0;
                    green = 0xB0;
                    blue = 0xF0;
                }
                set_moby_color(target, red, green, blue);
                return;
            other:
                if (g_endako_state.field34 < 0x395) {
                    *(s32 *)(state + 4) = moby_pack_handle(target);
                } else {
                    moby_set_light_color(target, *(s32 *)(state + 4));
                }
            }
        }
        return;
    }
    }
}
