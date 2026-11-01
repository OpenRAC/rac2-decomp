#include "include_asm.h"

#include "common.h"
typedef struct {
    u8 q[8];
    f32 height;
    u8 pad0C[4];
    s32 drop;
    s32 state;
} L03Vars9C38;
typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[3];
    s32 *cls;
    u8 pad28[0x34 - 0x28];
    u16 flags;
    u8 pad36[0x68 - 0x36];
    L03Vars9C38 *vars;
    u8 pad6C[0x98 - 0x6C];
    s32 f98;
} L03Moby9C38;
extern f32 D_L03_001B1654 __attribute__((sda));
extern f32 D_L03_001B1658 __attribute__((sda));
extern void func_002A7750(void *, int, int);
extern void func_002A93B0(void *);
extern float func_002AA548(void *, void *, float, float, float, float);

void func_PAL_L03_0040EA18(L03Moby9C38 *self, s32 quiet) {
    L03Vars9C38 *vars = self->vars;

    if (self->state != 2) {
        self->flags = (self->flags & 0xFFBE) | 0x1000;
        self->f98 = self->cls[4];
        func_002A7750(self, 2, -1);
        qcopy(self->pos, vars);
        vars->drop = 0;
        if (quiet == 0) {
            self->pos[2] = self->pos[2] + 10.0f;
            func_002AA548(&self->pos[2], &vars->drop, vars->height, 1.0f,
                          D_L03_001B1654 * 0.00040000002f, D_L03_001B1658 * 0.020000001f);
        }
    }
    self->flags |= 0x400;
    func_002A93B0(self);
    vars->state = 4;
}
