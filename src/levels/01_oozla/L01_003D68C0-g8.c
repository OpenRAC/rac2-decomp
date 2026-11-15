#include "common.h"

typedef struct {
    int active;
    int timer;
} OozlaCountdown;

typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0x10];
    u8 visible;
    u16 field32;
    u16 flags;
    u8 pad36[0x32];
    OozlaCountdown *vars;
    u8 pad6c[0x2C];
    int collision_disable;
    u8 pad9c[12];
    u8 hit_slot;
} OozlaStateMoby;

extern int D_L01_001AEC38 MACRO_ADDR;
extern float D_L01_001B2090, D_L01_001B208C;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0 MACRO_ADDR;
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_set_state(void *, int, int);
extern void part_l01_spawn_ring_of_sparks(void *, int, float, float, float, float);
extern void PlayMobySound(int, int, void *);
extern void part_spawn_scaled_bolts(void *, int, float);
extern void moby_l00_spawn_child(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);

/* Breakable object. When something hits it, it breaks into pieces, hides, and removes itself after a short wait. */
void breakable_l01_object_update(OozlaStateMoby *moby)
{
    OozlaCountdown *vars = moby->vars;

    switch (moby->state) {
    case 0: {
        D_L01_001AEC38++;
        moby->flags |= 0x800;
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !vars->active) {
            D_L01_001AEC38 = D_L01_001AEC38 - 1;
            moby_set_state(moby, 2, -1);
        }
        moby->hit_slot = 255;
        break;
    case 2:
        if (moby->visible && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f &&
            D_L01_001B3468 < D_L01_001B15E0)
            part_l01_spawn_ring_of_sparks(moby, 15, 1.5f, 6.5f, 1.5f, 0.06666667f);
        else
            part_l01_spawn_ring_of_sparks(moby, 6, 1.5f, 6.5f, 1.5f, 0.06666667f);
        PlayMobySound(0, 0, moby);
        part_spawn_scaled_bolts(moby, 1, 0.0f);
        moby_l00_spawn_child(moby, 0xF94, 0);
        moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(moby)) {
            moby->flags |= 1;
            moby->visible = 0;
            moby->collision_disable = 0;
            vars->timer = 120;
            D_L01_001B3468++;
        }
        if (math_fast_float_d(&vars->timer)) {
            D_L01_001B3468--;
            moby_mark_spawned(moby);
        }
        break;
    }
}
