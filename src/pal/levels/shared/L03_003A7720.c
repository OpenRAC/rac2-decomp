#include "include_asm.h"
#include "names.h"


extern int func_419B10(void *, void *, int, void *, void *, void *, float, float);
extern void func_32D0F0(void *, int, float);
float bot_compute_speed_from_turn(unsigned char *);

/* Asks where a bot should go next and moves it that way, returning the result of the check. */
int bot_move_toward_waypoint_pal(unsigned char *object, int index, int use_extra) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float extra = 0.0f;
    float out;
    int result;

    if (use_extra != 0)
        extra = bot_compute_speed_from_turn(object);
    result = func_419B10(*(void **)(state + 0x220), object + 0x10, index, &out, state + 0x368, state + 0x36C, extra,
                    *(float *)(state + 0x110));
    func_32D0F0(object, index, out);
    return result;
}




