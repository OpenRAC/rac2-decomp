#include "include_asm.h"
#include "names.h"

extern int g_menu_mode __attribute__((sda));
extern int g_pal_return_value_a __attribute__((sda));

/* Returns a PAL-only global value. */
int get_pal_return_value_a(void) {
    return g_pal_return_value_a;
}



extern float mat_fast_helper_a(float, float);
extern char *moby_get_controller(void *);
extern float FastAddRotations(float, float);
extern int FastDecTimer(short *);
extern int math_random_int_range(int, int);
extern int moby_step_controller(void *, void *, float);
extern int moby_step_controller(void *, void *, float);

/* Turns the moby toward a target point (with a wobble) and steps the controller (PAL). */
int moby_turn_toward_target_and_step_pal(char *self, float *target, float amount)
{
    char *data = moby_get_controller(self);
    float angle;
    if (data == 0)
        return 8;
    angle = mat_fast_helper_a(target[0] - *(float *)(self + 0x10),
                         target[1] - *(float *)(self + 0x14));
    angle = FastAddRotations(angle, amount);
    if (*(float *)(data + 0xDC) != 0.0f) {
        angle = FastAddRotations(angle, *(float *)(data + 0xDC));
        if (FastDecTimer((short *)(data + 0xE0))) {
            *(float *)(data + 0xDC) = -*(float *)(data + 0xDC);
            *(short *)(data + 0xE0) = math_random_int_range(*(short *)(data + 0xE2), *(short *)(data + 0xE4));
        }
    }
    return moby_step_controller(self, target, angle);
}


/* Steps the moby controller toward the moby's own position, using its field at 0xF8 (PAL). */
int moby_step_at_own_position_pal(char *moby) {
    return moby_step_controller(moby, moby + 0x10, *(float *)(moby + 0xF8));
}

