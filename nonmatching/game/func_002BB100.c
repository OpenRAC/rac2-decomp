/* 8 November 2026 (Sonnet round): re-measured 14 positions; permuter -j2 25 min from the note's C: best 925 vs base 930, no plain gain. Gap A unchanged. */
/* 8 November 2026, permuter round 4 (35 min -j3, base 130): best 120 only by duplicating the then-arm under `if (cfg->minimum || ai)` (reads uninitialised ai), invalid; no plain gain. C below unchanged, 5 positions (gap A). */
/* 8 November 2026, round 3 (gap A only, 12 checks, best body unchanged): no plain form
 * makes $s0 live at the else target. Tried: function-scope `n = D_001BAFC0` before the if
 * (+0x8, 53 diffs); inverted `if (!(flags&1) || !call) copy; else {...}` (1680 bytes);
 * `hit = 0; if (flags&1) hit = call; if (hit)` (1688); else arm as qcopy() (1692; the asm
 * needs a register base, retail uses 0x10(s5)); unit flags -frac2-qcopy(+barrier) (1696),
 * -frac2-hazard-labels, -frac2-sticky-volatile-refs, -fno-sched-interblock, -g (all 5).
 * Retail never reads $s0 after the join, so no real value can be live there.
 */
/* 8 November 2026, round 2 (Claude Opus 5.5, v101/m1k): gap (B) CLOSED with the
 * allowed dead-test helper frac_byte below (one `if (result != 0) scaled = scale;`
 * on a dead float, hud_coord shape) for fractional[0] only: 65535 -> f21, 255 -> f20
 * as retail. Now 1684/1684, 0/28, first rejection +0xA4, only the 5 positions of
 * gap (A) remain (beqz slot after func_002761F8: retail addiu a0, ours lui s0).
 * (A) is not reachable with the dead-float shape: flow2 deletes that test, so $s0
 * is never live at the else target; it needs a test that survives flow2 on a value
 * in $s0 (only the uninitialised-variable form found, forbidden).
 * Inside src/game/002B7E28.c write `typedef TI Quad_BB100;`.
 */
/* 8 November 2026, Claude Opus 5.5 (task v101/m1k): body below unchanged, still
 * 1684/1684 bytes, 0/28 places, first rejection +0xA4, 14 real positions. 8 checks:
 * - (A) nested `if (flags&1) { if (call) {...} else copy; } else copy;`: no change
 *   (jump2 cross-jumps the copies, but flow2 already saw $s0 dead).
 * - (A) reorg: the lwc1s are refused by may_trap_p, not liveness; only $s0 liveness at
 *   the else target can stop the lui, so the slot needs a register read flow2 sees.
 * - (B) do/while(0) groups around the 255 uses, the 65535 uses, or both (nested):
 *   1676/1688/1676 bytes, the loop notes pin the constant loads late. Worse.
 * Local-alloc priorities (refs*log2(refs)/length): 65535 = 8/16 beats 255 = 10/42.
 */
/* Claude Opus 5.5 (xhigh), task v2092; USA v1.01, default game profile.
 * Body below unchanged (legal best, recompiled here): 1684/1684 bytes, 0/28 places,
 * first rejection +0xA4, 14 real positions differ. Both remaining differences are
 * diagnosed; each is fixed only by a construct the guide forbids, so FAILED.
 * Exact bytes (28/28 places, checked) with BOTH of these changes:
 * (A) +0x9C..+0xB0, beqz delay slot after func_002761F8: retail fills it with
 *     `addiu a0,sp,0x10` because $s0 is live at the else target in flow2's view.
 *     sched2 order already matches; only reorg differs. RAC1 form:
 *       } else {
 *           unsigned char *u;
 *           if (u) *(Quad_BB100 *)p->position=*(Quad_BB100 *)next;
 *           else *(Quad_BB100 *)p->position=*(Quad_BB100 *)next;
 *       }
 *     (uninitialised u gets $s0; jump2 merges the arms after flow2).
 * (B) +0x338..+0x394, 65535 in f21 and 255 in f20: a flow1 block split right after
 *     the 65535 set makes it global and leaves 255 local (local-alloc gives it f20 first):
 *       float c65 = 65535.0f, c255;
 *       if (PB(p,4) & 0x100) q->fractional[0] = 0;   (never taken; combine folds it)
 *       c255 = 255.0f;   then the seven conversions use c65/c255.
 *     This is RAC1's update_colliding_effect_particle hack too.
 * Needed for a legal match: (A) a real value already in $s0 tested on the else path
 * (nothing sets $s0 before the call in retail); (B) a real test between the two
 * constant sets that vanishes at jump2 (live register vs zero, arms differing in source).
 * None found: p/q/cfg null tests are always-true; flags tests leave their loads.
 * Inside src/game/002B7E28.c write `typedef TI Quad_BB100;` (the file already has TI).
 */
/* GPT-6.1 Sol, high effort; USA v1.01, default game profile.
 * Best check.py: 1684/1684 bytes, 0/28 places; first rejection +0xA4.
 * Fourteen instruction positions differ after disregarding relocation values:
 * five around +0x9C..+0xB0 (reflection destination address versus normal loads),
 * nine at +0x338..+0x394 (65535 in f20 and 255 in f21, reversed in retail).
 * The prologue, initial xyz addition, TI transfers and packed-color assembly
 * now agree. Keep separate conversion results live through alpha conversion,
 * then use a distinct packed accumulator; reusing the red result for the
 * accumulator changes its saved-register allocation.
 * Seventeen checker invocations (one typedef-scope compile error), including
 * a final successful compile/recheck, and two allocator diagnoses.
 * Raw/typed fields tie; explicit result-address local, FP-first reflection
 * declaration and alternate collision-global base tie on reflection setup.
 * Named constant locals and signed/unsigned color temporaries tie; reusing
 * normalization scale, pre-scaling RGB and an inline pack helper are worse.
 * Allocator on the best body: 65535 pseudo197 has 4 refs/16 insns/2 calls
 * and takes f20; 255 pseudo206 has 5 refs/42 insns/6 calls and takes f21.
 * Next: evidence for the original constant lifetimes or reflection destination
 * expression. Do not repeat tied declaration-only changes.
 * No linked build was run: this remains a near miss.
 */
#include "common.h"
extern float Fe617c30b_FUN_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002B9180(char *);
extern void func_00282CC0(char *, char *, char *);
typedef int Quad_BB100 __attribute__((mode(TI)));
typedef struct ParticleConfig_BB100 {
    float force[4];
    float minimum[4];
    float maximum[4];
    float sizeStep, spinStep, alphaStep, bounce, damping;
    float alphaMin, alphaMax;
    float colorStep[3], colorMin[3], colorMax[3];
    int flags;
    float sizeMin, sizeMax;
    char *owner;
} ParticleConfig_BB100;
typedef struct ParticleMotion_BB100 {
    float velocity[3];
    ParticleConfig_BB100 *config;
    float alpha, spin;
    u8 fractional[3], direction;
} ParticleMotion_BB100;
typedef struct Particle_BB100 {
    u8 type[4];
    int color;
    u8 spin, mode;
    short life;
    float size;
    float position[4];
    ParticleMotion_BB100 motion;
} Particle_BB100;
extern int func_00282978(void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern void func_002AB168(void *, void *, void *, float);
extern void func_00283410(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282FB8(void *, void *, float);
extern float D_001BAFC0[];
#define PF(p,o) (*(float *)((char *)(p)+(o)))
#define PI(p,o) (*(int *)((char *)(p)+(o)))
#define PB(p,o) (*(u8 *)((char *)(p)+(o)))
/* frac0 with a dead result test (dead-test rounding helper, allowed by owner ruling,
 * precedent src/game/002D2188-g8.c). */
static __inline__ int frac_byte(float value, float scale)
{
    float scaled = value * scale;
    int result = func_00283CF0(scaled);

    if (result != 0)
        scaled = scale;
    return result;
}
void func_002BB100(Particle_BB100 *p)
{
    float next[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float matrix[16] __attribute__((aligned(16)));
    ParticleMotion_BB100 *q = &p->motion;
    ParticleConfig_BB100 *cfg;
    float r,g,b;
    int ri,gi,bi,ai,packed;
    float x,y,z;
    x = p->position[0]+q->velocity[0];
    y = p->position[1]+q->velocity[1];
    z = p->position[2]+q->velocity[2];
    next[0]=x; next[1]=y; next[2]=z;
    cfg = q->config;
    if ((cfg->flags&1) && func_002761F8(p->position,next,4,p,0)) {
        velocity[0]=q->velocity[0]; velocity[1]=q->velocity[1]; velocity[2]=q->velocity[2];
        func_002AB168(temp,velocity,D_001BAFC0,cfg->bounce);
        q->velocity[0]=temp[0]; q->velocity[1]=temp[1]; q->velocity[2]=temp[2];
        func_00282F20(offset,D_001BAFC0,0.055f);
        func_00282CC0((char *)p->position,(char *)(D_001BAFC0-8),(char *)offset);
    } else *(Quad_BB100 *)p->position=*(Quad_BB100 *)next;
    if (cfg->flags&2) {
        r=Fe617c30b_FUN_00283CE0((PB(p,4)<<8)|q->fractional[0])* (1.0f/65535.0f);
        g=func_00283CF0((float)((p->color&0xff00)|q->fractional[1]))*(1.0f/65535.0f);
        b=func_00283CF0((float)(int)(((u32)p->color>>8 &0xff00)|q->fractional[2]))*(1.0f/65535.0f);
        if(q->direction&16) r-=cfg->colorStep[0]; else r+=cfg->colorStep[0];
        if(q->direction&32) g-=cfg->colorStep[1]; else g+=cfg->colorStep[1];
        if(q->direction&64) b-=cfg->colorStep[2]; else b+=cfg->colorStep[2];
        if(r>cfg->colorMax[0]) {r=cfg->colorMax[0];if(cfg->flags&0x100)q->direction^=16;}
        if(r<cfg->colorMin[0]) {r=cfg->colorMin[0];if(cfg->flags&0x10)q->direction^=16;}
        if(g>cfg->colorMax[1]) {g=cfg->colorMax[1];if(cfg->flags&0x200)q->direction^=32;}
        if(g<cfg->colorMin[1]) {g=cfg->colorMin[1];if(cfg->flags&0x20)q->direction^=32;}
        if(b>cfg->colorMax[2]) {b=cfg->colorMax[2];if(cfg->flags&0x400)q->direction^=64;}
        if(b<cfg->colorMin[2]) {b=cfg->colorMin[2];if(cfg->flags&0x40)q->direction^=64;}
        q->fractional[0]=frac_byte(r,65535.0f);
        q->fractional[1]=func_00283CF0(g*65535.0f);
        q->fractional[2]=func_00283CF0(b*65535.0f);
        ri=func_00283CF0(r*255.0f);
        gi=func_00283CF0(g*255.0f);
        bi=func_00283CF0(b*255.0f);
        ai=func_00283CF0(q->alpha*255.0f);
        packed=ri&255;
        packed|=(gi&255)<<8;
        packed|=(bi&255)<<16;
        packed|=ai<<24;
        p->color=packed;
    } else if(cfg->flags&4) p->color=(p->color&0xffffff)|(func_00283CF0(q->alpha*255.0f)<<24);
    if(cfg->flags&4) {
        if(q->direction&128) q->alpha-=cfg->alphaStep; else q->alpha+=cfg->alphaStep;
        if(q->alpha>cfg->alphaMax) {q->alpha=cfg->alphaMax;if(cfg->flags&0x800)q->direction^=128;}
        if(q->alpha<cfg->alphaMin) {q->alpha=cfg->alphaMin;if(cfg->flags&0x80)q->direction^=128;}
    }
    p->spin=func_00283CF0(q->spin*255.0f);
    if(cfg->flags&8) {
        next[0]=q->velocity[0];next[1]=q->velocity[1];next[2]=q->velocity[2];
        if(cfg->flags&0x8000) {
            func_00283410(matrix,cfg->owner+0xf0);
            func_002830C0(temp,cfg,matrix);
        } else *(Quad_BB100 *)temp=*(Quad_BB100 *)cfg;
        func_00282CC0((char *)next,(char *)next,(char *)temp);
        func_00282FB8(next,next,cfg->damping);
        q->velocity[0]=next[0];q->velocity[1]=next[1];q->velocity[2]=next[2];
    }
    p->size+=cfg->sizeStep;
    if(p->size<cfg->sizeMin)p->size=cfg->sizeMin;
    if(p->size>cfg->sizeMax)p->size=cfg->sizeMax;
    q->spin+=cfg->spinStep;
    if(q->alpha<=0.0f || func_00282978(&p->life) || p->position[0]<cfg->minimum[0] || p->position[1]<cfg->minimum[1] || p->position[2]<cfg->minimum[2] || p->position[0]>cfg->maximum[0] || p->position[1]>cfg->maximum[1] || p->position[2]>cfg->maximum[2]) func_002B9180((char *)p);
}
#undef PF
#undef PI
#undef PB
