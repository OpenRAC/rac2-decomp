/* func_PAL_00309A30, the PAL copy of func_00308768: the same C. */
#include "common.h"
/* Adapted from RAC1 visibomb_and_pyrocitor.c (OpenRAC, GPL-3.0). */
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) BeamVec;
typedef int Q_2B4918 __attribute__((mode(TI)));
typedef struct { float pos[4][4]; unsigned int col[4]; float uv[4][2]; unsigned long tag[4]; } Quad_2B4918;
typedef struct { int a, b; } Ids_2B4918;
typedef struct { float x, y, z; } P3_2B4918;
typedef struct { float u, v; } UV_2B4918;
typedef struct Child_2B4918 { char pad0[0xAA]; short cls; } Child_2B4918;
typedef struct Data_2B4918 { int f0; int f4; Child_2B4918 *child; char padC[0x14]; float f20; char pad24[8]; float f2C; } Data_2B4918;

extern Child_2B4918 *D_0018B130 NOT_SDA;
extern Ids_2B4918 D_001AED90 NOT_SDA;
extern Ids_2B4918 D_001AED98 NOT_SDA;
extern float D_001AECF0[][4] SDATA(D_001AECF0);
extern UV_2B4918 D_001AED70[] SDATA(D_001AED70);
/* Retail constructs the V-component address absolutely, the U base through GP. */
extern UV_2B4918 beam_uv_absolute[] __asm__("D_001AED70") MACRO_ADDR;
extern float D_001AED30[][4] SDATA(D_001AED30);
extern float D_001B5340[];
extern UV_2B4918 D_00265FA0[];
extern float D_00265360[][4];
extern P3_2B4918 D_00228840[];
extern int D_002665C0[];
extern char D_00189E20[];
extern void func_0029FD48(void *, int, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00283388(void *);
extern void func_00283788(void *, void *, void *);
extern long func_0027C878(int);
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_00280B90(void *, void *, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_002FC560(int, long);
extern void func_00280328(void);
extern void func_00281810(int, void *, void *, void *, int);

/* Draws the moby's beam: orients the moby along its child's two joints, draws three quads and a ribbon of 196 points. */
void func_PAL_00309A30(char *m) {
    Quad_2B4918 pk;
    BeamVec mtx[4];
    BeamVec out[2];
    Ids_2B4918 ids;
    BeamVec up;
    BeamVec res[4];
    BeamVec idm[4];
    BeamVec a;
    BeamVec b;
    BeamVec c;
    BeamVec d;
    BeamVec e;
    Child_2B4918 *child = D_0018B130;
    Data_2B4918 *data = (Data_2B4918 *)*(void **)(m + 0x68);
    int i;
    int j;

    if (child == 0 || (child->cls != 0x260 && child->cls != 0x96C)) {
        return;
    }
    pk.tag[2] = 0xFF9000000260;
    pk.tag[3] = 0x8000000048;
    pk.tag[0] = 0;
    if (data->f4 != 0) {
        ids = D_001AED90;
        func_0029FD48(child, 2, &ids, out);
    } else {
        ids = D_001AED98;
        func_0029FD48(child, 2, &ids, out);
    }
    *(Q_2B4918 *)&up = 0;
    up.y = 1.0f;
    func_00282CF0(&mtx[2], &out[0], &out[1]);
    func_00282F20(&mtx[2], &mtx[2], 1.0f);
    mtx[2].w = 0.0f;
    func_00282DD8(&mtx[0], &up, &mtx[2]);
    func_00282F20(&mtx[0], &mtx[0], 1.0f);
    mtx[0].w = 0.0f;
    func_00282DD8(&mtx[1], &mtx[2], &mtx[0]);
    mtx[1].w = 0.0f;
    qcopy(&mtx[3], &out[1]);
    mtx[3].w = 1.0f;
    qcopy(m + 0xC0, &mtx[0]);
    qcopy(m + 0xD0, &mtx[1]);
    qcopy(m + 0xE0, &mtx[2]);
    qcopy(m + 0x10, &mtx[3]);
    func_00283388(idm);
    idm[3].w = 1.0f;
    idm[3].z = -0.075f;
    idm[3].x = 0.0f;
    idm[3].y = 0.0f;
    func_00283788(res, mtx, idm);
    pk.tag[1] = func_0027C878(0xC);
    for (i = 0; i < 4; i++) {
        pk.col[i] = 0x80808080;
        if (i == 0 || i == 2) {
            func_00282D30(pk.pos[i], D_001AECF0[i], data->f2C);
        } else {
            float *v = pk.pos[i];
            func_00282D30(v, D_001AECF0[i], data->f2C);
            v[2] -= func_002A7878(0.0f, 0.1f);
        }
        pk.uv[i][0] = D_001AED70[i].u;
        pk.uv[i][1] = beam_uv_absolute[i].v;
    }
    func_00280B90(&pk, res, 0);
    for (i = 0; i < 4; i++) {
        if (i == 0 || i == 2) {
            func_00282D30(pk.pos[i], D_001AED30[i], data->f2C);
        } else {
            float *v = pk.pos[i];
            func_00282D30(v, D_001AED30[i], data->f2C);
            v[2] -= func_002A7878(0.0f, 0.1f);
        }
    }
    func_00280B90(&pk, res, 0);
    pk.tag[1] = func_0027C878(0xB);
    func_00282D30(&d, &mtx[2], -0.13f);
    func_00282CC0(&d, &d, &mtx[3]);
    func_00282CF0(&a, D_001B5340, &d);
    func_00282F20(&a, &a, 1.0f);
    func_00282DD8(&b, &a, D_00189E20 + 0x2C0);
    func_00282F20(&b, &b, -1.0f);
    func_00282DD8(&c, &b, &a);
    pk.col[0] = pk.col[1] = pk.col[2] = pk.col[3] = 0x7F2020FF;
    for (j = 0; j < 4; j++) {
        func_00282D30(pk.pos[j], D_001AECF0[j], 0.1f);
        func_002830C0(pk.pos[j], pk.pos[j], &a);
    }
    func_00280B90(&pk, 0, 0);
    func_002FC560(6, func_0027C878(0xA));
    func_002FC560(0x42, pk.tag[3]);
    func_002FC560(8, 0);
    func_002FC560(0x14, 0xFF9000000260);
    func_002FC560(0x4A, 0);
    func_00280328();
    for (i = 0; i < 0xC4; i++) {
        func_00282D30(&e, D_00265360[i], data->f20);
        func_002830C0(&e, &e, mtx);
        D_00228840[i].x = e.x;
        D_00228840[i].y = e.y;
        D_00228840[i].z = e.z;
        D_00265FA0[i].v -= 0.025f;
        if (D_00265FA0[i].v < -7.0f) {
            D_00265FA0[i].v += 7.0f;
        }
    }
    func_00281810(0x94, D_00228840, D_002665C0, D_00265FA0, 1);
    func_00281810(0x32, &D_00228840[0x92], &D_002665C0[0x92], &D_00265FA0[0x92], 1);
}
