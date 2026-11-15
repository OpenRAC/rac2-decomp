#include "common.h"

extern f32 D_L05_001AEBE8 __attribute__((sda));
extern f32 D_L05_001AEBE4 __attribute__((sda));
extern f32 D_L05_001AEBE0 __attribute__((sda));
extern f32 D_L05_001AEBDC __attribute__((sda));

typedef struct { f32 a, b, c, d; } SpawnVector97F48;

typedef struct {
    SpawnVector97F48 v;
    s32 s10;
    s32 s14;
    u8 b18;
    u8 b19;
    u16 h1A;
    f32 f1C;
    s32 s20;
} SpawnRecord97F48;

extern void vec_scale_to_length(SpawnRecord97F48 *a, SpawnRecord97F48 *b, f32 c);
extern void coll_process_hit(char *a, s32 b, s32 c, SpawnRecord97F48 *d, f32 e);

/* Build and submit the projectile hit record from its owner and flight state. */
void SubmitFlightStateHitRecord(s32 owner, char *state, char *position)
{
    SpawnRecord97F48 t;
    u16 id;

    t.s14 = 0x810000;
    t.s10 = owner;
    if (*(s32 *)(state + 0x24))
        t.f1C = D_L05_001AEBE8;
    else
        t.f1C = D_L05_001AEBE4;
    t.s20 = 1;
    qcopy(&t.v, state);
    vec_scale_to_length(&t, &t, 1.0f);
    id = *(u16 *)(owner + 0xAA);
    t.v.d = 5627.9248046875f;
    t.b18 = 3;
    t.b19 = 2;
    t.h1A = id;
    coll_process_hit(position, 1, *(s32 *)(state + 0x20), &t,
                  *(s32 *)(state + 0x24) ? D_L05_001AEBE0 : D_L05_001AEBDC);
}
