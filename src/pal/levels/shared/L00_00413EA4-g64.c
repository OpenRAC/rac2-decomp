#include "include_asm.h"
#include "names.h"

typedef struct {
    int count0;
    int pad4;
    float f8;
    char padC[0x28 - 0xC];
    int n;
} Node_410508;
typedef struct {
    char pad0[0x20];
    float f20;
} Sub_410508;
typedef struct {
    char pad0[0x10];
    float pos[4];
    char pad20[0x68 - 0x20];
    void *node;
    char pad6C[0xB8 - 0x6C];
    void *owner;
    char padBC[0xC0 - 0xBC];
    float mtx[4];
} Obj_410508;
extern int get_ammo(int);
extern int weapon_spend_ammo(int, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void *projectile_spawn_targeted_pal(int a, void *b, int c, char *d, float e, float f, float g, float h);
extern float g_sequenced_child_offset_table[4][4] __attribute__((sda));
extern int g_sequenced_child_flag __attribute__((nosda));

void sequenced_child_spawn_pal(Obj_410508 *self)
{
    Node_410508 *st = self->node;
    float v[4];
    float w[4];
    float sign;
    int n;
    Obj_410508 *r;

    if (get_ammo(-1) == 0) {
        st->n = -1;
        return;
    }
    n = st->n;
    sign = (float)(n & 1);
    if (sign == 0.0f)
        sign = -1.0f;
    st->n = n - 1;
    matrix_mul_vec3(v, g_sequenced_child_offset_table[n], self->mtx);
    FastVecAdd(w, self->pos, v);
    if (st->n == -1) {
        if (st->count0 != 0) {
            v[2] = 0.0f;
            v[0] = 0.0f;
        }
    }
    r = (Obj_410508 *)projectile_spawn_targeted_pal((int)self, w, st->count0, (char *)v, st->f8, 4.0f, 8.0f, 0.5f);
    if (r != 0) {
        Sub_410508 *p;
        weapon_spend_ammo(-1, 1);
        g_sequenced_child_flag = 1;
        r->owner = self;
        p = r->node;
        {
            float f = p->f20, z = 0.0f;

            if (z < f && sign < z)
                p->f20 = -f;
            else if (f < z && z < sign)
                p->f20 = -p->f20;
        }
    }
}
