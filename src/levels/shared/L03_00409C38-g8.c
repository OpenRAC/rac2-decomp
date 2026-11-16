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

extern f32 g_slim_ship_turn_rate __attribute__((sda));
extern f32 g_slim_ship_accel __attribute__((sda));

extern void moby_set_state(void *, int, int);
extern void moby_update_ground_check(void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);

/* Starts the object falling; when not quiet it first lifts the object a little and gives it a downward push. */
void moby_start_drop(L03Moby9C38 *self, s32 quiet) {
    L03Vars9C38 *vars = self->vars;

    if (self->state != 2) {
        self->flags = (self->flags & 0xFFBE) | 0x1000;
        self->f98 = self->cls[4];
        moby_set_state(self, 2, -1);
        qcopy(self->pos, vars);
        vars->drop = 0;
        if (quiet == 0) {
            self->pos[2] = self->pos[2] + 10.0f;
            math_step_value_toward_target(&self->pos[2], &vars->drop, vars->height, 1.0f,
                          g_slim_ship_turn_rate * 0.00027777778f, g_slim_ship_accel * 0.016666668f);
        }
    }
    self->flags |= 0x400;
    moby_update_ground_check(self);
    vars->state = 4;
}
