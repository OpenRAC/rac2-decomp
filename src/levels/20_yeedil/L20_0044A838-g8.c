#include "names.h"
/* Advances the phase and restores the complete saved position before the height update. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_turret_bob_amplitude __attribute__((sda));
extern float g_turret_bob_phase __attribute__((sda));
extern float g_turret_bob_amount __attribute__((sda));

extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern void part_queue_ground_shadow(char *, float);
extern void turret_turn_toward_target(char *);

/* Ends each turret frame: counts the frame, bobs the turret up and down, and turns its aim. */
void turret_update_bob_aim(char *moby) {
    char *state = *(char **)(moby + 0x68);
    u16 frame = *(u16 *)(moby + 0x96);
    float phase;

    *(u16 *)(moby + 0x96) = frame + 1;
    if (*(u8 *)(moby + 0x31)) {
        qcopy((moby + 0x10), (state + 0x180));
        phase = g_turret_bob_phase;
        phase = FastAddRotations(*(float *)(state + 0x1A0), phase * 0.000290888245f);
        *(float *)(state + 0x1A0) = phase;
        phase = math_fast_sin_or_cos_b(phase);
        {
            float amount = g_turret_bob_amount;
            *(float *)(moby + 0x18) = *(float *)(moby + 0x18) + g_turret_bob_amplitude * phase;
            part_queue_ground_shadow(moby, amount);
        }
    }
    if (((*(u16 *)(moby + 0x34)) ^ 1) & 1) {
        turret_turn_toward_target(moby);
    }
}
