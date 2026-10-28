/* func_00330CA0 - 420 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft = whole new file src/game/00330CA0-g8.c, flags line
   (config/cflags.txt):
     src/game/00330CA0-g8.c<TAB>-O2 -G8 -ffunction-sections -ffast-math
   (min.s needs fast-math; gp access needs -G8)
   (remove marker from src/game/0032EB28.c). 436 B vs 420 B; frame 0xB0 vs
   0xA0.
   Found: ternary `D < src ? D : src` gives min.s f12,f12,f0; locals struct
   {TI128 dir; Hit q;} puts dir at sp+0, q at sp+0x10; q is normalised
   (func_00282F20) before it is initialised, as in retail; constant is
   5627.9248f (0x45AFDF66); byte table D_00139568[0x20], class table at
   0x239BA0 (+0x70 float), skip object D_00189E20+0x2290.
   Remaining: mine hoists 5627.9248f into $f21 (retail saves only $f20 and
   builds the constant with lui/ori/mtc1 $f0 at the store); mine hoists 0x2290
   base ($fp) and table bases differently (retail: fp=D_00139568, s7=class
   table, skip base lui each time); retail has s6=0xE0, s5=1 hoisted
   constants.
   Tried: nested if instead of `continue`, min as if/else (c.lt, worse), plain
   locals (dir ended at sp+0x40). */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[0x1C];
    float w;
    unsigned char pad20[8];
    unsigned char b28;
    unsigned char b29;
    unsigned short s2A;
    unsigned char pad2C[4];
    int w30;
} Hit_330CA0;

typedef struct {
    unsigned char pad0[0x70];
    float f70;
    unsigned char pad74[0x6C];
} Class_330CA0;

typedef struct Mob_330CA0 {
    unsigned char pad0[0x10];
    TI128 pos;
    unsigned char pad20[0x14];
    unsigned short flags34;
    unsigned char pad36[0x74];
    unsigned short s_AA;
} Mob_330CA0;

typedef struct {
    unsigned char pad0[0x64];
    float f64;
} Src_330CA0;

typedef struct {
    unsigned char pad0[0x10];
    TI128 pos;
    unsigned char pad20[0x48];
    Src_330CA0 *src;
    unsigned char pad6C[0x4C];
    int wB8;
} Self_330CA0;

extern float D_001B0954 __attribute__((sda));
extern Mob_330CA0 *D_001BF000[];
extern unsigned char D_00139568[];
extern Class_330CA0 D_00239BA0[];
extern struct { unsigned char pad[0x2290]; Mob_330CA0 *skip; } D_00189E20;

extern int func_00277F48(float, void *, int, void *, int);
extern int func_002AB1F0(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002A8C00(void *, void *, int, float, void *);
extern void func_002A8E20(void *, void *);
extern void func_0032D758(void *, int, int);

void func_00330CA0(Self_330CA0 *self)
{
    struct {
        TI128 dir;
        Hit_330CA0 q;
    } L;
    int count;
    int i;
    Mob_330CA0 *m;
    float r;

    r = D_001B0954 < self->src->f64 ? D_001B0954 : self->src->f64;
    count = func_00277F48(r, &self->pos, 0, self, 0);
    for (i = 0; i < count; i++) {
        m = D_001BF000[i];
        if (func_002AB1F0(m) || (m->flags34 & 0x4000)) {
            if (m != D_00189E20.skip) {
                func_00282CF0(&L.dir, &m->pos, &self->pos);
                func_00282F20(&L.dir, &L.dir, 1.0f);
                func_00282F20(&L.q, &L.q, 1.0f);
                func_002A8C00(&L.q, self, 0x810000, D_00239BA0[D_00139568[0x20]].f70, &L.dir);
                qcopy(&L.q, &L.dir);
                L.q.w = 5627.9248f;
                L.q.b28 = 5;
                L.q.b29 = 3;
                L.q.w30 = 1;
                L.q.s2A = m->s_AA;
                func_002A8E20(m, &L.q);
                func_0032D758(m, 0x4E, self->wB8);
            }
        }
    }
}
