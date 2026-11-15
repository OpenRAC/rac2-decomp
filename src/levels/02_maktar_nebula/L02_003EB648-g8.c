#include "include_asm.h"
#include "names.h"

/* func_L02_003EB648 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(void *, int, int);

extern float func_00282C48(float);

extern void func_00282CF0(void *, void *, void *);

extern void func_00283098(void *, void *, void *);

extern void func_002830C0(void *, void *, void *);

extern float func_00283B98(float, float);

extern float func_00283198(float);

typedef struct {
    char pad0[0x20];
    char x20[0x3C];
    int flags;
    int index;
    float t;
    float angle;
    char pad6c[8];
    float lx;
    float ly;
    float lz;
    int slot;
} State;

typedef struct {
    char pad0[0x10];
    float pos[4];
    unsigned char kind;
    char pad21[0x43];
    int update;
    State *state;
    char pad6c[0x84];
    float vel[4];
} Actor;

extern int func_002E5CF8(int, int, void *);

extern void func_002AD6F0(void *, void *, void *, void *);

extern void func_L02_003EB8F8();

extern char D_00188660[];

extern char *D_L02_001B368C;

extern float D_L02_001B0DB8 __attribute__((sda));

extern float D_L02_001B0DBC __attribute__((sda));

/* Attaches the actor to a moving surface, then makes it bob up and down on it
   and passes its movement on. */
void func_L02_003EB648(Actor *actor) {
    State *state = actor->state;
    float prevPos[4];
    float prevVel[4];
    float offset[4];
    float localPoint[4];
    char *soundSlot;
    TI128 quad;

    *(TI128 *)prevPos = *(TI128 *)actor->pos;
    *(TI128 *)prevVel = *(TI128 *)actor->vel;
    switch (actor->kind) {
    case 0:
        if (state->index == -1) {
            SetMobyState(actor, 3, -1);
            return;
        }
        if (FloatAbs(*(float *)((char *)((state->index << 7) + (int)D_L02_001B368C) + 0x28) - 2.0f) < 0.01f) {
            actor->update = (int)UpdateElevatorMoby_L02;
            return;
        }
        state->flags |= 0x10;
        FastVecSub(offset, actor->pos, D_L02_001B368C + (state->index << 7) + 0x30);
        matrix_mul_vec3(offset, offset, D_L02_001B368C + (state->index << 7) + 0x40);
        state->angle = state->t * 6.2831855f - 3.1415927f;
        state->lx = offset[0];
        state->lz = offset[2];
        state->slot = -1;
        SetMobyState(actor, 2, -1);
        break;
    case 2:
        state->angle = FastAddRotations(state->angle, D_L02_001B0DBC * 0.0002908882452175021f);
        state->ly = D_L02_001B0DB8 * FastSinOrCosB(state->angle);
        soundSlot = gSoundState + state->slot * 0x70;
        if (*(int *)(soundSlot + 0x88) != (int)actor || *(unsigned char *)(soundSlot + 0x74) == 0)
            state->slot = PlayMobySound(0, 4, actor);
        *(TI128 *)localPoint = 0;
        localPoint[0] = state->lx;
        localPoint[1] = state->ly;
        localPoint[2] = state->lz;
        localPoint[3] = 1.0f;
        quad = *(TI128 *)localPoint;
        *(TI128 *)offset = quad;
        transform_vector(actor->pos, offset, D_L02_001B368C + (state->index << 7));
        break;
    }
    FastVecSub(offset, actor->pos, prevPos);
    CombineTransformsAndStore(state->x20, offset, prevVel, actor->vel);
}
