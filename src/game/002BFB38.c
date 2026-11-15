#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pos[16];
    s32 kind;
    s32 life;
    f32 z;
    f32 rate;
} Spark2BFB38;

typedef struct {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u32 color;
    u8 f8;
    u8 f9;
    u8 padA[2];
    f32 fC;
    f32 pos[4];
    Spark2BFB38 s;
} Effect2BFB38;

extern u8 *D_001F25CC[];

extern Effect2BFB38 *part_alloc(int);
extern int FloatToInt(float);
extern float math_random_float_range(float, float);

/* Creates a small spark effect at a spot, moving in a given direction for a set time. */
Effect2BFB38 *part_spawn_spark_2(void *pos, void *dir, s32 kind, s32 life) {
    Effect2BFB38 *e;
    Spark2BFB38 *s;

    e = part_alloc(0x23);
    if (e != 0) {
        qcopy(e->pos, pos);
        s = &e->s;
        e->color = 0x80808080;
        e->f9 = FloatToInt(2.0f) + 0x10;
        e->f1 = 0;
        e->f3 = 0x44;
        e->fC = math_random_float_range(10500.0f, 16800.0f);
        e->f2 = *D_001F25CC[0];
        qcopy(s->pos, dir);
        s->life = life;
        s->kind = kind;
        s->z = e->pos[2];
        if (kind == 2) {
            s->z = 0;
        }
        s->rate = math_random_float_range(0.0029166667f, 0.005f);
    }
    return e;
}
