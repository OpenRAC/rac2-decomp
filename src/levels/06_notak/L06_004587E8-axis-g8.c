/* func_L06_004587E8 (1,572 bytes, Notak). Own unit: -O2 -G8 -ffunction-sections
 * -frac2-mult-add-no-flatten -frac2-pre-call-test -frac2-cse-noskip-store
 * -frac2-sched-retstore -frac2-sched-stackaddr (config/cflags.txt; docs/build/compiler-notes.md).
 * In the timer loop `base` is a set-once local holding the table address (owner ruling on
 * set-once locals): its `la` is hoisted and reload rematerialises it in $v1, as retail.
 * Owner standard of 12 November 2026 for the switches.
 */
#include "common.h"
extern short D_L06_001B3790[] __attribute__((sda));
extern short D_L06_001B37A0[] __attribute__((sda));
extern char D_L06_0025FFC0[];
extern float func_00283B98(float, float);
typedef unsigned int NotakQuad __attribute__((mode(TI)));
extern char D_00188660[];
extern char D_L06_001A8F20[] __attribute__((sda));
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern char D_L06_001B9840[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, float, int);
extern void func_002A7750(char *, int, int);
extern float func_002A7878(float, float);
extern void func_00350388(char *);
typedef struct {
    char prefix[0x18];
    char *hit;
    int count;
    float point[4];
} NotakCollision;
extern NotakCollision D_L06_001BFC80;
extern char D_L06_001C79C0[];
extern int D_L06_001B3778[] __attribute__((sda));
extern int D_L06_001B3760[];
extern void func_002A8C00(void *, char *, int, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_0031EBF8(float, void *, int, void *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_L06_00459828(float *, int);
extern void func_00291450(int);
extern void func_002A7988(void *, float, float);
extern float func_00282DF0(void *);
extern int func_002E59B0(void *, int);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L06_00458F30(char *);

/* Updates a flying projectile: it moves, leaves a twisting trail and bursts when it hits something. */
void func_L06_004587E8(char *moby) {
    float pos[4];
    typedef union { NotakQuad q; float f[4]; } Vec;
    char *vars = *(char **)(moby + 0x68);
    char *hit;
    float *impact;
    char *soundRecord;
    int snd, index, row, col;
    char *slot;
    int k, j, sign;
    int count = 6;
    typedef NotakQuad Trail[6][4];
    float direction;
    float size;
    int i;
    int one = 1;
    int type = *(unsigned char *)(moby + 0x20);
    {
    if (type == 0) goto c0;
    if (type == one) goto c1;
    goto def;
    c0: {
        char collision[112];
        *(float *)(moby + 0xF0) = FastAddRotations(*(float *)(moby + 0xF0), 0.104719773f);
        FastVecAdd(pos, moby + 0x10, vars);
        make_hit_descriptor(collision, moby, 1, vars, *(float *)(vars + 0x40));
        *(unsigned short *)(collision + 0x1A) = *(unsigned short *)(moby + 0xAA);
        if (CollLine(moby + 0x10, pos, 0, moby, collision) ||
            func_0031EBF8(0.3f, moby + 0x10, 0, moby) || FastFloatHelperD(vars + 0x38)) {
            hit = D_L06_001BFC80.hit;
            if (hit) {
                if (hit == *(char **)(vars + 0x3C)) goto update_position;
                if (*(short *)(hit + 0xAA) != 0x4E /* moby class 78 */)
                    SweepCollisionFromObject(moby, moby + 0x10, 0x10001, 0, 1, 0, 0.5f, *(float *)(vars + 0x40), 1.0f);
                impact = (float *)(moby + 0x10);
            } else {
                impact = D_L06_001BFC80.point;
            }
            EmitPairedSpinParticles(impact, 20);
            snd = *(int *)(vars + 0x4C);
            if (snd != -1) {
                soundRecord = gSoundState + snd * 0x70;
                if (*(char **)(soundRecord + 0x88) == moby && *(unsigned char *)(soundRecord + 0x74)) StopSoundVoice(snd);
            }
            *(int *)(vars + 0x4C) = -1;
            SetMobyState(moby, 1, -1);
            return;
        }
    update_position:
        qcopy(moby + 0x10, pos);
        goto def;
    }
    c1: {
        index = D_L06_001B3778[*(int *)(vars + 0x48)];
        if (index >= 0) {
            slot = D_L06_001C79C0 + index * 32;
            *(float *)(slot + 0x1C) -= 0.166666672f;
            if (!(*(float *)(slot + 0x1C) <= 0)) return;
            FreePointLight(D_L06_001B3778[*(int *)(vars + 0x48)]);
            D_L06_001B3778[*(int *)(vars + 0x48)] = -1;
            D_L06_001B3760[*(int *)(vars + 0x48)] = 0;
            for (row = 0; row < 6; row++) {
                for (col = 1; col < 4; col++)
                    qzero_nc(&((NotakQuad *)(D_L06_0025FFC0 + *(int *)(vars + 0x48) * 0x180 + (row << 6)))[col]);
            }
            func_00350388(moby);
            return;
        }
        D_L06_001B3760[*(int *)(vars + 0x48)] = 0;
        func_00350388(moby);
        return;
    }
    }
def:
    qcopy(pos, moby + 0x10);
    {
        k = 0;
        if (D_L06_001B3790[k]) goto scanned;
    next:
        k++;
        while (k < 6) {
            if (!D_L06_001B3790[k]) goto next;
            break;
        }
    scanned:;
    }
    for (i = 0; i < count; i++) {
        Vec velocity, axis;
        short *base = D_L06_001B3790; short *timer = &base[i];
        if (--*timer < 0) *timer = 0;
        *timer = 2;
        D_L06_001B37A0[i] = 64;
        SpawnRandomDirectionEffect(velocity.f, 0.2f, 0.2f);
        if (FastVecLength(velocity.f) > 0.2f) vec_scale_to_length((char *)velocity.f, (char *)velocity.f, 0.2f);
        qcopy(&((Trail *)D_L06_0025FFC0)[*(int *)(vars + 0x48)][i][0], pos);
        direction = 1.0f;
        for (j = 1; j < 4; j++) {
            float *prev = (float *)(&((Trail *)D_L06_0025FFC0)[*(int *)(vars + 0x48)][i][j - 1]);
            FastVecSub(axis.f, prev, (float *)D_L06_001B9840);
            ApplyAxisRotationToQuaternion(velocity.f, velocity.f, axis.f, RandomFloatRange(0.17453295f, 0.7853982448577881f) * direction);
            direction = -direction;
            FastVecAdd(&((Trail *)D_L06_0025FFC0)[*(int *)(vars + 0x48)][i][j], &((Trail *)D_L06_0025FFC0)[*(int *)(vars + 0x48)][i][j - 1], velocity.f);
        }
    }
    if (!RandomIntBelow(2)) {
        size = RandomFloatRange(0.2f, 0.9f);
        sign = RandomIntBelow(2);
        if (!sign) sign--;
        SpawnGroundEffectParticle(moby + 0x10, 2, size * 0.1f, size, 0x7F7F2020, 0, sign, D_L06_001A8F20, 0, 0);
        SpawnGroundEffectParticle(moby + 0x10, 2, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, D_L06_001A8F20, 0, 0);
    }
    if (!IsVoicePlayingForOwner(moby, *(int *)(vars + 0x4C)))
        *(int *)(vars + 0x4C) = PlaySoundFromClassBank(7, 4, moby, *(short *)(*(char **)(vars + 0x3C) + 0xAA));
    AddDrawCallbackToList3(DrawProjectileTrails, moby);
}
