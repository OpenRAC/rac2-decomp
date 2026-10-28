/* func_L00_00408800 - 496 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_L00_00408800: draft.c is a whole file,
   src/levels/shared/L00_00408800-hazard.c, cflags line:
   `src/levels/shared/L00_00408800-hazard.c      -O2 -G0 -ffunction-sections
   -frac2-hazard-labels`; remove the INCLUDE_ASM marker from L00_003FFA70.c.
   Sibling of func_L00_00403730 (same spawn code). 2 diff lines only.
   Needed: chain assignment `m->f32 = m->alpha = 0x7F;` (separate li 0x7F),
   -frac2-hazard-labels, struct view of D_00189E20 with floats at 0x80/0x84.
   Left: final call func_002ACA50(m, D_L00_001B2030, 0x1F): retail `daddu
   a0,s0 ; lui a1,0x1B ; addiu a1,.. ; jal ; a2=0x1F`; mine `lui a1` before
   `daddu a0,s0`. Tried array vs &scalar decl. */

#include "include_asm.h"
#include "common.h"

typedef struct {
    u8 pad00[4];
    u8 f4;
    u8 pad05[0xE0 - 5];
} Weapon408800;

typedef struct {
    u8 pad00[0x10];
    s32 f10;
} Class408800;

typedef struct {
    u8 pad00[0x54];
    s16 delay;
    s16 f56;
    u8 pad58[4];
    s32 f5C;
    s32 f60;
    u8 pad64[4];
    f32 rate;
    u8 pad6C[4];
    s32 f70;
    s32 f74;
    s32 f78;
} Vars408800;

typedef struct {
    u8 pad00[0xE];
    u8 mode;
    u8 pad0F[0x17 - 0xF];
    u8 f17;
} Link408800;

typedef struct {
    u8 pad00[0x10];
    f32 pos[4];
    u8 state;
    u8 pad21[3];
    Class408800 *cls;
    u8 pad28[8];
    u8 alpha;
    u8 f31;
    s16 f32;
    u16 flags;
    u8 pad36[0x48 - 0x36];
    f32 scale;
    u8 pad4C[0x68 - 0x4C];
    Vars408800 *vars;
    u8 pad6C[0x98 - 0x6C];
    s32 f98;
    u8 pad9C[0xC0 - 0x9C];
    f32 mtx[12];
    f32 rot[4];
} Moby408800;

extern s32 D_001A8FF4[] __attribute__((sda));
extern s32 D_001A8FF0[] __attribute__((sda));
extern u8 D_00139578[];
extern Weapon408800 D_L00_00262570[];

extern void func_00282C88(void *);
extern void func_00283658(void *, void *);
extern Moby408800 *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern void func_002A6C58(void *, int, int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern Link408800 *func_002AB1F0(void *);
extern void func_002AB6D8(float *, float *);
extern void func_L00_00403CB8(void *);

extern Weapon408800 D_L00_00262570[];
extern void func_00282C88(void *);
extern void func_00283658(void *, void *);
extern Moby408800 *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern void func_002A6C58(void *, int, int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A7940(void);
extern Link408800 *func_002AB1F0(void *);
extern void func_002AB6D8(float *, float *);
extern void func_L00_00403CB8(void *);
extern void func_002ACA50(void *, void *, int);
extern float func_00283248(float, float);
extern char D_L00_001B2030;
extern u8 D_00139578[];
extern s32 D_001A8FF4[] __attribute__((sda));
extern s32 D_001A8FF0[] __attribute__((sda));
typedef struct { char pad[0x80]; f32 x; f32 y; } Resident408800;
extern Resident408800 D_00189E20;

Moby408800 *func_L00_00408800(Moby408800 *self)
{
    f32 mtx[16] __attribute__((aligned(16)));
    Moby408800 *m;
    Vars408800 *vars;
    Link408800 *link;
    Weapon408800 *w;
    f32 rate;

    m = func_0029EFD0(0xEB0);
    if (m != 0) {
        m->f32 = m->alpha = 0x7F;
        m->f31 = 1;
        vars = m->vars;
        m->scale = func_002A7878(0.85f, 1.15f);
        qcopy(m->pos, self->pos);
        if (D_001A8FF4[0] != 0 || D_001A8FF0[0] != 0) {
            func_00283658(mtx, self->mtx);
            func_002AB6D8(mtx, m->rot);
        } else {
            func_00282C88(m->rot);
            m->rot[2] = func_00283248(m->pos[0] - D_00189E20.x, m->pos[1] - D_00189E20.y);
        }
        m->state = 1;
        vars->f56 = 0;
        vars->delay = func_002A7820(0x78, 0x12C);
        vars->f70 = 600;
        vars->f74 = 15;
        vars->f5C = 0;
        vars->f78 = 0;
        m->state = 4;
        m->f98 = m->cls->f10;
        w = &D_L00_00262570[D_00139578[0]];
        rate = 1.0f;
        if (w->f4 != 0) {
            rate = 4.0f;
        }
        vars->rate = rate;
        vars->f60 = -1;
        if (m->flags & 0x1000) {
            func_002A6C58(self, 0, 3);
        }
        link = func_002AB1F0(self);
        if (link != 0 && link->mode == 1) {
            link->mode = 2;
        } else {
            func_0029F338(self);
        }
        func_002ACA50(m, &D_L00_001B2030, 0x1F);
        func_002A0F48(m);
    }
    return m;
}
