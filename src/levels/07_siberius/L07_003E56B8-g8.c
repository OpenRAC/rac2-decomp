#include "common.h"

extern int FloatToInt(float);
extern void moby_set_state(char *, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(char *);
extern int PlayMobySound(int, int, char *);
extern int moby_apply_damage_to_object(char *, void *, int);
extern void entity_set_group_alert_a(char *);
extern void entity_handle_death_or_respawn(char *);
extern void entity_follow_platform(char *);
/* Returns int (src/game/002B3BA8.c); the call's result register shapes the allocation after it. */
extern int weapon_select_aim_target(char *, int, void *, int, float, float);

/* Two tuning values: the first scaled by 1/3600, the second by 1/60. */
extern float D_L07_001B0AA0 __attribute__((sda));
extern float D_L07_001B0AA4 __attribute__((sda));
extern char D_L07_001B9200[];
/* The sound slots, 0x70 bytes each. */
extern char g_sound_state[];

/* In state 0, set up the object's state block (offsets in ascending order, with +0x98 first and
   +0x30 last, as retail's store schedule requires). Then: within 24 units of D_L07_001B9200 while
   +0x31 is set, call func_002A93B0; restart the sound when its slot no longer belongs to the
   object; run func_L07_003E5AC8 and func_L07_003E5D80 on a func_002B0ED8 count of two or more or
   when +0x2E is 2; and follow the platform at +0x260 unless the state byte is 8. */
/* Sets up the group entity on its first frame, then keeps its sound, alert checks and platform
   following going. */
void group_entity_base_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *slot;
    float accelStep, speedLimit;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        *(unsigned char *)(vars + 0x48) = FloatToInt(15.0f);
        *(unsigned char *)(vars + 0x4A) = FloatToInt(2.4f);
        *(unsigned char *)(vars + 0x60) = 7;
        *(unsigned char *)(vars + 0x2E) = 1;
        *(unsigned char *)(vars + 0xC7) = 1;
        accelStep = D_L07_001B0AA0;
        speedLimit = D_L07_001B0AA4;
        accelStep *= 0.00027777778f;
        speedLimit *= 0.016666667f;
        *(int *)(vars + 0x98) = 3;
        *(float *)(vars + 0x80) = 0.5f;
        *(int *)(vars + 0x84) = 0;
        *(float *)(vars + 0x8C) = 0.15f;
        *(float *)(vars + 0xA8) = 1.0f;
        *(float *)(vars + 0xAC) = 1.0f;
        *(float *)(vars + 0x120) = 0.45f;
        *(int *)(vars + 0x124) = 0;
        *(float *)(vars + 0x140) = accelStep;
        *(float *)(vars + 0x144) = accelStep;
        *(float *)(vars + 0x148) = speedLimit;
        *(int *)(vars + 0x158) |= 0x15;
        *(int *)(vars + 0x30) = 0;
        qcopy(vars + 0x220, moby + 0x10);
        if (*(short *)(vars + 0x218))
            moby_set_state(moby, 1, 0);
        else {
            *(int *)(moby + 0x98) = 0;
            *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) | 0x41) & 0xEFFF;
            moby_set_state(moby, 8, 4);
        }
    }
    if (*(unsigned char *)(moby + 0x31) && fast_vec_dist(moby + 0x10, D_L07_001B9200) < 24.0f) {
        moby_update_ground_check(moby);
        *(unsigned char *)(moby + 0x6F) = 22;
    }
    if (*(unsigned char *)(moby + 0x95) != 4) {
        slot = g_sound_state + *(int *)(vars + 0x264) * 0x70;
        if (*(char **)(slot + 0x88) != moby || !*(unsigned char *)(slot + 0x74))
            *(int *)(vars + 0x264) = PlayMobySound(1, 4, moby);
    }
    if (moby_apply_damage_to_object(moby, vars + 0x50, 0) >= 2 || *(unsigned char *)(vars + 0x2E) == 2) {
        entity_set_group_alert_a(moby);
        entity_handle_death_or_respawn(moby);
    }
    weapon_select_aim_target(moby, *(int *)(vars + 0x214), 0, 0, 0.0f, 0.0f);
    if (*(int *)(vars + 0x260) && *(unsigned char *)(moby + 0x20) != 8)
        entity_follow_platform(moby);
}
