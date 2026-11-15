#include "include_asm.h"
#include "common.h"

typedef struct { char pad[0x10]; f32 f10; char pad14[0xA]; u16 flags; } Link40B838;

typedef struct {
    f32 dir[3];
    f32 pad0C;
    s32 f10;
    f32 f14;
    s32 f18;
    s32 f1C;
    u8 pad20[0x10];
    f32 anchor_pos[4];
} Vars40B838;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[0x0F];
    u8 alpha;
    u8 f31;
    s16 f32;
    s16 f34;
    u8 pad36[0x68 - 0x36];
    Vars40B838 *vars;
    u8 pad6C[0xB8 - 0x6C];
    s32 fB8;
    u8 pad_BC[0xF0 - 0xBC];
    f32 rot[3];
} Moby40B838;

extern s32 D_L00_001B0FE4 __attribute__((sda));
extern s16 D_L00_001B2D40[3];
extern s16 D_L00_001B2D50[3];
extern Moby40B838 *CreateMoby(int);
extern Link40B838 *moby_get_private_value_0(void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecScale(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 func_002EF240(int);
extern f32 math_random_angle(void);
extern void func_002A0F48(void *);

/* Creates a Clank Zapper at a position, attached to a parent object, with random spin. */
Moby40B838 *clank_zapper_spawn(f32 *pos, int param, f32 *parent, int extra)
{
    f32 parent_pos[4] __attribute__((aligned(16)));
    f32 offset[4] __attribute__((aligned(16)));
    Moby40B838 *moby;
    Vars40B838 *vars;
    Link40B838 *link;
    int i;

    moby = CreateMoby(MOBY_CLASS_CLANK_ZAPPER);
    if (moby != 0) {
        vars = moby->vars;
        moby->alpha = 0xFF;
        moby->f34 = 0x100;
        moby->f32 = 0xFF;
        moby->f31 = 1;
        moby->fB8 = param;
        moby->state = 0;
        qcopy(vars->anchor_pos, parent + 4);
        vars->anchor_pos[2] += moby_get_private_value_0(parent)->f10;
        if (parent != 0) {
            qcopy(parent_pos, parent + 4);
            link = moby_get_private_value_0(parent);
            if (link != 0) {
                cam_compute_view_direction(parent + 4, offset, 1);
                FastVecScale(offset, offset, link->f10);
                FastVecAdd(parent_pos, parent_pos, offset);
            }
        }
        qcopy(moby->pos, pos);
        vars->f10 = D_L00_001B0FE4;
        vars->f14 = 1.0f / func_002EF240(D_L00_001B0FE4);
        vars->f1C = extra;
        *(f32 **)((char *)vars + 0xC) = parent;
        if (parent != 0) {
            link = moby_get_private_value_0(parent);
            if (link != 0)
                link->flags |= 0x80;
        }
        moby->rot[0] = math_random_angle();
        moby->rot[1] = math_random_angle();
        moby->rot[2] = math_random_angle();
        vars->dir[0] = math_random_angle();
        vars->dir[1] = math_random_angle();
        vars->dir[2] = math_random_angle();
        for (i = 0; i < 3; i++) {
            D_L00_001B2D40[i] = -1;
            D_L00_001B2D50[i] = 0x18;
        }
        moby->state = 0;
        func_002A0F48(moby);
    }
    return moby;
}
