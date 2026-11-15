#include "include_asm.h"
#include "common.h"

typedef struct {
    f32 pos[3];
    f32 len;
} Seg3FDD80;

typedef struct {
    u8 pad00[0x10];
    Seg3FDD80 seg[1];
} Path3FDD80;

typedef struct {
    u8 pad000[0x314];
    s32 dest;
    s32 path;
    u8 pad31C[0x324 - 0x31C];
    s32 count;
    u8 pad328[2];
    s16 wrap;
    u8 pad32C[0x38C - 0x32C];
    f32 speed;
    u8 pad390[0x3B0 - 0x390];
    f32 scale;
    f32 vel[3];
    u8 pad3C0[0x3EC - 0x3C0];
    f32 extra;
} Vars3FDD80;

typedef struct {
    u8 pad00[0x10];
    f32 pos[3];
    u8 pad1C[0x68 - 0x1C];
    Vars3FDD80 *vars;
} Moby3FDD80;

extern Path3FDD80 *D_L09_001FE6C0[];

extern f32 func_002AA3A8(f32 *, f32 *, f32, f32, f32, f32);
extern s32 func_L00_00341820(void *path, void *out, s32 *index, f32 *offset, s32 wrap, f32 step);

void func_L09_003FDD80(Moby3FDD80 *self) {
    f32 out[4] __attribute__((aligned(16)));
    s32 index;
    f32 offset;
    Vars3FDD80 *vars = self->vars;
    Path3FDD80 *path = D_L09_001FE6C0[vars->path];
    f32 total = 0.0f;
    s32 i;

    for (i = 0; i < vars->count; i++) {
        total += path->seg[i].len;
    }
    total += vars->extra;
    index = 0;
    offset = 0.0f;
    Spline_AdvanceByDistance(D_L09_001FE6C0[vars->dest], out, &index, &offset, vars->wrap, total / vars->speed * vars->scale);
    func_002AA3A8(&self->pos[0], &vars->vel[0], out[0], 0.02f, 0.2f, 0.0f);
    func_002AA3A8(&self->pos[1], &vars->vel[1], out[1], 0.02f, 0.2f, 0.0f);
    func_002AA3A8(&self->pos[2], &vars->vel[2], out[2], 0.02f, 0.2f, 0.0f);
}
