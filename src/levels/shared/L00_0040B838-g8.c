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

extern s32 D_L00_001B0FE4 __attribute__((sda));
extern s16 D_L00_001B2D40[3];
extern s16 D_L00_001B2D50[3];
extern Moby40B838 *func_0029EFD0(int);
extern Link40B838 *func_002AB1F0(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_00282D30(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_002EF240(int);
extern f32 func_002A7940(void);
extern void func_002A0F48(void *);

Moby40B838 *func_L00_0040B838(f32 *pos, int arg1, f32 *parent, int arg3)
{
    f32 tmp[4] __attribute__((aligned(16)));
    f32 vec[4] __attribute__((aligned(16)));
    Moby40B838 *m;
    Vars40B838 *vars;
    Link40B838 *link;
    int i;

    m = func_0029EFD0(0xED8);
    if (m != 0) {
        vars = m->vars;
        m->alpha = 0xFF;
        m->f34 = 0x100;
        m->f32 = 0xFF;
        m->f31 = 1;
        m->fB8 = arg1;
        m->state = 0;
        qcopy(vars->vec, parent + 4);
        vars->vec[2] += func_002AB1F0(parent)->f10;
        if (parent != 0) {
            qcopy(tmp, parent + 4);
            link = func_002AB1F0(parent);
            if (link != 0) {
                func_002AFFD8(parent + 4, vec, 1);
                func_00282D30(vec, vec, link->f10);
                func_00282CC0(tmp, tmp, vec);
            }
        }
        qcopy(m->pos, pos);
        vars->f10 = D_L00_001B0FE4;
        vars->f14 = 1.0f / func_002EF240(D_L00_001B0FE4);
        vars->f1C = arg3;
        *(f32 **)((char *)vars + 0xC) = parent;
        if (parent != 0) {
            link = func_002AB1F0(parent);
            if (link != 0)
                link->flags |= 0x80;
        }
        m->rot[0] = func_002A7940();
        m->rot[1] = func_002A7940();
        m->rot[2] = func_002A7940();
        vars->dir[0] = func_002A7940();
        vars->dir[1] = func_002A7940();
        vars->dir[2] = func_002A7940();
        for (i = 0; i < 3; i++) {
            D_L00_001B2D40[i] = -1;
            D_L00_001B2D50[i] = 0x18;
        }
        m->state = 0;
        func_002A0F48(m);
    }
    return m;
}
