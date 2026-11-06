/* func_PAL_L00_0042FA70, the PAL copy of func_L00_0042A520: the same C, where scale D_L00_001B164C. */
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    float m10[4];
    char pad20[0xC0 - 0x20];
    float mC0[4];
    char padD0[0x10];
    float mE0[4];
} Model_42A520;

typedef struct {
    char pad0[0x20];
    Model_42A520 *model;
    int f24;
    float f28;
    float f2C;
    float f30;
    float f34;
    char pad38[0x60 - 0x38];
    float v60[4];
} Ent_42A520;

typedef struct {
    char pad0[0x1C];
    Ent_42A520 *ent;
} Rec_42A520;

typedef struct {
    float m0[4];
    float m10[4];
    float m20[4];
    float m30[4];
    char pad40[0x84 - 0x40];
    short idx;
} Self_42A520;

extern float func_00282C48(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern Rec_42A520 *D_L00_001B1844;
extern float D_L00_001B163C __attribute__((sda));
extern float D_L00_001B1640 __attribute__((sda));
extern int D_L00_001B164C __attribute__((sda));

void func_PAL_L00_0042FA70(Self_42A520 *self)
{
    float m0[4];
    float m1[4];
    float m2[4];
    float v[4];
    Ent_42A520 *e;
    Model_42A520 *m;

    e = D_L00_001B1844[self->idx].ent;
    e->f28 = D_L00_001B163C;
    e->f2C = D_L00_001B1640;
    e->f30 = func_00282C48(D_L00_001B163C);
    e->f34 = D_L00_001B1640;
    m = e->model;
    *(TI128 *)e->v60 = *(TI128 *)m->mE0;
    func_00282F20(m0, m->mC0, e->f28);
    func_00282F20(m1, e->model->mE0, e->f2C);
    func_00282CC0(m2, m1, m0);
    func_00282CC0(self->m30, m2, e->model->m10);
    func_00282CC0(m2, self->m30, m0);
    *(TI128 *)v = 0;
    v[2] = 1.0f;
    v[3] = 1.0f;
    func_00282CF0(self->m0, self->m30, m2);
    func_00282F20(self->m0, self->m0, 1.0f);
    func_00282DD8(self->m10, self->m0, v);
    func_00282F20(self->m10, self->m10, 1.0f);
    func_00282DD8(self->m20, self->m10, self->m0);
    e->f24 = (((int)(D_L00_001B164C) * 5 + 2) / 6);
}
