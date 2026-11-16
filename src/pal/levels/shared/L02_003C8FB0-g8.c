#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern void func_PAL_L02_003CDF48(char *);
extern void moby_position_effect_children(char *);
extern float ApproachValue(float *, float, float);
extern void moby_set_light_color(void *, int);
extern void moby_mark_spawned(void *);
extern void gfx_add_draw_callback_first(void *, void *);
extern float g_glow_effect_params __attribute__((sda));
extern float g_glow_approach_rate[] __attribute__((sda));
extern void DrawEffectQuad(char *);

/* Advance the two timers, initialize the effect once, and release four children. */
void UpdateTimedChildEffects_pal(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char **list;
    int count;
    float one;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        one = 1.0f;
        if (*(float *)(sub + 8) < one) {
            ApproachValue((float *)(sub + 8), one, g_glow_effect_params * (0.020000001f));
            goto update;
        }
        list = (char **)(sub + 0x10);
        if (!(*(float *)(sub + 12) < one))
            goto cleanup;
        if (*(int *)(sub + 4) == 0) {
            *(int *)(sub + 4) = 1;
            func_PAL_L02_003CDF48(obj);
        }
        moby_position_effect_children(obj);
        ApproachValue((float *)(sub + 12), one, g_glow_approach_rate[0] * (0.020000001f));
        goto update;
    cleanup:
        count = 3;
        sub += 0x30;
        do {
            if (*list) {
                *(unsigned short *)(*list + 0x34) = *(unsigned short *)(sub - 0x10);
                moby_set_light_color(*list, *(int *)sub);
            }
            sub += 4;
            count--;
            list++;
        } while (count >= 0);
        moby_mark_spawned(obj);
        break;
    update:
        gfx_add_draw_callback_first((void *)DrawEffectQuad, obj);
        break;
    }
}
