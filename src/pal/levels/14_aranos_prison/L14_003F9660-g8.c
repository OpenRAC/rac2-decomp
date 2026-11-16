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
void pulsing_tint_update_pal(char *self)
{
    char *v = *(char **)(self + 0x68);
    int c1 = 0x808C8C8C;
    int c2 = 0x80282828;
    int idx;
    float f;
    int r;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (hero_is_current_selected_id(self) != 0) {
            idx = *(int *)(v + 0);
            if (idx != -1) {
                moby_set_flag_bit(g_moby_l14_pool + (idx << 8), 1);
            }
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        if (flag_set_first_pending(self) != 0) {
            PlayMobySound(0, 0, self);
        }
        c1 = 0x80468CDC;
        c2 = 0x801E78AA;
        break;
    }
    f = FastAddRotations(*(float *)(v + 4), 0.12915438f);
    *(float *)(v + 4) = f;
    r = FastTweenColor(c1, c2, math_fast_sin_or_cos_b(f) * 0.5f + 0.5f);
    *(int *)(self + 0x78) = FastTweenColor(*(int *)(self + 0x78), r, 0.18f);
}
