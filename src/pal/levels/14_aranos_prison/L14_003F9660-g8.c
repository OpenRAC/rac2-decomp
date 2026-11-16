#include "include_asm.h"
#include "names.h"

extern int FastTweenColor(int a, int b, float c);
extern int g_moby_l14_pool __attribute__((sda));
extern int hero_is_current_selected_id(char *self);
extern void moby_set_flag_bit(int table, int mode);
extern void moby_set_state(char *self, int state, int mode);
extern int flag_set_first_pending(char *self);
extern int PlayMobySound(int a, int b, char *self);
extern float FastAddRotations(float a, float b);
extern float math_fast_sin_or_cos_b(float a);
extern int FastTweenColor(int a, int b, float c);

/* Steps the owner's state block, then blends the two colours its state asks for. */
void pulsing_tint_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int bright_color = 0x808C8C8C;
    int dark_color = 0x80282828;
    int link_index;
    float phase;
    int blended;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (hero_is_current_selected_id(moby) != 0) {
            link_index = *(int *)(vars + 0);
            if (link_index != -1) {
                moby_set_flag_bit(g_moby_l14_pool + (link_index << 8), 1);
            }
            moby_set_state(moby, 1, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(moby) != 0) {
            PlayMobySound(0, 0, moby);
        }
        bright_color = 0x80468CDC;
        dark_color = 0x801E78AA;
        break;
    }
    phase = FastAddRotations(*(float *)(vars + 4), 0.12915438f);
    *(float *)(vars + 4) = phase;
    blended = FastTweenColor(bright_color, dark_color, math_fast_sin_or_cos_b(phase) * 0.5f + 0.5f);
    *(int *)(moby + 0x78) = FastTweenColor(*(int *)(moby + 0x78), blended, 0.18f);
}
