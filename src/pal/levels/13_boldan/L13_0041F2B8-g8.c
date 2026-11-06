/*
 * func_PAL_L13_0041F2B8, the PAL copy of func_L13_0041A550: the same C, with the 50 Hz scale
 * on the duration bounds and the spark counts, 0.02f for 1.0f/60.0f, and the position w store
 * ahead of the bounds. As a struct member it cannot alias those fixed globals, so the
 * bounds load after the first division trap.
 * RAC1 counterpart: plasmabot.c start_vendor_beam_pulse.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vq_02C80;
typedef struct { int idx; char pad4[14]; short s12; char pad14[4]; unsigned char cnt[8]; Vq_02C80 pts[32],off[32],a[4][4],b[4][4]; int r620; char pad624[0x650-0x624]; float rotation[3]; } D_02C80;
extern int func_002A7820(int,int),func_002A77E0(int),func_00283CF0(float);
extern float func_002A7878(float,float),func_002A78D8(float,float),func_002A7940(void),func_00283CE0(int),func_00282E80(void *,void *);
extern void func_00282C88(void *),func_002A7A00(void *,float,float),func_00282CC0(void *,void *,void *),func_00282D30(void *,void *,float),func_00283410(void *,void *),func_002830C0(void *,void *,void *);
extern char *func_002BAA28(void *,void *,void *,int,int,int,int,int,int);
extern int D_L13_001B161C __attribute__((sda)),D_L13_001B1620 __attribute__((sda));
extern float D_L13_001B16A0 __attribute__((sda)),D_L13_001B16A4 __attribute__((sda)),D_L13_001B16B8 __attribute__((sda));
extern int D_L13_001B16C0 __attribute__((sda)),D_L13_001B16C4 __attribute__((sda)),D_L13_001B16AC __attribute__((sda)),D_L13_001B16B0 __attribute__((sda));
extern char *D_L13_001B2A0C __attribute__((sda));
extern char D_L13_001B98C0[];
/* The two spark colours as read by the second loop's unused pick. */
extern const int D_L13_001B16C0_1[], D_L13_001B16C4_1[];
typedef struct { char pad0[0x10]; float position[4]; } MobyHead;
void func_PAL_L13_0041F2B8(char *moby) {
    D_02C80 *beam = (*(D_02C80 **)(moby+0x68));
    Vq_02C80 path[32];
    Vq_02C80 path_steps[32];
    Vq_02C80 work, delta;
    Vq_02C80 matrix[4];

    float length;
    int duration;
    int i = 0, j = 0, k = 0, branch = 0;

    ((MobyHead *)moby)->position[3] = 1.0f;
    duration = func_002A7820((D_L13_001B161C * 5 + 2) / 6, (D_L13_001B1620 * 5 + 2) / 6);
    beam->s12=(short)duration;
    beam->r620=(short)duration;
    length=func_002A7878(4.0f,8.0f);

    for (i = 0; i < 32; i++) {
        float y_offset = func_00283CE0(i);
        float last = func_00283CE0(0x1F);
        float y;
        y_offset = y_offset / last;
        y_offset = (0.5f - y_offset) * length;
        if (i < 3 || i > 28) {
            func_00282C88(&path[i]);
            func_00282C88(&path_steps[i]);
        } else {
            {
                float radius = D_L13_001B16A0;
                func_002A7A00(&path[i], 0.0f, radius);
            }
            func_002A7A00(&path_steps[i], 0.0f, D_L13_001B16A4 * (0.020000001f));
        }
        y = path[i].f[1];
        path[i].f[3] = 1.0f;
        path[i].f[1] = y + y_offset;
    }

    for (j = 0; j < 32; j++) {
        if (j == 0 || j == 31) {
            qcopy(&beam->pts[j], &path[j]);
            qcopy(&beam->off[j], &path_steps[j]);
        } else {
            func_00282CC0(&work, &path[j - 1], &path[j]);
            func_00282CC0(&work, &work, &path[j + 1]);
            func_00282D30(&beam->pts[j], &work, 0.333f);
            func_00282CC0(&work, &path_steps[j - 1], &path_steps[j]);
            func_00282CC0(&work, &work, &path_steps[j + 1]);
            func_00282D30(&beam->off[j], &work, 0.333f);
        }
    }

    for (branch = 0; branch < 4; branch++) {
        int start;
        float spread = (D_L13_001B16A0);
        func_002A7A00(&work, spread, spread);
        start = func_00283CF0(func_002A7878((float)branch * 6.0f, (float)(branch + 1) * 6.0f)) + 4;
        beam->cnt[branch] = (unsigned char)start;
        qcopy(&beam->a[0][branch], &beam->pts[start]);
        qcopy(&beam->b[0][branch], &beam->off[start]);
        {
            char *b_col, *prev_col, *cur_col;
            prev_col = (char *)(branch * 16);
            prev_col = prev_col + (int)beam;
            prev_col = prev_col + 0x420;
            cur_col = (char *)(branch * 16);
            cur_col = cur_col + (int)beam;
            cur_col = cur_col + 0x420;
            b_col = (char *)(branch * 16);
            b_col = b_col + (int)beam;
            b_col = b_col + 0x520;
            for (k = 1; k < 4; k++) {
                func_002A7A00(&delta, 0.1f, 0.1f);
                func_002A7A00(b_col + k * 64, 0.0f, (D_L13_001B16A4) * (0.020000001f));
                func_00282CC0(cur_col + k * 64, prev_col + (k - 1) * 64, &work);
                func_00282CC0(cur_col + k * 64, cur_col + k * 64, &delta);
            }
        }
    }

    if (func_00282E80(moby+0x10, D_L13_001B98C0) >= 4.0f) {
        int color;
        int l;
        char *frame=(char *)((beam->idx<<7)+(int)D_L13_001B2A0C);
        beam->rotation[2]=*(float *)(frame+0x78);
        beam->rotation[1]=*(float *)(frame+0x74);
        beam->rotation[1]+=func_002A78D8(0.0f,30.0f)*0.0174532942f;
        beam->rotation[0]=func_002A7940();
        func_00283410(matrix,beam->rotation);
        qcopy(&matrix[3], moby+0x10);
        for (l = 0; l < 32; l += 8) {
            func_002830C0(&work, &beam->pts[l], matrix);
            qcopy(&delta, &beam->off[l]);
            delta.f[3] = (D_L13_001B16B8);
            {
                int heads = func_002A77E0(2) != 0;
                color = heads ? (D_L13_001B16C0) : (D_L13_001B16C4);
            }
            {
                int n = ((func_002A77E0(10) + 20) * 5 + 2) / 6;
                int start = D_L13_001B16AC;
                int end = D_L13_001B16B0;
                func_002BAA28(&work, &delta, &delta, start, end, l >> 1, 15, n, color);
            }
        }
        for (k = 0; k < 2; k++) {
            int n;
            func_002830C0(&work, &beam->a[3][k], matrix);
            qcopy(&delta, &beam->b[3][k]);
            delta.f[3] = (D_L13_001B16B8);
            {
                /* Result unused, as in RAC1's second loop. */
                int heads = func_002A77E0(2) != 0;
                color = heads ? D_L13_001B16C0_1[0] : D_L13_001B16C4_1[0];
            }
            n = ((func_002A77E0(10) + 20) * 5 + 2) / 6;
            {
                {
                int tip = D_L13_001B16C4;
                int start = D_L13_001B16AC;
                int end = D_L13_001B16B0;
                func_002BAA28(&work, &delta, &delta, start, end, beam->cnt[k] >> 1, 15, n, tip);
            }
            }
        }
    }
}
