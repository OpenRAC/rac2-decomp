/* func_002E5AD0 - 552 bytes.  Worker attempt, 27 October 2026 (draft below).

   Not at handoff quality (476 B vs 552). Logic and field offsets decoded
   (draft.c); needs a new file src/game/002E10B8-qcopy.c with cflags `-O2 -G0
   -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`.
   Problem: retail recomputes `mult a0,s0,a0` (index*0x70, constant 0x70
   reloaded) in each basic block/branch arm; mine CSEs it once into a2 across
   the whole function, and the first condition (`sltiu v1,b18,1` + `xori`) is
   shaped differently. Pool = D_00188660, entries 0x70 apart, fields start
   0x70 after the entry base.
   Second pass: tried 3-way if/else-if chain (src / vec / neither), pool as
   array of 0x70-byte PoolEntry indexed [i+1], xori/sltiu variants for the
   first test; size stays 476 vs 552. Retail ends with a single `return index`
   epilogue (addiu s0,-1 / daddu v0,s0) and recomputes `mult` per basic block;
   mine CSEs the multiply. */

#include "include_asm.h"
#include "common.h"


/* One 0x70-byte record of the pool at D_00188660. The first record of the pool is a header; the
   entries start at the second one. */
typedef struct {
    int f70;
    u8 state;
    u8 flags;
    u8 pad06[2];
    char *owner;
    u16 id;
    short f7e;
    short arg;
    short f82;
    int f84;
    int f88;
    int f8c;
    float f90[4];
    float fa0[4];
    float fb0;
    u8 pad_b4[0x2C];
} PoolEntry2E5AD0;

typedef struct {
    u8 pad00[0x10];
    int start;
    int end;
    u8 b18;
    u8 pad19;
    u16 id;
} Source2E5AD0;

extern PoolEntry2E5AD0 D_00188660[];

extern int func_002E5A50(int);
extern void func_00282C88(void *);
extern int func_002E46C0(void *, void *);
extern int func_002A77E0(int);

#define SLOT(i) (&D_00188660[(i) + 1])

int func_002E5AD0(Source2E5AD0 *obj, int flags, char *src, char *vec, int arg)
{
    int index;
    int distance;
    int end;
    int none = obj->b18 == 0;

    if ((flags & 4) ? none : none ^ 1)
        return -1;
    index = func_002E5A50((int)src);
    if (index >= 0x34)
        return -1;
    SLOT(index)->owner = (char *)obj;
    SLOT(index)->fb0 = -1.0f;
    SLOT(index)->id = obj->id;
    SLOT(index)->f7e = -1;
    SLOT(index)->arg = arg;
    SLOT(index)->f88 = 0;
    SLOT(index)->f8c = 0;
    qzero(SLOT(index)->fa0);
    if (src != 0) {
        qcopy(SLOT(index)->f90, src + 0x10);
        SLOT(index)->f90[2] += 1.0f;
    } else if (vec != 0) {
        qcopy(SLOT(index)->f90, vec);
    } else {
        flags |= 0x11;
        func_00282C88(SLOT(index)->f90);
    }
    if (flags & 0x10)
        distance = arg;
    else
        distance = func_002E46C0((u8 *)SLOT(index) - 0x20, SLOT(index));
    if (distance < 0x20)
        return -1;
    SLOT(index)->flags = flags;
    SLOT(index)->state = 7;
    SLOT(index)->f82 = 0;
    end = obj->end;
    if (end != obj->start)
        end = func_002A77E0(end - obj->start) + obj->start;
    SLOT(index)->f70 = -1;
    SLOT(index)->f84 = end;
    return index;
}
