/* func_PAL_L18_003FF850, the PAL copy of func_L18_003FB708: the same C at 50 Hz (frame constants
   rescaled, tick counts through (x * 5 + 2) / 6).
   Per-frame update of the grelbin-style effect moby (L18, L19 and L20): a seven-state switch that
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

void func_PAL_L18_003FF850(char *m)
{
    f32 pos[4] __attribute__((aligned(16)));
    f32 rot[4] __attribute__((aligned(16)));
    f32 vm[3][4] __attribute__((aligned(16)));
    PvVars *pv;
    char *path;
    char *rec;
    ClassRec *tbl;
    ClassRec *tbl2;
    char *src;
    char *snd;
    char *t;
    int n;
    int i;
    int k;
    int cls;
    int st;
    int j;
    float f;
    float g;
    float r;

    pv = *(PvVars **)(m + 0x68);
    qcopy(pos, m + 0x10);
    qcopy(rot, m + 0xF0);
    if (pv->iD4 != -1 && func_L00_00329520(D_L18_001B97C0, pv->iD4) != 0) {
        func_L18_003FC958(m, 0);
    }
    if (pv->iE0 > 0) {
        func_00282948(&pv->iE0);
        if (pv->iE0 < 2) {
            func_L00_002B30E8();
        }
    }
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        qcopy(pv->v60, m + 0x10);
        qcopy(pv->v70, m + 0xF0);
        if (pv->iB0 != -1) {
            pv->fD8 = 0.0f;
            path = D_L18_001FE480[pv->iB0];
            r = 1.0f / func_00282E48(path + 0x10, path + 0x20);
            pv->fDC = r * (0.020000001f * pv->fD0);
            qcopy(m + 0x10, path + 0x10);
            pv->iE0 = -1;
        }
        if (*(s16 *)(m + 0xAA) != 0xD9B && *(s16 *)(m + 0xAA) != 0x11CF) {
            pv->i8 = 0;
        }
        if (pv->iC8 != -1) {
            func_00282CF0(pv->vA0, m + 0x10, D_L18_001B281C[0][pv->iC8].pos);
            func_002836E8(vm[0], (float *)D_L18_001B281C[0][pv->iC8].mat);
            func_00283098(pv->vA0, pv->vA0, vm[0]);
        }
        if (pv->iB4 != -1) {
            *(u16 *)(m + 0x34) |= 1;
            func_002A7750(m, 4, -1);
        } else {
            func_002A7750(m, 1, -1);
        }
        break;
    case 4:
        if (func_002B3868(m) != 0) {
            *(u16 *)(m + 0x34) |= 1;
        }
        if (func_002ACBC8(D_00189E20 + 0x80, pv->iB4) != 0) {
            if (pv->iC8 == -1) {
                *(u16 *)(m + 0x34) |= 0x100;
                func_00282F20(m + 0xC0, m + 0xC0, 0.03234f);
                func_002A7750(m, 7, -1);
            } else {
                func_002A7750(m, 1, -1);
            }
        }
        break;
    case 1:
        if (func_002B3868(m) != 0) {
            func_00282F20(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
        }
        if (pv->iB0 != -1) {
            func_002C9828(D_L18_001FE480[pv->iB0], 0, m + 0x10, m + 0xF0, 0, pv->fD8);
            pv->fD8 = pv->fD8 + pv->fDC;
        } else {
            if (pv->iC8 != -1) {
                tbl = D_L18_001B281C[0];
                *(u16 *)(m + 0x34) = tbl[pv->iC8].h34;
                *(u8 *)(m + 0x23) = tbl[pv->iC8].b23;
                tbl2 = D_L18_001B281C[0];
                *(u16 *)(m + 0x34) = tbl2[pv->iC8].h34;
                *(int *)(m + 0x98) = tbl2[pv->iC8].i98;
                cls = pv->iC8;
                for (k = 0; k < 4; k++) {
                    qcopy(m + 0xC0 + k * 16, tbl2[cls].mat[k]);
                }
                func_00283098(vm[0], pv->vA0, m + 0xC0);
                func_00282CC0(m + 0x10, vm[0], D_L18_001B281C[0][pv->iC8].pos);
            } else {
                func_00282CC0(m + 0x10, m + 0x10, pv->v80);
            }
            if (pv->iE4 == -1
                || *(char **)((snd = (char *)D_00188660 + pv->iE4 * 0x70) + 0x88) != m
                || *(u8 *)(snd + 0x74) == 0) {
                pv->iE4 = func_002E5DA0(0, 4, m, 0xD5C);
            }
            if (pv->iB8 != -1 && pv->iC8 == -1 && func_002ACBC8(m + 0x10, pv->iB8) != 0) {
                if (pv->iE4 != -1) {
                    snd = (char *)D_00188660 + pv->iE4 * 0x70;
                    if (*(char **)(snd + 0x88) == m && *(u8 *)(snd + 0x74) != 0) {
                        func_002E59F8(pv->iE4);
                    }
                }
                pv->iE4 = -1;
                if (*(s16 *)(m + 0xAA) == 0xD9B || *(s16 *)(m + 0xAA) == 0x11CF) {
                    func_002A7750(m, 5, -1);
                } else {
                    func_002A7750(m, 6, -1);
                }
            }
        }
        if (*(s16 *)(m + 0xAA) == 0xD9B) {
            func_00283098(vm[0], D_L18_001B05F0, m + 0xC0);
            func_00282CC0(vm[0], vm[0], m + 0x10);
            n = func_00277F48(D_L18_001B0600, vm[0], 0, m, 0);
            if (n != 0) {
                for (j = 0; j < n; j++) {
                    t = D_L18_001C3C80[j];
                    if (t == ((Hero *)D_00189E20)->ptr[0x2290 / 4]) {
                        func_00282D30(vm[1], m + 0xC0, -D_L18_001B0608);
                        vm[1][2] = D_L18_001B0608 * 4.0f;
                        vm[1][3] = 5627.9248f;
                        func_L18_002E0070(0, 1);
                        g = (f32)D_001A7A00[0] * 30.0f;
                        func_002A8F70(t, m, 0x10001, D_00189E20 + 0x80, vm[1], g > 100.0f ? g : 100.0f);
                        pv->iE0 = (D_L18_001B060C * 5 + 2) / 6;
                        func_0032C700(D_00189E20 + 0x80, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
                    } else {
                        func_00282D30(vm[1], m + 0xC0, D_L18_001B0604);
                        vm[1][3] = 5627.9248f;
                        vm[1][2] = D_L18_001B0604 * 4.0f;
                        func_002A8F70(t, m, 0x10001, t + 0x10, vm[1], 50.0f);
                    }
                }
            }
            func_L18_003FCC48(m);
            if (*(u8 *)(m + 0x31) != 0 && (D_L18_001B2348 & 0xF) == (((int)m >> 8) & 0xF)) {
                for (i = 0; i < D_L18_001B0630; i++) {
                    func_00283098(vm[1], D_L18_001B0620, m + 0xC0);
                    func_00282CC0(vm[1], vm[1], m + 0x10);
                    f = func_002A7878(D_L18_001B063C, D_L18_001B0640) * 0.020000001f;
                    func_00282F20(vm[2], m + 0xD0, func_002A77E0(2) != 0 ? -f : f);
                    vm[2][2] = func_002A7878(-0.10000001f, 0.020000001f);
                    vm[2][3] = -0.012f;
                    func_002BE278(vm[1], vm[2], 0, func_002A7878(D_L18_001B0634, D_L18_001B0638));
                }
            }
        }
        break;
    case 5:
        func_002B3868(m);
        r = D_L18_001B05E4 * 0.0003490659f;
        pv->v80[2] = pv->v80[2] - D_L18_001B05E0 * 0.00040000002f;
        *(f32 *)(m + 0xF4) = func_00283B98(*(f32 *)(m + 0xF4), r);
        func_00282CC0(m + 0x10, m + 0x10, pv->v80);
        break;
    case 6:
        if (func_002B3868(m) != 0) {
            *(u8 *)(m + 0xBC) = 0;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) |= 0x100;
            pv->fC0 = D_L18_001B06A8;
            func_00283098(pv->v90, D_L18_001B0680, m + 0xC0);
            func_00282CC0(pv->v90, m + 0x10, pv->v90);
            func_00282F20(pv->v80, m + 0xC0, D_L18_001B0644 * 0.020000001f);
            *(u16 *)(m + 0x34) |= 8;
            func_002E5DA0(1, 0, m, 0xD5C);
            if (*(u8 *)(m + 0x31) != 0) {
                func_L18_003FCD70(m);
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            func_00282D30(m + 0xC0, m + 0xC0, D_L18_001B0658[D_001A7B90[0] != 0] * 0.020000001f + 1.0f);
            pv->fC0 = D_L18_001B06A8 + (D_L18_001B06AC[0] - D_L18_001B06A8) * (func_00283CE0(moby_timer(m)) / ((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = func_00283D38(func_00283CE0(moby_timer(m)) / ((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f), D_L18_001B06B8[0], D_L18_001B06B8[1]);
            if (((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f) < (f32)moby_timer(m)) {
                *(u8 *)(m + 0xBC) = 1;
                func_00282F20(pv->v80, m + 0xC0, D_L18_001B0648 * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 1) {
            func_00282D30(m + 0xC0, m + 0xC0, 1.0f - D_L18_001B0668[D_001A7B90[0] != 0] * 0.020000001f);
            pv->fC0 = D_L18_001B06AC[0] + (D_L18_001B06B0[0] - D_L18_001B06AC[0]) * (func_00283CE0(moby_timer(m)) / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = func_00283D38(func_00283CE0(moby_timer(m)) / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f), D_L18_001B06B8[1], D_L18_001B06B8[2]);
            *(u8 *)(m + 0x23) = func_00283CF0((1.0f - func_00283CE0(moby_timer(m)) / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f)) * 128.0f);
            if (D_L18_001B0670 < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                if (pv->iBC != 0) {
                    pv->fD8 = 0.0f;
                    qcopy(m + 0x10, pv->v60);
                    qcopy(m + 0xF0, pv->v70);
                    func_002A7750(m, 7, -1);
                } else {
                    *(u16 *)(m + 0x34) &= ~0x100;
                    func_L18_003FC958(m, 1);
                }
            }
        }
        if (*(u8 *)(m + 0x31) != 0) {
            func_L08_002F2D10(D_L18_003FD630, m);
            func_L08_002F2D10(D_L18_003FCA38, m);
            func_L00_002E6CF0(D_L18_003FD730, m);
        }
        func_00282CC0(m + 0x10, m + 0x10, pv->v80);
        break;
    case 7:
        if (func_002B3868(m) != 0) {
            *(u8 *)(m + 0xBC) = 1;
            *(u16 *)(m + 0x96) = 0;
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & ~1) | 0x100;
            pv->fC0 = D_L18_001B06A8;
            *(u8 *)(m + 0x23) = 0;
            for (i = 0; i < 3; i++) {
                func_00282F20(vm[i], m + 0xC0 + i * 0x10, 1.0f);
            }
            func_00283098(pv->v90, D_L18_001B0690, vm[0]);
            func_00282D30(pv->v90, pv->v90, func_00283CE0(pv->iCC) + 1.0f);
            func_00282CC0(pv->v90, m + 0x10, pv->v90);
            func_00282F20(pv->v80, m + 0xC0, (func_00283CE0(pv->iCC) + 1.0f) * (0.020000001f * D_L18_001B0650[D_001A7B90[0] != 0]));
            *(u16 *)(m + 0x34) |= 8;
            if (*(u8 *)(m + 0x31) != 0) {
                func_L18_003FCD70(m);
            }
            func_002E5DA0(1, 0, m, 0xD5C);
        } else if (*(u8 *)(m + 0xBC) == 1) {
            func_00282D30(m + 0xC0, m + 0xC0, 1.0f / (1.0f - D_L18_001B0668[D_001A7B90[0] != 0] * 0.020000001f));
            pv->fC0 = D_L18_001B06B0[0] + (D_L18_001B06AC[0] - D_L18_001B06B0[0]) * (func_00283CE0(moby_timer(m)) / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = func_00283D38(func_00283CE0(moby_timer(m)) / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f), D_L18_001B06B8[2], D_L18_001B06B8[1]);
            *(u8 *)(m + 0x23) = func_00283CF0(func_00283CE0(moby_timer(m)) * 128.0f / ((D_L18_001B0670 * 5.0f + 2.0f) / 6.0f));
            if (D_L18_001B0670 < (f32)moby_timer(m) || *(f32 *)(m + 0xE8) < 0.0f) {
                *(u8 *)(m + 0x23) = 0x80;
                *(u8 *)(m + 0xBC) = 0;
                *(u16 *)(m + 0x34) &= ~8;
                func_00282F20(pv->v80, m + 0xC0, pv->fD0 * 0.020000001f);
                *(u16 *)(m + 0x96) = 0;
            }
        } else if (*(u8 *)(m + 0xBC) == 0) {
            func_00282D30(m + 0xC0, m + 0xC0, 1.0f / (D_L18_001B0658[D_001A7B90[0] != 0] * 0.020000001f + 1.0f));
            pv->fC0 = D_L18_001B06AC[0] + (D_L18_001B06A8 - D_L18_001B06AC[0]) * (func_00283CE0(moby_timer(m)) / ((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f));
            pv->iC4 = func_00283D38(func_00283CE0(moby_timer(m)) / ((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f), D_L18_001B06B8[1], D_L18_001B06B8[0]);
            if (((D_L18_001B0660 * 5.0f + 2.0f) / 6.0f) < (f32)moby_timer(m)) {
                *(u16 *)(m + 0x34) &= ~0x100;
                func_002A7750(m, 1, -1);
            }
        }
        if (pv->iE4 == -1
            || *(char **)((snd = (char *)D_00188660 + pv->iE4 * 0x70) + 0x88) != m
            || *(u8 *)(snd + 0x74) == 0) {
            pv->iE4 = func_002E5DA0(0, 4, m, 0xD5C);
        }
        if (*(u8 *)(m + 0x31) != 0) {
            func_L08_002F2D10(D_L18_003FD630, m);
            func_L08_002F2D10(D_L18_003FCA38, m);
            func_L00_002E6CF0(D_L18_003FD730, m);
        }
        func_00282CC0(m + 0x10, m + 0x10, pv->v80);
        break;
    case 2:
        if (pv->iD4 != -1 && func_L00_00329520(D_L18_001B97C0, pv->iD4) == 0) {
            rec = *(char **)(m + 0x24);
            st = *(u8 *)(m + 0x94);
            *(u16 *)(m + 0x34) = (*(u16 *)(m + 0x34) & 0xFFBE) | 0x1000;
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(int *)(m + 0x98) = *(int *)(rec + 0x10);
            *(u8 *)(m + 0x20) = st;
        }
        break;
    }
    func_00282CF0(vm[0], m + 0x10, pos);
    func_002AD6F0(pv->v20, vm[0], rot, m + 0xF0);
    if (*(f32 *)(m + 0x18) < 85.0f && *(u8 *)(m + 0x20) == 5) {
        func_0032C700(m + 0x10, 0, 5, 0, 5, 0x14, 0, 0, 4.0f, 0.0f, 1, 0, 0, 0);
        func_L18_003FC958(m, 1);
    }
    if (moby_timer(m) < 0xFFFF) {
        *(u16 *)(m + 0x96) = moby_timer(m) + 1;
    }
    
}
