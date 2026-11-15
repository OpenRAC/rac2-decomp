#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern int g_current_map_index __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));
extern void mem_fast_helper_b(void *, int);
extern float math_fabs(float);
extern int hero_l07_enter_state(int, int);
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword word; float f[4]; } Vector;
typedef struct {
    u8 prefix[0x80];
    Vector position;
    u8 pad90[0xf0 - 0x90];
    Vector velocity, pad100, motion;
    u8 pad120[0x1dc - 0x120];
    short timer, inputLock;
    u8 pad1e0[0x21c - 0x1e0];
    short soundTimer;
    u8 pad21e[0x31c - 0x21e];
    float elapsed;
    u8 pad320[0x330 - 0x320];
    float jumpTime2, jumpTime;
    u8 pad338[8];
    int busy;
    u8 pad344[4];
    short pendingJump;
    u8 pad34a[2];
    short jumpCount;
    u8 pad34e[0x49e - 0x34e];
    u8 animationDone;
    u8 pad49f[0x1490 - 0x49f];
    short command;
    u8 pad1492a, attack, pad1494[2], jump, jumpPressed, pad1498[2], hover, cancel, flag149c, saved;
    u8 pad149e[0x1500 - 0x149e];
    int interrupted;
    u8 pad1504[0x2290 - 0x1504];
    u8 *object;
    int state, phase, movement;
    u8 pad22a0[0x22b4 - 0x22a0];
    u8 mode;
    u8 pad22b5[0x22b9 - 0x22b5];
    u8 request;
    u8 pad22ba[3];
    u8 disabled;
    u8 pad22be[0x249c - 0x22be];
    u8 *contact;
    u8 pad24a0[0x24cc - 0x24a0];
    int health;
} PlayerInputView;
extern PlayerInputView g_hero_state;

/* Hand-adapted from func_L01_002ADDC8. */
/* Reads the newest button command and starts the matching hero action, such as an attack, a hover or a ledge grab. */
void hero_queue_action_from_input(void)
{
    short command = g_hero_state.command;
    u8 saved = g_hero_state.saved;
    int active;

    mem_fast_helper_b(&g_hero_state.command, 16);
    g_hero_state.command = command;
    g_hero_state.saved = saved;
    g_hero_state.request = 0;
    g_hero_state.pendingJump = 0;
    if (g_hero_state.disabled) return;
    active = 0;
    if (g_hero_state.busy || (g_hero_state.state == 0x7b && g_hero_state.elapsed < 0.4f)) active = 1;
    if (command == -1) return;
    if (command == 2 && !g_hero_state.inputLock &&
        (!g_hero_state.jumpCount || g_hero_state.elapsed < 2.5f)) {
        g_hero_state.jumpPressed = 1;
        if (!g_hero_state.mode && D_001A7B0B) g_hero_state.pendingJump = 1;
    }
    if (command == 3) g_hero_state.jump = 1;
    if (command == 11) g_hero_state.cancel = 1;
    if (command == 4) g_hero_state.attack = 1;
    if (command == 13) g_hero_state.flag149c = 1;
    if (command == 8) g_hero_state.hover = 1;
    if (command == 12) g_hero_state.hover = 1;
    if (g_hero_state.attack && active && g_hero_state.movement != 16 && g_hero_state.movement != 20 &&
        g_hero_state.movement != 7) {
        hero_l07_enter_state(0x30, 1);
        return;
    }
    if (g_hero_state.flag149c && g_hero_state.state != 0x7c &&
        math_fabs(g_hero_state.jumpTime2-(g_hero_state.position.f[2]+0.25f)) < 1.0f &&
        g_hero_state.jumpTime2-g_hero_state.position.f[2] > 0.0f &&
        (g_hero_state.motion.f[2] < 0.0f || g_hero_state.state == 0x7b)) {
        hero_l07_enter_state(0x7c,1); return;
    }
    if (g_hero_state.jump && g_hero_state.state != 0x65 && g_hero_state.state != 0x78 &&
        math_fabs(g_hero_state.jumpTime-(g_hero_state.position.f[2]+0.25f)) < 1.0f &&
        g_hero_state.jumpTime-g_hero_state.position.f[2] > 0.0f &&
        (g_hero_state.state != 0x66 || g_hero_state.animationDone) &&
        (g_hero_state.motion.f[2] < 0.0f || g_hero_state.state == 0x7b)) {
        if (!g_hero_state.health) { hero_l07_enter_state(0x78,1); return; }
        hero_l07_enter_state(0x65,1); return;
    }
    if (!g_hero_state.cancel || g_hero_state.state == 0x78 || g_hero_state.state == 0x74) return;
    if (!(math_fabs(g_hero_state.jumpTime-(g_hero_state.position.f[2]+0.25f)) < 1.0f)) return;
    if (!(g_hero_state.jumpTime-g_hero_state.position.f[2] > 0.0f)) return;
    if (!(g_hero_state.motion.f[2] < 0.0f) && g_hero_state.state != 0x7b) return;
    if (g_current_map_index == 13) {
        hero_l07_enter_state(0x74, 1);
        return;
    }
    hero_l07_enter_state(0x78, 1);
}
