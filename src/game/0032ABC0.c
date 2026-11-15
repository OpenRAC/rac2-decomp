#include "include_asm.h"
#include "common.h"

typedef int TI_0032ABC0 __attribute__((mode(TI)));
typedef union { char b[0x2600]; char *ptr[0x980]; } Hero_0032ABC0;
typedef struct { float dir[4]; float spin; float speed; int life; void *owner; float scale; char pad24[0xC]; } Debris0032ABC0;

extern Debris0032ABC0 g_debris_pieces[];
extern char g_hero_state[];
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void moby_get_facing_direction(void *, float *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);

extern void vec_scale_to_length(float *, float *, float);

/* Takes the first free debris slot for owner: a random spin and speed, a 37-frame life, and a
   direction pointing away from the hero's target. */
void part_claim_debris_piece(void *owner)
{
    Debris0032ABC0 *debris;
    int i;
    float target_offset[4];
    TI_0032ABC0 delta;
    TI_0032ABC0 pos;

    for (i = 0; i < 12; i++) {
        debris = &g_debris_pieces[i];
        if (debris->owner == 0) {
            debris->owner = owner;
            debris->spin = math_random_angle();
            debris->speed = math_random_signed_float_range(1200.0f, 1400.0f) * 0.00029088825f;
            debris->life = 0x25;
            debris->scale = math_random_float_range(0.3f, 0.4f);
            moby_get_facing_direction(((Hero_0032ABC0 *)g_hero_state)->ptr[0x2290 / 4] + 0x10, target_offset);
            qcopy(&pos, ((Hero_0032ABC0 *)g_hero_state)->ptr[0x2290 / 4] + 0x10);
            FastVecAdd(&delta, &pos, target_offset);
            FastVecCross(&pos, &pos, &delta);
            vec_scale_to_length(debris->dir, (float *)&pos, debris->scale);
            return;
        }
    }
}
