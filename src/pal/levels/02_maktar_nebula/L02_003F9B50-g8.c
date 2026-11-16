#include "include_asm.h"
#include "names.h"

extern float g_actor_cycle_timer_rate __attribute__((sda));
extern int g_actor_shared_state;

void func_PAL_L02_003F9D50(void) {
    int v0 = g_actor_shared_state;
    float *p = (float *)((char *)v0 + 0x74);
    float f;

    f = p[0] + g_actor_cycle_timer_rate * 0.020000001f;
    p[0] = f;
    if (f > 1.0f)
        p[0] = f - 1.0f;
}
