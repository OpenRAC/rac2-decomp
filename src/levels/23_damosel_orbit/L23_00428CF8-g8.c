#include "include_asm.h"
#include "names.h"

/* func_L23_00428CF8 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -frac2-no-annulled-wide-stores keeps its 16-byte clear out of a branch-likely's annulled slot. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI128 __attribute__((mode(TI)));

typedef struct Hit_00428CF8 {
    u8 pad00[0x18];
    u8 f18;
    u8 f19;
    u16 f1A;
    u8 pad1C[0x14];
} Hit_00428CF8;

extern float D_L23_001B1AE4 __attribute__((sda));

extern u8 D_L23_001C0A80[];

extern s32 D_0018C0B0 __attribute__((nosda));

extern void func_002A7750(u8 *, s32, s32);

extern void func_00282CC0(void *, void *, void *);

extern void func_002A8C00(void *, u8 *, s32, void *, float);

extern s32 func_002761F8(void *, void *, s32, u8 *, s32);

extern s32 func_00277258(void *, s32, u8 *, float);

extern s32 func_00277F48(float, void *, s32, u8 *, void *);

extern void func_00282D30(void *, void *, float);

extern void func_00282C88(void *);

extern s32 func_L00_0035F5A0(s32, s32, s32);

extern void func_0032C700(void *, s32, s32, s32, s32, s32, s32, s32, float, float, s32, s32, s32, s32);

extern void func_0029F338(u8 *);

extern void func_002ACEC0(void *, void *, void *, float);

extern void func_L00_002E6EF8(void *, u8 *);

extern void func_L13_0040DE50(u8 *);

/* Per-frame handler of a moving object: steps the state-0 object by its velocity, bounces or
   finishes on a hit, and in every other state rotates the two matrices and clamps the counter. */
/* Per-frame update of a fast flying shot. It moves, hits things, plays hit effects and
   removes itself after a short time. */
void func_L23_00428CF8(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float move[4];
    Hit_00428CF8 hit1;
    float vec[4];
    Hit_00428CF8 hit2;
    s32 counter;

    if (moby[0xBC] == 0) {
        *(s32 *)(vars + 0x24) = *(s32 *)(vars + 0x24) + 1;
        if (*(s32 *)(vars + 0x24) > 0xF0) {
            if (moby[0xBC] == 0) {
                SetMobyState(moby, 1, -1);
            }
        }
        switch (moby[0x20]) {
        case 0:
            FastVecAdd(move, moby + 0x10, vars);
            make_hit_descriptor(&hit1, moby, 0x80003, vars, *(float *)(vars + 0x14));
            hit1.f1A = *(u16 *)(moby + 0xAA);
            if (CollLine(moby + 0x10, move, 0, moby, 0) != 0 || TestPointAgainstCollision(moby + 0x10, 0, moby, 0.3f) != 0) {
                u8 *base = gLastRayHit;

                if (*(u8 **)(base + 0x18) != 0) {
                    s16 hitClass = *(s16 *)(*(u8 **)(base + 0x18) + 0xAA);

                    if (hitClass != 0x7E5 /* moby class 2021 */ && hitClass != 0xF7F /* Mothership Boss Part */ && hitClass != 0xF7E /* moby class 3966 */) {
                        *(TI128 *)vec = *(TI128 *)vars;
                        FastVecScale(vec, vec, 1.5f);
                        vec[2] = 1.0f;
                        vec[3] = 5627.9248046875f;
                        make_hit_descriptor(&hit2, moby, 0x90003, vec, *(float *)(vars + 0x14));
                        hit2.f19 = 1;
                        hit2.f1A = *(u16 *)(moby + 0xAA);
                        hit2.f18 = 0;
                        if (*(s32 *)(base + 0x18) == gHeroMoby_0018C0B0) {
                            StartEffectInSlot(0x20, 0, 0);
                        }
                        ProcessCollisionHit(0.6f, moby + 0x10, 0, moby, &hit2);
                        if (moby[0xBC] == 0) {
                            SetMobyState(moby, 1, -1);
                        }
                        return;
                    }
                } else {
                    *(TI128 *)vec = *(TI128 *)vars;
                    FastVecScale(vec, vec, 3.0f);
                    vec[2] = 1.0f;
                    vec[3] = 5627.9248046875f;
                    make_hit_descriptor(&hit2, moby, 0x90003, vec, *(float *)(vars + 0x14));
                    hit2.f19 = 1;
                    hit2.f1A = *(u16 *)(moby + 0xAA);
                    hit2.f18 = 0;
                    if (moby[0xBC] == 0) {
                        SetMobyState(moby, 1, -1);
                    }
                    return;
                }
            }
            if (moby[0xBC] == 0) {
                *(TI128 *)(moby + 0x10) = *(TI128 *)move;
            }
            FastVecScale(vec, vars, -0.5f);
            ClearVector128(&hit2);
            break;
        case 1:
            SpawnExplosion(moby + 0x10, 0, 25, 25, 25, 25, 0, 0, 1.0f, 20.0f, 1, 0, 0, 0);
            MarkMobySpawned(moby);
            return;
        }
    }
    ApplyAxisRotationToQuaternion(moby + 0xE0, moby + 0xE0, moby + 0xD0, D_L23_001B1AE4 * 0.017453294f);
    ApplyAxisRotationToQuaternion(moby + 0xC0, moby + 0xC0, moby + 0xD0, D_L23_001B1AE4 * 0.017453294f);
    AddDrawCallbackToList3((void *)DrawSignBandSparkles, moby);
    counter = *(s32 *)(vars + 0x2C) + 2;
    *(s32 *)(vars + 0x2C) = counter;
    if (counter > 0x40) {
        *(s32 *)(vars + 0x2C) = 0x40;
    } else if (counter < 0) {
        *(s32 *)(vars + 0x2C) = 0;
    }
}
