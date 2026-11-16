#include "include_asm.h"

#include "common.h"
typedef struct Task28E458 {
    u8 pad00[0x18];
    void (*update)(struct Task28E458 *);
    u8 pad1C[0x90 - 0x1C];
} Task28E458;
extern s32 g_weapon_wheel_slot_seven[] __attribute__((sda));
extern s32 g_cutscene_active_flag[] __attribute__((sda));
extern s32 g_hud_sprite_color_word[] __attribute__((sda));
extern s32 g_hud_record_active_a[] __attribute__((sda));
extern s32 g_hud_record_fade[] __attribute__((sda));
extern s32 g_hud_record_timer[] __attribute__((sda));
extern s32 g_current_game_mode[] __attribute__((sda));
extern Task28E458 g_hud_elements[];

void hud_update_record_handlers_pal(void) {
    Task28E458 *t;
    s32 i;

    if (g_weapon_wheel_slot_seven[1] != 0 || g_cutscene_active_flag[0] != 0) {
        g_weapon_wheel_slot_seven[1] = 0;
        return;
    }
    t = g_hud_elements;
    g_hud_sprite_color_word[0] = 0xFFFFF0;
    for (i = 12; i >= 0; i--) {
        if (t->update != 0) {
            t->update(t);
        }
        t++;
    }
    if ((g_hud_record_active_a[0] != 0 || g_hud_record_fade[0] != 0) && g_current_game_mode[0] == 0) {
        if (g_hud_record_active_a[0] != 0) {
            g_hud_record_fade[0] += 0x12;
            if (g_hud_record_fade[0] > 0x80) {
                g_hud_record_fade[0] = 0x80;
            }
        } else {
            g_hud_record_fade[0] -= 0x12;
            if (g_hud_record_fade[0] < 0) {
                g_hud_record_fade[0] = 0;
            }
        }
        if (g_hud_record_active_a[0] != 0) {
            g_hud_record_active_a[0]--;
        }
        if (g_hud_record_active_a[0] == 1000) {
            g_hud_record_active_a[0] = 0;
        }
    } else {
        g_hud_record_timer[0] = 100;
    }
}
