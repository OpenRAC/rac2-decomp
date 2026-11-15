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
extern int FloatToInt(float);
void matrix_mul_vec3(void *,void *,void *);
void FastVecAdd(void *,void *,void *);
void FastVecSub(void *,void *,void *);
void FastVecScale(void *,void *,float);
void vec_scale_to_length(void *,void *,float);
void FastVecCross(void *,void *,void *);
float math_fast_sin_or_cos_b(float);
float math_fast_sin_or_cos_a(float);
void UpdateViewContext(void);
void hero_l00_set_action(int,int);
int Spline_AdvanceByDistance(void *,void *,int *,float *,float,int);
int FastDecTimer(void *);
float math_cosine_blend(float,float,float);
float fast_vec_dist(void *,void *);

/* Adapted from RAC1 Camera19_Update, rocket_and_path_camera.c. */
/* Runs a cinematic camera that moves along a path, fades in and out and changes zoom. When the path ends it hands the camera back. */
void cam_path_update_cinematic(char *moby) {
    float va[4];
    float v1[4];
    float v2[4];
    float v3[4];
    int ia;
    float ib;
    char *vars;
    char *f;
    struct CamK_72D8 *k;
    char *desc;
    char *pathData;
    short phase;
    float t;

    vars = *(char **)(moby + 0x70);
    f = vars + 0x40;
    k = (struct CamK_72D8 *)(vars + 0x58);
    desc = *(char **)(D_L00_001B1844 + *(short *)(moby + 0x84) * 0x20 + 0x1C);
    D_L00_001B1BE8 = 1;
    phase = *(short *)(f + 0x14);

    if (phase == 0) {
        char *a;
        char *b;
        char *pm;
        char *gb;
        float *c3;
        D_L00_001B18E0 += 0.05f;
        if (1.0f <= D_L00_001B18E0) {
            a = D_L00_001FDA80[*(int *)(desc + 0x20)];
            b = D_L00_001FDA80[*(int *)(desc + 0x24)];
            pm = moby + 0x30;
            D_L00_001B18E0 = 1.0f;
            a = a + 0x10;
            D_L00_001B18E8 = 1;
            *(short *)(f + 0x14) = 1;
            qcopy(pm, a);
            if (*(int *)(desc + 0x28) >= 0) {
                gb = D_L00_001B1E9C + (*(int *)(desc + 0x28) << 8);
                c3 = (float *)(desc + 0x2C);
                v1[0] = c3[0];
                v1[1] = c3[1];
                v1[2] = c3[2];
                v1[3] = 0.0f;
                matrix_mul_vec3(v1, v1, D_L00_001B8FF0);
                FastVecAdd(v2, gb + 0x10, v1);
                FastVecSub(va, v2, pm);
            } else {
                FastVecSub(va, b + 0x10, pm);
            }
            FastVecScale(v1, D_0018A0E0, -1.0f);
            vec_scale_to_length(moby, va, 1.0f);
            FastVecCross(moby + 0x10, moby, v1);
            vec_scale_to_length(moby + 0x10, moby + 0x10, 1.0f);
            FastVecCross(moby + 0x20, moby + 0x10, moby);
        }
        return;
    }
    if (phase == 2) {
        float x;
        float aa;
        float bb;
        D_L00_001B18E0 += 0.05f;
        if (1.0f <= D_L00_001B18E0) {
            *(short *)(f + 0x14) = 3;
            D_L00_001B18E0 = 1.0f;
            x = k->vals[8] * 0.5f;
            aa = math_fast_sin_or_cos_b(x);
            bb = math_fast_sin_or_cos_a(x); D_L00_001BD370 = aa / bb;
            UpdateViewContext();
            *(unsigned char *)(desc + 0x39) = 1;
            func_L00_002D99A0(15.0f);
            *(short *)(moby + 0x7E) = 4;
            D_L00_001B18E8 = 0;
            if (*(int *)(desc + 0x4C) == 0) {
                hero_l00_set_action(0, 1);
            }
        }
        if (*(int *)(desc + 0x40) == 0) {
            return;
        }
    } else if (phase == 3) {
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
        int pathDone;
        int i;
        struct CamKeys *keys;

        pathData = D_L00_001FDA80[*(int *)(desc + 0x20)];
        qcopy(va, (moby + 0x30));
        pathDone = Spline_AdvanceByDistance(pathData, (moby + 0x30), (int *)f, (float *)(f + 4), *(float *)(desc + 0x3C) * 0.01666666753590107f, 0);
        if (*(short *)(f + 0x16) != 0) {
            if (FastDecTimer(f + 0x16) != 0) {
                pathDone = 1;
            } else if (*(int *)(desc + 0x40) != 0) {
                short s16 = *(short *)(f + 0x16);
                if (s16 < FloatToInt(20.0f)) {
                    pathDone = 1;
                }
            }
        }
        if (*(unsigned char *)(desc + 0x39) != 0) {
            pathDone = 1;
        }
        if (pathDone != 0) {
            *(short *)(f + 0x14) = 2;
            if (*(int *)(desc + 0x40) == 0) {
                return;
            }
        }
        keys = (struct CamKeys *)desc;
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
                    sum = sum + *(float *)(pathData + j * 16 + 0x1C);
                }
                total = sum;
                sum = sum + fv;
                for (j2 = *(int *)f; j2 < keys->ids[i + 1]; j2++) {
                    total = total + *(float *)(pathData + j2 * 16 + 0x1C);
                }
                r = math_cosine_blend(keys->vals[i], keys->vals[i + 1], sum / total);
                m = r * 0.00872664712369442f;
                aa = math_fast_sin_or_cos_b(m);
                bb = math_fast_sin_or_cos_a(m); cam = D_L00_001BD2C0; *(float *)(cam + 0xB0) = aa / bb;
                UpdateViewContext();
            }
            i++;
        }
        d = fast_vec_dist(va, (moby + 0x30));
        nv = *(float *)(f + 0x10) + d;
        *(float *)(f + 0x10) = nv;
        if (*(int *)(desc + 0x28) >= 0) {
            char *b17 = D_L00_001B1E9C + (*(int *)(desc + 0x28) << 8);
            float *c3 = (float *)(desc + 0x2C);
            v2[0] = c3[0];
            v2[1] = c3[1];
            v2[2] = c3[2];
            v2[3] = 0.0f;
            matrix_mul_vec3(v2, v2, D_L00_001B8FF0);
            FastVecAdd(v3, b17 + 0x10, v2);
            FastVecSub(v1, v3, (moby + 0x30));
        } else {
            char *h;
            d = (nv / *(float *)(f + 8)) * *(float *)(f + 0xC);
            h = D_L00_001FDA80[*(int *)(desc + 0x24)];
            ia = 0;
            ib = 0.0f;
            Spline_AdvanceByDistance(h, v2, &ia, &ib, d, 0);
            FastVecSub(v1, v2, (moby + 0x30));
        }
        FastVecScale(v2, D_0018A0E0, -1.0f);
        vec_scale_to_length(moby, v1, 1.0f);
        FastVecCross(moby + 0x10, moby, v2);
        vec_scale_to_length(moby + 0x10, moby + 0x10, 1.0f);
        FastVecCross(moby + 0x20, moby + 0x10, moby);
    }
}
