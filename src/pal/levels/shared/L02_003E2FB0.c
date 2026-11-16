#include "include_asm.h"

#include "common.h"
extern f32 fade_reduce_value(float);

void moby_call_helper_10000_pal(void) {
    fade_reduce_value(10000.0f);
}

