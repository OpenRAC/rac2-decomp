#include "include_asm.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    Vec pos; float z_vel; char pad14[12];
    Vec up, target, prev_target; float velocity[4];
    Vec prev_pos, delta, side, projection;
    float distance, side_distance, up_distance, yaw[5];
} Follow;
extern Follow D_001B53A0;
typedef struct {char prefix[0x80]; Vec pos, rot; char padA0[0x21f4]; int state; char pad2298[0x208]; int mode;} Hero;
extern char D_00189E20[], D_0018A0E0[];
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern float func_002702C8(float *, float, float, float, float, float);
/* Follow camera update: computes the direction from the hero, smooths the follow target and adjusts the up vector. */
void func_00271B90(void)
{
    Vec dir, projection;
    Follow *f = &D_001B53A0;
    char *hero = D_0018A0E0;
    float d;
    int i;
    func_00282F20(&dir, hero, -1.0f);
    f->prev_target.q = f->target.q;
    f->target.q = dir.q;
    if (func_00282DB0(&f->up, &dir) < -0.98f) {
        dir.f[0] += 0.2f;
        dir.f[1] += 0.2f;
        dir.f[2] += 0.2f;
    }
    f->up.f[0] = func_002702C8(&f->velocity[0], f->up.f[0], dir.f[0], 0.015f, 0.2f, 0.0f);
    f->up.f[1] = func_002702C8(&f->velocity[1], f->up.f[1], dir.f[1], 0.015f, 0.2f, 0.0f);
    f->up.f[2] = func_002702C8(&f->velocity[2], f->up.f[2], dir.f[2], 0.015f, 0.2f, 0.0f);
    func_00282F20(&f->up, &f->up, 1.0f);
    func_00282CF0(&f->delta, hero - 0x240, &f->prev_pos);
    f->distance = func_00282DF0(&f->delta);
    d = func_00282DB0(&f->delta, &dir);
    f->up_distance = d;
    func_00282F20(&projection, &dir, d);
    f->projection.q = projection.q;
    func_00282CF0(&f->side, &f->delta, &projection);
    f->side_distance = func_00282DF0(&f->side);
    d = 1.0f / f->side_distance;
    func_00282D30(&f->side, &f->side, d);
    f->prev_pos.q = *(Quad *)(hero - 0x240);
    { Hero *g = (Hero *)(hero - 0x2c0);
    if (g->mode != 0x50 || g->state == 0x11) {
        f->pos.f[0] = g->pos.f[0];
        f->pos.f[1] = g->pos.f[1];
        f->pos.f[2] = func_002702C8(&f->z_vel, f->pos.f[2], g->pos.f[2], 0.0075f, 0.175f, 0.0f);
        f->pos.f[3] = g->pos.f[2];
    } else {
        f->pos.f[0] = g->pos.f[0];
        f->pos.f[1] = g->pos.f[1];
    }
    }
    for (i = 0; i < 4; i++) f->yaw[i] = f->yaw[i + 1];
    f->yaw[i] = ((Hero *)D_00189E20)->rot.f[2];
}
