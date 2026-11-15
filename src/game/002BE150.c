/* func_002BE150: the colour word at +4 keeps its low 24 bits (retail masks it with
 * 0x00FFFFFF before or-ing the new alpha in; the draft dropped the mask), and the
 * 16-byte copy is qcopy(). */
#include "common.h"

extern void func_002B9180(void *);
extern float func_00283CE0(int n);
extern int func_00283CF0(float f);


/* Makes an effect follow the object it belongs to, copying its position and fading it in or out. It disappears when that object goes away. */
void func_002BE150(char *effect)
{
    char *particle;
    char *state;
    unsigned char *source;
    float size;
    float fade;
    float f2;
    float zero;
    unsigned int color;
    int alpha;

    particle = effect;
    if (particle == 0)
        return;
    state = particle + 0x20;
    source = *(unsigned char **)(particle + 0x20);
    if (source == 0 || (source[1] & 0x80)) {
        KillParticle(particle);
        return;
    }
    qcopy(particle + 0x10, source + 0x10);
    *(unsigned char *)(particle + 8) = source[8];
    size = *(float *)(source + 0xC) * *(float *)(state + 4) + *(float *)(state + 8);
    *(float *)(particle + 0xC) = size;
    zero = 0.0f;
    fade = *(float *)(state + 0xC) + *(float *)(state + 0x14);
    *(float *)(state + 0xC) = fade;
    if (fade < zero) {
        *(float *)(state + 0xC) = zero;
        return;
    }
    if (1.0f < fade) {
        *(float *)(state + 0xC) = 1.0f;
    }
    color = *(unsigned int *)(particle + 4) & 0xFFFFFF;
    alpha = FloatToInt(((IntToFloat((*(unsigned char **)(particle + 0x20))[7]) / 256.0f)
                       * *(float *)(state + 0x10) + *(float *)(state + 0xC)) * 256.0f);
    color = color | ((unsigned int)alpha << 24);
    *(unsigned int *)(particle + 4) = color;
}
