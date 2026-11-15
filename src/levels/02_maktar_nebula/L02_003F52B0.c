#include "common.h"

/* Prefix view of the effect-position field; not a complete global layout. */
typedef struct { char pad[0xB0]; float effect_position[4]; } EffectPositionView;
extern EffectPositionView g_hero_state;
/* Keep the destination address as the assembler's absolute-address macro. */
extern char D_L02_001B3210[] __attribute__((sda));
extern char *D_L02_001AD410 __attribute__((sda));
extern void actor_collect_matching_indices(char *);
extern void sway_update_pieces(char *);
extern void actor_advance_cycle_timer(char *);
extern void hero_update_height_zone_flags(char *);
extern void set_scale_matrix(char *, float);
extern void moby_set_state(u8 *, s32, s32);

/* Updates this actor: sets up a fixed point and its camera on the first frame, then runs its per-frame checks. */
void camera_point_actor_update(char *moby) {
    switch (*(u8 *)(moby + 0x20)) {
    case 0: {
        EffectPositionView *hero_block = &g_hero_state;

        float *source;
        char *dest;
        hero_block->effect_position[1] = 200.0f;
        hero_block->effect_position[0] = 500.0f;
        hero_block->effect_position[2] = 500.0f;
        hero_block->effect_position[3] = 1.0f;
        source = hero_block->effect_position;
        dest = D_L02_001B3210;
        qcopy(dest, source);
        *(u8 *)(moby + 0x30) = 0xFF;
        actor_collect_matching_indices(moby);
        set_scale_matrix(D_L02_001AD410 + 0x40, 1.0f);
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1:
        sway_update_pieces(moby);
        actor_advance_cycle_timer(moby);
        hero_update_height_zone_flags(moby);
        break;
    }
}
