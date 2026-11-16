#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern unsigned char g_unlocked_item_flags[] __attribute__((sda));
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern int flag_set_first_pending(char *);
extern void cam_lock_entry(int);
extern int ForceClaimNotice(int, int, int);
extern int hero_set_action_state_pal(int, int);
extern float FastAddRotations(float, float);

/* State 0 opens the trigger; state 1 reacts to the hero being on the object, or being in state
 * 0x82 inside its cuboid. Then pulses the object's colour, in the channel the flag selects. */
void warp_ring_trigger_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *hero, *other;
    int cam_id, cuboid, alpha;
    float turn, pulse;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned short *)(moby + 0x34) |= 0x10;
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(moby) != 0) {
            cam_id = *(int *)vars;
            if (cam_id != -1) {
                cam_lock_entry(cam_id);
                *(int *)vars = -1;
            }
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == moby && *(int *)(hero + 0x340) != 0) {
            if (g_unlocked_item_flags[0xC0] != 0) {
                ForceClaimNotice(0xC, 0x1349, 1);
                *(short *)(hero + 0x1F2) = 0x8;
                turn = *(float *)(vars + 0xC);
                if (turn != 0.0f)
                    *(float *)(hero + 0x5B8) = turn;
            }
        } else {
            other = g_hero_state;
            if (*(int *)(other + 0x2294) == 0x82) {
                cuboid = *(int *)(vars + 8);
                if (cuboid >= 0 && IsPointInCuboid(other + 0x80, cuboid) != 0)
                    hero_set_action_state_pal(6, 1);
            }
        }
        break;
    }
    if (*(unsigned char *)(moby + 0x31) != 0) {
        pulse = FastAddRotations(*(float *)(vars + 4), 0.12566373f);
        *(float *)(vars + 4) = pulse;
        alpha = FloatToInt(math_fast_sin_or_cos_b(pulse) * 128.0f);
        if (alpha > 0x80)
            alpha = 0x80;
        else if (alpha < 0x20)
            alpha = 0x20;
        if (g_unlocked_item_flags[0xC0] != 0)
            *(int *)(moby + 0x78) = (alpha << 8) | 0x80000000;
        else
            *(int *)(moby + 0x78) = alpha | 0x80000000;
    }
}

