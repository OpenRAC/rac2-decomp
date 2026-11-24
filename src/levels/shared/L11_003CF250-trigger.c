#include "common.h"

extern char g_hero_state[];
/* Read at +0xC0: a symbol-plus-offset address stays one two-instruction macro load, which reorg
 * cannot move into a branch delay slot. */
extern unsigned char g_unlocked_item_flags[] __attribute__((sda));
extern int FloatToInt(float);
extern float math_fast_sin_or_cos_b(float);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern int flag_set_first_pending(char *);
extern void cam_lock_entry(int);
extern int ForceClaimNotice(int, int, int);
extern int hero_l11_set_move_state(int, int);
extern float FastAddRotations(float, float);

/* Per-frame update of the Levitator Pad (moby class 2274). */
/* State 0 opens the trigger; state 1 reacts to the hero being on the object, or being in state
 * 0x82 inside its cuboid. Then pulses the object's colour, in the channel the flag selects. */
void levitator_l11_pad_update(char *obj)
{
    char *rig = *(char **)(obj + 0x68);
    char *hero, *other;
    int word, level, glow;
    float turn, pulse;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(unsigned short *)(obj + 0x34) |= 0x10;
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (flag_set_first_pending(obj) != 0) {
            word = *(int *)rig;
            if (word != -1) {
                cam_lock_entry(word);
                *(int *)rig = -1;
            }
        }
        hero = g_hero_state;
        if (*(char **)(hero + 0x33C) == obj && *(int *)(hero + 0x340) != 0) {
            if (g_unlocked_item_flags[0xC0] != 0) {
                ForceClaimNotice(0xC, 0x27F7, 1);
                *(short *)(hero + 0x1F2) = 0xA;
                turn = *(float *)(rig + 0xC);
                if (turn != 0.0f)
                    *(float *)(hero + 0x5B8) = turn;
            }
        } else {
            other = g_hero_state;
            if (*(int *)(other + 0x2294) == 0x82) {
                level = *(int *)(rig + 8);
                if (level >= 0 && IsPointInCuboid(other + 0x80, level) != 0)
                    hero_l11_set_move_state(6, 1);
            }
        }
        break;
    }
    if (*(unsigned char *)(obj + 0x31) != 0) {
        pulse = FastAddRotations(*(float *)(rig + 4), 0.10471977f);
        *(float *)(rig + 4) = pulse;
        glow = FloatToInt(math_fast_sin_or_cos_b(pulse) * 128.0f);
        if (glow > 0x80)
            glow = 0x80;
        else if (glow < 0x20)
            glow = 0x20;
        if (g_unlocked_item_flags[0xC0] != 0)
            *(int *)(obj + 0x78) = (glow << 8) | 0x80000000;
        else
            *(int *)(obj + 0x78) = glow | 0x80000000;
    }
}
