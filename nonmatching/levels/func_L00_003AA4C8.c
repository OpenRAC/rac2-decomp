/* func_L00_003AA4C8 - 572 bytes.  Worker attempt, 27 October 2026 (draft below).

   Needs its own file with flags `-O2 -G0 -ffunction-sections -g` (nop pair
   before div.s; a separate statement `per = ...; rate = 40.0f / per;` so a
   line label sits between). Draft is the whole file L00_003AA4C8.c (add
   config/cflags.txt line). Registers all match now (obj=s3); locals in struct
   {Qword tmp; int c[3];} give retail stack layout.
   568 B vs 572 B. Remaining diff (all in the first 12 instructions + 1 nop):
   - retail: addiu a0,1 / addiu v0,0xFF / addiu v1,0xFF; sb a0,0x31; sh
   v1,0x32; sb v0,0x30; sb zero,0x20  (two separate 0xFF registers). Mine: one
   0xFF reg shared by sh 0x32 and sb 0x30, 1 in v0; stores 0x30,0x32,0x31.
   - one nop of the second pre-div.s pair (after jal 2EF250 / mov.s f12)
   missing in mine: retail jal; mov.s; nop; nop; div.s.
   Tried: store order permutations, int c[3] vs three ints, early d=obj->data. */

#include "common.h"

typedef int Qword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x50];
    float rate;
    char pad54[0x8C];
} SpawnClass;

typedef struct {
    char pad0[0x14];
    int w14;
    short s18;
    short s1A;
    int w1C;
    float f20;
    int w24;
    int w28;
    int w2C;
    int w30;
    float f34;
    int w38;
    int w3C;
    char pad40[0x10];
    float f50;
    char pad54[4];
    int w58;
    int w5C;
    char pad60[0x10];
    int w70;
    int w74;
    int w78;
    int w7C;
} SpawnData;

typedef struct {
    char pad0[0x10];
    Qword pos;
    char pad20[0xC];
    float f2C;
    char pad30[4];
    unsigned short flags;
    char pad36[0x32];
    SpawnData *data;
} SpawnObj;

extern unsigned char D_00139580;
extern SpawnClass D_L00_00262570[];
extern SpawnObj *func_003100D8(int);
extern int func_002EF250(float);
extern int func_0031A728(int);
extern void func_003120E8(void *, int *, int *, int *);
extern void func_003251D0(void *, void *, int);
extern void func_002EE3D0(void *, void *, float);
extern void func_002EE220(void *, void *, void *);
extern void func_0031A2A0(void *, int, int);
extern int func_0037E0F8(void *, int, float, float, float);

SpawnObj *func_L00_003AA4C8(Qword *pos, Qword *dir, int unused, int arg)
{
    SpawnObj *obj;
    SpawnData *d;
    struct { Qword tmp; int c[3]; } L;
    float per, rate, inv;
    int life;

    obj = func_003100D8(0xD01);
    if (obj) {
        ((unsigned char *)obj)[0x31] = 1;
        *(short *)((char *)obj + 0x32) = 0xFF;
        ((unsigned char *)obj)[0x30] = 0xFF;
        ((unsigned char *)obj)[0x20] = 0;
        d = obj->data;
        per = D_L00_00262570[D_00139580].rate * 0.016666668f;
        rate = 40.0f / per;
        life = func_002EF250(rate);
        inv = 1.0f / rate;
        d->w74 = arg;
        d->w14 = 0;
        d->w30 = 0;
        d->w24 = 0;
        d->w28 = 0;
        d->w2C = 0;
        d->w78 = 5;
        d->f20 = 3.1415927f;
        d->s18 = life;
        d->f34 = inv;
        d->s1A = func_0031A728(0xFF);
        d->w3C = 0;
        d->w1C = 0;
        d->w7C = 0;
        d->w58 = 0;
        d->f50 = 0.5f;
        d->w5C = -1;
        func_003120E8(obj, &L.c[0], &L.c[1], &L.c[2]);
        d->w38 = (L.c[2] << 16) | (L.c[1] << 8) | L.c[0];
        obj->f2C *= 1.5f;
        qcopy(&obj->pos, pos);
        qcopy(d, dir);
        obj->flags |= 0x100;
        func_003251D0(&obj->pos, &L.tmp, 1);
        func_002EE3D0((char *)obj + 0xC0, d, 1.0f);
        func_002EE220((char *)obj + 0xD0, (char *)obj + 0xC0, &L.tmp);
        func_002EE3D0((char *)obj + 0xD0, (char *)obj + 0xD0, 1.0f);
        func_002EE220((char *)obj + 0xE0, (char *)obj + 0xD0, (char *)obj + 0xC0);
        func_0031A2A0(obj, 2, 0);
        d->w70 = func_0037E0F8(obj, 0, 1.0f, 1.0f, 1.0f);
    }
    return obj;
}
