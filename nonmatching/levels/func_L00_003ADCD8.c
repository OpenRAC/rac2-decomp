/* Safety review, 30 October 2026: historical draft below is NOT valid C.
 * It reads and writes 16 bytes through the addresses of 4-byte pointer
 * parameters a and b. Their retail stack slots are +0x30 and +0x34; the
 * two-argument caller passes ordinary moby pointers, not vector values.
 * Do not compile or promote those out-of-bounds TI dereferences. Retained
 * solely to preserve the previous experiment. Reopen with an independently
 * evidenced complete object and valid R5900 lowering for these operations;
 * register pins, invented padding and fake volatile are not remedies.
 */
/* func_L00_003ADCD8 - 456 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft is a whole new file L00_003ADCD8-g8-qcopy-dbg.c; flags line to add to
   config/cflags.txt (copied from L00_003A7C30-g8-qcopy-dbg.c):
     src/levels/shared/L00_003ADCD8-g8-qcopy-dbg.c<TAB>-O2 -G8 -ffunction-
   sections -frac2-qcopy -frac2-qcopy-barrier -g
   460 B vs 456 B. Frame/regs/locals (vecs[3] -> tmp@0, 0x10, 0x20; a,b
   spilled at 0x30/0x34) match. Retail quirk: `lq a-slot; lq b-slot; sq
   ->b-slot; sq ->a-slot` on the spilled params (4-byte slots, so it is a no-
   op swap of two pointers via 16-byte ops) using address regs s6=&a, s5=&b
   set after the loop guard.
   Remaining diff: mine loads pb quad before pa quad; the `beql` with lwc1 f12
   (D_L00_001AF7D8) in the likely delay slot is not reproduced (mine beqz +
   reloads); 4 extra bytes.
   Tried: TI deref via &a/&b directly (sp-immediate addressing, wrong), Qword
   *pa/*pb hoisted at declaration (computed in prologue, wrong), assigned just
   before the loop (current), qcopy() through temps (+40 B). */

#include "common.h"

typedef int Qword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x10];
    Qword pos;
    unsigned char kind;
    char pad21[0x89];
    short group;
} BurstObj;

extern int D_L00_001AF7D0 __attribute__((sda));
extern float D_L00_001AF7D4 __attribute__((sda));
extern float D_L00_001AF7D8 __attribute__((sda));
extern int func_001163B0(void);
extern float func_0031A7C0(float, float);
extern int func_002EF250(float);
extern float func_002EF240(int);
extern void func_002EE138(void *, void *, void *);
extern float func_002EE238(void *);
extern void func_002EE178(void *, void *, float);
extern void func_002EE120(void *, void *, void *);
extern void func_002EE3D0(void *, void *, float);
extern int func_0031A728(int);
extern void func_0033A2B0(void *, void *, int, int, int, float, int);

void func_L00_003ADCD8(BurstObj *a, BurstObj *b)
{
    Qword vecs[3];
    Qword *pa;
    Qword *pb;
    int i;
    int life;
    float len;

    if (b == 0)
        return;
    if (a->group != b->group)
        return;
    if (b->kind == 0xFE)
        return;
    if (b->kind == 0xFD)
        return;
    pa = (Qword *)&a;
    pb = (Qword *)&b;
    for (i = 0; i < D_L00_001AF7D0; i++) {
        float spread;

        if (func_001163B0() & 1) {
            Qword t1 = *pa;
            Qword t2 = *pb;
            *pb = t1;
            *pa = t2;
        }
        spread = D_L00_001AF7D8;
        vecs[1] = a->pos;
        life = func_002EF250(func_0031A7C0(spread * 0.5f, spread));
        func_002EE138(&vecs[2], &b->pos, &vecs[1]);
        vecs[0] = vecs[2];
        len = func_002EE238(&vecs[0]);
        func_002EE178(&vecs[0], &vecs[0], func_0031A7C0(0.0f, 0.9f));
        func_002EE120(&vecs[2], &vecs[1], &vecs[0]);
        func_002EE3D0(&vecs[0], &vecs[0], func_0031A7C0(0.16666667f, len / func_002EF240(life << 2)));
        func_0033A2B0(&vecs[1], &vecs[0], 0x604040FF, life & 0xFF, func_0031A728(0xFF) & 0xFF, D_L00_001AF7D4, 0);
    }
}
