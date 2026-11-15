#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char pad_0[478];
    short ground;
    unsigned char pad_1e0[316];
    float time;
    unsigned char pad_320[32];
    int moving;
    unsigned char pad_344[4];
    short allowed;
    unsigned char pad_34a[2];
    short lock;
    unsigned char pad_34e[336];
    unsigned char enabled;
    unsigned char pad_49f[4081];
    short action;
    unsigned char pad_1492[3];
    unsigned char primary;
    unsigned char pad_1496[1];
    unsigned char secondary;
    unsigned char pad_1498[2];
    unsigned char tertiary;
    unsigned char pad_149b[2];
    unsigned char saved;
    unsigned char pad_149e[3570];
    char * object;
    int mode;
    unsigned char pad_2298[28];
    unsigned char state;
    unsigned char pad_22b5[4];
    unsigned char flag;
    unsigned char pad_22ba[3];
    unsigned char blocked;
    unsigned char pad_22be[526];
    int busy;
} PlayerInput;
extern unsigned char g_hero_state[];
#define PLAYER ((PlayerInput *)D_00189E20)
extern unsigned char D_001A7B0B __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern int D_L03_001A9010 __attribute__((sda));
extern void mem_fast_helper_b(void *, int);
extern int hero_l03_enter_state(int, int);

/* Reads the hero's button action this frame and switches the hero to the matching state (jump, glide, swing and so on). */
void hero_handle_action_input(void)
{
    PlayerInput *player = PLAYER;
    short action = player->action;
    unsigned char saved = player->saved;
    int active;
    mem_fast_helper_b(&player->action, 16);
    player->saved = saved;
    player->action = action;
    player->flag = 0;
    player->allowed = 0;
    if (player->blocked) return;
    active = 0;
    if (player->moving ||
        (player->mode == 0x7b && player->time < 0.4f))
        active = 1;
    if (action == -1) return;
    if (action == 2 && PLAYER->ground == 0 &&
        (PLAYER->lock == 0 || PLAYER->time < 2.5f)) {
        PLAYER->secondary = 1;
        if (!PLAYER->state && D_001A7B0B)
            PLAYER->allowed = 1;
    }
    if (action == 1) PLAYER->primary = 1;
    if (action == 8) PLAYER->tertiary = 1;
    if (action == 12) PLAYER->tertiary = 1;
    if (PLAYER->primary) {
        if (active && PLAYER->state == 1 && PLAYER->mode != 0x7a) {
            hero_l03_enter_state(0x7a, 1);
        } else if (PLAYER->primary && active) {
            if (PLAYER->mode == 0x38 && !PLAYER->enabled) return;
            if (PLAYER->busy) hero_l03_enter_state(0x38, 1);
            else if (g_current_map_index == 2 && D_L03_001A9010) hero_l03_enter_state(0x7d, 1);
            else if (*(int *)(*(char **)(PLAYER->object + 0x24) + 0x1f0))
                hero_l03_enter_state(0x79, 1);
            else hero_l03_enter_state(0x39, 1);
        }
    }
}
