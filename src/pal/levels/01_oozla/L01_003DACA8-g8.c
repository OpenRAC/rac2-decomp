#include "include_asm.h"

#include "common.h"
typedef struct {
    int active;
    int timer;
} OozlaCountdown;
typedef struct {
    u8 pad0[0x20];
    u8 state;
    u8 pad21[0x10];
    u8 field31;
    u16 field32;
    u16 flags;
    u8 pad36[0x32];
    OozlaCountdown *p;
    u8 pad6c[0x2C];
    int field98;
    u8 pad9c[12];
    u8 fielda8;
} OozlaStateMoby;
extern int g_oozla_intro_timer MACRO_ADDR;
extern float g_breakable_alpha_check_a, g_breakable_alpha_check_b;
extern int g_breakable_count MACRO_ADDR;
extern int g_breakable_active_limit MACRO_ADDR;
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_set_state(void *, int, int);
extern void part_l01_spawn_ring_of_sparks(void *, int, float, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern char *moby_l00_spawn_child(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);

void breakable_l01_object_update_pal(OozlaStateMoby *a0)
{
    OozlaCountdown *p = a0->p;

    switch (a0->state) {
    case 0: {
        g_oozla_intro_timer++;
        a0->flags |= 0x800;
        moby_set_state(a0, 1, -1);
        break;
    }
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) && !p->active) {
            g_oozla_intro_timer = g_oozla_intro_timer - 1;
            moby_set_state(a0, 2, -1);
        }
        a0->fielda8 = 255;
        break;
    case 2:
        if (a0->field31 && g_breakable_alpha_check_a < 0.9f && g_breakable_alpha_check_b < 0.9f &&
            g_breakable_count < g_breakable_active_limit)
            part_l01_spawn_ring_of_sparks(a0, 15, 1.5f, 6.5f, 1.5f, 0.080000006f);
        else
            part_l01_spawn_ring_of_sparks(a0, 6, 1.5f, 6.5f, 1.5f, 0.080000006f);
        PlayMobySound(0, 0, a0);
        part_spawn_scaled_bolts_pal(a0, 1, 0.0f);
        moby_l00_spawn_child(a0, 0xF94, 0);
        moby_set_state(a0, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(a0)) {
            a0->flags |= 1;
            a0->field31 = 0;
            a0->field98 = 0;
            p->timer = 100;
            g_breakable_count++;
        }
        if (math_fast_float_d(&p->timer)) {
            g_breakable_count--;
            moby_mark_spawned(a0);
        }
        break;
    }
}
