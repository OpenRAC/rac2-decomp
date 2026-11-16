/* func_PAL_L00_00410418, the PAL copy of func_L00_0040B838: the same C, where D_L00_001B0FE4 is scaled for 50 Hz. */
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
    f32 vec[4];
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

extern s32 g_clank_zapper_timer __attribute__((sda));
extern s16 g_strand_timers[3];
extern s16 g_strand_periods[3];
extern Moby40B838 *CreateMoby(int);
extern Link40B838 *moby_get_private_value_0(void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecScale(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern f32 IntToFloat(int);
extern f32 math_random_angle(void);
extern void func_002A0F48(void *);

/* Creates a Clank Zapper at a position, attached to a parent object, with random spin. (PAL: 50 Hz timings) */
Moby40B838 *clank_zapper_spawn_pal(f32 *pos, int param, f32 *parent, int extra)
{
    f32 attach_position[4] __attribute__((aligned(16)));
    f32 view_direction[4] __attribute__((aligned(16)));
    Moby40B838 *zapper;
    Vars40B838 *vars;
    Link40B838 *link;
    int i;

    zapper = CreateMoby(0xED8);
    if (zapper != 0) {
        vars = zapper->vars;
        zapper->alpha = 0xFF;
        zapper->f34 = 0x100;
        zapper->f32 = 0xFF;
        zapper->f31 = 1;
        zapper->fB8 = param;
        zapper->state = 0;
        qcopy(vars->vec, parent + 4);
        vars->vec[2] += moby_get_private_value_0(parent)->f10;
        if (parent != 0) {
            qcopy(attach_position, parent + 4);
            link = moby_get_private_value_0(parent);
            if (link != 0) {
                cam_compute_view_direction(parent + 4, view_direction, 1);
                FastVecScale(view_direction, view_direction, link->f10);
                FastVecAdd(attach_position, attach_position, view_direction);
            }
        }
        qcopy(zapper->pos, pos);
        {
            int scaled = ((s32)(g_clank_zapper_timer) * 5 + 2) / 6;
            vars->f10 = scaled;
            vars->f14 = 1.0f / IntToFloat(scaled);
        }
        vars->f1C = extra;
        *(f32 **)((char *)vars + 0xC) = parent;
        if (parent != 0) {
            link = moby_get_private_value_0(parent);
            if (link != 0)
                link->flags |= 0x80;
        }
        zapper->rot[0] = math_random_angle();
        zapper->rot[1] = math_random_angle();
        zapper->rot[2] = math_random_angle();
        vars->dir[0] = math_random_angle();
        vars->dir[1] = math_random_angle();
        vars->dir[2] = math_random_angle();
        for (i = 0; i < 3; i++) {
            g_strand_timers[i] = -1;
            g_strand_periods[i] = 0x18;
        }
        zapper->state = 0;
        func_002A0F48(zapper);
    }
    return zapper;
}
