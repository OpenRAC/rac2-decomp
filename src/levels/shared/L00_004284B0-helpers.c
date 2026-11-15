#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern void moby_zero_five_words(char *p);
extern void vec_copy5_blend_first(char *dst, char *src, f32 x);
extern void cam_l00_init_blend_values_2(char *p);

extern char g_hero_position[];

/* Installs two aligned control vectors, raises the first Z component and
 * copies it into the saved state before clearing and refreshing the blend. */
void cam_init_control_vectors(char *camera)
{
    char *state;
    char *blendVec;
    char *cameraAlias = camera;
    {
        char *initial = *(char **)(camera + 0x70);
        char *block = initial + 0xB0;
        qcopy(block, g_hero_position);
        *(f32 *)(block + 8) += 2.0f;
        qcopy(initial + 0xC0, g_hero_position + 0x10);
        state = *(char **)(camera + 0x70);
        qcopy(state + 0x80, block);
    }
    blendVec = state + 0x14;
    moby_zero_five_words(blendVec);
    *(f32 *)(state + 0x1C) = 4.64f;
    vec_copy5_blend_first(cameraAlias + 0x50, blendVec, 0.0f);
    cam_l00_init_blend_values_2(cameraAlias);
}
