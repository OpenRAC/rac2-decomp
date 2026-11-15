#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

typedef struct {
    f32 v0[4];
    f32 v1[4];
    f32 at[4];
    f32 out[4];
    f32 off[4];
    f32 a[3];
    f32 da[3];
    f32 ra[3];
    f32 b[3];
    f32 db[3];
    f32 rb[3];
    s32 timer;
    u8 pad9C[4];
    void *owner;
    u8 padA4[0xB0 - 0xA4];
} Orbit3BCC10;

typedef struct {
    u8 pad00[0x58];
    s32 count;
} Vars3BCC10;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 pad20[0x68 - 0x20];
    Vars3BCC10 *vars;
    u8 pad6C[0xC0 - 0x6C];
    f32 mtx[16];
} Moby3BCC10;

extern Orbit3BCC10 D_L00_0023F060[16];

extern int func_00282948(void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float, float);

void func_L00_003BCC10(Moby3BCC10 *self) {
    f32 tmp[4] __attribute__((aligned(16)));
    Vars3BCC10 *vars = self->vars;
    f32 *pos = self->pos;
    Orbit3BCC10 *tab = D_L00_0023F060;
    Orbit3BCC10 *e;
    s32 i;

    for (i = 0; i < 16; i++) {
        e = &tab[i];
        if (e->owner == self) {
            e->a[0] = FastAddRotations(e->a[0], e->da[0]);
            e->a[1] = FastAddRotations(e->a[1], e->da[1]);
            e->a[2] = FastAddRotations(e->a[2], e->da[2]);
            e->b[0] = FastAddRotations(e->b[0], e->db[0]);
            e->b[1] = FastAddRotations(e->b[1], e->db[1]);
            e->b[2] = FastAddRotations(e->b[2], e->db[2]);
            e->v0[0] = func_00283180(e->a[0]) * e->ra[0];
            e->v0[1] = func_00283198(e->a[1]) * e->ra[1];
            e->v0[2] = -func_00283198(e->a[2]) * e->ra[2];
            e->v1[0] = func_00283180(e->b[0]) * e->rb[0];
            e->v1[1] = func_00283198(e->b[1]) * e->rb[1];
            e->v1[2] = -func_00283198(e->b[2]) * e->rb[2];
            matrix_mul_vec3(tmp, e->off, self->mtx);
            qcopy(e->at, pos);
            FastVecAdd(e->out, tmp, pos);
            if (func_00282948(&e->timer)) {
                e->owner = 0;
                vars->count--;
            }
        }
    }
}
