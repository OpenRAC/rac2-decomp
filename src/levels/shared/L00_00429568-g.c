#include "common.h"

struct CamK_72D8 { int unused[4]; float vals[9]; };
struct CamKeys { char pad[0x60]; float vals[8]; int ids[8]; };
extern char *D_L00_001B1844 MACRO_ADDR;
extern float D_L00_001B18E0 MACRO_ADDR;
extern char *D_L00_001B1E9C MACRO_ADDR;
extern char *D_L00_001FDA80[];
extern int D_L00_001B18E8 MACRO_ADDR;
extern int D_L00_001B1BE8 MACRO_ADDR;
extern float D_L00_001BD370;
extern char D_L00_001BD2C0[];
extern char D_L00_001B8FF0[];
extern char D_0018A0E0[];
extern void func_L00_002D99A0(float);
extern int func_00283CF0(float);
void func_00283098(void *,void *,void *);
void func_00282CC0(void *,void *,void *);
void func_00282CF0(void *,void *,void *);
void func_00282D30(void *,void *,float);
void func_00282F20(void *,void *,float);
void func_00282DD8(void *,void *,void *);
float func_00283198(float);
float func_00283180(float);
void func_0027AB40(void);
void func_L00_002C42E0(int,int);
int func_L00_00341820(void *,void *,int *,float *,float,int);
int func_00282978(void *);
float func_002A7C00(float,float,float);
float func_00282E48(void *,void *);

/* Adapted from RAC1 Camera19_Update, rocket_and_path_camera.c. */
void func_L00_00429568(char *moby) {
    float va[4];
    float v1[4];
    float v2[4];
    float v3[4];
    int ia;
    float ib;
    char *dat;
    char *f;
    struct CamK_72D8 *k;
    char *e;
    char *g;
    short st;
    float t;

    dat = *(char **)(moby + 0x70);
    f = dat + 0x40;
    k = (struct CamK_72D8 *)(dat + 0x58);
    e = *(char **)(D_L00_001B1844 + *(short *)(moby + 0x84) * 0x20 + 0x1C);
    D_L00_001B1BE8 = 1;
    st = *(short *)(f + 0x14);

    if (st == 0) {
        char *a;
        char *b;
        char *pm;
        char *gb;
        float *c3;
        D_L00_001B18E0 += 0.05f;
        if (1.0f <= D_L00_001B18E0) {
            a = D_L00_001FDA80[*(int *)(e + 0x20)];
            b = D_L00_001FDA80[*(int *)(e + 0x24)];
            pm = moby + 0x30;
            D_L00_001B18E0 = 1.0f;
            a = a + 0x10;
            D_L00_001B18E8 = 1;
            *(short *)(f + 0x14) = 1;
            qcopy(pm, a);
            if (*(int *)(e + 0x28) >= 0) {
                gb = D_L00_001B1E9C + (*(int *)(e + 0x28) << 8);
                c3 = (float *)(e + 0x2C);
                v1[0] = c3[0];
                v1[1] = c3[1];
                v1[2] = c3[2];
                v1[3] = 0.0f;
                func_00283098(v1, v1, D_L00_001B8FF0);
                func_00282CC0(v2, gb + 0x10, v1);
                func_00282CF0(va, v2, pm);
            } else {
                func_00282CF0(va, b + 0x10, pm);
            }
            func_00282D30(v1, D_0018A0E0, -1.0f);
            func_00282F20(moby, va, 1.0f);
            func_00282DD8(moby + 0x10, moby, v1);
            func_00282F20(moby + 0x10, moby + 0x10, 1.0f);
            func_00282DD8(moby + 0x20, moby + 0x10, moby);
        }
        return;
    }
    if (st == 2) {
        float x;
        float aa;
        float bb;
        D_L00_001B18E0 += 0.05f;
        if (1.0f <= D_L00_001B18E0) {
            *(short *)(f + 0x14) = 3;
            D_L00_001B18E0 = 1.0f;
            x = k->vals[8] * 0.5f;
            aa = func_00283198(x);
            bb = func_00283180(x); D_L00_001BD370 = aa / bb;
            func_0027AB40();
            *(unsigned char *)(e + 0x39) = 1;
            func_L00_002D99A0(15.0f);
            *(short *)(moby + 0x7E) = 4;
            D_L00_001B18E8 = 0;
            if (*(int *)(e + 0x4C) == 0) {
                func_L00_002C42E0(0, 1);
            }
        }
        if (*(int *)(e + 0x40) == 0) {
            return;
        }
    } else if (st == 3) {
        return;
    } else {
        D_L00_001B18E0 -= 0.05f;
        if (D_L00_001B18E0 < 0.0f) {
            D_L00_001B18E0 = 0.0f;
        }
    }

    {
        float d;
        float nv;
        int rr;
        int i;
        struct CamKeys *keys;

        g = D_L00_001FDA80[*(int *)(e + 0x20)];
        qcopy(va, (moby + 0x30));
        rr = func_L00_00341820(g, (moby + 0x30), (int *)f, (float *)(f + 4), *(float *)(e + 0x3C) * 0.01666666753590107f, 0);
        if (*(short *)(f + 0x16) != 0) {
            if (func_00282978(f + 0x16) != 0) {
                rr = 1;
            } else if (*(int *)(e + 0x40) != 0) {
                short s16 = *(short *)(f + 0x16);
                if (s16 < func_00283CF0(20.0f)) {
                    rr = 1;
                }
            }
        }
        if (*(unsigned char *)(e + 0x39) != 0) {
            rr = 1;
        }
        if (rr != 0) {
            *(short *)(f + 0x14) = 2;
            if (*(int *)(e + 0x40) == 0) {
                return;
            }
        }
        keys = (struct CamKeys *)e;
        i = 0;
        while (i < 7 && keys->ids[i] >= 0 && keys->ids[i + 1] >= 0) {
            if (*(int *)f >= keys->ids[i] && *(int *)f < keys->ids[i + 1]) {
                char *cam;
                float sum = 0.0f;
                float fv = *(float *)(f + 4);
                float total;
                float r;
                float m;
                float aa;
                float bb;
                int j;
                int j2;
                for (j = keys->ids[i]; j < *(int *)f; j++) {
                    sum = sum + *(float *)(g + j * 16 + 0x1C);
                }
                total = sum;
                sum = sum + fv;
                for (j2 = *(int *)f; j2 < keys->ids[i + 1]; j2++) {
                    total = total + *(float *)(g + j2 * 16 + 0x1C);
                }
                r = func_002A7C00(keys->vals[i], keys->vals[i + 1], sum / total);
                m = r * 0.00872664712369442f;
                aa = func_00283198(m);
                bb = func_00283180(m); cam = D_L00_001BD2C0; *(float *)(cam + 0xB0) = aa / bb;
                func_0027AB40();
            }
            i++;
        }
        d = func_00282E48(va, (moby + 0x30));
        nv = *(float *)(f + 0x10) + d;
        *(float *)(f + 0x10) = nv;
        if (*(int *)(e + 0x28) >= 0) {
            char *b17 = D_L00_001B1E9C + (*(int *)(e + 0x28) << 8);
            float *c3 = (float *)(e + 0x2C);
            v2[0] = c3[0];
            v2[1] = c3[1];
            v2[2] = c3[2];
            v2[3] = 0.0f;
            func_00283098(v2, v2, D_L00_001B8FF0);
            func_00282CC0(v3, b17 + 0x10, v2);
            func_00282CF0(v1, v3, (moby + 0x30));
        } else {
            char *h;
            d = (nv / *(float *)(f + 8)) * *(float *)(f + 0xC);
            h = D_L00_001FDA80[*(int *)(e + 0x24)];
            ia = 0;
            ib = 0.0f;
            func_L00_00341820(h, v2, &ia, &ib, d, 0);
            func_00282CF0(v1, v2, (moby + 0x30));
        }
        func_00282D30(v2, D_0018A0E0, -1.0f);
        func_00282F20(moby, v1, 1.0f);
        func_00282DD8(moby + 0x10, moby, v2);
        func_00282F20(moby + 0x10, moby + 0x10, 1.0f);
        func_00282DD8(moby + 0x20, moby + 0x10, moby);
    }
}
