#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    char pad[0x80];
    float pos[4];
    char gap[0x2AC];
    char *obj;
    int active;
    char gap2[0x1F70];
    unsigned char mode;
} PlayerState;
typedef struct { char pad[0x38]; float height; char tail[0x44]; } Projection;
extern PlayerState D_00189E20;
extern char D_00188660[];
extern void func_002A7750();
extern void func_002AD6F0(void *, void *, void *, void *);
extern float func_00282C48(float);
extern int func_002ACBC8(void *, int);
extern void func_002AA548(void *, void *, float, float, float, float);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_L14_003DF100(char *, int);
extern void func_L14_003DF200(char *);
extern int func_L14_003DF440(char *), func_L14_003DF540(char *);
extern void func_002B0C28(int, int, int);
extern unsigned int D_00138324 NOT_SDA;
extern Projection *D_L14_001B268C __attribute__((sda));
extern Projection *D_L14_001B268C_gp SDATA(D_L14_001B268C);
extern char D_L14_001A8F20[] __attribute__((sda));
extern float func_00282E80(void *, void *);

/* Move between the initial height and the projection-table height, updating
 * the collision displacement and keeping the movement sound active. */
void func_US2_L14_003E01F8(char *self) {
    Vec delta, velocity;
    char *state = *(char **)(self + 0x68);
    float target, speed;
    int active, blocked;

    switch ((unsigned char)self[0x20]) {
    case 0:
        if (!state || *(int *)(state + 0x60) == -1) {
            func_0029F338(self);
            return;
        }
        {
            float originalHeight = *(float *)(self + 0x18);
            *(int *)(state + 0x7C) = 0;
            *(float *)(state + 0x70) = originalHeight;
        }
        func_L14_003DF100(self, 0);
        func_002A7750(self, 1, -1);
        break;
    case 1:
        active = 0;
        if (D_00189E20.obj == self && D_00189E20.active) {
            func_L14_003DF200(self);
            if (!*(int *)(state + 0x6C) || func_L14_003DF440(self) || func_L14_003DF540(self)) {
                func_002B0C28(4, 0x12EC, 1);
                {
                    int flags = D_00138324 & 0x10;
                    active = flags != 0;
                }
            }
        } else {
            /* Keeping the distance guard in each height case lets the
             * compiler share the floating-point branch, as retail does. */
            if (*(int *)(state + 0x7C)) {
                if (D_00189E20.pos[2] - *(float *)(state + 0x70) > -0.25f) {
                    if (func_00282E80(D_00189E20.pos, self + 0x10) < 24.0f)
                        active = 1;
                }
            } else {
                PlayerState *player = &D_00189E20;
                if (func_00282C48(player->pos[2] - D_L14_001B268C[*(int *)(state + 0x60)].height) < 1.0f) {
                    if (func_00282E80(player->pos, self + 0x10) < 24.0f)
                        active = 1;
                }
            }
        }
        if (active) {
            func_002A7750(self, 2, -1);
            *(int *)(state + 0x7C) = (*(int *)(state + 0x7C) + 1) & 1;
            func_L14_003DF100(self, 1);
        }
        break;
    case 2:
        if (*(int *)(state + 0x7C))
            target = D_L14_001B268C_gp[*(int *)(state + 0x60)].height;
        else
            target = *(float *)(state + 0x70);
        speed = 0.00111111114f;
        blocked = 0;
        if (*(int *)(state + 0x7C) && D_00189E20.pos[2] < *(float *)(self + 0x18) - 1.0f &&
            func_002ACBC8(D_00189E20.pos, *(int *)(state + 0x60))) {
            blocked = 1;
            target += 1.5f;
            speed = 0.00222222228f;
        }
        if (!blocked && func_00282C48(*(float *)(self + 0x18) - target) <= *(float *)(state + 0x74)) {
            *(float *)(self + 0x18) = target;
            *(float *)(state + 0x74) = 0.0f;
            func_002A7750(self, 1, -1);
            func_L14_003DF100(self, 0);
            {
                char *collision = state + 0x20;
                func_002AD6F0(collision, D_L14_001A8F20, self + 0xF0, self + 0xF0);
            }
        } else {
            func_002AA548(self + 0x18, state + 0x74, target, 0.00055555557f, speed, 0.166666672f);
            velocity.q = 0;
            velocity.f[2] = *(float *)(state + 0x74);
            delta.q = velocity.q;
            func_002AD6F0(state + 0x20, &delta, self + 0xF0, self + 0xF0);
        }
        break;
    }
    if (func_00282C48(*(float *)(state + 0x74)) > 0.01f) {
        unsigned char *e = (unsigned char *)D_00188660 + *(int *)(state + 0x78) * 0x70;
        if (*(char **)(e + 0x88) != self || !e[0x74])
            *(int *)(state + 0x78) = func_002E5CF8(0, 4, self);
    } else {
        int n = *(int *)(state + 0x78);
        if (n != -1) {
            unsigned char *e = (unsigned char *)D_00188660 + n * 0x70;
            if (*(char **)(e + 0x88) == self && e[0x74])
                func_002E59F8(n);
        }
        *(int *)(state + 0x78) = -1;
    }
}
