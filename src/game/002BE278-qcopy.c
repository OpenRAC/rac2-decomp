#include "include_asm.h"
#include "names.h"

/* func_002BE278 in its own unit for the grouped lq/sq profile. */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char unk00;
    unsigned char unk01;
    unsigned char unk02;
    unsigned char unk03;
    int colour;
    unsigned char unk08;
    unsigned char unk09;
    short life;
    float size;
    TI128 position;
    struct {
        TI128 velocity;
        float scale[3];
        float alpha;
    } motion;
} Particle_002BE278;

extern Particle_002BE278 *part_alloc(int);
extern int gfx_pack_color_floats(float, float, float, float);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);
extern unsigned char *D_001F25A4;

/* Spawns a white flash particle at position moving with velocity; growing, or
   shrinking when flag is set; a negative size picks a random one. */
void part_spawn_white_flash(TI128 *position, TI128 *velocity, int flag, float size)
{
    Particle_002BE278 *particle = part_alloc(0x19);
    typeof(particle->motion) *motion = &particle->motion;

    if (particle != 0) {
        particle->position = *position;
        if (flag == 0) {
            particle->colour = gfx_pack_color_floats(1.0f, 1.0f, 1.0f, 0.6f);
            motion->scale[0] = 1.0f;
            motion->scale[1] = 1.0f;
            motion->scale[2] = 1.0f;
        } else {
            particle->colour = gfx_pack_color_floats(1.0f, 1.0f, 1.0f, 0.6f);
            motion->scale[0] = -1.0f;
            motion->scale[1] = -1.0f;
            motion->scale[2] = -1.0f;
        }
        particle->unk09 = FloatToInt(4.0f) + 0x40;
        particle->unk03 = 0x48;
        particle->unk01 = 0;
        if (size < 0.0f)
            particle->size = math_random_float_range(5000.0f, 30000.0f);
        else
            particle->size = size;
        particle->unk08 = 0;
        particle->unk02 = *D_001F25A4;
        motion->alpha = 0.6f;
        particle->life = 0x50;
        motion->velocity = *velocity;
    }
}
