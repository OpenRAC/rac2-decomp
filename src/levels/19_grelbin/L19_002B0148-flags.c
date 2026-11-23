#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
extern int g_current_map_index __attribute__((sda));
extern int g_hero_l19_special_state_flag __attribute__((sda));
extern u8 g_hero_input_enabled __attribute__((sda));
extern void mem_fast_helper_b(void *, int);
extern float math_fabs(float);
extern int hero_l19_set_move_state(int, int);
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
    u8 pad21e[0x318 - 0x21e];
    float t318, elapsed;
    u8 pad320[0x330 - 0x320];
    float t330;
    float jumpTime;
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
    u8 pad1492[2], flag1494;
    u8 attack, jump, jumpPressed, pad1498[2], hover, cancel, flag149c, saved;
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
    u8 pad24a0[0x24c4 - 0x24a0];
    float t24c4;
    u8 pad24c8[4];
    int health;
} PlayerInputView;
extern PlayerInputView g_hero_state;

/* Same body as func_L09_002AFC90, with this function's own callees. */
/* Reads the newest button command and sets the hero's jump, attack, hover and grab requests, starting an attack state when allowed. */
void hero_process_button_command(void)
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
        if (!g_hero_state.mode && g_hero_input_enabled) g_hero_state.pendingJump = 1;
    }
    if (command == 14) {
        g_hero_state.flag1494 = 1;
        g_hero_state.t24c4 = 0.2f;
        g_hero_state.t330 = g_hero_state.t318 + 0.2f;
    }
    if (command == 0) {
        float d = g_hero_state.t330 - g_hero_state.t318;

        g_hero_state.t24c4 = d;
        if (d < 0.85f && 0.25f < d) g_hero_state.request = 1;
        g_hero_state.flag1494 = 1;
    }
    if (command == 13) g_hero_state.flag149c = 1;
    if (command == 1) g_hero_state.attack = 1;
    if (command == 8) g_hero_state.hover = 1;
    if (command == 12) g_hero_state.hover = 1;
    if (g_hero_state.attack) {
        if (g_hero_state.attack && active &&
            (g_hero_state.state != 0x38 || g_hero_state.animationDone)) {
            if (g_hero_state.health) { hero_l19_set_move_state(0x38,1); return; }
            if (g_current_map_index == 2 && g_hero_l19_special_state_flag) { hero_l19_set_move_state(0x7d,1); return; }
            if (*(int *)(*(u8 **)(g_hero_state.object + 0x24) + 0x1f0)) { hero_l19_set_move_state(0x79,1); return; }
            hero_l19_set_move_state(0x39,1); return;
        }
    }
    if (g_hero_state.flag149c && g_hero_state.state != 0x7c &&
        math_fabs(g_hero_state.t330-(g_hero_state.position.f[2]+0.25f)) < 1.0f &&
        g_hero_state.t330-g_hero_state.position.f[2] > 0.0f &&
        (g_hero_state.motion.f[2] < 0.0f || g_hero_state.state == 0x7b)) {
        hero_l19_set_move_state(0x7c,1);
    }
}
