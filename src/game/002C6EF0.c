#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

typedef struct {
    u8 f0;
    u8 f1;
    u8 shade;
    u8 f3;
    u32 color;
    u8 life;
    u8 f9;
    s16 age;
    u32 color2;
    f32 pos[4];
    f32 prev[4];
    f32 vel[4];
} Spark2C6EF0;

extern u8 *g_part_tex_spark_trail_table[];

extern s32 FastDecTimer(s16 *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern void part_kill(void *);

/* Updates a spark that flies along, leaves a short streak behind it and fades out. */
void part_update_spark_trail(Spark2C6EF0 *e) {
    f32 old[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    f32 *vel = e->vel;
    f32 *pos;
    f32 t;
    u32 a;

    if (FastDecTimer(&e->age)) {
        part_kill(e);
        return;
    }
    pos = e->pos;
    e->shade = g_part_tex_spark_trail_table[0][math_random_int_below(2)];
    qcopy(old, pos);
    FastVecAdd(pos, pos, vel);
    FastVecSub(step, pos, old);
    vec_scale_to_length(step, step, 0.9f);
    FastVecSub(e->prev, pos, step);
    e->prev[3] = 2.0f;
    vel[2] = vel[2] - vel[3];
    if (e->age < e->life) {
        t = IntToFloat(e->age);
        t = t / IntToFloat(e->life);
        a = FloatToInt(t * 127.0f) << 24;
        e->color = a | (e->color & 0xFFFFFF);
        e->color2 = a | (e->color2 & 0xFFFFFF);
    }
}
