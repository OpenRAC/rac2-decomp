#include "names.h"
/* Updates contact state, retaining the separate attached-owner pointer lifetime.
 * Position and fallback vectors are complete sixteen-byte transfers. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_turret_health_aim_scale __attribute__((sda));

extern u32 g_hero_state[] __attribute__((nosda));

extern void moby_set_state(char *, int, int);

extern void *part_find_owned_effect_slot(char *, int, int);

extern float moby_update_aim_target_strength(char *, char *);

extern int weapon_select_aim_target(char *, int, void *, int, float, float);
extern float ApproachValue(float *, float, float);

extern void turret_death_burst(char *);

/* Handles the turret's health and aim target: sets it up on the first frame, takes damage from hits, and blows up when its health reaches zero. */
void turret_update_health_aim(char *moby) {
    char *state;
    char *hit;
    u32 *hitter;
    short hit_class;
    float damage;

    state = *(char **)(moby + 0x68);
    if (*(u8 *)(moby + 0x20) == 0) {
        moby_set_state(moby, 1, -1);
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        *(int *)(moby + 0x98) = 0;
        qcopy((state + 0x180), (moby + 0x10));
        *(float *)(moby + 0x2C) =
            *(float *)(*(u32 *)(moby + 0x24) + 0x24) * g_turret_health_aim_scale;
        *(int *)(state + 0x1B8) = -1;
    }
    if (*(u8 *)(moby + 0x20) == 1) {
        return;
    }
    hit = part_find_owned_effect_slot(moby, 0x10000, 0);
    if (hit != 0) {
        hitter = *(u32 **)(hit + 0x20);
        if (hitter != 0) {
            hit_class = *(short *)((char *)hitter + 0xAA);
            if (hit_class == 0x12F2 /* moby class 4850 */ || hit_class == 0x12EF /* moby class 4847 */) {
                hit = 0;
            }
        }
    }
    damage = moby_update_aim_target_strength(moby, hit);
    ApproachValue((float *)(state + 0x20), 0.0f, damage);
    *(u8 *)(moby + 0xA8) = 0xFF;
    if (*(float *)(state + 0x20) == 0.0f) {
        turret_death_burst(moby);
        *(u8 *)(moby + 0xA8) = 0xFF;
        moby_set_state(moby, 1, -1);
        *(int *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
    }
    if (*(u8 *)(moby + 0x20) == 5) {
        return;
    }
    {
    char *owner = *(char **)(state + 0x1B0);
    if (owner != 0) {
        *(u32 *)(state + 0x150) = (u32)owner;
        qcopy((state + 0x140), (owner + 0x10));
        *(float *)(state + 0x148) = *(float *)(state + 0x148) + 0.5f;
        return;
    }
    }
    weapon_select_aim_target(moby, *(int *)(state + 0x160), 0, 0, 1024.0f, 37.0f);
    if (*(u32 *)(state + 0x150) != 0) {
        return;
    }
    {
        u32 *base = (u32 *)g_hero_state;
        *(u32 *)(state + 0x150) = base[0x8A4];
        qcopy((state + 0x140), ((char *)base + 0xD0));
    }
}
