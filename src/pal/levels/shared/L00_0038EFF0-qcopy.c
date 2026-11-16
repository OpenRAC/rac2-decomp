#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char pad00[0x10];
    TI128 position;
    char state20;
    char pad21[0x30 - 0x21];
    unsigned char alpha;
    char visible;
    short timer;
    char pad34[0x68 - 0x34];
    char *vars;
    char pad6C[0xF0 - 0x6C];
    float spin[3];
    int spin_time;
} Moby_38D530;
extern Moby_38D530 *CreateMoby(int size);
extern float math_random_float_range(float lo, float hi);
extern int part_alloc_effect_slot(Moby_38D530 *object, int a, float b, float c, float d);
extern void func_002A0F48(Moby_38D530 *object);

/* Spawns object 0x79 at A1 with the state vector A2 (the func_L00_003E7650 spawner): a random
   spin on all three axes, a 30..300 frame timer and its effect handle. */
Moby_38D530 *part_l00_spawn_spinning_debris_pal(TI128 *position, TI128 *state_vector)
{
    Moby_38D530 *moby;
    char *vars;
    float lo;
    float hi;

    moby = CreateMoby(0x79);
    if (moby != 0) {
        moby->alpha = 0xFF;
        moby->timer = 0x1FF;
        moby->visible = 1;
        vars = moby->vars;
        moby->state20 = 0;
        qcopy(&moby->position, position);
        *(TI128 *)vars = *state_vector;
        lo = -3.1415927f;
        hi = 3.1415927f;
        *(int *)(vars + 0x14) = 0;
        *(int *)(vars + 0x10) = 0x19;
        *(int *)(vars + 0x18) = 0xFA;
        moby->spin[0] = math_random_float_range(lo, hi);
        moby->spin[1] = math_random_float_range(lo, hi);
        moby->spin[2] = math_random_float_range(lo, hi);
        moby->spin_time = 0;
        func_002A0F48(moby);
        *(int *)(vars + 0x1C) = part_alloc_effect_slot(moby, 0, 1.0f, 1.0f, 1.0f);
    }
    return moby;
}
