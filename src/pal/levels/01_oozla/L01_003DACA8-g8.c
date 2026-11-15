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
extern int D_L01_001AEC38 MACRO_ADDR;
extern float D_L01_001B2090, D_L01_001B208C;
extern int D_L01_001B3468 MACRO_ADDR;
extern int D_L01_001B15E0 MACRO_ADDR;
extern void *part_find_owned_effect_slot(void *, int, int);
extern void moby_set_state(void *, int, int);
extern void part_l01_spawn_ring_of_sparks(void *, int, float, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void func_PAL_L00_003281C0(void *, int, float);
extern char *moby_l00_spawn_child(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);

void func_PAL_L01_003DACA8(OozlaStateMoby *a0)
{
    OozlaCountdown *p = a0->p;

    switch (a0->state) {
    case 0: {
        D_L01_001AEC38++;
        a0->flags |= 0x800;
        moby_set_state(a0, 1, -1);
        break;
    }
    case 1:
        if (part_find_owned_effect_slot(a0, 0x4010000, 0) && !p->active) {
            D_L01_001AEC38 = D_L01_001AEC38 - 1;
            moby_set_state(a0, 2, -1);
        }
        a0->fielda8 = 255;
        break;
    case 2:
        if (a0->field31 && D_L01_001B2090 < 0.9f && D_L01_001B208C < 0.9f &&
            D_L01_001B3468 < D_L01_001B15E0)
            part_l01_spawn_ring_of_sparks(a0, 15, 1.5f, 6.5f, 1.5f, 0.080000006f);
        else
            part_l01_spawn_ring_of_sparks(a0, 6, 1.5f, 6.5f, 1.5f, 0.080000006f);
        PlayMobySound(0, 0, a0);
        func_PAL_L00_003281C0(a0, 1, 0.0f);
        moby_l00_spawn_child(a0, 0xF94, 0);
        moby_set_state(a0, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(a0)) {
            a0->flags |= 1;
            a0->field31 = 0;
            a0->field98 = 0;
            p->timer = 100;
            D_L01_001B3468++;
        }
        if (math_fast_float_d(&p->timer)) {
            D_L01_001B3468--;
            moby_mark_spawned(a0);
        }
        break;
    }
}
