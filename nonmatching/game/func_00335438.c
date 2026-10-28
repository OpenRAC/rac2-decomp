/* func_00335438 - 364 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft is a whole new file src/game/00335438-qcopy.c with config/cflags.txt
   line:
     src/game/00335438-qcopy.c<TAB>-O2 -G0 -ffunction-sections -frac2-qcopy
   -frac2-qcopy-barrier
   (remove the INCLUDE_ASM marker from src/game/0032EB28.c). Size 364 matches;
   whole function matches except the last block (type==3):
   - retail: lui a2,0x19; addiu v1,s3,0x110; addiu a2,a2,-0x6160; lq v0,0(a2);
   sq v0,0(v1)   (src address in a2, dst in v1)
   - mine:   lui v1; addiu a0,s3,0x110; addiu v1,v1,0; lq v0,0(v1); sq
   v0,0(a0)
   Key finds: sub = (Sub*)&d->e0 (d+0xE0) taken right after d = obj->f70 gives
   the s5 base and the a3 spill; d80 = &d->q80 as an early local pointer; `if
   (type != 2) { if (type != 3) return; ...} common tail`.
   Tried: local src pointer for D_00189EA0, d90 pointer hoist (worse). */

#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[0x30];
    TI128 q30;
    TI128 q40;
    unsigned char pad50[0x20];
    void *f70;
    unsigned char pad74[9];
    unsigned char b7D;
    unsigned char pad7E[10];
    unsigned char b88;
} Obj_335438;

typedef struct {
    unsigned char pad0[0x80];
    TI128 q80;
    TI128 q90;
    unsigned char padA0[0x40];
    int e0;
    int e4;
    unsigned char padE8[0x14];
    unsigned char fc[0x14];
    TI128 q110;
} Dat_335438;

typedef struct {
    int w0;
    int w4;
    unsigned char pad8[0x38];
    int t40;
    float f44;
    int w48;
} Sub_335438;

extern TI128 D_001B5340[2];
extern TI128 D_00189EA0;

extern Obj_335438 *func_00270280(int id);
extern void func_00270598(void *obj);
extern void func_00272550(void *a0, void *a1);

void func_00335438(TI128 *a, TI128 *b, int type, int value, int count)
{
    Obj_335438 *obj;
    Dat_335438 *d;
    Sub_335438 *sub;
    TI128 *d80;
    TI128 pa, pb, pc, pd;

    obj = func_00270280(5);
    qcopy(&pa, a);
    qcopy(&pb, b);
    qcopy(&pc, &D_001B5340[0]);
    qcopy(&pd, &D_001B5340[1]);
    func_00270598(obj);
    d = obj->f70;
    sub = (Sub_335438 *)&d->e0;
    d80 = &d->q80;
    obj->b7D = 1;
    qcopy(&obj->q30, &pa);
    qcopy(&D_001B5340[0], &pa);
    qcopy(&obj->q40, &pb);
    qcopy(d80, &pa);
    qcopy(&d->q90, &pb);
    sub->t40 = count;
    obj->b88 = type;
    if (type != 2) {
        if (type != 3)
            return;
        sub->f44 = 1.0f;
        sub->w48 = 0;
        qcopy(&obj->q30, &pc);
        qcopy(&obj->q40, &pd);
        qcopy(&d->q110, &D_00189EA0);
        func_00272550(d->fc, &pc);
    }
    sub->w4 = value;
    d->e0 = value;
}
