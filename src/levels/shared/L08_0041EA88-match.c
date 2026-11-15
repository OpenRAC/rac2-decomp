#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

typedef union L08Scratch {
    TI128 ti;
    struct {
        u8 pad[8];
        f32 scale;
        u8 pad2[4];
    } s;
} L08Scratch;

extern u8 D_00189E20[];
extern u8 D_00189EA0[];
extern float D_L08_001B9D30[];
extern Vec D_L08_001BFF60;

extern void func_L01_00323310(void *, void *);
extern int func_L08_00318F90(int, int, unsigned int);
extern void ref_L08_0041EA88_00(void *, int);
extern void func_0029F338(void *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00277258(void *, int, void *, float);

/* Ends the hero's ride on a vehicle: frees the vehicle's effects, resets the hero's state and
   places the hero on the ground in front of the vehicle. */
void func_L08_0041EA88(u8 *vehicle)
{
    u8 *vars;
    u8 *hero;
    L08Scratch spot;

    vars = *(u8 **)(vehicle + 0x68);
    QueueKeyedRequest(*(void **)(vars + 0x198), *(void **)(vars + 0x1A0));
    SetGameStatePair(0, 0, 1);
    hero = gHeroState;
    *(u8 *)(hero + 0x22B5) = 0;
    ref_L08_0041EA88_00(0, 1);
    *(f32 *)(hero + 0x108) = 0.16666667f;
    *(s16 *)(hero + 0x1834) = -1;
    *(s32 *)(hero + 0x1830) = 0;
    if (*(u32 *)(vars + 0x74) != 0)
        MarkMobySpawned((void *)*(u32 *)(vars + 0x74));
    *(u32 *)(vars + 0x74) = 0;
    *(s16 *)(vars + 0x88) = 0;
    *(u8 *)(vars + 0x8A) = 0;
    qcopy(&spot, D_L08_001B9D30);
    spot.s.scale = 0.0f;
    vec_scale_to_length((char *)&spot, (char *)&spot, 2.5f);
    spot.s.scale = 0.7f;
    FastVecAdd((char *)&spot, (char *)(vehicle + 0x10), (char *)&spot);
    *(u32 *)(vehicle + 0x98) = 0;
    if (CollLine(hero + 0x80, (char *)&spot, 2, (void *)*(u32 *)(hero + 0x2290), 0) != 0) {
        qcopy(&spot, &D_L08_001BFF60);
        if (TestPointAgainstCollision((char *)&spot, 2, (void *)*(u32 *)(hero + 0x2290), 0.4f) != 0) {
            qcopy(&spot, &D_L08_001BFF60);
        }
    }
    qcopy(gHeroPosition, &spot);
    *(u32 *)(vehicle + 0x98) = *(u32 *)((u8 *)*(u32 **)(vehicle + 0x24) + 0x10);
    *(u32 *)((u8 *)*(u32 **)(gHeroPosition + 0x2210) + 0x9C) = 0;
}
