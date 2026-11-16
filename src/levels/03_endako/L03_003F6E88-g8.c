#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
extern void endako_boss_start_voice_line(u8 *, int);
extern int func_31B9F0(int);
extern float func_31BA88(float, float);
extern void func_31B640(int, int, int, int);
extern void func_32ECF8(void);
extern void func_2EEBF0(void *);
typedef struct { u8 pad[0x1B8]; int busy; u8 pad2[0x62]; short timer; u8 pad3[0x2074]; int action; int unknown; int weapon; } Player;
extern Player g_hero_state;
typedef struct { u8 pad[0x6C]; short id; u8 pad2[4]; short mode; } Voice;
extern Voice g_music_state;
extern float g_endako_boss_health_ratio __attribute__((sda));
/* Picks boss voice lines to play based on its health, its state and what the hero is doing. */
void endako_boss_play_voice_lines(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float ratio = *(float *)(state + 0x20) / (float)*(short *)(state + 0x24);
    if (entity[0x20] == 2 && !state[0x41D]) endako_boss_start_voice_line(entity, 13);
    if (entity[0x20] == 6 && !*(unsigned short *)(state + 0x410)) {
        if (func_31BA88(0, 1) > 0.3f) endako_boss_start_voice_line(entity, 1);
        else endako_boss_start_voice_line(entity, 0);
    }
    if (entity[0x20] >= 6) {
        if (entity[0x20] == 15 && !state[0x413]) endako_boss_start_voice_line(entity, 3);
        if (g_hero_state.action == 0x39 && !g_hero_state.busy) {
            int choice = func_31B9F0(3);
            if (choice == 0) endako_boss_start_voice_line(entity, 8);
            else if (choice == 1) {
                endako_boss_start_voice_line(entity, 9);
                g_hero_state.timer = 0xF0;
            }
        }
        if (g_hero_state.weapon == 7 && !g_hero_state.busy) {
            if (func_31B9F0(5) == 0 && !state[0x41A]) endako_boss_start_voice_line(entity, 10);
        }
        if (ratio < 0.8f && g_endako_boss_health_ratio >= 0.8f && !func_31B9F0(2)) {
            endako_boss_start_voice_line(entity, 2);
        } else if (ratio < 0.6f && g_endako_boss_health_ratio >= 0.6f && !func_31B9F0(2)) {
            endako_boss_start_voice_line(entity, 5);
        } else if (ratio < 0.4f && g_endako_boss_health_ratio >= 0.4f && !func_31B9F0(2)) {
            endako_boss_start_voice_line(entity, 6);
        } else if (ratio < 0.2f && g_endako_boss_health_ratio >= 0.2f && !func_31B9F0(2)) {
            endako_boss_start_voice_line(entity, 4);
        }
        g_endako_boss_health_ratio = ratio;
    }
    if (g_music_state.mode == 3 && g_music_state.id < 6000) {
        func_31B640(*(int *)(state + 0x2C4), 1, 0, 10);
        func_32ECF8();
    }
    func_2EEBF0(state + 0x408);
}
