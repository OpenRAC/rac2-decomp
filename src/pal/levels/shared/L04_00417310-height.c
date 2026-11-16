#include "include_asm.h"
#include "names.h"

typedef short s16;
extern int g_current_map_index[] __attribute__((sda));
extern int g_current_lap[] __attribute__((sda));
typedef struct {
    char pad000[0x274];
    s16 unk_274;
    char pad276[6];
    float unk_27C;
    char pad280[0x298 - 0x280];
    float target_height;
    char pad29C[0x2A8 - 0x29C];
    float base_height;
    char pad2AC[0x314 - 0x2AC];
    int unk_314;
    int anim_frame;
    char pad31C[0x34C - 0x31C];
    int unk_34C;
} HeightState;

/* Computes the target height offset from the base height, scaled by how far height is above or below base. */
void bike_compute_target_height_pal(void *object, HeightState *state, float height, float base,
                       float factor, float speed, float margin)
{
    float t, extra;

    if (state->unk_34C >= 7) {
        state->target_height = state->base_height + speed * 0.00040000002f;
        return;
    }

    if (margin + base < height) {
        if (g_current_map_index[0] == 4 && state->unk_274 != 0 &&
            state->unk_314 == -1 && state->anim_frame >= 476) {
            t = state->unk_27C * 8.333333f;
            if (t > 1.0f)
                t = 1.0f;
            else if (t < 0.0f)
                t = 0.0f;
            if (g_current_lap[0] >= 2)
                extra = t * 7.0f + 3.5f;
            else
                extra = t * 3.0f + 1.5f;
        } else {
            extra = 0.0f;
        }

        t = (height - base + margin) / (base + margin);
        if (t > 1.0f)
            t = 1.0f;
        if (t < 0.0f)
            t = 0.0f;
        state->target_height = state->base_height - (speed + extra) * t * 0.00040000002f;
    } else {
        t = (base - height + margin) / base;
        if (t > 1.0f)
            t = 1.0f;
        if (t < 0.0f)
            t = 0.0f;
        t = t * factor;
        state->target_height = state->base_height + speed * t * 0.00040000002f;
    }
}
