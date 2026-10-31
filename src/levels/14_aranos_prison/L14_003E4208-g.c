#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

extern float func_002A7878(float, float);
extern int func_00282948(int *counter);
extern void func_00283098(void *dst, void *a, void *mtx);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_002A7750(char *object, int state, int arg);
extern int func_002B3868(char *self);
extern void func_002E59F8(int index);
extern int func_002E5CF8(int index, int a1, char *a2);
extern int func_00283D38(int a, int b, float t);
extern float func_002AA140(float a, float b, float t);
/* The particle spawner (src/levels/shared/L00_0033E888-qcopy.c), declared with the life and
   rotation floats among the integer arguments: the EE ABI keeps each register bank's order. */
extern void *func_L00_0033E888(void *position, void *velocity, int color, int value, float life, int size,
                               int extra, float rotation, int texture, int flags, int weight);
extern char D_00188660[];
extern char D_L14_001A8F20[] __attribute__((sda));

/* The state block of a particle emitter. */
typedef struct {
    float rate_start;   /* 0x00 */
    float rate_end;     /* 0x04 */
    float accum;        /* 0x08 */
    float trigger;      /* 0x0C */
    int size;           /* 0x10 */
    int total;          /* 0x14 */
    int reset;          /* 0x18 */
    int remaining;      /* 0x1C */
    float spread[3];    /* 0x20 */
    float rotation;     /* 0x2C */
    int color[4];       /* 0x30 */
    float life_min[2];  /* 0x40 */
    float life_max[2];  /* 0x48 */
    int entry;          /* 0x50 */
} Emitter;

/* Particle emitter state machine. State 0 fills in the emitter block at self+0x68. State 2 stops
   the sound slot self still owns, then, while func_00282948 has not finished the remaining count,
   spawns particles at self+0x10 whenever the accumulated emission rate exceeds 1, with the rate
   and color ramped over that count; once the count is done it moves to state 3. State 3 claims a
   sound slot if self does not own one and keeps spawning at the end rate until triggered. */
void func_L14_003E4208(char *self)
{
    Emitter *st = *(Emitter **)(self + 0x68);
    Vec pos;
    Vec vel;
    Vec tmp;
    float rate;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        st->trigger = 0.0f;
        st->rate_start = 2.0f;
        st->rate_end = 30.0f;
        st->size = 60;
        st->total = 100;
        st->reset = 100;
        st->spread[0] = 0.005f;
        st->spread[1] = 0.01f;
        st->spread[2] = 0.002f;
        st->rotation = 4.0f;
        st->life_min[0] = 105000.0f;
        st->life_min[1] = 210000.0f;
        st->life_max[0] = 210000.0f;
        st->life_max[1] = 420000.0f;
        st->color[0] = 0x30505000;
        st->color[2] = 0x80508000;
        st->color[1] = 0x70700050;
        st->color[3] = 0x80800070;
        st->entry = -1;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (st->trigger == 1.0f) {
            st->trigger = 0.0f;
            func_002A7750(self, 2, -1);
        }
        break;
    case 2: {
        int a;
        int color;
        int value;
        float life;
        float rotation;

        if (st->trigger == 1.0f) {
            st->trigger = 0.0f;
            func_002A7750(self, 2, -1);
        }
        if (func_002B3868(self)) {
            st->accum = 0.0f;
            st->remaining = st->total;
        }
        if (st->entry != -1) {
            char *e = D_00188660 + st->entry * 0x70;
            if (*(int *)(e + 0x88) == (int)self && *(unsigned char *)(e + 0x74) != 0) {
                func_002E59F8(st->entry);
            }
        }
        st->entry = -1;
        if (func_00282948(&st->remaining) == 0) {
            rate = (st->rate_end - st->rate_start) / (float)st->total;
            rate = st->rate_start + rate * (((float)st->total - (float)st->remaining) - 0.008333334f);
            rate *= 0.016666668f;
            st->accum += rate;
            while (st->accum > 1.0f) {
                char *src = self + 0x10;

                qcopy(&pos, src);
                qcopy(&vel, D_L14_001A8F20);
                qcopy(&tmp, D_L14_001A8F20);
                tmp.f[0] += 1.1f;
                func_00283098(&tmp, &tmp, self + 0xC0);
                func_00282CC0(&pos, &pos, &tmp);
                a = func_00283D38(st->color[0], st->color[2], func_002A7878(0.0f, 1.0f));
                color = func_00283D38(func_00283D38(st->color[1], st->color[3], func_002A7878(0.0f, 1.0f)), a,
                                      (float)st->remaining / (float)st->total);
                value = color & 0xFFFFFF;
                life = func_002A7878(func_002AA140(st->life_max[0], st->life_min[0], (float)st->remaining / (float)st->total),
                                     func_002AA140(st->life_max[1], st->life_min[1], (float)st->remaining / (float)st->total));
                if (st->remaining < st->total / 3) {
                    vel.f[0] += func_002A7878(0.0f, st->spread[0] * 2.0f);
                    vel.f[1] += func_002A7878(0.0f, st->spread[1] * 2.0f);
                    vel.f[2] += func_002A7878(-st->spread[2], 0.0f);
                    life *= 1.5f;
                    rotation = 0.0f;
                } else {
                    vel.f[0] += func_002A7878(0.0f, st->spread[0]);
                    vel.f[1] += func_002A7878(0.0f, st->spread[1]);
                    vel.f[2] += func_002A7878(-st->spread[2], 0.0f);
                    rotation = st->rotation;
                }
                func_00283098(&vel, &vel, self + 0xC0);
                func_L00_0033E888(&pos, &vel, color, value, life, st->size, 0, rotation, 2, -1, 0);
                st->accum -= 1.0f;
            }
        } else {
            func_002A7750(self, 3, -1);
        }
        break;
    }
    case 3: {
        char *e;

        func_002B3868(self);
        e = D_00188660 + st->entry * 0x70;
        if (*(int *)(e + 0x88) != (int)self || *(unsigned char *)(e + 0x74) == 0) {
            st->entry = func_002E5CF8(0, 4, self);
        }
        if (st->trigger == 0.0f) {
            rate = (st->rate_end - st->rate_start) / (float)st->total;
            rate = st->rate_start + rate * ((float)st->total - 0.008333334f);
            rate *= 0.016666668f;
            st->accum += rate;
            while (st->accum > 1.0f) {
                int color;
                int value;
                float life;

                qcopy(&pos, self + 0x10);
                qcopy(&vel, D_L14_001A8F20);
                qcopy(&tmp, D_L14_001A8F20);
                tmp.f[0] += 1.1f;
                func_00283098(&tmp, &tmp, self + 0xC0);
                func_00282CC0(&pos, &pos, &tmp);
                color = func_00283D38(st->color[1], st->color[3], func_002A7878(0.0f, 1.0f));
                value = color & 0xFFFFFF;
                life = func_002A7878(func_002AA140(st->life_max[0], st->life_min[0], (float)st->remaining / (float)st->total),
                                     func_002AA140(st->life_max[1], st->life_min[1], (float)st->remaining / (float)st->total));
                vel.f[0] += func_002A7878(0.0f, st->spread[0] * 2.0f);
                vel.f[1] += func_002A7878(0.0f, st->spread[1] * 2.0f);
                vel.f[2] += func_002A7878(-st->spread[2], 0.0f);
                life *= 1.5f;
                func_00283098(&vel, &vel, self + 0xC0);
                func_L00_0033E888(&pos, &vel, color, value, life, st->size, 0, 0.0f, 2, -1, 0);
                st->accum -= 1.0f;
            }
        } else {
            st->trigger = 0.0f;
            func_002A7750(self, 2, -1);
        }
        break;
    }
    }
}
