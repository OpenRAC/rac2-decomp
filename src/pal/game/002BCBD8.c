#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002BCBD8);


#include "common.h"
extern char *func_002B9030(int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern unsigned char *D_001F2574, *D_001F25A4;

/* func_002BC508 is in 002BC508-g8.c. */

char *func_PAL_002BD400(char *pos, int spin, int color, float spread, float low, float high, float accel, float size)
{
    char *p = func_002B9030(13);
    char *q;
    if (p) {
        qcopy(p + 16, pos);
        q = p + 32;
        *(int *)(p + 4) = color;
        p[9] = func_00283CF0(4.0f) + 64;
        p[3] = 0x48;
        *(float *)(p + 12) = size;
        p[1] = 0;
        p[8] = 0;
        p[2] = D_001F2574[0];
        *(float *)(p + 16) += func_002A78D8(0.0f, spread);
        *(float *)(p + 20) += func_002A78D8(0.0f, spread);
        *(float *)(p + 24) += func_002A78D8(0.0f, spread);
        *(short *)(p + 10) = 8;
        *(int *)(q + 4) = 0;
        if (func_002A77E0(2))
            *(int *)(q + 8) = spin;
        else
            *(int *)(q + 8) = -spin;
        *(int *)(q + 20) = color & 0xffffff;
        *(float *)(q + 12) = func_002A7878(low, high);
        *(float *)(q + 16) = accel;
    }
    return p;
}


extern int Fd1c348f5_FUN_00282978(char *p);
extern int Fd1c348f5_FUN_00283CF0(float v);
extern void Fd1c348f5_FUN_002B9180(char *p);

void func_PAL_002BD580(char *p)
{
    char *q = p + 32;
    int r;
    int v;
    float f;

    *(unsigned char *)(p + 8) = *(unsigned char *)(p + 8) + *(unsigned char *)(q + 8);
    *(float *)(p + 24) = *(float *)(p + 24) + *(float *)(q + 16);
    *(float *)(p + 12) = *(float *)(p + 12) * *(float *)(q + 12);
    if (*(int *)(q + 4) == 0) {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            *(int *)(q + 4) = 1;
            *(short *)(p + 10) = 25;
            *(int *)(p + 4) = *(int *)(q + 20) | 0x7f000000;
        } else {
            f = (float)(8 - *(short *)(p + 10)) * 12.0f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = ((v + 32) << 24) | *(int *)(q + 20);
        }
    } else {
        r = Fd1c348f5_FUN_00282978(p + 10);
        if (r != 0) {
            Fd1c348f5_FUN_002B9180(p);
        } else {
            f = (float)*(short *)(p + 10) * 5.08f;
            v = Fd1c348f5_FUN_00283CF0(f);
            *(int *)(p + 4) = (v << 24) | *(int *)(q + 20);
        }
    }
}


typedef struct {
    unsigned char b0, b1, b2, b3;
    int color;
    unsigned char seed, alpha;
    short size;
    float life;
    float position[4];
    float payload[8];
} Particle;
extern char D_001B5340[];
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);

/* Particle tick: drift the position along its anchor, or fade out. */
void func_PAL_002BD698(Particle *p)
{
    float *pl = p->payload;
    p->seed += *(unsigned char *)pl;
    if (((int *)pl)[1] == 0) {
        float v[4] __attribute__((aligned(16)));
        qcopy(p->position, ((Particle *)((void **)pl)[2])->position);
        func_00282CF0(v, D_001B5340, p->position);
        func_00282F20(v, v, 0.01f);
        func_00282CC0(p->position, p->position, v);
    } else if (func_00282978(&p->size)) {
        func_002B9180(p);
    } else {
        p->color = (func_00283CF0(p->size * 25.4f) << 24) | 0xFFFFFF;
    }
}



