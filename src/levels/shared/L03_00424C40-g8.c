#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int s32;
typedef float f32;

/* The current level: read through $gp only from a branch delay slot, absolute elsewhere. */
extern s32 D_001A79F0 __attribute__((section(".sdata")));

/* One done flag per slot. `sda` on an unsized array makes cc1 emit the `la` macro, so the
   `lui`/`addiu` pair stays together, as in retail. */
extern u8 D_001A7A28[] __attribute__((sda));

extern char D_00189EA0[];

extern u8 D_001395D0 __attribute__((nosda));

extern unsigned short D_0018CFB8 __attribute__((nosda));

extern u8 *D_L03_001B1E70 __attribute__((sda));

extern u8 *D_L03_001B2A28 __attribute__((sda));

/* Four offsets of 16 bytes, addressed from $gp: declared as one float so cc1 keeps it small. */
extern f32 D_L03_001B1E80 __attribute__((sda));

extern f32 D_L03_001B1EC0 __attribute__((sda));

extern f32 D_L03_001B1EC4 __attribute__((sda));

extern s32 D_L03_001B1EC8 __attribute__((sda));

extern f32 D_L03_001B1ED0 __attribute__((sda));

extern f32 D_L03_001B1ED4[3] __attribute__((sda));

extern f32 D_L03_001B1EE0 __attribute__((sda));

extern f32 func_00283B98(f32, f32);
extern void func_0029F338(u8 *);
extern void func_00282F20(u8 *, u8 *, f32);
extern void func_00282CC0(u8 *, u8 *, u8 *);
extern void func_00282CF0(float *, u8 *, u8 *);
extern float func_00282E48(void *, void *);
extern void func_002833F0(void *, void *);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern u8 *func_002C7970(void *, void *, int, int, int, int, int, float, float, float, int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_0028A180(int, int);
extern void func_L03_00425030(u8 *);
extern void func_L03_00425108(u8 *);

/* A three-state object: state 0 arms it (and on level 5 finds the entity of class 0xFBF),
   state 1 spins its four angles and throws four particles each frame until the player (or that
   entity on level 5) comes near, state 2 marks its slot done and removes it. */
/* Updates the Nanotech Upgrade pickup (moby class 4548). */
void func_L03_00424C40(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 matrix[12];
    f32 dir[4];
    f32 pos[4];
    f32 (*src)[4];
    u8 *pos0;
    u8 *posPtr;
    u8 *posPtrCopy;
    u8 *scan;
    u8 *found;
    s32 lifetime;
    s32 i;
    f32 distance;

    switch (moby[0x20]) {
    case 0:
        moby[0x20] = 1;
        moby[0xBC] = 0;
        *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * 1.1f;
        if (D_001A7A28[*(s32 *)vars] == 1) {
            MarkMobySpawned(moby);
            return;
        }
        if (gCurrentMapIndex == 5 && D_L03_001B1E70 == 0 && (scan = D_L03_001B2A28) != 0) {
            s32 id = 0xFBF /* moby class 4031 */;     /* in posPtr register: retail compares with `xor`, not `xori` */
            found = 0;
            do {
                if (*(short *)(scan + 0xAA) == id)
                    found = scan;
                scan = *(u8 **)(scan + 0x28);
            } while (scan != 0);
            D_L03_001B1E70 = found;
        }
        InitRandomColorValues(moby);
        return;
    case 1:
        /* Retail keeps the position in two registers (the first test's and posPtr copy for the
           rest); with this unit's -fno-gcse the copy after the first call gives both. */
        posPtr = moby + 0x10;
        *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8), 0.03f);
        distance = fast_vec_dist(gHeroPosition, posPtr);
        posPtrCopy = posPtr;
        if (distance < 1.5f)
            moby[0x20] = 2;
        if (gCurrentMapIndex == 5 && D_L03_001B1E70 != 0) {
            if (fast_vec_dist(D_L03_001B1E70 + 0x10, posPtrCopy) < 3.0f)
                moby[0x20] = 2;
        }
        pos0 = posPtrCopy;
        *(f32 *)(vars + 0x50) = FastAddRotations(*(f32 *)(vars + 0x50), D_L03_001B1ED0 * 0.00029088825f);
        *(f32 *)(vars + 0x54) = FastAddRotations(*(f32 *)(vars + 0x54), D_L03_001B1ED4[0] * 0.00029088825f);
        *(f32 *)(vars + 0x58) = FastAddRotations(*(f32 *)(vars + 0x58), D_L03_001B1ED4[1] * 0.00029088825f);
        *(f32 *)(vars + 0x5C) = FastAddRotations(*(f32 *)(vars + 0x5C), D_L03_001B1ED4[2] * 0.00029088825f);
        euler_rotation_basis(matrix, vars + 0x50);
        src = (f32 (*)[4])&D_L03_001B1E80;
        i = 3;
        do {
            i--;
            lifetime = FloatToInt(RandomSignedFloatRange(2.0f, 5.0f));
            matrix_mul_vec3(pos, src, matrix);
            src++;
            vec_scale_to_length((u8 *)pos, (u8 *)pos, D_L03_001B1EC0);
            FastVecAdd((u8 *)pos, (u8 *)pos, pos0);
            FastVecSub(dir, pos0, (u8 *)pos);
            vec_scale_to_length((u8 *)dir, (u8 *)dir, D_L03_001B1EC4 * (1.0f / 60.0f));
            SpawnFadingDriftParticle(pos, dir, D_L03_001B1EC8, 0x804020, lifetime, 0, 0x6F,
                          RandomFloatRange(0.07f, 0.12f) * 210000.0f, 42000.0f, 0.0f, 6);
        } while (i >= 0);
        *(f32 *)(moby + 0xF0) = FastSinOrCosA(*(f32 *)(vars + 0x5C)) * D_L03_001B1EE0;
        *(f32 *)(moby + 0xF4) = FastSinOrCosB(*(f32 *)(vars + 0x5C)) * D_L03_001B1EE0;
        DrawGlowRingSprites_L03(moby);
        return;
    case 2:
        D_001A7A28[*(s32 *)vars] = 1;
        if (*(s32 *)vars == 0)
            D_001395D0 = 1;
        if (D_0018CFB8 == 0)
            QueueHintMessage(0xA31, 0x88);
        MarkMobySpawned(moby);
        return;
    }
}
