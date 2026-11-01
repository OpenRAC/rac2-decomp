#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s8 c[0x2600]; s16 h[0x1300]; u16 uh[0x1300]; s32 i[0x980]; u32 u[0x980]; f32 f[0x980]; void *ptr[0x980]; s64 d[0x4C0]; TI128 q[0x260]; } Hero;
typedef struct {
    u8 pad0[0x70];
    f32 f70;
    f32 f74;
    u8 pad78[0x68];
} LevelClass;
typedef struct {
    s32 i0;
    s32 i4;
    u8 pad8[0x14];
    s32 i1C;
    s32 i20;
    u8 pad24[8];
} CamMode;
typedef struct {
    u8 pad0[0x18];
    char *moby;
    s32 count;
    f32 pos[4];
} CollResult;
typedef struct {
    f32 v[4];
    char *moby;
    s32 mask;
    s8 b18;
    s8 b19;
    u16 h1A;
    f32 f1C;
    s32 i20;
} CollQuery;
extern char D_00189E20[];
extern u8 D_00139568[];
extern u8 D_00188660[];
extern LevelClass D_L00_00262570[];
extern CamMode D_L00_0025D990[];
extern CollResult D_L00_001BF200 __attribute__((aligned(16)));
extern char *D_L00_001C3280 __attribute__((nosda));
extern int D_001A72C0;
extern void func_00273318(void *, int, int, int, int, int, float, float, float);
extern void ref_L00_0038BF18_00(void *, void *);
extern void func_L00_0038B208(void *);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0038B6F8(char *);
extern void func_0029FCC0(void *, int, void *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282F70(void *, void *, float);
extern float func_00282DF0(void *);
extern void func_L00_0038BE70(char *);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern int func_L00_0031F220(char *);
extern int func_002E5CF8(int, int, void *);
extern void func_L00_0038BA80(char *);
extern void func_002A8F70(void *, void *, int, void *, void *, float);
extern int func_L00_002B3998(float);
extern void func_L00_002D3778(void *, void *, float);
extern void func_002A8C00(void *, void *, int, void *, float);
extern void func_002AFD88(void *, void *, float, float, float);
extern int func_L00_0031C3D0(char *, char *, char *, char *, void *, void *, int);
extern int func_L00_0038B848(void);
extern int func_L00_0038B7F8(void);
extern int func_00277F48(float, void *, int, void *, void *);
extern void func_L00_00322BE0(void *, int);
extern void func_L00_00322A18(void *, float, float, float);
extern int func_00282948(void *);
extern float func_002A89A8(void *, int, float);
extern float func_002AA2E8(float *, float, float);
extern void func_US2_L00_0038D100(char *);
extern void func_L00_002D24D0(int);
extern void func_002E59F8(int);
extern int func_L00_002B9B88(int, int);
extern void func_L00_00322EC8(void *);
extern int func_002ABB78(char *);
extern float *func_002AB1F0(char *);
extern void func_L00_0031D670(void *, void *, void *, float);
extern void func_L00_0038B888(void *, int);

void func_US2_L00_0038D318(char *m)
{
    f32 vec[8][4] __attribute__((aligned(16)));
    char *pv;
    float ang;
    char *t;
    char *t2;
    char *t3;
    char *mode;
    char *pos;
    char *snd;
    float *r;
    float yaw;
    float diff;
    float lim;
    float range;
    float k;
    float sc;
    float d;
    float zf;
    float g;
    float top;
    LevelClass *cls;
    CamMode *cm;
    int ok;
    int found;
    int hit;
    int done;
    int far;

    pv = *(char **)(m + 0x68);
    ((Hero *)D_00189E20)->b[0x123C] = 0;
    if (((Hero *)D_00189E20)->i[0x1244 / 4] == 3) {
        return;
    }
    switch (*(u8 *)(m + 0x20)) {
    case 0:
        *(void **)(m + 0xB8) = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
        if ((((Hero *)D_00189E20)->i[0x2294 / 4] == 1 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x1D)
            && (*(u16 *)((char *)((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x34) & 1)) {
            func_00273318(m, 0xFF917267, 0, 0x25, -1, 4, 1.0f, 0.0f, 90.0f);
        }
        if (pv != 0 && *(f32 *)(pv + 0x70) != 0.0f) {
            ref_L00_0038BF18_00(func_L00_0038B208, m);
        }
        if (D_001A72C0 == 0) {
            *(u16 *)(m + 0x34) &= ~0x10;
        } else {
            *(u32 *)(m + 0x78) = 0x80909090;
            *(u16 *)(m + 0x34) |= 0x10;
        }
        if (*(u8 *)(m + 0x43) != 0) {
            if (*(u8 *)(m + 0x43) == 0xE) {
                if (*(u8 *)(m + 0x60) & 2) {
                    func_002A7470(m, 1, 0, 5);
                }
                return;
            }
            if (((Hero *)D_00189E20)->b[0x22BE] != 0) {
                if ((u8)(*(u8 *)(m + 0x43) - 0xF) >= 2) {
                    func_002A7470(m, 0xF, 0, 4);
                } else if ((*(u8 *)(m + 0x60) & 2) && *(u8 *)(m + 0x43) == 0xF) {
                    func_002A7470(m, 0x10, 0, 5);
                }
                return;
            }
            if ((u8)(*(u8 *)(m + 0x43) - 0xF) < 2) {
                func_002A7470(m, 0xE, 0, 2);
                return;
            }
        }
        if ((*(u8 *)(m + 0x60) & 2) && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x37 && ((Hero *)D_00189E20)->i[0x229C / 4] != 0x22
            && *(u8 *)(m + 0x43) != 1) {
            func_002A7470(m, 1, 0, 5);
        }
        func_L00_0038B6F8(m);
        if (((Hero *)D_00189E20)->i[0x2294 / 4] != 0x13 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x20 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x2A
            && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6D && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x14
            && *(u8 *)(m + 0x43) >= 3 && *(u8 *)(m + 0x43) < 6) {
            func_002A7470(m, 1, 0, 4);
        }
        t = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
        if (*(u8 *)(t + 0x43) != *(u8 *)(t + 0x42) || *(u8 *)(t + 0x41) - *(u8 *)(t + 0x40) >= 3) {
            *(u16 *)(pv + 0x74) += 1;
        }
        *(f32 *)(m + 0x48) = ((Hero *)D_00189E20)->f[0xC20 / 4];
        cm = &D_L00_0025D990[((Hero *)D_00189E20)->h[0xBFC / 2]];
        if (((Hero *)D_00189E20)->i[0x229C / 4] != 6 && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x2A) {
            return;
        }
        ok = 1;
        if (((Hero *)D_00189E20)->i[0xC2C / 4] != 0 || ((Hero *)D_00189E20)->f[0xC38 / 4] < (f32)cm->i1C || (f32)cm->i20 < ((Hero *)D_00189E20)->f[0xC38 / 4]) {
            ok = 0;
        }
        found = 0;
        if (*(s16 *)(pv + 0x7C) != *(s16 *)(pv + 0x74)) {
            t2 = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
            if (*(u8 *)(t2 + 0x42) == *(u8 *)(t2 + 0x43)) {
                if (*(u8 *)(t2 + 0x42) == 0x17) {
                    found = 1;
                    if (!(0.0f <= ((Hero *)D_00189E20)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x18) {
                    found = 1;
                    if (!(0.0f <= ((Hero *)D_00189E20)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x19) {
                    found = 1;
                    if (!(12.0f <= ((Hero *)D_00189E20)->f[0xC38 / 4])) {
                        found = 0;
                    }
                } else if (*(u8 *)(t2 + 0x42) == 0x2B) {
                    found = 1;
                    if (!(23.0f <= ((Hero *)D_00189E20)->f[0xC38 / 4])) {
                        found = 0;
                    }
                }
            }
        }
        if (found != 0) {
            *(f32 *)(pv + 0x70) = 1.0f;
            *(s16 *)(pv + 0x7C) = *(s16 *)(pv + 0x74);
        }
        diff = 0.0f;
        yaw = ((Hero *)D_00189E20)->f[0x98 / 4];
        qcopy(&((Hero *)D_00189E20)->b[0xB90], &((Hero *)D_00189E20)->b[0xB70]);
        qcopy(&((Hero *)D_00189E20)->b[0xB80], &((Hero *)D_00189E20)->b[0xB60]);
        func_0029FCC0(m, 1, &((Hero *)D_00189E20)->b[0xB70]);
        func_0029FCC0(((Hero *)D_00189E20)->ptr[0x2290 / 4], 0, &((Hero *)D_00189E20)->b[0xB60]);
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x13 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x6D || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x2A) {
            yaw = func_00283248(((Hero *)D_00189E20)->f[0xB70 / 4] - ((Hero *)D_00189E20)->f[0x80 / 4], ((Hero *)D_00189E20)->f[0xB74 / 4] - ((Hero *)D_00189E20)->f[0x84 / 4]);
            if (D_L00_0025D990[((Hero *)D_00189E20)->h[0xBFC / 2]].i4 == 1) {
                yaw = func_00283B98(yaw, -1.57079649f);
            } else {
                yaw = func_00283B98(yaw, 1.57079649f);
            }
        }
        {
            func_00282CF0(vec[0], &((Hero *)D_00189E20)->b[0xB70], &((Hero *)D_00189E20)->b[0xB60]);
            func_00282F20(vec[0], vec[0], func_00282DF0(vec[0]) + 0.17f);
            if (((Hero *)D_00189E20)->i[0x229C / 4] != 0xF && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6D && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x14) {
                diff = func_00283C80(((Hero *)D_00189E20)->f[0x98 / 4],
                                     func_00283248(((Hero *)D_00189E20)->f[0xB70 / 4] - ((Hero *)D_00189E20)->f[0x80 / 4],
                                                   ((Hero *)D_00189E20)->f[0xB74 / 4] - ((Hero *)D_00189E20)->f[0x84 / 4]));
                if (diff > 1.57079649f) {
                    ok = 0;
                }
                func_L00_0038BE70((char *)vec[0]);
            }
            func_00282CC0(&((Hero *)D_00189E20)->b[0xB70], &((Hero *)D_00189E20)->b[0xB60], vec[0]);
            if (((Hero *)D_00189E20)->i[0x2294 / 4] != 0x2A && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x6D && diff < 1.22173059f
                && ((Hero *)D_00189E20)->i[0x1B8 / 4] >= 11) {
                qcopy(vec[0], &((Hero *)D_00189E20)->b[0x80]);
                vec[0][2] = vec[0][2] + 0.5f;
                ang = func_00283248(((Hero *)D_00189E20)->f[0xB70 / 4] - ((Hero *)D_00189E20)->f[0x80 / 4], ((Hero *)D_00189E20)->f[0xB74 / 4] - ((Hero *)D_00189E20)->f[0x84 / 4]);
                qcopy(vec[1], &((Hero *)D_00189E20)->b[0x80]);
                vec[1][2] = vec[1][2] + 0.5f;
                vec[2][0] = func_00283180(ang) * 1.4f;
                vec[2][1] = func_00283198(ang) * 1.4f;
                vec[2][2] = 0.0f;
                func_L00_0038BE70((char *)vec[2]);
                func_00282CC0(vec[1], vec[1], vec[2]);
                if (((Hero *)D_00189E20)->h[0xBFE / 2] == 0 && func_002761F8(vec[0], vec[1], 2, 0, 0) != 0 && func_00278E78() != 0
                    && (D_L00_001BF200.moby == 0 || func_L00_0031F220(D_L00_001BF200.moby) != 0)) {
                    ((Hero *)D_00189E20)->h[0xBFE / 2] = 1;
                    func_002E5CF8(2, 0, m);
                    func_L00_0038BA80(m);
                    if (D_L00_001BF200.moby != 0) {
                        if (((Hero *)D_00189E20)->b[0x22C3] == 0) {
                            vec[3][0] = func_00283180(yaw);
                            vec[3][1] = func_00283198(yaw);
                            vec[3][2] = 0.0f;
                        } else {
                            qcopy(vec[3], &((Hero *)D_00189E20)->b[0]);
                        }
                        func_002A8F70(D_L00_001BF200.moby, m, 0x10000, D_L00_001BF200.pos, vec[3], 1.0f);
                    }
                }
            }
            if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x14 && func_L00_002B3998(27.0f) != 0) {
                func_002E5CF8(2, 0, m);
                qcopy(vec[0], &((Hero *)D_00189E20)->b[0xB70]);
                qcopy(vec[1], vec[0]);
                func_L00_002D3778(vec[0], vec[0], 0.7f);
                func_L00_002D3778(vec[1], vec[1], -0.9f);
                if (func_002761F8(vec[0], vec[1], 2, 0, 0) != 0) {
                    func_L00_0038BA80(m);
                }
            }
        }
        if (ok != 0) {
            cls = &D_L00_00262570[D_00139568[0xA]];
            sc = 1.0f;
            range = cls->f70;
            if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x14) {
                range = cls->f74;
                sc = 1.55f;
            }
            vec[3][0] = func_00283180(yaw);
            vec[3][1] = func_00283198(yaw);
            vec[3][2] = 0.0f;
            func_002A8C00(vec[0], m, 0x10000, vec[3], range);
            func_00282F70(vec[0], vec[0], sc);
            vec[0][2] = 1.0f;
            vec[0][3] = 5627.9248f;
            ((CollQuery *)vec[0])->b19 = 1;
            ((CollQuery *)vec[0])->h1A = *(u16 *)(m + 0xAA);
            ((CollQuery *)vec[0])->b18 = 0;
            if (((Hero *)D_00189E20)->b[0x22C3] != 0) {
                qzero_nc(vec[3]);
                func_002AFD88(((Hero *)D_00189E20)->ptr[0x2290 / 4], vec[3], 1.0f, 0.0f, 1.0f);
            }
            if (func_L00_0031C3D0(&((Hero *)D_00189E20)->b[0xB60], &((Hero *)D_00189E20)->b[0xB70], &((Hero *)D_00189E20)->b[0xB80], &((Hero *)D_00189E20)->b[0xB90],
                                  ((Hero *)D_00189E20)->ptr[0x2290 / 4], (CollQuery *)vec[0], 5) != 0
                && D_L00_001BF200.moby != 0 && func_L00_0038B848() == 0 && ((Hero *)D_00189E20)->h[0xBFE / 2] == 0
                && (D_L00_001BF200.moby == 0 || *(char **)(D_L00_001BF200.moby + 0x24) == 0
                    || *(s16 *)(*(char **)(D_L00_001BF200.moby + 0x24) + 0x46) != 0x14)) {
                ((Hero *)D_00189E20)->h[0xBFE / 2] = 1;
                func_002E5CF8(func_L00_0038B7F8(), 0, m);
                func_L00_0038BA80(m);
            }
            func_00282CF0(vec[5], &((Hero *)D_00189E20)->b[0xB70], &((Hero *)D_00189E20)->b[0xB60]);
            func_00282F20(vec[5], vec[5], func_00282DF0(vec[5]) - 0.085f);
            func_00282CC0(vec[4], vec[5], &((Hero *)D_00189E20)->b[0xB60]);
            g = 0.35f;
            if (((Hero *)D_00189E20)->i[0x229C / 4] == 0xF) {
                g = 0.7f;
            }
            if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x14) {
                g = 0.47f;
            }
            if (func_00277F48(g, vec[4], 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], (CollQuery *)vec[0]) == 0) {
                return;
            }
            if (D_L00_001C3280 != 0 && *(char **)(D_L00_001C3280 + 0x24) != 0
                && *(s16 *)(*(char **)(D_L00_001C3280 + 0x24) + 0x46) == 0x12) {
                return;
            }
            if (func_L00_0038B848() != 0) {
                return;
            }
            if (((Hero *)D_00189E20)->h[0xBFE / 2] != 0) {
                return;
            }
            ((Hero *)D_00189E20)->h[0xBFE / 2] = 1;
            func_002E5CF8(func_L00_0038B7F8(), 0, m);
            func_L00_0038BA80(m);
        }
        break;
    case 10:
    case 11: {
        func_L00_00322BE0(&((Hero *)D_00189E20)->b[0x1A30], 0);
        *(void **)(m + 0xB8) = ((Hero *)D_00189E20)->ptr[0x2290 / 4];
        ((Hero *)D_00189E20)->b[0x123C] = 2;
        if (*(u8 *)(m + 0x20) == 10) {
            snd = (char *)D_00188660 + ((Hero *)D_00189E20)->i[0x2430 / 4] * 0x70;
            if (*(void **)(snd + 0x88) != ((Hero *)D_00189E20)->ptr[0x2290 / 4] || *(u8 *)(snd + 0x74) == 0) {
                ((Hero *)D_00189E20)->i[0x2430 / 4] = func_002E5CF8(0xB, 4, ((Hero *)D_00189E20)->ptr[0x2290 / 4]);
            }
        }
        func_L00_00322A18(m, 0.0f, 0.0f, 0.40724355f);
        if (((Hero *)D_00189E20)->h[0xBFE / 2] != 0 && func_00282948(pv + 0x6C) != 0) {
            ((Hero *)D_00189E20)->h[0xBFE / 2] = 0;
        }
        pos = m + 0x10;
        if (((Hero *)D_00189E20)->b[0x22C3] == 0) {
            top = func_002A89A8(pos, 0, 0.5f);
            zf = *(f32 *)(m + 0x18);
            if (zf - top < 0.8f) {
                top = top + 0.55f;
                if (zf < top) {
                    func_002AA2E8((f32 *)(m + 0x18), top, 0.06666667f);
                } else {
                    func_002AA2E8((f32 *)(m + 0x18), top, 0.016666668f);
                }
            }
        }
        qcopy(vec[0], pos);
        if (*(u8 *)(m + 0x20) == 10) {
            qcopy(vec[1], &((Hero *)D_00189E20)->b[0x150]);
            func_00282D30(vec[1], vec[1], 0.98f);
            func_00282CC0(pos, pos, vec[1]);
            func_00282F20(vec[1], pv + 0x40, *(f32 *)(pv + 0x60));
            func_00282CC0(pos, pos, vec[1]);
            *(f32 *)(pv + 0x64) = *(f32 *)(pv + 0x64) + 0.000787037017f;
            func_002AA2E8((f32 *)(pv + 0x60), 0.0f, *(f32 *)(pv + 0x64));
            if (*(f32 *)(pv + 0x60) == 0.0f) {
                *(u8 *)(m + 0x20) = 11;
            }
        } else {
            qcopy(vec[1], &((Hero *)D_00189E20)->b[0x150]);
            func_00282D30(vec[1], vec[1], 0.98f);
            done = 0;
            func_00282CC0(pos, pos, vec[1]);
            func_US2_L00_0038D100(m);
            func_00282CF0(vec[1], &((Hero *)D_00189E20)->b[0x1200], pos);
            *(f32 *)(pv + 0x64) = *(f32 *)(pv + 0x64) + 0.00025f;
            *(f32 *)(pv + 0x60) = *(f32 *)(pv + 0x60) + *(f32 *)(pv + 0x64);
            d = func_00282DF0(vec[1]);
            if (d / *(f32 *)(pv + 0x60) < 5.0f && *(u8 *)(m + 0x43) != 1) {
                func_002A7470(m, 1, 0, 5);
            }
            if (d <= *(f32 *)(pv + 0x60)) {
                *(f32 *)(pv + 0x60) = d;
                done = 1;
            }
            func_00282F20(vec[1], vec[1], *(f32 *)(pv + 0x60));
            func_00282CC0(pos, pos, vec[1]);
            if (d / *(f32 *)(pv + 0x60) < 4.0f && ((Hero *)D_00189E20)->i[0xC40 / 4] != -1) {
                func_L00_002D24D0(2);
                ((Hero *)D_00189E20)->i[0xC44 / 4] = 0x1A;
                if (((Hero *)D_00189E20)->i[0x2430 / 4] != -1) {
                    snd = (char *)D_00188660 + ((Hero *)D_00189E20)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(snd + 0x88) == ((Hero *)D_00189E20)->ptr[0x2290 / 4] && *(u8 *)(snd + 0x74) != 0) {
                        func_002E59F8(((Hero *)D_00189E20)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)D_00189E20)->i[0x2430 / 4] = -1;
            }
            far = 0;
            if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x31 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x61 || d > 32.0f) {
                far = 1;
            }
            if (done != 0 || far != 0) {
                if (far == 0) {
                    func_L00_002B9B88(5, 0);
                }
                if (((Hero *)D_00189E20)->i[0x2430 / 4] != -1) {
                    snd = (char *)D_00188660 + ((Hero *)D_00189E20)->i[0x2430 / 4] * 0x70;
                    if (*(void **)(snd + 0x88) == ((Hero *)D_00189E20)->ptr[0x2290 / 4] && *(u8 *)(snd + 0x74) != 0) {
                        func_002E59F8(((Hero *)D_00189E20)->i[0x2430 / 4]);
                    }
                }
                ((Hero *)D_00189E20)->i[0x2430 / 4] = -1;
                func_L00_00322EC8(&((Hero *)D_00189E20)->b[0x1A30]);
                ((Hero *)D_00189E20)->b[0x123A] = 0;
                *(u8 *)(m + 0x20) = 0;
            }
        }
        hit = 0;
        if (func_002761F8(vec[0], pos, 2, 0, 0) != 0 && func_00278E78() != 0
            && (D_L00_001BF200.moby == 0 || func_002ABB78(D_L00_001BF200.moby) == 0)) {
            hit = D_L00_001BF200.count != 0;
        }
        if (hit != 0 || *(s16 *)(pv + 0x76) != 0) {
            *(s16 *)(pv + 0x76) = 0;
            if (((Hero *)D_00189E20)->h[0xBFE / 2] == 0) {
                *(int *)(pv + 0x6C) = 0x1E;
                ((Hero *)D_00189E20)->h[0xBFE / 2] = 1;
                func_002E5CF8(2, 0, m);
            }
            if (*(u8 *)(m + 0x20) == 10) {
                func_L00_0038BA80(m);
                *(f32 *)(pv + 0x60) = *(f32 *)(pv + 0x60) * 0.5f;
                *(u8 *)(m + 0x20) = 11;
            }
        }
        k = 1.2f;
        if (*(u8 *)(m + 0x20) == 11) {
            k = -0.37f;
        }
        func_00282F20(vec[4], pv + 0x40, k);
        func_002A8C00(vec[1], m, 0x10000, vec[4], (&D_L00_00262570[D_00139568[0xA]])->f70);
        vec[1][2] = 1.0f;
        if (((Hero *)D_00189E20)->b[0x22C3] != 0) {
            qzero_nc(vec[1]);
            func_002AFD88(((Hero *)D_00189E20)->ptr[0x2290 / 4], vec[1], k, 0.0f, 1.0f);
        }
        vec[1][3] = 5627.9248f;
        ((CollQuery *)vec[1])->b19 = 1;
        ((CollQuery *)vec[1])->h1A = ((Hero *)D_00189E20)->uh[0xC0C / 2] + 1;
        ((CollQuery *)vec[1])->b18 = 0;
        func_0029FCC0(m, 1, vec[5]);
        if ((func_00277F48(0.4f, vec[5], 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], (CollQuery *)vec[1]) != 0
             || (func_0029FCC0(m, 0, vec[5]), func_00277F48(0.4f, vec[5], 0, ((Hero *)D_00189E20)->ptr[0x2290 / 4], (CollQuery *)vec[1]) != 0))
            && ((Hero *)D_00189E20)->h[0xBFE / 2] == 0 && D_L00_001BF200.moby != 0) {
            t3 = *(char **)(D_L00_001BF200.moby + 0x24);
            if (t3 == 0 || *(s16 *)(t3 + 0x46) != 0x14) {
                r = func_002AB1F0(D_L00_001BF200.moby);
                if (r == 0 || *(s16 *)((char *)r + 0x1C) == 0 || *(char **)((char *)r + 0x18) != m) {
                    *(TI128 *)vec[7] = *(TI128 *)(D_L00_001BF200.moby + 0x10);
                    func_L00_0031D670(vec[6], vec[5], vec[7], 0.5f);
                    func_L00_0038B888(vec[6], 5);
                    *(int *)(pv + 0x6C) = 0x1E;
                    ((Hero *)D_00189E20)->h[0xBFE / 2] = 1;
                    func_002E5CF8(func_L00_0038B7F8(), 0, m);
                }
            }
        }
        break;
    }
    }
}
