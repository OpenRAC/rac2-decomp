#include "include_asm.h"
#include "names.h"
extern void vec_scale_to_length(void *, void *, float);
typedef struct {
    float direction[4];
    char *owner;
    float scale;
    int timer;
    int duration;
    float phase;
    float zero;
    float sign;
    float one;
} ParticleE3;
extern ParticleE3 *D_001B2754 __attribute__((section(".data")));
extern float math_random_float_range(float, float);
extern int math_fast_float_d(void *);
extern int math_random_int_range(int, int);
extern int func_001163B0(void);
/* Every frame, slowly turns the glow ring entries that belong to this object. When an entry's timer runs out it picks a new random direction. */
void glow_ring_update_entries(char *object)
{
    int i;
    ParticleE3 *p;
    for (i = 0; i < 64; i++) {
        p = (ParticleE3 *)(i * 48 + (unsigned int)D_001B2754);
        if (p->owner != object) continue;
        {
            float decrement = math_random_float_range(0.01f, 0.075f);
            p->phase -= decrement;
            if (p->phase <= -8.0f) p->phase += 8.0f;
        }
        if (math_fast_float_d(&p->timer)) {
            p->direction[0] = math_random_float_range(-1.0f, 1.0f);
            p->direction[1] = math_random_float_range(-1.0f, 1.0f);
            p->direction[2] = math_random_float_range(-1.0f, 1.0f);
            p->zero = 0;
            p->duration = p->timer = math_random_int_range(20, 50);
            p->sign = func_001163B0() & 1 ? -1.0f : 1.0f;
            p->one = 1.0f;
            vec_scale_to_length(p, p, 1.0f);
            p->scale = math_random_float_range(0.7f, 0.9f);
        }
    }
}

