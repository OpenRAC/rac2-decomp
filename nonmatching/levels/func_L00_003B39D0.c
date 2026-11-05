/* 5 November 2026: default profile, no wrapper, 296/292. Declaring position before data (object dies at the data load) ties. Measured cause: the data load only reaches the call through an anti edge, while the mask load feeds $a2, and the 0.25f mtc1 takes the one memory slot at t3, so `a0 = position` issues first. Volatile data + volatile mask (read_dependence orders two volatile reads) gives retail's data-before-mask and a0-in-slot order, but a volatile cast on mask breaks %lo folding and a volatile mask field blocks dbr (jal slot nop): not the source. Next: something that gives the data load a true or memory edge into the call. */
/* 5 November 2026 (w-c4): sched1 dump: data load (insn 11) prio 3 loses the memory unit to f12 (25, prio 4) and mask (27, prio 4), so a0 = position (21) issues first. Reusing the parameter as position (`position = &obj->position` after the data load) does order the load first via the anti edge, but object and position then share s0 (daddu s0,a0; addiu s0,s0,0x10): 296/292. A copy into a fresh position var gives 308. */
/* 4 November 2026 current-RAC1 source-method trial; retained, not linked.
 * Grouping the actual data read or actual collision-result call gives 292/292 bytes, 0/27 USA
 * placements, first +0x4, with the default G0 profile. The entry schedule and subsequent
 * allocation remain different; no empty barrier or invented access was used.
 */
/* Claude Opus 5.5 (xhigh), 2026-10-31: code below unchanged, remeasured.
 * -fno-schedule-insns: 292/292 bytes, 0/27 places, 11 register/order lines in the arms.
 * Default -O2 -G0 -ffunction-sections: 296/292, 0/27; only the entry block differs, and it
 * causes the extra word. So sched1 was on in retail (the arms need it); the entry is the blocker.
 * sched1 priorities there (-fsched-verbose-5): position 4, f12 4, a2 load 4, data load 3,
 * a0 = position 3. f12 and both loads share the one memory unit, so a0 = position issues before
 * the data load, the object pseudo overlaps $a0 and takes $v1. Retail needs the load first, so
 * the load needs priority >= 4 or a boundary. Ties: float local for 0.25f, true prototype
 * (void *, int, void *, float), -g, -frac2-qcopy, -fno-gcse, -fno-expensive-optimizations,
 * -fno-strength-reduce, -fno-rerun-loop-opt, -fno-regmove, -fno-rerun-cse-after-loop.
 * Diagnostic only, forbidden wrapper: do { } while (0) just before the call gives 292/292 on the
 * default profile with the whole body right, but the note also binds sched2, so the prologue
 * order still differs: not exact. `if (hero)` keeps a real test.
 * Reopen with: an independent reason for the data load to precede a0 = position.
 */
/* GPT-6.1 Sol (high), 2026-10-29. Retained near miss; not linked.
 * Profile: -O2 -G0 -ffunction-sections -fno-schedule-insns.
 * USA v1.01: 292/292 bytes, 0/27 places. The first scheduling pass caused
 * the extra object-pointer copy in the older 296-byte draft. Disabling it
 * reproduces the complete retail prologue and first vector operations.
 * Remaining: projection/remaining use s0/s1 rather than s1/s0, and both
 * func_00283028 calls put the third argument in the delay slot instead of
 * retail's first/second argument. Reusing the position variable regresses
 * allocation; aggregate temporary storage ties. FP-first collision arguments,
 * -fno-force-mem, -fno-sched-spec and -fno-sched-interblock retain 296 bytes.
 * The declarations below are complete; the source needs the profile above.
 */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { char pad00[0xb0]; float origin[4]; char padc0[0x21d0]; int mask; } CollisionState;
extern CollisionState D_00189E20;
extern Quad D_L00_001BF230[2];
extern int D_L00_001A8FF0[] __attribute__((sda));
extern int func_00277258(void *,int,float,void *);
extern void func_00282CF0(float *,void *,void *);
extern void func_00282F20(float *,float *,float);
extern float func_00282DB0(float *,float *);
extern void func_00282D30(float *,float *,float);
extern void func_00283028(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);

typedef struct { char pad[0x10]; Quad position; char pad20[0x48]; char *data; } CollisionObject;

void func_L00_003B39D0(CollisionObject *object)
{
    float normal[4],projection[4],remaining[4];
    char *data=object->data;
    void *position=&object->position;
    int collided;
    do {
        collided = func_00277258(position,0,0.25f,(void *)D_00189E20.mask);
    } while (0);
    if (collided) {
        qcopy(position,D_L00_001BF230);
        if(D_L00_001A8FF0[0]) {
            float dot;
            data+=0x30;
            func_00282CF0(normal,D_00189E20.origin,position);
            func_00282F20(normal,normal,1.0f);
            dot=func_00282DB0(normal,(float *)data);
            func_00282D30(projection,normal,dot);
            func_00282CF0(remaining,data,projection);
            func_00283028(data,remaining,&D_L00_001BF230[1]);
            func_00282CC0(data,data,projection);
        } else {
            float vertical=*(float *)(data+0x38);
            *(float *)(data+0x38)=0;
            func_00283028(data+0x30,data+0x30,&D_L00_001BF230[1]);
            *(float *)(data+0x38)=vertical;
        }
    }
}
