#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float FastVecLength(void *);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, unsigned int, int, float, float, float);
extern void DrawOrientedQuadsAtPoints(void *, void *, int, unsigned int, unsigned int, float, float, float, int);

/* Each frame, makes smoky sparks around the object and, once enough has built up, shoots a few larger puffs. */
void smoky_spark_effect_update(char *arg) {
    float v[4];
    char *vars = *(char **)(arg + 0x68);
    float scroll;
    float speed;

    *(TI128 *)v = 0;
    v[3] = 1.0f;
    scroll = *(float *)(vars + 0x14) - 0.1f;
    *(float *)(vars + 0x14) = scroll;
    if (scroll <= -8.0f) {
        *(float *)(vars + 0x14) = scroll + 8.0f;
    }
    speed = FastVecLength(vars);
    *(float *)(vars + 0x18) = *(float *)(vars + 0x18) + speed;
    gfx_draw_billboard_quad(arg + 0x10, 0x31, 0x40801010, 1, 0.2f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(arg + 0x10, 0x31, 0x707F7F7F, 1, 0.1f, 0.0f, math_random_angle());
    gfx_draw_billboard_quad(arg + 0x10, 0x2F, 0x407F7F7F, 1, 0.05f, 0.0f, math_random_angle());
    if (*(float *)(vars + 0x18) > 1.0f) {
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F804040, 0x00804040, 0.03f, 1.2f, *(float *)(vars + 0x14), 0x17);
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F801010, 0x00801010, 0.1f, 1.2f, *(float *)(vars + 0x14), 0x17);
        DrawOrientedQuadsAtPoints(arg, v, 1, 0x7F801010, 0x00801010, 0.1f, 1.2f, *(float *)(vars + 0x14), 0x17);
    }
}

