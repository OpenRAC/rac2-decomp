/* func_L00_00408E58 has a unit of its own for -g: the entry pointer and the
 * division are two statements, so the second one's line label sits before the
 * lwc1 and the assembler pads one nop in front of div.s (the division floor,
 * docs/build/compiler-notes.md).
 *
 * done starts at 0 and takes the timer's result after the loop. Its value is
 * then equal to i's at the loop guard and it outlives i, so cse keeps it as the
 * canonical register there: the guard tests done, and i is cleared separately.
 * count and timer share a stack record, which keeps the timer's address out of a
 * register that would be issued ahead of the list's address. D_L00_001A8F00 is
 * declared plain: its macro load uses one register for the lui and the lw. */
#include "common.h"

extern void func_L00_00409420(char *);
extern void ref_L00_00408E58_00(int, int);
extern void func_002A75E0(char *, int, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002829D8(void *);
extern void func_00282A88(void *, int);
extern int func_00282948(void *);
extern int func_L00_002D4040(int);
extern void func_L00_002AF568(void);
extern int func_L00_002D6998(void *);
extern void func_002E5CF8(int, int, char *);
extern void func_00282F20(void *, void *, float);
extern char *func_L00_00416F68(void *, int, char *);
extern void func_002E6EF8(void (*)(char *), char *);
extern void func_L00_00409480(char *);
extern void func_L00_0037E000(char *);
extern void func_002AF580(void *, void *, int *, void *, int, int, float, float, float, float, float, int, int);
extern char *func_002AB1F0(char *);
extern void func_002A6C58(char *, int, int);
extern void func_00310440(char *);
extern void func_L00_002D3F30(int, int);

extern struct {
    char pad0[0x1230];
    int mask;
    char pad1234[0xc];
    int level;
    char pad1244[0x104c];
    char *object;
    int state;
    char pad2298[0x24];
    unsigned char disabled;
} D_00189E20;

typedef struct {
    char pad[0x54];
    float rate;
    char pad58[0xe0 - 0x58];
} RateEntry;

extern int D_L00_001A8F00;
extern int D_00138324 __attribute__((nosda));
extern int D_L00_001B0F90 __attribute__((sda));
extern unsigned char D_00139593 __attribute__((nosda));
extern RateEntry D_L00_00262570[];
extern float D_L00_0025C64C __attribute__((nosda));
extern char D_L00_0029FBE0[];
extern char D_L00_001B8FF0[];

#define I(p, n) (*(int *)((char *)(p) + (n)))
#define F(p, n) (*(float *)((char *)(p) + (n)))
#define B(p, n) (*(unsigned char *)((char *)(p) + (n)))

/* Per-frame update of a charging weapon: it charges, fires a pulse that damages everything in range and plays a sound for the hits. */
void func_L00_00408E58(char *object)
{
    char *vars = *(char **)(object + 104);
    int base[4] __attribute__((aligned(16)));
    int v[4] __attribute__((aligned(16)));
    int out[4] __attribute__((aligned(16)));
    char *list[32];
    struct {
        int count;
        int *timer;
    } hits;
    int i;

    InitMobyOnFirstFrame(object);
    if (gHeroState.state == 1) {
        ref_L00_00408E58_00(29, 1);
    }
    if (B(object, 0x31)) {
        D_L00_0025C64C = 0.1f;
    }
    if (B(object, 0x42) == B(object, 0x43) && (B(object, 0x60) & 2)) {
        StartAnimationBlendedWithFlags(object, 1, 0, 2, 0);
    }
    FastVecAdd(base, base, object + 16);
    FastVectorHelperB(vars);
    if (B(object, 32) == 1) {
        if (D_L00_001A8F00 || gHeroState.disabled || !(D_00138324 & gHeroState.mask) || gHeroState.level < 23) {
            return;
        }
        if (get_ammo(-1)) {
            start_equipped_item_animation();
            I(vars, 24) = CopyRecordsToFreeSlots(D_L00_0029FBE0);
            B(object, 32) = 2;
            I(vars, 4) = D_L00_001B0F90;
        } else {
            PlayMobySound(4, 0, object);
        }
        {
            RateEntry *entry = &gWeaponTable_L00[D_00139593];
            F(vars, 0) = 1.0f / entry->rate;
        }
    } else if (B(object, 32) == 2) {
        if (FastFloatHelperD(vars + 16)) {
            B(object, 32) = 4;
            I(vars, 16) = 30;
            I(vars, 20) = 0;
        }
        if (I(vars, 16) == 10) {
            StartAnimationBlendedWithFlags(object, 2, 0, 3, 0);
            PlayMobySound(1, 0, object);
        }
    } else if (B(object, 32) == 4) {
        if (FastFloatHelperD(vars + 16)) {
            B(object, 32) = 5;
            I(vars, 20) = 0;
            I(vars, 16) = 30;
            StartAnimationBlendedWithFlags(object, 3, 0, 3, 0);
        } else if (!I(vars, 20)) {
            qcopy(v, gHeroState.object + 0xc0);
            vec_scale_to_length(v, v, 1.0f);
            FastVecAdd(out, base, v);
            SpawnSparkEffectMoby(out, 1, object);
            I(vars, 20) = 1;
        }
    } else if (B(object, 32) == 5) {
        if (FastFloatHelperD(vars + 8)) {
            B(object, 32) = 3;
            I(vars, 8) = 64;
            StartAnimationBlendedWithFlags(object, 4, 0, 3, 0);
        } else {
            func_002E6EF8(DrawScreenFlashFade, object);
        }
    } else if (B(object, 32) == 3) {
        int done = 0;

        qcopy(v, D_L00_001B8FF0);
        hits.timer = (int *)(vars + 4);
        FastMemoryHelperB(list, 128);
        ReleaseDeadOrExpiredSlots(object);
        SelectBestTargetInCone(object + 16, v, &hits.count, list, 32, 0, 3.1415929794311523f, 1.047197699546814f, 40.0f, 0.0f,
                      0.0f, 0, 0);
        for (i = 0; i < hits.count; i++) {
            char *p;
            int active;

            qcopy_nc(out, list[i] + 16);
            p = GetMobyPrivateValue0(list[i]);
            active = 1;
            if (p) {
                F(out, 8) += F(p, 16) * 1.5f;
                if (F(p, 0) > 100.0f) {
                    active = 0;
                }
            }
            if (list[i] && B(list[i], 32) != 254 && B(list[i], 32) != 253) {
                if (*(short *)(list[i] + 0xaa) == 0xa8d /* Swamp Monster I Arm */) {
                    B(list[i], 0x95) = 9;
                }
                if (*(short *)(list[i] + 0xaa) == 0xa8e /* Swamp Monster I Eye */) {
                    B(list[i], 0x95) = 7;
                }
                if (*(short *)(list[i] + 0xaa) == 0x1002 /* Desert Dune Monster */) {
                    B(list[i], 32) = 7;
                }
            }
            if (active) {
                if ((p && B(p, 14) == 1) || B(p, 14) == 2) {
                    SpawnSparkEffectMoby(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits(list[i], 0, 3);
                    B(p, 14) = 2;
                } else if (p && B(p, 14) != 3) {
                    SpawnSparkEffectMoby(out, 0, 0);
                    I(vars, 28)++;
                    SetDeathBits(list[i], 0, 3);
                    func_00310440(list[i]);
                }
            } else {
                F(p, 0) -= 20.0f;
                if (F(p, 0) < 0.0f) {
                    F(p, 0) = 0.0f;
                }
            }
        }
        done = FastFloatHelperD(hits.timer);
        if (done) {
            if (I(vars, 28)) {
                PlayMobySound(2, 0, object);
            } else {
                PlayMobySound(3, 0, object);
            }
            I(vars, 28) = 0;
            B(object, 32) = 0;
            SpendWeaponAmmo(-1, 1);
        }
    }
}
