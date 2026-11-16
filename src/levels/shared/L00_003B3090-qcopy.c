#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

extern void vec_fast_normalize_helper(void *, void *, float);
extern int coll_process_hit(void *, int, int, void *, float);
extern int g_collision_hero_owner;

struct S {
    float f0;
    float f4;
    float f8;
    float fC;
    char *p10;
    int f14;
    signed char b18;
    signed char b19;
    unsigned short h1A;
    float f1C;
    int f20;
};

/* Hurts everything near a point, using the size and damage kept in a shot's data. */
void shot_damage_around(char *moby, char *vars, char *position) {
    struct S hit;
    char *shot = vars;
    char *owner = moby;
    char *center = position;

    hit.f14 = 0x10000;
    hit.f1C = *(float *)(shot + 0x2C);
    hit.f20 = 1;
    hit.p10 = owner;
    *(TI128 *)&hit.f0 = *(TI128 *)shot;
    vec_fast_normalize_helper(&hit, &hit, 1.0f);
    hit.f8 = 1.0f;
    hit.fC = 5627.925f;
    hit.b18 = 3;
    hit.b19 = 2;
    hit.h1A = *(unsigned short *)(owner + 0xAA);
    coll_process_hit(center, 1, g_collision_hero_owner, &hit, *(float *)(shot + 0x30));
}
