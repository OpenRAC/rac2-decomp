#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

/* The level state fields the target picker reads. */
typedef struct {
    char pad0[0x230];
    int group[0x58];
    char pad390[2];
    short dir;
    unsigned short kind;
    short res;
    char pad398[0x3E0 - 0x398];
    float origin[4];
    float target[4];
    float *ref;
    char pad404[0x410 - 0x404];
    char frame[0x40];
} PickState;

typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x68 - 0x20];
    PickState *state;
    char pad6C[0xE0 - 0x6C];
    TI128 up;
} PickMoby;

/* 16-byte rows: the key tested for a hit, then the key tested for a miss. */
typedef struct {
    u64 hit;
    u64 miss;
} PickKeys;

extern PickKeys D_L23_002595C8[];

extern float (*D_L23_001FF300[])[4];

extern char D_00189EA0[];

extern int func_L23_00418F30(PickMoby *, u64, int *, int);

extern int func_L23_00418FD0(PickMoby *, int, short);

extern void func_L23_00419088();

extern int func_L23_00419CE0(u64);

extern int func_002A77E0(int);

extern float func_00282E48(float *, float *);

extern float func_00282DB0(float *, float *);

extern void func_00282DD8(float *, float *, float *);

extern void func_L00_00325600(void *, void *, void *);

extern void func_00282CF0(float *, float *, float *);

extern void func_00282F20(float *, float *, float);

extern float func_00282C48(float);

/* Picks one of the targets whose bits are set in the mask: at random, or the one nearest,
   farthest or best aligned, and latches its side and result in the state. */
void func_L23_004190C8(PickMoby *arg0, u64 mask, int mode, int check) {
    PickState *state = arg0->state;
    int idx[4];
    float *pts[4];
    int res[4];
    u64 *keys[4];
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));
    float n1[4] __attribute__((aligned(16)));
    float n2[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float c1[4] __attribute__((aligned(16)));
    float up1[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c2[4] __attribute__((aligned(16)));
    float up2[4] __attribute__((aligned(16)));
    int n;
    int i;
    int k;
    int best;

    n = func_L23_00418F30(arg0, mask, idx, check);
    if (n == 0) {
        state->dir *= -1;
        return;
    }
    if (mode == 0) {
        int k;
        int v;

        k = idx[func_002A77E0(n)];
        v = func_L23_00418FD0(arg0, k, state->kind);

        state->dir = v == 0 ? 1 : -1;
        state->res = v;
        func_L23_00419088(arg0, k);
        return;
    }
    for (i = 0; i < n; i++) {
        int v;
        float (*e)[4];
        k = idx[i];
        v = func_L23_00418FD0(arg0, k, state->kind);

        res[i] = v;
        e = D_L23_001FF300[state->group[k]];
        if (v == 0) {
            pts[i] = e[*(int *)e];
            keys[i] = &D_L23_002595C8[state->group[k]].miss;
        } else {
            pts[i] = e[1];
            keys[i] = &D_L23_002595C8[state->group[k]].hit;
        }
    }
    best = 0;
    switch (mode) {
    case 1: {
        float f = 30000.0f;
        int j;

        for (j = 0; j < n; j++) {
            int ok = 0;
            float d;

            if (check != 0)
                ok = func_L23_00419CE0(*keys[j]);
            d = fast_vec_dist(pts[j], state->ref);
            if ((d < f && ok == 0) || n == 1) {
                best = j;
                f = d;
            }
        }
        break;
    }
    case 3: {
        float f = -30000.0f;
        int j;

        for (j = 0; j < n; j++) {
            int ok = 0;
            float d;

            if (check != 0)
                ok = func_L23_00419CE0(*keys[j]);
            FastVecSub(d1, (float *)D_00189EA0, arg0->pos);
            FastVecSub(d2, pts[j], arg0->pos);
            d = FastVecDot(d1, d2);
            if ((f < d && ok == 0) || n == 1) {
                best = j;
                f = d;
            }
        }
        break;
    }
    case 2:
    default:
        if (state->kind >= 0x22 && state->kind <= 0x25) {
            float f = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int ok = 0;
                float d;

                if (check != 0)
                    ok = func_L23_00419CE0(*keys[j]);
                FastVecSub(d1, (float *)D_00189EA0, arg0->pos);
                FastVecSub(d2, pts[j], arg0->pos);
                d = FastVecDot(d1, d2);
                if ((d < f && ok == 0) || n == 1) {
                    best = j;
                    f = d;
                }
            }
        } else {
            float lim = -0.35f;
            float f = 30000.0f;
            int j;

            for (j = 0; j < n; j++) {
                int ok = 0;
                float d;

                if (check != 0)
                    ok = func_L23_00419CE0(*keys[j]);
                FastVecSub(d1, state->target, state->origin);
                FastVecSub(d2, pts[j], state->origin);
                vec_scale_to_length(n1, d1, 1.0f);
                vec_scale_to_length(n2, d2, 1.0f);
                qcopy(a ,n1);
                qcopy(b ,n2);
                qcopy(up1,&arg0->up);
                qcopy(up2,&arg0->up);
                FastVecCross(c1, up1, a);
                FastVecCross(c2, up2, b);
                func_L00_00325600(a, state->frame, 0);
                func_L00_00325600(b, state->frame, 0);
                d = func_00282C48(FastVecDot(a, b) - lim);
                if ((d < f && ok == 0) || n == 1) {
                    best = j;
                    f = d;
                }
            }
        }
        break;
    }
    if (res[best] == 0) {
        k = idx[best];
        state->dir = 1;
    } else {
        k = idx[best];
        state->dir = -1;
    }
    state->res = res[best];
    func_L23_00419088(arg0, k);
}
