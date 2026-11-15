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

/* Spins each orbiting spark owned by this moby around it and frees the ones that finish. */
void func_L00_003BCC10(Moby3BCC10 *self) {
    f32 tmp[4] __attribute__((aligned(16)));
    Vars3BCC10 *vars = self->vars;
    f32 *pos = self->pos;
    Orbit3BCC10 *table = D_L00_0023F060;
    Orbit3BCC10 *entry;
    s32 i;

    for (i = 0; i < 16; i++) {
        entry = &table[i];
        if (entry->owner == self) {
            entry->a[0] = FastAddRotations(entry->a[0], entry->da[0]);
            entry->a[1] = FastAddRotations(entry->a[1], entry->da[1]);
            entry->a[2] = FastAddRotations(entry->a[2], entry->da[2]);
            entry->b[0] = FastAddRotations(entry->b[0], entry->db[0]);
            entry->b[1] = FastAddRotations(entry->b[1], entry->db[1]);
            entry->b[2] = FastAddRotations(entry->b[2], entry->db[2]);
            entry->v0[0] = FastSinOrCosA(entry->a[0]) * entry->ra[0];
            entry->v0[1] = FastSinOrCosB(entry->a[1]) * entry->ra[1];
            entry->v0[2] = -FastSinOrCosB(entry->a[2]) * entry->ra[2];
            entry->v1[0] = FastSinOrCosA(entry->b[0]) * entry->rb[0];
            entry->v1[1] = FastSinOrCosB(entry->b[1]) * entry->rb[1];
            entry->v1[2] = -FastSinOrCosB(entry->b[2]) * entry->rb[2];
            matrix_mul_vec3(tmp, entry->off, self->mtx);
            qcopy(entry->at, pos);
            FastVecAdd(entry->out, tmp, pos);
            if (FastFloatHelperD(&entry->timer)) {
                entry->owner = 0;
                vars->count--;
            }
        }
    }
}
