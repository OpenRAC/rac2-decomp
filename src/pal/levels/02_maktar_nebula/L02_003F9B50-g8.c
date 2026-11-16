#include "include_asm.h"
#include "names.h"

extern float g_actor_cycle_timer_rate __attribute__((sda));
extern int g_actor_shared_state;

/* Advances a shared cycle timer in the actor's state by a fixed rate, wrapping it past 1.0 (PAL). */
void actor_advance_cycle_timer_pal(void) {
    int shared_state = g_actor_shared_state;
    float *timer_ptr = (float *)((char *)shared_state + 0x74);
    float timer_value;

    timer_value = timer_ptr[0] + g_actor_cycle_timer_rate * 0.020000001f;
    timer_ptr[0] = timer_value;
    if (timer_value > 1.0f)
        timer_ptr[0] = timer_value - 1.0f;
}
