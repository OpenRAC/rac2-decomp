#include "common.h"

/* The grouped quadword copy: the R5900 lq/sq pair with both addresses in registers,
   and the copy as the scheduling barrier the retail's inline-asm macro was. */
typedef int TI128 __attribute__((mode(TI)));

extern void func_00282CC0(char *, char *, char *);

extern void func_002A8C00(char *, int, int, void *, float);

extern int func_002761F8(void *, void *, int, int, void *);

extern int func_00282948(void *);

extern void func_002E5DA0(int, int, void *, int);

extern void func_L00_002E6EF8(void *, int);

extern void func_L20_0039C5D0(char *);

extern void func_L20_0039C8C8(char *, int, int);

extern void func_L20_0039CC10(void);

extern void func_0029F338(int);

extern char D_L20_001C0420[];

/* Flies a shot forward each frame, checks what it hits, and on a hit makes sparks and removes the shot. */
void func_L20_0039C448(char *moby) {
    char *position = moby + 0x10;
    char *vars = *(char **)(moby + 0x68);
    char *velocity;
    char hitInfo[0x30];

    *(TI128 *)vars = *(TI128 *)position;
    velocity = vars + 0x10;
    FastVecAdd(position, position, velocity);
    make_hit_descriptor(hitInfo, (int)moby, 0x10001, velocity, *(float *)(vars + 0x2C));
    if (CollLine(vars, position, 0, *(int *)(moby + 0xB8), hitInfo) != 0
        || FastFloatHelperD(vars + 0x20) != 0) {
        SpawnSparkBurst_L20(D_L20_001C0420, 0x14, 1);
        PlaySoundFromClassBank(2, 0, moby, 0x12EF);
        MarkMobySpawned((int)moby);
    } else {
        EmitJitteredParticleTrail(moby);
        AddDrawCallbackToList3(DrawProjectileTrailRibbon, (int)moby);
    }
}

/* Fills in the settings block of this object and copies one position vector into it. */
void func_L20_0043D470(char *moby) {
    char *state = *(char **)(moby + 0x68);

    *(f32 *)(*(char **)(state + 0x84) + 0x0) = 8.0f;
    *(f32 *)(*(char **)(state + 0x84) + 0x4) = 2.5f;
    *(u8 *)(*(char **)(state + 0x84) + 0x18) = 1;
    *(u16 *)(*(char **)(state + 0x84) + 0x1A) = 0;
    *(u8 *)(*(char **)(state + 0x84) + 0x1E) = 1;
    *(u8 *)(*(char **)(state + 0x84) + 0x1F) = 0;
    *(TI128 *)(*(char **)(state + 0x84) + 0x20) = *(TI128 *)(state + 0x60);
}
