#include "include_asm.h"

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
extern void func_PAL_L02_003EFD50();
extern char D_00188660[];
extern char *D_L02_001B368C;
extern float D_L02_001B0DB8 __attribute__((sda));
extern float D_L02_001B0DBC __attribute__((sda));

void func_PAL_L02_003EFAA0(Actor *arg0) {
    State *state = arg0->state;
    float pos[4];
    float vel[4];
    float tmp[4];
    float tmp2[4];
    char *rec;
    TI128 t;

    *(TI128 *)pos = *(TI128 *)arg0->pos;
    *(TI128 *)vel = *(TI128 *)arg0->vel;
    switch (arg0->kind) {
    case 0:
        if (state->index == -1) {
            func_002A7750(arg0, 3, -1);
            return;
        }
        if (func_00282C48(*(float *)((char *)((state->index << 7) + (int)D_L02_001B368C) + 0x28) - 2.0f) < 0.01f) {
            arg0->update = (int)func_PAL_L02_003EFD50;
            return;
        }
        state->flags |= 0x10;
        func_00282CF0(tmp, arg0->pos, D_L02_001B368C + (state->index << 7) + 0x30);
        func_00283098(tmp, tmp, D_L02_001B368C + (state->index << 7) + 0x40);
        state->angle = state->t * 6.2831855f - 3.1415927f;
        state->lx = tmp[0];
        state->lz = tmp[2];
        state->slot = -1;
        func_002A7750(arg0, 2, -1);
        break;
    case 2:
        state->angle = func_00283B98(state->angle, D_L02_001B0DBC * 0.0003490659f);
        state->ly = D_L02_001B0DB8 * func_00283198(state->angle);
        rec = D_00188660 + state->slot * 0x70;
        if (*(int *)(rec + 0x88) != (int)arg0 || *(unsigned char *)(rec + 0x74) == 0)
            state->slot = func_002E5CF8(0, 4, arg0);
        *(TI128 *)tmp2 = 0;
        tmp2[0] = state->lx;
        tmp2[1] = state->ly;
        tmp2[2] = state->lz;
        tmp2[3] = 1.0f;
        t = *(TI128 *)tmp2;
        *(TI128 *)tmp = t;
        func_002830C0(arg0->pos, tmp, D_L02_001B368C + (state->index << 7));
        break;
    }
    func_00282CF0(tmp, arg0->pos, pos);
    func_002AD6F0(state->x20, tmp, vel, arg0->vel);
}
