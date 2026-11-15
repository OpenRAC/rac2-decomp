#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int g_current_map_index MACRO_ADDR;

extern int D_001A79F0_alt MACRO_ADDR;

extern TI128 D_L05_001B35D0 MACRO_ADDR;

extern TI128 D_L05_001B35E0 MACRO_ADDR;

extern TI128 D_L05_001B35F0 MACRO_ADDR;

extern float ref_L05_004431A0_00(float);

extern void ref_L05_004431A0_01(void *, void *, float);

extern void ref_L05_004431A0_02(void *, void *, void *);

/* Rotates the ship's three direction vectors by the turn amounts from the steering, then saves them. */
void ship_apply_steering_rotation(void *obj, float *yawRate, float *pitchRate)
{
    void *ship = obj;
    float *yawPtr = yawRate;
    float *pitchPtr = pitchRate;
    TI128 scratch;
    float epsilon;

    if (g_current_map_index == 20)
        goto done;
    epsilon = 1e-5f;
    if (epsilon < ref_L05_004431A0_00(*yawPtr)) {
        ref_L05_004431A0_01(&scratch, (char *)ship + 0x20, *yawPtr);
        ref_L05_004431A0_02(ship, ship, &scratch);
        ref_L05_004431A0_02((char *)ship + 0x10, (char *)ship + 0x10, &scratch);
    }
    if (D_001A79F0_alt == 20 || D_001A79F0_alt == 15)
        goto done;
    if (epsilon < ref_L05_004431A0_00(*pitchPtr)) {
        ref_L05_004431A0_01(&scratch, (char *)ship + 0x10, *pitchPtr);
        ref_L05_004431A0_02(ship, ship, &scratch);
        ref_L05_004431A0_02((char *)ship + 0x20, (char *)ship + 0x20, &scratch);
    }
done:
    qcopy(&D_L05_001B35D0, obj);
    qcopy(&D_L05_001B35E0, (char *)ship + 0x10);
    qcopy(&D_L05_001B35F0, (char *)ship + 0x20);
}
