/* Per-frame update of the grelbin-style effect moby (L18, L19 and L20): a seven-state switch that
   blends the instance's colors and vectors from the state timer, steps the timer, and
   handles the hero hit loop and the sound slots. Needs -g and -ffast-math (min/max). */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;

/* the frame counter of the effect moby, a u16 at +0x96 */
static inline u16 moby_timer(char *m)
{
    return *(u16 *)(m + 0x96);
}

/* the moby's per-instance variables (m + 0x68) */
typedef struct {
    u8 pad0[8];
    s32 i8;
    u8 padC[0x14];
    f32 v20[4][4];
    f32 v60[4];
    f32 v70[4];
    f32 v80[4];
    f32 v90[4];
    f32 vA0[4];
    s32 iB0;
    s32 iB4;
    s32 iB8;
    s32 iBC;
    f32 fC0;
    s32 iC4;
    s32 iC8;
    s32 iCC;
    f32 fD0;
    s32 iD4;
    f32 fD8;
    f32 fDC;
    s32 iE0;
    s32 iE4;
} PvVars;

/* one 0x100-byte record of the level's moby-class table at D_L18_001B281C */
typedef struct {
    u8 pad0[0x10];
    f32 pos[4];
    u8 pad20[3];
    u8 b23;
    u8 pad24[0x10];
    u16 h34;
    u8 pad36[0x62];
    s32 i98;
    u8 pad9C[0x24];
    f32 mat[4][4];
} ClassRec;

extern char D_00189E20[];
extern u8 D_00188660[];
extern int D_001A7A00[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern char D_L18_001B97C0[];
extern char *D_L18_001FE480[];
extern ClassRec *D_L18_001B281C[] __attribute__((sda));
extern char *D_L18_001C3C80[];
extern f32 D_L18_001B06AC[] __attribute__((sda));
extern f32 D_L18_001B06B0[] __attribute__((sda));
extern f32 D_L18_001B05E0 __attribute__((sda));
extern f32 D_L18_001B05E4 __attribute__((sda));
extern f32 D_L18_001B05F0[4] __attribute__((sda));
extern f32 D_L18_001B0600 __attribute__((sda));
extern f32 D_L18_001B0604 __attribute__((sda));
extern f32 D_L18_001B0608 __attribute__((sda));
extern int D_L18_001B060C __attribute__((sda));
extern f32 D_L18_001B0620[4] __attribute__((sda));
extern int D_L18_001B0630 __attribute__((sda));
extern f32 D_L18_001B0634 __attribute__((sda));
extern f32 D_L18_001B0638 __attribute__((sda));
extern f32 D_L18_001B063C __attribute__((sda));
extern f32 D_L18_001B0640 __attribute__((sda));
extern f32 D_L18_001B0644 __attribute__((sda));
extern f32 D_L18_001B0648 __attribute__((sda));
extern f32 D_L18_001B0650[2] __attribute__((sda));
extern f32 D_L18_001B0658[2] __attribute__((sda));
extern f32 D_L18_001B0660 __attribute__((sda));
extern f32 D_L18_001B0668[2] __attribute__((sda));
extern f32 D_L18_001B0670 __attribute__((sda));
extern f32 D_L18_001B0680[4] __attribute__((sda));
extern f32 D_L18_001B0690[4] __attribute__((sda));
extern f32 D_L18_001B06A8 __attribute__((sda));
extern int D_L18_001B06B8[] __attribute__((sda));
extern int D_L18_001B2348 __attribute__((sda));
extern char D_L18_003FD630[];
extern char D_L18_003FCA38[];
extern char D_L18_003FD730[];

extern int func_00277F48(float, void *, int, void *, void *);
extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282E48(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002836E8(float *, float *);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(float, int, int);
extern void func_002A7750(char *, int, int);
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern int func_002ACBC8(void *, int);
extern void func_002AD6F0(void *, void *, void *, void *);
extern int func_002B3868(char *);
extern void func_002BE278(void *, void *, int, float);
extern void func_002C9828(char *, int, void *, void *, int, float);
extern void func_002E59F8(int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L00_002B30E8(void);
extern void func_L00_002E6CF0(void *, void *);
extern int func_L00_00329520(void *, int);
extern void func_L08_002F2D10(void *, void *);
extern void func_L18_003FC958(char *, int);
extern void func_L18_003FCC48(char *);
extern void func_L18_003FCD70(char *);
extern void func_L18_002E0070(int, int);

/* Updates the train: it rides its rail path or follows another object, speeds up
   and slows down, falls when released, and plays its sounds and effects. */
void func_L18_003FB708(char *moby)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 vm[3][4] __attribute__((aligned(16)));
    PvVars *vars;
    char *path;
    char *rec;
    ClassRec *classTable;
    ClassRec *classTable2;
    char *src;
    char *sound;
    char *target;
    int hitCount;
    int i;
    int k;
    int parentIndex;
    int savedState;
    int j;
    float f;
    float g;
    float r;

    vars = *(PvVars **)(moby + 0x68);
    qcopy(pos, moby + 0x10);
    qcopy(rot, moby + 0xF0);
    if (vars->iD4 != -1 && IsPointInsideRegion(gCameraPosition_L18, vars->iD4) != 0) {
        StartEnterAnimation(moby, 0);
    }
    if (vars->iE0 > 0) {
        FastFloatHelperD(&vars->iE0);
        if (vars->iE0 < 2) {
            RecordHeroPlayCounters();
        }
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        qcopy(vars->v60, moby + 0x10);
        qcopy(vars->v70, moby + 0xF0);
        if (vars->iB0 != -1) {
            vars->fD8 = 0.0f;
            path = D_L18_001FE480[vars->iB0];
            r = 1.0f / fast_vec_dist(path + 0x10, path + 0x20);
            vars->fDC = r * (0.016666668f * vars->fD0);
            qcopy(moby + 0x10, path + 0x10);
            vars->iE0 = -1;
        }
        if (*(s16 *)(moby + 0xAA) != 0xD9B /* Train */ && *(s16 *)(moby + 0xAA) != 0x11CF /* moby class 4559 */) {
            vars->i8 = 0;
        }
        if (vars->iC8 != -1) {
            FastVecSub(vars->vA0, moby + 0x10, gMobyTable_L18[0][vars->iC8].pos);
            FastMatrixHelperC(vm[0], (float *)gMobyTable_L18[0][vars->iC8].mat);
            matrix_mul_vec3(vars->vA0, vars->vA0, vm[0]);
        }
        if (vars->iB4 != -1) {
            *(u16 *)(moby + 0x34) |= 1;
            SetMobyState(moby, 4, -1);
        } else {
            SetMobyState(moby, 1, -1);
        }
        break;
    case 4:
        if (SetFirstPendingFlag(moby) != 0) {
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (IsPointInCuboid(gHeroState + 0x80, vars->iB4) != 0) {
            if (vars->iC8 == -1) {
                *(u16 *)(moby + 0x34) |= 0x100;
                vec_scale_to_length(moby + 0xC0, moby + 0xC0, 0.03234f);
                SetMobyState(moby, 7, -1);
            } else {
                SetMobyState(moby, 1, -1);
            }
        }
        break;
    case 1:
        if (SetFirstPendingFlag(moby) != 0) {
            vec_scale_to_length(vars->v80, moby + 0xC0, vars->fD0 * 0.016666668f);
        }
        if (vars->iB0 != -1) {
            SamplePathPosition(D_L18_001FE480[vars->iB0], 0, moby + 0x10, moby + 0xF0, 0, vars->fD8);
            vars->fD8 = vars->fD8 + vars->fDC;
        } else {
            if (vars->iC8 != -1) {
                classTable = gMobyTable_L18[0];
                *(u16 *)(moby + 0x34) = classTable[vars->iC8].h34;
                *(u8 *)(moby + 0x23) = classTable[vars->iC8].b23;
                classTable2 = gMobyTable_L18[0];
                *(u16 *)(moby + 0x34) = classTable2[vars->iC8].h34;
                *(int *)(moby + 0x98) = classTable2[vars->iC8].i98;
                parentIndex = vars->iC8;
                for (k = 0; k < 4; k++) {
                    qcopy(moby + 0xC0 + k * 16, classTable2[parentIndex].mat[k]);
                }
                matrix_mul_vec3(vm[0], vars->vA0, moby + 0xC0);
                FastVecAdd(moby + 0x10, vm[0], gMobyTable_L18[0][vars->iC8].pos);
            } else {
                FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
            }
            if (vars->iE4 == -1
                || *(char **)((sound = (char *)gSoundState + vars->iE4 * 0x70) + 0x88) != moby
                || *(u8 *)(sound + 0x74) == 0) {
                vars->iE4 = PlaySoundFromClassBank(0, 4, moby, 0xD5C);
            }
            if (vars->iB8 != -1 && vars->iC8 == -1 && IsPointInCuboid(moby + 0x10, vars->iB8) != 0) {
                if (vars->iE4 != -1) {
                    sound = (char *)gSoundState + vars->iE4 * 0x70;
                    if (*(char **)(sound + 0x88) == moby && *(u8 *)(sound + 0x74) != 0) {
                        StopSoundVoice(vars->iE4);
                    }
                }
                vars->iE4 = -1;
                if (*(s16 *)(moby + 0xAA) == 0xD9B /* Train */ || *(s16 *)(moby + 0xAA) == 0x11CF /* moby class 4559 */) {
                    SetMobyState(moby, 5, -1);
                } else {
                    SetMobyState(moby, 6, -1);
                }
            }
        }
        if (*(s16 *)(moby + 0xAA) == 0xD9B /* Train */) {
            matrix_mul_vec3(vm[0], D_L18_001B05F0, moby + 0xC0);
            FastVecAdd(vm[0], vm[0], moby + 0x10);
            hitCount = ProcessCollisionHit(D_L18_001B0600, vm[0], 0, moby, 0);
            if (hitCount != 0) {
                for (j = 0; j < hitCount; j++) {
                    target = gNearbyHitTargets[j];
                    if (target == ((Hero *)gHeroState)->ptr[0x2290 / 4]) {
                        FastVecScale(vm[1], moby + 0xC0, -D_L18_001B0608);
                        vm[1][2] = D_L18_001B0608 * 4.0f;
                        vm[1][3] = 5627.9248f;
                        SetHeroAction_L18(0, 1);
                        g = (f32)D_001A7A00[0] * 30.0f;
                        QueueImpactEffect(target, moby, 0x10001, gHeroState + 0x80, vm[1], g > 100.0f ? g : 100.0f);
                        vars->iE0 = D_L18_001B060C;
                        SpawnExplosion(gHeroState + 0x80, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                    } else {
                        FastVecScale(vm[1], moby + 0xC0, D_L18_001B0604);
                        vm[1][3] = 5627.9248f;
                        vm[1][2] = D_L18_001B0604 * 4.0f;
                        QueueImpactEffect(target, moby, 0x10001, target + 0x10, vm[1], 50.0f);
                    }
                }
            }
            SpawnUpwardParticles(moby);
            if (*(u8 *)(moby + 0x31) != 0 && (D_L18_001B2348 & 0xF) == (((int)moby >> 8) & 0xF)) {
                for (i = 0; i < D_L18_001B0630; i++) {
                    matrix_mul_vec3(vm[1], D_L18_001B0620, moby + 0xC0);
                    FastVecAdd(vm[1], vm[1], moby + 0x10);
                    f = RandomFloatRange(D_L18_001B063C, D_L18_001B0640) * 0.016666668f;
                    vec_scale_to_length(vm[2], moby + 0xD0, RandomIntBelow(2) != 0 ? -f : f);
                    vm[2][2] = RandomFloatRange(-0.083333336f, 0.016666668f);
                    vm[2][3] = -0.008333334f;
                    SpawnWhiteFlashParticle(vm[1], vm[2], 0, RandomFloatRange(D_L18_001B0634, D_L18_001B0638));
                }
            }
        }
        break;
    case 5:
        SetFirstPendingFlag(moby);
        r = D_L18_001B05E4 * 0.00029088825f;
        vars->v80[2] = vars->v80[2] - D_L18_001B05E0 * 0.00027777778f;
        *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4), r);
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 6:
        if (SetFirstPendingFlag(moby) != 0) {
            *(u8 *)(moby + 0xBC) = 0;
            *(u16 *)(moby + 0x96) = 0;
            *(u16 *)(moby + 0x34) |= 0x100;
            vars->fC0 = D_L18_001B06A8;
            matrix_mul_vec3(vars->v90, D_L18_001B0680, moby + 0xC0);
            FastVecAdd(vars->v90, moby + 0x10, vars->v90);
            vec_scale_to_length(vars->v80, moby + 0xC0, D_L18_001B0644 * 0.016666668f);
            *(u16 *)(moby + 0x34) |= 8;
            PlaySoundFromClassBank(1, 0, moby, 0xD5C);
            if (*(u8 *)(moby + 0x31) != 0) {
                SpawnParticleSpray(moby);
            }
        } else if (*(u8 *)(moby + 0xBC) == 0) {
            FastVecScale(moby + 0xC0, moby + 0xC0, D_L18_001B0658[gIsPalVideo[0] != 0] * 0.016666668f + 1.0f);
            vars->fC0 = D_L18_001B06A8 + (D_L18_001B06AC[0] - D_L18_001B06A8) * (IntToFloat(moby_timer(moby)) / D_L18_001B0660);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0660, D_L18_001B06B8[0], D_L18_001B06B8[1]);
            if (D_L18_001B0660 < (f32)moby_timer(moby)) {
                *(u8 *)(moby + 0xBC) = 1;
                vec_scale_to_length(vars->v80, moby + 0xC0, D_L18_001B0648 * 0.016666668f);
                *(u16 *)(moby + 0x96) = 0;
            }
        } else if (*(u8 *)(moby + 0xBC) == 1) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f - D_L18_001B0668[gIsPalVideo[0] != 0] * 0.016666668f);
            vars->fC0 = D_L18_001B06AC[0] + (D_L18_001B06B0[0] - D_L18_001B06AC[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0670);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0670, D_L18_001B06B8[1], D_L18_001B06B8[2]);
            *(u8 *)(moby + 0x23) = FloatToInt((1.0f - IntToFloat(moby_timer(moby)) / D_L18_001B0670) * 128.0f);
            if (D_L18_001B0670 < (f32)moby_timer(moby) || *(f32 *)(moby + 0xE8) < 0.0f) {
                if (vars->iBC != 0) {
                    vars->fD8 = 0.0f;
                    qcopy(moby + 0x10, vars->v60);
                    qcopy(moby + 0xF0, vars->v70);
                    SetMobyState(moby, 7, -1);
                } else {
                    *(u16 *)(moby + 0x34) &= ~0x100;
                    StartEnterAnimation(moby, 1);
                }
            }
        }
        if (*(u8 *)(moby + 0x31) != 0) {
            QueueDrawCallback(D_L18_003FD630, moby);
            QueueDrawCallback(D_L18_003FCA38, moby);
            AddDrawCallbackToList1(D_L18_003FD730, moby);
        }
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 7:
        if (SetFirstPendingFlag(moby) != 0) {
            *(u8 *)(moby + 0xBC) = 1;
            *(u16 *)(moby + 0x96) = 0;
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & ~1) | 0x100;
            vars->fC0 = D_L18_001B06A8;
            *(u8 *)(moby + 0x23) = 0;
            for (i = 0; i < 3; i++) {
                vec_scale_to_length(vm[i], moby + 0xC0 + i * 0x10, 1.0f);
            }
            matrix_mul_vec3(vars->v90, D_L18_001B0690, vm[0]);
            FastVecScale(vars->v90, vars->v90, IntToFloat(vars->iCC) + 1.0f);
            FastVecAdd(vars->v90, moby + 0x10, vars->v90);
            vec_scale_to_length(vars->v80, moby + 0xC0, (IntToFloat(vars->iCC) + 1.0f) * (0.016666668f * D_L18_001B0650[gIsPalVideo[0] != 0]));
            *(u16 *)(moby + 0x34) |= 8;
            if (*(u8 *)(moby + 0x31) != 0) {
                SpawnParticleSpray(moby);
            }
            PlaySoundFromClassBank(1, 0, moby, 0xD5C);
        } else if (*(u8 *)(moby + 0xBC) == 1) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f / (1.0f - D_L18_001B0668[gIsPalVideo[0] != 0] * 0.016666668f));
            vars->fC0 = D_L18_001B06B0[0] + (D_L18_001B06AC[0] - D_L18_001B06B0[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0670);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0670, D_L18_001B06B8[2], D_L18_001B06B8[1]);
            *(u8 *)(moby + 0x23) = FloatToInt(IntToFloat(moby_timer(moby)) * 128.0f / D_L18_001B0670);
            if (D_L18_001B0670 < (f32)moby_timer(moby) || *(f32 *)(moby + 0xE8) < 0.0f) {
                *(u8 *)(moby + 0x23) = 0x80;
                *(u8 *)(moby + 0xBC) = 0;
                *(u16 *)(moby + 0x34) &= ~8;
                vec_scale_to_length(vars->v80, moby + 0xC0, vars->fD0 * 0.016666668f);
                *(u16 *)(moby + 0x96) = 0;
            }
        } else if (*(u8 *)(moby + 0xBC) == 0) {
            FastVecScale(moby + 0xC0, moby + 0xC0, 1.0f / (D_L18_001B0658[gIsPalVideo[0] != 0] * 0.016666668f + 1.0f));
            vars->fC0 = D_L18_001B06AC[0] + (D_L18_001B06A8 - D_L18_001B06AC[0]) * (IntToFloat(moby_timer(moby)) / D_L18_001B0660);
            vars->iC4 = FastTweenColor(IntToFloat(moby_timer(moby)) / D_L18_001B0660, D_L18_001B06B8[1], D_L18_001B06B8[0]);
            if (D_L18_001B0660 < (f32)moby_timer(moby)) {
                *(u16 *)(moby + 0x34) &= ~0x100;
                SetMobyState(moby, 1, -1);
            }
        }
        if (vars->iE4 == -1
            || *(char **)((sound = (char *)gSoundState + vars->iE4 * 0x70) + 0x88) != moby
            || *(u8 *)(sound + 0x74) == 0) {
            vars->iE4 = PlaySoundFromClassBank(0, 4, moby, 0xD5C);
        }
        if (*(u8 *)(moby + 0x31) != 0) {
            QueueDrawCallback(D_L18_003FD630, moby);
            QueueDrawCallback(D_L18_003FCA38, moby);
            AddDrawCallbackToList1(D_L18_003FD730, moby);
        }
        FastVecAdd(moby + 0x10, moby + 0x10, vars->v80);
        break;
    case 2:
        if (vars->iD4 != -1 && IsPointInsideRegion(gCameraPosition_L18, vars->iD4) == 0) {
            rec = *(char **)(moby + 0x24);
            savedState = *(u8 *)(moby + 0x94);
            *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(moby + 0x98) = *(int *)(rec + 0x10);
            *(int *)(moby + 0x98) = *(int *)(rec + 0x10);
            *(u8 *)(moby + 0x20) = savedState;
        }
        break;
    }
    FastVecSub(vm[0], moby + 0x10, pos);
    CombineTransformsAndStore(vars->v20, vm[0], rot, moby + 0xF0);
    if (*(f32 *)(moby + 0x18) < 85.0f && *(u8 *)(moby + 0x20) == 5) {
        SpawnExplosion(moby + 0x10, 0, 5, 0, 5, 0x14, 0, 0, 4.0f, 0.0f, 1, 0, 0, 0);
        StartEnterAnimation(moby, 1);
    }
    if (moby_timer(moby) < 0xFFFF) {
        *(u16 *)(moby + 0x96) = moby_timer(moby) + 1;
    }
    
}
