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
extern void *projectile_spawn_targeted(int a, void *b, int c, char *d, float e, float f, float g, float h);
extern float D_L00_001B12C0[4][4] __attribute__((sda));
extern int D_L00_001B2D58 __attribute__((nosda));

/* Spawns the next piece of a timed sequence at a spot picked from a table, then counts the sequence down. Ends the sequence when nothing more can be spawned. */
void sequenced_child_spawn(Obj_410508 *self)
{
    Node_410508 *vars = self->node;
    float offset[4];
    float spawnPos[4];
    float spinSign;
    int step;
    Obj_410508 *child;

    if (get_ammo(-1) == 0) {
        vars->n = -1;
        return;
    }
    step = vars->n;
    spinSign = (float)(step & 1);
    if (spinSign == 0.0f)
        spinSign = -1.0f;
    vars->n = step - 1;
    matrix_mul_vec3(offset, D_L00_001B12C0[step], self->mtx);
    FastVecAdd(spawnPos, self->pos, offset);
    if (vars->n == -1) {
        if (vars->count0 != 0) {
            offset[2] = 0.0f;
            offset[0] = 0.0f;
        }
    }
    child = (Obj_410508 *)projectile_spawn_targeted((int)self, spawnPos, vars->count0, (char *)offset, vars->f8, 4.0f, 8.0f, 0.5f);
    if (child != 0) {
        Sub_410508 *childVars;
        weapon_spend_ammo(-1, 1);
        D_L00_001B2D58 = 1;
        child->owner = self;
        childVars = child->node;
        {
            float spin = childVars->f20, zero = 0.0f;

            if (zero < spin && spinSign < zero)
                childVars->f20 = -spin;
            else if (spin < zero && zero < spinSign)
                childVars->f20 = -childVars->f20;
        }
    }
}
