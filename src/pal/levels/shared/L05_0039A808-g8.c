/* func_PAL_L05_0039A808, the PAL copy of func_L05_003979B0: the same C, where the step 1/60 becomes 0.020000001f and the timer takes the 50 Hz scale, stored after the rate. */
#include "common.h"

/* The fields of the spawned object and of its state that this function fills. */
typedef struct {
    float vec[4];               /* 0x00 */
    int a2;                     /* 0x10 */
    int zero;                   /* 0x14 */
    int count;                  /* 0x18 */
    float rate;                 /* 0x1C */
    char *a3;                   /* 0x20 */
    int flag;                   /* 0x24 */
    int value;                  /* 0x28 */
} SpawnState003979B0;

typedef struct {
    char pad00[0x10];
    float pos[4];               /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0xB];
    float scale;                /* 0x2C */
    unsigned char dist;         /* 0x30 */
    unsigned char drawn;        /* 0x31 */
    unsigned short drawDist;    /* 0x32 */
    char pad34[0x34];
    SpawnState003979B0 *st;     /* 0x68 */
    char pad6C[0x54];
    float m0[4];                /* 0xC0 */
    float m1[4];                /* 0xD0 */
    float m2[4];                /* 0xE0 */
} SpawnObject003979B0;

extern SpawnObject003979B0 *func_0029EFD0(int);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float D_L05_001AEBC4 __attribute__((sda));
extern float D_L05_001AEBD0 __attribute__((sda));
extern int D_L05_001AEBCC __attribute__((sda));

SpawnObject003979B0 *func_PAL_L05_0039A808(float *pos, float *vec, int a2, SpawnObject003979B0 *a3, int flag)
{
    SpawnObject003979B0 *obj;

    if (flag != 0)
        obj = func_0029EFD0(0x12D8);
    else
        obj = func_0029EFD0(0x1173);
    if (obj != 0) {
        SpawnState003979B0 *st;
        float f20;
        float f21;
        int count;

        obj->drawn = 1;
        obj->state = 1;
        obj->dist = 0xFF;
        st = obj->st;
        obj->drawDist = 0x1FF;
        f20 = D_L05_001AEBC4 * (0.020000001f);
        st->flag = flag;
        f21 = 1.0f;
        count = func_00283CF0(D_L05_001AEBD0);
        st->count = count;
        st->a2 = a2;
        st->a3 = (char *)a3;
        st->zero = 0;
        st->rate = f21 / D_L05_001AEBD0;
        st->value = ((s32)(D_L05_001AEBCC) * 5 + 2) / 6;
        qcopy(obj->pos, pos);
        obj->scale = obj->scale * 0.5f;
        func_00282F20(st, vec, f20);
        func_00282F20(obj->m0, st, f21);
        func_00282DD8(obj->m1, obj->m0, a3->m2);
        func_00282F20(obj->m1, obj->m1, f21);
        func_00282DD8(obj->m2, obj->m1, obj->m0);
    }
    return obj;
}
