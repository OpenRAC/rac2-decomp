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

Moby40B838 *func_PAL_L00_00410418(f32 *pos, int arg1, f32 *parent, int arg3)
{
    f32 tmp[4] __attribute__((aligned(16)));
    f32 vec[4] __attribute__((aligned(16)));
    Moby40B838 *m;
    Vars40B838 *vars;
    Link40B838 *link;
    int i;

    m = CreateMoby(0xED8);
    if (m != 0) {
        vars = m->vars;
        m->alpha = 0xFF;
        m->f34 = 0x100;
        m->f32 = 0xFF;
        m->f31 = 1;
        m->fB8 = arg1;
        m->state = 0;
        qcopy(vars->vec, parent + 4);
        vars->vec[2] += moby_get_private_value_0(parent)->f10;
        if (parent != 0) {
            qcopy(tmp, parent + 4);
            link = moby_get_private_value_0(parent);
            if (link != 0) {
                cam_compute_view_direction(parent + 4, vec, 1);
                FastVecScale(vec, vec, link->f10);
                FastVecAdd(tmp, tmp, vec);
            }
        }
        qcopy(m->pos, pos);
        {
            int scaled = ((s32)(g_clank_zapper_timer) * 5 + 2) / 6;
            vars->f10 = scaled;
            vars->f14 = 1.0f / IntToFloat(scaled);
        }
        vars->f1C = arg3;
        *(f32 **)((char *)vars + 0xC) = parent;
        if (parent != 0) {
            link = moby_get_private_value_0(parent);
            if (link != 0)
                link->flags |= 0x80;
        }
        m->rot[0] = math_random_angle();
        m->rot[1] = math_random_angle();
        m->rot[2] = math_random_angle();
        vars->dir[0] = math_random_angle();
        vars->dir[1] = math_random_angle();
        vars->dir[2] = math_random_angle();
        for (i = 0; i < 3; i++) {
            g_strand_timers[i] = -1;
            g_strand_periods[i] = 0x18;
        }
        m->state = 0;
        func_002A0F48(m);
    }
    return m;
}
